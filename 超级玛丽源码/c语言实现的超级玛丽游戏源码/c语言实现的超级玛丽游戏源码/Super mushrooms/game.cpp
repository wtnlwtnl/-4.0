//EasyX是针对C++的图形库，可以帮助C/C++初学者快速上手图形和游戏编程。
//  比如,可以基于EasyX图形库很快用几何图形画一个房子，或者一辆移动的小车，可以编写俄罗斯方块 、贪吃蛇、黑白棋等小游戏。
#include <graphics.h>
//这个头文件通常用于在 C/C++ 中进行简单的图形编程
//它提供了一些基本的图形绘制函数，如画线、画圆、填充颜色等，以及控制图形窗口的函数，如创建窗口、关闭窗口等
#include <conio.h>
//这个头文件提供了一些用于在控制台中进行输入输出的函数，主要是针对字符的输入输出操作。
//其中包括了一些用于控制光标位置、设置文本颜色、从控制台中读取字符等函数。
#include<math.h>
//这是 C/C++ 标准库中的数学函数头文件，提供了各种数学函数的声明和定义。
//它包含了一系列常用的数学函数，如三角函数、对数函数、指数函数、幂函数等。
//math.h 中的函数可以用于各种数学计算和科学计算，如数值分析、物理学、工程学等领域的计算。
#include "MyTimer.h"               //一个保证精确延时的类。下载于easyx官网
#pragma comment(lib,"Winmm.lib")   //给游戏添加音乐要用到它

#define G 9.8                      //重力加速度
#define XSIZE 512                  //屏幕大小
#define YSIZE 384
#define X 64                       //主角起始位置
#define Y 192
#define W 32                       //主角的宽和高
#define H 32
#define STEP 4                     //主角走一步相距的像素个数
#define HIGH (2*role.w+1)          //主角跳跃的最大高度
 
