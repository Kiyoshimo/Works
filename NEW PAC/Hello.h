


class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd
{
	BOOL m_bTracking;
public:
	CMainWindow();
	
	afx_msg void OnKeyDown(UINT nchar, UINT nRepCnt, UINT nFlags);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nTimerID);
	afx_msg void OnClose();


	DECLARE_MESSAGE_MAP()
};

#define HEADSIZE 30
#define BODYHEIGHT 60
#define FULLLIMB 60
#define HALFLIMB 30
#define MAXMOTION 2


class CPerson {
	CDC *dc;
	int start_x, start_y;
	int prev_x, prev_y;
	int prev_motion;
	int motion;
public:
	CPerson() : start_x(0), start_y(0), prev_motion(0), motion(0) {};
	void setPos(int x, int y) { prev_x = start_x; start_x = x; prev_y = start_y; start_y = y; };
	void setDC(CDC *in_dc) { dc = in_dc; };
	void draw(int type, bool clear = 0, COLORREF curColor = RGB(0, 0, 0));
	void changemotion(int next_motion);
	int getmotion() { return motion; };
	void nextmotion() { if ((++motion) == MAXMOTION) motion = 0; }
};



CPen PY(PS_SOLID, 5, RGB(255, 255, 0));//黄色笔（吃豆人）
CPen PW(PS_SOLID, 2, RGB(255, 255, 255));//白笔（豆子）
CPen PP(PS_SOLID, 5, RGB(242, 156, 177));//粉色笔（攻击怪物）
CPen PB(PS_SOLID, 5, RGB(102, 204, 255));//蓝色笔（可食用怪物）
CPen PL(PS_SOLID, 10, RGB(0, 0, 255));//蓝色粗笔（墙壁）
CPen PD(PS_SOLID, 2, RGB(0, 0, 0));//黑色笔（删除）

CBrush BD(RGB(0, 0, 0));//黑色刷（背景）
CBrush BW(RGB(255, 255, 255));//白色刷（豆子）

int x = 2; int y = 10;//pac位置
int ox = 0, oy = 0;//旧的pac位置
double x_ps, y_ps, x_pe, y_pe;//pac画图用函数
double x_ms, y_ms, x_me, y_me;//怪物画图用函数
int score = 0;//分数
int s_t = 0;//大力丸持续时间
bool dead = false;//是否死亡
bool END = false;//是否结束
bool strong = false;//大力模式
bool restart = true;//初始化
bool KT = true;//开头
bool pause = false;//暂停
int pa = 0;//暂停
int gnum = 4;//怪物数字
const int seg[10][7] = {
	{ 1, 1, 1, 1, 1, 1, 0 }, /* 0 */
	{ 0, 1, 1, 0, 0, 0, 0 }, /* 1 */
	{ 1, 1, 0, 1, 1, 0, 1 }, /* 2 */
	{ 1, 1, 1, 1, 0, 0, 1 }, /* 3 */
	{ 0, 1, 1, 0, 0, 1, 1 }, /* 4 */
	{ 1, 0, 1, 1, 0, 1, 1 }, /* 5 */
	{ 1, 0, 1, 1, 1, 1, 1 }, /* 6 */
	{ 1, 1, 1, 0, 0, 0, 0 }, /* 7 */
	{ 1, 1, 1, 1, 1, 1, 1 }, /* 8 */
	{ 1, 1, 1, 1, 0, 1, 1 }  /* 9 */
};//七段显示器
  //string FX = "l";string ofx = "l";
int t1=0;//开头动画计时器
int t2=-500;//死亡动画计时器
int SPEED = 10;//游戏速度
int  deadspeed = 1;
int fps=0;//控制帧数的那个神奇东西
int xx = -100;
int yy = 440;
int gxx = -200;
int gyy = 440;
int sel;
bool click = false;
bool rule;
int startime=60;
int bgm1 = 1;
int bgm2 = 1;
int bgms = 0;
int bgmd = 1;
int big = 30;
int bgme = 1;

