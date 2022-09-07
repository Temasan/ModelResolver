//
// Created by artem on 28.08.2022.
//

#ifndef MODELRESOLVER_TYPEDEQUATIONNODE_H
#define MODELRESOLVER_TYPEDEQUATIONNODE_H

#include <type_traits>
#include <vector>
#include <memory>
#include "../EquationMaking/EquationRules.h"
#include "EquationNode.h"

class TypedEquationNode {
    using ChildNodeType = std::shared_ptr<TypedEquationNode>;
    using ParentNodeType = std::weak_ptr<TypedEquationNode>;

public:
    template<typename T>
    TypedEquationNode(T initValue, EquationRules::Rule const &rule, ChildNodeType child1, ChildNodeType child2)
            : m_value(initValue)
            , m_children(std::make_pair(child1, child2))
            , m_resolver(rule) {
    }

    template<typename T>
    static ChildNodeType make_node(T initValue, EquationRules::Rule const &rule = EquationRules::Rule::constVal, ChildNodeType child1 = nullptr, ChildNodeType child2 = nullptr){
        ChildNodeType node = std::make_shared<TypedEquationNode>(initValue, rule, child1, child2);
        if(child1) child1->assignParent(node);
        if(child2) child2->assignParent(node);
        node->calc(false);
        return node;
    }

    TypedEquationNode() = delete;

    void assignParent(std::shared_ptr<TypedEquationNode> parent){
        m_parent = parent;
    }

    template<typename T = int>
    void setValue(T newValue, bool recalc = true){
        if(m_resolver.getRule() == EquationRules::Rule::constVal){
            throw std::exception();
        }
        m_value.set(newValue);
        if(recalc){
            auto parent{m_parent.lock()};
            if(parent){
                parent->calc(false);
            }
        }
    }

    template<typename Type>
    const double get() const{
        return m_value.get<Type>();
    }

private:
    void calc(bool downDirection){
        if(downDirection){
            if(m_children.first){
                m_children.first->calc(true);
            }
            if(m_children.second){
                m_children.second->calc(true);
            }
        }
        auto value1{ !m_children.first ? 0 : m_children.first->m_value.getType() == Value::valueType::intType ?
                    m_children.first->get<int>() :
                    m_children.first->get<double>() };

        auto value2{ !m_children.second ? 0 : m_children.second->m_value.getType() == Value::valueType::intType ?
                    m_children.second->get<int>() :
                    m_children.second->get<double>() };

        switch (m_value.getType()) {
            case Value::valueType::doubleType:
                m_value.set(m_resolver.calc(value1, value2, m_value.get<double>()));
                break;
            case Value::valueType::intType:
                m_value.set(m_resolver.calc(value1, value2, m_value.get<int>()));
                break;
        }
        if(!downDirection){
            auto parent{m_parent.lock()};
            if(parent){
                parent->calc(false);
            }
        }
    }
    struct Value {
        enum class valueType{
            doubleType,
            intType
        } m_valueType;
    public:
        Value(int value)
            : m_valueType(valueType::intType)
        {
            m_unionValue.m_intValue = value;
        }

        Value(double value)
                : m_valueType(valueType::doubleType)
        {
            m_unionValue.m_doubleValue = value;
        }

        template<typename Type>
        void set(Type newValue){
            switch(m_valueType){
                case valueType::doubleType:
                    m_unionValue.m_doubleValue = newValue;
                    break;
                case valueType::intType:
                    m_unionValue.m_intValue = newValue;
                    break;
            }
        }

        template<typename Type>
        Type get() const {
            switch(m_valueType){
                case valueType::doubleType:
                    return m_unionValue.m_doubleValue;
                case valueType::intType:
                    return m_unionValue.m_intValue;
            }
            return m_unionValue.m_doubleValue;
        }

        valueType getType() const {
            return  m_valueType;
        }
    private:
        // todo replace on boost::variant
        union {
            int m_intValue;
            double m_doubleValue;
        } m_unionValue;
    }  m_value;

    std::pair<ChildNodeType, ChildNodeType> m_children;
    ParentNodeType m_parent{};
    EquationRules m_resolver;
};

#endif //MODELRESOLVER_TYPEDEQUATIONNODE_H
