


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



CPen PY(PS_SOLID, 5, RGB(255, 255, 0));//��ɫ�ʣ��Զ��ˣ�
CPen PW(PS_SOLID, 2, RGB(255, 255, 255));//�ױʣ����ӣ�
CPen PP(PS_SOLID, 5, RGB(242, 156, 177));//��ɫ�ʣ��������
CPen PB(PS_SOLID, 5, RGB(102, 204, 255));//��ɫ�ʣ���ʳ�ù��
CPen PL(PS_SOLID, 10, RGB(0, 0, 255));//��ɫ�ֱʣ�ǽ�ڣ�
CPen PD(PS_SOLID, 2, RGB(0, 0, 0));//��ɫ�ʣ�ɾ����

CBrush BD(RGB(0, 0, 0));//��ɫˢ��������
CBrush BW(RGB(255, 255, 255));//��ɫˢ�����ӣ�

int x = 2; int y = 10;//pacλ��
int ox = 0, oy = 0;//�ɵ�pacλ��
double x_ps, y_ps, x_pe, y_pe;//pac��ͼ�ú���
double x_ms, y_ms, x_me, y_me;//���ﻭͼ�ú���
int score = 0;//����
int s_t = 0;//���������ʱ��
bool dead = false;//�Ƿ�����
bool END = false;//�Ƿ����
bool strong = false;//����ģʽ
bool restart = true;//��ʼ��
bool KT = true;//��ͷ
bool pause = false;//��ͣ
int pa = 0;//��ͣ
int gnum = 4;//��������
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
};//�߶���ʾ��
  //string FX = "l";string ofx = "l";
int t1=0;//��ͷ������ʱ��
int t2=-500;//����������ʱ��
int SPEED = 10;//��Ϸ�ٶ�
int  deadspeed = 1;
int fps=0;//����֡�����Ǹ����涫��
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

