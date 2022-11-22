//
// Created by artem on 28.08.2022.
//

#ifndef MODELRESOLVER_EQUATIONRULES_H
#define MODELRESOLVER_EQUATIONRULES_H
#include <algorithm>
namespace {
    class EquationResolver {
    public:
        enum class Rule {
            variable,
            constVal,
            sum,
            minus,
            multiple,
            divide,
            assign,
            bracket_open,
            bracket_close
        };

        constexpr explicit EquationResolver(Rule rule)
                : m_rule(rule) {}

        EquationResolver() = delete;

        virtual inline Rule getRule() const noexcept {
            return m_rule;
        }

        template<typename T, typename T1, typename T2>
        inline constexpr T2 calc(T value1, T1 value2, T2 defaultValue) noexcept {
            switch (m_rule) {
                case Rule::sum:
                    return value1 + value2;
                case Rule::minus:
                    return value1 - value2;
                case Rule::multiple:
                    return value1 * value2;
                case Rule::divide:
                    return value1 / value2;
                case Rule::assign:
                    return value2;
            }
            return defaultValue;
        }

        static std::string ruleToSign(EquationResolver::Rule rule) {
            auto smb = m_ruleToSign.find(rule);
            if (smb != m_ruleToSign.end()) return {smb->second};
            return "";
        }

        static EquationResolver::Rule signToRule(char sign) {
            if ((sign >= 48 && sign <= 57) || sign == 46) {
                return EquationResolver::Rule::constVal;
            } else {
                auto smb = m_signToRule.find(sign);
                if (smb != m_signToRule.end()) return {smb->second};
            }
            return EquationResolver::Rule::variable;
        }

        static bool lessPriored(EquationResolver::Rule const &rule1, EquationResolver::Rule const &rule2) {
            auto it1 = m_prior.find(rule1), it2 = m_prior.find(rule2);
            if(it1 != m_prior.end() && it2 != m_prior.end()){
                return it1->second > it2->second;
            }
            return false;
        }

    private:
        static const std::unordered_map<char, EquationResolver::Rule> m_signToRule;
        static const std::unordered_map<EquationResolver::Rule, char> m_ruleToSign;
        static const std::unordered_map<EquationResolver::Rule, int> m_prior;

        Rule m_rule;
    };

    const std::unordered_map<char, EquationResolver::Rule> EquationResolver::m_signToRule{
            std::make_pair('+', EquationResolver::Rule::sum),
            std::make_pair('-', EquationResolver::Rule::minus),
            std::make_pair('*', EquationResolver::Rule::multiple),
            std::make_pair('/', EquationResolver::Rule::divide),
            std::make_pair('(', EquationResolver::Rule::bracket_open),
            std::make_pair(')', EquationResolver::Rule::bracket_close),
    };

    const std::unordered_map<EquationResolver::Rule, char> EquationResolver::m_ruleToSign{
            std::make_pair(EquationResolver::Rule::sum, '+'),
            std::make_pair(EquationResolver::Rule::minus, '-'),
            std::make_pair(EquationResolver::Rule::multiple, '*'),
            std::make_pair(EquationResolver::Rule::divide, '/'),
            std::make_pair(EquationResolver::Rule::bracket_open, '('),
            std::make_pair(EquationResolver::Rule::bracket_close, ')'),
    };

    const std::unordered_map<EquationResolver::Rule, int> EquationResolver::m_prior{
            std::make_pair(EquationResolver::Rule::sum, 1),
            std::make_pair(EquationResolver::Rule::minus, 1),
            std::make_pair(EquationResolver::Rule::multiple, 0),
            std::make_pair(EquationResolver::Rule::divide, 0),
            std::make_pair(EquationResolver::Rule::bracket_open, 0),
            std::make_pair(EquationResolver::Rule::bracket_close, 0),
    };
}

#endif //MODELRESOLVER_EQUATIONRULES_H
