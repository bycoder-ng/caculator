#include "calculate_unit.h"
#include "word_analyze.h"
#include <sstream>
#include <vector>


using namespace std;

int sign_number = 0;          //判定进入负数的状态数
int bracket_number = 0;       // 
bool left_number = false;  //判定左端是否为操作数
vector<char> calculate_operator_stack;
vector<string> calculate_number_stack;
bool is_integer(string number) {   //判断是否为整数
	if (number.find('.') != string::npos) {
		return false;
	}
	return true;
}

string the_calculate(string number_1, string number_2, char symbol) {   //计算出结果
	long long int integer_number1, integer_number2;
	double decimals_number1, decimals_number2, temp;
	bool integer_1 = false;
	bool integer_2 = false;
	string result;
	stringstream ss;
	cout << number_1 << "  " << number_2 << endl;
	if (is_integer(number_1)) {
		integer_number1 = stoi(number_1);
		integer_1 = true;
	}
	else {
		decimals_number1 = stof(number_1);
	}
	 
	if (is_integer(number_2)) {
		integer_number2 = stoi(number_2);
		integer_2 = true;
	}
	else {
		decimals_number2 = stof(number_2);
	}

	if (symbol == '+') {
		if (integer_1&&integer_2) {
			integer_number1 = integer_number1 + integer_number2;
			ss << integer_number1;
		}
		else if (!integer_1&&integer_2) {
			decimals_number1 = decimals_number1 + integer_number2;
			ss << decimals_number1;
		}
		else if (integer_1 && !integer_2) {
			temp = integer_number1 + decimals_number2;
			ss << temp;
		}
		else if (!integer_1 && !integer_2) {
			decimals_number1 = decimals_number1 + decimals_number2;
			cout << decimals_number1 << endl << decimals_number2 << endl;
			ss << decimals_number1;
		}
		result = ss.str();
	}
	else if (symbol == '-') {
		if (integer_1&&integer_2) {
			integer_number1 = integer_number1 - integer_number2;
			ss << integer_number1;
		}
		else if (!integer_1&&integer_2) {
			decimals_number1 = decimals_number1 - integer_number2;
			ss << decimals_number1;
		}
		else if (integer_1 && !integer_2) {
			temp = integer_number1 - decimals_number2;
			ss << temp;
		}
		else if (!integer_1 && !integer_2) {
			decimals_number1 = decimals_number1 - decimals_number2;
			ss << decimals_number1;
		}
		result = ss.str();
	}
	else if (symbol == '*') {
		if (integer_1&&integer_2) {
			integer_number1 = integer_number1 * integer_number2;
			ss << integer_number1;
		}
		else if (!integer_1&&integer_2) {
			decimals_number1 = decimals_number1 * integer_number2;
			ss << decimals_number1;
		}
		else if (integer_1 && !integer_2) {
			temp = integer_number1 * decimals_number2;
			ss << temp;
		}
		else if (!integer_1 && !integer_2) {
			decimals_number1 = decimals_number1 * decimals_number2;
			ss << decimals_number1;
		}
		result = ss.str();
	}
	else if (symbol == '/') {
		if (integer_1&&integer_2) {
			if (integer_number2 == 0) {
				cout << "除数不能为零" << endl;
				result = "";
			}
			else {
				integer_number1 = integer_number1 + integer_number2;
				ss << integer_number1;
				result = ss.str();
			}
		}
		else if (!integer_1&&integer_2) {
			if (integer_number2 == 0) {
				cout << "除数不能为零" << endl;
				result = "";
			}
			else {
				decimals_number1 = decimals_number1 + integer_number2;
				ss << decimals_number1;
				result = ss.str();
			}
		}
		else if (integer_1 && !integer_2) {
			if (fabs(decimals_number2 - 0) < eps) {
				cout << "除数不能为零" << endl;
				result = "";
			}
			else {
				temp = integer_number1 + decimals_number2;
				ss << temp;
				result = ss.str();
			}
		}
		else if (!integer_1 && !integer_2) {
			if (fabs(decimals_number2 - 0) < eps) {
				cout << "除数不能为零" << endl;
				result = "";
			}
			else {
				decimals_number1 = decimals_number1 + decimals_number2;
				ss << decimals_number1;
				result = ss.str();
			}
		}
	}
	return result;
}

string change_symbol(string number) {  //数值取反
	bool integer = false;
	long long int the_integer_number;
	double the_demicals_number;
	stringstream ss;
	if (is_integer(number)) {
		integer = true;
	}

	if (integer) {
		the_integer_number = stoi(number);
		the_integer_number = -the_integer_number;
		ss << the_integer_number;
	}
	else {
		the_demicals_number = stof(number);
		the_demicals_number = -the_demicals_number;
		ss << the_demicals_number;
	}
	number = ss.str();
	return number;
}

void add_number(string number) {
	left_number = true;
	calculate_number_stack.push_back(number);
	if (whther_pop_minus()) {
		pop_operator(true);
	}
}

