/*������C++ʵ��
** Author�����ǳ�
**finish time: 2018.14.12 02.52
**������Date �����࣬������"-","<<",">","<"��"+"
**main�������������ַ���ʵ�� �û�ʹ�ø�����
**�����˼����������벻�Ϸ����쳣����
**���ܣ������������ĳ���µ�����������ĳ���������
        ����ĳ��������֮�������������ĳ������֮��n�������
**�����ʽ����
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime> 
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <iomanip>
#include <cassert>
#include <cctype>
#include <error.h>
#include <cfloat>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <windows.h>

//#define FILE_INPUT 666

using std::cin;
using std::cout;
using std::lower_bound;
using std::upper_bound;
using std::string;
using std::endl;
using std::ends;
using std::ostream;
using std::istream;
using std::setw;
using std::min;
using std::max;
using std::map;
using std::set;
using std::queue;
using std::vector;
using std::stack;
using std::deque;
 
//windows.h���ͷ�ļ��еĺ���
//Handle�Ǿ��
//foreground��ǰ������˼
//background�Ǳ�������˼ 
//intensity ��ǿ�ȣ�ǿ�ҵ���˼ 
//FOREGROUND_INTENSITY ��ʾǰ��ɫ��������ʾ 
//FOREGROUND_RED,FOREGROUND_BLUE,FOREGROUND_GREEN��Щ���Ǻ궨��õ�16���Ƴ���
//����˼�壬red���Ǻ�ɫ��green������ɫ��blue������ɫ
//��ô����Ҫ����õ�������ɫ��ô���أ�
//���ǿ��԰���ɫ���������ð�λ��| 
//��|��|�� ���Եõ� ��ɫ
//��|�� ���Եõ���ɫ
//��|�� ���Եõ���ɫ
//��|�� ���Եõ���ɫ
//���ǿ�����foreground��background �� color1[|color2][|color3][|INTENSITY]�������
//�Ӷ��õ�������Ҫ�����Ч��
 
#define RED    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED)
#define BLUE   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE)
#define GREEN  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN)
#define WHITE  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define CYAN   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define PURPLE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE)
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN)
#define B_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_RED)

//Sleep��������Ĳ�����ʾ��ͣ���г�����ٺ��� 
#define SL(time) Sleep(time)

//����forѭ���ĺ궨��
//һ����4�У��Ƿ���������䣬�Լ������������ǵݼ�����
//��Ϊforѭ���ڳ�����ʮ�ֳ��ã������궨����Դ��ӿ�д������ٶ� 
#define For(i,a,b) for(int i=(a); i<=(b); ++i)
#define Rep(i,a,b) for(int i=(a); i>=(b); --i)
#define _for(i,a,b) for(int i=(a); i<(b); ++i)
#define _rep(i,a,b) for(int i=(a); i>(b); --i)

//����long long �� memset�ĺ궨�� 
#define LL long long
#define Mst(a,b) memset(a,(b),sizeof(a))
#define CL(a) memset(a,0,sizeof(a))

#define pb push_back
#define L_b lower_bound
#define U_b upper_bound
#define MP(a,b) make_pair(a,b)

#define pii pair<int,int>
#define pil pair<int,long long> 
#define psi pair<string,int>
#define psl pair<string,long long>
#define pll pair<long long,long long>
#define For_it(v) for(it=v.begin(); it!=v.end(); ++it)
#define For_auto(v) for(auto it:v)

//���ֲ��� 
//�뿪��յ�д��
//������flagΪ0,��Ϊ���ұգ�
//flagΪ1��Ϊ����ҿ� 
//���ֿ���Ӧ���Ӿ����������
//�����ұգ��������ֵõ��Ĵ�Ϊright
//������ҿ����������ֵõ��Ĵ�Ϊleft
//���ֽ���֮��leftһ����rightҪС1 
#define bs(left,right,mid,flag)\
	while(right-left>1)\
	{\
		while(right-left>1)\
		{\
			mid = (left+right)>>1;\
			if(check(mid))\
			{\
				if(flag)\
				{\
					left = mid;\
				}\
				else\
				{\
					right = mid;\
				}\
			}\
			else\
			{\
				if(flag)\
				{\
					right = mid;\
				}\
				else\
				{\
					left = mid;\
				}\
			}\
		}\
}
//����binery_search��� 

#define lson (pos<<1)
#define rson (pos<<1|1)
#define Ldfs (left,mid)
#define Rdfs (mid+1,right)
 
const int maxyear = 100000 + 10;
int yearDays[maxyear] = {0,365};  //��ԪԪ����ƽ��
int weekdays[maxyear] = {0,1};  //��ԪԪ��һ��һ������һ
int monthday[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

//map  firstΪ���ڣ�second Ϊ�ַ�������������Ľ���
const int maxn = 1e6+10;
int notPrime[maxn];
int sushu[maxn/10],cntPrime;
void getPrime(int n,int flag=0)
{
	n = min(n,40000000);
	n = max(n,100);
	cntPrime = 0;
	for(int i=2;i<=n;++i)
	{
		if(!notPrime[i])
		{
			sushu[cntPrime] = i;
			cntPrime++;
		}
		for(int j=0; j<cntPrime&&1ll*i*sushu[j]<=n;++j)
		{
			int dele = i * sushu[j];
			notPrime[dele] = true;
			if(i%sushu[j]==0)
			{
				break;
			}
		}
	}
	if(!flag) 
	{
		return;
	}
	cout<<"��1��"<<n<<"һ����"<<cntPrime<<"��������\n";
	for(int i=0;i<cntPrime;++i)
	{
		cout<<setw(7)<<sushu[i]<<" ";
		//printf("%7d ",sushu[i]); 
		if((i+1)%10==0&&i) 
		{
			cout<<'\n';
			
		}
	}
	cout<<endl;
}
char cl[60][5] = {
				  "�ﺥ",
                  "����","�ҳ�","����","��î","�쳽","����","����","��δ","����","����",
                  "����","�Һ�","����","����","����","��î","����","����","����","��δ",
                  "����","����","����","����","����","����","����","��î","�ɳ�","����",
                  "����","��δ","����","����","����","����","����","����","����","��î",
                  "�׳�","����","����","��δ","����","����","����","����","����","���",
                  "����","��î","����","����","����","��δ","����","����","����",
};
                 
           
		   
/*
1��1��	Ԫ��
2��14��	���˽�
3��8��	��Ů��
3��15��	��������
4��1��	���˽�
5��1��	�Ͷ���
5�µ�2��������	ĸ�׽�
6��1��	��ͯ��
6�µ�3��������	���׽�
7��1��	������
8��1��	������
9��10��	���ҽ�
10��1��	�����
10��31��	��ʥҹ
11��1��	��ʥ��
11��11��	�����
11�µ�4��������	�ж���
12��24��	ƽ��ҹ
12��25��	ʥ����


*/      

