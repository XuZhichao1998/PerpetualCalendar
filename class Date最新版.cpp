/*万年历C++实现
** Author：许智超
**finish time: 2018.14.12 02.52
**定义了Date 日期类，重载了"-","<<",">","<"，"+"
**main函数中输入由字符串实现 用户使用更方便
**考虑了几乎所有输入不合法的异常处理
**功能：输出万年历、某个月的日历、具体某天的日历。
        具体某两个日期之间的天数。计算某个日期之后n天的日期
**输出样式美观
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
 
//windows.h这个头文件中的函数
//Handle是句柄
//foreground是前景的意思
//background是背景的意思 
//intensity 是强度，强烈的意思 
//FOREGROUND_INTENSITY 表示前景色都高亮显示 
//FOREGROUND_RED,FOREGROUND_BLUE,FOREGROUND_GREEN这些都是宏定义好的16进制常量
//顾名思义，red就是红色，green就是绿色，blue就是蓝色
//那么我们要是想得到更多颜色怎么办呢？
//我们可以吧颜色混起来，用按位或| 
//红|蓝|绿 可以得到 白色
//蓝|绿 可以得到青色
//红|蓝 可以得到紫色
//红|绿 可以得到黄色
//我们可以用foreground、background 和 color1[|color2][|color3][|INTENSITY]任意组合
//从而得到我们想要的输出效果
 
#define RED    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED)
#define BLUE   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE)
#define GREEN  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN)
#define WHITE  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define CYAN   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN)
#define PURPLE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE)
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN)
#define B_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_RED)

//Sleep函数里面的参数表示暂停运行程序多少毫秒 
#define SL(time) Sleep(time)

//关于for循环的宏定义
//一共有4中，是否包括右区间，以及递增遍历还是递减遍历
//因为for循环在程序中十分常用，这样宏定义可以大大加快写代码的速度 
#define For(i,a,b) for(int i=(a); i<=(b); ++i)
#define Rep(i,a,b) for(int i=(a); i>=(b); --i)
#define _for(i,a,b) for(int i=(a); i<(b); ++i)
#define _rep(i,a,b) for(int i=(a); i>(b); --i)

//关于long long 和 memset的宏定义 
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

//二分查找 
//半开半闭的写法
//若参数flag为0,则为左开右闭，
//flag为1则为左闭右开 
//两种开闭应该视具体情况而定
//若左开右闭，则最后二分得到的答案为right
//若左闭右开，则最后二分得到的答案为left
//二分结束之后left一定比right要小1 
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
//二分binery_search完毕 

#define lson (pos<<1)
#define rson (pos<<1|1)
#define Ldfs (left,mid)
#define Rdfs (mid+1,right)
 
const int maxyear = 100000 + 10;
int yearDays[maxyear] = {0,365};  //公元元年是平年
int weekdays[maxyear] = {0,1};  //公元元年一月一号是周一
int monthday[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

//map  first为日期，second 为字符串，代表这天的节日
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
	cout<<"从1到"<<n<<"一共有"<<cntPrime<<"个素数。\n";
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
				  "癸亥",
                  "甲子","乙丑","丙寅","丁卯","戊辰","己巳","庚午","辛未","壬申","癸酉",
                  "甲戌","乙亥","丙子","丁丑","戊寅","己卯","庚辰","辛巳","壬午","癸未",
                  "甲申","乙酉","丙戌","丁亥","戊子","己丑","庚寅","辛卯","壬辰","癸巳",
                  "甲午","乙未","丙申","丁酉","戊戌","己亥","庚子","辛丑","壬寅","癸卯",
                  "甲辰","乙巳","丙午","丁未","戊申","己酉","庚戌","辛亥","壬子","癸丑",
                  "甲寅","乙卯","丙辰","丁巳","戊午","己未","庚申","辛酉","壬戌",
};
                 
           
		   
/*
1月1日	元旦
2月14日	情人节
3月8日	妇女节
3月15日	消费者日
4月1日	愚人节
5月1日	劳动节
5月的2个星期日	母亲节
6月1日	儿童节
6月第3个星期日	父亲节
7月1日	建党节
8月1日	建军节
9月10日	教室节
10月1日	国庆节
10月31日	万圣夜
11月1日	万圣节
11月11日	光棍节
11月第4个星期四	感恩节
12月24日	平安夜
12月25日	圣诞节


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


void getWeekdays(void)   //预处理，求每年1月1日是星期几
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
		int monthday[13];  //monthday[0]记为该年总天数
		int daynum;
		bool leap;
	public:
		string festivalMessage; 
		Date(){}
		//无参构造函数 
		Date(int y=2019,int m=5,int d=25);
		void setDate(int y,int m,int d);
		void showDate();
		void showDayNumber();
		friend ostream& operator << (ostream& out,const Date& date)
		{
			out<<date.year<<"-"<<date.month<<"-"<<date.day;
			return out;
		}
		int dayNumber();  //这天是这年的第几天
		void showYear();  //按年显示日历
		void showMonth(); //按月显示日历
		void showDay();   //在月的日历中突出显示这天
		void showMonthDay();//显示该年每个月多少天
		
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


Date::Date(int y,int m,int d)          //构造函数
{
	if(y>0&&y<100000)
	{
		year = y;
	}
	else
	{
		cout<<"年份不合法！\n";
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
		cout<<"月份不合法！\n";
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
			cout<<"日期不合法！\n";
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
				cout<<"闰年2月日期不合法！\n";
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
				cout<<"平年2月日期不合法！\n";
			}
		}
	}
	daynum = dayNumber();
}


void Date::setDate(int y=2019,int m=5,int d=25)    //重置日期
{
	if(y>0&&y<100000) year = y;
	else
		cout<<"年份不合法！\n";
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
		cout<<"月份不合法！\n";
	}
	if(m!=2)
	{
		if(d>0&&d<=monthday[month]) day = d;
		else cout<<"日期不合法！\n";
	}
	else
	{
		if(leap)
		{
			if(d>0&&d<=29) day = d;
			else cout<<"日期不合法！\n";
		}
		else
		{
			if(d>0&&d<=28) day = d;
			else cout<<"日期不合法！\n";
		}
	}
	daynum = dayNumber();
}


void Date::showDate()
{
	printf("%04d年%02d月%02d日",year,month,day);
}


void Date::showDayNumber()
{
	cout<<*this<<"是"<<year<<"年的第"<<daynum<<"天\n";
}

void Date::showMonthDay()
{
	for(int i=0; i<=12; i++)
		cout<<monthday[i]<<" ";
	cout<<endl;
}


Date Date::operator = (Date a)                  //重载 =
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


bool operator < (Date a,Date b)                //重载 <
{
	if(a.year!=b.year) return(a.year<b.year);
	else if(a.month!=b.month) return(a.month<b.month);
	else return(a.day<b.day);
}

bool operator > (Date a,Date b)               //重载 >
{
	if(a.year!=b.year) return(a.year>b.year);
	else if(a.month!=b.month) return(a.month>b.month);
	else return(a.day>b.day);
}


bool operator == (Date a,Date b)             //重载 ==
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


int operator - (Date a,Date b)             //重载 - (减号)，用于计算两个日期之间相差几天
{
	int judge(1),ans(0);
	if(a<b)     //因为已经重载了小于号
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

Date Date::operator +=(int d)             //重载 += (Date + int) 用于更新日期    有问题
{
	if(d<0) d *=-1;
	while(d+daynum>monthday[0])
	{
		year++;
		month = day = 1;
		d = d + daynum - monthday[0];
		cout<<"日期加了一年。\n";
		cout<<"当前日期为："<<*this<<"  add = "<<d<<endl;
	}
	while(day+d>monthday[month])
	{
		cout<<"日期加了一个月。\n";
		month++;
		day = 1;
		d = d + day - monthday[month];
		if(month==13)
		{
			month = 1;
			year++;
			cout<<"月份13，使日期加了一年。\n";
		}
		cout<<"当前日期为："<<*this<<"  add = "<<d<<endl;
	};
	day = day + d;
	//还没写完
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
		cout<<"年增加1。\n";
		cout<<"当前日期为："<<aa<<"  add = "<<d<<endl;
	}
	while(d + aa.day>aa.monthday[month])
	{
		d = d + aa.day - aa.monthday[month] - 1;
		yy = aa.year;
		mm = aa.month + 1;
		if(mm<13)
		{
			aa.setDate(yy,mm,1);
			cout<<"月增加1\n";
		}
		else
		{
			yy++;
			aa.setDate(yy,1,1);
			cout<<"月增加1,年也加一，月变1，日变1\n";
		}
		cout<<"当前日期为："<<aa<<"  add = "<<d<<endl;
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

	printf("\n             公元%04d年(%s年)\n\n",year,cl[(year+57)%60]);
	for(i = 1; i < 13; i++)
	{
		GREEN;
		cout<<"      一   二   三   四   五   六   日"<<endl;
		cout<<"      Mon. Tue. Wed. Thur.Fri. Sat. Sun."<<endl; 
		BLUE;
//		if(showMonth())
//		{
			cout<<setw(2)<<i<<"月：";
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
	printf("\n               公元%04d年%02d月\n\n",year,month);
	for(i=1; i<month; i++)
		totalDays += monthday[i];

	GREEN;
	cout<<"      一   二   三   四   五   六   日"<<endl;
	cout<<"      Mon. Tue. Wed. Thur.Fri. Sat. Sun."<<endl; 
	BLUE;
//	cout<<setw(2)<<month<<"月：";
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
	printf("\n               公元%04d年%02d月\n\n",year,month);
	for(i=1; i<month; i++)
		totalDays += monthday[i];
	int tt = totalDays;
	totalDays += (weekdays[year] + 6) % 7;

	GREEN;
	cout<<"      一     二    三    四    五    六    日 "<<endl;
	cout<<"      Mon.  Tue.  Wed.  Thur. Fri.  Sat.  Sun."<<endl; 
	BLUE;
//	cout<<setw(2)<<month<<"月：";
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
			strcpy(weekker,"日");
			break;
		case 1:
			strcpy(weekker,"一");
			break;
		case 2:
			strcpy(weekker,"二");
			break;
		case 3:
			strcpy(weekker,"三");
			break;
		case 4:
			strcpy(weekker,"四");
			break;
		case 5:
			strcpy(weekker,"五");
			break;
		case 6:
			strcpy(weekker,"六");
			break;
	}
	printf("\n      %04d年%02d月%02d日是星期%s,这天是%04d年的第%d天\n",year,month,day,weekker,year,tt);
	printline();
	cout<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initMapFestivals()
{
	Date date1(1,1);
	string FestivalName;
	FestivalName = "元旦";
	festivals[date1] = FestivalName;
	
	date1.setDate(2,14);
	FestivalName = "情人节";
	festivals[date1] = FestivalName; 
	
	date1.setDate(3,8);
	FestivalName = "妇女节";
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
    cout<<"现在是北京时间: ";
	printf("%04d年%02d月%02d日 %02d:%02d:%02d",Year,Month,Day,Hour,Minute,Second);
	if(flag) 
	{
		cout<<"\n";	
	} 
//    printf("%d\n",p->tm_sec); /*获取当前秒*/
//    printf("%d\n",p->tm_min); /*获取当前分*/
//    printf("%d\n",8+p->tm_hour);/*获取当前时,这里获取西方的时间,刚好相差八个小时*/
//    printf("%d\n",p->tm_mday);/*获取当前月份日数,范围是1-31*/
//    printf("%d\n",1+p->tm_mon);/*获取当前月份,范围是0-11,所以要加1*/
//    printf("%d\n",1900+p->tm_year);/*获取当前年份,从1900开始，所以要加1900*/
//    printf("%d\n",p->tm_yday); /*从今年1月1日算起至今的天数，范围为0-365*/	
} 


