#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "picture.h"
#include "calculate_unit.h"
#include <vector>
#include "word_analyze.h"
using namespace std;
char button_symbol[20] = { 'C','/','*','~','7','8','9','-','4','5','6','+','1','2','3','.','(','0',')','=' };

button button_list[20];

panel exhibition;

void deal_expression() {
	cout << charstream << endl;
	if (read_token(charstream)) {
		for (int i = 0; i < token_list.size(); i++) {
			cout << token_list[i].word << " ";
		}
		cout << endl;
		if (drive()) {
			result_stream = calculate_number_stack[0];
		}
		else {
			result_stream = "null";
		}
	}
	else {
		result_stream = "null";
	}
	calculate_number_stack.resize(0);
	calculate_operator_stack.resize(0);
	token_list.resize(0);
	left_number = false;
	sign_number = 0;
	bracket_number = 0;
	cout << result_stream << endl;
}

void add_button(){
	for(int i = 0; i < 20; i++){
		button_list[i].set_parameter(0 + (i % 4) * 100, 200 + (i / 4) * 80, 100, 80,button_symbol[i]);
		button_list[i].draw_img();
	}
}

void deal_message(ExMessage m){
	for (int i = 0; i < 20; i++) {
		button_list[i].is_trigger(m);
	}
}


