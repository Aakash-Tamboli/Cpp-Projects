#include<iostream>
#include<bl/iuommanager>
#include<bl/uommanager>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
abc::IUnitOfMeasurementManager *manager;
manager=new UnitOfMeasurementManager;
cout<<"Unit of measurements are: "<<manager->getUnitOfMeasurementCount()<<endl;
delete manager;
return 0;
}