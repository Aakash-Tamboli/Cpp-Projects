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
UnitOfMeasurementDAO unitOfMeasurementDAO;
forward_list<abc::IUnitOfMeasurement *> *list;
try
{
list=unitOfMeasurementDAO.getAll();
abc::IUnitOfMeasurement *unitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
for(i=list->begin();i!=list->end();++i)
{
unitOfMeasurement=*i;
cout<<"Code: "<<unitOfMeasurement->getCode()<<", Title: "<<unitOfMeasurement->getTitle()<<endl;
}
}
catch(DAOException &err)
{
cout<<err.what()<<endl;
}
return 0;
}