#pragma once

#include <memory>
#include <vector>
#include <string>
#include <ostream>
#include <functional>
#include <sstream>
#include <typeinfo>

namespace scripting
{
    class Environment;
    class Heap;

    class Object
    {
    public:
        virtual void write(std::ostream&) const = 0;
        virtual bool operator ==(const Object&) const = 0;

        virtual std::shared_ptr<Object> evaluate(std::shared_ptr<scripting::Environment>) = 0;

    protected:
        Object();
    };

    bool operator !=(const Object& a, const Object& b);
    std::ostream& operator <<(std::ostream&, const Object&);

    template<typename T>
    bool has_object_type(const Object& object)
    {
        return dynamic_cast<const T*>(&object) != nullptr;
    }

    template<typename T>
    bool has_object_type(std::shared_ptr<const Object> object)
    {
        return std::dynamic_pointer_cast<const T>(object) != nullptr;
    }

    template<typename T, typename R>
    R with_object_type(Object& object, std::function<R(T&)> function)
    {
        auto converted = dynamic_cast<T&>(object);

        if (converted != nullptr)
        {
            return function(converted);
        }
        else
        {
            throw std::runtime_error("type error");
        }
    }

    template<typename T, typename R>
    R with_object_type(const Object& object, std::function<R(const T&)> function)
    {
        const T* converted = dynamic_cast<const T*>(&object);

        if (converted != nullptr)
        {
            return function(*converted);
        }
        else
        {
            throw std::runtime_error("type error");
        }
    }

    template<typename T, typename R>
    R with_object_type(std::shared_ptr<Object> object, std::function<R(std::shared_ptr<T>)> function)
    {
        auto converted = std::dynamic_pointer_cast<T>(object);

        if (converted != nullptr)
        {
            return function(converted);
        }
        else
        {
            throw std::runtime_error("type error");
        }
    }

    template<typename T>
    T& object_cast(Object& object)
    {
        T* converted = dynamic_cast<T*>(&object);

        if (converted == nullptr)
        {
            std::ostringstream ss;
            ss << "Type error: expected type " << typeid(T).name() << ", actual type " << typeid(*object).name();

            throw std::runtime_error(ss.str());
        }
        else
        {
            return *converted;
        }
    }

    template<typename T>
    const T& object_cast(const Object& object)
    {
        const T* converted = dynamic_cast<const T*>(&object);

        if (converted == nullptr)
        {
            std::ostringstream ss;
            ss << "Type error: expected type " << typeid(T).name() << ", actual type " << typeid(object).name();

            throw std::runtime_error(ss.str());
        }
        else
        {
            return *converted;
        }
    }

    template<typename T>
    std::shared_ptr<T> object_cast(std::shared_ptr<Object> object)
    {
        std::shared_ptr<T> converted = std::dynamic_pointer_cast<T>(object);

        if (converted == nullptr)
        {
            std::ostringstream ss;
            ss << "Type error: expected type " << typeid(T).name() << ", actual type " << typeid(*object).name();
            auto message = ss.str();

            throw std::runtime_error(message);
        }
        else
        {
            return converted;
        }
    }
}