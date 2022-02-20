#include<iostream>
#define bool int
#define TRUE 1
#define True 1
#define true 1
#define FALSE 0
#define False 0
#define false 0
using namespace std;
class TMList
{
public:
virtual void add(int data,bool *success)=0;
virtual void insert(int index,int data,bool *success)=0;
virtual int removeAt(int index,int *success)=0;
virtual int get(int index,int *success)=0;
virtual void update(int index,int *success)=0;
virtual void removeAll()=0;
virtual void clear()=0;
virtual int getSize()=0;
};
class TMArrayList:public TMList
{
private:
int **ptr;
int capacity;
int size;
bool addRow();
public:
TMArrayList();
TMArrayList(int buffer);
TMArrayList(const TMArrayList &other);
void add(int data,bool *success);
void insert(int index,int data,bool *success);
int removeAt(int index,int *success);
int get(int index,int *success);
void update(int index,int *success);
void removeAll();
void clear();
int getSize();
};
bool TMArrayList::addRow()
{


return 0; //Just Compiling
}
TMArrayList::TMArrayList()
{

}
TMArrayList::TMArrayList(int buffer)
{
}
TMArrayList::TMArrayList(const TMArrayList &other)
{

}
void TMArrayList::add(int data,bool *success)
{

}
void TMArrayList::insert(int index,int data,bool *success)
{
}
int TMArrayList::removeAt(int index,int *success)
{
return 0;
}
int TMArrayList::get(int index,int *success)
{
return 0;
}
void TMArrayList::update(int index,int *success)
{
}
void TMArrayList::removeAll()
{
}
void TMArrayList::clear()
{
}
int TMArrayList::getSize()
{
return 0;
}
