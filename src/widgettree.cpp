#include <algorithm>
#include <iostream>

#include "widgettree.h"


enum TokenType {
	STRING_TOKEN,
	IDENT_TOKEN,
	BOOL_TOKEN,
	NUMBER_TOKEN,
	OPERATOR_TOKEN
};

struct Token {
	std::string text;
	TokenType type;
	
	Token(std::string text, TokenType type): text(text), type(type) {}
	
	friend std::ostream& operator<<(std::ostream& o, const Token& t) {
		o << t.text;
		return o;
	}
};


enum TokenizerState {
	NONE,
	STRING,
	STRINGESCAPE,
	NUMBER,
	IDENT
};


bool isoperator(char c) {
	switch (c) {
		case '=': /* FALLTHROUGH */
		case ':':
			return true;
		default:
			return false;
	}
}


static std::vector<Token> tokenize(const std::string& text) {
	std::vector<Token> tokens;
	int len = (int) text.size();
	TokenizerState state = NONE;
	
	if (len == 0) {
		return tokens;
	}
	
	std::string token = "";
	
	for (int i = 0; i < len; ++i) {
		int c = text[i];
		
		if (c == '\"') {
			switch (state) {
				case NONE:
					state = STRING;
					break;
				case STRING:
					state = NONE;
					tokens.push_back(Token(token, STRING_TOKEN));
					token = "";
					break;
				case STRINGESCAPE:
					state = STRING;
					token += '"';
					break;
				case NUMBER:
					throw std::runtime_error("illegal symbol '\"' in numerical constant");
					break;
				case IDENT:
					throw std::runtime_error("illegal symbol '\"' in identifier");
					break;
			}
		}
		else if (isoperator(c)) {
			switch (state) {
				case NONE:
					token = c;
					tokens.push_back(Token(token, OPERATOR_TOKEN));
					token = "";
					break;
				case STRING:
					token += c;
					break;
				case STRINGESCAPE:
					throw std::runtime_error("unknown escape sequence");
					break;
				case NUMBER:
					tokens.push_back(Token(token, NUMBER_TOKEN));
					token = c;
					tokens.push_back(Token(token, OPERATOR_TOKEN));
					token = "";
					state = NONE;
					break;
				case IDENT:
					tokens.push_back(Token(token, IDENT_TOKEN));
					token = c;
					tokens.push_back(Token(token, OPERATOR_TOKEN));
					token = "";
					state = NONE;
					break;
			}
		}
		else if (c == '.') {
			switch (state) {
				case NONE:
					token = "0.";
					state = NUMBER;
					break;
				case STRING:
					token += c;
					break;
				case STRINGESCAPE:
					throw std::runtime_error("illegal escape sequence '\\.'");
					break;
				case NUMBER:
					if (std::find(token.begin(), token.end(), '.') == token.end()) {
						token += '.';
					}
					else {
						throw std::runtime_error("second floating point in numerical token");
					}
					break;
				case IDENT:
					throw std::runtime_error("illegal symbol '.' in identifier");
					break;
			}
		}
		else if (isspace(c)) {
			switch (state) {
				case NONE:
					/* nothing happens here */
					break;
				case STRING:
					token += c;
					break;
				case STRINGESCAPE:
					throw std::runtime_error("illegal escape sequence");
					break;
				case NUMBER:
					tokens.push_back(Token(token, NUMBER_TOKEN));
					token = "";
					state = NONE;
					break;
				case IDENT:
					tokens.push_back(Token(token, IDENT_TOKEN));
					token = "";
					state = NONE;
					break;
			}
		}
		else if (isalpha(c)) {
			switch (state) {
				case NONE:
					state = IDENT;
					token += c;
					break;
				case STRING:
					token += c;
					break;
				case STRINGESCAPE:
					switch (c) {
						case 't':
							token += '\t';
							break;
						default:
							throw std::runtime_error("unknown escape sequence");
							break;
					}
					state = STRING;
					break;
				case NUMBER:
					throw std::runtime_error("illegal character in numerical constant");
					break;
				case IDENT:
					token += c;
					break;
			}
		}
		else if (isdigit(c)) {
			switch (state) {
				case NONE:
					state = NUMBER;
					token += c;
					break;
				case STRING:
					token += c;
					break;
				case STRINGESCAPE:
					throw std::runtime_error("unknown escape sequence");
				case NUMBER:
					token += c;
					break;
				case IDENT:
					token += c;
					break;
			}
		}
		else {
			throw std::runtime_error("illegal character");
		}
	}
	
	switch (state) {
		case NONE:
			break;
		case STRING:
			throw std::runtime_error("unfinished string literal");
			break;
		case STRINGESCAPE:
			throw std::runtime_error("unfinished string literal with escape sequence");
			break;
		case NUMBER:
			tokens.push_back(Token(token, NUMBER_TOKEN));
			break;
		case IDENT:
			tokens.push_back(Token(token, IDENT_TOKEN));
			break;
	}
	
	return tokens;
}


std::shared_ptr<Container> read_widgettree(const std::string& text) {
	std::shared_ptr<Container> root;
	
	auto tokens = tokenize(text);
	std::cout << "tokens:" << std::endl;
	for (auto& token: tokens) {
		std::cout << token << std::endl;
	}
	
	return root;
}