bool add_operator(char symbol) {
	if (symbol == '+' || symbol == '-') {
		while (!calculate_operator_stack.empty()) {
			if (calculate_operator_stack[calculate_operator_stack.size() - 1] != '~' && calculate_operator_stack[calculate_operator_stack.size() - 1] != '(') {
				if (!pop_operator(true)) {
					return false;
				}
			}
			else {
				calculate_operator_stack.push_back(symbol);
				return true;
			}
		}
	}
	else {
		while (!calculate_operator_stack.empty()) {
			if (calculate_operator_stack[calculate_operator_stack.size() - 1] == '*'||calculate_operator_stack[calculate_operator_stack.size() - 1] == '/') {
				if (!pop_operator(true)) {
					return false;
				}
			}
			else {
				calculate_operator_stack.push_back(symbol);
				return true;
			}
		}
	}
	calculate_operator_stack.push_back(symbol);
	return true;
}

bool calculate(char symbol) {   //根据不同的操作符进行不同的操作
	string number_1;
	string number_2;
	string result;
	if (symbol == '~') {
		number_1 = calculate_number_stack[calculate_number_stack.size() - 1];
		calculate_number_stack.pop_back();
		result = change_symbol(number_1);
	}
	else if (symbol == '+') {
		number_2 = calculate_number_stack[calculate_number_stack.size() - 1];
		calculate_number_stack.pop_back();
		number_1 = calculate_number_stack[calculate_number_stack.size() - 1];
		calculate_number_stack.pop_back();
		result = the_calculate(number_1, number_2, '+');
	}
	else if (symbol == '-') {
		number_2 = calculate_number_stack[calculate_number_stack.size() - 1];
		calculate_number_stack.pop_back();
		number_1 = calculate_number_stack[calculate_number_stack.size() - 1];
		calculate_number_stack.pop_back();
		result = the_calculate(number_1, number_2, '-');
	}
	else if (symbol == '*') {
		number_2 = calculate_number_stack[calculate_number_stack.size() - 1];
		calculate_number_stack.pop_back();
		number_1 = calculate_number_stack[calculate_number_stack.size() - 1];
		calculate_number_stack.pop_back();
		result = the_calculate(number_1, number_2, '*');
	}
	else if (symbol == '/') {
		number_2 = calculate_number_stack[calculate_number_stack.size() - 1];
		calculate_number_stack.pop_back();
		number_1 = calculate_number_stack[calculate_number_stack.size() - 1];
		calculate_number_stack.pop_back();
		result = the_calculate(number_1, number_2, '/');
	}
	if (result != "") {
		add_number(result);
		return true;
	}
	else {
		return false;
	}
}


bool whther_pop_minus() {  //判断是否弹出符号
	if (!calculate_operator_stack.empty()) {
		if (left_number&&calculate_operator_stack[calculate_operator_stack.size() - 1] == '~'){
			return true;
		}
	}
	return false;
}

bool pop_operator(bool is_normal) {   //弹出操作符
	bool result=true;
	if (is_normal) {
		char temp_operator = calculate_operator_stack[calculate_operator_stack.size() - 1];
		calculate_operator_stack.pop_back();
		result = calculate(temp_operator);
		return result;
	}
	else {
		while (true) {
			char temp_operator = calculate_operator_stack[calculate_operator_stack.size() - 1];
			calculate_operator_stack.pop_back();
			if (temp_operator != '(') {
				result = calculate(temp_operator);
				if (result == false) {
					return result;
				}
			}
			else {
				return result;
			}
		}
	}
}

bool drive(){  //总驱动程序
	while (true){
		token temp=token_list[0];
		bool result;
		if (temp.is_operator) {
			if (left_number) {
				switch (temp.type) {
				case 3:
					add_operator('+');
					left_number = false;
					break;
				case 4:
					add_operator('-');
					left_number = false;
					break;
				case 5:
					add_operator('/');
					left_number = false;
					break;
				case 6:
					add_operator('*');
					left_number = false;
					break;
				case 7:
					cout << "错误的括号" << endl;
					return false;
				case 8:
					if (bracket_number > 0) {
						if (!pop_operator(false)) {
							cout << "除数不能为零" << endl;
							return false;
						}
						bracket_number--;
					}
					else {
						cout << "括号不匹配" << endl;
						return false;
					}
					break;
				case 9:
					if (bracket_number > 0) {
						cout << "括号不匹配" << endl;
						return false;
					}
					while (!calculate_operator_stack.empty()) {
						if (!pop_operator(true)) {
							cout << "除数不能为零" << endl;
							return false;
						}
					}
					return true;
				}
			}
			else {
				switch (temp.type) {
				case 3:
					cout << "操作符缺少操作符数" << endl;
					break;
				case 4:
					sign_number++;
					calculate_operator_stack.push_back('~');
					break;
				case 5:
					cout << "操作符缺少操作符数" << endl;
					break;
				case 6:
					cout << "操作符缺少操作符数" << endl;
					break;
				case 7:
					bracket_number++;
					calculate_operator_stack.push_back('(');
					break;
				case 8:
					cout << "不完整的表达式" << endl;
					return false;
				case 9:
					return false;
				}
			}
		}
		else {
			if (left_number) {
				cout << "确少操作符" << endl;
				return false;
			}
			else {
				add_number(temp.word);
			}
		}
		vector<token>::iterator iter = token_list.begin();
		token_list.erase(iter);
	}
	return true;
}