bool isleap(int y)
{
	if((y%400==0)||(y%4==0&&y%100)) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}


void getWeekdays(void)   //Ԥ������ÿ��1��1�������ڼ�
{
	int i;
	for(i = 2; i < maxyear - 1; i++)
	{
		if(isleap(i))
		{
			yearDays[i] = 366;
		} 
		else
		{
			yearDays[i] = 365;
		}
		weekdays[i] = (yearDays[i-1] + weekdays[i-1] ) % 7;
	}
}


void printBlank(int n)
{
	int i;
	if(n==0)
	{
		for(i=1; i<7; i++)
		{
			printf("     ");
		}
	}
	else
	{
		for(i=1; i<n; i++)
		{
			printf("     ");
		}
	}
}


void printline(void)
{
	BLUE;
	printf("----------------------------------------------------\n");
}


class Date
{
	private:
		int year;
		int month;
		int day;
		int monthday[13];  //monthday[0]��Ϊ����������
		int daynum;
		bool leap;
	public:
		string festivalMessage; 
		Date(){}
		//�޲ι��캯�� 
		Date(int y=2019,int m=5,int d=25);
		void setDate(int y,int m,int d);
		void showDate();
		void showDayNumber();
		friend ostream& operator << (ostream& out,const Date& date)
		{
			out<<date.year<<"-"<<date.month<<"-"<<date.day;
			return out;
		}
		int dayNumber();  //����������ĵڼ���
		void showYear();  //������ʾ����
		void showMonth(); //������ʾ����
		void showDay();   //���µ�������ͻ����ʾ����
		void showMonthDay();//��ʾ����ÿ���¶�����
		
