#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"Enter Code: ";
cin>>code;
try
{
abc::IUnitOfMeasurement *unitOfMeasurement;
unitOfMeasurement=unitOfMeasurementDAO.getByCode(code);
cout<<"Code: "<<unitOfMeasurement->getCode()<<", Title: "<<unitOfMeasurement->getTitle()<<endl;
}
catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}