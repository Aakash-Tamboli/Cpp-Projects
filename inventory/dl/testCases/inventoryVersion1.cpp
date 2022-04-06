#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurement data(0,"KG");
UnitOfMeasurementDAO m;
try
{
m.add(&data);
}
catch(DAOException &err)
{
cout<<err.what()<<endl;
}
return 0;
}