		friend int operator - (Date a,Date b);
		Date operator +  (int d);
		Date operator += (int d);
		Date operator ++();
		Date operator ++(int y);
		Date operator = (Date a);

		friend bool operator < (Date a,Date b);
		friend bool operator > (Date a,Date b);
		friend bool operator == (Date a,Date b);

};

map<Date,string> festivals; 


Date::Date(int y,int m,int d)          //���캯��
{
	if(y>0&&y<100000)
	{
		year = y;
	}
	else
	{
		cout<<"��ݲ��Ϸ���\n";
		year = 2000;
	}
	if((year%400==0)||(year%4==0&&year%100))
	{
		leap = true;
	}
	else
	{
		leap = false;
	}
	if(m>0&&m<=12)
	{
		month = m;
	}
	else
	{
		cout<<"�·ݲ��Ϸ���\n";
		month = 1;
	}
	int i;
	monthday[0] = 365;
	for(i=1; i<=12; i++)
	{
		if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
		{
			monthday[i] = 31;
		}
		else
		{
			monthday[i] = 30;
		}
	}
	if(leap)
	{
		monthday[2] = 29;
		monthday[0] = 366;
	}
	else 
	{
		monthday[2] = 28;
	}
	if(month!=2)
	{
		if(d>0&&d<=monthday[month]) 
		{
			day = d;
		}
		else 
		{
			cout<<"���ڲ��Ϸ���\n";
		}
	}
	else
	{
		if(leap)
		{
			if(d>0&&d<=29) 
			{
				day = d;
			}
			else 
			{
				cout<<"����2�����ڲ��Ϸ���\n";
			}
		}
		else
		{
			if(d>0&&d<=28) 
			{
				day = d;
			}
			else 
			{
				cout<<"ƽ��2�����ڲ��Ϸ���\n";
			}
		}
	}
	daynum = dayNumber();
}


void Date::setDate(int y=2019,int m=5,int d=25)    //��������
{
	if(y>0&&y<100000) year = y;
	else
		cout<<"��ݲ��Ϸ���\n";
	if(isleap(year)) leap = true;
	else leap = false;
	if(leap)
	{
		monthday[2] = 29;
		monthday[0] = 366;
	}
	else
	{
		monthday[2] = 28;
		monthday[0] = 365;
	}
	if(m>0&&m<=12)    
	{
		month = m;
	}
	else 
	{
		cout<<"�·ݲ��Ϸ���\n";
	}
	if(m!=2)
	{
		if(d>0&&d<=monthday[month]) day = d;
		else cout<<"���ڲ��Ϸ���\n";
	}
	else
	{
		if(leap)
		{
			if(d>0&&d<=29) day = d;
			else cout<<"���ڲ��Ϸ���\n";
		}
		else
		{
			if(d>0&&d<=28) day = d;
			else cout<<"���ڲ��Ϸ���\n";
		}
	}
	daynum = dayNumber();
}


void Date::showDate()
{
	printf("%04d��%02d��%02d��",year,month,day);
}


void Date::showDayNumber()
{
	cout<<*this<<"��"<<year<<"��ĵ�"<<daynum<<"��\n";
}

void Date::showMonthDay()
{
	for(int i=0; i<=12; i++)
		cout<<monthday[i]<<" ";
	cout<<endl;
}


