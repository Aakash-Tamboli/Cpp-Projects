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
