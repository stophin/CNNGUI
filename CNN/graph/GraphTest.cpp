//GraphTest.cpp
//
#include "GraphTest.h"

void bkground(HWND hWnd,Timer& t,const Ball& ball)
{	
	LINESTYLE linestyle;
	getlinestyle(&linestyle);
	COLORREF oldcolor=getcolor();

	t.UpdateFPS();
	char text[30];
	sprintf(text,"Grpah FPS: %3.0f fps",t.GetFPS());
	SetWindowText(hWnd,text);

	setlinestyle(0,10);
	setcolor(BLACK);
	rectangle(ball.getLimitLtX(),ball.getLimitLtY(),ball.getLimitRbX(),ball.getLimitRbY());

	setlinestyle(&linestyle);
	setcolor(oldcolor);
}

#include "../NN/Network.h"
extern Network * g_nets;
class LocalNet {
public:
	LocalNet() {
		nets = NULL;
		nets = NULL;
		trainStatus = NULL;
		trainRun = NULL;
	}
	Network * nets;

	int *trainStatus;
	int *trainRun;
} NET;
int initgraph_Waiting() {
	//wait for neural network initialize
	while (true)
	{
		//chnage this using Network/Net
		if (g_nets == NULL) {
			Sleep(1000);
			continue;
		}
		else {
			break;
		}
	}
	if (g_nets) {
		NET.nets = g_nets;
		NET.trainRun = &g_nets->trainRun;
		NET.trainStatus = &g_nets->trainStatus;
	}
	return 0;
}
int initgraph()
{
	Timer t;
	MyTimer mmt;

//	Graph G(50,true,false,false,10);
//	Graph G("顶点数13-拓扑排序.txt");
//	G+=Vertex(21);	
	Graph G;
	BallSet ball;
	
	GUIFrame mygui(SCRWD,SCRHT);
	mygui.bkcolor=BKCOLOR;

	GUIEditbox e1(1110,10,180,540);
//	e1.bkcolor=BLUE;
//	e1.fontcolor=RED;
	e1.content=G.lastErr;
	e1.uniname="e1";
	mygui.AddObject(e1);

	GUIButton bclear(1110,555, 180,30);
	bclear.caption="清除信息";
	bclear.uniname="bclear";
	bclear.isactive=true;
	mygui.AddObject(bclear);

	BeginBatchDraw();	
	bool run=true;
	t.InitTime();
	int drag=-1;
	char c[100];
	initgraph_Waiting();
	//build balls
	if (NET.nets) {
		G.Load(NET.nets);
		ball.Load(G.V);
		ball.getBallPos(G);
		NET.nets->trainRun = 1;//中断模式
	}
	while (run)
	{
		bkground(mygui.hWnd,t,ball[0]);
		
		if (mygui.hWnd==GetForegroundWindow())
		{
			POINT point;
			//获取鼠标信息
			GetCursorPos(&point);			// 获取鼠标指针位置（屏幕坐标）
			ScreenToClient(mygui.hWnd, &point);	// 将鼠标指针位置转换为窗口坐标
			Point pt(point.x,point.y);
			static Point p(pt);
			static Point s;
			static bool selecting=false;
			static bool moving=false;
			int d=ball.isin(pt);
			if (GetAsyncKeyState(VK_LBUTTON)&0x8000)
			{
				if (drag==-2)
				{
					if (!moving)
					{
						s=pt;
						moving=true;
					}
					for (int i=0;i<ball.num;i++)
					{
						if (ball[i].active)
						{
							Point g((PHXTYPE)G[i].v.pos.x,(PHXTYPE)G[i].v.pos.y);
							ball[i].setPos(g+pt-s);
							ball.conjunctionBall();
						}
					}
				}
				else if (!selecting&&drag!=-1)
				{
					if (ball.isinlimit(pt))
					{
						if (d != -1)
						{
							drag = d;
						}

						ball.clearactive();
						ball[drag].active = true;
						ball[drag].setPos(pt.getX(), pt.getY());
						ball.conjunctionBall();
}
					}
					else if (drag == -1)
					{
					if (!selecting)
					{
						if (d != -1)
						{
							drag = d;
						}
						else if (ball.isinlimit(pt))
						{
							selecting = true;
							p.set(pt.getX(), pt.getY());
						}
					}
					else
					{
						if (ball.isinlimit(pt))
						{
							s = pt;
						}
						rectangle(p.getX(), p.getY(), s.getX(), s.getY());
					}
				}
			}
			else
			{
			if (selecting)
			{
				int num = 0;
				for (int i = 0; i < ball.num; i++)
				{
					if (ball[i].isin(p, s))
					{
						num++;
						ball[i].active = true;
					}
				}
				if (num)
				{
					drag = -2;
				}
				else
				{
					drag = -1;
				}
				selecting = false;
			}
			if (drag == -2)
			{
				for (int i = 0; i < ball.num; i++)
				{
					if (ball[i].active)
					{
						G[i].v.pos.x = ball[i].getPosX();
						G[i].v.pos.y = ball[i].getPosY();
					}
				}
				moving = false;
			}
			}
			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
			{
				ball.clearactive();
				drag = -1;
			}
		}

		ball.lineGraph(G);
		ball.drawBall(G);
		mygui.Update();
		mygui.Redraw();

		if (((GUIButton*)mygui.GetObject("bclear"))->LBPressed())
		{
			((GUIEditbox*)mygui.GetObject("e1"))->content = "";
		}

		if (!(*NET.trainStatus && (*NET.trainRun == 0 || *NET.trainStatus == *NET.trainRun))) {
			if (NET.nets) {
				G.Update(NET.nets);
			}
		}
		if (_kbhit()) {
			char t = getch();
			if (t == 'c') {
				if (*NET.trainStatus) {
					sprintf(c, "c:%d ", *NET.trainStatus);
					((GUIEditbox*)mygui.GetObject("e1"))->content += c;
					*NET.trainRun = *NET.trainStatus;
					*NET.trainStatus = 0;
				}
			}
			else if (t == 'r') {
				sprintf(c, "r:%d ", *NET.trainRun);
				((GUIEditbox*)mygui.GetObject("e1"))->content += c;
				if (*NET.trainRun == 0) {
					*NET.trainRun = -1;
				}
				else {
					*NET.trainRun = -*NET.trainRun;
				}

			}
			else {
				if (*NET.trainStatus) {
					sprintf(c, "b:%d ", *NET.trainStatus);
					((GUIEditbox*)mygui.GetObject("e1"))->content += c;
					*NET.trainStatus = 0;
					*NET.trainRun = 0;
				}
			}
			if (NET.nets) {
				G.Update(NET.nets);
			}
		}

		FlushBatchDraw();
		mmt.msSleep(20);
		cleardevice();

	}
	EndBatchDraw();
	closegraph();
	return 0;
}