Date Date::operator = (Date a)                  //���� =
{
	year = a.year;
	month = a.month;
	day = a.day;
	leap = a.leap;
	daynum = a.daynum;
	monthday[0] = a.monthday[0];
	monthday[2] = a.monthday[2];
	return *this;
}


bool operator < (Date a,Date b)                //���� <
{
	if(a.year!=b.year) return(a.year<b.year);
	else if(a.month!=b.month) return(a.month<b.month);
	else return(a.day<b.day);
}

bool operator > (Date a,Date b)               //���� >
{
	if(a.year!=b.year) return(a.year>b.year);
	else if(a.month!=b.month) return(a.month>b.month);
	else return(a.day>b.day);
}


bool operator == (Date a,Date b)             //���� ==
{
	if(a.year==b.year&&a.month==b.month&&a.day==b.day) 
	{
		return true;		
	}
	else 
	{
		return false;
	}
}


int Date::dayNumber()
{
	int ans = 0;
	for(int i=1; i<month; i++)
		ans += monthday[i];
	ans += day;
	return ans;
}


int operator - (Date a,Date b)             //���� - (����)�����ڼ�����������֮������
{
	int judge(1),ans(0);
	if(a<b)     //��Ϊ�Ѿ�������С�ں�
	{
		Date temp = a;
		a = b;
		b = temp;
		judge = -1;
	}
	for(int i=b.year; i<a.year; i++)
	{
		if(isleap(i)) ans += 366;
		else ans += 365;
	}
	ans = ans + a.dayNumber() - b.dayNumber();
	ans *= judge;
	return ans;
}


///////////////////////////////////////////////////////////////////////////////////////////

Date Date::operator +=(int d)             //���� += (Date + int) ���ڸ�������    ������
{
	if(d<0) d *=-1;
	while(d+daynum>monthday[0])
	{
		year++;
		month = day = 1;
		d = d + daynum - monthday[0];
		cout<<"���ڼ���һ�ꡣ\n";
		cout<<"��ǰ����Ϊ��"<<*this<<"  add = "<<d<<endl;
	}
	while(day+d>monthday[month])
	{
		cout<<"���ڼ���һ���¡�\n";
		month++;
		day = 1;
		d = d + day - monthday[month];
		if(month==13)
		{
			month = 1;
			year++;
			cout<<"�·�13��ʹ���ڼ���һ�ꡣ\n";
		}
		cout<<"��ǰ����Ϊ��"<<*this<<"  add = "<<d<<endl;
	};
	day = day + d;
	//��ûд��
	return *this;
}


///////////////////////////////////////////////////////////////////////////////////////////

Date Date::operator +(int d)
{
	Date aa = *this;
	int yy = aa.year,mm = aa.month;
	while(d + aa.daynum>aa.monthday[0])
	{
		d = d + aa.daynum - aa.monthday[0] - 1;
		yy = aa.year + 1;
		aa.setDate(yy,1,1);
		cout<<"������1��\n";
		cout<<"��ǰ����Ϊ��"<<aa<<"  add = "<<d<<endl;
	}
	while(d + aa.day>aa.monthday[month])
	{
		d = d + aa.day - aa.monthday[month] - 1;
		yy = aa.year;
		mm = aa.month + 1;
		if(mm<13)
		{
			aa.setDate(yy,mm,1);
			cout<<"������1\n";
		}
		else
		{
			yy++;
			aa.setDate(yy,1,1);
			cout<<"������1,��Ҳ��һ���±�1���ձ�1\n";
		}
		cout<<"��ǰ����Ϊ��"<<aa<<"  add = "<<d<<endl;
	}
	aa.day += d;
	return aa;
}


Date Date:: operator ++()
{
	if(day==monthday[month])
	{
		day = 1;
		month++;
	}
	else day++;
	if(month==13)
	{
		year++;
		month = 1;
	}
	return *this;
}


Date Date:: operator ++(int y)
{
	if(day==monthday[month])
	{
		day = 1;
		month++;
	}
	else day++;
	if(month==13)
	{
		year++;
		month = 1;
	}
	return *this;
}


