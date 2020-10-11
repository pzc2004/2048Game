#include <cstdio>
#include <ctime>
#include <vector>
#include <windows.h>
/* A useful thing */
#include <gdiplus.h>
using namespace std;
using namespace Gdiplus;
namespace game
{
	int x[]= {0, 1, 0, -1}, y[]= {1, 0, -1, 0};
	struct point
	{
		int x, y;
		inline point(int x= 0, int y= 0) : x(x), y(y) {}
	};
	struct Table
	{
		bool dead;
		int a[4][4], score, maxscore;
		vector<point> rest;
		void insert(int x)
		{
			int ins= rand() % rest.size();
			a[rest[ins].x][rest[ins].y]= x;
			rest.erase(rest.begin() + ins);
		}
		void init()
		{
			memset(a, 0, sizeof(a)), dead= 0, score= 0;
			update();
			bool bb= rand() % 2;
			if(!bb)
				insert(2), insert(2);
			else
				insert(2), insert(4);
		}
		void check()
		{
			bool bb= 0;
			for(int i= 0; i < 4; i++)
			{
				for(int j= 0; j < 4; j++)
				{
					if(!a[i][j])
					{
						bb= 1;
						break;
					}
					for(int no= 0; no < 4; no++)
					{
						int nox= i + x[no], noy= j + y[no];
						if(nox < 0 || nox >= 4 || noy < 0 || noy >= 4) continue;
						if(a[nox][noy] == a[i][j]) bb= 1;
					}
				}
			}
			if(!bb) dead= 1;
		}
		void update()
		{
			rest.clear();
			for(int i= 0; i < 4; i++)
				for(int j= 0; j < 4; j++)
					if(!a[i][j]) rest.push_back(point(i, j));
		}
		bool checkmove(int op)
		{
			switch(op)
			{
				case 1:	 //Left
				{
					for(int i= 0; i < 4; i++)
					{
						for(int j= 1; j < 4; j++)
						{
							if(!a[i][j]) continue;
							if(!a[i][j - 1] || a[i][j - 1] == a[i][j]) return 1;
						}
					}
					break;
				}
				case 2:	 //Up
				{
					for(int i= 1; i < 4; i++)
					{
						for(int j= 0; j < 4; j++)
						{
							if(!a[i][j]) continue;
							if(!a[i - 1][j] || a[i - 1][j] == a[i][j]) return 1;
						}
					}
					break;
				}
				case 3:	 //Right
				{
					for(int i= 0; i < 4; i++)
					{
						for(int j= 0; j < 3; j++)
						{
							if(!a[i][j]) continue;
							if(!a[i][j + 1] || a[i][j + 1] == a[i][j]) return 1;
						}
					}
					break;
				}
				case 4:	 //Down
				{
					for(int i= 0; i < 3; i++)
					{
						for(int j= 0; j < 4; j++)
						{
							if(!a[i][j]) continue;
							if(!a[i + 1][j] || a[i + 1][j] == a[i][j]) return 1;
						}
					}
					break;
				}
			}
			return 0;
		}
		void move(int op)
		{
			check();
			if(dead) return;
			if(!checkmove(op)) return;
			switch(op)
			{
				case 1:	 //Left
				{
					for(int i= 0; i < 4; i++)
					{
						for(int j= 1; j < 4; j++)
						{
							if(!a[i][j]) continue;
							int k= j;
							while(k > 0 && !a[i][k - 1])
							{
								a[i][k - 1]= a[i][k], a[i][k]= 0, --k;
							}
						}
					}
					for(int i= 0; i < 4; i++)
					{
						for(int j= 0; j < 3; j++)
						{
							if(!a[i][j]) continue;
							if(a[i][j] == a[i][j + 1])
							{
								a[i][j]<<= 1, score+= a[i][j];
								for(int k= j + 1; k < 3; k++) a[i][k]= a[i][k + 1];
								a[i][3]= 0;
							}
						}
					}
					break;
				}
				case 2:	 //Up
				{
					for(int j= 0; j < 4; j++)
					{
						for(int i= 1; i < 4; i++)
						{
							if(!a[i][j]) continue;
							int k= i;
							while(k > 0 && !a[k - 1][j])
							{
								a[k - 1][j]= a[k][j], a[k][j]= 0, --k;
							}
						}
					}
					for(int j= 0; j < 4; j++)
					{
						for(int i= 0; i < 3; i++)
						{
							if(!a[i][j]) continue;
							if(a[i][j] == a[i + 1][j])
							{
								a[i][j]<<= 1, score+= a[i][j];
								for(int k= i + 1; k < 3; k++) a[k][j]= a[k + 1][j];
								a[3][j]= 0;
							}
						}
					}
					break;
				}
				case 3:	 //Right
				{
					for(int i= 0; i < 4; i++)
					{
						for(int j= 3; j >= 0; j--)
						{
							if(!a[i][j]) continue;
							int k= j;
							while(k < 3 && !a[i][k + 1])
							{
								a[i][k + 1]= a[i][k], a[i][k]= 0, ++k;
							}
						}
					}
					for(int i= 0; i < 4; i++)
					{
						for(int j= 4; j > 0; j--)
						{
							if(!a[i][j]) continue;
							if(a[i][j] == a[i][j - 1])
							{
								a[i][j]<<= 1, score+= a[i][j];
								for(int k= j - 1; k > 0; k--) a[i][k]= a[i][k - 1];
								a[i][0]= 0;
							}
						}
					}
					break;
				}
				case 4:	 //Down
				{
					for(int j= 0; j < 4; j++)
					{
						for(int i= 3; i >= 0; i--)
						{
							if(!a[i][j]) continue;
							int k= i;
							while(k < 3 && !a[k + 1][j])
							{
								a[k + 1][j]= a[k][j], a[k][j]= 0, ++k;
							}
						}
					}
					for(int j= 0; j < 4; j++)
					{
						for(int i= 4; i > 0; i--)
						{
							if(!a[i][j]) continue;
							if(a[i][j] == a[i - 1][j])
							{
								a[i][j]<<= 1, score+= a[i][j];
								for(int k= i - 1; k > 0; k--) a[k][j]= a[k - 1][j];
								a[0][j]= 0;
							}
						}
					}
					break;
				}
			}
			update();
			int x= rand() % 10;
			if(x == 0)
				insert(4);
			else
				insert(2);
			check();
			if(dead) return;
		}
	};
}  // namespace game
using game::Table;
Table table;
int Page;
PAINTSTRUCT ps;
Color numColor[64]= {
	Color::MakeARGB(255, 205, 193, 180),
	Color::MakeARGB(255, 238, 228, 218),
	Color::MakeARGB(255, 237, 224, 220),
	Color::MakeARGB(255, 242, 177, 121),
	Color::MakeARGB(255, 245, 149, 99),
	Color::MakeARGB(255, 246, 124, 95),
	Color::MakeARGB(255, 246, 94, 59),
	Color::MakeARGB(255, 237, 207, 114),
	Color::MakeARGB(255, 237, 204, 97),
	Color::MakeARGB(255, 236, 200, 80),
	Color::MakeARGB(255, 237, 196, 62),
	Color::MakeARGB(255, 237, 194, 46),
	// Color::MakeARGB(255,),
};
void PrintPage(Graphics &g)
{
	g.Clear(Color::White);
	Pen penY(Color::Yellow, 3), penR(Color::Red, 3), penB(Color::Brown);
	Font fonts(L"Blackadder ITC", 24, FontStyleRegular, UnitPoint, NULL);
	Font fontm(L"Blackadder ITC", 32, FontStyleRegular, UnitPoint, NULL);
	Font fontl(L"Blackadder ITC", 48, FontStyleRegular, UnitPoint, NULL);
	SolidBrush sbR(Color::Red), sbY(Color::Yellow);
	SolidBrush sbNum1(Color::MakeARGB(255, 119, 110, 101)), sbNum2(Color::MakeARGB(255, 249, 246, 242));
	// SolidBrush sb0(Color::MakeARGB(255, 205, 193, 180));
	// SolidBrush sb2(Color::MakeARGB(255, 238, 228, 218));
	// SolidBrush sb4(Color::MakeARGB(255, 237, 224, 220));
	// SolidBrush sb8(Color::MakeARGB(255, 242, 177, 121));
	// SolidBrush sb16(Color::MakeARGB(255, 245, 149, 99));
	// SolidBrush sb32(Color::MakeARGB(255, 246, 124, 95));
	// SolidBrush sb64(Color::MakeARGB(255, 246, 94, 59));
	// SolidBrush sb128(Color::MakeARGB(255, 237, 207, 114));
	switch(Page)
	{
		case 0:
		{
			g.DrawString(L"Welcome to 2048Game!", -1, &fontl, PointF(30, 30), &sbR);
			g.FillRectangle(&sbY, 240, 120, 140, 50);
			g.DrawString(L"Start game", -1, &fonts, PointF(250, 125), &sbR);
			if(table.maxscore)
			{
				wchar_t s[128];
				swprintf(s, L"Maxscore:%d", table.maxscore);
				g.DrawString(s, -1, &fontl, PointF(140, 200), &sbNum1);
			}
			break;
		}
		case 1:
		{
			for(int i= 0; i < 4; i++)
			{
				for(int j= 0; j < 4; j++)
				{
					SolidBrush sb(numColor[0]);
					Font *font;
					if(table.a[i][j])
					{
						sb.SetColor(numColor[(int)log2(table.a[i][j])]);
					}
					g.FillRectangle(&sb, 100 + 80 * j, 100 + 80 * i, 80, 80);
					if(table.a[i][j])
					{
						wchar_t s[128];
						swprintf(s, L"%d", table.a[i][j]);
						g.DrawString(s, -1, &fontl, PointF(100 + 80 * j, 93 + 80 * i), &(table.a[i][j] < 8 ? sbNum1 : sbNum2));
					}
					g.DrawRectangle(&penB, 100 + 80 * j, 100 + 80 * i, 80, 80);
				}
			}
			g.FillRectangle(&sbY, 480, 320, 120, 50);
			g.DrawString(L"Restart", -1, &fonts, PointF(490, 325), &sbR);
			wchar_t s[128];
			swprintf(s, L"Score:%d", table.score);
			g.DrawString(s, -1, &fontl, PointF(140, 20), &sbNum1);
			printf("%d\n", table.dead);
			if(table.dead)
			{
				table.maxscore= max(table.maxscore, table.score);
				g.DrawString(L"Game over!", -1, &fontl, PointF(180, 70), &sbR);
			}
			break;
		}
	}
}
void Click(HWND hwnd, int x, int y)
{
	HDC hdc= ::GetDC(hwnd);
	Graphics g(hdc);
	switch(Page)
	{
		case 0:
		{
			if(x >= 240 && x <= 380 && y >= 120 && y <= 170)
			{
				Page= 1;
				table.init();
				PrintPage(g);
			}
			break;
		}
		case 1:
		{
			if(x >= 480 && x <= 600 && y >= 320 && y <= 370)
			{
				Page= 0;
				PrintPage(g);
			}
			break;
		}
	}
	g.ReleaseHDC(hdc);
	ReleaseDC(hwnd, hdc);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			int x= lParam & 0xffff, y= lParam >> 16;
			Click(hwnd, x, y);
			break;
		}
		case WM_PAINT:
		{
			HDC hdc= BeginPaint(hwnd, &ps);
			Graphics g(hdc);
			PrintPage(g);
			g.ReleaseHDC(hdc);
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_KEYDOWN:
		{
			HDC hdc= ::GetDC(hwnd);
			Graphics g(hdc);
			int op;
			switch(wParam)
			{
				case 37: op= 1; break;
				case 65: op= 1; break;
				case 38: op= 2; break;
				case 87: op= 2; break;
				case 39: op= 3; break;
				case 68: op= 3; break;
				case 40: op= 4; break;
				case 83: op= 4; break;
				default: op= 0;
			}
			if(Page == 1 && op && !table.dead) table.move(op);
			PrintPage(g);
			g.ReleaseHDC(hdc);
			ReleaseDC(hwnd, hdc);
			break;
		}
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(0));
	system("chcp 65001");
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd;	   /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg;	   /* A temporary location for all messages */
	/* zero out the struct and set the stuff we want to modify */
	memset(&wc, 0, sizeof(wc));
	wc.cbSize= sizeof(WNDCLASSEX);
	wc.lpfnWndProc= WndProc; /* This is where we will send messages to */
	wc.hInstance= hInstance;
	wc.hCursor= LoadCursor(NULL, IDC_ARROW);
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground= (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName= "WindowClass";
	wc.hIcon= LoadIcon(NULL, IDI_APPLICATION);	 /* Load a standard icon */
	wc.hIconSm= LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */
	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	hwnd= CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Caption", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, /* x */
						 CW_USEDEFAULT,																				  /* y */
						 640,																						  /* width */
						 480,																						  /* height */
						 NULL,
						 NULL,
						 hInstance,
						 NULL);
	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{							/* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg);	/* Send it to WndProc */
	}
	return msg.wParam;
}