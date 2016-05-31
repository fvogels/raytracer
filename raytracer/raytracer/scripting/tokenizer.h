#pragma once

#include "scripting/tokens.h"
#include "scripting/stream_line_reader.h"
#include "scripting/string_reader.h"
#include "scripting/combined_reader.h"
#include <istream>
#include <memory>
#include <vector>

namespace scripting
{
	class TokenRecognizer
	{
	public:
		virtual bool is_valid_start(char c) const = 0;
		virtual std::shared_ptr<Token> tokenize(Reader<char, Location>& reader) const = 0;
	};

	class LeftParenthesisRecognizer : public TokenRecognizer
	{
	public:
		bool is_valid_start(char c) const override;
		std::shared_ptr<Token> tokenize(Reader<char, Location>& reader) const override;
	};

	class RightParenthesisRecognizer : public TokenRecognizer
	{
	public:
		bool is_valid_start(char c) const override;
		std::shared_ptr<Token> tokenize(Reader<char, Location>& reader) const override;
	};

	class StringRecognizer : public TokenRecognizer
	{
	public:
		bool is_valid_start(char c) const override;
		std::shared_ptr<Token> tokenize(Reader<char, Location>& reader) const override;
	};

	class NumberRecognizer : public TokenRecognizer
	{
	public:
		bool is_valid_start(char c) const override;
		std::shared_ptr<Token> tokenize(Reader<char, Location>& reader) const override;
	};

	class SymbolRecognizer : public TokenRecognizer
	{
	public:
		bool is_valid_start(char c) const override;
		std::shared_ptr<Token> tokenize(Reader<char, Location>& reader) const override;

	private:
		bool is_symbol_char(char) const;
	};

	class Tokenizer : public Reader<std::shared_ptr<const Token>, Location>
	{
	public:
		Tokenizer(std::istream&, std::vector<std::shared_ptr<const TokenRecognizer>>& recognizers);

		void next() override;
		bool end_reached() const override;
		std::shared_ptr<const Token> current() const override;
		Location location() const;

	private:
		CombinedReader<StreamLineReader, StringReader, LocationFactory> m_reader;
		std::vector<std::shared_ptr<const TokenRecognizer>> m_recognizers;
		std::shared_ptr<const Token> m_current_token;

		void tokenize();

		void skip_whitespace();
		void skip_comments();
		void skip_whitespace_and_comments();
	};
}