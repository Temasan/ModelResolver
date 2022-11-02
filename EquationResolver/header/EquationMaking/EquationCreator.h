//
// Created by artem on 01.11.2022.
//

#ifndef EQUATIONRESOLVER_EQUATIONCREATOR_H
#define EQUATIONRESOLVER_EQUATIONCREATOR_H
#include <string>
#include <stack>
#include <regex>
#include "EquationRules.h"

template<typename TNode>
class EquationCreator{
    class Token{
    public:
        explicit Token(std::string const & name, EquationResolver::Rule rule)
            : m_name(name)
            , m_rule(rule){}

        inline std::string const & name() const{
            return m_name;
        }

        inline EquationResolver::Rule const type() const{
            return m_rule;
        }
    private:
        std::string m_name;
        EquationResolver::Rule m_rule;
    };

    std::vector<Token> make_tokens(std::string const &e){
        std::string buff;
        std::vector<Token> smbl{};
        EquationResolver::Rule token_state = EquationResolver::Rule::constVal;
        for(auto it = e.begin(); it != e.end(); ++it){
            if(*it != ' '){
                auto char_state = EquationResolver::signToRule(*it);
                switch (char_state) {
                    case EquationResolver::Rule::variable:
                        token_state = EquationResolver::Rule::variable;
                    case EquationResolver::Rule::constVal:
                        buff.push_back(*it);
                        break;
                    default:
                        smbl.emplace_back(Token(buff, token_state));
                        smbl.emplace_back(Token({*it}, char_state));
                        token_state = EquationResolver::Rule::constVal;
                        buff.clear();
                }
            }
        }
        if(!buff.empty()){
            smbl.emplace_back(Token(buff, token_state));
        }
        return smbl;
    }

public:
    EquationCreator() = default;
    std::pair<std::shared_ptr<TNode>, std::vector<std::shared_ptr<TNode>>> make(std::string const &e){
        std::string_view equation{e};
        std::string buff;
        std::vector<std::shared_ptr<TNode>> nodes;
        std::shared_ptr<TNode> head;
        for(auto token: make_tokens(e)){
            if(token.type() == EquationResolver::Rule::variable ||
                    token.type() == EquationResolver::Rule::constVal){
                auto new_node = TNode::make_node(token.name().find('.') != std::string::npos ?
                                                    std::stod(token.name()):
                                                    std::stoi(token.name()),
                                                    token.type()) ;
                // todo append check for one or ternary operations
                if(m_operationStack.size() && m_variableStack.size()){
                    auto left_node = m_variableStack.top();
                    m_variableStack.pop();
                    auto head_node = m_operationStack.top();
                    m_operationStack.pop();
                    head_node->assignChildLeft(left_node);
                    head_node->assignChildRight(new_node);

                    left_node->assignParent(head_node);
                    new_node->assignParent(head_node);
                    m_variableStack.push(head_node);
                }
                else {
                    m_variableStack.push(new_node);
                    if(token.type() == EquationResolver::Rule::variable){
                        nodes.push_back(new_node);
                    }
                }
            }
            else{
                if(token.type() == EquationResolver::Rule::bracket_open ||
                token.type() == EquationResolver::Rule::bracket_close){
                    m_operationStack.push(nullptr);
                }
                else {
                    m_operationStack.push(TNode::make_node(0., token.type()));
                }
            }
        }
        while(!m_operationStack.empty()){
            auto head_node = m_operationStack.top();
            m_operationStack.pop();
            auto left_node = m_variableStack.top();
            m_variableStack.pop();
            auto right_node = m_variableStack.top();
            m_variableStack.pop();

            head_node->assignChildLeft(left_node);
            head_node->assignChildRight(right_node);

            left_node->assignParent(head_node);
            right_node->assignParent(head_node);
            m_variableStack.push(head_node);
        }
        head = m_variableStack.top();
        m_variableStack.pop();
        head->calc(true);
        return std::make_pair(head, nodes);
    }
private:
    std::stack<std::shared_ptr<TNode>> m_variableStack;
    std::stack<std::shared_ptr<TNode>> m_operationStack;
};
#endif //EQUATIONRESOLVER_EQUATIONCREATOR_H
