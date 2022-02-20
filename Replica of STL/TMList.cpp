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
if(capacity%100==0)
{
int numberOfPointers;
numberOfPointers=this->capacity;
int **tmp=new int*[numberOfPointers+10];
if(tmp==NULL) return false;
for(int e=0; e<numberOfPointers;e++) tmp[e]=this->ptr[e];
delete [] this->ptr;
this->ptr=tmp;
}
int i=this->capacity/10;
this->ptr[i]=new int[10];
if(this->ptr[i]==NULL) return false;
this->capacity=this->capacity+10;
return true;
}
TMArrayList::TMArrayList()
{
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
}
TMArrayList::TMArrayList(int bufferSize)
{
if(bufferSize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
}
else
{
int rows;
int numberOfPointers;
rows=bufferSize/10;
if(bufferSize%10!=0) rows++;
numberOfPointers= rows+(10-(rows%10));
this->ptr=new int *[numberOfPointers];
for(int e=0; e<rows;e++) this->ptr[e]=new int[10];
this->capacity=rows*10;
this->size=0;
}
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