void showCalendarFunction()
{
		YELLOW;
	cout<<" _____________________________________________________________________________"<<endl;
	cout<<"|                            ";
	GREEN;
	cout<<"      万年历                                     ";
	YELLOW;
	cout<<"|"<<endl;
	cout<<"|-----------------------------------------------------------------------------|"<<endl;
	cout<<"| -  该系统的查询功能如下：                                                   |"<<endl; 
	cout<<"|       ·查询任意年份的日期信息                                              |"<<endl;
	cout<<"|       ·查询某一天是星期几，是该年的第几天                                  |"<<endl;
	cout<<"|       ·输入年份，输出该年份的日历                                          |"<<endl; 
	cout<<"|       ·输入年月，输出该年份该月的日历                                      |"<<endl;
	cout<<"|       ·输入年月日，输出该日在该年该月的位置信息                            |"<<endl;
	cout<<"|       ·查询当前日期与时间                                                  |"<<endl;                                      
	cout<<"| -  该系统的计算功能如下：                                                   |"<<endl; 
	cout<<"| 	   ·输入天数，计算当前日期该天数后的日期                             |"<<endl;
	cout<<"|	   ·计算当前日期和上次输入日期相隔的天数                             |"<<endl; 
	cout<<"|注意：输入的数字可用任意个数空格隔开，在一行内输入即可                       |"<<endl;//改颜色，
	  	//对以上所有功能都举例说明。 
	cout<<"|-----------------------------------------------------------------------------|"<<endl;
	cout<<"|_______________________________Designed_by_XZC_______________________________|"<<endl;
	cout<<endl<<endl;
	SL(1000);
	WHITE;
} 


