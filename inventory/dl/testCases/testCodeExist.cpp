#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"Enter Code: ";
cin>>code;
if(!unitOfMeasurementDAO.codeExist(code))
{
cout<<code<<", does not exist"<<endl;
}
else
{
cout<<code<<" exist"<<endl;
}
return 0;
}