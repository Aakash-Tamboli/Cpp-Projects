#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
#include<ios>
#include<limits>
using namespace std;
inventory::business_layer::UnitOfMeasurementManager manager;
void addUnitOfMeasurements()
{
string title;
inventory::business_layer::UnitOfMeasurement uom;
cout<<"Enter Unit Of Measurement: ";
cin>>title;
cin.ignore(numeric_limits<streamsize>::max(),'\n');
uom.setTitle(title);
uom.setCode(0);
manager.addUnitOfMeasurement(&uom);
}
void showUnitOfMeasurements()
{
}
void updateUnitOfMeasurements()
{
}
void removeUnitOfMeasurements()
{
}
int main()
{
int ch;
while(1)
{
cout<<"1 for add Unit of Measurement"<<endl;
cout<<"2 for show Measurements"<<endl;
cout<<"3 for update Unit of Measurements"<<endl;
cout<<"4 for delete Unit of Measurement"<<endl;
cout<<"5 for exit"<<endl;
cin>>ch;
cin.ignore(numeric_limits<streamsize>::max(),'\n');
if(ch==5) return 0;
if(ch<0 && ch>5) continue;
try
{
if(ch==1) addUnitOfMeasurements();
}catch(inventory::business_layer::BLException &blException)
{
if(blException.hasExceptions())
{
cout<<blException.getPropertyException("title")<<endl;
}
}
if(ch==2) showUnitOfMeasurements();
else if(ch==3) updateUnitOfMeasurements();
else if(ch==4) removeUnitOfMeasurements();

}
return 0;
}