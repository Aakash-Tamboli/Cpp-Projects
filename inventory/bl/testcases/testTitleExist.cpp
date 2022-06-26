#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurementManager manager;
string title;
cout<<"Enter the title: ";
cin>>title;
if(manager.unitOfMeasurementTitleExists(title)) cout<<title<<" yes exist"<<endl;
else cout<<title<<" not exist"<<endl;
return 0;
}