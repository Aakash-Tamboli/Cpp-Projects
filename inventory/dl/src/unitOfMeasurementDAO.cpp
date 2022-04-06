#include<string.h>
#include<iuom>
#include<uom>
#include<iuomdao>
#include<daoexception>
#include<iuomdao>
#include<uomdao>
#include<fstream>
#include<stringutils>
using namespace inventory;
using namespace data_layer;
using namespace stringutils;
void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
if(unitOfMeasurement==NULL) throw DAOException("do not pass NULL");
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0) throw DAOException("title is required");
if(title.length()>50) throw DAOException("title excced 50 characters");
if(unitOfMeasurement->getCode()!=0) throw DAOException("code should be zero");
UnitOfMeasurementDAO::Header header;
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
fstream dataFile(FILE_NAME,ios::in|ios::out| ios::binary);
if(dataFile.fail())
{
fstream dFile(FILE_NAME,ios::app | ios::binary);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
dFile.write((char *)&header,sizeof(Header));
_unitOfMeasurement.code=1;
strcpy(_unitOfMeasurement.title,title.c_str());
dFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dFile.close();
unitOfMeasurement->setCode(1);
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) // if data file is 0 byte for any reason that's why we take precaution
{
dataFile.clear(); // try to understand if file is 0 byte and we are trying read from file so our internal pointer moves to eof point and rule is if internal pointer cross eof and you don't write anything that why its precautionary
dataFile.seekg(0,ios::beg);//sir says take precaution as much as possible in project
dataFile.seekp(0,ios::beg);//sir says take precaution as much as possible in project
header.lastGeneratedCode=1;
header.numberOfRecords=1;
dataFile.write((char *)&header,sizeof(Header));
_unitOfMeasurement.code=1;
strcpy(_unitOfMeasurement.title,title.c_str());
dataFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dataFile.close();
unitOfMeasurement->setCode(1);
return;
}
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0)
{
dataFile.close();
throw DAOException(title+" already exist");
}
}
dataFile.clear(); // because our internal pointer cross eof point
header.lastGeneratedCode++;
header.numberOfRecords++;
_unitOfMeasurement.code=header.lastGeneratedCode;
strcpy(_unitOfMeasurement.title,title.c_str());
dataFile.seekp(0,ios::end);
dataFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close();
unitOfMeasurement->setCode(_unitOfMeasurement.code);
}
void UnitOfMeasurementDAO::update(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
}
void UnitOfMeasurementDAO::remove(int code) throw(DAOException)
{
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByCode(int code) throw(DAOException)
{
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string Title) throw(DAOException)
{
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() throw(DAOException)
{
}
int UnitOfMeasurementDAO::getCount() throw(DAOException)
{
}
int UnitOfMeasurementDAO::codeExist(int code) throw(DAOException)
{
}
int UnitOfMeasurementDAO::titleExist(string title) throw(DAOException)
{
}