#define	CMD_LEFT 1                 //方向键的宏定义
#define	CMD_RIGHT 2	
#define	CMD_UP 4
#define CMD_DOWN 8
#define CMD_SHOOT 16
#define CMD_ESC 32
int life;                          //全局变量，主角共有多少条生命
int score;                         //全局变量，主角获得的分数
struct ROLE
{
	int id;
    int x;//横坐标
    int y;//纵坐标
    int w;//图片宽度
    int h;//图片高度
    int xleft;//水平运动的左界限 
    int xright;//水平运动的右界限
    int turn;//精灵的运动方向
    int jump;//精灵是否跳跃
    int iframe;//加载第几副精灵图，这样就能让精灵看上去动起来了
};
struct MAP        //储存地图的结构体
{
	int id;
	int x;
	int y;
};
struct BULLET      //子弹的结构体
{
	int x;
	int y;
	int turn;
	int iframe;
	int id;
};
struct COINT      //硬币的结构体
{
	int x;
	int y;
	double iframe;
};
struct ENEMY      //敌人的结构体
{
	int id;
	int x;
	int y;
	int turn;
	int iframe;
};
class game        //整个游戏只设置了这一个类
{
private:
	ROLE role;
	MAP map[350];
	BULLET bullet[20];
	COINT coint[50];
	ENEMY enemy[20];
	IMAGE img_mapsky,img_p,img_map,img_ani,img_mapbk,img_home;
	int xmapsky;           //背景天空的起始横坐标
	int xmap;              //地图的起始坐标
	double v0;             //精灵跳跃的初速度             
	double h;              //精灵跳跃的高度
	double t;              //精灵跳跃的时间
	int ibullet;           //第几颗子弹
	int xbullet;           //子弹的x坐标
	int ybullet;           //子弹的y坐标
	int get_bullet;        //是否获得武器，0表示没有获得，1表示已获得
	POINT icoint;          //储存硬币的坐标
	POINT bomb[20];        //储存哪些地方爆炸了的坐标
	POINT temp;            //临时坐标。储存哪些地方爆炸了的坐标
	double score_frame;    //下面3个double型的变量用于控制各自图片的帧，以实现动画的效果。如画面中的流水
	double bomb_frame;
	double mapbk_frame;
	int win;               //玩家是否过关
	int pause;             //玩家是否按Esc（暂停键）
public:
	game();
	~game();
	void start();          //处理游戏开始的界面，和按暂停键后的界面
	void init();           //初始化各项变量
	void move();           //控制主角移动
	void show();           //显示画面
	int isdie();           //判断主角是否已死
	int  GetCommand();	   // 获取控制命令。
	void left();           //主角向左运动
	void right();          //主角向右运动
	void up();             //主角跳跃
	void init_shoot();     //初始化发射子弹
	void fall();	       //主角自由落体或者向上跳跃
	int is_l_touch(int id);//主角的左边是否碰到墙或敌人，以及敌人是否碰到陆地的左边界
	int is_r_touch(int id);//主角的右边是否碰到墙或敌人，以及敌人是否碰到陆地的右边界
	int is_t_touch();      //主角的头是否碰到墙
	int is_b_touch(int id);//主角是否踩到敌人。
	int is_touch();        //主角是否吃到金币
	int is_land(ENEMY e);  //敌人是否站在陆地上
	void getbullet();      //获取子弹
	void shoot();          //发射子弹
	int eat(BULLET b);     //子弹是否打到敌人或者墙壁
	void end();            //处理游戏结束
};
game::game()
{
	initgraph(XSIZE,YSIZE);//XSIZE,YSIZE为前面宏定义得到的数据
}
//构造函数 game::game() 在对象被创建时调用
// 它的作用是初始化游戏的图形窗口
// 通过 initgraph(XSIZE, YSIZE) 创建一个指定大小的图形窗口，用于显示游戏画面
game::~game()
{
	closegraph();
}
//析构函数 game::~game() 在对象被销毁时调用，它的作用是关闭游戏的图形窗口
// 通过 closegraph() 关闭游戏的图形环境，释放相关资源，确保游戏结束时资源能够被正确释放。
void game::start()
{
	if(pause==1)//如果按了暂停键
	{
		BeginBatchDraw(); //开始批量绘制，以提高绘制效率
		int points[8]={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3,XSIZE/2+45,YSIZE/3+90,XSIZE/2-45,YSIZE/3+90};
		setfillstyle(GREEN);//定义一个包含菜单框架四个顶点坐标的数组
		fillpoly(4, points);//使用指定的顶点坐标数组绘制一个填充的四边形，即暂停菜单的背景框
		setbkmode(TRANSPARENT);//设置文本背景模式为透明，这样绘制的文字背景就会透明，不会覆盖背景框。
		setfont(20,0,"黑体"); //设置字体大小为 20，字体样式为正常，字体类型为黑体
    	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);
    	drawtext("回到游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//定义一个矩形 r2，用于包裹“回到游戏”文字，并绘制一个矩形框。
    	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);
        drawtext("重新开始", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//定义一个矩形 r3，用于包裹“重新开始”文字，并绘制一个矩形框。
	    RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);
    	drawtext(" 主 菜 单 ", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//定义一个矩形 r4，用于包裹“主菜单”文字，并绘制一个矩形框。
		FlushBatchDraw();
		//刷新批量绘制的结果，将绘制的图形和文字显示在屏幕上
	    MOUSEMSG m;//定义一个 MOUSEMSG 结构体变量 m，用于接收鼠标消息。
    	while(true)// 进入一个无限循环，不断监听鼠标事件
    	{
			BeginBatchDraw();//开始批量绘制，以提高绘制效率
    		m=GetMouseMsg();//获取鼠标消息
    		switch(m.uMsg)//根据鼠标消息类型进行分支处理
            {
			case WM_LBUTTONDOWN://当鼠标左键被按下时执行以下操作。
				EndBatchDraw();//结束批量绘制，绘制的图形和文字显示在屏幕上
				if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30)
    	     	    return;//如果鼠标点击位置在“回到游戏”按钮范围内，函数返回。
    			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60)
    			{
					mciSendString("close all", NULL, 0, NULL);	
    				pause=0;
					score=0;
    				return;
     			}//如果鼠标点击位置在“重新开始”按钮范围内，执行关闭所有音频、取消暂停、重置得分，然后返回。
    			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90)
				{
					mciSendString("close all", NULL, 0, NULL);	
					pause=0;
					score=0;
					life=0;
					cleardevice();
    				break;
				}
				//如果鼠标点击位置在“主菜单”按钮范围内
				// 执行关闭所有音频、取消暂停、重置得分、生命为0，清除屏幕内容，然后跳出循环。
    			else
    				break;
				//如果鼠标点击位置不在任何按钮范围内，跳出 switch 分支，然后继续下一次循环。
			case WM_MOUSEMOVE://当鼠标移动时执行以下操作
				RECT r;//定义一个矩形结构体变量 r，用于表示按钮的区域
				int i; //定义一个整型变量 i，用于循环控制
				for(i=0;i<3;i++)//循环遍历三个按钮
				{
				    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+i*30&&m.y<YSIZE/3+30+i*30)
				    {
					    r.left=XSIZE/2-45;
					    r.top=YSIZE/3+i*30;
					    r.right=XSIZE/2+45;
					    r.bottom=YSIZE/3+30+i*30;
						int points[8]={r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom};
						//循环遍历三个按钮
					    setfillstyle(RED);
						//使用 setfillstyle() 设置填充颜色为红色
						fillpoly(4, points);
						//使用 fillpoly() 函数绘制一个四边形，四个顶点坐标由数组 points 提供
						setbkmode(TRANSPARENT);
						//使用 setbkmode() 函数将文本背景模式设置为透明，以便文本可以在不受背景色影响的情况下显示
						switch(i)//根据变量 i 的值进行不同的操作
						{
						case 0:
						    drawtext("回到游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						    break;
							//使用 drawtext() 函数在矩形 r 的中心绘制文本 "回到游戏"，文本水平和垂直居中，单行显示。
						case 1:
						    drawtext("重新开始", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//使用 drawtext() 函数在矩形 r 的中心绘制文本 "重新开始"，文本水平和垂直居中，单行显示。
						case 2:
						    drawtext(" 主 菜 单 ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//使用 drawtext() 函数在矩形 r 的中心绘制文本 " 主 菜 单 "，文本水平和垂直居中，单行显示。
						}
					}
				    else
				    {
						if(getpixel(XSIZE/2-45+1,YSIZE/3+i*30+1)==RED)
						//检查按钮区域内的像素颜色是否为红色。 getpixel函数用于获取指定位置的像素颜色
						//(XSIZE/2-45+1,YSIZE/3+i*30+1) 是按钮区域内的一个点，通过向右和向下移动一个像素，以确保检查的点在按钮内部。
						{
				       	    r.left=XSIZE/2-45;
				            r.top=YSIZE/3+i*30;
				       	    r.right=XSIZE/2+45;
				       	    r.bottom=YSIZE/3+30+i*30;
				       		int points[8]={r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom};
			   		        setfillstyle(GREEN);
			       			fillpoly(4, points);
			       			setbkmode(TRANSPARENT);
			        		switch(i)
						    {
				    		case 0:
				    		    drawtext("回到游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 1:
				    			drawtext("重新开始", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 2:
				    			drawtext(" 主 菜 单 ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
							}
							//设置矩形 r 的位置。
							//使用 setfillstyle() 设置填充颜色为绿色。
							//fillpoly() 函数绘制绿色按钮。
							//使用 setbkmode() 函数将文本背景模式设置为透明。
							//根据按钮的索引选择不同的文本内容，使用 drawtext() 函数重新绘制按钮上的文本。
						}
						FlushBatchDraw();//刷新绘制结果，将变化后的按钮显示在屏幕上
					}
				}
			}
			if(pause==0)
				break;
			//if(pause==0) break;：如果游戏暂停状态为 0（未暂停），则跳出循环
		}
	}
	if(life==1||life==2)
		return;
	life=3;
	score=0;
	setfont(40,0,"方正舒体");	// 设置字体大小为40，字体样式为“方正舒体”
	RECT r1 = {0, 0, XSIZE, YSIZE/3};//定义一个矩形结构体变量 r1，用于显示标题区域
	drawtext("超级蘑菇", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE); //在标题区域中心绘制文本“超级蘑菇”。
	setfont(20,0,"宋体");//设置字体大小为20，字体样式为“宋体”
	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);
	drawtext("开始游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);
    drawtext("游戏介绍", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);
	drawtext("操作说明", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5={XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120};rectangle(XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120);
	drawtext("退出游戏", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//定义并绘制四个按钮及其文本：
	//  开始游戏按钮
	//	游戏介绍按钮
	//	操作说明按钮
	//	退出游戏按钮
	int flag1=1,flag2=0,flag3=0;
	//定义并初始化标志变量 flag1=1,flag2=0,flag3=0，用于控制界面的状态
	MOUSEMSG m;
	while(flag1==1)//进入循环，监听鼠标消息
	{
		BeginBatchDraw();
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:// 如果是鼠标左键点击事件
			EndBatchDraw();//根据鼠标点击位置和按钮状态执行相应的操作：
		    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30&&flag1==1&&flag2==0&&flag3==0)
		    {
				flag1=0;
				break;
			}//如果点击的是开始游戏按钮，则进入游戏
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60&&flag1==1&&flag3==0)
			{
			    flag2=1;
				cleardevice();
				rectangle(50,50,213,220);
				outtextxy(52,52,"游戏介绍：");
				outtextxy(52,82,"超级玛丽变");
				outtextxy(52,102,"身超级蘑菇");
				outtextxy(52,132,"开发者：");
				outtextxy(52,152,"czxczx");
				RECT R1={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);
	            drawtext("返回", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}//如果点击的是游戏介绍按钮，则显示游戏介绍
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90&&flag1==1&&flag2==0)
			{
				flag3=1;
				cleardevice();
				rectangle(50,50,213,220);
				outtextxy(52,52,"操作说明：");
				outtextxy(52,72,"左移：A键");
				outtextxy(52,92,"右移：D键");
				outtextxy(52,112,"发射：J键");
				outtextxy(52,132,"跳跃：W键/K键");
				outtextxy(52,152,"暂停：Esc键");
				RECT R2={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);
	            drawtext("返回", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;//如果点击的是操作说明按钮，则显示游戏操作说明
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+90&&m.y<YSIZE/3+120&&flag1==1&&flag2==0&&flag3==0)
			    exit(0);
			else if(m.x>XSIZE-46&&m.x<XSIZE-3&&m.y>YSIZE-26&&m.y<YSIZE-3&&(flag2==1||flag3==1))
			{
			    cleardevice();
				flag1=0,flag2=0,flag3=0;
				start();
			}
			else
			    break;//如果点击的是退出游戏按钮，则退出游戏
		case WM_MOUSEMOVE://如果是鼠标移动事件，根据鼠标移动位置和按钮状态改变按钮的颜色以及显示状态
			RECT r;//定义矩形结构体变量 r 用于表示按钮的区域
			if(flag2==1||flag3==1)//检查当前界面的状态，如果处于游戏介绍或操作说明状态，则处理返回按钮的颜色和显示状态
			{
			    if(m.x>XSIZE-46&&m.x<XSIZE-3&&m.y>YSIZE-26&&m.y<YSIZE-3)
				{
				    r.left=XSIZE-46;
				    r.top=YSIZE-26;
			        r.right=XSIZE-2;
					r.bottom=YSIZE-2;
					int points[8]={r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom};
				    setfillstyle(RED);
					fillpoly(4, points);
					setbkmode(TRANSPARENT);
					drawtext("返回", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}//如果鼠标位于返回按钮的区域内，将按钮填充为红色，显示文本“返回”
				else
				{
					if(getpixel(XSIZE-46+1,YSIZE-26+1)==RED)
					{
					    r.left=XSIZE-46;
			         	r.top=YSIZE-26;
			            r.right=XSIZE-2;
			        	r.bottom=YSIZE-2;
						int points[8]={r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom};
						setfillstyle(BLACK);
					    fillpoly(4, points);
					    setbkmode(TRANSPARENT);
					    drawtext("返回", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}//否则，如果返回按钮之前已经被绘制为红色，将其填充为黑色，以清除红色背景，然后显示文本“返回”
			}
			else//如果不处于游戏介绍或操作说明状态，则处理开始游戏、游戏介绍、操作说明和退出游戏按钮的颜色和显示状态。
			{
			    for(int i=0;i<4;i++)
				{
					//对于每个按钮，如果鼠标位于按钮的区域内，将按钮填充为红色，显示相应的文本。
				    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+i*30&&m.y<YSIZE/3+30+i*30)
				    {
					    r.left=XSIZE/2-45;
					    r.top=YSIZE/3+i*30;
					    r.right=XSIZE/2+45;
					    r.bottom=YSIZE/3+30+i*30;
						int points[8]={r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom};
					    setfillstyle(RED);
						fillpoly(4, points);
						setbkmode(TRANSPARENT);
						switch(i)
						{
						case 0:
						    drawtext("开始游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						    break;
						case 1:
						    drawtext("游戏介绍", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
						    drawtext("操作说明", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
					   	case 3:
							drawtext("退出游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					//否则，如果按钮之前已经被绘制为红色，将其填充为黑色，以清除红色背景，然后显示相应的文本
				    else
				    {
						if(getpixel(XSIZE/2-45+1,YSIZE/3+i*30+1)==RED)
						{
				       	    r.left=XSIZE/2-45;
				            r.top=YSIZE/3+i*30;
				       	    r.right=XSIZE/2+45;
				       	    r.bottom=YSIZE/3+30+i*30;
				       		int points[8]={r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom};
			   		        setfillstyle(BLACK);
			       			fillpoly(4, points);
			       			setbkmode(TRANSPARENT);
			        		switch(i)
						    {
				    		case 0:
				    		    drawtext("开始游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 1:
				    			drawtext("游戏介绍", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 2:
				    			drawtext("操作说明", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    	   	case 3:
				    			drawtext("退出游戏", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
							}
						}
					}
				}
			}
			FlushBatchDraw(); //刷新绘图结果，将按钮的变化显示在屏幕上
			break;
			default:
			    break;
		 }
	}
}
void game::init()
{
	if(pause==1)
		return;
	//首先检查 pause 是否为 1，如果是，则表示游戏处于暂停状态，函数直接返回。

	role.id=1;
	role.x=X;
	role.y=Y;
	role.w=W;
	role.h=H;
	role.xleft=0;
	role.xright=role.w*6+STEP;
	role.iframe=1;
	role.turn=1;
	role.jump=0;
	//接下来设置游戏角色的初始属性，包括角色的位置 (x, y)、大小 (w, h)，以及其他相关属性。

	xmapsky=0;//设置天空背景图的 x 坐标偏移量为 0，即初始情况下天空背景图不偏移
	xmap=0;//设置地图的 x 坐标偏移量为 0，即初始情况下地图不偏移
	v0=0;//设置初始速度为 0。这可能用于控制角色或其他游戏元素的移动速度
	h=0;//设置高度为 0。这可能是一个临时变量，用于计算角色的跳跃高度或其他游戏中的高度相关的变量。
	t=0;//设置时间为 0。这可能是用于计时或其他时间相关的游戏机制的变量
	ibullet=-1;//将当前子弹索引设置为 -1，表示初始情况下没有任何子弹
	icoint.x=-1;//将金币的索引坐标设置为 (-1, -1)，表示初始情况下没有金币
	icoint.y=-1;
	score_frame=0; //设置得分帧数为 0，可能用于控制得分动画的播放
	bomb_frame=1;//设置炸弹帧数为 1，可能用于控制炸弹动画的播放
	mapbk_frame=1;// 设置地图背景帧数为 1，可能用于控制地图背景动画的播放
	temp.x=-1;// 将临时变量 temp 的坐标设置为 (-1, -1)，表示它目前没有有效值
	temp.y=-1;
	xbullet=41*role.w-10;//设置子弹的初始位置坐标，这可能是游戏中角色发射子弹的初始位置
	ybullet=4*role.h-25;
	get_bullet=0; //将获取的子弹数量设置为 0，表示初始情况下玩家没有获得任何子弹
	win=0;//将游戏胜利状态设置为 0，表示游戏尚未胜利
	pause=0;//将暂停状态设置为 0，表示游戏初始时不处于暂停状态
	score=0;//将得分设置为 0，表示初始时玩家的得分为 0
	//接下来设置游戏角色的初始属性，包括角色的位置 (x, y)、大小 (w, h)，以及其他相关属性。

	int i;
	for(i=0;i<350;i++)
    {
		map[i].id=0;//将地图数组中第 i 个元素的 id 属性设置为 0，表示该位置的地图元素为空
		map[i].x=-1;//将地图数组中第 i 个元素的 x 坐标属性设置为 -1，表示该位置的地图元素的 x 坐标未定义或不可用
		map[i].y=-1;//将地图数组中第 i 个元素的 y 坐标属性设置为 -1，表示该位置的地图元素的 y 坐标未定义或不可用。
		if(i<50)
		{
			coint[i].x=-1;
			coint[i].y=-1;
			coint[i].iframe=1;
		}
		// 如果 i 小于 50，则将金币数组中第 i 个金币的 x、y 坐标属性都设置为 -1，表示该位置没有金币；
		// 并将该金币的 iframe 属性设置为 1，可能表示金币处于初始状态。
		if(i<20)//如果 i 小于 20，则对子弹、敌人和炸弹数组中的元素进行类似的初始化操作
		{
			bullet[i].id=0;//将第 i 个子弹的 id 属性设置为 0，表示该位置没有子弹
			bullet[i].x=-1;//将第 i 个子弹的 x、y 坐标属性都设置为 -1，表示该位置的子弹未定义或不可用
	        bullet[i].y=-1;
	        bullet[i].iframe=1;//将第 i 个子弹的 iframe 属性设置为 1，可能表示子弹处于初始状态
	        bullet[i].turn=-1;  //属性通常用来表示子弹的运动方向

			enemy[i].id=0;
   			enemy[i].x=-1;
	        enemy[i].y=-1;
         	enemy[i].turn=1;
	        enemy[i].iframe=1;

			bomb[i].x=-1;
			bomb[i].y=-1;

			//对敌人和炸弹数组的元素也进行类似的初始化操作，将它们的属性设置为初始值
	 	}
	}
	//初始化地图、金币、子弹、敌人等游戏元素的属性。

	loadimage(&img_mapsky,"res\\mapsky.bmp",XSIZE,YSIZE*4);
	loadimage(&img_p,"res\\role.bmp");
	loadimage(&img_map,"res\\map.bmp");
	loadimage(&img_ani,"res\\ani.bmp");
	loadimage(&img_mapbk,"res\\mapbk.bmp");
	loadimage(&img_home,"res\\home.bmp",XSIZE,YSIZE*5);
	//加载游戏所需的图片资源。

    mciSendString("open 背景音乐.mp3 alias mymusic1", NULL, 0, NULL);
	mciSendString("open 子弹.mp3 alias mymusic2", NULL, 0, NULL);
	mciSendString("open 金币.mp3 alias mymusic3", NULL, 0, NULL);
	mciSendString("open 跳.mp3 alias mymusic4", NULL, 0, NULL);
	mciSendString("open 子弹打到敌人.mp3 alias mymusic5", NULL, 0, NULL);
	mciSendString("open 子弹撞墙.mp3 alias mymusic6", NULL, 0, NULL);
	mciSendString("open 踩敌人.mp3 alias mymusic7", NULL, 0, NULL);
	mciSendString("open 吃到武器.mp3 alias mymusic8", NULL, 0, NULL);	
	mciSendString("open 胜利.mp3 alias mymusic9", NULL, 0, NULL);
	mciSendString("open 死亡1.mp3 alias mymusic10", NULL, 0, NULL);
	mciSendString("open 死亡2.mp3 alias mymusic11", NULL, 0, NULL);
	//初始化音乐资源。               


	for(i=0;i<300;i++)                 //以下都是编辑地图
	{
		map[i].id=1;
		map[i].x=i%100*role.w;
		if(i<100)
			map[i].y=9*role.h;
		else if(i>=100&&i<200)
			map[i].y=10*role.h;
		else
			map[i].y=11*role.h;
	}
	//编辑地图，设置地图中的障碍物。

	map[15].id=1,map[15].x=18*role.w,map[15].y=8*role.h;
	map[115].id=1,map[115].x=19*role.w,map[115].y=8*role.h;
	map[215].id=1,map[215].x=20*role.w,map[215].y=8*role.h;

	//在地图中的特定位置设置了一些地图元素，具体包括一些障碍物和其他元素，
	// 这些元素可能对游戏角色的移动和交互产生影响
	map[16].id=1,map[16].x=21*role.w,map[16].y=8*role.h;
	map[116].id=1,map[116].x=22*role.w,map[116].y=8*role.h;
	map[216].id=1,map[216].x=23*role.w,map[216].y=8*role.h;

	map[17].id=1,map[17].x=24*role.w,map[17].y=8*role.h;
	map[117].id=1,map[117].x=25*role.w,map[117].y=8*role.h;
	map[217].id=1,map[217].x=26*role.w,map[217].y=8*role.h;

	map[300].id=2,map[300].x=10*role.w,map[300].y=6*role.h;
	map[301].id=2,map[301].x=11*role.w,map[301].y=6*role.h;
	map[302].id=2,map[302].x=12*role.w,map[302].y=6*role.h;

	map[303].id=3,map[303].x=36*role.w,map[303].y=7*role.h;
	map[304].id=3,map[304].x=44*role.w,map[304].y=7*role.h;

	map[305].id=2,map[305].x=40*role.w,map[305].y=4*role.h;
	map[306].id=2,map[306].x=41*role.w,map[306].y=4*role.h;
	map[307].id=2,map[307].x=42*role.w,map[307].y=4*role.h;

	map[308].id=2,map[308].x=13*role.w,map[308].y=6*role.h;

	map[309].id=4,map[309].x=15*role.w,map[309].y=10*role.h;

	map[310].id=5,map[310].x=19*role.w,map[310].y=6*role.h;
	map[311].id=5,map[311].x=23*role.w,map[311].y=6*role.h;
	map[312].id=5,map[312].x=32*role.w,map[312].y=7*role.h;
	map[313].id=5,map[313].x=48*role.w,map[313].y=7*role.h;
	map[314].id=5,map[314].x=52*role.w,map[314].y=7*role.h;
	map[315].id=5,map[315].x=56*role.w,map[315].y=7*role.h;

	map[316].id=3,map[316].x=80*role.w,map[316].y=7*role.h;
	map[317].id=3,map[317].x=90*role.w,map[317].y=7*role.h;

	map[318].id=2,map[318].x=62*role.w,map[318].y=6*role.h;

	map[319].id=2,map[319].x=65*role.w,map[319].y=3*role.h;
	map[320].id=2,map[320].x=66*role.w,map[320].y=3*role.h;
	map[321].id=2,map[321].x=67*role.w,map[321].y=3*role.h;
	map[322].id=2,map[322].x=68*role.w,map[322].y=3*role.h;
	map[323].id=2,map[323].x=69*role.w,map[323].y=3*role.h;

	map[349].id=6,map[349].x=97*role.w,map[349].y=7*role.h;

	for(i=64;i<300;i+=100)
	{
		map[i].id=0;map[i].x=-1;map[i].y=-1;
		map[i+1].id=0;map[i+1].x=-1;map[i+1].y=-1;
		map[i+2].id=0;map[i+2].x=-1;map[i+2].y=-1;

		map[i+7].id=0;map[i].x=-1;map[i].y=-1;
		map[i+8].id=0;map[i+1].x=-1;map[i+1].y=-1;
		map[i+9].id=0;map[i+1].x=-1;map[i+1].y=-1;

		map[i+11].id=0;map[i].x=-1;map[i].y=-1;
		map[i+12].id=0;map[i+1].x=-1;map[i+1].y=-1;
		map[i+13].id=0;map[i+1].x=-1;map[i+1].y=-1;
	}
	map[64].id=4,map[64].x=64*role.w,map[64].y=10*role.h;
	map[71].id=4,map[71].x=71*role.w,map[71].y=10*role.h;
	map[75].id=4,map[75].x=75*role.w,map[75].y=10*role.h;

	enemy[0].id=1;enemy[0].x=6*role.w;enemy[0].y=8*role.h;enemy[0].turn=1;enemy[0].iframe=1;
	enemy[1].id=1;enemy[1].x=8*role.w;enemy[1].y=8*role.h;enemy[1].turn=1;enemy[1].iframe=1;
	enemy[2].id=1;enemy[2].x=27*role.w;enemy[2].y=8*role.h;enemy[2].turn=1;enemy[2].iframe=1;
	enemy[3].id=1;enemy[3].x=29*role.w;enemy[3].y=8*role.h;enemy[3].turn=1;enemy[3].iframe=1;
	enemy[4].id=1;enemy[4].x=31*role.w;enemy[4].y=8*role.h;enemy[4].turn=1;enemy[4].iframe=1;
	enemy[5].id=1;enemy[5].x=33*role.w;enemy[5].y=8*role.h;enemy[5].turn=1;enemy[5].iframe=1;
	enemy[6].id=1;enemy[6].x=35*role.w;enemy[6].y=8*role.h;enemy[6].turn=1;enemy[6].iframe=1;
	enemy[7].id=1;enemy[7].x=40*role.w;enemy[7].y=8*role.h;enemy[7].turn=1;enemy[7].iframe=1;
	enemy[8].id=1;enemy[8].x=82*role.w;enemy[8].y=8*role.h;enemy[8].turn=1;enemy[8].iframe=1;
	enemy[9].id=1;enemy[9].x=65*role.w;enemy[9].y=2*role.h;enemy[9].turn=1;enemy[9].iframe=1;
	enemy[10].id=1;enemy[10].x=69*role.w;enemy[10].y=2*role.h;enemy[10].turn=1;enemy[10].iframe=1;
	enemy[11].id=1;enemy[11].x=85*role.w;enemy[11].y=8*role.h;enemy[11].turn=1;enemy[11].iframe=1;
	//初始化了一些敌人的位置、朝向、以及是否处于动画帧中


	for(i=0;i<4;i++)
	{
		coint[i].x=(10+i)*role.w;
	    coint[i].y=5*role.h;

		coint[i+4].x=(67+i)*role.w;
		coint[i+4].y=8*role.w;

		coint[i+8].x=74*role.w;
		coint[i+8].y=(4+i)*role.w;
	}
	for(i=12;i<18;i++)
	{
		coint[i].x=(83-12+i)*role.w;
	    coint[i].y=6*role.h;

		coint[i+6].x=(83-12+i)*role.w;
		coint[i+6].y=7*role.w;
	}
	//设置金币的位置。

}
void game::move()
{	
	MyTimer tt;//创建了一个计时器对象，用于控制游戏循环的速度
	int c;//定义一个变量用于存储从键盘输入的命令
	int k=0;                              //控制发射子弹的频率和敌人的移动速度
	int n=0;                              //控制发射子弹的频率
	while(true)//进入游戏主循环，直到游戏结束才退出
	{
		tt.Sleep(25);//控制游戏循环每次执行的时间间隔，控制游戏的帧率
		t=sqrt(2*HIGH/G)/14; //根据角色跳跃的物理模型，计算出角色从最高点落到地面的时间。
		k++;//计数器自增，用于控制子弹发射频率和敌人的移动速度
		if(k==1000)
	    	k=0;//计数器自增，用于控制子弹发射频率和敌人的移动速度
		if(kbhit()&&win==0)//检测键盘输入，并且游戏还未结束时执行键盘控制的逻辑
		{
			c=GetCommand();//获取键盘输入的命令
	    	if(c&CMD_LEFT)
	    		left();
	    	if(c&CMD_RIGHT)
				right();
	    	if((c&CMD_UP)&&role.jump==0)
				up();
			if(c&CMD_ESC)
			{
				pause=1;
				break;
			}
			if(c&CMD_SHOOT&&get_bullet==1)////检查是否按下了射击键，并且主角拥有子弹（get_bullet为1）
			{
				if(n==0)
			    {
			    	init_shoot();
			    	n=1;
			    }
				//如果 n 等于0（即刚开始射击），则调用 init_shoot() 函数初始化射击动作，同时将 n 设为1
				n++;
				if(k%10==0&&n>10)
			    {
			    	init_shoot();
			    }//每次按下射击键，n 值加1，如果满足条件 k%10==0 并且 n 大于10，则再次调用 init_shoot() 函数进行射击，实现一定的射击频率
			}
			else
			    n=0;
			//否则，将 n 设为0，表示射击动作结束
		}
		if(-xmap+role.x==97*role.w)//当角色到达特定位置时播放相应的音乐
		{
		    mciSendString("stop mymusic1", NULL, 0, NULL);
			mciSendString("play mymusic9", NULL, 0, NULL);
		}
		if(-xmap+role.x>95*role.w)
		{
			
            win=1;//游戏胜利
			role.x+=STEP;//将角色向前移动一个步长(STEP)的距离
			if(role.x-STEP>XSIZE)//如果角色的x坐标减去步长后超过了屏幕的宽度(XSIZE)，则退出循环，结束游戏
				break;
		}
		if(is_b_touch(1)==0)//检查是否有地面支撑，如果没有，则将角色的jump标志设置为1，表示角色处于跳跃状态
			role.jump=1;
		if(role.jump==1)//检查角色是否处于跳跃状态，如果是，则执行 fall() 函数，实现角色的下落
			fall();
		if(isdie()==1)
		{
			mciSendString("stop mymusic1", NULL, 0, NULL);
			mciSendString("play mymusic11", NULL, 0, NULL);
			life--;//减少生命值
			return;	
		}
		//敌人的运动
		if(k%2==0)//检查变量 k 是否为偶数，这个条件每隔一定的时间执行一次敌人的运动逻辑
		{
	    	for(int i=0;i<20;i++)//对于每一个敌人，重复以下操作
	    	{
		    	if(enemy[i].id==1)//检查当前敌人是否存在
		    	{
		            if(is_land(enemy[i])==1)//检查当前敌人是否存在，如果是，执行以下操作：
		            {
		    	        if(enemy[i].turn==1)//如果敌人的方向为向右，则向右移动一个步长(STEP)
			    	        enemy[i].x+=STEP;
			            else//否则，向左移动一个步长(STEP)
				            enemy[i].x-=STEP;
			    	}
		            if(is_land(enemy[i])==0||is_l_touch(3)==1||is_r_touch(3)==1)
					//如果敌人不在地面上，或者敌人触碰到了左侧或右侧的障碍物，则执行以下操作
		            {
		            	if(enemy[i].turn==1)//如果敌人的方向为向右，则向左移动一个步长(STEP)
		            		enemy[i].x-=STEP;
		            	else//否则，向右移动一个步长(STEP)
		            		enemy[i].x+=STEP;
		            	enemy[i].turn*=-1;//将敌人的方向取反，改变敌人的移动方向
		            }
				    enemy[i].iframe*=-1;//改变敌人的动画帧，以实现动画效果
			    }
	    	}
		}
		int boom=0;
		if(is_b_touch(2)==1)                     //如果主角“踩到”敌人
			boom=1;
		getbullet();                             //获取子弹
		if(get_bullet==1)
			shoot();

		BeginBatchDraw();// 开始批量绘制，用于优化绘制性能
		show();//展示游戏画面
		FlushBatchDraw();//刷新批量绘制的内容到屏幕上

		if((is_l_touch(2)==1||is_r_touch(2)==1))
		//检查主角是否与敌人发生了碰撞，或者主角是否碰到了地图中的障碍物。
		// 如果条件成立，表示主角遭受了伤害，执行以下操作：
		{
			mciSendString("stop mymusic1", NULL, 0, NULL);//停止当前播放的背景音乐
			mciSendString("play mymusic10", NULL, 0, NULL);//播放另一段音乐作为受伤的音效
			life--;//减少主角的生命值(life)
			pause=0;//将暂停标志(pause)设置为0，表示游戏不处于暂停状态
			//根据受伤位置，更新主角的图像显示，以展示受伤效果
			putimage(role.x,role.y,role.w,role.h,&img_p,2*role.w,role.h,SRCAND);
	        putimage(role.x,role.y,role.w,role.h,&img_p,2*role.w,0,SRCPAINT);
		    return;
		}
	}
}
void game::show()
{
	if(xmapsky==-XSIZE)
		xmapsky=0;
    putimage(xmapsky,0,&img_mapsky);     //显示背景
	//在游戏窗口的左侧绘制背景图。xmapsky 控制了背景图的横向偏移，使其随着角色的移动而滚动
	putimage(XSIZE+xmapsky,0,&img_mapsky);
	//在游戏窗口的右侧绘制背景图，以实现无缝滚动的效果

	if(is_touch()==1)//检查是否与硬币发生了碰撞。如果碰撞了，将 score_frame 设置为1。
		score_frame=1;
	if(score_frame!=0)                  //碰到硬币，显示得分
	//检查是否与硬币发生了碰撞。如果碰撞了，将 score_frame 设置为1。
	{		
		// 根据 score_frame 的值，使用 switch 语句来决定当前播放的是哪一帧的硬币动画。
		// 根据不同的帧数，绘制相应的硬币动画
		switch((int)score_frame)
		{
		case 1:
			putimage(xmap+icoint.x,icoint.y,role.w,role.h,&img_ani,0,11*role.h,SRCAND);
		    putimage(xmap+icoint.x,icoint.y,role.w,role.h,&img_ani,0,10*role.h,SRCPAINT);
			break;
		case 2:
			putimage(xmap+icoint.x,icoint.y,role.w,role.h,&img_ani,role.w,11*role.h,SRCAND);
			putimage(xmap+icoint.x,icoint.y,role.w,role.h,&img_ani,role.w,10*role.h,SRCPAINT);
			break;
		case 3:
			putimage(xmap+icoint.x,icoint.y,role.w,role.h,&img_ani,2*role.w,11*role.h,SRCAND);
			putimage(xmap+icoint.x,icoint.y,role.w,role.h,&img_ani,2*role.w,10*role.h,SRCPAINT);
			break;
		case 4:
			putimage(xmap+icoint.x,icoint.y,role.w,role.h,&img_ani,3*role.w,11*role.h,SRCAND);
			putimage(xmap+icoint.x,icoint.y,role.w,role.h,&img_ani,3*role.w,10*role.h,SRCPAINT);
			break;
		default:
			break;
		}	
		score_frame+=0.2;
	    if(score_frame==5)
		    score_frame=0;
		//用来控制硬币动画帧的播放。每次执行完一帧动画后，score_frame 的值会增加0.2
		// 这样可以控制动画的播放速度
		// 当 score_frame 的值达到5时，表示已经播放完所有的硬币动画帧
		// 此时将 score_frame 重置为0，以实现动画的循环播放
	}
	int i;
	for(i=0;i<350;i++)             //显示地图，天空上的地图和硬币
	{
		if(map[i].id==1)
		{
			putimage(xmap+map[i].x,map[i].y,role.w,role.h,&img_map,0,0);
		}
		else if(map[i].id==2)
		{
			putimage(xmap+map[i].x,map[i].y,role.w,role.h,&img_map,0,role.h);
		}
		else if(map[i].id==3)
		{
			putimage(xmap+map[i].x,map[i].y,2*role.w,2*role.h,&img_map,0,9*role.h);
		}
		else
		{
		    if(map[i].id==4)
		    {
		    	switch((int)mapbk_frame)
		    	{
		    	case 1:
		    		putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,0,10*role.h,SRCAND);
		    	    putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,0,8*role.h,SRCPAINT);
		    		break;
		    	case 2:
		   	     	putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,3*role.w,10*role.h,SRCAND);
		     		putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,3*role.w,8*role.h,SRCPAINT);
			    	break;
	    		default:
	    			break;
	    		}	
		    }
			else if(map[i].id==5)
		    {
		    	switch((int)mapbk_frame)
		    	{
		    	case 1:
		    		putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,0,2*role.h,SRCAND);
		    	    putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,0,0,SRCPAINT);
		    		break;
		    	case 2:
		   	     	putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,3*role.w,2*role.h,SRCAND);
		     		putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,3*role.w,0,SRCPAINT);
			    	break;
	    		default:
	    			break;
	    		}	
		    }
			else if(map[i].id==6)
			{
				switch((int)mapbk_frame)
		    	{
		    	case 1:
		    		putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,0,6*role.h,SRCAND);
					putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,0,4*role.h,SRCPAINT);
		    		break;
		    	case 2:
		   	     	putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,3*role.w,6*role.h,SRCAND);
					putimage(xmap+map[i].x,map[i].y,3*role.w,2*role.h,&img_mapbk,3*role.w,4*role.h,SRCPAINT);
			    	break;
	    		default:
	    			break;
	    		}	
			}
			mapbk_frame+=0.003;
	        if(mapbk_frame>2.9)
	   		{
	   			mapbk_frame=1;
	   		}
		}
		if(i<50)
		{
			if(coint[i].x!=-1||coint[i].y!=-1)
			{
				switch((int)coint[i].iframe)
				{
				case 1:
					putimage(xmap+coint[i].x,coint[i].y,role.w,role.h,&img_ani,0,9*role.h,SRCAND);
				    putimage(xmap+coint[i].x,coint[i].y,role.w,role.h,&img_ani,0,8*role.h,SRCPAINT);
					break;
				case 2:
					putimage(xmap+coint[i].x,coint[i].y,role.w,role.h,&img_ani,role.w,9*role.h,SRCAND);
					putimage(xmap+coint[i].x,coint[i].y,role.w,role.h,&img_ani,role.w,8*role.h,SRCPAINT);
					break;
				case 3:
					putimage(xmap+coint[i].x,coint[i].y,role.w,role.h,&img_ani,2*role.w,9*role.h,SRCAND);
					putimage(xmap+coint[i].x,coint[i].y,role.w,role.h,&img_ani,2*role.w,8*role.h,SRCPAINT);
					break;
				case 4:
					putimage(xmap+coint[i].x,coint[i].y,role.w,role.h,&img_ani,3*role.w,9*role.h,SRCAND);
					putimage(xmap+coint[i].x,coint[i].y,role.w,role.h,&img_ani,3*role.w,8*role.h,SRCPAINT);
					break;
				default:
					break;
				}	
				coint[i].iframe+=0.125;
			    if(coint[i].iframe==5)
				    coint[i].iframe=1;
			}
		}
	}
	if(get_bullet==0)
	{

		switch((int)mapbk_frame)
	 	{
		    case 1:
		   		putimage(xmap+xbullet,ybullet,52,25,&img_ani,0,12*role.h+25,SRCAND);
                putimage(xmap+xbullet,ybullet,52,25,&img_ani,0,12*role.h,SRCPAINT);
		    	break;
		    case 2:
     	     	putimage(xmap+xbullet,ybullet,52,25,&img_ani,52,12*role.h+25,SRCAND);
                putimage(xmap+xbullet,ybullet,52,25,&img_ani,52,12*role.h,SRCPAINT);
			   	break;
	    	default:
	    	    break;
	  	}	

	}
	for(i=0;i<20;i++)             //显示子弹
	{
		if(get_bullet==1)
		{
		    if(bullet[i].id==1)
	        {
	            if(bullet[i].iframe==1)
    	        {
	            	putimage(bullet[i].x,bullet[i].y,role.w,role.h,&img_ani,0,3*role.h,SRCAND);
    		        putimage(bullet[i].x,bullet[i].y,role.w,role.h,&img_ani,0,2*role.h,SRCPAINT);
	            }
    	        else
    	        {
    	        	putimage(bullet[i].x,bullet[i].y,role.w,role.h,&img_ani,role.w,3*role.h,SRCAND);
    	        	putimage(bullet[i].x,bullet[i].y,role.w,role.h,&img_ani,role.w,2*role.h,SRCPAINT);
        	    }	
            }
		}
		if(enemy[i].id==1)
		{
	    	if(enemy[i].iframe==1)                           //显示敌人
	        { 
		        putimage(xmap+enemy[i].x,enemy[i].y,role.w,role.h,&img_ani,0,role.h,SRCAND);
    	        putimage(xmap+enemy[i].x,enemy[i].y,role.w,role.h,&img_ani,0,0,SRCPAINT);
	        }
	        else
	        {
	        	putimage(xmap+enemy[i].x,enemy[i].y,role.w,role.h,&img_ani,role.w,role.h,SRCAND);
	        	putimage(xmap+enemy[i].x,enemy[i].y,role.w,role.h,&img_ani,role.w,0,SRCPAINT);
	        }
	        
		}
		if(bomb[i].x!=-1||bomb[i].y!=-1)
		{
			switch((int)bomb_frame)
			{
			case 1:
				putimage(xmap+bomb[i].x-role.w/2,bomb[i].y-role.h/2,2*role.w,2*role.h,&img_ani,0,6*role.h,SRCAND);
			    putimage(xmap+bomb[i].x-role.w/2,bomb[i].y-role.h/2,2*role.w,2*role.h,&img_ani,0,4*role.h,SRCPAINT);
				break;
			case 2:
				putimage(xmap+bomb[i].x-role.w/2,bomb[i].y-role.h/2,2*role.w,2*role.h,&img_ani,2*role.w,6*role.h,SRCAND);
				putimage(xmap+bomb[i].x-role.w/2,bomb[i].y-role.h/2,2*role.w,2*role.h,&img_ani,2*role.w,4*role.h,SRCPAINT);
				break;
			case 3:
				putimage(xmap+bomb[i].x-role.w/2,bomb[i].y-role.h/2,2*role.w,2*role.h,&img_ani,4*role.w,6*role.h,SRCAND);
				putimage(xmap+bomb[i].x-role.w/2,bomb[i].y-role.h/2,2*role.w,2*role.h,&img_ani,4*role.w,4*role.h,SRCPAINT);
				break;
			case 4:
				putimage(xmap+bomb[i].x-role.w/2,bomb[i].y-role.h/2,2*role.w,2*role.h,&img_ani,6*role.w,6*role.h,SRCAND);
				putimage(xmap+bomb[i].x-role.w/2,bomb[i].y-role.h/2,2*role.w,2*role.h,&img_ani,6*role.w,4*role.h,SRCPAINT);
				break;
			default:
				break;
			}	
			bomb_frame+=0.25;
		    if(bomb_frame==5)
			{
				bomb[i].x=-1;
			    bomb[i].y=-1;
				bomb_frame=1;
			}
		}
	}
	int n=score;
	char s1[20]="当前得分：";
	char s2[10];
	itoa(n,s2,10);
	RECT r1={10,10,110,40};
	RECT r2={110,10,150,40};
	setfont(20, 0,"宋体");
	drawtext(s1, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(s2, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	if(role.iframe==1)                           //显示主角
	{
		if(role.turn==1)
		{
		    putimage(role.x,role.y,role.w,role.h,&img_p,0,role.h,SRCAND);
    	    putimage(role.x,role.y,role.w,role.h,&img_p,0,0,SRCPAINT);
		}
		else
		{
			putimage(role.x,role.y,role.w,role.h,&img_p,4*role.w,role.h,SRCAND);
    	    putimage(role.x,role.y,role.w,role.h,&img_p,4*role.w,0,SRCPAINT);
		}
	}
	else
	{
		if(role.turn==1)
		{
			putimage(role.x,role.y,role.w,role.h,&img_p,role.w,role.h,SRCAND);
    	    putimage(role.x,role.y,role.w,role.h,&img_p,role.w,0,SRCPAINT);
		}
		else
		{
			putimage(role.x,role.y,role.w,role.h,&img_p,3*role.w,role.h,SRCAND);
    	    putimage(role.x,role.y,role.w,role.h,&img_p,3*role.w,0,SRCPAINT);
		}
	}
}  
int game::isdie()
{
	if(role.y>=YSIZE)
		return 1;
	else
		return 0;
}//这个函数主要用于检查角色是否已经掉出了游戏地图的底部，如果掉出了，则视为角色死亡
int game::GetCommand()//这个函数的作用是获取玩家在游戏中输入的命令，以一个整数的形式返回
{
	int c = 0;
	//首先，定义一个整型变量c，用于存储命令的状态。初始值为0
	if (GetAsyncKeyState('A') & 0x8000)
		c |= CMD_LEFT;
	//如果按下键盘上的'A'键，c的第一位（从右向左数）将被置为1，表示左移命令
	if (GetAsyncKeyState('D') & 0x8000)
    	c |= CMD_RIGHT;
	//如果按下键盘上的'D'键，c的第二位将被置为1，表示右移命令
	if ((GetAsyncKeyState('W') & 0x8000)||(GetAsyncKeyState('K') & 0x8000))
    	c |= CMD_UP;
	//如果按下键盘上的'W'键或者'K'键，c的第三位将被置为1，表示向上移动的命令
	if (GetAsyncKeyState('S') & 0x8000)
    	c |= CMD_DOWN;
	//如果按下键盘上的'S'键，c的第四位将被置为1，表示向下移动的命令
	if (GetAsyncKeyState('J') & 0x8000)
    	c |= CMD_SHOOT;
	//如果按下键盘上的'J'键，c的第五位将被置为1，表示射击命令
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    	c |= CMD_ESC;
	//如果按下键盘上的'ESC'键，c的第六位将被置为1，表示退出命令
	return c;
	//最后，返回整数c，其中包含了玩家当前的输入命令状态
}
void game::left()
{
	role.iframe*=-1;//将角色的iframe乘以-1，可能是用于调整角色的动画帧，以反映向左移动的动作	
	role.turn=-1;//设置角色的turn属性为-1，可能是用于指示角色的朝向（-1表示向左
	role.x-=STEP;
	//将角色的横坐标减去一个预设的常数STEP，表示向左移动一个步长
	if(is_l_touch(1)==1)
	//如果角色与地图或其他物体发生了碰撞（is_l_touch(1)==1），
	// 则将角色的横坐标重新加上一个步长，即取消移动，以避免穿墙
		role.x+=STEP;	
	if(role.x<role.xleft)
      	role.x+=STEP;
	//如果角色的横坐标小于规定的左边界（role.xleft）
	// 则将角色的横坐标重新加上一个步长，同样是为了避免越界
}
void game::right()
{
	role.iframe*=-1;	
	role.turn=1;
	role.x+=STEP;
	
	if(is_r_touch(1)==1)
	//如果角色与地图或其他物体发生了碰撞（is_r_touch(1)==1），则将角色的横坐标重新减去一个步长，即取消移动
		role.x-=STEP;
	if(role.x>role.xright&&(-xmap+role.x<90*role.w))
	//如果角色的横坐标大于角色的右边界（role.xright）
	// 并且角色的位置离地图的左边界不足90个角色宽度（ - xmap + role.x < 90 * role.w）
	// 则进行如下操作：
	{
    	role.x-=STEP;//将角色的横坐标重新减去一个步长，即取消移动，以避免越界
		xmapsky-=1;//同时，将xmapsky减去1，可能是用于控制游戏中的天空背景的移动
	    xmap-=STEP;//将xmap减去一个步长，可能是用于控制游戏地图的滚动效果
	}
}
void game::up()
{
	mciSendString("play mymusic4 from 0", NULL, 0, NULL);
	role.iframe*=-1;	
	v0=-sqrt(2*G*HIGH);//这一行计算了一个名为 v0 的变量的值
	role.jump=1;//这一行将 role 对象中的另一个成员变量 jump 的值设置为 1
}
void game::init_shoot()
{
	mciSendString("play mymusic2 from 0", NULL, 0, NULL);
	ibullet++;//这行代码增加了一个名为 ibullet 的变量的值。它用来跟踪子弹的数量
	if(ibullet==20)
	// 这个条件语句检查 ibullet 的值是否达到了上限（20）
	// 如果是，就将其重置为0。这样做可能是为了循环利用子弹数组，避免索引越界
		ibullet=0;
	bullet[ibullet].id=1;
	// 这行代码将一个名为 bullet 的数组中特定索引处的 id 成员设置为1。这可能用于标识不同类型的子弹
	bullet[ibullet].y=role.y+8;
	//这行代码设置了特定索引处子弹的 y 坐标，是基于角色的位置进行设置的
    bullet[ibullet].turn=role.turn;
	//这行代码设置了特定索引处子弹的 turn 成员，是根据角色的朝向进行设置的
	if(bullet[ibullet].turn==1)
	//这行代码根据角色的朝向设置了特定索引处子弹的 x 坐标。
	// 如果角色朝向为1，就在角色的右边（role.x+10），否则就在左边
		bullet[ibullet].x=role.x+10;
	else
	//这是条件语句的另一个分支，如果角色的朝向不是1，就设置子弹的 x 坐标为角色的左边
		bullet[ibullet].x=role.x-26;
}
int game::is_l_touch(int id)
{
	int x,y;
	int i;
	if(id==1)                                    //id==1表示主角是否碰到id为1的地图，及游戏中黄色的地图
	{
    	x=-xmap+role.x;
    	y=role.y;
    	for(i=0;i<350;i++)
    	{
    		if(map[i].id!=0&&map[i].id<4)
    		{
    			POINT m[2];

			    m[0].x=map[i].x;
			    m[0].y=map[i].y;

		    	m[1].x=map[i].x+role.w;
		    	m[1].y=map[i].y;

				if(map[i].id==3)
				{
					if(((y-m[1].y)/role.h==0||(y-m[1].y-role.h)/role.h==0)&&x>m[1].x&&x<m[1].x+role.w)
			    	    return 1;
				}
				else
				{
					if((y-m[1].y)/role.h==0&&x>m[0].x&&x<m[1].x)
			    	    return 1;
				}
		    }
	    }
	    return 0;
	}
   	else if(id==2)                                 //id==2表示主角是否碰到敌人的左边
   	{
        x=-xmap+role.x;
       	y=role.y;
       	for(i=0;i<20;i++)
		{
        	if(enemy[i].id!=0)
        	{
		    	POINT m[2];  

	    		m[0].x=enemy[i].x;
	    		m[0].y=enemy[i].y;

	    	   	m[1].x=enemy[i].x+role.w;
		    	m[1].y=enemy[i].y;

		    	if((y-m[1].y)/role.h==0&&x>m[0].x&&x<m[1].x)  		
	    			return 1;
			}
		}
	    return 0;
	}
	else                                        //id==3表示敌人是否碰到地图的左边
	{
		int j;
		for(j=0;j<20;j++)
		{
			if(enemy[j].id!=0)
			{
    	        x=enemy[j].x;
    	        y=enemy[j].y;
			
    	        for(i=0;i<350;i++)
		        {
            		if(map[i].id!=0&&map[i].id<4)
            		{
            			POINT m[2];
     
			            m[0].x=map[i].x;
	        		    m[0].y=map[i].y;

		            	m[1].x=map[i].x+role.w;
		            	m[1].y=map[i].y;

			         	if(map[i].id==3)
			           	{
			        		if(((y-m[1].y)/role.h==0||(y-m[1].y-role.h)/role.h==0)&&x>m[1].x&&x<m[1].x+role.w)
			    	            return 1;
		         		}   
			        	else
			        	{
			        		if((y-m[1].y)/role.h==0&&x>m[0].x&&x<m[1].x)
			    	            return 1;
				        }   
					}
				}
			}
		}
		return 0;
	}
}
int game::is_r_touch(int id)
{
	int x,y;
	int i;
	if(id==1)
	{    
	    x=-xmap+role.x+role.w;
	    y=role.y;

	    for(i=0;i<350;i++)
    	{
	    	if(map[i].id!=0&&map[i].id<4)
		    {
			    POINT m[2];
 
    			m[0].x=map[i].x;
    			m[0].y=map[i].y;

    			m[1].x=map[i].x+role.w;
    			m[1].y=map[i].y;

				if(map[i].id==3)
				{
					if(((y-m[0].y)/role.h==0||(y-m[0].y-role.h)/role.h==0)&&x>m[0].x&&x<m[1].x)
			    	    return 1;
				}
				else
				{
					if((y-m[0].y)/role.h==0&&x>m[0].x&&x<m[1].x)
		    		    return 1;
				}
		    }
	    }
	    return 0;
	}
	else if(id==2)
	{
	    x=-xmap+role.x+role.w;
	    y=role.y;

	    for(i=0;i<20;i++)
	    {
		    if(enemy[i].id!=0)
		    {
		    	POINT m[2];

			    m[0].x=enemy[i].x;
		    	m[0].y=enemy[i].y;
 
    			m[1].x=enemy[i].x+role.w;
    			m[1].y=enemy[i].y;

	    		if((y-m[0].y)/role.h==0&&x>m[0].x&&x<m[1].x)
		    		return 1;
	    	}
	    }
	    return 0;
	}
	else
	{
		int j;
		for(j=0;j<20;j++)
		{
			if(enemy[j].id!=0)
			{
			    x=enemy[j].x+role.w;
	            y=enemy[j].y;
			
	            for(i=0;i<350;i++)
		        {
	            	if(map[i].id!=0&&map[i].id<4)
        		    {
		        	    POINT m[2];
 
            			m[0].x=map[i].x;
            			m[0].y=map[i].y;

            			m[1].x=map[i].x+role.w;
    	        		m[1].y=map[i].y;

			        	if(map[i].id==3)
			        	{
				        	if(((y-m[0].y)/role.h==0||(y-m[0].y-role.h)/role.h==0)&&x>m[0].x&&x<m[1].x)
			    	            return 1;
				        }
				        else
				        {
					        if((y-m[0].y)/role.h==0&&x>m[0].x&&x<m[1].x)
		    		            return 1;
				        }
					}
	            }
			}
		}
		return 0;
	}
}
int game::is_t_touch()
{
	int x,y;
	x=-xmap+role.x;
	y=role.y;

	for(int i=0;i<350;i++)
	{
		if(map[i].id!=0&&map[i].id<4)
		{
			POINT m[2];

			m[0].x=map[i].x;
			m[0].y=map[i].y;

			m[1].x=map[i].x;
			m[1].y=map[i].y+role.h;

			if((x-m[1].x)/role.w==0&&y>m[0].y&&y<m[1].y)
				return 1;
		}
	}
	return 0;
}
int game::is_b_touch(int id)
{
	if(id==1)
	{
	    int x,y;
	    x=-xmap+role.x;
    	y=role.y+role.h;

	    for(int i=0;i<350;i++)
	    {
    		if(map[i].id!=0&&map[i].id<4)
    		{
    			POINT m[2];  

    			m[0].x=map[i].x;
	    		m[0].y=map[i].y;

	    		m[1].x=map[i].x; 
		    	m[1].y=map[i].y+role.h;

				if(map[i].id==3)
				{
					if(((x-m[0].x)/role.w==0||(x+role.w-m[0].x-2*role.w)/role.w==0)&&y>=m[0].y&&y<m[1].y)
			    	    return 1;
				}
				else
				{
					if((x-m[0].x)/role.w==0&&y>=m[0].y&&y<m[1].y)
			    	    return 1;
				}
			}
		}
	    return 0;
	}
	else if(id==2)
	{
		int x,y;
	    x=-xmap+role.x;
	    y=role.y+role.h;

    	for(int i=0;i<20;i++)
    	{
    		if(enemy[i].id!=0)
    		{
    			POINT m[2];

	    		m[0].x=enemy[i].x;
	    		m[0].y=enemy[i].y;

		    	m[1].x=enemy[i].x;
		    	m[1].y=enemy[i].y+role.h;

		    	if((x-m[0].x)/role.w==0&&y>m[0].y&&y<m[1].y)
				{
			    	mciSendString("play mymusic7 from 0", NULL, 0, NULL);
					score+=10;
					bomb[i].x=enemy[i].x;
		        	bomb[i].y=enemy[i].y;
					enemy[i].id=0;
			        enemy[i].iframe=-1;
			        enemy[i].turn=1;
		        	enemy[i].x=-1;
		        	enemy[i].y=-1;
		    		return 1;
				}
		    }
		}
	    return 0;
	}
	return 0;
}
int game::is_touch()
{
	int i,j;
	POINT r[2];
	r[0].x=-xmap+role.x;
	r[0].y=role.y;
	r[1].x=-xmap+role.x+role.w;
	r[1].y=role.y+role.h;
	for(i=0;i<50;i++)
	{
		if(coint[i].x!=-1||coint[i].y!=-1)
		{
			POINT c[4];

			c[0].x=coint[i].x;
			c[0].y=coint[i].y;

			c[1].x=coint[i].x+role.w;
			c[1].y=coint[i].y;

			c[2].x=coint[i].x;
			c[2].y=coint[i].y+role.h;

			c[3].x=coint[i].x+role.w;
			c[3].y=coint[i].y+role.h;

		    for(j=0;j<4;j++)
			{
				if(c[j].x>=r[0].x&&c[j].y>=r[0].y&&c[j].x<=r[1].x&&c[j].y<=r[1].y)
				{
			    	mciSendString("play mymusic3 from 0", NULL, 0, NULL);
					score+=20;
					icoint.x=coint[i].x;
					icoint.y=coint[i].y;

					coint[i].x=-1;
					coint[i].y=-1;
					coint[i].iframe=1;

					return 1;
				}
			}
		}
	}
	return 0;
}
int game::is_land(ENEMY e)
{
	POINT r[2];//这里定义了一个 POINT 类型的数组 r，用于存储敌人的两个底边的坐标
	r[0].x=e.x;
	r[0].y=e.y+role.h;
	// 这两行代码将敌人的左下角和右下角的坐标存储到数组 r 的第一个元素中，其中 role.h 可能表示主角的高度
	r[1].x=e.x+role.h;
	r[1].y=e.y+role.h;
	//这两行代码将敌人的右下角的坐标存储到数组 r 的第二个元素中
	for(int i=0;i<350;i++)
	{
		if(map[i].id!=0&&map[i].id<4)
		//: 这是一个条件语句，检查地图元素的 id 是否不为0且小于4。
		// 这个条件用于排除空白区域，并且可能表示特定类型的地图元素
		{
			POINT m[3];//这里定义了一个 POINT 类型的数组 m，用于存储地图元素的三个顶点的坐标

			m[0].x=map[i].x;
			m[0].y=map[i].y;
			//这两行代码将地图元素的第一个点的坐标存储到数组 m 的第一个元素中
			m[1].x=map[i].x+role.w;
			m[1].y=map[i].y;
			//这两行代码将地图元素的第二个点的坐标存储到数组 m 的第二个元素中，其中 role.w 可能表示主角的宽度
			m[2].x=map[i].x;
			m[2].y=map[i].y+role.h;
			//这两行代码将地图元素的第三个点的坐标存储到数组 m 的第三个元素中，其中 role.h 可能表示主角的高度
			if(e.turn==1)
			{
				if((r[1].x-m[0].x)/role.w==0&&r[1].y>=m[0].y&&r[1].y<m[2].y)
			    	return 1;
			}
			//这是一个条件语句，检查敌人的朝向是否为1。如果是1，执行第一个代码块；否则执行第二个代码块
			else
			{
				if((r[0].x-m[1].x)/role.w==0&&r[0].y>=m[0].y&&r[0].y<m[2].y)
			    	return 1;
			}
		}
	}
	return 0;
}
void game::getbullet()
{
	int i;
	POINT r[2];//这里定义了一个 POINT 类型的数组 r，用于存储主角的两个对角点的坐标
	r[0].x=-xmap+role.x;
	r[0].y=role.y;
	r[1].x=-xmap+role.x+role.w;
	r[1].y=role.y+role.h;

	POINT b[4];//这里定义了一个 POINT 类型的数组 b，用于存储子弹的四个顶点的坐标
	b[0].x=xbullet;
	b[0].y=ybullet;

	b[1].x=xbullet+52;
	b[1].y=ybullet;

	b[2].x=xbullet;
	b[2].y=ybullet+25;

	b[3].x=xbullet+52;
	b[3].y=ybullet+25;
	
	for(i=0;i<4;i++)//用于遍历子弹的四个顶点
	{
		if(b[i].x>=r[0].x&&b[i].y>=r[0].y&&b[i].x<=r[1].x&&b[i].y<=r[1].y)//检查子弹是否位于主角的包围盒内
		{
			mciSendString("play mymusic8 from 0", NULL, 0, NULL);
			get_bullet=1;//这行代码将一个名为 get_bullet 的变量设置为1，表示主角获取到了子弹
			//这两行代码将子弹的坐标重置为0，可能表示子弹消失了
			xbullet=0;
			ybullet=0;
		}
	}
}
void game::fall()           
{

	h=v0*t+G*pow(t,2)/2;
	//这行代码计算了主角在时间 t 内的垂直位移，根据自由落体运动的公式。
	// h 是位移，v0 是初始速度，G 是重力加速度
    role.y+=(int)(h+0.5);
	// 这行代码根据计算得到的位移，更新了主角的纵向位置。(int)(h+0.5) 的作用是将浮点数四舍五入为整数
	if(v0>=0)   //自由落体
	{
		if(isdie()==1)
			return;    
		if(is_b_touch(1)==1)//如果主角踩到敌人
		{
			v0=0; //如果主角踩到敌人，将主角的速度设为0，表示停止下落
			role.y=role.y/role.h*role.h;//将主角的纵坐标调整为地面的高度，使其紧贴在地面上
			role.jump=0;
		}
	}
	else       //向上跳跃
	{
		if(v0>=0)
			h=0;
		else
			role.y+=(int)(h+0.5);
		//如果主角的速度大于等于0（向上跳跃），则将位移 h 设为0，否则继续更新主角的纵向位置
		if(is_t_touch()==1)
		{
			v0=0;//如果主角与地面碰撞，将主角的速度设为0，表示停止下落
			h=0;//如果主角与顶部碰撞，将位移 h 设为0，表示停止向上移动
			role.y=role.y/role.h*role.h+role.h;//将主角的纵坐标调整为与顶部对齐，使其紧贴在顶部上方
		}
	}
	v0=v0+G*t;//根据自由落体运动的公式，更新主角的速度。将当前速度加上重力加速度乘以时间 t
}
void game::shoot()
{
	int i;
	for(i=0;i<20;i++)
	{
		if(bullet[i].id==1)
		{
			
	        if(bullet[i].turn==1)
			{
	     	    bullet[i].x+=2*STEP;
			}
			else
			{
		        bullet[i].x-=2*STEP;
			}
			if((bullet[i].x<(-3*role.w))||(bullet[i].x>XSIZE))
			{
		        bullet[i].id=0;
				bullet[i].x=-1;
	            bullet[i].y=-1;
	            bullet[i].iframe=1;
	            bullet[i].turn=1;	
			}
	        if(eat(bullet[i])==1)
			{
		        bullet[i].id=0;
				bullet[i].x=-1;
	            bullet[i].y=-1;
	            bullet[i].iframe=1;
	            bullet[i].turn=1;

				bomb[i].x=temp.x;
				bomb[i].y=temp.y;
			}
			bullet[i].iframe*=-1;
		}
	}
}
int game::eat(BULLET b)
{
	POINT r[4];//这里定义了一个 POINT 类型的数组 r，用于存储主角四个顶点的坐标
	r[0].x=-xmap+b.x+role.w/2;
	r[0].y=b.y;
	//这两行代码将主角的左上角的坐标存储到数组 r 的第一个元素中，b.x 和 b.y 表示子弹的横纵坐标
	// role.w 可能表示主角的宽度
	r[1].x=-xmap+b.x+role.w;
	r[1].y=b.y;
	//这两行代码将主角的右上角的坐标存储到数组 r 的第二个元素中
	r[2].x=-xmap+b.x+role.w/2;
	r[2].y=b.y+role.h/2;
	//这两行代码将主角的左下角的坐标存储到数组 r 的第三个元素中，role.h 表示主角的高度
	r[3].x=-xmap+b.x+role.w;
	r[3].y=b.y+role.h/2;
	// 这两行代码将主角的右下角的坐标存储到数组 r 的第四个元素中
	int i;
	for(i=0;i<350;i++)
	{
		if(map[i].id!=0&&map[i].id<4)
		// 这是一个条件语句，检查地图元素的 id 是否不为0且小于4。
		// 这个条件用于排除空白区域，并且可能表示特定类型的地图元素
		{
			POINT m[2];
			// 这里定义了一个 POINT 类型的数组 m，用于存储地图元素的两个顶点的坐标
			m[0].x=map[i].x;
			m[0].y=map[i].y;

			if(map[i].id==3)
			{
				m[1].x=map[i].x+2*role.w;
			    m[1].y=map[i].y+2*role.h;
			}
			else
			{
				m[1].x=map[i].x+role.w;
			    m[1].y=map[i].y+role.h;
			}
			// 这是一个条件语句，检查地图元素的 id 是否为3。如果是3，执行第一个代码块；否则执行第二个代码块
			for(int j=0;j<4;j++)// 这是一个循环结构，用于遍历主角四个顶点
			{
				if(r[j].x>m[0].x&&r[j].x<m[1].x&&r[j].y>m[0].y&&r[j].y<m[1].y)
				//这是一个条件语句，检查主角的顶点是否与地图元素相交
				{
	                mciSendString("play mymusic6 from 0", NULL, 0, NULL);
					temp.x=r[0].x-role.w/4;
			        temp.y=r[0].y-role.w/4;
					return 1;
				}
			}
		}
		if(i<20)
		{
	    	if(enemy[i].id==1)//这是一个条件语句，检查敌人的 id 是否为1，表示敌人存活
	    	{
	    		POINT e[2];

    			e[0].x=enemy[i].x;
    			e[0].y=enemy[i].y;

	    		e[1].x=enemy[i].x+role.w;
				e[1].y=enemy[i].y+role.h;

				for(int j=0;j<4;j++)// 这是一个循环结构，用于遍历主角四个顶点
			    {
				    if(r[j].x>e[0].x&&r[j].x<e[1].x&&r[j].y>e[0].y&&r[j].y<e[1].y)
					//这是一个条件语句，检查主角的顶点是否与敌人相交
			    	{
						
	                    mciSendString("play mymusic5 from 0", NULL, 0, NULL);
						score+=10;//将分数增加10
			    		temp.x=enemy[i].x;
			            temp.y=enemy[i].y;
						//这两行代码设置一个临时坐标 temp，用于特效的显示
			    		enemy[i].id=0;
		    			enemy[i].iframe=-1;
		    			enemy[i].turn=1;
		    			enemy[i].x=-1;
		    			enemy[i].y=-1;
						// 将敌人的相关属性重置，表示敌人被消灭
				    	return 1;
						//返回1，表示主角吃到了敌人
				    }
			    }
		    }
		}
	}
	return 0;
}
void game::end()
{
	MyTimer tt;//创建了一个名为 tt 的 MyTimer 对象，用于计时
	EndBatchDraw();//结束绘图批处理，可能用于绘制图形的显示效果
	if(isdie()==1||win==1)//:如果主角已死亡或者游戏胜利，且暂停标志为1，则将暂停标志设置为0，用于恢复游戏状态
		pause=0;
	if(pause==1)//如果暂停标志为1，则直接返回，不执行后续代码
		return;
	if(win==1)
		tt.Sleep(5000);
	else
		tt.Sleep(2700);
	mciSendString("close all", NULL, 0, NULL);	
	tt.Sleep(1000);
	
	if(win==1)//如果游戏胜利，将暂停标志、分数和生命值重置为0，可能用于游戏状态的初始化
	{
		pause=0;
		score=0;
		life=0;
		mciSendString("open 通关.mp3 alias mymusic13", NULL, 0, NULL);
	    mciSendString("play mymusic13", NULL, 0, NULL);
		putimage(0,-3*YSIZE,&img_home);
		tt.Sleep(7000);//延迟7000毫秒（7秒)
		mciSendString("close mymusic13", NULL, 0, NULL);//关闭胜利音乐
	}
	else//如果游戏未胜利，则执行下面的代码块
	{
		score=0;
		if(life==0)
		{
			mciSendString("open 游戏结束.mp3 alias mymusic12", NULL, 0, NULL);
	        mciSendString("play mymusic12", NULL, 0, NULL);
			putimage(0,-YSIZE,&img_home);
		    tt.Sleep(5500);
	        mciSendString("close mymusic12", NULL, 0, NULL);
		}
		else//清空屏幕，显示“生命还剩下”文字，并根据剩余生命值显示相应的数字，并延迟2000毫秒（2秒）
		{
			cleardevice();
			outtextxy(XSIZE/2-43,YSIZE/3,"生命还剩下:");
			if(life==1)
				outtextxy(XSIZE/2,YSIZE/2-20,"1");
			else if(life==2)
				outtextxy(XSIZE/2,YSIZE/2-20,"2");
			tt.Sleep(2000);
		}
	}
	cleardevice();// 清空屏幕
}
void main()
{
	game g;
	while(true)
	{
		g.start();
	    g.init();
		mciSendString("play mymusic1 repeat", NULL, 0, NULL);
	    g.show();
        g.move();
	    g.end();
	}
}
