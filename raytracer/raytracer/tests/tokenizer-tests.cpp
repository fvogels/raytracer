#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/tokenizing/tokenizer.h"
#include "math/util.h"
#include <sstream>

using namespace scripting;

bool is_lparen(std::shared_ptr<const Token> token)
{
    return has_token_type<LeftParenthesisToken>(token);
}

bool is_rparen(std::shared_ptr<const Token> token)
{
    return has_token_type<RightParenthesisToken>(token);
}

bool is_string(std::shared_ptr<const Token> token, std::string string)
{
    if (has_token_type<StringToken>(token))
    {
        auto string_token = std::dynamic_pointer_cast<const StringToken>(token);

        return string_token->string == string;
    }
    else
    {
        return false;
    }
}

bool is_number(std::shared_ptr<const Token> token, double value)
{
    if (has_token_type<NumberToken>(token))
    {
        auto number_token = std::dynamic_pointer_cast<const NumberToken>(token);

        return number_token->value == math::approx<double>(value);
    }
    else
    {
        return false;
    }
}

bool is_symbol(std::shared_ptr<const Token> token, std::string string)
{
    if (has_token_type<SymbolToken>(token))
    {
        auto symbol_token = std::dynamic_pointer_cast<const SymbolToken>(token);

        return symbol_token->name == string;
    }
    else
    {
        return false;
    }
}

TEST_CASE("[Tokenizer] Empty stream", "[Tokenizer]")
{
    std::stringstream ss("");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing (", "[Tokenizer]")
{
    std::stringstream ss("(");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_lparen(tokenizer->current()));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing )", "[Tokenizer]")
{
    std::stringstream ss(")");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_rparen(tokenizer->current()));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing ()", "[Tokenizer]")
{
    std::stringstream ss("()");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_lparen(tokenizer->current()));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_rparen(tokenizer->current()));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\"", "[Tokenizer]")
{
    std::stringstream ss("\"abc\"");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "abc"));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\" \"xyz\"", "[Tokenizer]")
{
    std::stringstream ss("\"abc\" \"xyz\"");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "abc"));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "xyz"));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\"     \"xyz\"", "[Tokenizer]")
{
    std::stringstream ss("\"abc\"     \"xyz\"");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "abc"));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "xyz"));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\"\\n\"xyz\"", "[Tokenizer]")
{
    std::stringstream ss("\"abc\"\n\"xyz\"");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "abc"));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "xyz"));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\" ; Hello\\n\"xyz\"", "[Tokenizer]")
{
    std::stringstream ss("\"abc\" ; Hello\n\"xyz\"");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "abc"));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "xyz"));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing \"abc\" ; Hello\\n     \"xyz\"", "[Tokenizer]")
{
    std::stringstream ss("\"abc\" ; Hello\n     \"xyz\"");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "abc"));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_string(tokenizer->current(), "xyz"));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing 1", "[Tokenizer]")
{
    std::stringstream ss("1");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_number(tokenizer->current(), 1));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing 12", "[Tokenizer]")
{
    std::stringstream ss("12");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_number(tokenizer->current(), 12));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing 1 2", "[Tokenizer]")
{
    std::stringstream ss("1 2");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_number(tokenizer->current(), 1));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_number(tokenizer->current(), 2));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing abc", "[Tokenizer]")
{
    std::stringstream ss("abc");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_symbol(tokenizer->current(), "abc"));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing +", "[Tokenizer]")
{
    std::stringstream ss("+");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_symbol(tokenizer->current(), "+"));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

TEST_CASE("[Tokenizer] Tokenizing (+ 5 3)", "[Tokenizer]")
{
    std::stringstream ss("(+ 5 3)");
    std::shared_ptr<Tokenizer> tokenizer = create_tokenizer(ss);

    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_lparen(tokenizer->current()));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_symbol(tokenizer->current(), "+"));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_number(tokenizer->current(), 5));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_number(tokenizer->current(), 3));
    tokenizer->next();
    REQUIRE(!tokenizer->end_reached());
    REQUIRE(is_rparen(tokenizer->current()));
    tokenizer->next();
    REQUIRE(tokenizer->end_reached());
}

#endif
