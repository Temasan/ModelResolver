//
// Created by artem on 28.08.2022.
//

#ifndef MODELRESOLVER_EQUATIONFABRIC_H
#define MODELRESOLVER_EQUATIONFABRIC_H

template<typename TNode>
class EquationFabric {

public:
    explicit EquationFabric(std::string const &equation){

    }

    static std::pair<TNode, std::vector<TNode>> make_equation(std::string const &equation){

    }

    void union_equation(TNode head_node1, TNode head_node2){

    }
private:
    TNode m_head;
    std::vector<TNode> m_branches;
};
#endif //MODELRESOLVER_EQUATIONFABRIC_H
