
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define FrameX 2  //���洰�����Ͻǵ�X������
#define FrameY 2   //���洰�����Ͻǵ�Y������
#define Frame_height  20 //���洰�ڵĸ߶�
#define Frame_width   40 //���洰�ڵĿ��
/*����ѧ���ṹ��*/
struct student
{
	char num[15];
	char name[20];
} students;
/*������ϰ������ṹ��*/
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
room *head,*p,*rear;
/*�����������ṹ��*/
struct
{
	int x;
	int y;
} cursor;
/*������ϰ��ѡ�����λ����Ϣ*/
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
/*�����������б�*/
int sign_in;	//�Ƿ��¼����
int page_num,page_sum,total=0;	//����ȫ�ֱ���
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
	make_info (sign_in,p);
	make_menu (sign_in);
	fun_chose (sign_in);
    printf("PureColorText\n");
    system("pause");
    system("color 0A");
    printf("\nTurn to green\n");
    system("pause");
	return 0;
}

void if_sign_in ()	//�Ƿ��¼��麯��
{
	char ch;
	page_sum = make_room_whole (6);
	FILE *fp;
	fp = fopen ("user.txt","r+");
	if (fp == NULL)
	{
		sign_in = 0;
		fp = fopen ("user.txt","w");
	}
	else
	{
		ch = fgetc (fp);
		if (ch == '1')
			sign_in = 1;
		else
			sign_in = 0;
	}
}

void color_option ()	//��ɫ���ú���
{
	system ("color 79");
}

void gotoxy (HANDLE hOut, int x, int y)	//�ı���λ�ú���
{
 	COORD pos;
	pos.X = x;  //������
	pos.Y = y;  //������
	SetConsoleCursorPosition(hOut, pos);
}

void make_info (int a,room *p)	//��Ϣ��ʾ����
{
	struct tm *tm_now;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	//������ʾ��������
	if (a)
	{
		gotoxy (hOut,FrameX+2*Frame_width+5,FrameY+8);
		printf ("%s",students.name);
		gotoxy (hOut,FrameX+2*Frame_width+6,FrameY+5);
		printf ("��ǰ��ϰ������������%d",total);
		gotoxy (hOut,FrameX+2*Frame_width+14,FrameY+8);
	 	printf ("��ǰ״̬���ѵ�¼");
	 	if (p->checked_seat_num)
	 	{
	 		gotoxy (hOut,FrameX+2*Frame_width+7,FrameY+3);
	 		printf ("Ϊ��Ԥ������ϰ�ң�%d",p->num);
		}
	}
	else
	{
		gotoxy (hOut,FrameX+2*Frame_width+14,FrameY+8);
		printf ("��ǰ״̬��δ��¼");
	}
	show_time ();
}

void show_time()	//ʱ����ʾ����
{
	time_t now;
	struct tm *tm_now;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	time(&now);
    tm_now = localtime(&now);
    gotoxy (hOut,FrameX+2*Frame_width+5,FrameY+1);
    printf("%d-%d-%d %d:%02d",tm_now->tm_year+1900,tm_now->tm_mon+1,tm_now->tm_mday,tm_now->tm_hour,tm_now->tm_min);
}

void make_menu (int a)	//���ܲ˵�����
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (a)
 	{
	 	gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+11);
 		printf (" �� �� λ ѡ ��");
 		gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+13);
		printf (" �� �� �� �� λ (������)");
		gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+15);
		printf (" �� �� ռ �� (������)");
		gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+17);
		printf (" �� �� �� ¼");
		gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+23);
		printf (" �� �� �� ����������)");
	}
	else
	{
		gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+11);
 		printf (" �� ¼");
	}
 	gotoxy (hOut,FrameX+2*Frame_width+2,FrameY+19);
 	printf (" �� ��");
}

