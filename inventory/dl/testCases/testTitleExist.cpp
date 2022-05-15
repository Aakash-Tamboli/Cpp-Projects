#include<uom>
#include<uomdao>
#include<daoexception>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
string title;
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"Enter title: ";
getline(cin,title);
if(!unitOfMeasurementDAO.titleExist(title))
{
cout<<title<<" not exist"<<endl;
}
else
{
cout<<title<<" already exist"<<endl;
}
return 0;
}