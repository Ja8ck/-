/**********************************************************************  
* Copyright (c)2021,HHY
* Filename:SeatOccupy.c   
* Compiler: GCC,VS,VC6.0  win64  
* Author:Hehangyu 
* Time: 2021 7 11
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define FrameX 2   //界面窗口左上角的X轴坐标
#define FrameY 3   //界面窗口左上角的Y轴坐标
#define Frame_height  20 //界面窗口的高度
#define Frame_width   40 //界面窗口的宽度
/*创建学生结构体*/
struct student
{
	char num[15];
	char name[20];
} students;	
/*创建自习室链表结构体*/
typedef struct room
{
	int num;
	int avlb;
	int occupied;
	int occup_seat_num [48];
	int checked_seat_num ;
	struct room *next;
	struct room *lost;
} room; 
room *head,*p,*rear,*mem;
/*创建光标坐标结构体*/
struct 
{
	int x;
	int y;
} cursor;
/*创建自习室选择界面位置信息*/
int room_x_y[10][2]={
	0,0,
	FrameX+2,FrameY+1,
	FrameX+40,FrameY+1,
	FrameX+2,FrameY+7,
	FrameX+40,FrameY+7,
	FrameX+2,FrameY+13,
	FrameX+40,FrameY+13,
	FrameX+Frame_width-14,FrameY+Frame_height-1,
	FrameX+Frame_width+6,FrameY+Frame_height-1,
	FrameX+2*Frame_width-8,FrameY+Frame_height-1
};
/*函数、参数列表*/
int user_statu;	//用户状态参数（0/1/2） 
int page_num,page_sum,total=0;	//定义全局变量 
void if_sign_in ();	 
void make_frame ();
void make_info (int a,room *p);
void menu (int a);
void fun_chose (int a);
void color_option ();

int main ()
{
	color_option ();
	make_frame ();
	if_sign_in ();
	make_info (user_statu,p);
	make_menu (user_statu); 
	fun_chose (user_statu);
	return 0;
} 

void if_sign_in ()	//登录信息检查函数
{
	char ch;
	page_sum = make_room_whole (24);
	FILE *fp;
	fp = fopen ("user.txt","r+");
	if (fp == NULL)
	{
		user_statu = 0;
		fp = fopen ("user.txt","w");
	} 
	else
	{
		ch = fgetc (fp);
		if (ch == '1')
			user_statu = 1;
		else
			user_statu = 0;
	}
} 

void color_option ()	//颜色设置函数
{
	system ("color 9F");
}

void gotoxy (HANDLE hOut, int x, int y)	//改变光标位置函数 
{
 	COORD pos;
	pos.X = x;  //横坐标
	pos.Y = y;  //纵坐标
	SetConsoleCursorPosition(hOut, pos);
}

void make_info (int a,room *p)	//信息显示函数
{
	struct tm *tm_now;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	//定义显示器光标变量
	switch (a)
	{
		case 0:
			gotoxy (hOut,FrameX+2*Frame_width+14,FrameY+8);
			printf ("当前状态：未登录");
			break;
		case 2:
			gotoxy (hOut,FrameX+2*Frame_width+7,FrameY+3);
	 		printf ("为你预留的自习室：%d",p->num);
		case 1:
			gotoxy (hOut,FrameX+2*Frame_width+5,FrameY+8);
			printf ("%s",students.name);
			gotoxy (hOut,FrameX+2*Frame_width+6,FrameY+5);
			printf ("当前自习室内总人数：%d",total);
			gotoxy (hOut,FrameX+2*Frame_width+14,FrameY+8);
 			printf ("当前状态：已登录");
			break;
	}
	show_time ();
}

void show_time()	//时间显示函数 
{
	time_t now;
	struct tm *tm_now;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	time(&now);
    tm_now = localtime(&now);
    gotoxy (hOut,FrameX+2*Frame_width+5,FrameY+1);
    printf("%d-%d-%d %d:%02d",tm_now->tm_year+1900,tm_now->tm_mon+1,tm_now->tm_mday,tm_now->tm_hour,tm_now->tm_min);
}

