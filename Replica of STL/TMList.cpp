#include<iostream>
#define TRUE 1;
#define True 1;
#define true 1;
#define FALSE 0;
#define False 0;
#define false 0;
using namespace std;
class TMList
{
public:
virtual void add(int data,bool *success)=0;
virtual void insert(int index,int data,bool *success)=0;
virtual int removeAt(int index,int *success)=0;
virtual void update(int index,int *success)=0;
virtual void removeAll()=0;
virtual void clear()=0;
virtual int getSize()=0;
};
class TMForwardList:public TMList
{
private:

// More Variables

public:
TMForwardList();
TMForwardList(int bufferSize);
TMForwardList(TMForwardList &other);
TMForwardList & operator=(TMForwardList &other);
virtual ~TMForwardList();
TMForwardList & operator+=(TMForwardList &other);
TMForwardList & operator+(TMForwardList &other);
int operator[](int index);

void add(int data,bool *success);
void insert(int index,int data,bool *success);
int removeAt(int index,int *success);
void update(int index,int *success);
void removeAll();
void clear();
int getSize();
};
TMForwardList::TMForwardList()
{

}

TMForwardList::TMForwardList(int bufferSize)
{

}
TMForwardList::TMForwardList(TMForwardList &other)
{


}
TMForwardList & TMForwardList::operator=(TMForwardList &other)
{

}
TMForwardList::~TMForwardList()
{

}
TMForwardList & TMForwardList::operator+=(TMForwardList &other)
{

}
TMForwardList & TMForwardList::operator+(TMForwardList &other)
{

}
int TMForwardList::operator[](int index)
{

}
void TMForwardList::add(int data,bool *success)
{

}
void TMForwardList::insert(int index,int data,bool *success)
{

}
int TMForwardList::removeAt(int index,int *success)
{

}
void TMForwardList::update(int index,int *success)
{

}
void TMForwardList::removeAll()
{

}
void TMForwardList::clear()
{

}
int TMForwardList::getSize()
{

}
int main()
{

return 0;
}