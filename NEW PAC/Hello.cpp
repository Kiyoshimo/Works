#include <afxwin.h>
#include <time.h>
#include <math.h>
#include "Hello.h"
#include "CockRoach.h"
#include "GlobalInfo.h"
#include "ImageData.h"
#include "resource1.h"
#include<vector>
#include<cstdlib>
# include<iostream>
#include<windows.h>
# include<stdio.h>
#include <string>    
#include<algorithm>
#include<fstream>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

#define TIMER_CKROACH 1
using namespace std;
#define MaxSize 1


CPerson p;
//-----------------------
string FX = "r";
string ofx = "r";
vector <vector <int> > map;
struct ghostclass { int x, y, ox, oy, oox, ooy; };
vector <ghostclass  > ghost;
//-----------------------


CMyApp myApp;
DWORD prevTime;
CCockRoach ck;
CImageData *CGlobalInfo::image_data = new CImageData;



BOOL CMyApp::InitInstance ()
{


    m_pMainWnd = new CMainWindow;
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow ();
    return TRUE;
}


void CMainWindow::OnKeyDown(UINT nchar, UINT nRepCnt, UINT nFlags) {

	if (dead == false) {
		if (nchar == VK_LEFT) { FX = "l"; }
		if (nchar == VK_RIGHT) { FX = "r"; }
		if (nchar == VK_DOWN) { FX = "d"; }
		if (nchar == VK_UP) { FX = "u"; }
		if (nchar == VK_UP) { FX = "u"; }
		if (nchar == VK_ESCAPE) { pause = !pause; }
	}
}
void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point) {
	SetCapture();
	click = true;
	if (rule == true) rule =false;
	if(sel == 2) rule = true;
	
}

void CMainWindow::OnMouseMove(UINT nFlags, CPoint point) {
	if (point.x > 780 && point.x < 1020)
	{
		if (point.y > 512 && point.y < 512+ 59)
		{ sel = 1; }
		else if (point.y > 512 + 59 && point.y < 512 + 59 + 59) { sel = 2; }
		else if (point.y > 512 + 59 + 59 && point.y < 512 + 59 + 59 + 59) { sel = 3; }
		else { sel = 0; }
	}
	else { sel = 0; }
}

BEGIN_MESSAGE_MAP (CMainWindow, CFrameWnd)

	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER ()
END_MESSAGE_MAP ()

BOOL CMainWindow::PreCreateWindow(CREATESTRUCT& cs)
{ 
	if(!CFrameWnd::PreCreateWindow(cs) ) 
		return FALSE; 
	cs.style &= ~WS_MAXIMIZEBOX; 
	cs.style &= ~WS_SIZEBOX; 
	cs.cx = BIG_COCKROACH_WIDTH;
	cs.cy = BIG_COCKROACH_HEIGHT;
	return TRUE; 
} 

CMainWindow::CMainWindow ()
{	
#if 0
	POINT window_pos;
	window_pos.x = window_pos.y = 0;
	SIZE window_size;
	window_size.cx = BIG_COCKROACH_WIDTH;
	window_size.cy = BIG_COCKROACH_HEIGHT;
	CRect rect(window_pos, window_size);
    Create (NULL, _T (" "), WS_OVERLAPPED | WS_SYSMENU | WS_BORDER, rect);		
#else
	Create (NULL, _T (" "));	
#endif
}



