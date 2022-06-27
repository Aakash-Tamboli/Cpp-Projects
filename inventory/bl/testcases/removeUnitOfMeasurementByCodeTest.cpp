#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
int code;
cout<<"Enter the code of Unit Of Measurement you want to delete: ";
cin>>code;
UnitOfMeasurementManager manager;
try
{
manager.removeUnitOfMeasurementByCode(code);
cout<<code<<" with unit of measurement is deleted"<<endl;
}
catch(BLException blException)
{
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}
}// catch block ends
return 0;
}