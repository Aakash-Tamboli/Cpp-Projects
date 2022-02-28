#include<iostream>
#include<time.h>
using namespace std;
class TMDate
{
private:
int dayOfMonth;
int month;
int year;
public:
TMDate();
int getDayOfMonth();
int getMonth();
int getYear();
};
TMDate::TMDate()
{
time_t x;
time(&x);
struct tm *now;
now=localtime(&x);
this->dayOfMonth=now->tm_mday;
this->month=now->tm_mon+1;
this->year=now->tm_year+1900;
}
int TMDate::getDayOfMonth()
{
return  this->dayOfMonth;
}
int TMDate::getMonth()
{
return this->month;
}
int TMDate::getYear()
{
return this->year;
}
ostream & operator<<(ostream &mout,TMDate &tmdate)
{
mout<<tmdate.getDayOfMonth()<<"/"<<tmdate.getMonth()<<"/"<<tmdate.getYear()<<endl;
return mout;
}
int main()
{
TMDate date;
cout<<date;
return 0;
}