#include "word_analyze.h"
#include "calculate_unit.h"
#include "picture.h"

using namespace std;
string charstream;
string result_stream;
int main(){
	initgraph(400, 600, EW_SHOWCONSOLE);
	SetWindowText(GetHWnd(), _T("¼ÆËãÆ÷"));
	float H = 190;
	float S = 1;
	float L = 0.7f;
	for (int y = 0; y < 600; y++) {
		L += 0.0005f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, y, 399, y);
	}
	add_button();
	exhibition.init();
	exhibition.draw_inputstream();
	ExMessage m;
	while (true) {
		m = getmessage(EM_MOUSE);
		switch (m.message) {
		case(WM_MOUSEMOVE):
			break;
		case(WM_LBUTTONDOWN):
			deal_message(m);
			break;
		}
	}
	_getch();
	closegraph();
}