void make_menu (int a)	//功能菜单函数
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (a)
	{
		case 0:
			gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+11);  
 			printf (" 登 录");
 			break;
 		case 1:
 			gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+11);  
 			printf (" 空 座 位 选 择");
 			gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+13);
			printf (" 查 找 空 座 位");
			gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+15);
			printf (" 学 号 查 询 (功能实现中)"); 
			gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+17);
			printf (" 退 出 登 录");
			break;
		case 2:
			gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+11);  
 			printf (" 查 看 自 习 室");
 			gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+13);
			printf (" 确 认 入 座 ");
			gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+15);
			printf (" 取 消 座 位 预 留");
			gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+17);
			printf (" 退 出 登 录");
			break; 
	}
 	gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+19);
 	printf (" 退 出");
}

void make_frame()	//界面框架函数
{
	int i; 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//打印显示界面框角
 	gotoxy (hOut,FrameX,FrameY);       
 	printf ("╔");
 	gotoxy (hOut,FrameX+2*Frame_width-2,FrameY);
 	printf ("╗");
 	gotoxy (hOut,FrameX,FrameY+Frame_height);
 	printf ("╚");
 	gotoxy (hOut,FrameX+2*Frame_width-2,FrameY+Frame_height);
 	printf ("╝");
 	for (i=2;i<2*Frame_width-2;i+=2)
 	{
 		gotoxy(hOut,FrameX+i,FrameY);
  		printf("═");         //打印上横框
 	}
 	for (i=2;i<2*Frame_width-2;i+=2)
 	{
  		gotoxy(hOut,FrameX+i,FrameY+Frame_height);
  		printf("═");         //打印下横框
 	}
 	for (i=1;i<Frame_height;i++)
 	{
  		gotoxy(hOut,FrameX,FrameY+i); 
  		printf("║");         //打印左竖框
 	}
 	for (i=1;i<Frame_height;i++)
 	{
  		gotoxy(hOut,FrameX+2*Frame_width-2,FrameY+i); 
  		printf("║");         //打印右竖框
 	}
 	//打印简略信息界面框脚 
 	gotoxy (hOut,FrameX+2*Frame_width+3,FrameY);       
 	printf ("┌");
 	gotoxy (hOut,FrameX+2*Frame_width+30,FrameY);
 	printf ("┐");
 	gotoxy (hOut,FrameX+2*Frame_width+3,FrameY+9);
 	printf ("└");
 	gotoxy (hOut,FrameX+2*Frame_width+30,FrameY+9);
 	printf ("┘");
 	for (i=1;i<27;i++)
 	{
 		gotoxy(hOut,FrameX+2*Frame_width+3+i,FrameY);
  		printf("─");         //打印上横框
 	}
 	for (i=1;i<27;i++)
 	{
  		gotoxy(hOut,FrameX+2*Frame_width+3+i,FrameY+9);
  		printf("─");         //打印下横框
 	}
 	for (i=1;i<9;i++)
 	{
  		gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+i); 
  		printf("│");         //打印左竖框
 	}
 	for (i=1;i<9;i++)
 	{
  		gotoxy(hOut,FrameX+2*Frame_width+30,FrameY+i); 
  		printf("│");         //打印右竖框
 	}
	//打印程序名称 
 	gotoxy (hOut,FrameX+Frame_width-8,FrameY-2);
 	printf ("自习室占座系统");
}

