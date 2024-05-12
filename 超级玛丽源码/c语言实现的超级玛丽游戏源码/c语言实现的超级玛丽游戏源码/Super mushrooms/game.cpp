//EasyX�����C++��ͼ�ο⣬���԰���C/C++��ѧ�߿�������ͼ�κ���Ϸ��̡�
//  ����,���Ի���EasyXͼ�ο�ܿ��ü���ͼ�λ�һ�����ӣ�����һ���ƶ���С�������Ա�д����˹���� ��̰���ߡ��ڰ����С��Ϸ��
#include <graphics.h>
//���ͷ�ļ�ͨ�������� C/C++ �н��м򵥵�ͼ�α��
//���ṩ��һЩ������ͼ�λ��ƺ������续�ߡ���Բ�������ɫ�ȣ��Լ�����ͼ�δ��ڵĺ������紴�����ڡ��رմ��ڵ�
#include <conio.h>
//���ͷ�ļ��ṩ��һЩ�����ڿ���̨�н�����������ĺ�������Ҫ������ַ����������������
//���а�����һЩ���ڿ��ƹ��λ�á������ı���ɫ���ӿ���̨�ж�ȡ�ַ��Ⱥ�����
#include<math.h>
//���� C/C++ ��׼���е���ѧ����ͷ�ļ����ṩ�˸�����ѧ�����������Ͷ��塣
//��������һϵ�г��õ���ѧ�����������Ǻ���������������ָ���������ݺ����ȡ�
//math.h �еĺ����������ڸ�����ѧ����Ϳ�ѧ���㣬����ֵ����������ѧ������ѧ������ļ��㡣
#include "MyTimer.h"               //һ����֤��ȷ��ʱ���ࡣ������easyx����
#pragma comment(lib,"Winmm.lib")   //����Ϸ�������Ҫ�õ���

#define G 9.8                      //�������ٶ�
#define XSIZE 512                  //��Ļ��С
#define YSIZE 384
#define X 64                       //������ʼλ��
#define Y 192
#define W 32                       //���ǵĿ�͸�
#define H 32
#define STEP 4                     //������һ���������ظ���
#define HIGH (2*role.w+1)          //������Ծ�����߶�
 
