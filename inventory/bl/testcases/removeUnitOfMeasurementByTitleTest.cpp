#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
string title;
cout<<"Enter Unit Of Measurement you want to delete: ";
cin>>title;
UnitOfMeasurementManager manager;
try
{
manager.removeUnitOfMeasurementByTitle(title);
cout<<title<<" is deleted"<<endl;
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