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
UnitOfMeasurementManager manager;
string title;
int code;
cout<<"Enter the code of Unit Of Measurement you want to update: ";
cin>>code;
cout<<"Enter the title of Unit Of Measurement you want to update: ";
cin>>title;
uom.setCode(code);
uom.setTitle(title);
try
{
manager.updateUnitOfMeasurement(&uom);
cout<<title<<" is updated in data file"<<endl;
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