///////////////////////////////////// ____main() ____///////////////////////////////////////////////////////////

int main()
{
	//条件编译 
	#ifdef FILE_INPUT
	//如果宏定义了 FILE_INPUT 就从文件in.txt中输入
//运行结果输出到out.txt文件中 
		freopen("in.txt","r",stdin);
		freopen("out1.txt","w",stdout);
	#endif
	//条件编译结束
	 
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
	if(a>b) cout<<"大于\n";
	if(b==c) cout<<"等于\n";
	cout<<b-a<<endl;
	Date dd1(1998,3,31),dd2(2015,1,1);
	cout<<dd1<<endl;
	dd1 = dd2;
	cout<<dd1<<endl;
	int add;
	cout<<"请输入增加的天数：";
	while(cin>>add){
		//cout<<dd1+add<<endl;
		dd1 = dd1 + add;
		cout<<dd1<<endl;
		cout<<"请继续输入增加的天数(0 to quit)：";
	}
	dd1.showDayNumber();
	cout<<endl;
	dd1.showMonthDay();
	cout<<endl;
	dd1.showDate();
	dd1++;
	dd1.showDate();
	cout<<dd1++<<endl;//有问题后置的++还先自增 */
	Date date1(2019,5,25);
	Date date2(date1);
	system("title 万年历by xzc");
	int flag = 1,i;
	int day,month,year;
	YELLOW;
	SL(1000);
	showCalendarFunction();
//	printf("万年历：\n");
//	printf("Design by 许智超。\n");
//	cout<<"1.查询某年的日历请输入年份;       2.查询具体月份请输入年和月; \n";
//	cout<<"3.查询具体日期请输入年、月、日;   4.查询两个日期间隔的天数只需重复3;\n";
//	WHITE;

	BLUE;
	printf("--------------------------------------------------------------------------------\n");
	getWeekdays();
	GREEN;
	char demo[] = "请欣赏样例\n";
	for(i=0; demo[i]!='\0'; i++)
	{
		printf("%c",demo[i]);
		SL(100);
	}
	WHITE;
	SL(500);
	printf("请输入：____\b\b\b\b");
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
		cout<<"请输入：____\b\b\b\b";
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
				cout<<"输入中有非数字的非法字符！\n";
				judge = 1;
				break;
			}
		sscanf(date,"%d %d %d",&year,&month,& day);
		if(year>100000||year==0)
		{
			RED;
			cout<<"年份不合法！\n";
			judge = 1;
		}
		if(month>12||month==0)
		{
			RED;
			cout<<"月份不合法！\n";
			judge = 1;
		}
		bool leapp = isleap(year);
		if(leapp) monthday[2] = 29;
		else monthday[2] = 28;
		if(month<13&&(day>monthday[month]||day==0))
		{
			RED;
			cout<<"日期不合法！\n";
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
				cout<<min(date1,date2)<<" 与 "<<max(date1,date2)<<" 之间相距"<<daysbetween<<"天\n\n";
				WHITE;
				int nextuse = 0,adddays;
				Date date3(2019,5,25);
				cout<<"想计算这天之后若干天的日期吗？请输入1。不想请输入0。\n_\b";
				CYAN;
				cin>>nextuse;
				if(nextuse)
				{
					while(1)
					{
						WHITE;
						if(taps%2)  cout<<"请输入要从"<<date1<<"加的天数(0 to quit)：";
						else  cout<<"请输入要从"<<date2<<"加的天数(0 to quit)：";
						CYAN;
						cin>>adddays;
						if(adddays==0) break;
						if(taps%2)
						{
							date3 = date1 + adddays;
							cout<<"从"<<date1<<"开始加"<<adddays<<"天之后的日期为"<<date3<<endl;
							date3.showDay();
						}
						if(taps%2==0)
						{
							date3 = date2 + adddays;
							cout<<"从"<<date2<<"开始加"<<adddays<<"天之后的日期为"<<date3<<endl;
							date3.showDay();
						}
					}
				}

				break;
			}
			default:
				cout<<"还没写好。\n";
		}
		WHITE;
		cout<<"退出按0，继续按1,继续并清屏请按2,显示当前时间请按3，清屏并显示当前时间请按4：_\b";
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
			printf("万年历：\n");
			printf("Design by 许智超。\n");

			cout<<"1.查询某年的日历请输入年份;       2.查询具体月份请输入年和月; \n";
			cout<<"3.查询具体日期请输入年、月、日;   4.查询两个日期间隔的天数只需重复3;\n";
			WHITE;
			cout<<"(输入的数字用任意个数空格隔开，请在一行内输入)\n";
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
	
	//条件编译 
	#ifdef FILE_INPUT
	//如果之前宏定义了 FILE_INPUT,那么就打开了文件in.txt和out.txt
	//那么在程序运行结束之前一定要关闭文件指针 
		fclose(stdin);
		fclose(stdout);
	//关闭了输入文件和输出文件 
	#endif 
	//条件编译结束 

	return 0;
}
