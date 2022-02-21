#include<iostream>
#include<stdio.h>
using namespace std;
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
virtual void insertAt(int index,int data,bool *success)=0;
virtual int removeAt(int index,int *success)=0;
virtual int get(int index,int *success) const=0;
virtual void update(int index,int data,int *success)=0;
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
char allocationFlag;
bool addRow();
public:
TMArrayList();
TMArrayList(int buffer);
TMArrayList(const TMArrayList &other);
virtual ~TMArrayList();
void add(int data,bool *success);
void insertAt(int index,int data,bool *success);
int removeAt(int index,int *success);
int get(int index,int *success) const;
void update(int index,int data,int *success);
void removeAll();
void clear();
int getSize();
TMArrayList& operator=(const TMArrayList &other);
void operator+=(const TMArrayList &other);
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
this->allocationFlag=0;
}
TMArrayList::TMArrayList(int bufferSize)
{
this->allocationFlag=0;
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
int bufferSize=other.size;
this->allocationFlag=0;
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
numberOfPointers=rows+(10-(rows%10));
this->ptr=new int*[numberOfPointers];
for(int e=0;e<rows;e++)
{
this->ptr[e]=new int[10];
}
this->capacity=rows*10;
this->size=0;
}
bool succ;
for(int e=0; e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
TMArrayList:: ~TMArrayList()
{
// This is Why Because We know that what we Implelemented in operator+
if(this->allocationFlag==0)
{
int rows=this->capacity/10;
int j;
for(j=0; j<rows;j++)
{
delete [] this->ptr[j];
}
delete[] this->ptr;
}
}
void TMArrayList::add(int data,bool *success)
{
if(success) *success=false;
if(this->size==this->capacity)
{
if(!addRow()) return;
}
int rowIndex,columnIndex;
rowIndex=this->size/10;
columnIndex=this->size%10;
this->ptr[rowIndex][columnIndex]=data;
this->size++;
if(success) *success=true;
}
void TMArrayList::insertAt(int index,int data,bool *success)
{
if(success) *success=false;
if(index<0 || index>this->size) return;
if(index==this->size)
{
this->add(data,success);
return;
}
bool succ;
int k=this->get(this->size-1,&succ);
this->add(k,&succ);
if(succ==false) return;
int j;
while(j>=index)
{
this->update(j+1,this->get(j,&succ),&succ);
j--;
}
this->update(index,data,&succ);
if(success) *success=true;
}
int TMArrayList::removeAt(int index,int *success)
{
if(success) *success=false;
if(index<0 || index>=this->size) return 0;
bool succ;
int data=this->get(index,&succ);
int j;
int ep=this->size-2;
j=index;
while(j<=ep)
{
this->update(j,this->get(j+1,&succ),&succ);
j++;
}
this->size--;
if(success) *success=true;
return data;
}
int TMArrayList::get(int index,int *success) const
{
if(success) *success=false;
if(index<0 || index>=this->size) return 0;
int rowIndex=index/10;
int columnIndex=index%10;
if(success) *success=true;
return ptr[rowIndex][columnIndex];
}
void TMArrayList::update(int index,int data,int *success)
{
if(success) *success=false;
if(index<0 || index>=size) return;
int rowIndex=index/10;
int columnIndex=index%10;
this->ptr[rowIndex][columnIndex]=data;
if(success) *success=true;
}
void TMArrayList::removeAll()
{
this->size=0;
}
void TMArrayList::clear()
{
this->size=0;
}
int TMArrayList::getSize()
{
return this->size;
}
TMArrayList& TMArrayList::operator=(const TMArrayList &other)
{
if(other.allocationFlag==0)
{
//this is normal case;
this->size=0;
int succ;
for(int e=0; e<other.size; e++)
{
this->add(other.get(e,&succ),&succ);
}
}
else
{
int rows=this->capacity/10;
int j;
for(j=0; j<rows; j++)
{
delete [] this->ptr[j];
}
delete [] this->ptr;
this->ptr=other.ptr;
this->capacity=other.capacity;
this->size=other.size;
}
return *this;
}
void TMArrayList::operator+=(const TMArrayList &other)
{
int succ;
for(int e=0; e<other.size; e++)
{
this->add(other.get(e,&succ),&succ);
}
}
int main()
{
TMArrayList list1(6000);
bool k;
for(int x=100;x<=123;x++) list1.add(x,&k);
cout<<"Size of list 1 is "<<list1.getSize()<<endl;
TMArrayList list2(list1);
cout<<"This is Content of List 2"<<endl;
for(int x=0;x<list2.getSize();x++)
{
cout<<list2.get(x,&k)<<" ";
}
cout<<endl;
return 0;
}