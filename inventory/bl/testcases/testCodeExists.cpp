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
int code;
cout<<"Enter the code: ";
cin>>code;
if(manager.unitOfMeasurementCodeExists(code)) cout<<code<<" yes exist"<<endl;
else cout<<code<<" not exist"<<endl;
return 0;
}