void fun_chose (int a)	//功能选择函数
{
	unsigned char kb;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;	//初始化光标位置 
	while (1)	
	{
		gotoxy (hOut,cursor.x,cursor.y);
		printf ("★");
		kb = getch ();
		gotoxy (hOut,cursor.x,cursor.y);
		printf ("  ");
		switch (a)
		{
			case 0:	//未登录用户界面 
				switch (kb)
				{
					case 0X0D:	//选择功能
						if (cursor.y == FrameY+11)
							a = user_sign_in ();	//用户登录
						else
							exit (0);
						break;
					case 72:	//向上移动
						if (cursor.y == FrameY+11)
							cursor.y = FrameY+19;
						else
							cursor.y = FrameY+11;	
						break;
					case 80:	//向下移动
						if (cursor.y == FrameY+19)
							cursor.y = FrameY+11;
						else
							cursor.y = FrameY+19;
						break;
				}
				break;
			case 1:	//已登录用户界面
				switch (kb)	
				{
					case 0X0D:	//选择功能 
						switch (cursor.y)
						{
							case FrameY+11:	//空座位选择
								a = fun_chose_room ();	//选择自习室 
								break;
							case FrameY+13:	//查找空座位
								enter_find_room (fun_find_seat ());
								cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
								clean_screen (user_statu);
								if (user_statu == 2)
									a = 2;
								break; 
							case FrameY+15:	//学号查询  
								putchar ('\a'); 
								break; 
							case FrameY+17:	//退出登录
								a = user_sign_out (); 
								break; 
							case FrameY+19:	//退出
								exit (0);
						}
						break;
					case 72:	//向上移动
						if (cursor.y == FrameY+11)
							cursor.y = FrameY+19;
						else
							cursor.y -= 2;	
						break;
					case 80:	//向下移动
						if (cursor.y == FrameY+19)
							cursor.y = FrameY+11;
						else
							cursor.y += 2;
						break;
						}
				break;
			case 2:	//已占座用户界面
				switch (kb)	
				{
					case 0X0D:	//选择功能 
						switch (cursor.y)
						{
							case FrameY+11:	//查看预留的自习室
								enter_reserved_room (mem);
								clean_screen (2);
								break;
							case FrameY+13:	//确认入座 
								seat_down ();
								goto end;
							case FrameY+15:	//取消座位预留
								a = cancel_reserved_seat ();
								break; 
							case FrameY+17:	//退出登录
								a = user_sign_out ();
								break; 
							case FrameY+19:	//退出
								exit (0);
						}
						break;
					case 72:	//向上移动
						if (cursor.y == FrameY+11)
							cursor.y = FrameY+19;
						else
							cursor.y -= 2;	
						break;
					case 80:	//向下移动
						if (cursor.y == FrameY+19)
							cursor.y = FrameY+11;
						else
							cursor.y += 2;
						break;
				}
				break;
		}
	}
	end : return ;
}

void clean_screen (int a)	//清屏函数
{ 
	system ("cls");
	make_frame ();
	make_info (a,p);
	make_menu (a);
} 

int user_sign_in ()	//用户登录 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = FrameX+Frame_width-14; cursor.y = FrameY+7;	//初始化登录输入栏坐标
	gotoxy (hOut,cursor.x,cursor.y);
	printf ("学号："); 
	FILE *fp;
	fp = fopen ("user.txt","w");
	gets (students.num);
	fprintf (fp,"   %s",students.num);
	cursor.y += 2;
	gotoxy (hOut,cursor.x,cursor.y);
	printf ("姓名：");
	gets (students.name);
	fprintf (fp,"  %s",students.name); 
	rewind (fp);
	fprintf (fp,"1");	//记录用户登录信息 
	fclose (fp);
	user_statu = 1;
	clean_screen (user_statu);
	cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
	return 1;
}

int user_sign_out ()	//用户退出登录
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	FILE *fp;
	fp = fopen ("user.txt","w");
	rewind (fp);
	fprintf (fp,"0");	//将用户登录状态更改为“未登录” 
	fclose (fp);
	cursor.x = FrameX+Frame_width-8; cursor.y = FrameY+9;
	if (user_statu == 2) 
		mem->checked_seat_num = 0; 
	gotoxy (hOut,cursor.x,cursor.y); 
	printf ("\a退出登录成功！");
	sleep (2);
	user_statu = 0;
	clean_screen (user_statu);
	cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
	return 0;
}