void Date::showYear()
{
	printline();
	int i,j,totalDays = (weekdays[year] + 6) % 7;
	YELLOW;

	printf("\n             ��Ԫ%04d��(%s��)\n\n",year,cl[(year+57)%60]);
	for(i = 1; i < 13; i++)
	{
		GREEN;
		cout<<"      һ   ��   ��   ��   ��   ��   ��"<<endl;
		cout<<"      Mon. Tue. Wed. Thur.Fri. Sat. Sun."<<endl; 
		BLUE;
//		if(showMonth())
//		{
			cout<<setw(2)<<i<<"�£�";
//		}
		PURPLE;
		if(i==1)
			printBlank(weekdays[year]);
		else
			printBlank(totalDays % 7 + 1);
		for(j = 1; j<=monthday[i]; j++)
		{
			totalDays++;
			cout<<setw(2)<<j<<"   ";
			if((totalDays) % 7==0)
			{
				cout<<endl;
				cout<<"      ";
			}
		}
		cout<<endl;
		//printline();
		cout<<endl;
	}
	printline();
	printf("\n");
}


void Date::showMonth()
{
	printline();
	int i,j;
	int totalDays = (weekdays[year] + 6) % 7;
	YELLOW;
	printf("\n               ��Ԫ%04d��%02d��\n\n",year,month);
	for(i=1; i<month; i++)
		totalDays += monthday[i];

	GREEN;
	cout<<"      һ   ��   ��   ��   ��   ��   ��"<<endl;
	cout<<"      Mon. Tue. Wed. Thur.Fri. Sat. Sun."<<endl; 
	BLUE;
//	cout<<setw(2)<<month<<"�£�";
	cout<<"      ";
	PURPLE;
	printBlank(totalDays % 7 + 1);
	for(j = 1; j<=monthday[month]; j++)
	{
		totalDays++;
		cout<<setw(2)<<j<<"   ";
		if((totalDays) % 7==0)
		{
			cout<<endl;
			cout<<"      ";
		}
	}
	cout<<endl;
	printline();
	cout<<endl;
}


