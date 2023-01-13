#include "calculate_unit.h"
#include "word_analyze.h"
#include <sstream>
#include <vector>


using namespace std;

int sign_number = 0;          //�ж����븺����״̬��
int bracket_number = 0;       // 
bool left_number = false;  //�ж�����Ƿ�Ϊ������
vector<char> calculate_operator_stack;
vector<string> calculate_number_stack;
bool is_integer(string number) {   //�ж��Ƿ�Ϊ����
	if (number.find('.') != string::npos) {
		return false;
	}
	return true;
}

string the_calculate(string number_1, string number_2, char symbol) {   //��������
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
				cout << "��������Ϊ��" << endl;
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
				cout << "��������Ϊ��" << endl;
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
				cout << "��������Ϊ��" << endl;
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
				cout << "��������Ϊ��" << endl;
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

string change_symbol(string number) {  //��ֵȡ��
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

bool calculate(char symbol) {   //���ݲ�ͬ�Ĳ��������в�ͬ�Ĳ���
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


bool whther_pop_minus() {  //�ж��Ƿ񵯳�����
	if (!calculate_operator_stack.empty()) {
		if (left_number&&calculate_operator_stack[calculate_operator_stack.size() - 1] == '~'){
			return true;
		}
	}
	return false;
}

bool pop_operator(bool is_normal) {   //����������
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

bool drive(){  //����������
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
					cout << "���������" << endl;
					return false;
				case 8:
					if (bracket_number > 0) {
						if (!pop_operator(false)) {
							cout << "��������Ϊ��" << endl;
							return false;
						}
						bracket_number--;
					}
					else {
						cout << "���Ų�ƥ��" << endl;
						return false;
					}
					break;
				case 9:
					if (bracket_number > 0) {
						cout << "���Ų�ƥ��" << endl;
						return false;
					}
					while (!calculate_operator_stack.empty()) {
						if (!pop_operator(true)) {
							cout << "��������Ϊ��" << endl;
							return false;
						}
					}
					return true;
				}
			}
			else {
				switch (temp.type) {
				case 3:
					cout << "������ȱ�ٲ�������" << endl;
					break;
				case 4:
					sign_number++;
					calculate_operator_stack.push_back('~');
					break;
				case 5:
					cout << "������ȱ�ٲ�������" << endl;
					break;
				case 6:
					cout << "������ȱ�ٲ�������" << endl;
					break;
				case 7:
					bracket_number++;
					calculate_operator_stack.push_back('(');
					break;
				case 8:
					cout << "�������ı��ʽ" << endl;
					return false;
				case 9:
					return false;
				}
			}
		}
		else {
			if (left_number) {
				cout << "ȷ�ٲ�����" << endl;
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
