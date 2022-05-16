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
int code;
UnitOfMeasurementDAO m;
cout<<"Enter Code: ";
cin>>code;
cin.ignore(numeric_limits<streamsize>::max(),'\n');
try
{
m.remove(code);
cout<<"Record is Removed successfully"<<endl;
}
catch(DAOException &err)
{
cout<<err.what()<<endl;
}
return 0;
}