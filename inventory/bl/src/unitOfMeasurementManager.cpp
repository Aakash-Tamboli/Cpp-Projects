#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<common/stringutils>
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
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
dlUnitOfMeasurements=unitOfMeasurementDAO.getAll();
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
}
UnitOfMeasurementManager::UnitOfMeasurementManager()
{
}
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
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
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) throw(BLException)
{
}
forward_list<abc::IUnitOfMeasurement *> UnitOfMeasurementManager::getUnitOfMeasurements() throw(BLException)
{
}
int UnitOfMeasurementManager::unitOfMeasurementCodeExists(int code) throw(BLException)
{
}
int UnitOfMeasurementManager::unitOfMeasurementTitleExists(string &title) throw(BLException)
{
}
int UnitOfMeasurementManager::getUnitOfMeasurementCount() throw(BLException)
{
}
