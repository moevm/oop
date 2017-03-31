#include <iostream>
#include <windows.h>                     
#include <windowsx.h> 
#include <conio.h>
#include <string>
#include <wchar.h>
#include "circle.h"
#include "ellipse.h"
#include "arc.h"

using namespace std;

HINSTANCE hInstance; 
HINSTANCE hPrevInst; 
LPSTR lpszArgs; 
int nWinMode;

LRESULT CALLBACK WindowFunc(HWND, UINT, WPARAM, LPARAM); 

class my_window
{
public: 
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode) 
	{
		TCHAR szWinName[] = L"OOP_WINDOW";      
		TCHAR szTitle[] = L"OOP_LAB2";               
		MSG msg;                   
		WNDCLASS wc;                                  
		
		ZeroMemory(&wc, sizeof(wc));                             
		wc.hInstance = hInstance;                            
		wc.lpszClassName = szWinName;                         
		wc.lpfnWndProc = WindowFunc;                           
		wc.style = 0;                                                    
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);          
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);            
		wc.hbrBackground = GetStockBrush(WHITE_BRUSH);         
		wc.lpszMenuName = NULL;                                  
		wc.cbClsExtra = 0;                                                 
		wc.cbWndExtra = 0;                                               
		
		if(!RegisterClass(&wc))                                         
		{                                    
			MessageBox(NULL, L"Невозможно зарегистрировать окно!", L"Ошибка!", MB_OK | MB_ICONERROR);
			return 1;
		}  

		HWND hwnd = CreateWindow(szWinName, szTitle, WS_OVERLAPPEDWINDOW,             
								 500, 200, 500, 500,                                                         
			                     HWND_DESKTOP, NULL, hInstance, NULL);                                                     
		ShowWindow(hwnd, SW_SHOWMAXIMIZED);       
		
		while(GetMessage(&msg, NULL, 0, 0)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg); 
		}

		return 0;                                                    
	}                                                                   
};

void clear_paint_area(HDC & hdc, HWND & hWndMain)
{
	LPRECT rect = NULL;
	GetWindowRect(hWndMain, rect);

	SetBkColor(hdc, RGB(255, 255, 255));
	ExtTextOut(hdc, 0, 0, ETO_OPAQUE, rect, NULL, 0, NULL);
}
 
LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)  
{
	PAINTSTRUCT ps;
    HDC hdc;

	static circle fig1 = circle(50, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
	static ellipse fig2 = ellipse(300, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));
	static arc fig3 = arc(40, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));

	static int fig1_angle = 0;
	static int fig2_angle = 0;
	static int fig3_angle = 0;

	static int fig1_x = 0;
	static int fig2_x = 0;
	static int fig3_x = 0;

	static int fig1_y = 0;
	static int fig2_y = 0;
	static int fig3_y = 0;

	static float fig1_ratio = 0;
	static float fig2_ratio = 0;
	static float fig3_ratio = 0;

	static int small_axle = 200;
	static int big_axle = 100;

	static int angle1 = 0;
	static int angle2 = 270;

	switch(message) 
	{          
		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);

			fig1 = circle(50, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
			fig2 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));
			fig3 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));

			Rectangle(hdc, 0, 500, 500, 0);
			Rectangle(hdc, 500, 500, 1000, 0);
			Rectangle(hdc, 1000, 500, 1500, 0);

			fig1.scale(0);
			fig1.draw(0, 0);
			fig2.draw(0, 0);
			fig3.draw(0, 0);

			HFONT font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			SelectObject(hdc, font);
			TCHAR s1[] = L"Увеличить угол поворота окружности - клавиша Q";
			TCHAR s2[] = L"Уменьшить угол поворота окружности - клавиша W";
			TCHAR s3[] = L"Увеличить радиус окружности - клавиша E";
			TCHAR s4[] = L"Уменшить радиус окружности - клавиша R";
			TCHAR s5[] = L"Сдвинуть окружность в лево - клавиша 3";
			TCHAR s6[] = L"Сдвинуть окружность в право - клавиша 4";
			TCHAR s7[] = L"Сдвинуть окружность в верх - клавиша 1";
			TCHAR s8[] = L"Сдвинуть окружность в низ - клавиша 2";

            TextOut(hdc, 10, 520, s1, ARRAYSIZE(s1));
			TextOut(hdc, 10, 540, s2, ARRAYSIZE(s2));
			TextOut(hdc, 10, 560, s3, ARRAYSIZE(s3));
			TextOut(hdc, 10, 580, s4, ARRAYSIZE(s4));
			TextOut(hdc, 10, 600, s5, ARRAYSIZE(s5));
			TextOut(hdc, 10, 620, s6, ARRAYSIZE(s6));
			TextOut(hdc, 10, 640, s7, ARRAYSIZE(s7));
			TextOut(hdc, 10, 660, s8, ARRAYSIZE(s8));

			TCHAR s9[] = L"Увеличить угол поворота эллипса - клавиша A";
			TCHAR s10[] = L"Уменьшить угол поворота эллипса - клавиша S";
			TCHAR s11[] = L"Увеличить эллипс - клавиша D";
			TCHAR s12[] = L"Уменьшить эллипс - клавиша F";
			TCHAR s13[] = L"Увеличить длинну большой полуоси - клавиша G";
			TCHAR s14[] = L"Уменьшить длинну большой полуоси - клавиша H";
			TCHAR s15[] = L"Увеличить длинну малой полуоси - клавиша J";
			TCHAR s16[] = L"Уменьшить длинну малой полуоси - клавиша K";
			TCHAR s17[] = L"Сдвинуть эллипс в право - клавиша 7";
			TCHAR s18[] = L"Сдвинуть эллипс в лево - клавиша 8";
			TCHAR s19[] = L"Сдвинуть эллипс в верх - клавиша 5";
			TCHAR s20[] = L"Сдвинуть эллипс в низ - клавиша 6";
			
            TextOut(hdc, 510, 520, s9, ARRAYSIZE(s9));
			TextOut(hdc, 510, 540, s10, ARRAYSIZE(s10));
			TextOut(hdc, 510, 560, s11, ARRAYSIZE(s11));
			TextOut(hdc, 510, 580, s12, ARRAYSIZE(s12));
			TextOut(hdc, 510, 600, s13, ARRAYSIZE(s13));
			TextOut(hdc, 510, 620, s14, ARRAYSIZE(s14));
			TextOut(hdc, 510, 640, s15, ARRAYSIZE(s15));
			TextOut(hdc, 510, 660, s16, ARRAYSIZE(s16));
			TextOut(hdc, 510, 680, s17, ARRAYSIZE(s17));
			TextOut(hdc, 510, 700, s18, ARRAYSIZE(s18));
			TextOut(hdc, 510, 720, s19, ARRAYSIZE(s19));
			TextOut(hdc, 510, 740, s20, ARRAYSIZE(s20));


			TCHAR s21[] = L"Увеличить начальный угол дуги - клавиша Z";
			TCHAR s22[] = L"Уменьшить началный угол дуги - клавиша X";
			TCHAR s23[] = L"Увеличить конечный угол дуги - клавиша C";
			TCHAR s24[] = L"Уменьшить конечный угол дуги  - клавиша V";
			TCHAR s25[] = L"Увеличить радиус дуги дуги - клавиша B";
			TCHAR s26[] = L"Уменьшить радиус дуги - клавиша N";
			TCHAR s27[] = L"Увеличить угол поворота дуги - клавиша M";
			TCHAR s28[] = L"Уменьшить угол поворота дуги - клавиша ,";
			TCHAR s29[] = L"Сдвинуть дугу в влево - клавиша -";
			TCHAR s30[] = L"Сдвинуть дугу в право - клавиша =";
			TCHAR s31[] = L"Сдвинуть дугу в низ - клавиша 0";
			TCHAR s32[] = L"Сдвинуть дугу в верх - клавиша 9";

            TextOut(hdc, 1010, 520, s21, ARRAYSIZE(s21));
			TextOut(hdc, 1010, 540, s22, ARRAYSIZE(s22));
			TextOut(hdc, 1010, 560, s23, ARRAYSIZE(s23));
			TextOut(hdc, 1010, 580, s24, ARRAYSIZE(s24));
			TextOut(hdc, 1010, 600, s25, ARRAYSIZE(s25));
			TextOut(hdc, 1010, 620, s26, ARRAYSIZE(s26));
			TextOut(hdc, 1010, 640, s27, ARRAYSIZE(s27));
			TextOut(hdc, 1010, 660, s28, ARRAYSIZE(s28));
			TextOut(hdc, 1010, 680, s29, ARRAYSIZE(s29));
			TextOut(hdc, 1010, 700, s30, ARRAYSIZE(s30));
			TextOut(hdc, 1010, 720, s31, ARRAYSIZE(s31));
			TextOut(hdc, 1010, 740, s32, ARRAYSIZE(s32));

			TCHAR s33[] = L"Для выхода из программы нажмите клавишу ESC";

			static LOGFONT lf; 
			lf.lfCharSet = DEFAULT_CHARSET; 
			lf.lfPitchAndFamily = DEFAULT_PITCH;
			wcscpy_s(lf.lfFaceName, L"Times New Roman"); 
			lf.lfHeight = 40; 
			lf.lfWidth = 10; 
			lf.lfWeight = 30; 
			lf.lfEscapement = 0; 

			HFONT hFont = CreateFontIndirect(&lf);
			SelectObject(hdc, hFont); 
			SetTextColor(hdc, RGB(255, 0, 0)); 
			SetBkColor(hdc, RGB(255, 255, 255)); 
			TextOut(hdc, 500, 790, s33, ARRAYSIZE(s33)); 
			DeleteObject(hFont); 

			EndPaint(hwnd, &ps);
			break;
		}
		case WM_CHAR:
		{
			system("cls");
			switch(wParam)
			{
				case '1':
				{
					hdc = GetDC(hwnd);

					circle c1 = circle(50, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));

					Rectangle(hdc, 0, 500, 500, 0);

					if(c1.get_radius() + fig1_y < 245)
						fig1_y+=5;

					c1.scale(fig1_ratio);
					c1.draw(fig1_x, fig1_y);
					cout << c1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case '2':
				{
					hdc = GetDC(hwnd);

					circle c1 = circle(50, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));

					Rectangle(hdc, 0, 500, 500, 0);

					if(c1.get_radius() - fig1_y < 245)
						fig1_y-=5;

					c1.scale(fig1_ratio);
					c1.draw(fig1_x, fig1_y);
					cout << c1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case '3':
				{
					hdc = GetDC(hwnd);

					circle c1 = circle(50, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));

					Rectangle(hdc, 0, 500, 500, 0);

					if(c1.get_radius() - fig1_x < 245)
						fig1_x-=5;

					c1.scale(fig1_ratio);
					c1.draw(fig1_x, fig1_y);
					cout << c1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case '4':
				{
					hdc = GetDC(hwnd);

					circle c1 = circle(50, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));

					Rectangle(hdc, 0, 500, 500, 0);

					if(c1.get_radius() + fig1_x < 245)
						fig1_x+=5;

					c1.scale(fig1_ratio);
					c1.draw(fig1_x, fig1_y);
					cout << c1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case 'e':
				{
					hdc = GetDC(hwnd);

					circle c1 = circle(50, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));

					if(fig1_ratio < 3.0)
						fig1_ratio += float(0.1);
					c1.scale(fig1_ratio);

					Rectangle(hdc, 0, 500, 500, 0);
					c1.draw(fig1_x, fig1_y);
					cout << c1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case 'r':
				{
					hdc = GetDC(hwnd);

					circle c1 = circle(50, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));

					if(fig1_ratio > -0.9)
						fig1_ratio -= float(0.1);
					c1.scale(fig1_ratio);

					Rectangle(hdc, 0, 500, 500, 0);
					c1.draw(fig1_x, fig1_y);
					cout << c1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case '5':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(fig2.get_small_axle() + fig2_y < 245)
						fig2_y+=5;

					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case '6':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(fig2.get_small_axle() - fig2_y < 245)
						fig2_y-=5;

					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case '7':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(fig2.get_big_axle() - fig2_x < 245)
						fig2_x-=5;

					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case '8':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(fig2.get_big_axle() + fig2_x < 245)
						fig2_x+=5;

					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case 'a':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(fig2_angle >= 0 && fig2_angle < 360)
						fig2_angle += 1;
					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case 's':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));
					
					if(fig2_angle > 0 && fig2_angle <= 360)
						fig2_angle -= 1;
					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case 'd':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(fig2_ratio < 1.5)
						fig2_ratio += float(0.1);
					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case 'f':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(fig2_ratio > -0.9)
						fig2_ratio -= float(0.1);
					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case 'g':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(big_axle < 70)
						big_axle += 3;
					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case 'h':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(big_axle > 6)
						big_axle -= 3;
					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);		
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case 'j':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(small_axle < 70)
						small_axle += 3;
					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case 'k':
				{
					hdc = GetDC(hwnd);

					ellipse e1 = ellipse(200, 100, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));

					if(small_axle > 6)
						small_axle -= 3;
					e1.set_small_axle(small_axle);
					e1.set_big_axle(big_axle);
					e1.rotate(fig2_angle);
					e1.scale(fig2_ratio);

					Rectangle(hdc, 500, 500, 1000, 0);
					e1.draw(fig2_x, fig2_y);
					cout << e1 << endl;
										
					EndPaint(hwnd, &ps);
					break;
				}
				case '9':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(a1.get_radius() + fig3_y < 245)
						fig3_y+=5;

					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case '0':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(a1.get_radius() - fig3_y < 245)
						fig3_y-=5;

					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case '-':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(a1.get_radius() - fig3_x < 245)
						fig3_x-=5;

					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case '=':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(a1.get_radius() + fig3_x < 245)
						fig3_x+=5;

					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case 'z':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(angle1 <= 357)
						angle1 += 3;
					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}

				case 'x':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(angle1 >= 3)
						angle1 -= 3;
					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case 'c':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(angle2 <= 357)
						angle2 += 3;
					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case 'v':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(angle2 >= 3)
						angle2 -= 3;
					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case 'b':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(fig3_ratio < 3.0)
						fig3_ratio += float(0.1);
					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case 'n':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(fig3_ratio > -0.9)
						fig3_ratio -= float(0.1);
					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case 'm':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(fig3_angle < 360)
						fig3_angle += 1;
					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case ',':
				{
					hdc = GetDC(hwnd);

					arc a1 = arc(100, 0, 270, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
					
					if(fig3_angle > 0)
						fig3_angle -= 1;
					a1.set_start_angle(angle1);
					a1.set_stop_angle(angle2);
					a1.rotate(fig3_angle);
					a1.scale(fig3_ratio);

					Rectangle(hdc, 1000, 500, 1500, 0);
					a1.draw(fig3_x, fig3_y);
					cout << a1 << endl;

					EndPaint(hwnd, &ps);
					break;
				}
				case '/':
				{
					cout << "Circle vs Ellipse: " << shape::comparePerimeter(fig1, fig2) << endl;
					cout << "Circle vs Arc: " << shape::comparePerimeter(fig1, fig3) << endl;
					cout << "Ellipse vs Arc: " << shape::comparePerimeter(fig2, fig3) << endl;
					
					break;
				}
			}
			break;
		}
		case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
				exit(0);
			else break;
		}
		case WM_DESTROY:  
		{
			PostQuitMessage(0);                          
			break;
		}
		default:                                    
			return DefWindowProc(hwnd, message, wParam, lParam);
	}                                                           
	return 0;
}

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	
	HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOW);
	SetWindowPos(hWnd, HWND_TOPMOST, 400, 500, 677, 350, SWP_NOACTIVATE);

	my_window wnd;
	wnd.WinMain(hInstance, hPrevInst, lpszArgs, nWinMode);
}