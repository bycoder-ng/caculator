#pragma once
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "word_analyze.h"
#include "calculate_unit.h"
extern std::string charstream;

void deal_expression();

void add_button();

extern char button_symbol[20];

extern std::string result_stream;

void deal_message(ExMessage);

class panel{
	private: 
	int	x=20, y=25, height=150, width=360;
	IMAGE img;
	public:

		void init() {
			getimage(&(this->img), this->x, this->y, this->width, this->height);
		}

		void draw_inputstream(){
			SetWorkingImage(&img);
			setbkcolor(WHITE);
			cleardevice();
			settextcolor(BLACK);
			RECT r = {0,0,width,height};
			char* a = new char[charstream.size() + 1];
			for (int i = 0; i < charstream.size(); i++) {
				a[i] = charstream[i];
			}
			a[charstream.size()] = '\0';
			drawtext(a,&r, DT_WORDBREAK | DT_LEFT | DT_EDITCONTROL);
			SetWorkingImage();
			putimage(x, y, &img);
			delete a;
		}

		void draw_result() {
			SetWorkingImage(&img);
			setbkcolor(WHITE);
			cleardevice();
			settextcolor(BLACK);
			RECT r = { 0,0,width,height };
			char* a = new char[result_stream.size() + 1];
			for(int i = 0; i < result_stream.size(); i++) {
				a[i] = result_stream[i];
			}
			a[result_stream.size()] = '\0';
			drawtext(a, &r, DT_WORDBREAK | DT_LEFT | DT_EDITCONTROL);
			SetWorkingImage();
			putimage(x, y, &img);
			delete a;
		}
};

extern panel exhibition;

class button {
private:
	int x, y, height, width;
	char symbol;
	IMAGE img;

public:
	void set_parameter(int x, int y, int width, int height, char symbol) {
		this->x = x;
		this->y = y;
		this->height = height;
		this->width = width;
		this->symbol = symbol;
		getimage(&(this->img), this->x, this->y, this->width, this->height);
	}

	void draw_img() {
		SetWorkingImage(&img);
		setfillcolor(BLACK);
		solidroundrect(20, 10, width - 20, height - 10, 20, 20);
		settextcolor(WHITE);
		RECT r = { 0,0,width,height };
		drawtext(symbol, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SetWorkingImage();
		putimage(x, y, &img);
	}

	void is_trigger(ExMessage message) {
		if (message.x > x&&message.x<x + width && message.y>y&&message.y < y + height) {
			if (message.message == WM_LBUTTONDOWN) {
				std::cout << "CLICKED£º" << symbol << std::endl;
				if (symbol == 'C') {
					charstream = "";
					exhibition.draw_inputstream();
				}
				else if (symbol == '~') {
					if(!charstream.empty()){
						charstream.pop_back();
						exhibition.draw_inputstream();
					}
				}
				else if(symbol == '='){
					charstream += "#";
					deal_expression();
					charstream = "";
					exhibition.draw_result();
				}
				else {
					charstream += symbol;
					exhibition.draw_inputstream();
				}
			}
		}
	}
};

extern button button_list[20];