void make_frame()	//�����ܺ���
{
	int i;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ӡ��ʾ������
 	gotoxy (hOut,FrameX,FrameY);
 	printf ("��");
 	gotoxy (hOut,FrameX+2*Frame_width-2,FrameY);
 	printf ("��");
 	gotoxy (hOut,FrameX,FrameY+Frame_height);
 	printf ("��");
 	gotoxy (hOut,FrameX+2*Frame_width-2,FrameY+Frame_height);
 	printf ("��");
 	for (i=2;i<2*Frame_width-2;i+=2)
 	{
 		gotoxy(hOut,FrameX+i,FrameY);
  		printf("��");         //��ӡ�Ϻ��
 	}
 	for (i=2;i<2*Frame_width-2;i+=2)
 	{
  		gotoxy(hOut,FrameX+i,FrameY+Frame_height);
  		printf("��");         //��ӡ�º��
 	}
 	for (i=1;i<Frame_height;i++)
 	{
  		gotoxy(hOut,FrameX,FrameY+i);
  		printf("|");         //��ӡ������
 	}
 	for (i=1;i<Frame_height;i++)
 	{
  		gotoxy(hOut,FrameX+2*Frame_width-2,FrameY+i);
  		printf("|");         //��ӡ������
 	}
 	//��ӡ������Ϣ������
 	gotoxy (hOut,FrameX+2*Frame_width+3,FrameY);
 	printf ("��");
 	gotoxy (hOut,FrameX+2*Frame_width+30,FrameY);
 	printf ("��");
 	gotoxy (hOut,FrameX+2*Frame_width+3,FrameY+9);
 	printf ("��");
 	gotoxy (hOut,FrameX+2*Frame_width+30,FrameY+9);
 	printf ("��");
 	for (i=1;i<27;i++)
 	{
 		gotoxy(hOut,FrameX+2*Frame_width+3+i,FrameY);
  		printf("��");         //��ӡ�Ϻ��
 	}
 	for (i=1;i<27;i++)
 	{
  		gotoxy(hOut,FrameX+2*Frame_width+3+i,FrameY+9);
  		printf("��");         //��ӡ�º��
 	}
 	for (i=1;i<9;i++)
 	{
  		gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+i);
  		printf("��");         //��ӡ������
 	}
 	for (i=1;i<9;i++)
 	{
  		gotoxy(hOut,FrameX+2*Frame_width+30,FrameY+i);
  		printf("��");         //��ӡ������
 	}
	//��ӡ��������
 	gotoxy (hOut,FrameX+Frame_width-8,FrameY-2);
 	printf ("��ϰ��ռ��ϵͳ");
}

void fun_chose (int a)	//����ѡ����
{
	unsigned char kb;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;	//��ʼ�����λ��
	while (1)
	{
		gotoxy (hOut,cursor.x,cursor.y);
		printf ("<<");
		kb = getch ();
		gotoxy (hOut,cursor.x,cursor.y);
		printf ("  ");
		if (a)
		{
			switch (kb)	//�ѵ�¼�û�����
			{
				case 0X0D:	//ѡ����
					switch (cursor.y)
					{
						case FrameY+11:	//����λѡ��
							fun_chose_room ();	//ѡ����ϰ��
							break;
						case FrameY+13:	//���ҿ���λ��δʵ��
                        case FrameY+23://�������⣬δʵ��
						case FrameY+15:	//����ռ����δʵ��
							putchar ('\a');
							break;
						case FrameY+17:	//�˳���¼
							a = user_sign_out ();
							break;
						case FrameY+19:	//�˳�
							exit (0);
					}
					break;
				case 72:	//�����ƶ�
					if (cursor.y == FrameY+11)
						cursor.y = FrameY+19;
					else
						cursor.y -= 2;
					break;
				case 80:	//�����ƶ�
					if (cursor.y == FrameY+19)
						cursor.y = FrameY+11;
					else
						cursor.y += 2;
					break;
			}
		}
		else	//δ��¼�û�����
		{
			switch (kb)
			{
				case 0X0D:	//ѡ����
					if (cursor.y == FrameY+11)
					{
						a = user_sign_in ();
						break;
					}
					else
						exit (0);
				case 72:	//�����ƶ�
					if (cursor.y == FrameY+11)
						cursor.y = FrameY+19;
					else
						cursor.y = FrameY+11;
					break;
				case 80:	//�����ƶ�
					if (cursor.y == FrameY+19)
						cursor.y = FrameY+11;
					else
						cursor.y = FrameY+19;
					break;
			}
		}
	}
}

void clean_screen (int a)	//��������
{
	system ("cls");
	make_frame ();
	make_info (a,p);
	make_menu (a);
}

int user_sign_in ()	//�û���¼
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = FrameX+Frame_width-14; cursor.y = FrameY+7;	//��ʼ����¼����������
	gotoxy (hOut,cursor.x,cursor.y);
	printf ("ѧ�ţ�");
	FILE *fp;
	fp = fopen ("user.txt","w");
	gets (students.num);
	fprintf (fp,"   %s",students.num);
	cursor.y += 2;
	gotoxy (hOut,cursor.x,cursor.y);
	printf ("������");
	gets (students.name);
	fprintf (fp,"  %s",students.name);
	rewind (fp);
	fprintf (fp,"1");	//��¼�û���¼��Ϣ
	fclose (fp);
	sign_in = 1;
	clean_screen (sign_in);
	cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
	return 1;
}

