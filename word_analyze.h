#pragma once
#include <string>
#include <vector>

struct token {
	std::string word;
	int type;
	bool is_operator;
};

extern std::vector<token> token_list;

bool is_digit(char);

void save_token(std::vector<int>&, std::string, int, bool);

bool read_token(std::string);