int fun_chose_room ()	//选择房间功能函数,返回用户状态参数 
{
	int i=1;	//定义功能框位置变量 
	unsigned char kb;
	loop_1:page_num = 1;
	p = head->next;
	make_room_frame_onepage (page_num,p);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[9][0],room_x_y[9][1]);
	printf ("<返回>");
	while (1)
	{
		page_check (page_num,page_sum);
		switch (i)
		{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				make_room_frame_chosen_one (room_x_y[i][0],room_x_y[i][1]);
				break;
			case 7:
				text_color (15,32);
				gotoxy (hOut,room_x_y[7][0],room_x_y[7][1]);
				printf ("<上一页>");
				break;
			case 8:
				text_color (15,32);
				gotoxy (hOut,room_x_y[8][0],room_x_y[8][1]);
				printf ("<下一页>");
				break;
			case 9:
				text_color (15,32);
				gotoxy (hOut,room_x_y[9][0],room_x_y[9][1]);
				printf ("<返回>");
				break;
		}
		loop_2:kb = getch ();
		switch (kb /*= getch ()*/)
		{
			case 0X0D:	//选择房间/功能 
				switch (i)
				{
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						enter_chosen_room (page_num,i);
						clean_screen (user_statu);
						if (user_statu == 1)
							goto loop_1;	//回到410行 
						return 2;
					case 7:
						switch (page_check (page_num,page_sum))
						{
							case 0:
							case 1:
								putchar ('\a');
								break;
							case -1:
							default :
								page_num = page_roll_up (page_num);
						}
						break;
					case 8:
						switch (page_check (page_num,page_sum))
						{
							case 0:
							case -1:
								putchar ('\a');
								break;
							case 1:
							default :
								 page_num = page_roll_down (page_num);
						}
						break;
					case 9:
						text_color (15,16);
						clean_screen (1);
						cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
						return 1;
				}
				break;
			case 72:	//向上移动 
				i = move_chosen_room (i,1,page_num,page_sum);
				break;
			case 80:	//向下移动
				i = move_chosen_room (i,2,page_num,page_sum);
				break;
			case 75:	//向左移动
				i = move_chosen_room (i,3,page_num,page_sum);
				break;
			case 77:	//向右移动
				i = move_chosen_room (i,4,page_num,page_sum);
				break;
			default :
				goto loop_2;	//回到447行 
		}
	}
}

int move_chosen_room (int before,int direction)	//移动选择框并返回新选择框位置序号 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (before)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			make_room_frame_one (room_x_y[before][0],room_x_y[before][1]);
			break;
		case 9:
			text_color (15,16);
			gotoxy (hOut,room_x_y[9][0],room_x_y[9][1]);
			printf ("<返回>");
			break;
		default :
			page_check (page_num,page_sum);
			break;
	}
	switch (direction)
	{
		case 1:	//向上移动 
			switch (before)
			{
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
					return before-2;
				case 9:
					return before-3;
				default :
					putchar ('\a');
					break;
			}
		return before; 
		case 2:	//向下移动 
			switch (before)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					return before+2;
				default :
					putchar ('\a');
					break;
			}
		return before; 
		case 3:	//向左移动 
			switch (before)
			{
				case 2:
				case 4:
				case 6:
				case 8:
				case 9:
					return before-1;
				default :
					putchar ('\a');
					break;
			}
		return before; 
		case 4:	//向右移动 
			switch (before)
			{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
					return before+1;
				default :
					putchar ('\a');
					break;
			}
		return before; 
	}
} 

void text_color (int x,int y)	//文本颜色函数 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x | 8 | y | 128);
}

int page_check (int page_num,int page_sum)	//页码/页数检查并返回状态值 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	text_color (15,16);
	gotoxy (hOut,FrameX+Frame_width-3,FrameY+Frame_height-1);
	printf ("(%d/%d)",page_num,page_sum);
	if (page_sum == 1)	//只有一页时，返回0 
	{
		text_color (8,16);
		gotoxy (hOut,room_x_y[7][0],room_x_y[7][1]);
		printf ("<上一页>");
		gotoxy (hOut,room_x_y[8][0],room_x_y[8][1]);
		printf ("<下一页>");
		text_color (8,16);
		return 0;
	}
	else
	{
		text_color (8,16);
		if (page_num == 1)	 //第一页时，返回1 
		{
			gotoxy (hOut,room_x_y[7][0],room_x_y[7][1]);
			printf ("<上一页>");
			text_color (15,16);
			gotoxy (hOut,room_x_y[8][0],room_x_y[8][1]);
			printf ("<下一页>");
			return 1; 
		}
		else if (page_num == page_sum)	//最后一页时，返回-1 
		{
			gotoxy (hOut,room_x_y[8][0],room_x_y[8][1]);
			printf ("<下一页>");
			text_color (15,16);
			gotoxy (hOut,room_x_y[7][0],room_x_y[7][1]);
			printf ("<上一页>");
			return -1;
		}
		else	//中间页面，无返回值 
		{
			text_color (15,16);
			gotoxy (hOut,room_x_y[7][0],room_x_y[7][1]);
			printf ("<上一页>");
			gotoxy (hOut,room_x_y[8][0],room_x_y[8][1]);
			printf ("<下一页>");
			return ; 
		}
	}
}

