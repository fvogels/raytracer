#pragma once

#include "scripting/tokens.h"
#include "scripting/stream_line_reader.h"
#include "scripting/string_reader.h"
#include "scripting/combined_reader.h"
#include <istream>
#include <memory>

namespace scripting
{
	class Tokenizer : public Reader<std::shared_ptr<Token>, Location>
	{
	public:
		Tokenizer(std::istream&);

		void next() override;
		bool end_reached() const override;
		std::shared_ptr<Token> current() const override;
		Location location() const;

	private:
		CombinedReader<StreamLineReader, StringReader, Location> m_reader;
		std::shared_ptr<Token> m_current_token;

		void tokenize();
		void tokenize_lparen();
		void tokenize_rparen();
		void tokenize_string();

		void skip_whitespace();
		void skip_comments();
		void skip_whitespace_and_comments();
	};
}