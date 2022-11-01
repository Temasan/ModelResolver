//
// Created by artem on 01.11.2022.
//

#ifndef EQUATIONRESOLVER_NAMEDEQUATIONNODE_H
#define EQUATIONRESOLVER_NAMEDEQUATIONNODE_H

#include "TypedEquationNode.h"

class NamedEquationNode : public TypedEquationNode{
public:
    using NamedNodeType = std::shared_ptr<NamedEquationNode>;
    template<typename T>
    NamedEquationNode(std::string const &name, T initValue, ChildNodeType child1, ChildNodeType child2)
        : TypedEquationNode(initValue, EquationResolver::Rule::variable, child1, child2)
        , m_nodeName(name)
    {
        calc(false);
    }

    template<typename T>
    static NamedNodeType make_const_node(T initValue, ChildNodeType child1 = nullptr, ChildNodeType child2 = nullptr){
        auto node {TypedEquationNode::make_node(initValue, EquationResolver::Rule::constVal, child1, child2)};
        if(child1) child1->assignParent(node);
        if(child2) child2->assignParent(node);
    }

    template<typename T>
    static NamedNodeType make_variable_node(std::string const &name, T initValue, ChildNodeType child1 = nullptr, ChildNodeType child2 = nullptr){
        auto node {std::make_shared<NamedEquationNode>(name, initValue, child1, child2)};
        if(child1) child1->assignParent(node);
        if(child2) child2->assignParent(node);
    }

    std::string const & name() const noexcept{
        return m_nodeName;
    }
private:
    std::string m_nodeName;
};
#endif //EQUATIONRESOLVER_NAMEDEQUATIONNODE_H
