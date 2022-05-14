#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurement data(0,"ABCDEFGHIJKLMNOPQRSTUWZXYABCDEFGHIJKLMNOPQRSTUWZXYABCDEFGHIJKLMNOPQRSTUWZXYABCDEFGHIJKLMNOPQRSTUWZXYABCDEFGHIJKLMNOPQRSTUWZXY");
UnitOfMeasurementDAO m;
try
{
m.add(&data);
cout<<"Unit of Measurement added with code as: "<<data.getCode()<<endl;
}
catch(DAOException &err)
{
cout<<err.what()<<endl;
}
return 0;
}