//
// Created by artem on 28.08.2022.
//

#ifndef MODELRESOLVER_EQUATIONRULES_H
#define MODELRESOLVER_EQUATIONRULES_H
#include <algorithm>
class EquationRules {
public:
    enum class Rule{
        variable,
        sum,
        minus,
        multiple,
        divide
    };
    explicit EquationRules(Rule rule)
        : m_rule(rule){}

    EquationRules() = delete;

    template <typename T, typename T1, typename T2>
    inline constexpr T2 calc(T value1, T1 value2, T2 defaultValue) noexcept {
        switch(m_rule){
            case Rule::sum:
                return value1 + value2;
            case Rule::minus:
                return value1 - value2;
            case Rule::multiple:
                return value1 * value2;
            case Rule::divide:
                return value1 / value2;
        }
        return defaultValue;
    }
private:
    Rule m_rule;
};
#endif //MODELRESOLVER_EQUATIONRULES_H