int CMainWindow::OnCreate(LPCREATESTRUCT lpcs)
{
	srand((unsigned int)time(NULL));
	if (CFrameWnd::OnCreate(lpcs) == -1)
		return -1;
	if (!SetTimer(TIMER_CKROACH, SPEED, NULL)) {
		MessageBox("SetTimer failed");
		return -1;
	}

	CGlobalInfo::image_data->Initialize();
	m_bTracking = false;
	prevTime = GetTickCount();
	CRect rect;
	GetClientRect(&rect);
	ck.setPos(50, 10);

	return 0;
}
void CMainWindow::OnTimer(UINT nTimerID) {





	fps++;
	srand(time(NULL));
	CBitmap bmp;
	CRect rect;
	CClientDC pDC(this);
	CDC mdc, BGdc;


	GetClientRect(&rect);
	mdc.CreateCompatibleDC(&pDC);
	BGdc.CreateCompatibleDC(&pDC);
	bmp.CreateCompatibleBitmap(&pDC, rect.Width(), rect.Height());
	BGdc.SelectObject(&CGlobalInfo::image_data->ck_BG);
	mdc.SelectObject(&bmp);

	if (bgm1 == 1) {sndPlaySound("menu.wav", SND_ASYNC); bgm1 = 0;}


	


	//暂停
	{
		if (pause == true) {
			ck.pause1(&mdc);
			pDC.BitBlt(540, 330, 180, 60, &mdc, 0, 0, SRCCOPY);
			pa = 1;
		}
		else {
			if (pa == 1) {
				ck.pause0(&mdc);
				pDC.BitBlt(540, 330, 180, 60, &mdc, 0, 0, SRCCOPY); pa = 0;
			}
		}
	}


	//开头动画
	{
		if (KT == true)
		{
		
			t1++;
			if (t1 <= 250) {
				ck.KT1(&mdc);
				pDC.BitBlt(0, 0, 1800, 900, &mdc, 0, 0, SRCCOPY);
			}


			else if (t1 < 50000) {
				if (!rule ) {
					ck.setPos(333, 200);
					if (t1 / 3 % 7 == 0) ck.logo0(&mdc);
					if (t1 / 3 % 7 == 1) ck.logo1(&mdc);
					if (t1 / 3 % 7 == 2) ck.logo2(&mdc);
					if (t1 / 3 % 7 == 3) ck.logo3(&mdc);
					if (t1 / 3 % 7 == 4) ck.logo4(&mdc);
					if (t1 / 3 % 7 == 5) ck.logo5(&mdc);
					if (t1 / 3 % 7 == 6) ck.logo6(&mdc);
					ck.menu(&mdc);
					if (sel != 0) { ck.setPos(765, 535 - 59 + sel * 59); ck.tri(&mdc); }


					pDC.BitBlt(0, 0, 1800, 900, &mdc, 0, 0, SRCCOPY);

					//----------------

					if (xx == 2100) { FX = "l"; }
					if (xx == -100) { FX = "r"; }
					if (FX == "r") { xx = xx + 10; x_ps = xx + 26; y_ps = yy - 14; x_pe = xx + 26; y_pe = yy + 14; }
					if (FX == "l") { xx = xx - 10; x_pe = xx - 26; y_pe = yy - 14; x_ps = xx - 26; y_ps = yy + 14; }

					CPoint PacS(x_ps, y_ps);
					CPoint PacE(x_pe, y_pe);
					CPoint Mouth[3] = { CPoint(x_ps, y_ps) ,CPoint(xx,yy), CPoint(x_pe, y_pe) };
					CRect Pac(xx - 30, yy - 30, xx + 30, yy + 30);
					pDC.SelectObject(PY);
					pDC.Arc(&Pac, PacS, PacE);
					pDC.Polyline(Mouth, 3);

					for (int ikt = 0; ikt < 3; ikt++) {
						gxx = xx - 100 - 60 * ikt;
						if (FX == "r") { pDC.SelectObject(PP); }
						if (FX == "l") { pDC.SelectObject(PB); }
						CPoint Mbody[7] = { CPoint(gxx + 20,gyy) ,CPoint(gxx + 20,gyy + 30),CPoint(gxx + 10,gyy + 15),CPoint(gxx  ,gyy + 30) ,CPoint(gxx - 10,gyy + 15) ,CPoint(gxx - 20,gyy + 30) ,CPoint(gxx - 20,gyy) };
						CPoint MS(gxx + 20, gyy);
						CPoint ME(gxx - 20, gyy);
						CRect M(gxx - 20, gyy - 20, gxx + 20, gyy + 20);
						pDC.Polyline(Mbody, 7);
						pDC.Arc(&M, MS, ME);
					}


					if (click == true) {
						if (sel == 1) { KT = false; }
						if (sel == 2) { KT = true; }
						if (sel == 3) { exit(0); }
					}

				}


				if (rule ) {
					ck.r(&mdc);
					pDC.BitBlt(0, 0, 1800, 1800, &mdc, 0, 0, SRCCOPY);
					
				}
			}
		}
		
	}







	if (KT == false && pause == false)
	{

		if (bgm2 == 1)
		{ sndPlaySound("g.wav", SND_ASYNC); bgm2 = 0; }
		if (restart == true) //墙壁
		{
			srand(time(NULL));

			CRect backdrop(0, 0, rect.Width(), rect.Height());
			pDC.SelectObject(BD);
			pDC.Rectangle(&backdrop);//绘制矩形
			restart = false;

			//墙读档
			ifstream fin("map.txt");
			for (int i0 = 0; i0 < 13; i0++) {
				vector <int> yihang;
				int mx;
				int my;
				for (int i1 = 0; i1 < 23; i1++) {
					int ppp;
					fin >> ppp;
					yihang.push_back(ppp);
				}
				map.push_back(yihang);
			}
			fin.close();
			//画出蓝色墙壁
			for (int i2 = 1; i2 < 12; i2++)
			{
				for (int i3 = 1; i3 < 22; i3++) {
					if (map[i2][i3] == 0) {
						if (map[i2][i3 - 1] == 0 && i3 != 1)//左边墙壁
						{
							pDC.SelectObject(PL); pDC.MoveTo(i3 * 60 - 30, i2 * 60); pDC.LineTo(i3 * 60, i2 * 60);
						}
						if (map[i2][i3 + 1] == 0 && i3 != 21)//右边墙壁
						{
							pDC.SelectObject(PL); pDC.MoveTo(i3 * 60 + 30, i2 * 60); pDC.LineTo(i3 * 60, i2 * 60);
						}
						if (map[i2 - 1][i3] == 0 && i2 != 1)//上边墙壁
						{
							pDC.SelectObject(PL); pDC.MoveTo(i3 * 60, i2 * 60 - 30); pDC.LineTo(i3 * 60, i2 * 60);
						}
						if (map[i2 + 1][i3] == 0 && i2 != 11)//下边墙壁
						{
							pDC.SelectObject(PL); pDC.MoveTo(i3 * 60, i2 * 60 + 30); pDC.LineTo(i3 * 60, i2 * 60);
						}
					}
					else if (map[i2][i3] == 2)//豆子
					{
						CRect dou(i3 * 60 - 3, i2 * 60 - 3, i3 * 60 + 3, i2 * 60 + 3); pDC.SelectObject(&PW); pDC.Rectangle(&dou);
					}//绘制矩形
					else if (map[i2][i3] == 3)//大力丸
					{
						CRect dou(i3 * 60 - 10, i2 * 60 - 10, i3 * 60 + 10, i2 * 60 + 10); pDC.SelectObject(&PW); pDC.Ellipse(&dou);
					}//绘制矩形
				}

				//

			}

		}
		//随机数种子


		
		if ((dead == false&& END==false)&&fps%6==0) {

			//怪物位置
			for (int im = 0; im < gnum; im++) {
				ghostclass g1;
				g1.x = 9 + im; g1.y = 6;
				g1.ox = 0; g1.oy = 0;
				ghost.push_back(g1);
			}



			//大力模式
			if (s_t > 0) { s_t--; }

			//吃豆人移动
			{
				if (FX == "r") { x++; if (map[y][x] == 0) { x--; } }
				else if (FX == "l") { x--; if (map[y][x] == 0) { x++; } }
				else if (FX == "u") { y--; if (map[y][x] == 0) { y++; } }
				else if (FX == "d") { y++; if (map[y][x] == 0) { y--; } }
			}

			//删除上一个pac位置
			{
				CRect OPac1(x * 60 - 31, y * 60 - 31, x * 60 + 31, y * 60 + 31);
				CRect OPac2(ox * 60 - 31, oy * 60 - 31, ox * 60 + 31, oy * 60 + 31);
				pDC.SelectObject(PD); pDC.SelectObject(BD);
				pDC.Rectangle(&OPac1); pDC.Rectangle(&OPac2);
			}

			//删除上一个分数
			{
				CRect oscrse(1400, -60, 1620, 180);
				pDC.SelectObject(PD);
				pDC.Ellipse(&oscrse);
			}
			//删除上一个怪物位置
			for (int i8 = 0; i8 < gnum; i8++) {
				int gx, gy;
				gx = ghost[i8].x; gy = ghost[i8].y;
				pDC.SelectObject(PD);
				CPoint Mbody[7] = { CPoint(gx * 60 + 20,gy * 60) ,CPoint(gx * 60 + 20,gy * 60 + 30),CPoint(gx * 60 + 10,gy * 60 + 15),CPoint(gx * 60 ,gy * 60 + 30) ,CPoint(gx * 60 - 10,gy * 60 + 15) ,CPoint(gx * 60 - 20,gy * 60 + 30) ,CPoint(gx * 60 - 20,gy * 60) };
				pDC.Polyline(Mbody, 7);
				CPoint MS(gx * 60 + 20, gy * 60);
				CPoint ME(gx * 60 - 20, gy * 60);
				CRect M(gx * 60 - 20, gy * 60 - 20, gx * 60 + 20, gy * 60 + 20);
				pDC.Arc(&M, MS, ME);
			}

			//吃豆人方向（FX）
			{
				if (FX == "r") { x_ps = x * 60 + 26; y_ps = y * 60 - 14; x_pe = x * 60 + 26; y_pe = y * 60 + 14; }
				else if (FX == "l") { x_pe = x * 60 - 26; y_pe = y * 60 - 14; x_ps = x * 60 - 26; y_ps = y * 60 + 14; }
				else if (FX == "u") { x_pe = x * 60 + 14; y_pe = y * 60 - 26; x_ps = x * 60 - 14; y_ps = y * 60 - 26; }
				else if (FX == "d") { x_ps = x * 60 + 14; y_ps = y * 60 + 26; x_pe = x * 60 - 14; y_pe = y * 60 + 26; }
				cout << x * 60 << " " << "y*60" << endl;
			}

			//印出吃豆人
			{
				
				CPoint PacS(x_ps, y_ps);
				CPoint PacE(x_pe, y_pe);
				CPoint Mouth[3] = { CPoint(x_ps, y_ps) ,CPoint(x * 60,y * 60), CPoint(x_pe, y_pe) };
				CRect Pac(x * 60 - 30, y * 60 - 30, x * 60 + 30, y * 60 + 30);

				pDC.SelectObject(PY);
				pDC.Arc(&Pac, PacS, PacE);
				pDC.Polyline(Mouth, 3);
			}




			//怪物随机移动
			{
				for (int i4 = 0; i4 < gnum; i4++) {
					int gx, gy, gox, goy, ra, cc;
					cc = 0;
					string gfx;
					int l = 0; int d = 0; int r = 0; int u = 0;
					gx = ghost[i4].x; gy = ghost[i4].y; gox = ghost[i4].ox; goy = ghost[i4].oy;
					if (map[gy][gx + 1] != 0) { cc++; l = 1; }
					if (map[gy][gx - 1] != 0) { cc++; r = 1; }
					if (map[gy + 1][gx] != 0) { cc++; d = 1; }
					if (map[gy - 1][gx] != 0) { cc++; u = 1; }
					ra = (rand() % 12);

					if (cc == 1) {
						if (l == 1) gfx = "l";
						else if (r == 1) gfx = "r";
						else if (u == 1) gfx = "u";
						else if (d == 1) gfx = "d";
					}

					else {
						while (ra > 0) {
							if (l == 1 && gx + 1 != gox) { gfx = "l"; ra--; }
							if (ra <= 0)break;
							if (r == 1 && gx - 1 != gox) { gfx = "r"; ra--; }
							if (ra <= 0)break;
							if (u == 1 && gy - 1 != goy) { gfx = "u"; ra--; }
							if (ra <= 0)break;
							if (d == 1 && gy + 1 != goy) { gfx = "d"; ra--; }
							if (ra <= 0)break;
						}


					}

					if (gfx == "l") { ghost[i4].ox = gx; ghost[i4].oy = gy; ghost[i4].x = gx + 1; }
					if (gfx == "r") { ghost[i4].ox = gx; ghost[i4].oy = gy; ghost[i4].x = gx - 1; }
					if (gfx == "u") { ghost[i4].ox = gx; ghost[i4].oy = gy; ghost[i4].y = gy - 1; }
					if (gfx == "d") { ghost[i4].ox = gx; ghost[i4].oy = gy; ghost[i4].y = gy + 1; }

				}

			}

			//画出怪物g(gx,gy)
			for (int i5 = 0; i5 < gnum; i5++) {
				int gx, gy;
				gx = ghost[i5].x; gy = ghost[i5].y;
				if (s_t == 0 || s_t == 2 || s_t == 4) { pDC.SelectObject(PP); }
				else { pDC.SelectObject(PB); }
				CPoint Mbody[7] = { CPoint(gx * 60 + 20,gy * 60) ,CPoint(gx * 60 + 20,gy * 60 + 30),CPoint(gx * 60 + 10,gy * 60 + 15),CPoint(gx * 60 ,gy * 60 + 30) ,CPoint(gx * 60 - 10,gy * 60 + 15) ,CPoint(gx * 60 - 20,gy * 60 + 30) ,CPoint(gx * 60 - 20,gy * 60) };
				pDC.Polyline(Mbody, 7);
				CPoint MS(gx * 60 + 20, gy * 60);
				CPoint ME(gx * 60 - 20, gy * 60);
				CRect M(gx * 60 - 20, gy * 60 - 20, gx * 60 + 20, gy * 60 + 20);
				pDC.Arc(&M, MS, ME);
			}

			//碰撞判定
			for (int i6 = 0; i6 < gnum; i6++) {

				if ((x == ghost[i6].x) && (y == ghost[i6].y) && (s_t == 0)) {
					dead = true;
					//system("PAUSE");
				}
				if ((x == ghost[i6].ox) && (y == ghost[i6].oy) && (ox == ghost[i6].x) && (oy == ghost[i6].y) && (s_t == 0)) {
					dead = true;
					//system("PAUSE");
				}
				if ((x == ghost[i6].x) && (y == ghost[i6].y) && (s_t != 0)) {
					ghost[i6].x = 9 + i6; ghost[i6].y = 6;
					ghost[i6].ox = 0; ghost[i6].oy = 0;
				}
			}



			//吃东西
			{
				if (map[y][x] == 2) { map[y][x] = 1; score++; }//eat到豆子
				if (map[y][x] == 3) //eat到大力丸
				{
					map[y][x] = 1; 
					strong = true;
					if(s_t==0)bgms = 1;
					else bgms = 0;
					s_t = startime;
				 }
				
				if (bgms == 1) { sndPlaySound("super.wav", SND_ASYNC); bgms = 0; }
				if (s_t == 1) { bgm2 = 1; }

			}



			//分数显示
			{
				int bs, bsx, bsy; pDC.SelectObject(PB);
				for (int i7 = 0; i7 < 2; i7++) {
					if (i7 == 0) { bsx = 1440, bsy = 60;  bs = score / 10; }
					if (i7 == 1) { bsx = 1500, bsy = 60;  bs = score % 10; }
					if (seg[bs][0] == 1) { pDC.MoveTo(bsx - 20, bsy - 30);    pDC.LineTo(bsx + 20, bsy - 30); }
					if (seg[bs][1] == 1) { pDC.MoveTo(bsx + 20, bsy - 30);    pDC.LineTo(bsx + 20, bsy); }
					if (seg[bs][2] == 1) { pDC.MoveTo(bsx + 20, bsy);		  pDC.LineTo(bsx + 20, bsy + 30); }
					if (seg[bs][3] == 1) { pDC.MoveTo(bsx - 20, bsy + 30);    pDC.LineTo(bsx + 20, bsy + 30); }
					if (seg[bs][4] == 1) { pDC.MoveTo(bsx - 20, bsy);		  pDC.LineTo(bsx - 20, bsy + 30); }
					if (seg[bs][5] == 1) { pDC.MoveTo(bsx - 20, bsy);	      pDC.LineTo(bsx - 20, bsy - 30); }
					if (seg[bs][6] == 1) { pDC.MoveTo(bsx - 20, bsy);		  pDC.LineTo(bsx + 20, bsy); }
				}

				if (score == 98) { END = true;  }
			}


			//记录旧的pac位置
			ox = x; oy = y; ofx = FX;
			for (int i9 = 0; i9 < gnum; i9++) {
				ghost[i9].oox = ghost[i9].x; ghost[i9].ooy = ghost[i9].y;
			}



		}
	}

		//死亡动画
		if (dead == true){
			t2=t2+deadspeed;
			SPEED = 1;
			if (bgmd == 1) { sndPlaySound("dead.wav", SND_ASYNC); bgmd = 0; }
				CRect backdrop(0, 0, rect.Width(), rect.Height());
				pDC.SelectObject(BD);
				pDC.Rectangle(&backdrop);//绘制矩形
			
			if (t2 < 50) {
				CPoint PacS(x_ps, y_ps);
				CPoint PacE(x_pe, y_pe);
				CPoint Mouth[3] = { CPoint(x_ps, y_ps) ,CPoint(x * 60,y * 60), CPoint(x_pe, y_pe) };
				CRect Pac(x * 60 - 30, y * 60 - 30, x * 60 + 30, y * 60 + 30);
				pDC.SelectObject(PY);
				pDC.Arc(&Pac, PacS, PacE);
				pDC.Polyline(Mouth, 3);
				deadspeed = 10;
			}
			else if (t2 < 565) {


				if (FX == "r") { x_pe = x * 60 + 30 * cos(((double)t2/180)); y_pe = y * 60+ 30 * sin(((double)t2 / 180)); x_ps = x * 60 +30 * cos(((double)t2 / 180)); y_ps = y * 60 - 30 * sin(((double)t2 / 180)); }
				else if (FX == "l") { x_ps = x * 60 - 30 * cos(((double)t2 / 180)); y_ps = y * 60 + 30 * sin(((double)t2 / 180)); x_pe = x * 60 - 30 * cos(((double)t2 / 180)); y_pe = y * 60 - 30 * sin(((double)t2 / 180)); }
				else if (FX == "u") { x_pe = x * 60 + 30 * sin(((double)(565-t2) / 180)); y_pe = y * 60+ 30 * cos(((double)(565 - t2) / 180)); x_ps = x * 60 - 30 * sin(((double)(565 - t2) / 180)); y_ps = y * 60 + 30 * cos(((double)(565 - t2) / 180)); }
				else if (FX == "d") { x_ps = x * 60 + 30 * sin(((double)(565 - t2) / 180)); y_ps = y * 60 - 30 * cos(((double)(565 - t2) / 180)); x_pe = x * 60 - 30 * sin(((double)(565 - t2) / 180)); y_pe = y * 60 -30 * cos(((double)(565 - t2) / 180)); }

				CPoint PacS(x_ps, y_ps);
				CPoint PacE(x_pe, y_pe);
				CPoint Mouth[3] = { CPoint(x_ps, y_ps) ,CPoint(x * 60,y * 60), CPoint(x_pe, y_pe) };
				CRect Pac(x * 60 - 30, y * 60 - 30, x * 60 + 30, y * 60 + 30);
				pDC.SelectObject(PY);
				pDC.Arc(&Pac, PacS, PacE);
				pDC.Polyline(Mouth, 3);

				
			}
			else if (t2 < 1300) {}
			else { exit(0); }
		}
	

		if (END == true)
		{
			
			big=big+5;
			CRect backdrop(0, 0, rect.Width(), rect.Height());
			pDC.SelectObject(BD);
			pDC.Rectangle(&backdrop);//绘制矩形
			t2 = 30;
			if (FX == "r") { x_pe = x * 60 + big * cos(((double)t2 / 180)); y_pe = y * 60 + big * sin(((double)t2 / 180)); x_ps = x * 60 + big * cos(((double)t2 / 180)); y_ps = y * 60 - big * sin(((double)t2 / 180)); }
			else if (FX == "l") { x_ps = x * 60 - big * cos(((double)t2 / 180)); y_ps = y * 60 + big * sin(((double)t2 / 180)); x_pe = x * 60 - big * cos(((double)t2 / 180)); y_pe = y * 60 - big * sin(((double)t2 / 180)); }
			else if (FX == "u") { x_pe = x * 60 + big * sin(((double)(565 - t2) / 180)); y_pe = y * 60 + big * cos(((double)(565 - t2) / 180)); x_ps = x * 60 - big * sin(((double)(565 - t2) / 180)); y_ps = y * 60 + big * cos(((double)(565 - t2) / 180)); }
			else if (FX == "d") { x_ps = x * 60 + big * sin(((double)(565 - t2) / 180)); y_ps = y * 60 - big * cos(((double)(565 - t2) / 180)); x_pe = x * 60 - big * sin(((double)(565 - t2) / 180)); y_pe = y * 60 - big * cos(((double)(565 - t2) / 180)); }

			CPoint PacS(x_ps, y_ps);
			CPoint PacE(x_pe, y_pe);
			CPoint Mouth[3] = { CPoint(x_ps, y_ps) ,CPoint(x * 60,y * 60), CPoint(x_pe, y_pe) };
			CRect Pac(x * 60 - big, y * 60 - big, x * 60 + big, y * 60 + big);
			pDC.SelectObject(PY);
			pDC.Arc(&Pac, PacS, PacE);
			pDC.Polyline(Mouth, 3);
			if (bgme == 1) { sndPlaySound("win.wav", SND_ASYNC); bgme = 0; }
			if (big > 1800) { exit(0); }
		}








		click = false;


}