#define	CMD_LEFT 1                 //������ĺ궨��
#define	CMD_RIGHT 2	
#define	CMD_UP 4
#define CMD_DOWN 8
#define CMD_SHOOT 16
#define CMD_ESC 32
int life;                          //ȫ�ֱ��������ǹ��ж���������
int score;                         //ȫ�ֱ��������ǻ�õķ���
struct ROLE
{
	int id;
    int x;//������
    int y;//������
    int w;//ͼƬ���
    int h;//ͼƬ�߶�
    int xleft;//ˮƽ�˶�������� 
    int xright;//ˮƽ�˶����ҽ���
    int turn;//������˶�����
    int jump;//�����Ƿ���Ծ
    int iframe;//���صڼ�������ͼ�����������þ��鿴��ȥ��������
};
struct MAP        //�����ͼ�Ľṹ��
{
	int id;
	int x;
	int y;
};
struct BULLET      //�ӵ��Ľṹ��
{
	int x;
	int y;
	int turn;
	int iframe;
	int id;
};
struct COINT      //Ӳ�ҵĽṹ��
{
	int x;
	int y;
	double iframe;
};
struct ENEMY      //���˵Ľṹ��
{
	int id;
	int x;
	int y;
	int turn;
	int iframe;
};
class game        //������Ϸֻ��������һ����
{
private:
	ROLE role;
	MAP map[350];
	BULLET bullet[20];
	COINT coint[50];
	ENEMY enemy[20];
	IMAGE img_mapsky,img_p,img_map,img_ani,img_mapbk,img_home;
	int xmapsky;           //������յ���ʼ������
	int xmap;              //��ͼ����ʼ����
	double v0;             //������Ծ�ĳ��ٶ�             
	double h;              //������Ծ�ĸ߶�
	double t;              //������Ծ��ʱ��
	int ibullet;           //�ڼ����ӵ�
	int xbullet;           //�ӵ���x����
	int ybullet;           //�ӵ���y����
	int get_bullet;        //�Ƿ���������0��ʾû�л�ã�1��ʾ�ѻ��
	POINT icoint;          //����Ӳ�ҵ�����
	POINT bomb[20];        //������Щ�ط���ը�˵�����
	POINT temp;            //��ʱ���ꡣ������Щ�ط���ը�˵�����
	double score_frame;    //����3��double�͵ı������ڿ��Ƹ���ͼƬ��֡����ʵ�ֶ�����Ч�����续���е���ˮ
	double bomb_frame;
	double mapbk_frame;
	int win;               //����Ƿ����
	int pause;             //����Ƿ�Esc����ͣ����
public:
	game();
	~game();
	void start();          //������Ϸ��ʼ�Ľ��棬�Ͱ���ͣ����Ľ���
	void init();           //��ʼ���������
	void move();           //���������ƶ�
	void show();           //��ʾ����
	int isdie();           //�ж������Ƿ�����
	int  GetCommand();	   // ��ȡ�������
	void left();           //���������˶�
	void right();          //���������˶�
	void up();             //������Ծ
	void init_shoot();     //��ʼ�������ӵ�
	void fall();	       //���������������������Ծ
	int is_l_touch(int id);//���ǵ�����Ƿ�����ǽ����ˣ��Լ������Ƿ�����½�ص���߽�
	int is_r_touch(int id);//���ǵ��ұ��Ƿ�����ǽ����ˣ��Լ������Ƿ�����½�ص��ұ߽�
	int is_t_touch();      //���ǵ�ͷ�Ƿ�����ǽ
	int is_b_touch(int id);//�����Ƿ�ȵ����ˡ�
	int is_touch();        //�����Ƿ�Ե����
	int is_land(ENEMY e);  //�����Ƿ�վ��½����
	void getbullet();      //��ȡ�ӵ�
	void shoot();          //�����ӵ�
	int eat(BULLET b);     //�ӵ��Ƿ�򵽵��˻���ǽ��
	void end();            //������Ϸ����
};
game::game()
{
	initgraph(XSIZE,YSIZE);//XSIZE,YSIZEΪǰ��궨��õ�������
}
//���캯�� game::game() �ڶ��󱻴���ʱ����
// ���������ǳ�ʼ����Ϸ��ͼ�δ���
// ͨ�� initgraph(XSIZE, YSIZE) ����һ��ָ����С��ͼ�δ��ڣ�������ʾ��Ϸ����
game::~game()
{
	closegraph();
}
//�������� game::~game() �ڶ�������ʱ���ã����������ǹر���Ϸ��ͼ�δ���
// ͨ�� closegraph() �ر���Ϸ��ͼ�λ������ͷ������Դ��ȷ����Ϸ����ʱ��Դ�ܹ�����ȷ�ͷš�
void game::start()
{
	if(pause==1)//���������ͣ��
	{
		BeginBatchDraw(); //��ʼ�������ƣ�����߻���Ч��
		int points[8]={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3,XSIZE/2+45,YSIZE/3+90,XSIZE/2-45,YSIZE/3+90};
		setfillstyle(GREEN);//����һ�������˵�����ĸ��������������
		fillpoly(4, points);//ʹ��ָ���Ķ��������������һ�������ı��Σ�����ͣ�˵��ı�����
		setbkmode(TRANSPARENT);//�����ı�����ģʽΪ͸�����������Ƶ����ֱ����ͻ�͸�������Ḳ�Ǳ�����
		setfont(20,0,"����"); //���������СΪ 20��������ʽΪ��������������Ϊ����
    	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);
    	drawtext("�ص���Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//����һ������ r2�����ڰ������ص���Ϸ�����֣�������һ�����ο�
    	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);
        drawtext("���¿�ʼ", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//����һ������ r3�����ڰ��������¿�ʼ�����֣�������һ�����ο�
	    RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);
    	drawtext(" �� �� �� ", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//����һ������ r4�����ڰ��������˵������֣�������һ�����ο�
		FlushBatchDraw();
		//ˢ���������ƵĽ���������Ƶ�ͼ�κ�������ʾ����Ļ��
	    MOUSEMSG m;//����һ�� MOUSEMSG �ṹ����� m�����ڽ��������Ϣ��
    	while(true)// ����һ������ѭ�������ϼ�������¼�
    	{
			BeginBatchDraw();//��ʼ�������ƣ�����߻���Ч��
    		m=GetMouseMsg();//��ȡ�����Ϣ
    		switch(m.uMsg)//���������Ϣ���ͽ��з�֧����
            {
			case WM_LBUTTONDOWN://��������������ʱִ�����²�����
				EndBatchDraw();//�����������ƣ����Ƶ�ͼ�κ�������ʾ����Ļ��
				if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30)
    	     	    return;//��������λ���ڡ��ص���Ϸ����ť��Χ�ڣ��������ء�
    			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60)
    			{
					mciSendString("close all", NULL, 0, NULL);	
    				pause=0;
					score=0;
    				return;
     			}//��������λ���ڡ����¿�ʼ����ť��Χ�ڣ�ִ�йر�������Ƶ��ȡ����ͣ�����õ÷֣�Ȼ�󷵻ء�
    			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90)
				{
					mciSendString("close all", NULL, 0, NULL);	
					pause=0;
					score=0;
					life=0;
					cleardevice();
    				break;
				}
				//��������λ���ڡ����˵�����ť��Χ��
				// ִ�йر�������Ƶ��ȡ����ͣ�����õ÷֡�����Ϊ0�������Ļ���ݣ�Ȼ������ѭ����
    			else
    				break;
				//��������λ�ò����κΰ�ť��Χ�ڣ����� switch ��֧��Ȼ�������һ��ѭ����
			case WM_MOUSEMOVE://������ƶ�ʱִ�����²���
				RECT r;//����һ�����νṹ����� r�����ڱ�ʾ��ť������
				int i; //����һ�����ͱ��� i������ѭ������
				for(i=0;i<3;i++)//ѭ������������ť
				{
				    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+i*30&&m.y<YSIZE/3+30+i*30)
				    {
					    r.left=XSIZE/2-45;
					    r.top=YSIZE/3+i*30;
					    r.right=XSIZE/2+45;
					    r.bottom=YSIZE/3+30+i*30;
						int points[8]={r.left,r.top,r.right,r.top,r.right,r.bottom,r.left,r.bottom};
						//ѭ������������ť
					    setfillstyle(RED);
						//ʹ�� setfillstyle() ���������ɫΪ��ɫ
						fillpoly(4, points);
						//ʹ�� fillpoly() ��������һ���ı��Σ��ĸ��������������� points �ṩ
						setbkmode(TRANSPARENT);
						//ʹ�� setbkmode() �������ı�����ģʽ����Ϊ͸�����Ա��ı������ڲ��ܱ���ɫӰ����������ʾ
						switch(i)//���ݱ��� i ��ֵ���в�ͬ�Ĳ���
						{
						case 0:
						    drawtext("�ص���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						    break;
							//ʹ�� drawtext() �����ھ��� r �����Ļ����ı� "�ص���Ϸ"���ı�ˮƽ�ʹ�ֱ���У�������ʾ��
						case 1:
						    drawtext("���¿�ʼ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//ʹ�� drawtext() �����ھ��� r �����Ļ����ı� "���¿�ʼ"���ı�ˮƽ�ʹ�ֱ���У�������ʾ��
						case 2:
						    drawtext(" �� �� �� ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
							//ʹ�� drawtext() �����ھ��� r �����Ļ����ı� " �� �� �� "���ı�ˮƽ�ʹ�ֱ���У�������ʾ��
						}
					}
				    else
				    {
						if(getpixel(XSIZE/2-45+1,YSIZE/3+i*30+1)==RED)
						//��鰴ť�����ڵ�������ɫ�Ƿ�Ϊ��ɫ�� getpixel�������ڻ�ȡָ��λ�õ�������ɫ
						//(XSIZE/2-45+1,YSIZE/3+i*30+1) �ǰ�ť�����ڵ�һ���㣬ͨ�����Һ������ƶ�һ�����أ���ȷ�����ĵ��ڰ�ť�ڲ���
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
				    		    drawtext("�ص���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 1:
				    			drawtext("���¿�ʼ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 2:
				    			drawtext(" �� �� �� ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
							}
							//���þ��� r ��λ�á�
							//ʹ�� setfillstyle() ���������ɫΪ��ɫ��
							//fillpoly() ����������ɫ��ť��
							//ʹ�� setbkmode() �������ı�����ģʽ����Ϊ͸����
							//���ݰ�ť������ѡ��ͬ���ı����ݣ�ʹ�� drawtext() �������»��ư�ť�ϵ��ı���
						}
						FlushBatchDraw();//ˢ�»��ƽ�������仯��İ�ť��ʾ����Ļ��
					}
				}
			}
			if(pause==0)
				break;
			//if(pause==0) break;�������Ϸ��ͣ״̬Ϊ 0��δ��ͣ����������ѭ��
		}
	}
	if(life==1||life==2)
		return;
	life=3;
	score=0;
	setfont(40,0,"��������");	// ���������СΪ40��������ʽΪ���������塱
	RECT r1 = {0, 0, XSIZE, YSIZE/3};//����һ�����νṹ����� r1��������ʾ��������
	drawtext("����Ģ��", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE); //�ڱ����������Ļ����ı�������Ģ������
	setfont(20,0,"����");//���������СΪ20��������ʽΪ�����塱
	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);
	drawtext("��ʼ��Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);
    drawtext("��Ϸ����", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);
	drawtext("����˵��", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5={XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120};rectangle(XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120);
	drawtext("�˳���Ϸ", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//���岢�����ĸ���ť�����ı���
	//  ��ʼ��Ϸ��ť
	//	��Ϸ���ܰ�ť
	//	����˵����ť
	//	�˳���Ϸ��ť
	int flag1=1,flag2=0,flag3=0;
	//���岢��ʼ����־���� flag1=1,flag2=0,flag3=0�����ڿ��ƽ����״̬
	MOUSEMSG m;
	while(flag1==1)//����ѭ�������������Ϣ
	{
		BeginBatchDraw();
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:// ���������������¼�
			EndBatchDraw();//���������λ�úͰ�ť״ִ̬����Ӧ�Ĳ�����
		    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30&&flag1==1&&flag2==0&&flag3==0)
		    {
				flag1=0;
				break;
			}//���������ǿ�ʼ��Ϸ��ť���������Ϸ
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60&&flag1==1&&flag3==0)
			{
			    flag2=1;
				cleardevice();
				rectangle(50,50,213,220);
				outtextxy(52,52,"��Ϸ���ܣ�");
				outtextxy(52,82,"����������");
				outtextxy(52,102,"����Ģ��");
				outtextxy(52,132,"�����ߣ�");
				outtextxy(52,152,"czxczx");
				RECT R1={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);
	            drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}//������������Ϸ���ܰ�ť������ʾ��Ϸ����
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90&&flag1==1&&flag2==0)
			{
				flag3=1;
				cleardevice();
				rectangle(50,50,213,220);
				outtextxy(52,52,"����˵����");
				outtextxy(52,72,"���ƣ�A��");
				outtextxy(52,92,"���ƣ�D��");
				outtextxy(52,112,"���䣺J��");
				outtextxy(52,132,"��Ծ��W��/K��");
				outtextxy(52,152,"��ͣ��Esc��");
				RECT R2={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);
	            drawtext("����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;//���������ǲ���˵����ť������ʾ��Ϸ����˵��
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
			    break;//�����������˳���Ϸ��ť�����˳���Ϸ
		case WM_MOUSEMOVE://���������ƶ��¼�����������ƶ�λ�úͰ�ť״̬�ı䰴ť����ɫ�Լ���ʾ״̬
			RECT r;//������νṹ����� r ���ڱ�ʾ��ť������
			if(flag2==1||flag3==1)//��鵱ǰ�����״̬�����������Ϸ���ܻ����˵��״̬�������ذ�ť����ɫ����ʾ״̬
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
					drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}//������λ�ڷ��ذ�ť�������ڣ�����ť���Ϊ��ɫ����ʾ�ı������ء�
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
					    drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}//����������ذ�ť֮ǰ�Ѿ�������Ϊ��ɫ���������Ϊ��ɫ���������ɫ������Ȼ����ʾ�ı������ء�
			}
			else//�����������Ϸ���ܻ����˵��״̬������ʼ��Ϸ����Ϸ���ܡ�����˵�����˳���Ϸ��ť����ɫ����ʾ״̬��
			{
			    for(int i=0;i<4;i++)
				{
					//����ÿ����ť��������λ�ڰ�ť�������ڣ�����ť���Ϊ��ɫ����ʾ��Ӧ���ı���
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
						    drawtext("��ʼ��Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						    break;
						case 1:
						    drawtext("��Ϸ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
						    drawtext("����˵��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
					   	case 3:
							drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					//���������ť֮ǰ�Ѿ�������Ϊ��ɫ���������Ϊ��ɫ���������ɫ������Ȼ����ʾ��Ӧ���ı�
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
				    		    drawtext("��ʼ��Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 1:
				    			drawtext("��Ϸ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 2:
				    			drawtext("����˵��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    	   	case 3:
				    			drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
							}
						}
					}
				}
			}
			FlushBatchDraw(); //ˢ�»�ͼ���������ť�ı仯��ʾ����Ļ��
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
	//���ȼ�� pause �Ƿ�Ϊ 1������ǣ����ʾ��Ϸ������ͣ״̬������ֱ�ӷ��ء�

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
	//������������Ϸ��ɫ�ĳ�ʼ���ԣ�������ɫ��λ�� (x, y)����С (w, h)���Լ�����������ԡ�

	xmapsky=0;//������ձ���ͼ�� x ����ƫ����Ϊ 0������ʼ�������ձ���ͼ��ƫ��
	xmap=0;//���õ�ͼ�� x ����ƫ����Ϊ 0������ʼ����µ�ͼ��ƫ��
	v0=0;//���ó�ʼ�ٶ�Ϊ 0����������ڿ��ƽ�ɫ��������ϷԪ�ص��ƶ��ٶ�
	h=0;//���ø߶�Ϊ 0���������һ����ʱ���������ڼ����ɫ����Ծ�߶Ȼ�������Ϸ�еĸ߶���صı�����
	t=0;//����ʱ��Ϊ 0������������ڼ�ʱ������ʱ����ص���Ϸ���Ƶı���
	ibullet=-1;//����ǰ�ӵ���������Ϊ -1����ʾ��ʼ�����û���κ��ӵ�
	icoint.x=-1;//����ҵ�������������Ϊ (-1, -1)����ʾ��ʼ�����û�н��
	icoint.y=-1;
	score_frame=0; //���õ÷�֡��Ϊ 0���������ڿ��Ƶ÷ֶ����Ĳ���
	bomb_frame=1;//����ը��֡��Ϊ 1���������ڿ���ը�������Ĳ���
	mapbk_frame=1;// ���õ�ͼ����֡��Ϊ 1���������ڿ��Ƶ�ͼ���������Ĳ���
	temp.x=-1;// ����ʱ���� temp ����������Ϊ (-1, -1)����ʾ��Ŀǰû����Чֵ
	temp.y=-1;
	xbullet=41*role.w-10;//�����ӵ��ĳ�ʼλ�����꣬���������Ϸ�н�ɫ�����ӵ��ĳ�ʼλ��
	ybullet=4*role.h-25;
	get_bullet=0; //����ȡ���ӵ���������Ϊ 0����ʾ��ʼ��������û�л���κ��ӵ�
	win=0;//����Ϸʤ��״̬����Ϊ 0����ʾ��Ϸ��δʤ��
	pause=0;//����ͣ״̬����Ϊ 0����ʾ��Ϸ��ʼʱ��������ͣ״̬
	score=0;//���÷�����Ϊ 0����ʾ��ʼʱ��ҵĵ÷�Ϊ 0
	//������������Ϸ��ɫ�ĳ�ʼ���ԣ�������ɫ��λ�� (x, y)����С (w, h)���Լ�����������ԡ�

	int i;
	for(i=0;i<350;i++)
    {
		map[i].id=0;//����ͼ�����е� i ��Ԫ�ص� id ��������Ϊ 0����ʾ��λ�õĵ�ͼԪ��Ϊ��
		map[i].x=-1;//����ͼ�����е� i ��Ԫ�ص� x ������������Ϊ -1����ʾ��λ�õĵ�ͼԪ�ص� x ����δ����򲻿���
		map[i].y=-1;//����ͼ�����е� i ��Ԫ�ص� y ������������Ϊ -1����ʾ��λ�õĵ�ͼԪ�ص� y ����δ����򲻿��á�
		if(i<50)
		{
			coint[i].x=-1;
			coint[i].y=-1;
			coint[i].iframe=1;
		}
		// ��� i С�� 50���򽫽�������е� i ����ҵ� x��y �������Զ�����Ϊ -1����ʾ��λ��û�н�ң�
		// �����ý�ҵ� iframe ��������Ϊ 1�����ܱ�ʾ��Ҵ��ڳ�ʼ״̬��
		if(i<20)//��� i С�� 20������ӵ������˺�ը�������е�Ԫ�ؽ������Ƶĳ�ʼ������
		{
			bullet[i].id=0;//���� i ���ӵ��� id ��������Ϊ 0����ʾ��λ��û���ӵ�
			bullet[i].x=-1;//���� i ���ӵ��� x��y �������Զ�����Ϊ -1����ʾ��λ�õ��ӵ�δ����򲻿���
	        bullet[i].y=-1;
	        bullet[i].iframe=1;//���� i ���ӵ��� iframe ��������Ϊ 1�����ܱ�ʾ�ӵ����ڳ�ʼ״̬
	        bullet[i].turn=-1;  //����ͨ��������ʾ�ӵ����˶�����

			enemy[i].id=0;
   			enemy[i].x=-1;
	        enemy[i].y=-1;
         	enemy[i].turn=1;
	        enemy[i].iframe=1;

			bomb[i].x=-1;
			bomb[i].y=-1;

			//�Ե��˺�ը�������Ԫ��Ҳ�������Ƶĳ�ʼ�������������ǵ���������Ϊ��ʼֵ
	 	}
	}
	//��ʼ����ͼ����ҡ��ӵ������˵���ϷԪ�ص����ԡ�

	loadimage(&img_mapsky,"res\\mapsky.bmp",XSIZE,YSIZE*4);
	loadimage(&img_p,"res\\role.bmp");
	loadimage(&img_map,"res\\map.bmp");
	loadimage(&img_ani,"res\\ani.bmp");
	loadimage(&img_mapbk,"res\\mapbk.bmp");
	loadimage(&img_home,"res\\home.bmp",XSIZE,YSIZE*5);
	//������Ϸ�����ͼƬ��Դ��

    mciSendString("open ��������.mp3 alias mymusic1", NULL, 0, NULL);
	mciSendString("open �ӵ�.mp3 alias mymusic2", NULL, 0, NULL);
	mciSendString("open ���.mp3 alias mymusic3", NULL, 0, NULL);
	mciSendString("open ��.mp3 alias mymusic4", NULL, 0, NULL);
	mciSendString("open �ӵ��򵽵���.mp3 alias mymusic5", NULL, 0, NULL);
	mciSendString("open �ӵ�ײǽ.mp3 alias mymusic6", NULL, 0, NULL);
	mciSendString("open �ȵ���.mp3 alias mymusic7", NULL, 0, NULL);
	mciSendString("open �Ե�����.mp3 alias mymusic8", NULL, 0, NULL);	
	mciSendString("open ʤ��.mp3 alias mymusic9", NULL, 0, NULL);
	mciSendString("open ����1.mp3 alias mymusic10", NULL, 0, NULL);
	mciSendString("open ����2.mp3 alias mymusic11", NULL, 0, NULL);
	//��ʼ��������Դ��               


	for(i=0;i<300;i++)                 //���¶��Ǳ༭��ͼ
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
	//�༭��ͼ�����õ�ͼ�е��ϰ��

	map[15].id=1,map[15].x=18*role.w,map[15].y=8*role.h;
	map[115].id=1,map[115].x=19*role.w,map[115].y=8*role.h;
	map[215].id=1,map[215].x=20*role.w,map[215].y=8*role.h;

	//�ڵ�ͼ�е��ض�λ��������һЩ��ͼԪ�أ��������һЩ�ϰ��������Ԫ�أ�
	// ��ЩԪ�ؿ��ܶ���Ϸ��ɫ���ƶ��ͽ�������Ӱ��
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
	//��ʼ����һЩ���˵�λ�á������Լ��Ƿ��ڶ���֡��


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
	//���ý�ҵ�λ�á�

}
void game::move()
{	
	MyTimer tt;//������һ����ʱ���������ڿ�����Ϸѭ�����ٶ�
	int c;//����һ���������ڴ洢�Ӽ������������
	int k=0;                              //���Ʒ����ӵ���Ƶ�ʺ͵��˵��ƶ��ٶ�
	int n=0;                              //���Ʒ����ӵ���Ƶ��
	while(true)//������Ϸ��ѭ����ֱ����Ϸ�������˳�
	{
		tt.Sleep(25);//������Ϸѭ��ÿ��ִ�е�ʱ������������Ϸ��֡��
		t=sqrt(2*HIGH/G)/14; //���ݽ�ɫ��Ծ������ģ�ͣ��������ɫ����ߵ��䵽�����ʱ�䡣
		k++;//���������������ڿ����ӵ�����Ƶ�ʺ͵��˵��ƶ��ٶ�
		if(k==1000)
	    	k=0;//���������������ڿ����ӵ�����Ƶ�ʺ͵��˵��ƶ��ٶ�
		if(kbhit()&&win==0)//���������룬������Ϸ��δ����ʱִ�м��̿��Ƶ��߼�
		{
			c=GetCommand();//��ȡ�������������
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
			if(c&CMD_SHOOT&&get_bullet==1)////����Ƿ��������������������ӵ���ӵ���get_bulletΪ1��
			{
				if(n==0)
			    {
			    	init_shoot();
			    	n=1;
			    }
				//��� n ����0�����տ�ʼ������������ init_shoot() ������ʼ�����������ͬʱ�� n ��Ϊ1
				n++;
				if(k%10==0&&n>10)
			    {
			    	init_shoot();
			    }//ÿ�ΰ����������n ֵ��1������������� k%10==0 ���� n ����10�����ٴε��� init_shoot() �������������ʵ��һ�������Ƶ��
			}
			else
			    n=0;
			//���򣬽� n ��Ϊ0����ʾ�����������
		}
		if(-xmap+role.x==97*role.w)//����ɫ�����ض�λ��ʱ������Ӧ������
		{
		    mciSendString("stop mymusic1", NULL, 0, NULL);
			mciSendString("play mymusic9", NULL, 0, NULL);
		}
		if(-xmap+role.x>95*role.w)
		{
			
            win=1;//��Ϸʤ��
			role.x+=STEP;//����ɫ��ǰ�ƶ�һ������(STEP)�ľ���
			if(role.x-STEP>XSIZE)//�����ɫ��x�����ȥ�����󳬹�����Ļ�Ŀ��(XSIZE)�����˳�ѭ����������Ϸ
				break;
		}
		if(is_b_touch(1)==0)//����Ƿ��е���֧�ţ����û�У��򽫽�ɫ��jump��־����Ϊ1����ʾ��ɫ������Ծ״̬
			role.jump=1;
		if(role.jump==1)//����ɫ�Ƿ�����Ծ״̬������ǣ���ִ�� fall() ������ʵ�ֽ�ɫ������
			fall();
		if(isdie()==1)
		{
			mciSendString("stop mymusic1", NULL, 0, NULL);
			mciSendString("play mymusic11", NULL, 0, NULL);
			life--;//��������ֵ
			return;	
		}
		//���˵��˶�
		if(k%2==0)//������ k �Ƿ�Ϊż�����������ÿ��һ����ʱ��ִ��һ�ε��˵��˶��߼�
		{
	    	for(int i=0;i<20;i++)//����ÿһ�����ˣ��ظ����²���
	    	{
		    	if(enemy[i].id==1)//��鵱ǰ�����Ƿ����
		    	{
		            if(is_land(enemy[i])==1)//��鵱ǰ�����Ƿ���ڣ�����ǣ�ִ�����²�����
		            {
		    	        if(enemy[i].turn==1)//������˵ķ���Ϊ���ң��������ƶ�һ������(STEP)
			    	        enemy[i].x+=STEP;
			            else//���������ƶ�һ������(STEP)
				            enemy[i].x-=STEP;
			    	}
		            if(is_land(enemy[i])==0||is_l_touch(3)==1||is_r_touch(3)==1)
					//������˲��ڵ����ϣ����ߵ��˴������������Ҳ���ϰ����ִ�����²���
		            {
		            	if(enemy[i].turn==1)//������˵ķ���Ϊ���ң��������ƶ�һ������(STEP)
		            		enemy[i].x-=STEP;
		            	else//���������ƶ�һ������(STEP)
		            		enemy[i].x+=STEP;
		            	enemy[i].turn*=-1;//�����˵ķ���ȡ�����ı���˵��ƶ�����
		            }
				    enemy[i].iframe*=-1;//�ı���˵Ķ���֡����ʵ�ֶ���Ч��
			    }
	    	}
		}
		int boom=0;
		if(is_b_touch(2)==1)                     //������ǡ��ȵ�������
			boom=1;
		getbullet();                             //��ȡ�ӵ�
		if(get_bullet==1)
			shoot();

		BeginBatchDraw();// ��ʼ�������ƣ������Ż���������
		show();//չʾ��Ϸ����
		FlushBatchDraw();//ˢ���������Ƶ����ݵ���Ļ��

		if((is_l_touch(2)==1||is_r_touch(2)==1))
		//��������Ƿ�����˷�������ײ�����������Ƿ������˵�ͼ�е��ϰ��
		// ���������������ʾ�����������˺���ִ�����²�����
		{
			mciSendString("stop mymusic1", NULL, 0, NULL);//ֹͣ��ǰ���ŵı�������
			mciSendString("play mymusic10", NULL, 0, NULL);//������һ��������Ϊ���˵���Ч
			life--;//�������ǵ�����ֵ(life)
			pause=0;//����ͣ��־(pause)����Ϊ0����ʾ��Ϸ��������ͣ״̬
			//��������λ�ã��������ǵ�ͼ����ʾ����չʾ����Ч��
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
    putimage(xmapsky,0,&img_mapsky);     //��ʾ����
	//����Ϸ���ڵ������Ʊ���ͼ��xmapsky �����˱���ͼ�ĺ���ƫ�ƣ�ʹ�����Ž�ɫ���ƶ�������
	putimage(XSIZE+xmapsky,0,&img_mapsky);
	//����Ϸ���ڵ��Ҳ���Ʊ���ͼ����ʵ���޷������Ч��

	if(is_touch()==1)//����Ƿ���Ӳ�ҷ�������ײ�������ײ�ˣ��� score_frame ����Ϊ1��
		score_frame=1;
	if(score_frame!=0)                  //����Ӳ�ң���ʾ�÷�
	//����Ƿ���Ӳ�ҷ�������ײ�������ײ�ˣ��� score_frame ����Ϊ1��
	{		
		// ���� score_frame ��ֵ��ʹ�� switch �����������ǰ���ŵ�����һ֡��Ӳ�Ҷ�����
		// ���ݲ�ͬ��֡����������Ӧ��Ӳ�Ҷ���
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
		//��������Ӳ�Ҷ���֡�Ĳ��š�ÿ��ִ����һ֡������score_frame ��ֵ������0.2
		// �������Կ��ƶ����Ĳ����ٶ�
		// �� score_frame ��ֵ�ﵽ5ʱ����ʾ�Ѿ����������е�Ӳ�Ҷ���֡
		// ��ʱ�� score_frame ����Ϊ0����ʵ�ֶ�����ѭ������
	}
	int i;
	for(i=0;i<350;i++)             //��ʾ��ͼ������ϵĵ�ͼ��Ӳ��
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
	for(i=0;i<20;i++)             //��ʾ�ӵ�
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
	    	if(enemy[i].iframe==1)                           //��ʾ����
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
	char s1[20]="��ǰ�÷֣�";
	char s2[10];
	itoa(n,s2,10);
	RECT r1={10,10,110,40};
	RECT r2={110,10,150,40};
	setfont(20, 0,"����");
	drawtext(s1, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(s2, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	if(role.iframe==1)                           //��ʾ����
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
}//���������Ҫ���ڼ���ɫ�Ƿ��Ѿ���������Ϸ��ͼ�ĵײ�����������ˣ�����Ϊ��ɫ����
int game::GetCommand()//��������������ǻ�ȡ�������Ϸ������������һ����������ʽ����
{
	int c = 0;
	//���ȣ�����һ�����ͱ���c�����ڴ洢�����״̬����ʼֵΪ0
	if (GetAsyncKeyState('A') & 0x8000)
		c |= CMD_LEFT;
	//������¼����ϵ�'A'����c�ĵ�һλ��������������������Ϊ1����ʾ��������
	if (GetAsyncKeyState('D') & 0x8000)
    	c |= CMD_RIGHT;
	//������¼����ϵ�'D'����c�ĵڶ�λ������Ϊ1����ʾ��������
	if ((GetAsyncKeyState('W') & 0x8000)||(GetAsyncKeyState('K') & 0x8000))
    	c |= CMD_UP;
	//������¼����ϵ�'W'������'K'����c�ĵ���λ������Ϊ1����ʾ�����ƶ�������
	if (GetAsyncKeyState('S') & 0x8000)
    	c |= CMD_DOWN;
	//������¼����ϵ�'S'����c�ĵ���λ������Ϊ1����ʾ�����ƶ�������
	if (GetAsyncKeyState('J') & 0x8000)
    	c |= CMD_SHOOT;
	//������¼����ϵ�'J'����c�ĵ���λ������Ϊ1����ʾ�������
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    	c |= CMD_ESC;
	//������¼����ϵ�'ESC'����c�ĵ���λ������Ϊ1����ʾ�˳�����
	return c;
	//��󣬷�������c�����а�������ҵ�ǰ����������״̬
}
void game::left()
{
	role.iframe*=-1;//����ɫ��iframe����-1�����������ڵ�����ɫ�Ķ���֡���Է�ӳ�����ƶ��Ķ���	
	role.turn=-1;//���ý�ɫ��turn����Ϊ-1������������ָʾ��ɫ�ĳ���-1��ʾ����
	role.x-=STEP;
	//����ɫ�ĺ������ȥһ��Ԥ��ĳ���STEP����ʾ�����ƶ�һ������
	if(is_l_touch(1)==1)
	//�����ɫ���ͼ���������巢������ײ��is_l_touch(1)==1����
	// �򽫽�ɫ�ĺ��������¼���һ����������ȡ���ƶ����Ա��⴩ǽ
		role.x+=STEP;	
	if(role.x<role.xleft)
      	role.x+=STEP;
	//�����ɫ�ĺ�����С�ڹ涨����߽磨role.xleft��
	// �򽫽�ɫ�ĺ��������¼���һ��������ͬ����Ϊ�˱���Խ��
}
void game::right()
{
	role.iframe*=-1;	
	role.turn=1;
	role.x+=STEP;
	
	if(is_r_touch(1)==1)
	//�����ɫ���ͼ���������巢������ײ��is_r_touch(1)==1�����򽫽�ɫ�ĺ��������¼�ȥһ����������ȡ���ƶ�
		role.x-=STEP;
	if(role.x>role.xright&&(-xmap+role.x<90*role.w))
	//�����ɫ�ĺ�������ڽ�ɫ���ұ߽磨role.xright��
	// ���ҽ�ɫ��λ�����ͼ����߽粻��90����ɫ��ȣ� - xmap + role.x < 90 * role.w��
	// ��������²�����
	{
    	role.x-=STEP;//����ɫ�ĺ��������¼�ȥһ����������ȡ���ƶ����Ա���Խ��
		xmapsky-=1;//ͬʱ����xmapsky��ȥ1�����������ڿ�����Ϸ�е���ձ������ƶ�
	    xmap-=STEP;//��xmap��ȥһ�����������������ڿ�����Ϸ��ͼ�Ĺ���Ч��
	}
}
void game::up()
{
	mciSendString("play mymusic4 from 0", NULL, 0, NULL);
	role.iframe*=-1;	
	v0=-sqrt(2*G*HIGH);//��һ�м�����һ����Ϊ v0 �ı�����ֵ
	role.jump=1;//��һ�н� role �����е���һ����Ա���� jump ��ֵ����Ϊ 1
}
void game::init_shoot()
{
	mciSendString("play mymusic2 from 0", NULL, 0, NULL);
	ibullet++;//���д���������һ����Ϊ ibullet �ı�����ֵ�������������ӵ�������
	if(ibullet==20)
	// ������������ ibullet ��ֵ�Ƿ�ﵽ�����ޣ�20��
	// ����ǣ��ͽ�������Ϊ0��������������Ϊ��ѭ�������ӵ����飬��������Խ��
		ibullet=0;
	bullet[ibullet].id=1;
	// ���д��뽫һ����Ϊ bullet ���������ض��������� id ��Ա����Ϊ1����������ڱ�ʶ��ͬ���͵��ӵ�
	bullet[ibullet].y=role.y+8;
	//���д����������ض��������ӵ��� y ���꣬�ǻ��ڽ�ɫ��λ�ý������õ�
    bullet[ibullet].turn=role.turn;
	//���д����������ض��������ӵ��� turn ��Ա���Ǹ��ݽ�ɫ�ĳ���������õ�
	if(bullet[ibullet].turn==1)
	//���д�����ݽ�ɫ�ĳ����������ض��������ӵ��� x ���ꡣ
	// �����ɫ����Ϊ1�����ڽ�ɫ���ұߣ�role.x+10��������������
		bullet[ibullet].x=role.x+10;
	else
	//��������������һ����֧�������ɫ�ĳ�����1���������ӵ��� x ����Ϊ��ɫ�����
		bullet[ibullet].x=role.x-26;
}
int game::is_l_touch(int id)
{
	int x,y;
	int i;
	if(id==1)                                    //id==1��ʾ�����Ƿ�����idΪ1�ĵ�ͼ������Ϸ�л�ɫ�ĵ�ͼ
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
   	else if(id==2)                                 //id==2��ʾ�����Ƿ��������˵����
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
	else                                        //id==3��ʾ�����Ƿ�������ͼ�����
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
	POINT r[2];//���ﶨ����һ�� POINT ���͵����� r�����ڴ洢���˵������ױߵ�����
	r[0].x=e.x;
	r[0].y=e.y+role.h;
	// �����д��뽫���˵����½Ǻ����½ǵ�����洢������ r �ĵ�һ��Ԫ���У����� role.h ���ܱ�ʾ���ǵĸ߶�
	r[1].x=e.x+role.h;
	r[1].y=e.y+role.h;
	//�����д��뽫���˵����½ǵ�����洢������ r �ĵڶ���Ԫ����
	for(int i=0;i<350;i++)
	{
		if(map[i].id!=0&&map[i].id<4)
		//: ����һ��������䣬����ͼԪ�ص� id �Ƿ�Ϊ0��С��4��
		// ������������ų��հ����򣬲��ҿ��ܱ�ʾ�ض����͵ĵ�ͼԪ��
		{
			POINT m[3];//���ﶨ����һ�� POINT ���͵����� m�����ڴ洢��ͼԪ�ص��������������

			m[0].x=map[i].x;
			m[0].y=map[i].y;
			//�����д��뽫��ͼԪ�صĵ�һ���������洢������ m �ĵ�һ��Ԫ����
			m[1].x=map[i].x+role.w;
			m[1].y=map[i].y;
			//�����д��뽫��ͼԪ�صĵڶ����������洢������ m �ĵڶ���Ԫ���У����� role.w ���ܱ�ʾ���ǵĿ��
			m[2].x=map[i].x;
			m[2].y=map[i].y+role.h;
			//�����д��뽫��ͼԪ�صĵ������������洢������ m �ĵ�����Ԫ���У����� role.h ���ܱ�ʾ���ǵĸ߶�
			if(e.turn==1)
			{
				if((r[1].x-m[0].x)/role.w==0&&r[1].y>=m[0].y&&r[1].y<m[2].y)
			    	return 1;
			}
			//����һ��������䣬�����˵ĳ����Ƿ�Ϊ1�������1��ִ�е�һ������飻����ִ�еڶ��������
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
	POINT r[2];//���ﶨ����һ�� POINT ���͵����� r�����ڴ洢���ǵ������Խǵ������
	r[0].x=-xmap+role.x;
	r[0].y=role.y;
	r[1].x=-xmap+role.x+role.w;
	r[1].y=role.y+role.h;

	POINT b[4];//���ﶨ����һ�� POINT ���͵����� b�����ڴ洢�ӵ����ĸ����������
	b[0].x=xbullet;
	b[0].y=ybullet;

	b[1].x=xbullet+52;
	b[1].y=ybullet;

	b[2].x=xbullet;
	b[2].y=ybullet+25;

	b[3].x=xbullet+52;
	b[3].y=ybullet+25;
	
	for(i=0;i<4;i++)//���ڱ����ӵ����ĸ�����
	{
		if(b[i].x>=r[0].x&&b[i].y>=r[0].y&&b[i].x<=r[1].x&&b[i].y<=r[1].y)//����ӵ��Ƿ�λ�����ǵİ�Χ����
		{
			mciSendString("play mymusic8 from 0", NULL, 0, NULL);
			get_bullet=1;//���д��뽫һ����Ϊ get_bullet �ı�������Ϊ1����ʾ���ǻ�ȡ�����ӵ�
			//�����д��뽫�ӵ�����������Ϊ0�����ܱ�ʾ�ӵ���ʧ��
			xbullet=0;
			ybullet=0;
		}
	}
}
void game::fall()           
{

	h=v0*t+G*pow(t,2)/2;
	//���д��������������ʱ�� t �ڵĴ�ֱλ�ƣ��������������˶��Ĺ�ʽ��
	// h ��λ�ƣ�v0 �ǳ�ʼ�ٶȣ�G ���������ٶ�
    role.y+=(int)(h+0.5);
	// ���д�����ݼ���õ���λ�ƣ����������ǵ�����λ�á�(int)(h+0.5) �������ǽ���������������Ϊ����
	if(v0>=0)   //��������
	{
		if(isdie()==1)
			return;    
		if(is_b_touch(1)==1)//������ǲȵ�����
		{
			v0=0; //������ǲȵ����ˣ������ǵ��ٶ���Ϊ0����ʾֹͣ����
			role.y=role.y/role.h*role.h;//�����ǵ����������Ϊ����ĸ߶ȣ�ʹ������ڵ�����
			role.jump=0;
		}
	}
	else       //������Ծ
	{
		if(v0>=0)
			h=0;
		else
			role.y+=(int)(h+0.5);
		//������ǵ��ٶȴ��ڵ���0��������Ծ������λ�� h ��Ϊ0����������������ǵ�����λ��
		if(is_t_touch()==1)
		{
			v0=0;//��������������ײ�������ǵ��ٶ���Ϊ0����ʾֹͣ����
			h=0;//��������붥����ײ����λ�� h ��Ϊ0����ʾֹͣ�����ƶ�
			role.y=role.y/role.h*role.h+role.h;//�����ǵ����������Ϊ�붥�����룬ʹ������ڶ����Ϸ�
		}
	}
	v0=v0+G*t;//�������������˶��Ĺ�ʽ���������ǵ��ٶȡ�����ǰ�ٶȼ����������ٶȳ���ʱ�� t
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
	POINT r[4];//���ﶨ����һ�� POINT ���͵����� r�����ڴ洢�����ĸ����������
	r[0].x=-xmap+b.x+role.w/2;
	r[0].y=b.y;
	//�����д��뽫���ǵ����Ͻǵ�����洢������ r �ĵ�һ��Ԫ���У�b.x �� b.y ��ʾ�ӵ��ĺ�������
	// role.w ���ܱ�ʾ���ǵĿ��
	r[1].x=-xmap+b.x+role.w;
	r[1].y=b.y;
	//�����д��뽫���ǵ����Ͻǵ�����洢������ r �ĵڶ���Ԫ����
	r[2].x=-xmap+b.x+role.w/2;
	r[2].y=b.y+role.h/2;
	//�����д��뽫���ǵ����½ǵ�����洢������ r �ĵ�����Ԫ���У�role.h ��ʾ���ǵĸ߶�
	r[3].x=-xmap+b.x+role.w;
	r[3].y=b.y+role.h/2;
	// �����д��뽫���ǵ����½ǵ�����洢������ r �ĵ��ĸ�Ԫ����
	int i;
	for(i=0;i<350;i++)
	{
		if(map[i].id!=0&&map[i].id<4)
		// ����һ��������䣬����ͼԪ�ص� id �Ƿ�Ϊ0��С��4��
		// ������������ų��հ����򣬲��ҿ��ܱ�ʾ�ض����͵ĵ�ͼԪ��
		{
			POINT m[2];
			// ���ﶨ����һ�� POINT ���͵����� m�����ڴ洢��ͼԪ�ص��������������
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
			// ����һ��������䣬����ͼԪ�ص� id �Ƿ�Ϊ3�������3��ִ�е�һ������飻����ִ�еڶ��������
			for(int j=0;j<4;j++)// ����һ��ѭ���ṹ�����ڱ��������ĸ�����
			{
				if(r[j].x>m[0].x&&r[j].x<m[1].x&&r[j].y>m[0].y&&r[j].y<m[1].y)
				//����һ��������䣬������ǵĶ����Ƿ����ͼԪ���ཻ
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
	    	if(enemy[i].id==1)//����һ��������䣬�����˵� id �Ƿ�Ϊ1����ʾ���˴��
	    	{
	    		POINT e[2];

    			e[0].x=enemy[i].x;
    			e[0].y=enemy[i].y;

	    		e[1].x=enemy[i].x+role.w;
				e[1].y=enemy[i].y+role.h;

				for(int j=0;j<4;j++)// ����һ��ѭ���ṹ�����ڱ��������ĸ�����
			    {
				    if(r[j].x>e[0].x&&r[j].x<e[1].x&&r[j].y>e[0].y&&r[j].y<e[1].y)
					//����һ��������䣬������ǵĶ����Ƿ�������ཻ
			    	{
						
	                    mciSendString("play mymusic5 from 0", NULL, 0, NULL);
						score+=10;//����������10
			    		temp.x=enemy[i].x;
			            temp.y=enemy[i].y;
						//�����д�������һ����ʱ���� temp��������Ч����ʾ
			    		enemy[i].id=0;
		    			enemy[i].iframe=-1;
		    			enemy[i].turn=1;
		    			enemy[i].x=-1;
		    			enemy[i].y=-1;
						// �����˵�����������ã���ʾ���˱�����
				    	return 1;
						//����1����ʾ���ǳԵ��˵���
				    }
			    }
		    }
		}
	}
	return 0;
}
void game::end()
{
	MyTimer tt;//������һ����Ϊ tt �� MyTimer �������ڼ�ʱ
	EndBatchDraw();//������ͼ�������������ڻ���ͼ�ε���ʾЧ��
	if(isdie()==1||win==1)//:�������������������Ϸʤ��������ͣ��־Ϊ1������ͣ��־����Ϊ0�����ڻָ���Ϸ״̬
		pause=0;
	if(pause==1)//�����ͣ��־Ϊ1����ֱ�ӷ��أ���ִ�к�������
		return;
	if(win==1)
		tt.Sleep(5000);
	else
		tt.Sleep(2700);
	mciSendString("close all", NULL, 0, NULL);	
	tt.Sleep(1000);
	
	if(win==1)//�����Ϸʤ��������ͣ��־������������ֵ����Ϊ0������������Ϸ״̬�ĳ�ʼ��
	{
		pause=0;
		score=0;
		life=0;
		mciSendString("open ͨ��.mp3 alias mymusic13", NULL, 0, NULL);
	    mciSendString("play mymusic13", NULL, 0, NULL);
		putimage(0,-3*YSIZE,&img_home);
		tt.Sleep(7000);//�ӳ�7000���루7��)
		mciSendString("close mymusic13", NULL, 0, NULL);//�ر�ʤ������
	}
	else//�����Ϸδʤ������ִ������Ĵ����
	{
		score=0;
		if(life==0)
		{
			mciSendString("open ��Ϸ����.mp3 alias mymusic12", NULL, 0, NULL);
	        mciSendString("play mymusic12", NULL, 0, NULL);
			putimage(0,-YSIZE,&img_home);
		    tt.Sleep(5500);
	        mciSendString("close mymusic12", NULL, 0, NULL);
		}
		else//�����Ļ����ʾ��������ʣ�¡����֣�������ʣ������ֵ��ʾ��Ӧ�����֣����ӳ�2000���루2�룩
		{
			cleardevice();
			outtextxy(XSIZE/2-43,YSIZE/3,"������ʣ��:");
			if(life==1)
				outtextxy(XSIZE/2,YSIZE/2-20,"1");
			else if(life==2)
				outtextxy(XSIZE/2,YSIZE/2-20,"2");
			tt.Sleep(2000);
		}
	}
	cleardevice();// �����Ļ
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
