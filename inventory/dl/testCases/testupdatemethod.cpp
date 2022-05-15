#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurement data(1,"Killograms");
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"data is going to update"<<endl;
try
{
unitOfMeasurementDAO.update(&data);
cout<<"data is updated"<<endl;
}
catch(DAOException &err)
{
cout<<err.what()<<endl;
}
return 0;
}