int page_roll_up (int page_num)	//向上翻页并返回新页码 
{
	int i;
	for (i=0;i<6;i++)
	{
		p = p->lost;
	}
	make_room_frame_onepage (--page_num,p);
	return page_num;
} 

int page_roll_down (int page_num)	//向下翻页并返回新页码
{
	int i;
	for (i=0;i<6;i++)
	{
		p = p->next;
	}
	make_room_frame_onepage (++page_num,p);
	return page_num;
} 

void enter_chosen_room (int page_num,int a)	//进入选择的房间 
{
	int i;
	clean_screen (1);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[9][0]-5,room_x_y[9][1]);
	printf ("<返回(Esc)>");
	p = head;
	for (i=0;i<(page_num-1)*6+a;i++)
	{
		p = p->next;
	}
	make_room_inside (p);
	gotoxy (hOut,room_x_y[9][0]-7,room_x_y[9][1]-2);
	printf ("<选择(Enter)>");
	fun_chose_seat (p);
}

void enter_find_room (int a)	//进入查找到的房间 
{
	int i=1;
	clean_screen (1);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[9][0]-5,room_x_y[9][1]);
	printf ("<返回(Esc)>");
	p = head;
	for (p = p->next;i;p = p->next)
	{
		if (p->num == a)
			break;
	}
	make_room_inside (p);
	gotoxy (hOut,room_x_y[9][0]-7,room_x_y[9][1]-2);
	printf ("<选择(Enter)>");
	fun_chose_seat (p);
}

void enter_reserved_room (room *p)	//进入预定的房间 
{
	clean_screen (2);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[9][0]-5,room_x_y[9][1]);
	printf ("<返回(Esc)>");
	make_reserved_room_inside (p);
	cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
	back (); 
}

void back ()	//返回函数
{
	unsigned char kb;
	do
	{
		kb = getch ();
		switch (kb)
		{
			case 0X1B:
				return ;
			default :
				break;
		}	
	} while (1);
}

int seat_num[49][2]={	//座位坐标数组 
	0,0,
	26,12,29,12,35,12,38,12,41,12,44,12,50,12,53,12,
	26,13,29,13,35,13,38,13,41,13,44,13,50,13,53,13,
	26,14,29,14,35,14,38,14,41,14,44,14,50,14,53,14,
	26,15,29,15,35,15,38,15,41,15,44,15,50,15,53,15,
	26,16,29,16,35,16,38,16,41,16,44,16,50,16,53,16,
	26,17,29,17,35,17,38,17,41,17,44,17,50,17,53,17
};

void make_room_inside (room *p)	//打印房间界面 
{
	int i;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = room_x_y[1][0]; cursor.y = room_x_y[1][1];
	make_room_frame_one (cursor.x,cursor.y);
	make_room_one_info (cursor.x,cursor.y,p);
	show_time ();
	if (p->checked_seat_num)
		room_inside_text_2 (p);
	else
		room_inside_text_1 ();
	for (i=1;i<49;i++)	//打印全部座位 
	{
		gotoxy (hOut,seat_num[i][0],seat_num[i][1]);
		printf ("□");
	}
	for (i=0;i<p->occupied;i++)	//打印不可用座位 
	{
		gotoxy (hOut,seat_num[p->occup_seat_num[i]][0],seat_num[p->occup_seat_num[i]][1]);
		printf ("■");
	}	
}

void room_inside_text_1 ()	//创建座位选择界面文本 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[2][0]+9,room_x_y[2][1]+2);
	printf ("选择空座位后按下<确认>");
	gotoxy (hOut,room_x_y[2][0]+4,room_x_y[2][1]+3);
	printf ("确定占座后座位将为你预留20分钟");
	gotoxy (hOut,room_x_y[2][0]+5,room_x_y[2][1]+4);
	printf ("文明自习，请勿浪费自习室空间！");
	gotoxy (hOut,seat_num[2][0]-1,seat_num[43][1]+2);
	printf ("按下\'<\'、\'>\'键选择空座位");
}

