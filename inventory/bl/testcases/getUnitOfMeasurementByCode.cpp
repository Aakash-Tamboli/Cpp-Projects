#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
abc::IUnitOfMeasurement *unitOfMeasurement;
int code;
cout<<"Enter the code of your unit of measurement ";
cin>>code;
UnitOfMeasurementManager manager;
try
{
unitOfMeasurement=manager.getUnitOfMeasurementByCode(code);
cout<<"Code: "<<unitOfMeasurement->getCode()<<endl;
cout<<"Tile: "<<unitOfMeasurement->getTitle()<<endl;
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