int user_sign_out ()	//�û��˳���¼
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	FILE *fp;
	fp = fopen ("user.txt","w");
	rewind (fp);
	fprintf (fp,"0");	//���û���¼״̬����Ϊ��δ��¼��
	fclose (fp);
	cursor.x = FrameX+Frame_width-8; cursor.y = FrameY+9;
	gotoxy (hOut,cursor.x,cursor.y);
	printf ("\a�˳���¼�ɹ���");
	sign_in = 0;
	clean_screen (sign_in);
	cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
	return 0;
}

void fun_chose_room ()	//ѡ�񷿼书�ܺ���
{
	int i=1;	//���幦�ܿ�λ�ñ���
	unsigned char kb;
	loop_1:page_num = 1;
	p = head->next;
	make_room_frame_onepage (page_num,p);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[9][0],room_x_y[9][1]);
	printf ("<����>");
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
			case 8:
			case 9:
				text_color (20,40);
				gotoxy (hOut,room_x_y[9][0],room_x_y[9][1]);
				printf ("<����>");
				break;
		}
		loop_2:kb = getch ();
		switch (kb )
		{
			case 0X0D:	//ѡ�񷿼�/����
				switch (i)
				{
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						enter_chosen_room (page_num,i);
						clean_screen (1);
						goto loop_1;
						break;
					case 9:
						text_color (15,16);
						clean_screen (1);
						goto end;
				}
				break;
			case 72:	//�����ƶ�
				i = move_chosen_room (i,1);
				break;
			case 80:	//�����ƶ�
				i = move_chosen_room (i,2);
				break;
			case 75:	//�����ƶ�
				i = move_chosen_room (i,3);
				break;
			case 77:	//�����ƶ�
				i = move_chosen_room (i,4);
				break;
			default :
				goto loop_2;
		}
	}
	end : cursor.x = FrameX+2*Frame_width+30; cursor.y = FrameY+11;
}

int move_chosen_room (int before,int direction)	//�ƶ�ѡ��򲢷�����ѡ���λ�����
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
			printf ("<����>");
			break;
		default :
			page_check (page_num,page_sum);
			break;
	}
	switch (direction)
	{
		case 1:	//�����ƶ�
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
		case 2:	//�����ƶ�
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
		case 3:	//�����ƶ�
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
		case 4:	//�����ƶ�
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

void text_color (int x,int y)	//�ı���ɫ����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),121  );
}

int page_check (int page_num,int page_sum)	//ҳ��/ҳ����鲢����״ֵ̬
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	text_color (15,16);
	gotoxy (hOut,FrameX+Frame_width-3,FrameY+Frame_height-1);
	printf ("(%d/%d)",page_num,page_sum);
}

void enter_chosen_room (int page_num,int a)	//����ѡ��ķ���
{
	int i;
	clean_screen (1);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[9][0]-5,room_x_y[9][1]);
	printf ("<����(Esc)>");
	p = head;
	for (i=0;i<(page_num-1)*6+a;i++)
	{
		p = p->next;
	}
	make_room_inside (p);
	if (!p->checked_seat_num)
	{
		gotoxy (hOut,room_x_y[9][0]-7,room_x_y[9][1]-2);
		printf ("<ѡ��(Enter)>");
		fun_chose_seat (p);
	}
	else
		back ();
}

void back ()	//���غ���
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

int seat_num[49][2]={	//��λ��������
	0,0,
	26,12,29,12,35,12,38,12,41,12,44,12,50,12,53,12,
	26,13,29,13,35,13,38,13,41,13,44,13,50,13,53,13,
	26,14,29,14,35,14,38,14,41,14,44,14,50,14,53,14,
	26,15,29,15,35,15,38,15,41,15,44,15,50,15,53,15,
	26,16,29,16,35,16,38,16,41,16,44,16,50,16,53,16,
	26,17,29,17,35,17,38,17,41,17,44,17,50,17,53,17
};

