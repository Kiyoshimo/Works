
#ifndef IMAGEDATA_H
#define IMAGEDATA_H
#include "resource1.h"

#define EASTNORTH_WIDTH 41
#define EASTNORTH_HEIGHT 51
#define EASTSOUTH_WIDTH 51
#define EASTSOUTH_HEIGHT 41
#define WESTNORTH_WIDTH 51
#define WESTNORTH_HEIGHT 41
#define WESTSOUTH_WIDTH 41
#define WESTSOUTH_HEIGHT 51

#define BIG_COCKROACH_WIDTH 1800
#define BIG_COCKROACH_HEIGHT 900

class CImageData {
public:
	CBitmap ck_EastNorth, ck_EastSouth, ck_WestNorth, ck_WestSouth, ck_BG;
	CImageData (){};
	void Initialize (){
		
	};
};

#endif