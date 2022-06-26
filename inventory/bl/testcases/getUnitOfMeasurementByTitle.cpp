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
string title;
cout<<"Enter Unit Of Measurement: ";
cin>>title;
UnitOfMeasurementManager manager;
try
{
unitOfMeasurement=manager.getUnitOfMeasurementByTitle(title);
cout<<"Code: "<<unitOfMeasurement->getCode()<<endl;
cout<<"Tile: "<<unitOfMeasurement->getTitle()<<endl;
}
catch(BLException blException)
{
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<blException.getPropertyException("title")<<endl;
}
}// catch block ends
return 0;
}