void room_inside_text_2 (room *p)	//创建自习室查看界面文本
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[2][0]+12,room_x_y[2][1]+2);
	printf ("座位已为你预留");
	gotoxy (hOut,room_x_y[2][0]+10,room_x_y[2][1]+3);
	printf ("座位将为你预留20分钟");
	gotoxy (hOut,room_x_y[2][0]+5,room_x_y[2][1]+4);
	printf ("文明自习，请勿浪费自习室空间！");
	gotoxy (hOut,seat_num[4][0],seat_num[43][1]+2);
	printf ("座号：%2d",p->checked_seat_num);
} 

void fun_chose_seat (room *p)	//座位选择功能函数 
{
	int a;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	a = find_first_seat (p);
	do
	{
		gotoxy (hOut,seat_num[a][0],seat_num[a][1]);
		printf ("★");
		a = move_chosen_seat (a,p);
	} while (a);
}

int find_first_seat (room *p)	//查找序号最小的空座位并返回其座位序号 
{
	int i=0;
	if (p->occup_seat_num[i] != 1)
		return 1;
	for (;i<p->occupied;i++)
	{
		if (p->occup_seat_num[i+1] != p->occup_seat_num[i]+1)
			return p->occup_seat_num[i]+1;
	}
}

int move_chosen_seat (int a,room *p)	//移动选择空座位光标并返回最接近的下一个座位 
{
	int i;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned char kb;
	kb = getch ();
	gotoxy (hOut,seat_num[a][0],seat_num[a][1]);
	printf ("□");
	switch (kb)
	{
		case 0X1B:
			user_statu = 1; 
			return 0;
		case 0X0D:
			gotoxy (hOut,seat_num[a][0],seat_num[a][1]);
			printf ("◎");
			i = check_seat (a,p); 
			return i;
		/*case 72:	//向上移动
			if (avlb_seat_num (a,1,p))
			{
				do
				{
					a -= 8;
				} while (search (a,p));
				gotoxy (hOut,seat_num[a][0],seat_num[a][1]);
			}
			else
			{
			}
			return 1;
		case 80:	//向下移动
			if (avlb_seat_num (a,2,p))
			{
				do
				{
					a += 8;
				} while (search (a,p));
				gotoxy (hOut,seat_num[a][0],seat_num[a][1]);
			}
			return 1;*/
		case 75:	//向左移动
			if (a != 1)
				a = avlb_seat_num (a,3,p);
			return a;
		case 77:	//向右移动
			if (a != 48)
				a = avlb_seat_num (a,4,p);
			return a;
		default :
			return a;
	}
}

int avlb_seat_num (int a,int direction,room *p)	//返回对应方向最近的空座位序号 
{
	int mem=a;
	switch (direction)
	{
		/*case 1:	//向上查找
			switch (a)
			{
				if (a>=9)
				{
					do
					{
						mem = a;
						mem -= 8;
						if (search (mem,p))
							i++;
					} while (mem-8>0);
					return i;
				}
				else
					return 0;
			}
		case 2:	//向下查找
			switch (a)
			{
				if (a<=40)
				{
					do
					{
						mem = a;
						mem += 8;
						if (search(mem,p))
							i++;
					} while (mem+8>48);
					return i;
				}
				else
					return 0;
			}*/
		case 3:	//向左查找
			do
			{
				mem--;
				if (search(mem,p))
					continue;
				else
					return mem;
			} while (mem != 1);
			putchar ('\a');
			return a;
		case 4:	//向右查找
			do
			{
				mem++;
				if (search(mem,p))
					continue;
				else
					return mem;
			} while (mem != 48);
			putchar ('\a');
			return a;
	}
} 

void make_room_frame_onepage (int page_num,room *p)	//创建一页房间选择框 
{
	int i=6,j,X,Y;
	/*if (page_sum)
	{*/
		for (j = 1;i--;j++) 
		{
			X = room_x_y[j][0];Y = room_x_y[j][1];
			make_room_frame_one (X,Y);
			make_room_one_info (X,Y,p);
			p = p->next;
		}
	/*}
	else
	{
		for (b = a%6,j = 1;b--;j++) 
		{
			X = room_x_y[j][0];Y = room_x_y[j][1];
			make_room_frame_one (X,Y);
			make_room_one_info (X,Y,p);
			p = p->next;
		}
	}*/
} 

