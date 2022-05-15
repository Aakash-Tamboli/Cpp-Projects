#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
#include<limits>
#include<ios>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
string title;
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"Enter string: ";
getline(cin,title);
try
{
abc::IUnitOfMeasurement *unitOfMeasurement;
unitOfMeasurement=unitOfMeasurementDAO.getByTitle(title);
cout<<"Code: "<<unitOfMeasurement->getCode()<<", Title: "<<unitOfMeasurement->getTitle()<<endl;
}
catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}