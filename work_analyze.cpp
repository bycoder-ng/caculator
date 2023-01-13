#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "word_analyze.h"
using namespace std;

/*
....type....
1:整数
2：小数
3：+
4：-
5：/
6:*
7:(
8:)
9:#
*/

vector<token> token_list;

bool is_digit(char ch){   //判断是否为数字
	if (ch >= '0'&&ch <= '9'){
		return true;
	}
	else {
		return false;
	}
}


void save_token(vector<token>& token_list, string word,int type,bool is_operator) {   //将新识别的token加入列表
	token newone;
	newone.type = type;
	newone.word = word;
	newone.is_operator = is_operator;
	token_list.push_back(newone);
}

bool read_token(string input_stream) {   //识别token
	int state = 0;
	string word = "";
	int i = 0;
	char ch;
	while (true) {
		ch = input_stream[i];
		switch (state){
			case 0:
     			if (is_digit(ch)) {
	     			state = 1;
		    		word += ch;
				}
				else if(ch=='+') {
					state = 0;
					word += '+';
					save_token(token_list,word,3,true);
					word = "";
				}
				else if(ch == '-') {
					state = 0;
					word += '-';
					save_token(token_list, word, 4,true);
					word = "";
				}
				else if (ch == '/') {
					state = 0;
					word += '/';
					save_token(token_list, word, 5,true);
					word = "";
				}
				else if (ch == '*') {
					state = 0;
					word += '*';
					save_token(token_list, word, 6,true);
					word = "";
				}
				else if (ch == '(') {
					state = 0;
					word += '(';
					save_token(token_list, word, 7,true);
					word = "";
				}
				else if (ch == ')') {
					state = 0;
					word += ')';
					save_token(token_list, word, 8,true);
					word = "";
				}
				else if (ch == '#') {
					word += '#';
					save_token(token_list, word, 9,true);
					return true;
				}
				else {
					return false;
				}
				break;
			case 1:
				if (is_digit(ch)) {
					word += ch;
				}
				else if (ch == '.') {
					word += '.';
					state = 2;
				}
				else {
					state = 0;
					save_token(token_list, word, 1,false);
					word ="";
					i--;
				}
				break;
			case 2:
				if (is_digit(ch)) {
					state = 3;
					word += ch;
				}
				else {
					state = 0;
					return false;
				}
				break;
			case 3:
				if (is_digit(ch)) {
					word += ch;
				}
				else {
					state = 0;
					save_token(token_list, word, 2,false);
					word = "";					
					i--;
				}
				break;
		}
		i++;
	}
	return true;
}