void make_room_inside (room *p)	//��ӡ�������
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
	for (i=1;i<49;i++)	//��ӡȫ����λ
	{
		gotoxy (hOut,seat_num[i][0],seat_num[i][1]);
		printf ("��");
	}
	for (i=0;i<p->occupied;i++)	//��ӡ��������λ
	{
		gotoxy (hOut,seat_num[p->occup_seat_num[i]][0],seat_num[p->occup_seat_num[i]][1]);
		printf ("��");
	}
	if (p->checked_seat_num)	//��ӡԤ������λ
	{
		gotoxy (hOut,seat_num[p->checked_seat_num][0],seat_num[p->checked_seat_num][1]);
		printf ("��");
	}
}

void room_inside_text_1 ()	//������λѡ������ı�
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[2][0]+9,room_x_y[2][1]+2);
	printf ("ѡ�����λ����<ȷ��>");
	gotoxy (hOut,seat_num[2][0]-1,seat_num[43][1]+2);
	printf ("����\'<\'��\'>\'��ѡ�����λ");
}

void room_inside_text_2 (room *p)	//������ϰ�Ҳ鿴�����ı�
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[2][0]+12,room_x_y[2][1]+2);
	printf ("��λ��Ϊ��Ԥ��");
	gotoxy (hOut,seat_num[4][0],seat_num[43][1]+2);
	printf ("���ţ�%2d",p->checked_seat_num);
}

void fun_chose_seat (room *p)	//��λѡ���ܺ���
{
	int a;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	a = find_first_seat (p);
	do
	{
		gotoxy (hOut,seat_num[a][0],seat_num[a][1]);
		printf ("*");
		a = move_chosen_seat (a,p);
	} while (a);
}

int find_first_seat (room *p)	//���������С�Ŀ���λ����������λ���
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

int move_chosen_seat (int a,room *p)	//�ƶ�ѡ�����λ��겢������ӽ�����һ����λ
{
	int i;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned char kb;
	kb = getch ();
	gotoxy (hOut,seat_num[a][0],seat_num[a][1]);
	printf ("��");
	switch (kb)
	{
		case 0X1B:
			return 0;
		case 0X0D:
			gotoxy (hOut,seat_num[a][0],seat_num[a][1]);
			printf ("��");
			i = check_seat (a,p);
			return i;
		case 75:	//�����ƶ�
			if (a != 1)
				a = avlb_seat_num (a,3,p);
			return a;
		case 77:	//�����ƶ�
			if (a != 48)
				a = avlb_seat_num (a,4,p);
			return a;
		default :
			return a;
	}
}

