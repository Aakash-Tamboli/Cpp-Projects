#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"Number of Record in context to unit of measurement: "<<unitOfMeasurementDAO.getCount()<<endl;
return 0;
}