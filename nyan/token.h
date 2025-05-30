// Copyright 2016-2021 the nyan authors, LGPLv3+. See copying.md for legal info.
#pragma once


#include <string>

#include "error.h"
#include "location.h"

namespace nyan {

class File;

/**
 * Available token types.
 */
enum class token_type {
	AS,
	AT,
	BANG,
	COLON,
	COMMA,
	DEDENT,
	DOT,
	ENDFILE,
	ENDLINE,
	ELLIPSIS,
	FLOAT,
	FROM,
	ID,
	IMPORT,
	INDENT,
	INF,
	INT,
	INVALID,
	LANGLE,
	LBRACE,
	LBRACKET,
	LPAREN,
	OPERATOR,
	PASS,
	RANGLE,
	RBRACE,
	RBRACKET,
	RPAREN,
	STRING,
};

/**
 * Known bracket types.
 */
enum class bracket_type {
	PAREN,
	ANGLE,
	BRACKET,
	BRACE,
};


/**
 * Get the string representation of a given token type.
 *
 * @param type Token type.
 *
 * @return String representation of the token type.
 */
constexpr const char *token_type_str(token_type type) {
	using namespace std::string_literals;

	switch (type) {
	case token_type::AS:
		return "as";
	case token_type::AT:
		return "@";
	case token_type::BANG:
		return "!";
	case token_type::COLON:
		return "colon";
	case token_type::COMMA:
		return "comma";
	case token_type::DEDENT:
		return "dedentation";
	case token_type::DOT:
		return "dot";
	case token_type::ELLIPSIS:
		return "ellipsis";
	case token_type::ENDFILE:
		return "end of file";
	case token_type::ENDLINE:
		return "end of line";
	case token_type::FLOAT:
		return "float";
	case token_type::FROM:
		return "from";
	case token_type::ID:
		return "identifier";
	case token_type::IMPORT:
		return "import";
	case token_type::INDENT:
		return "indentation";
	case token_type::INF:
		return "inf";
	case token_type::INT:
		return "int";
	case token_type::INVALID:
		return "invalid";
	case token_type::LANGLE:
		return "'<'";
	case token_type::LBRACE:
		return "'{'";
	case token_type::LBRACKET:
		return "'['";
	case token_type::LPAREN:
		return "'('";
	case token_type::OPERATOR:
		return "operator";
	case token_type::PASS:
		return "pass";
	case token_type::RANGLE:
		return "'>'";
	case token_type::RBRACE:
		return "'}'";
	case token_type::RBRACKET:
		return "']'";
	case token_type::RPAREN:
		return "')'";
	case token_type::STRING:
		return "string";
	}

	return "unhandled token_type";
}


/**
 * Check if the given token type requires a payload storage.
 * If not, then the token type is already enough information.
 *
 * @param type Token type.
 *
 * @return true if the token type requires a payload, else false.
 */
constexpr bool token_needs_payload(token_type type) {
	switch (type) {
	case token_type::FLOAT:
	case token_type::ID:
	case token_type::INF:
	case token_type::INT:
	case token_type::OPERATOR:
	case token_type::STRING:
		return true;
	default:
		return false;
	}
}


/**
 * Tokens are generated by the nyan lexer.
 */
class Token {
public:
	Token();
	Token(const std::shared_ptr<File> &file,
	      int line,
	      int line_offset,
	      int length,
	      token_type type);
	Token(const std::shared_ptr<File> &file,
	      int line,
	      int line_offset,
	      int length,
	      token_type type,
	      const std::string &value);
	~Token() = default;

	/**
	 * Check if the token has a payload.
	 *
	 * @return true if a payload exists, else false.
	 */
	bool exists() const;

	/**
	 * Check if the token is an endmarker (EOL or EOF).
	 *
	 * @return true if the token is an endmarker, else false.
	 */
	bool is_endmarker() const;

	/**
	 * Check if the token type is used for storing content.
	 * This can be member values or object references.
	 *
	 * @return true if the token type is used for content, else false.
	 */
	bool is_content() const;

	/**
	 * Get the token payload.
	 *
	 * @return String of the token payload.
	 */
	const std::string &get() const;

	/**
	 * Get the string representation of the token.
	 *
	 * @return String representation of the token.
	 */
	std::string str() const;

	/**
	 * Location of the token in a file.
	 */
	Location location;

	/**
	 * Token type.
	 */
	token_type type;

protected:
	/**
	 * Token payload.
	 */
	std::string value;
};

} // namespace nyan