int avlb_seat_num (int a,int direction,room *p)	//���ض�Ӧ��������Ŀ���λ���
{
	int mem=a;
	switch (direction)
	{
		case 3:	//�������
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
		case 4:	//���Ҳ���
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

void make_room_frame_onepage (int page_num,room *p)	//����һҳ����ѡ���
{
	int i=6,j,X,Y;
		for (j = 1;i--;j++)
		{
			X = room_x_y[j][0];Y = room_x_y[j][1];
			make_room_frame_one (X,Y);
			make_room_one_info (X,Y,p);
			p = p->next;
		}
}

int make_room_whole (int a)	//�������䲢����ҳ��
{
	int b,page_sum,X ,Y ,i = 1,j,loop;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!a)
	{
		cursor.x = FrameX+Frame_width-8; cursor.y = FrameY+9;
		gotoxy (hOut,cursor.x,cursor.y);
		printf ("û�п��õ���ϰ�ң����Ժ�����");
		gotoxy (hOut,FrameX+2*Frame_width+30,FrameY+11);
		return 0;
	}
	page_sum = a/6;
	p = (room *)malloc (sizeof(room));
	head = p;
	for (loop = a;loop != 0;loop--)
		make_room_one (a-loop+1);
	if (a%6)
		page_sum++;
	return page_sum;
}

void make_room_frame_one (int x,int y)	//����һ������ѡ���
{
	int i;
	const int WIDTH = 36,LENGTH = 5;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = x; cursor.y = y;
	gotoxy (hOut,cursor.x,cursor.y);
	printf ("��");
	gotoxy (hOut,cursor.x+WIDTH,cursor.y);
	printf ("�� ");
	gotoxy (hOut,cursor.x,cursor.y+LENGTH);
	printf ("��");
	gotoxy (hOut,cursor.x+WIDTH,cursor.y+LENGTH);
	printf ("�� ");
	for (i=1;WIDTH-i;i++)
	{
		gotoxy (hOut,cursor.x+i,cursor.y);
		printf ("��");
		gotoxy (hOut,cursor.x+i,cursor.y+LENGTH);
		printf ("��");
	}
	for (i=1;LENGTH-i;i++)
	{
		gotoxy (hOut,cursor.x,cursor.y+i);
		printf ("�� ");
		gotoxy (hOut,cursor.x+WIDTH,cursor.y+i);
		printf ("�� ");
	}
}

void make_room_frame_chosen_one (int x,int y)	//����һ����ѡ�еķ����
{
	int i;
	const int WIDTH = 36,LENGTH = 5;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = x; cursor.y = y;
	gotoxy (hOut,cursor.x,cursor.y);
	printf ("��");
	gotoxy (hOut,cursor.x+WIDTH,cursor.y);
	printf ("�� ");
	gotoxy (hOut,cursor.x,cursor.y+LENGTH);
	printf ("��");
	gotoxy (hOut,cursor.x+WIDTH,cursor.y+LENGTH);
	printf ("�� ");
	for (i=1;WIDTH-i;i++)
	{
		gotoxy (hOut,cursor.x+i,cursor.y);
		printf ("��");
		gotoxy (hOut,cursor.x+i,cursor.y+LENGTH);
		printf ("��");
	}
	for (i=1;LENGTH-i;i++)
	{
		gotoxy (hOut,cursor.x,cursor.y+i);
		printf ("�� ");
		gotoxy (hOut,cursor.x+WIDTH,cursor.y+i);
		printf ("�� ");
	}
}

void make_room_one (int a)	//����һ������ṹ��
{
	int i,j;
	srand ((unsigned int)time (NULL)+rand ());
	rear = p;
	p = (room *)malloc (sizeof(room));
	p->lost = rear;
	rear->next = p;
	p->num = 100*(1+(a-1)/8)+(a-1)%8+1;	//�����
	p->occupied = rand()%49;
	p->checked_seat_num = 0;
	total += p->occupied;
	for (i=0;i<p->occupied;i++)	//������ռ����λ���
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

void sort (int a[],room *p)	//������������Ԫ��
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

int search (int n,room *p)	//�����ṹ���������Ƿ��ж�ӦԪ��
{
	int i;
	for (i=0;i<p->occupied;i++)
	{
		if (n == p->occup_seat_num[i])
			return 1;
	}
	return 0;
}

void make_room_one_info (int x,int y,room *p)	//����һ��������Ϣ
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.x = x; cursor.y = y;
	gotoxy (hOut,cursor.x+1,cursor.y+1);
	printf (" %d",p->num);
	gotoxy (hOut,cursor.x+21,cursor.y+3);
	printf ("��ϰ��������%2d",p->occupied);
	gotoxy (hOut,cursor.x+23,cursor.y+1);
	printf ("          ");
	gotoxy (hOut,cursor.x+23,cursor.y+4);
	if (p->occupied == 48)
		printf ("����");
	else
		printf ("����λ����%2d",p->avlb);
	if (p->checked_seat_num != 0)
	{
		gotoxy (hOut,cursor.x+23,cursor.y+1);
		text_color (0,6);
		printf ("��λԤ����");
		text_color (15,16);
	}
}

int check_seat (int a,room *p)	//��λȷ�ϲ�����ȷ�����
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy (hOut,room_x_y[9][0]-7,room_x_y[9][1]-2);
	printf ("<ȷ��(Enter)>");
	gotoxy (hOut,room_x_y[9][0]-5,room_x_y[9][1]);
	printf ("<ȡ��(Esc)>");
	unsigned char kb;
	kb = getch ();
	switch (kb)
	{
		case 0X1B:
			gotoxy (hOut,seat_num[a][0],seat_num[a][1]);
			printf ("%2d",a);
			gotoxy (hOut,room_x_y[9][0]-7,room_x_y[9][1]-2);
			printf ("<ѡ��(Enter)>");
			gotoxy (hOut,room_x_y[9][0]-5,room_x_y[9][1]);
			printf ("<����(Esc)>");
			return a;
		case 0X0D:
			clean_screen (1);
			p->checked_seat_num = a;
			gotoxy (hOut,FrameX+Frame_width-12,FrameY+9);
			printf ("\a��λԤ���ɹ��� ���ţ�%d",a/*p->checked_seat_num*/);
			gotoxy (hOut,FrameX+2*Frame_width+30,FrameY+11);
			return 0;
	}
}
