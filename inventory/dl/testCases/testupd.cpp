#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
#include<forward_list>
#include<limits>
#include<ios>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
string title;
cout<<"Enter code: ";
cin>>code;
cin.ignore(numeric_limits<streamsize>::max(),'\n');
cout<<"Enter unit: ";
getline(cin,title);
UnitOfMeasurement data(code,title);
UnitOfMeasurementDAO unitOfMeasurementDAO;
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