int fun_find_seat ()	//寻找人数最少的自习室并返回房间号 
{
	int min,room_num;
	p = head;
	p = p->next;
	for (min = p->occupied;p != NULL;p = p->next)
	{
		if (p->occupied<min)
		{
			min = p->occupied;
			room_num = p->num;
		}
	}
	p = head;
	return room_num;
}

int make_room_whole (int a)	//创建房间并返回页数
{
	int b,page_sum,X ,Y ,i = 1,j,loop;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!a)
	{
		cursor.x = FrameX+Frame_width-8; cursor.y = FrameY+9;
		gotoxy (hOut,cursor.x,cursor.y);
		printf ("没有可用的自习室！");
		gotoxy (hOut,FrameX+2*Frame_width+30,FrameY+11);
		return 0; 
	}
	page_sum = a/6;
	p = (room *)malloc (sizeof(room));
	head = p;
	for (loop = a;loop != 0;loop--)
		make_room_one (a-loop+1);
	p->next = NULL;
	if (a%6)
		page_sum++;
	return page_sum;
}

void make_room_frame_one (int x,int y)	//创建一个房间选择框 
{
	int i;
	const int WIDTH = 36,LENGTH = 5;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = x; cursor.y = y;
	gotoxy (hOut,cursor.x,cursor.y);
	printf ("┌");
	gotoxy (hOut,cursor.x+WIDTH,cursor.y);
	printf ("┐ ");
	gotoxy (hOut,cursor.x,cursor.y+LENGTH);
	printf ("└");
	gotoxy (hOut,cursor.x+WIDTH,cursor.y+LENGTH);
	printf ("┘ ");
	for (i=1;WIDTH-i;i++)
	{
		gotoxy (hOut,cursor.x+i,cursor.y);
		printf ("─");
		gotoxy (hOut,cursor.x+i,cursor.y+LENGTH);
		printf ("─");
	}
	for (i=1;LENGTH-i;i++)
	{
		gotoxy (hOut,cursor.x,cursor.y+i);
		printf ("│ ");
		gotoxy (hOut,cursor.x+WIDTH,cursor.y+i);
		printf ("│ ");
	}
}

void make_room_frame_chosen_one (int x,int y)	//创建一个被选中的房间框
{
	int i;
	const int WIDTH = 36,LENGTH = 5;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = x; cursor.y = y;
	text_color (15,32);
	gotoxy (hOut,cursor.x,cursor.y);
	printf ("┌");
	gotoxy (hOut,cursor.x+WIDTH,cursor.y);
	printf ("┐ ");
	gotoxy (hOut,cursor.x,cursor.y+LENGTH);
	printf ("└");
	gotoxy (hOut,cursor.x+WIDTH,cursor.y+LENGTH);
	printf ("┘ ");
	for (i=1;WIDTH-i;i++)
	{
		gotoxy (hOut,cursor.x+i,cursor.y);
		printf ("─");
		gotoxy (hOut,cursor.x+i,cursor.y+LENGTH);
		printf ("─");
	}
	for (i=1;LENGTH-i;i++)
	{
		gotoxy (hOut,cursor.x,cursor.y+i);
		printf ("│ ");
		gotoxy (hOut,cursor.x+WIDTH,cursor.y+i);
		printf ("│ ");
	}
	text_color (15,16);
} 

void make_room_one (int a)	//创建一个房间结构体 
{
	int i,j;
	srand ((unsigned int)time (NULL)+rand ());
	rear = p;
	p = (room *)malloc (sizeof(room));
	p->lost = rear;
	rear->next = p;
	p->num = 100*(1+(a-1)/8)+(a-1)%8+1;	//房间号 
	p->occupied = rand()%49;
	p->checked_seat_num = 0;
	total += p->occupied;
	for (i=0;i<p->occupied;i++)	//产生被占用座位序号 
	{
		p->occup_seat_num[i] = rand()%48+1;
		if (i>0)
			for (j=0;j<i;j++)
			{
				if (p->occup_seat_num[j] == p->occup_seat_num[i])
					i--;
			}
	}
	sort (p->occup_seat_num,p);
	p->avlb = 48-p->occupied;
}

