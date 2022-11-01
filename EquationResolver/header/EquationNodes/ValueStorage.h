//
// Created by artem on 21.09.2022.
//

#ifndef EQUATIONRESOLVER_VALUESTORAGE_H
#define EQUATIONRESOLVER_VALUESTORAGE_H
#include "boost/variant.hpp"

class ValueStorage {
    using value_type = boost::variant< int, double >;

    template<typename TType>
    class Visitor : public boost::static_visitor<TType>
    {
    public:
        inline TType operator()(TType i) const noexcept
        {
            return i;
        }
        template<typename TTypeOther>
        inline TType operator()(TTypeOther i) const noexcept
        {
            return static_cast<TType>(i);
        }
    };
public:
    template<typename T>
    ValueStorage(T value) noexcept
        : m_value(std::move(value)){}

    template<typename T>
    inline void set(T newValue) noexcept{
        m_value = std::move(newValue);
    }

    template<typename T>
    inline T get() const noexcept{
       return boost::apply_visitor(Visitor<T>(), m_value);
    }

    inline const boost::typeindex::type_info& type() const noexcept{
        return m_value.type();
    }

    inline const bool isInt() const noexcept{
        return m_value.type() == typeid(int);
    }

    inline const bool isDouble() const noexcept{
        return m_value.type() == typeid(int);
    }

private:
    value_type m_value;
};



#endif //EQUATIONRESOLVER_VALUESTORAGE_H
