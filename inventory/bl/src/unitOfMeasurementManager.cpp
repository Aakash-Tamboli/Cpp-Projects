#include<common/stringutils>
#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<dl/iuom>
#include<dl/uom>
#include<dl/daoexception>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<map>
#include<forward_list>
using namespace inventory;
using namespace business_layer;
using namespace stringutils;
UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel;
bool UnitOfMeasurementTitleComparator::operator()(string *left,string *right)
{
return compareStringIgnoreCase(left->c_str(),right->c_str())<0;
}
UnitOfMeasurementManager::DataModel::DataModel()
{
populateDataStructure();
}
UnitOfMeasurementManager::DataModel::~DataModel()
{
/*
iterate any one map,and release all bl UnitOfMeasurements object clear both
maps
*/
}
void UnitOfMeasurementManager::DataModel::populateDataStructure()
{
/*
1) iterate the dlUnitOfMeasurements forward_list.
2) On Every iterattion create an object of bl UnitOfMeasurement.
3) set code and title by picking it up dl UnitOfMeasurement.
4) insert the address of bl UnitOfMeasurement in the 2 defined maps
					Note: in one map key will be whatever get code returns
					in another map key will be the address of whatever getTitle returns.
5) free the dlUnitOfMeasurements (inside the iteration loop itself.
6) after the loop free the object the forward_list object.
*/
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
dlUnitOfMeasurements=unitOfMeasurementDAO.getAll();
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
_UnitOfMeasurement *blUnitOfMeasurement;
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
int code;
string *title;
for(i=dlUnitOfMeasurements->begin();i!=dlUnitOfMeasurements->end();++i)
{
dlUnitOfMeasurement=*i;
code=dlUnitOfMeasurement->getCode();
title=new string(dlUnitOfMeasurement->getTitle());
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=title;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code,blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(title,blUnitOfMeasurement));
delete dlUnitOfMeasurement;
}
dlUnitOfMeasurements->clear();
delete dlUnitOfMeasurements;
}catch(inventory::data_layer::DAOException &daoException)
{
// no need to anything
}
}
UnitOfMeasurementManager::UnitOfMeasurementManager()
{
}
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
BLException blException;
if(unitOfMeasurement==NULL)
{
blException.setGenericException("Unit of measurement required, NULL Encountered");
throw blException;
}
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code!=0)
{
blException.addPropertyException("code","Code should be zero");
}
if(title.length()==0)
{
blException.addPropertyException("title","Title required");
}
if(title.length()>50)
{
blException.addPropertyException("title","length of title should not be more than 50 character");
}
if(blException.hasExceptions())
{
throw blException;
}
map<string *,_UnitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Given tile exists");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
dlUnitOfMeasurement=new inventory::data_layer::UnitOfMeasurement;
dlUnitOfMeasurement->setCode(0);
dlUnitOfMeasurement->setTitle(title);
unitOfMeasurementDAO.add(dlUnitOfMeasurement);
unitOfMeasurement->setCode(dlUnitOfMeasurement->getCode());
delete dlUnitOfMeasurement;
string *t=new string(title);
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=t;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code,blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(t,blUnitOfMeasurement));
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) throw(BLException)
{
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) throw(BLException)
{
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) throw(BLException)
{
BLException blException;
abc::IUnitOfMeasurement *blUnitOfMeasurement;
_UnitOfMeasurement *unitOfMeasurement;
blUnitOfMeasurement=new UnitOfMeasurement;
map<int,_UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.setGenericException(string("code not exists"));
blException.addPropertyException("code","Not Exists");
throw blException;
}
unitOfMeasurement=i->second;
blUnitOfMeasurement->setCode(unitOfMeasurement->code);
blUnitOfMeasurement->setTitle(*(unitOfMeasurement->title));
return blUnitOfMeasurement;
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) throw(BLException)
{
BLException blException;
abc::IUnitOfMeasurement *blUnitOfMeasurement;
_UnitOfMeasurement *unitOfMeasurement;
blUnitOfMeasurement=new UnitOfMeasurement;
map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i==dataModel.titleWiseMap.end())
{
blException.setGenericException(string("First add this: ")+string(title));
blException.addPropertyException("title","Not Exists");
throw blException;
}
unitOfMeasurement=i->second;
blUnitOfMeasurement->setCode(unitOfMeasurement->code);
blUnitOfMeasurement->setTitle(*(unitOfMeasurement->title));
return blUnitOfMeasurement;
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementManager::getUnitOfMeasurements() throw(BLException)
{
/*
Iterate on map (2 of any)
Create a forward_list of unitOfMeasurement *
*/
map<string *,_UnitOfMeasurement *>::iterator i=dataModel.titleWiseMap.begin();
_UnitOfMeasurement *unitOfMeasurement;
abc::IUnitOfMeasurement *blUnitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
unitOfMeasurements=new forward_list<abc::IUnitOfMeasurement *>;
forward_list<abc::IUnitOfMeasurement *>::iterator listi=unitOfMeasurements->before_begin();
while(i!=dataModel.titleWiseMap.end())
{
unitOfMeasurement=i->second;
blUnitOfMeasurement=new UnitOfMeasurement;
blUnitOfMeasurement->setCode(unitOfMeasurement->code);
blUnitOfMeasurement->setTitle(*(unitOfMeasurement->title));
listi=unitOfMeasurements->insert_after(listi,blUnitOfMeasurement);
++i;
}
return unitOfMeasurements;
}
int UnitOfMeasurementManager::unitOfMeasurementCodeExists(int code) throw(BLException)
{
map<int,_UnitOfMeasurement *>::iterator i=dataModel.codeWiseMap.begin();
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end()) return 0;
else return 1;
}
int UnitOfMeasurementManager::unitOfMeasurementTitleExists(string &title) throw(BLException)
{
map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparator>::iterator i=dataModel.titleWiseMap.begin();
i=dataModel.titleWiseMap.find(&title);
if(i==dataModel.titleWiseMap.end()) return 0;
else return 1;
}
int UnitOfMeasurementManager::getUnitOfMeasurementCount() throw(BLException)
{
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
return unitOfMeasurementDAO.getCount();
}