void sort (int a[],room *p)	//升序排列数组元素 
{
	int i,j,t,r; 
	for (j=0;j<p->occupied-1;j++)
	{
		for (i=0;i<p->occupied-1;i++)
		{
			r=i+1;
			if (a[i]>a[r]) 
			{
				t=a[i];
				a[i]=a[r];
				a[r]=t;
			}
		}	
	}
}

int search (int n,room *p)	//搜索结构体数组中是否有对应元素 
{
	int i;
	for (i=0;i<p->occupied;i++)
	{
		if (n == p->occup_seat_num[i])
			return 1;
	}
	return 0;
} 

void make_room_one_info (int x,int y,room *p)	//创建一个房间信息 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = x; cursor.y = y;
	gotoxy (hOut,cursor.x+1,cursor.y+1);
	printf (" %d",p->num);
	gotoxy (hOut,cursor.x+21,cursor.y+3);
	printf ("自习室人数：%2d",p->occupied);
	gotoxy (hOut,cursor.x+23,cursor.y+1);
	printf ("          ");
	gotoxy (hOut,cursor.x+23,cursor.y+4);
	if (p->occupied == 48)
		printf ("已满");
	else
		printf ("空座位数：%2d",p->avlb);
	if (p->checked_seat_num != 0)
	{
		gotoxy (hOut,cursor.x+23,cursor.y+1);
		text_color (0,6); 
		printf ("座位预留中");
		text_color (15,16);
	}
}

int check_seat (int a,room *p)	//座位确认并返回确认情况 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[9][0]-7,room_x_y[9][1]-2);
	printf ("<确认(Enter)>"); 
	gotoxy (hOut,room_x_y[9][0]-5,room_x_y[9][1]);
	printf ("<取消(Esc)>");
	unsigned char kb;
	kb = getch ();
	switch (kb)
	{
		case 0X1B:
			gotoxy (hOut,room_x_y[9][0]-7,room_x_y[9][1]-2);
			printf ("<选择(Enter)>"); 
			gotoxy (hOut,room_x_y[9][0]-5,room_x_y[9][1]);
			printf ("<返回(Esc)>");
			return a;
		case 0X0D:
			user_statu = 2;
			clean_screen (user_statu);
			mem = p;
			mem->checked_seat_num = a;
			gotoxy (hOut,FrameX+Frame_width-12,FrameY+9);
			printf ("\a座位预定成功！ 座号：%d",a/*p->checked_seat_num*/);
			sleep (2); 
			cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
			return 0;
	}
}

int make_reserved_room_inside (room *p)	//进入预留的房间 
{
	int i;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = room_x_y[1][0]; cursor.y = room_x_y[1][1];
	make_room_frame_one (cursor.x,cursor.y);
	make_room_one_info (cursor.x,cursor.y,p);
	show_time ();
	if (p->checked_seat_num)
		room_inside_text_2 (p);
	else
		room_inside_text_1 ();
	for (i=1;i<49;i++)	//打印全部座位 
	{
		gotoxy (hOut,seat_num[i][0],seat_num[i][1]);
		printf ("□");
	}
	for (i=0;i<p->occupied;i++)	//打印不可用座位 
	{
		gotoxy (hOut,seat_num[p->occup_seat_num[i]][0],seat_num[p->occup_seat_num[i]][1]);
		printf ("■");
	}
	if (p->checked_seat_num)	//打印预留中座位 
	{
		gotoxy (hOut,seat_num[p->checked_seat_num][0],seat_num[p->checked_seat_num][1]);
		printf ("◎");
	}
}

void seat_down()	//确认入座函数 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	total++;
	clean_screen (2);
	gotoxy (hOut,FrameX+Frame_width-7,FrameY+9);
	printf ("\a确认成功！");
	sleep (3);
}

int cancel_reserved_seat ()	//取消预留座位并返回用户状态参数 
{
	unsigned char kb;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,FrameX+Frame_width-11,FrameY+8);
	printf ("确认取消座位预留吗？");
	gotoxy (hOut,FrameX+Frame_width-16,FrameY+11);
	printf ("确认<Enter>\t\t返回<Esc>");
	do
	{
		kb = getch();
		switch (kb)
		{
			case 0X1B:
				clean_screen (2);
				cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
				return 2;
			case 0X0D:
				clean_screen (1);
				cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
				mem->checked_seat_num = 0;
				return 1; 
			default :
				break;
		}
	} while (1);
} 
