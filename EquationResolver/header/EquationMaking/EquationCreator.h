//
// Created by artem on 01.11.2022.
//

#ifndef EQUATIONRESOLVER_EQUATIONCREATOR_H
#define EQUATIONRESOLVER_EQUATIONCREATOR_H
#include <string>
#include <stack>
#include <regex>

template<typename TNode>
class EquationCreator{
public:
    EquationCreator() = default;
    std::pair<TNode, std::vector<TNode>> make(std::string const &e){
        std::string_view equation{e};
        std::string buff;
        special_symbl buff_status = constant;
        for(auto it = equation.begin(); it != equation.end(); ++it){
            auto smb_status {check(*it)};
            switch(smb_status){
                case variable:
                    buff_status = variable;
                case constant:
                    buff.push_back(*it);
                    break;
                case operation:
                    m_variableStack.push(buff_status == constant ?
                        TNode::element_type::make_const_node(std::stod(buff)) : // todo
                        TNode::element_type::make_variable_node(buff, 0.) );
                    break;
                case bracket_open:
                    // todo
                    buff.push_back(*it);
                    break;
                case bracket_close:
                    // todo
                    buff.push_back(*it);
                    break;
                case assign:
                    // todo
                    buff.push_back(*it);
                    break;
            }
        }
    }
private:
    enum special_symbl{
        variable,
        constant,
        operation,
        bracket_open,
        bracket_close,
        assign
    };
    special_symbl check(char smb){
        // todo
    }
    std::stack<TNode> m_variableStack;
    std::stack<TNode> m_operationStack;
};
#endif //EQUATIONRESOLVER_EQUATIONCREATOR_H