void Date::showDay()
{

	printline();
	int i,j;
	int totalDays = 0;
	YELLOW;
	printf("\n               ��Ԫ%04d��%02d��\n\n",year,month);
	for(i=1; i<month; i++)
		totalDays += monthday[i];
	int tt = totalDays;
	totalDays += (weekdays[year] + 6) % 7;

	GREEN;
	cout<<"      һ     ��    ��    ��    ��    ��    �� "<<endl;
	cout<<"      Mon.  Tue.  Wed.  Thur. Fri.  Sat.  Sun."<<endl; 
	BLUE;
//	cout<<setw(2)<<month<<"�£�";
	cout<<"         ";
	PURPLE;
	printBlank(totalDays % 7 + 1);
	for(j = 1; j<=monthday[month]; j++)
	{
		totalDays++;
		if(j==day) RED;
		cout<<setw(2)<<j<<"    ";
		PURPLE;
		if((totalDays) % 7==0)
		{
			cout<<endl;
			cout<<"       ";
		}
	}
	cout<<endl;
	YELLOW;
	tt += day;
	int weekk = (tt + weekdays[year] + 6) % 7;
	char weekker[3];
	switch(weekk)
	{
		case 0:
			strcpy(weekker,"��");
			break;
		case 1:
			strcpy(weekker,"һ");
			break;
		case 2:
			strcpy(weekker,"��");
			break;
		case 3:
			strcpy(weekker,"��");
			break;
		case 4:
			strcpy(weekker,"��");
			break;
		case 5:
			strcpy(weekker,"��");
			break;
		case 6:
			strcpy(weekker,"��");
			break;
	}
	printf("\n      %04d��%02d��%02d��������%s,������%04d��ĵ�%d��\n",year,month,day,weekker,year,tt);
	printline();
	cout<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initMapFestivals()
{
	Date date1(1,1);
	string FestivalName;
	FestivalName = "Ԫ��";
	festivals[date1] = FestivalName;
	
	date1.setDate(2,14);
	FestivalName = "���˽�";
	festivals[date1] = FestivalName; 
	
	date1.setDate(3,8);
	FestivalName = "��Ů��";
	festivals[date1] = FestivalName; 
	

} 



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Bye(void)
{
	cout<<endl<<endl;
	char ch[] = "Bye-bye!See you next time!";
	for(int i=0; ch[i]!='\0'; i++)
	{
		switch(i%6)
		{
			case 0:
				PURPLE;
				cout<<ch[i];
				break;
			case 1:
				GREEN;
				cout<<ch[i];
				break;
			case 2:
				YELLOW;
				cout<<ch[i];
				break;
			case 3:
				RED;
				cout<<ch[i];
				break;
			case 4:
				BLUE;
				cout<<ch[i];
				break;
			case 5:
				CYAN;
				cout<<ch[i];
				break;
		}
		if(ch[i]==' ') SL(100);
		else SL(300);
	}
	WHITE;
}


void showCurrentDateAndTime(int flag=1)
{
	time_t timep;
    struct tm * p;
    time (&timep);
    p=gmtime(&timep);
    int Year = 1900+p->tm_year;
    int Month = 1+p->tm_mon;
    int Day = p->tm_mday;
    int Hour = 8+p->tm_hour;
    int Minute = p->tm_min;
    int Second = p->tm_sec;
    cout<<"�����Ǳ���ʱ��: ";
	printf("%04d��%02d��%02d�� %02d:%02d:%02d",Year,Month,Day,Hour,Minute,Second);
	if(flag) 
	{
		cout<<"\n";	
	} 
//    printf("%d\n",p->tm_sec); /*��ȡ��ǰ��*/
//    printf("%d\n",p->tm_min); /*��ȡ��ǰ��*/
//    printf("%d\n",8+p->tm_hour);/*��ȡ��ǰʱ,�����ȡ������ʱ��,�պ����˸�Сʱ*/
//    printf("%d\n",p->tm_mday);/*��ȡ��ǰ�·�����,��Χ��1-31*/
//    printf("%d\n",1+p->tm_mon);/*��ȡ��ǰ�·�,��Χ��0-11,����Ҫ��1*/
//    printf("%d\n",1900+p->tm_year);/*��ȡ��ǰ���,��1900��ʼ������Ҫ��1900*/
//    printf("%d\n",p->tm_yday); /*�ӽ���1��1�������������������ΧΪ0-365*/	
} 


void showCalendarFunction()
{
		YELLOW;
	cout<<" _____________________________________________________________________________"<<endl;
	cout<<"|                            ";
	GREEN;
	cout<<"      ������                                     ";
	YELLOW;
	cout<<"|"<<endl;
	cout<<"|-----------------------------------------------------------------------------|"<<endl;
	cout<<"| -  ��ϵͳ�Ĳ�ѯ�������£�                                                   |"<<endl; 
	cout<<"|       ����ѯ������ݵ�������Ϣ                                              |"<<endl;
	cout<<"|       ����ѯĳһ�������ڼ����Ǹ���ĵڼ���                                  |"<<endl;
	cout<<"|       ��������ݣ��������ݵ�����                                          |"<<endl; 
	cout<<"|       ���������£��������ݸ��µ�����                                      |"<<endl;
	cout<<"|       �����������գ���������ڸ�����µ�λ����Ϣ                            |"<<endl;
	cout<<"|       ����ѯ��ǰ������ʱ��                                                  |"<<endl;                                      
	cout<<"| -  ��ϵͳ�ļ��㹦�����£�                                                   |"<<endl; 
	cout<<"| 	   ���������������㵱ǰ���ڸ������������                             |"<<endl;
	cout<<"|	   �����㵱ǰ���ں��ϴ������������������                             |"<<endl; 
	cout<<"|ע�⣺��������ֿ�����������ո��������һ�������뼴��                       |"<<endl;//����ɫ��
	  	//���������й��ܶ�����˵���� 
	cout<<"|-----------------------------------------------------------------------------|"<<endl;
	cout<<"|_______________________________Designed_by_XZC_______________________________|"<<endl;
	cout<<endl<<endl;
	SL(1000);
	WHITE;
} 


///////////////////////////////////// ____main() ____///////////////////////////////////////////////////////////

int main()
{
	//�������� 
	#ifdef FILE_INPUT
	//����궨���� FILE_INPUT �ʹ��ļ�in.txt������
//���н�������out.txt�ļ��� 
		freopen("in.txt","r",stdin);
		freopen("out1.txt","w",stdout);
	#endif
	//�����������
	 
	#ifdef GETPRIME
		getPrime(1000000,0);
	#endif
	getPrime(40000000,1);
	return 0;
	PURPLE;
	showCurrentDateAndTime(0);
	SL(1500);
	printf("\r");
	for(int i=0;i<40;++i)
	{
		SL(35);
		printf(" ");
	}
	printf("\r");
	/*Date a;
	a.showDate();
	a.setDate(2003,12,-3);
	a.showDate();
	Date b(2004,12,19);
	b.showDate();
	Date c(b);
	cout<<c;
	cout<<b;
	if(a>b) cout<<"����\n";
	if(b==c) cout<<"����\n";
	cout<<b-a<<endl;
	Date dd1(1998,3,31),dd2(2015,1,1);
	cout<<dd1<<endl;
	dd1 = dd2;
	cout<<dd1<<endl;
	int add;
	cout<<"���������ӵ�������";
	while(cin>>add){
		//cout<<dd1+add<<endl;
		dd1 = dd1 + add;
		cout<<dd1<<endl;
		cout<<"������������ӵ�����(0 to quit)��";
	}
	dd1.showDayNumber();
	cout<<endl;
	dd1.showMonthDay();
	cout<<endl;
	dd1.showDate();
	dd1++;
	dd1.showDate();
	cout<<dd1++<<endl;//��������õ�++�������� */
	Date date1(2019,5,25);
	Date date2(date1);
	system("title ������by xzc");
	int flag = 1,i;
	int day,month,year;
	YELLOW;
	SL(1000);
	showCalendarFunction();
//	printf("��������\n");
//	printf("Design by ���ǳ���\n");
//	cout<<"1.��ѯĳ����������������;       2.��ѯ�����·������������; \n";
//	cout<<"3.��ѯ���������������ꡢ�¡���;   4.��ѯ�������ڼ��������ֻ���ظ�3;\n";
//	WHITE;

	BLUE;
	printf("--------------------------------------------------------------------------------\n");
	getWeekdays();
	GREEN;
	char demo[] = "����������\n";
	for(i=0; demo[i]!='\0'; i++)
	{
		printf("%c",demo[i]);
		SL(100);
	}
	WHITE;
	SL(500);
	printf("�����룺____\b\b\b\b");
	CYAN;
	SL(1000);
	char example[] = "2019 5 25";
	for(i=0; example[i]!='\0'; i++)
	{
		printf("%c",example[i]);
		SL(200);
	}
	SL(500);
	cout<<endl;
	date1.setDate(2019,5,25);
	date1.showDay();
	int taps(0);
	while(flag)
	{
		year = month = day = -5;
		char date[100];
		WHITE;
		cout<<"�����룺____\b\b\b\b";
		CYAN;
		gets(date);
		//cin.getline(date,100);
		int leng = strlen(date);
		if(strcmp(date,"quit")==0) break;
		int judge = 0;
		for(int i=0; i<leng; i++)
			if((date[i]<'0'||date[i]>'9')&&date[i]!=' ')
			{
				RED;
				cout<<"�������з����ֵķǷ��ַ���\n";
				judge = 1;
				break;
			}
		sscanf(date,"%d %d %d",&year,&month,& day);
		if(year>100000||year==0)
		{
			RED;
			cout<<"��ݲ��Ϸ���\n";
			judge = 1;
		}
		if(month>12||month==0)
		{
			RED;
			cout<<"�·ݲ��Ϸ���\n";
			judge = 1;
		}
		bool leapp = isleap(year);
		if(leapp) monthday[2] = 29;
		else monthday[2] = 28;
		if(month<13&&(day>monthday[month]||day==0))
		{
			RED;
			cout<<"���ڲ��Ϸ���\n";
			judge = 1;
		}
		if(judge) continue;

		//cout<<year<<" "<<month<<" "<<day<<endl;
		int kase;
		if(month==-5&&day==-5) kase = 1;
		else if(month!=-5&&day==-5) kase = 2;
		else
		{
			kase = 3;
			taps++;
		}
		switch(kase)
		{
			case 1:
				date1.setDate(year,1,1);
				date1.showYear();
				break;
			case 2:
				date1.setDate(year,month,1);
				date1.showMonth();
				break;
			case 3:
			{
				if(taps%2)
				{
					date1.setDate(year,month,day);
					date1.showDay();
				}
				else
				{
					date2.setDate(year,month,day);
					date2.showDay();
				}
				int daysbetween = 0;
				daysbetween = abs(date2 - date1);
				GREEN;
				cout<<min(date1,date2)<<" �� "<<max(date1,date2)<<" ֮�����"<<daysbetween<<"��\n\n";
				WHITE;
				int nextuse = 0,adddays;
				Date date3(2019,5,25);
				cout<<"���������֮���������������������1������������0��\n_\b";
				CYAN;
				cin>>nextuse;
				if(nextuse)
				{
					while(1)
					{
						WHITE;
						if(taps%2)  cout<<"������Ҫ��"<<date1<<"�ӵ�����(0 to quit)��";
						else  cout<<"������Ҫ��"<<date2<<"�ӵ�����(0 to quit)��";
						CYAN;
						cin>>adddays;
						if(adddays==0) break;
						if(taps%2)
						{
							date3 = date1 + adddays;
							cout<<"��"<<date1<<"��ʼ��"<<adddays<<"��֮�������Ϊ"<<date3<<endl;
							date3.showDay();
						}
						if(taps%2==0)
						{
							date3 = date2 + adddays;
							cout<<"��"<<date2<<"��ʼ��"<<adddays<<"��֮�������Ϊ"<<date3<<endl;
							date3.showDay();
						}
					}
				}

				break;
			}
			default:
				cout<<"��ûд�á�\n";
		}
		WHITE;
		cout<<"�˳���0��������1,�����������밴2,��ʾ��ǰʱ���밴3����������ʾ��ǰʱ���밴4��_\b";
		cin>>flag;
		getchar();
		if(flag==3)
		{
			PURPLE;
			showCurrentDateAndTime();
			continue;
		}
		if(flag==2||flag==4)
		{
			system("CLS");
			YELLOW;
			printf("��������\n");
			printf("Design by ���ǳ���\n");

			cout<<"1.��ѯĳ����������������;       2.��ѯ�����·������������; \n";
			cout<<"3.��ѯ���������������ꡢ�¡���;   4.��ѯ�������ڼ��������ֻ���ظ�3;\n";
			WHITE;
			cout<<"(�������������������ո����������һ��������)\n";
			BLUE;
			printf("--------------------------------------------------------------------------------\n");
			if(flag==4)
			{
				PURPLE;
				showCurrentDateAndTime(); 
			}
		}
		
	
	}

	Bye();
	system("pause");
	
	//�������� 
	#ifdef FILE_INPUT
	//���֮ǰ�궨���� FILE_INPUT,��ô�ʹ����ļ�in.txt��out.txt
	//��ô�ڳ������н���֮ǰһ��Ҫ�ر��ļ�ָ�� 
		fclose(stdin);
		fclose(stdout);
	//�ر��������ļ�������ļ� 
	#endif 
	//����������� 

	return 0;
}
