#include<iostream>
#include<time.h>
#include<string.h>
using namespace std;
class TMDate
{
private:
int dayOfMonth;
int month;
int year;
int dayNumber; // how many days from today to 1901;
int isLeapYear(int); // internal use Method
void toDayNumber(); // internal use Method
void fromDayNumber();
void isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y);
public:
TMDate();
TMDate(const char *);
int getDayOfMonth();
int getMonth();
int getYear();
/*
int getDayNumber() // remove after testing
{
return this->dayNumber;
}
*/
void operator+=(int);
void operator-=(int);
};
int TMDate::isLeapYear(int y)
{
if(y%400==0) return 1;
else if(y%100==0) return 0;
else if(y%4==0) return 1;
else return 0;
}
void TMDate::toDayNumber()
{
int x=0;
int y=1900;
int m;
while(y<this->year)
{
if(isLeapYear(y)) x=x+366;
else x=x+365;
y++;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(this->year)) mth[1]=29;
int ep=this->month-2;
m=0;
while(m<=ep)
{
x=x+mth[m];
m++;
}
x=x+this->dayOfMonth;
this->dayNumber=x;
}
void TMDate::fromDayNumber()
{
if(this->dayNumber==0)
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
return;
}
int x=this->dayNumber;
int d,m,y;
int daysInYear;
int daysInMonth;
y=1900;
while(1)
{
if(isLeapYear(y)) daysInYear=366; 
else daysInYear= 365;
if(x<daysInYear) break;
x=x-daysInYear;
y=y+1;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(y)) mth[1]=29;
m=0;
while(1)
{
daysInMonth=mth[m];
if(x<daysInMonth) break;
x=x-daysInMonth;
m++;
}
m++;
d=x;
this->dayOfMonth=d;
this->month=m;
this->year=y;
}
void TMDate::isValidDate(const char *dateString,int *isValid,int *d,int *m,int *y)
{
int dd,mm,yy;
int sepIndex1,sepIndex2,i,r;
char mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
char sep;
*isValid=0;
if(dateString==NULL) return;
int x=strlen(dateString);
if(x<8 || x>10) return;
if(!(dateString[1]=='/' || dateString[2]=='/' || dateString[1]=='-' || dateString[2]=='-')) return;
if(dateString[1]=='/' || dateString[1]=='-') sepIndex1=1;
else sepIndex1=2;
sep=dateString[sepIndex1];
if(dateString[0]<48 || dateString[0]>57) return;
if(sepIndex1==2 && (dateString[1]<48 || dateString[1]>57)) return;
if(sepIndex1==1)
{
dd=dateString[0]-48;
if(dd==0) return;
}
else
{
dd=((dateString[0]-48)*10)+(dateString[1]-48);
if(dd==0) return;
}
i=sepIndex1+1;
if(!(dateString[i+1]==sep || dateString[i+2]==sep)) return;
if(dateString[i+1]==sep) sepIndex2=i+1;
else sepIndex2=i+2;
if(dateString[i]<48 || dateString[i]>57) return;
if(sepIndex2==2 && (dateString[i+1]<48 || dateString[i+1]>57)) return;
if(sepIndex2==1)
{
mm=dateString[i]-48;
}
else
{
mm=((dateString[i]-48)*10)+(dateString[i+1]-48);
}
if(mm<1 || mm>12) return;
i=sepIndex2+1;
yy=0;
r=0;
while(r<=3)
{
if(dateString[i+r] < 48|| dateString[i+r] >57) return;
yy=(yy*10)+(dateString[i+r]-48);
r++;
}
if(yy<1900) return;
if(yy%400==0) mth[1]=29;
else if(yy%100==0) mth[1]=28;
else if(yy%4==0) mth[1]=29;
else mth[1]=28;
if(dd < 1 || dd > mth[mm-1]) return;
*d=dd;
*m=mm;
*y=yy;
*isValid=1;
}
TMDate::TMDate()
{
time_t x;
time(&x);
struct tm *now;
now=localtime(&x);
this->dayOfMonth=now->tm_mday;
this->month=now->tm_mon+1;
this->year=now->tm_year+1900;
this->toDayNumber(); // set Day Number;
}
TMDate::TMDate(const char *dateString)
{
int d,m,y,isValid;
this->isValidDate(dateString,&isValid,&d,&m,&y);
if(isValid)
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
else
{
this->dayNumber=0;
this->dayOfMonth=1;
this->month=1;
this->year=1900;
}
}
int TMDate::getDayOfMonth()
{
return this->dayOfMonth;
}
int TMDate::getMonth()
{
return this->month;
}
int TMDate::getYear()
{
return this->year;
}
void TMDate::operator+=(int days)
{
if(this->dayNumber==0) return;
this->dayNumber+=days;
this->fromDayNumber();
}
void TMDate::operator-=(int days)
{
if(this->dayNumber==0) return;
this->dayNumber-=days;
this->fromDayNumber();
}
ostream& operator<<(ostream &mout,TMDate &tmdate)
{
mout<<tmdate.getDayOfMonth()<<"/"<<tmdate.getMonth()<<"/"<<tmdate.getYear();
return mout;
}
int main()
{
TMDate d2="10/12/2020";
cout<<d2<<endl;
d2+=20;
cout<<d2<<endl;
d2+=2;
cout<<d2<<endl;
return 0;
}