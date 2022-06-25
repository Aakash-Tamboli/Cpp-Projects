#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/uommanager>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
abc::IUnitOfMeasurement *uom;
UnitOfMeasurementManager manager;
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements=manager.getUnitOfMeasurements();
forward_list<abc::IUnitOfMeasurement *>::iterator i;
for(i=unitOfMeasurements->begin();i!=unitOfMeasurements->end();++i)
{
uom=*i;
cout<<uom->getCode()<<" , "<<uom->getTitle()<<endl;
}
return 0;
}