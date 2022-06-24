#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurement uom;
uom.setCode(0);
string title("");
uom.setTitle(title);
UnitOfMeasurementManager manager;
try
{
manager.addUnitOfMeasurement(&uom);
cout<<"Unit of measurement"<<endl;
}
catch(BLException blException)
{
cout<<"Some Problem"<<endl;
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<blException.getPropertyException("title")<<endl;
}
}// catch block ends
return 0;
}