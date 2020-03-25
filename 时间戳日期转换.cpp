#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
#define RED    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED)
#define BLUE   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE)
#define GREEN  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN)
#define WHITE  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define CYAN   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define PURPLE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE)
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN)
#define LL long long
using namespace std;
const int maxn = 1e5 + 20;
const int DaySeconds = 3600 * 24;
const int YearSeconds = 365 * DaySeconds;
const int LeapYearSeconds = 366 * DaySeconds;
int monthday[15] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int sumOfMonthDay[15]; //��¼ ��ĳ�꿪ʼ�� i �½���������
LL record[maxn];  //��¼����1.1.00:00:00�� 1970.1.1.00:00:00������
bool isleap(int y)
{
	if(y%4==0&&y%100||y%400==0) return true;
	return false;
}
void init()
{
	for(int i=1971; i<maxn; i++)
	{
		if(isleap(i-1)) record[i] = record[i-1] + LeapYearSeconds;
		else record[i] = record[i-1] + YearSeconds;
	}
	for(int j=1; j<=12; j++)
		sumOfMonthDay[j] = monthday[j] + sumOfMonthDay[j-1];
}
void toDate();
void toTimeStamp();
int main()
{
	system("title ʱ�������ת�� by xzc");
	init();
	CYAN;
	printf("Design by ���ǳ���\n\n");
	int i,j,t;
	YELLOW;
	printf("ʱ���");
	printf("�Ķ����Ǵ�1970.1.1 00:00:00����ǰʱ�������\n\n");
	PURPLE;
	printf("һ����%d�룬ƽ����%d�룬������%d��\n\n",DaySeconds,YearSeconds,LeapYearSeconds);
	while(1)
	{
		WHITE;
		printf("������������1; ��ʱ���������2; �˳�������0 : _\b");
		CYAN;
		scanf("%d",&t);
		if(t==0) break;
		if(t==1) toDate();
		else if(t==2) toTimeStamp();
		else
		{
			RED;
			printf("�������\n");
		}
		printf("\n");
	}
	YELLOW;
	printf("Bye-Bye!\n");
	Sleep(1000);
	return 0;
}
void toDate()
{
	long long x;
	int i;
	WHITE;
	printf("������ʱ�����");
	CYAN;
	scanf("%I64d",&x);
	if(x<0) x = 0;
	//x = min(x,3093528067200ll);
	x = min(x,3093559603199ll);
	long long temp = x;
	int year = 1970,month = 1,day = 1,hour = 0,minute = 0,second = 0;
	year = lower_bound(record,record+maxn,x) - record - 1;
	year = max(year,1970);//��x=0,lowerbond���ҵ�ʱ����ҵ�0
	//cout<<"���ֲ��ҳ��������"<<year<<endl;
	if(record[year+1]==x)
	{
		year++;
		GREEN;
		printf("ʱ��� %I64d ����Ӧ��",temp);
		printf("����Ϊ ");
		YELLOW;
		printf("%04d-%02d-%02d %02d:%02d:%02d\n",year,month,day,hour,minute,second);
		return;
	}
	if(isleap(year)) monthday[2] = 29;
	else monthday[2] = 28;
	x -= record[year];
	for(i=1; i<=12; i++)
	{
		if(x>=monthday[i]*DaySeconds)
		{
			x -= monthday[i]*DaySeconds;
			month++;
		}
		else break;
	}
	day = x / DaySeconds + (x%DaySeconds!=0);
	day = max(day,1);
	x -= (day-1) * DaySeconds;
	if(x>0) hour = x / 3600;
	x-= hour * 3600;
	if(x>0) minute = x / 60;
	second = x - minute * 60;
	GREEN;
	printf("ʱ��� %I64d ����Ӧ��",temp);
	printf("����Ϊ ");
	YELLOW;
	printf("%04d-%02d-%02d %02d:%02d:%02d\n",year,month,day,hour,minute,second);
}
void toTimeStamp()
{
	int year,month=1,day=1,hour=0,minute=0,second=0,i,j;
	WHITE;
	printf("�������ꡢ�¡��գ�\n");
	CYAN;
	scanf("%d%d%d",&year,&month,&day);
	year = max(year,1970);
	year = min(year,100000);
	long long ans = record[year];
	if(isleap(year))
	{
		for(i=2; i<=12; i++) sumOfMonthDay[i]++;
	}
	if(month>12||month<1) month = 1;
	if(day>monthday[month]||day<1) day = 1;
	ans += (sumOfMonthDay[month-1] + day - 1) * DaySeconds;
	WHITE;
	printf("������ʱ���֡���\n");
	CYAN;
	scanf("%d%d%d",&hour,&minute,&second);
	hour = max(hour,0) ;
	minute = max(minute,0) ;
	second = max(second,0) ;
	hour = min(hour,23);
	minute = min(minute,59);
	second = min(second,59);
	ans += hour * 3600 + minute * 60 + second;
	GREEN;
	printf("%04d-%02d-%02d %02d:%02d:%02d ��ʱ���Ϊ ",year,month,day,hour,minute,second);
	YELLOW;
	printf("%I64d\n",ans);
}
