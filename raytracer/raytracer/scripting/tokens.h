#pragma once

#include <string>

namespace scripting
{
	class TokenVisitor;

	struct Location
	{
		unsigned line_index, char_index;

		Location(unsigned line_index, unsigned char_index)
			: line_index(line_index), char_index(char_index) { }
	};

	class Token
	{
	public:
		virtual void accept(TokenVisitor&) = 0;
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

		void accept(TokenVisitor&) override;
		void accept(TokenVisitor&) const override;
	};

	class RightParenthesisToken : public Token
	{
	public:
		RightParenthesisToken(const Location& location)
			: Token(location) { }

		void accept(TokenVisitor&) override;
		void accept(TokenVisitor&) const override;
	};

	class SymbolToken : public Token
	{
	public:
		SymbolToken(const Location& location, const std::string& symbol)
			: Token(location), symbol(symbol) { }

		void accept(TokenVisitor&) override;
		void accept(TokenVisitor&) const override;

		std::string symbol;
	};

	class StringToken : public Token
	{
	public:
		StringToken(const Location& location, const std::string& string)
			: Token(location), string(string) { }

		void accept(TokenVisitor&) override;
		void accept(TokenVisitor&) const override;

		std::string string;
	};

	class NumberToken : public Token
	{
	public:
		NumberToken(const Location& location, double value)
			: Token(location), value(value) { }

		void accept(TokenVisitor&) override;
		void accept(TokenVisitor&) const override;

		double value;
	};

	class TokenVisitor
	{
	public:
		virtual void visit(LeftParenthesisToken&) = 0;		
		virtual void visit(RightParenthesisToken&) = 0;
		virtual void visit(SymbolToken&) = 0;
		virtual void visit(StringToken&) = 0;
		virtual void visit(NumberToken&) = 0;

		virtual void visit(const LeftParenthesisToken&) = 0;
		virtual void visit(const RightParenthesisToken&) = 0;
		virtual void visit(const SymbolToken&) = 0;
		virtual void visit(const StringToken&) = 0;
		virtual void visit(const NumberToken&) = 0;
	};
}