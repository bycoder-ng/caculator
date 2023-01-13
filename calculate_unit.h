#pragma once
#include <iostream>
#include <string>
#include <vector>
#define eps 1e-10
extern int sign_number;
extern int bracket_number;
extern bool left_number;
extern std::vector<std::string> calculate_number_stack;
extern std::vector<char> calculate_operator_stack;

bool is_integer(std::string);

std::string the_calculate(std::string, std::string number, char);

std::string  change_symbol(std::string);

void add_number(std::string);

bool add_operator(char);

bool calculate(char);

bool whther_pop_minus();

bool pop_operator(bool);

bool drive();


