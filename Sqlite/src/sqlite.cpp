#include<sqlite>
#include<sqlite3.h>
#include<iostream>
#include<common/stringutils>
using namespace std;
using namespace sqlite;
using namespace stringutils;
SqliteDB::SqliteDB() throw (SQLiteException)
{
this->db=NULL;
this->FILE_NAME="";
this->fetchedData=NULL;
}
SqliteDB::SqliteDB(const SqliteDB &other) throw (SQLiteException)
{
int resultCode;
string error;
if(other.db==NULL)
{
this->db=NULL;
this->FILE_NAME="";
this->fetchedData=NULL;
return;
}
resultCode=sqlite3_open(other.FILE_NAME.c_str(),&(this->db));
if(resultCode!=SQLITE_OK)
{
error=sqlite3_errmsg(this->db);
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
this->fetchedData=NULL;
throw SQLiteException(string("unable to connect,reason: ")+error);
}
this->FILE_NAME=other.FILE_NAME;
this->fetchedData=NULL;
}
SqliteDB::SqliteDB(const char *fileName) throw (SQLiteException)
{
int resultCode;
string error;
resultCode=sqlite3_open(fileName,&(this->db));
if(resultCode!=SQLITE_OK)
{
error=sqlite3_errmsg(this->db);
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
this->fetchedData=NULL;
throw SQLiteException("unable to connect,reason: "+error);
}
this->FILE_NAME=fileName;
this->fetchedData=NULL;
}
SqliteDB::SqliteDB(string &fileName) throw (SQLiteException)
{
int resultCode;
string error;
resultCode=sqlite3_open(fileName.c_str(),&(this->db));
if(resultCode!=SQLITE_OK)
{
error=sqlite3_errmsg(this->db);
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
this->fetchedData=NULL;
throw SQLiteException("unable to connect,reason: "+error);
}
this->FILE_NAME=fileName;
this->fetchedData=NULL;
}
SqliteDB::~SqliteDB() throw(SQLiteException)
{
if(this->db!=NULL)
{
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
// code to free queue and his element memory;
}
}
void SqliteDB::executeInsert(const char *sql) throw(SQLiteException)
{
string error;
char *errorMessage;
int resultCode,sqlLength;
string vsql=trimmed(string(sql));
sqlLength=vsql.length();
if(sqlLength==0 || sqlLength <= 11) throw SQLiteException("Invalid SQL Statement");
if(this->db==NULL) throw SQLiteException("Unable to insert because no connection to database");
resultCode=sqlite3_exec(this->db,vsql.c_str(),0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
error=errorMessage;
sqlite3_free(errorMessage);
throw SQLiteException(string("unable to insert, reason: ")+error);
}
}
void SqliteDB::executeInsert(const string &sql) throw(SQLiteException)
{
string error;
char *errorMessage;
int resultCode,sqlLength;
string vsql=trimmed(sql);
sqlLength=vsql.length();
if(sqlLength==0 || sqlLength <= 11) throw SQLiteException("Invalid SQL Statement");
if(this->db==NULL) throw SQLiteException("Unable to insert because no connection to database");
resultCode=sqlite3_exec(this->db,vsql.c_str(),0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
error=errorMessage;
sqlite3_free(errorMessage);
throw SQLiteException(string("unable to insert, reason: ")+error);
}
}
void SqliteDB::close() throw (SQLiteException)
{
if(this->db!=NULL)
{
sqlite3_close(this->db);
this->db=NULL;
this->FILE_NAME="";
this->fetchedData=NULL;
}
}
void SqliteDB::open(const char *fileName) throw (SQLiteException)
{
string error;
int resultCode;
if(this->db!=NULL) this->close();
resultCode=sqlite3_open(fileName,&(this->db));
if(resultCode!=SQLITE_OK)
{
error=sqlite3_errmsg(this->db);
this->db=NULL;
throw SQLiteException(string("unable to connect with database, reason: ")+error);
}
}
