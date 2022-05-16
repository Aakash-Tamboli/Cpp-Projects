#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
string title;
UnitOfMeasurementDAO m;
cout<<"Enter Unit: ";
getline(cin,title);
UnitOfMeasurement data(0,title);
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