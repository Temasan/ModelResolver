//
// Created by artem on 28.08.2022.
//

#ifndef MODELRESOLVER_TYPEDEQUATIONNODE_H
#define MODELRESOLVER_TYPEDEQUATIONNODE_H

#include <type_traits>
#include <vector>
#include <memory>
#include "../EquationMaking/EquationRules.h"
#include "ValueStorage.h"

class TypedEquationNode {
class const_change_exception : public std::exception{
    virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override{
        return "Denied to change const variable";
    }
};

public:
    using ChildNodeType = std::shared_ptr<TypedEquationNode>;
    using ParentNodeType = std::weak_ptr<TypedEquationNode>;

    template<typename T>
    TypedEquationNode(T initValue, std::string const & signature, EquationResolver::Rule const &rule, ChildNodeType child1 = nullptr, ChildNodeType child2 = nullptr)
            : m_value(initValue)
            , m_children(std::make_pair(child1, child2))
            , m_resolver(rule)
            , m_signature(signature){
        calc(false);
    }

    template<typename T>
    static ChildNodeType make_node(T initValue,
                                   EquationResolver::Rule const &rule = EquationResolver::Rule::constVal,
                                   ChildNodeType child1 = nullptr, ChildNodeType child2 = nullptr){
        ChildNodeType node = std::make_shared<TypedEquationNode>(initValue, EquationResolver::ruleToSign(rule), rule, child1, child2);
        if(child1) child1->assignParent(node);
        if(child2) child2->assignParent(node);
        return node;
    }

    static ChildNodeType make_variable(std::string initValue){
        return std::make_shared<TypedEquationNode>(0., initValue, EquationResolver::Rule::variable);
    }

    TypedEquationNode() = delete;

    void assignParent(std::shared_ptr<TypedEquationNode> parent){
        m_parent = parent;
    }

    void assignChildLeft(std::shared_ptr<TypedEquationNode> child){
        m_children.first = child;
    }

    ChildNodeType getLeftChild(){
        return m_children.first;
    }

    void assignChildRight(std::shared_ptr<TypedEquationNode> child){
        m_children.second = child;
    }

    ChildNodeType getRightChild(){
        return m_children.second;
    }

    template<typename T = int>
    void setValue(T newValue, bool recalc = true){
        if(m_resolver.getRule() == EquationResolver::Rule::constVal){
            throw const_change_exception();
        }
        m_value.set(newValue);
        if(recalc){
            auto parent{m_parent.lock()};
            if(parent){
                parent->calc(false);
            }
        }
    }

    template<typename T>
    const T get() const{
        return m_value.get<T>();
    }

    std::string const & signature() const{
        return m_signature;
    }

    bool lessPriored(EquationResolver::Rule const & rule) const {
        return m_resolver.lessPriored(m_resolver.getRule(), rule);
    }

    void calc(bool downDirection) noexcept{
        if(downDirection){
            if(m_children.first){
                m_children.first->calc(true);
            }
            if(m_children.second){
                m_children.second->calc(true);
            }
        }
        auto value1{ !m_children.first ? 0 : m_children.first->m_value.isInt() ?
                    m_children.first->get<int>() :
                    m_children.first->get<double>() };

        auto value2{ !m_children.second ? 0 : m_children.second->m_value.isInt() ?
                    m_children.second->get<int>() :
                    m_children.second->get<double>() };
        // todo
        if (m_value.type() == typeid(double)) {
            m_value.set(calc<double>(value1, value2));
        }
        else {
            m_value.set(calc<int>(value1, value2));
        }
        if(!downDirection){
            auto parent{m_parent.lock()};
            if(parent){
                parent->calc(false);
            }
        }
    }

private:
    template<typename T, typename T1, typename T2>
    inline T calc(T1 value1, T2 value2) noexcept{
        return m_resolver.calc(value1, value2, m_value.get<T>());
    }

    ValueStorage m_value;
    std::pair<ChildNodeType, ChildNodeType> m_children;
    ParentNodeType m_parent{};
    EquationResolver m_resolver;
    std::string m_signature;
};

#endif //MODELRESOLVER_TYPEDEQUATIONNODE_H
