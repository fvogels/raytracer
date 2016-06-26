#pragma once

#include "scripting/location.h"
#include <string>
#include <memory>

namespace scripting
{
    class TokenVisitor;

    class Token
    {
    public:
        virtual void accept(TokenVisitor&) const = 0;

        Location location;

    protected:
        Token(Location location) : location(location) { }
    };

    class LeftParenthesisToken : public Token
    {
    public:
        LeftParenthesisToken(const Location& location)
            : Token(location) { }

        void accept(TokenVisitor&) const override;
    };

    class RightParenthesisToken : public Token
    {
    public:
        RightParenthesisToken(const Location& location)
            : Token(location) { }

        void accept(TokenVisitor&) const override;
    };

    class SymbolToken : public Token
    {
    public:
        SymbolToken(const Location& location, const std::string& name)
            : Token(location), name(name) { }

        void accept(TokenVisitor&) const override;

        std::string name;
    };

    class StringToken : public Token
    {
    public:
        StringToken(const Location& location, const std::string& string)
            : Token(location), string(string) { }

        void accept(TokenVisitor&) const override;

        std::string string;
    };

    class NumberToken : public Token
    {
    public:
        NumberToken(const Location& location, double value)
            : Token(location), value(value) { }

        void accept(TokenVisitor&) const override;

        double value;
    };

    class TokenVisitor
    {
    public:
        virtual void visit(const LeftParenthesisToken&) = 0;
        virtual void visit(const RightParenthesisToken&) = 0;
        virtual void visit(const SymbolToken&) = 0;
        virtual void visit(const StringToken&) = 0;
        virtual void visit(const NumberToken&) = 0;
    };

    template<typename T>
    bool has_token_type(const Token* p)
    {
        return dynamic_cast<const T*>(p) != nullptr;
    }

    template<typename T>
    bool has_token_type(std::shared_ptr<const Token> p)
    {
        return std::dynamic_pointer_cast<const T>(p) != nullptr;
    }
}