#ifndef COCKROACH_H
#define COCKROACH_H

class CCockRoach
{
	int curX;
	int curY;

public:
	CCockRoach(int x = 0, int y = 0)
	{
		curX = x;
		curY = y;
	}
	void setPos(int x, int y) { curX = x; curY = y; };

	void tigerup(CDC *dc);

	void CCockRoach::pause1(CDC *dc);
	void CCockRoach::pause0(CDC *dc);
	void CCockRoach::KT1(CDC *dc);
	void CCockRoach::logo6(CDC *d);
	void CCockRoach::logo5(CDC *dc);
	void CCockRoach::logo4(CDC *dc);
	void CCockRoach::logo3(CDC *dc);
	void CCockRoach::logo2(CDC *dc);
	void CCockRoach::logo1(CDC *dc);
	void CCockRoach::logo0(CDC *dc);
	void CCockRoach::menu(CDC *dc);
	void tri(CDC * dc);
	void r(CDC * dc);
};

#endif
