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
virtual int getSize()const=0;
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
TMArrayList(const TMList &other);
virtual ~TMArrayList();
void add(int data,bool *success);
void insertAt(int index,int data,bool *success);
int removeAt(int index,int *success);
int get(int index,int *success) const;
void update(int index,int data,int *success);
void removeAll();
void clear();
int getSize()const;
TMArrayList& operator=(const TMArrayList &other);
TMArrayList& operator=(const TMList &other);
TMArrayList operator+(const TMArrayList &other);
TMArrayList operator+(const TMList &other);
void operator+=(const TMArrayList &other); 
void operator+=(const TMList &other); // Note Done
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
TMArrayList::TMArrayList(const TMList &other)
{
this->ptr=new int *[10];
this->ptr[0]=new int[10];
this->capacity=10;
this->size=0;
this->allocationFlag=0;
int e;
int succ;
for(e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
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
int TMArrayList::getSize() const
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
TMArrayList& TMArrayList::operator=(const TMList &other)
{
this->size=0;
int succ;
for(int e=0; e<other.getSize(); e++) this->add(other.get(e,&succ),&succ);
return *this;
}
TMArrayList TMArrayList::operator+(const TMArrayList &other)
{
TMArrayList k;
int succ;
for(int e=0; e<this->size; e++) k.add(this->get(e,&succ),&succ);
for(int e=0; e<other.size; e++) k.add(other.get(e,&succ),&succ);
k.allocationFlag=1;
return k;
}
TMArrayList TMArrayList::operator+(const TMList &other)
{
TMArrayList k;
int succ;
for(int e=0; e<this->size; e++) k.add(this->get(e,&succ),&succ);
for(int e=0; e<other.getSize(); e++) k.add(other.get(e,&succ),&succ);
return k;
}

void TMArrayList::operator+=(const TMArrayList &other)
{
int succ;
for(int e=0; e<other.size; e++)
{
this->add(other.get(e,&succ),&succ);
}
}
void TMArrayList::operator+=(const TMList &other)
{
int succ;
for(int e=0; e<other.getSize(); e++) this->add(other.get(e,&succ),&succ);
}
// TMForwardList starts here
class TMForwardList:public TMList
{
class TMNode
{
public:
int data;
TMNode *next;
TMNode()
{
this->next=NULL;
}
};
private:
char allocationFlag;
TMNode *start,*end;
int size;
public:
TMForwardList();
TMForwardList(int buffer);
TMForwardList(const TMForwardList &other);
TMForwardList(const TMList &other);
virtual ~TMForwardList();
void add(int data,bool *success);
void insertAt(int index,int data,bool *success);
int removeAt(int index,int *success);
int get(int index,int *success) const;
void update(int index,int data,int *success);
void removeAll();
void clear();
int getSize()const;
TMForwardList& operator=(const TMForwardList &other);
TMForwardList& operator=(const TMList &other);
TMForwardList operator+(const TMForwardList &other);
TMForwardList operator+(const TMList &other);
void operator+=(const TMForwardList &other);
void operator+=(const TMList &other);
};
TMForwardList::TMForwardList()
{
this->allocationFlag=0;
this->start=NULL;
this->end=NULL;
this->size=0;
}
TMForwardList::TMForwardList(int bufferSize)
{
this->allocationFlag=0;
this->start=NULL;
this->end=NULL;
this->size=0;
}
TMForwardList::TMForwardList(const TMForwardList &other)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0; e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
TMForwardList::TMForwardList(const TMList &other)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->allocationFlag=0;
int succ;
for(int e=0; e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
TMForwardList:: ~TMForwardList()
{
}
void TMForwardList::add(int data,bool *success)
{
if(success) *success=false;
TMNode *t;
t= new TMNode;
if(t==NULL) return;
t->data=data;
if(this->start==NULL)
{
this->start=t;
this->end=t;
}
else
{
this->end->next=t;
this->end=t;
}
this->size++;
if(success) *success=true;
}
void TMForwardList::insertAt(int index,int data,bool *success)
{
if(success) *success=false;
if(index<0 || index > this->size) return;
if(index==this->size)
{
this->add(data,success);
return;
}
TMNode *node;
node=new TMNode;
if(node==NULL) return;
node->data=data;
int x;
TMNode *p1,*p2;
p1=this->start;
for(x=0; x<index; x++)
{
p2=p1;
p1=p1->next;
}
if(p1==this->start)
{
node->next=this->start;
this->start=node;
}
else
{
node->next=p1;
p2->next=node;
}
this->size++;
if(success) *success=true;
}
int TMForwardList::removeAt(int index,int *success)
{
int data=0;
if(success) *success=false;
if(index<0 || index>=this->size) return data;
TMNode *p1,*p2;
int x=0;
p1=this->start;
while(x<index)
{
p2=p1;
p1=p1->next;
x++;
}
data=p1->data;
if(p1==this->start && p1==this->end) // only One Node Present
{
this->start=NULL;
this->end=NULL;
}
else if(p1==this->start) // many node present but delete first
{
this->start=this->start->next;
}
else if(p1==this->end) // many node present but delete last
{
p2->next=NULL;
this->end=p2;
}
else // Many but not First nor Last
{
p2->next=p1->next;
}
this->size--;
delete p1;
if(success) *success=true;
return data;
}
int TMForwardList::get(int index,int *success) const
{
if(success) *success=false;
if(index<0 || index >= this->size) return 0;
TMNode *t;
int x;
for(x=0,t=this->start; x<index; x++,t=t->next);
if(success) *success=true;
return t->data;
}
void TMForwardList::update(int index,int data,int *success)
{
if(success) *success=false;
if(index<0 || index>=this->size) return;
TMNode *t;
int x;
for(t=this->start,x=0;x<index;x++,t=t->next);
t->data=data;
if(success) *success=true;
}
void TMForwardList::removeAll()
{
this->clear();
}
void TMForwardList::clear()
{
TMNode *t;
while(this->start!=NULL)
{
t=this->start;
this->start=this->start->next;
delete t;
}
this->end=NULL;
this->size=0;
}
int TMForwardList::getSize()const
{
return this->size;
}
TMForwardList& TMForwardList::operator=(const TMForwardList &other)
{
this->clear();
if(other.allocationFlag==1)
{
this->size=other.size;
this->start=other.start;
this->end=other.end;
}
else
{
int succ;
for(int e=0; e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
return *this;
}
TMForwardList& TMForwardList::operator=(const TMList &other)
{
int succ;
this->clear();
for(int e=0; e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
return *this;
}
TMForwardList TMForwardList::operator+(const TMForwardList &other)
{
TMForwardList k;
k+=(*this);
k+=other;
return k;
}
TMForwardList TMForwardList::operator+(const TMList &other)
{
TMForwardList k;
k+=(*this);
k+=other;
return k;
}
void TMForwardList::operator+=(const TMForwardList &other)
{
int k;
for(int e=0; e<other.getSize();e++) this->add(other.get(e,&k),&k);
}
void TMForwardList::operator+=(const TMList &other)
{
int k;
for(int e=0; e<other.getSize();e++) this->add(other.get(e,&k),&k);
}
// TMForwardList end here

int main()
{
bool succ;
TMArrayList arr;
for(int e=1;e<=20;e++) arr.add(e,&succ);
cout<<"content of TMArray Obj"<<endl;
for(int i=0;i<arr.getSize();i++) cout<<arr.get(i,&succ)<<" ";
cout<<endl;
TMForwardList sll;
sll=sll+arr;
cout<<"Content of TMFowardList obj Using + operator"<<endl;
for(int i=0;i<sll.getSize();i++) cout<<sll.get(i,&succ)<<" | ";
cout<<endl;
return 0;
}