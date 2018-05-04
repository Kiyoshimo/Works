#include <afxwin.h>
#include "CockRoach.h"
#include "resource1.h"
#include "GlobalInfo.h"
#include <cstring>
#include<iostream>

#define lx 1010
#define lx 220

void DrawTransparentBitmap(CDC *pDC, UINT IDImage,CRect &rect, COLORREF rgbMask) 
{ 
	CDC ImageDC,MaskDC;

	CBitmap Image,*pOldImage; 
	CBitmap maskBitmap,*pOldMaskDCBitmap ;

	Image.LoadBitmap(IDImage); 
	ImageDC.CreateCompatibleDC(pDC); 
	pOldImage=ImageDC.SelectObject(&Image);

	MaskDC.CreateCompatibleDC(pDC); 
	maskBitmap.CreateBitmap( rect.Width(), rect.Height(), 1, 1, NULL ); 
	pOldMaskDCBitmap = MaskDC.SelectObject( &maskBitmap );

	ImageDC.SetBkColor(rgbMask); 
	MaskDC.BitBlt( 0, 0, rect.Width(), rect.Height(), &ImageDC, 0, 0, SRCCOPY );

	ImageDC.SetBkColor(RGB(0,0,0)); 
	ImageDC.SetTextColor(RGB(255,255,255)); 
	ImageDC.BitBlt(0, 0, rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND);

	pDC->BitBlt(rect.left,rect.top,rect.Width(), rect.Height(), &MaskDC, 0, 0, SRCAND); 
	pDC->BitBlt(rect.left,rect.top,rect.Width(), rect.Height(), &ImageDC, 0, 0,SRCPAINT);

	MaskDC.SelectObject(pOldMaskDCBitmap); 
	ImageDC.SelectObject(pOldImage); 
}




void CCockRoach::tigerup(CDC *dc) {
	UINT PictureID = 0;
	CRect Field;
		PictureID = IDB_BITMAP3;
		Field.left = curX; Field.right = curX +44; Field.top = curY; Field.bottom = curY +100;
		DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}

void CCockRoach::pause1(CDC *dc) {
	UINT PictureID = IDB_BITMAP3;
	CRect Field;
	Field.left = 0; Field.right = 180; Field.top = 0; Field.bottom = 60;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}
void CCockRoach::pause0(CDC *dc) {
	UINT PictureID = IDB_BITMAP4;
	CRect Field;

	Field.left = 0; Field.right = 180; Field.top = 0; Field.bottom = 60;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}

void CCockRoach::KT1(CDC *dc) {
	UINT PictureID = IDB_BITMAP1;
	CRect Field;

	Field.left = 0; Field.right = 1800; Field.top = 0; Field.bottom = 900;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}

void CCockRoach::logo0(CDC *dc) {
	UINT PictureID;
    { PictureID = IDB_BITMAP11; }
	CRect Field;
	Field.left = curX; Field.right = curX + 1010; Field.top = curY; Field.bottom = curY + 220;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}
void CCockRoach::logo1(CDC *dc) {
	UINT PictureID;
	 { PictureID = IDB_BITMAP10; }
	CRect Field;
	Field.left = curX; Field.right = curX + 1010; Field.top = curY; Field.bottom = curY + 220;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}
void CCockRoach::logo2(CDC *dc) {
	UINT PictureID;
	 { PictureID = IDB_BITMAP9; }
	CRect Field;
	Field.left = curX; Field.right = curX + 1010; Field.top = curY; Field.bottom = curY + 220;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}
void CCockRoach::logo3(CDC *dc) {
	UINT PictureID;
	{ PictureID = IDB_BITMAP8; }
	CRect Field;
	Field.left = curX; Field.right = curX + 1010; Field.top = curY; Field.bottom = curY + 220;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}
void CCockRoach::logo4(CDC *dc) {
	UINT PictureID;
	 { PictureID = IDB_BITMAP7; }
	CRect Field;
	Field.left = curX; Field.right = curX + 1010; Field.top = curY; Field.bottom = curY + 220;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}
void CCockRoach::logo5(CDC *dc) {
	UINT PictureID;
	 { PictureID = IDB_BITMAP6; }
	CRect Field;
	Field.left = curX; Field.right = curX + 1010; Field.top = curY; Field.bottom = curY + 220;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}
void CCockRoach::logo6(CDC *dc) {
	UINT PictureID;
	 { PictureID = IDB_BITMAP5; }
	CRect Field;
	Field.left = curX; Field.right = curX + 1010; Field.top = curY; Field.bottom = curY + 220;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}

void CCockRoach::menu(CDC *dc) {
	UINT PictureID = IDB_BITMAP12;
	CRect Field;
	Field.left = 900 -120; Field.right =900 +120; Field.top = 600 -88; Field.bottom = 600+89;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}
void CCockRoach::tri(CDC *dc) {
	UINT PictureID = IDB_BITMAP13;
	CRect Field;
	Field.left = curX-15; Field.right = curX +15; Field.top = curY-15; Field.bottom = curY + 15;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}
void CCockRoach::r(CDC *dc) {
	UINT PictureID = IDB_BITMAP14;
	CRect Field;

	Field.left = 0; Field.right = 1800; Field.top = 0; Field.bottom = 900;
	DrawTransparentBitmap(dc, PictureID, Field, RGB(255, 255, 255));
}