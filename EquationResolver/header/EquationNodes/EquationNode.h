//
// Created by artem on 28.08.2022.
//

#ifndef MODELRESOLVER_EQUATIONNODE_H
#define MODELRESOLVER_EQUATIONNODE_H
template <typename T>
class EquationNode {
    T m_value;
public:
    explicit EquationNode(T initValue) noexcept :
        m_value(initValue){
    }

    void set(T newValue){
        m_value = newValue;
    }

    T const get() const{
        return m_value;
    }
};
#endif //MODELRESOLVER_EQUATIONNODE_H
