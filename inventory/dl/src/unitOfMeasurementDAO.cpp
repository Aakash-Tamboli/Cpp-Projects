#include<string.h>
#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/daoexception>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<fstream>
#include<common/stringutils>
#include<forward_list>
#include<iostream>
#include<sqlite3.h>
#include<string.h>
using namespace inventory;
using namespace data_layer;
using namespace stringutils;
int isTitleExistIgnoreCase(void *ptr,int columnCount,char **dataPtr,char **columnNamePtr)
{
int i;
for(i=1;i<columnCount;i+=2)
{
if(compareStringIgnoreCase(dataPtr[i],(char *)ptr)==0) throw DAOException(string((char *)ptr)+" already exist");
}
return 0;
}
int preparingList(void *ptr,int columnCount,char **dataPtr,char **columnNamePtr)
{
int e=0;
forward_list<abc::IUnitOfMeasurement *> *list;
list=(forward_list<abc::IUnitOfMeasurement *> *)ptr;
forward_list<abc::IUnitOfMeasurement *>::iterator i=list->before_begin();
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
abc::IUnitOfMeasurement *unitOfMeasurement;
while(1)
{
if(e>=columnCount) break;
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(atoi(dataPtr[e]));
e++;
unitOfMeasurement->setTitle(dataPtr[e]);
e++;
i=list->insert_after(i,unitOfMeasurement);
}
return 0;
}
void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
sqlite3 *db;
int resultCode,tableExist;
char *errorMessage=NULL;
char sql[1001];
if(unitOfMeasurement==NULL) throw DAOException("do not pass NULL");
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
if(title.length()==0) throw DAOException("title is required");
if(title.length()>50) throw DAOException("title excced 50 characters");
if(unitOfMeasurement->getCode()!=0) throw DAOException("code should be zero");
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
throw DAOException("unable to establish connection");
sqlite3_close(db);
}
sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS UOM(code Integer NOT NULL primary key AUTOINCREMENT,title char(50));",0,0,&errorMessage);
sqlite3_exec(db,"select * from UOM;",isTitleExistIgnoreCase,(void *)title.c_str(),&errorMessage);
sprintf(sql,"insert into UOM (title) values('%s');",title.c_str());
resultCode=sqlite3_exec(db,sql,0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
throw DAOException("unable to add : "+title);
sqlite3_close(db);
}
unitOfMeasurement->setCode(sqlite3_last_insert_rowid(db));
}
void UnitOfMeasurementDAO::update(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
int found,pos;
UnitOfMeasurementDAO::Header header;
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
string vTitle;
int code;
char arr[101];
code=unitOfMeasurement->getCode();
vTitle=unitOfMeasurement->getTitle();
vTitle=trimmed(vTitle);
if(vTitle.length()==0) throw DAOException("title is required");
if(vTitle.length()>50) throw DAOException("title excced 50 characters");
if(code<=0)
{
throw DAOException("Invalid Code may be you pass negative or zero");
}
fstream dataFile(FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
throw DAOException(string(unitOfMeasurement->getTitle())+string(", does not exist"));
}
dataFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);
dataFile.read((char *)&header,sizeof(UnitOfMeasurementDAO::Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException(string(unitOfMeasurement->getTitle())+string(", does not exist"));
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException(string(unitOfMeasurement->getTitle())+string(", does not exist"));
}
found=0;
while(1)
{
pos=dataFile.tellp();
dataFile.read((char *)&_unitOfMeasurement,sizeof(UnitOfMeasurementDAO::_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code)
{
found=1;
break;
}
}
if(found==0)
{
dataFile.close();
sprintf(arr,"Code does not exist: %d",code);
throw DAOException(string(arr));
}
dataFile.clear();
dataFile.seekg(sizeof(UnitOfMeasurementDAO::Header),ios::beg);
dataFile.seekp(sizeof(UnitOfMeasurementDAO::Header),ios::beg);
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(UnitOfMeasurementDAO::_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,vTitle.c_str())==0 && code!=_unitOfMeasurement.code)
{
found=0;
break;
}
}
if(found==0)
{
dataFile.close();
throw DAOException(vTitle+string(" ,exist"));
}
strcpy(_unitOfMeasurement.title,vTitle.c_str());
_unitOfMeasurement.code=code;
dataFile.clear();
dataFile.seekg(pos,ios::beg);
dataFile.seekp(pos,ios::beg);
dataFile.write((char *)&_unitOfMeasurement,sizeof(UnitOfMeasurementDAO::_UnitOfMeasurement));
dataFile.close();
}
void UnitOfMeasurementDAO::remove(int code) throw(DAOException)
{
int found;
UnitOfMeasurementDAO::Header header;
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
char arr[101];
if(code<=0)
{
throw DAOException("Invalid Code may be you pass negative or zero");
}
fstream dataFile(FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
sprintf(arr,"%d is not Exist",code);
throw DAOException(arr);
}
dataFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);
dataFile.read((char *)&header,sizeof(UnitOfMeasurementDAO::Header));
if(dataFile.fail())
{
dataFile.close();
sprintf(arr,"%d is not Exist",code);
throw DAOException(arr);
}
if(header.numberOfRecords==0)
{
dataFile.close();
sprintf(arr,"%d is not Exist",code);
throw DAOException(arr);
}
found=0;
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(UnitOfMeasurementDAO::_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code)
{
found=1;
break;
}
}
if(found==0)
{
dataFile.close();
sprintf(arr,"Code does not exist: %d",code);
throw DAOException(string(arr));
}
else
{
dataFile.clear();
dataFile.seekg(sizeof(UnitOfMeasurementDAO::Header),ios::beg);
dataFile.seekp(sizeof(UnitOfMeasurementDAO::Header),ios::beg);
ofstream tmpWrite("tmp.dat",ios::out | ios::binary);
header.numberOfRecords--;
tmpWrite.write((char *)&header,sizeof(UnitOfMeasurementDAO::Header));
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(UnitOfMeasurementDAO::_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code!=code)
{
tmpWrite.write((char *)&_unitOfMeasurement,sizeof(UnitOfMeasurementDAO::_UnitOfMeasurement));
}
}
dataFile.close();
tmpWrite.close();
ifstream tmpRead("tmp.dat",ios::in | ios::binary);
tmpRead.seekg(0,ios::beg);
ofstream newDataFile(FILE_NAME,ios::out | ios::binary);
tmpRead.read((char *)&header,sizeof(UnitOfMeasurementDAO::Header));
newDataFile.write((char *)&header,sizeof(UnitOfMeasurementDAO::Header));
while(1)
{
tmpRead.read((char *)&_unitOfMeasurement,sizeof(UnitOfMeasurementDAO::_UnitOfMeasurement));
if(tmpRead.fail()) break;
newDataFile.write((char *)&_unitOfMeasurement,sizeof(UnitOfMeasurementDAO::_UnitOfMeasurement));
}
newDataFile.close();
tmpRead.close();
tmpWrite.open("tmp.dat",ios::out | ios::binary);
tmpWrite.close();
}
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
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string title) throw(DAOException)
{
UnitOfMeasurementDAO::Header header;
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
abc::IUnitOfMeasurement *unitOfMeasurement;
string vTitle=trimmed(title);
if(vTitle.length()==0) throw DAOException("title is required");
if(vTitle.length()>50) throw DAOException("title excced 50 characters");
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException(string(vTitle)+string(" ,not Exist"));
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException(string(vTitle)+string(" ,not Exist"));
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException(string(vTitle)+string(" ,not Exist"));
}
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0)
{
dataFile.close();
unitOfMeasurement=new UnitOfMeasurement;
unitOfMeasurement->setCode(_unitOfMeasurement.code);
unitOfMeasurement->setTitle(_unitOfMeasurement.title);
return unitOfMeasurement;
}
}
dataFile.close();
throw DAOException(string(vTitle)+string(" ,not Exist"));
}

forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() throw(DAOException)
{
sqlite3 *db;
char *errorMessage;
int resultCode;
forward_list<abc::IUnitOfMeasurement *> *list;
resultCode=sqlite3_open(FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
throw DAOException("unable to establish connection");
}
resultCode=sqlite3_exec(db,"CREATE TABLE UOM(code Integer NOT NULL primary key AUTOINCREMENT,title char(50));",0,0,&errorMessage);
if(resultCode==0) // means first time table created so no record;
{
sqlite3_close(db);
throw DAOException("No Records");
}
list=new forward_list<abc::IUnitOfMeasurement *>;
resultCode=sqlite3_exec(db,"select * from UOM;",preparingList,list,&errorMessage);
if(resultCode!=SQLITE_OK)
{
sqlite3_close(db);
sqlite3_free(errorMessage);
throw DAOException("something wrong");
}
sqlite3_close(db);
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
if(code<1)
{
/*
because we know our add method implementation is like whever new record
is inserted every time numberOfRecords increment by 1 and its base value
is 1 if code value is zero or negative then return false;
*/
return 0;
}
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
if(header.numberOfRecords==0)
{
dataFile.close();
return 0;
}
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(code==_unitOfMeasurement.code)
{
return 1;
}
}
return 0;
}
int UnitOfMeasurementDAO::titleExist(string title) throw(DAOException)
{
UnitOfMeasurementDAO::Header header;
UnitOfMeasurementDAO::_UnitOfMeasurement _unitOfMeasurement;
string vTitle=trimmed(title);
if(vTitle.length()==0) throw DAOException("title is required");
if(vTitle.length()>50) throw DAOException("title excced 50 characters");
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
if(header.numberOfRecords==0)
{
dataFile.close();
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
