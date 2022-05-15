#include<string.h>
#include<iuom>
#include<uom>
#include<iuomdao>
#include<daoexception>
#include<iuomdao>
#include<uomdao>
#include<fstream>
#include<stringutils>
#include<forward_list>
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
UnitOfMeasurementDAO::Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
char arr[100];
if(dataFile.fail())
{
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
abc::IUnitOfMeasurement *unitOfMeasurement;
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code)
{
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(_unitOfMeasurement.code);
unitOfMeasurement->setTitle(string(_unitOfMeasurement.title));
dataFile.close();
return unitOfMeasurement;
}
}
dataFile.close();
sprintf(arr,"Invalid unit of measurement code: %d",code);
throw DAOException(string(arr));
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string Title) throw(DAOException)
{
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() throw(DAOException)
{
UnitOfMeasurementDAO::Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Unit Of Measurement does not exist.");
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Unit Of Measurement does not exist.");
}
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
abc::IUnitOfMeasurement *unitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *> *list;
list=new forward_list<abc::IUnitOfMeasurement *>;
forward_list<abc::IUnitOfMeasurement *>::iterator i=list->before_begin();
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(_unitOfMeasurement.code);
unitOfMeasurement->setTitle(_unitOfMeasurement.title);
i=list->insert_after(i,unitOfMeasurement);
}
dataFile.close();
return list;
/*
Special Note For Aakash,
All The Memory which is allocated in Heap, this All Memeory will be released 
by user or Destructor.
*/
}
int UnitOfMeasurementDAO::getCount() throw(DAOException)
{
UnitOfMeasurementDAO::Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
return 0;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
dataFile.close();
return header.numberOfRecords;
}
int UnitOfMeasurementDAO::codeExist(int code) throw(DAOException)
{
UnitOfMeasurementDAO::Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
return 0;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
if(code<1||code>header.lastGeneratedCode)
{
/*
because we know our add method implementation is like whever new record
is inserted every time lastGeneratedCode increment by 1 and its base value
is 1 so if parameter code variable have value between 1 and lastgenratedCode
then code exists but if not then return  0 means false;
*/
dataFile.close();
return 0;
}
return 1;
}
int UnitOfMeasurementDAO::titleExist(string title) throw(DAOException)
{
UnitOfMeasurementDAO::Header header;
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
return 0;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
return 0;
}
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0)
{
dataFile.close();
return 1;
}
}
dataFile.close();
return 0;
}
