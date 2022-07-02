# SQLite Wrapper for C++
## DOCUMENTATION

## Overview
here you get to know about `SQLite Wrapper for c++`, which is built in `c++` programming language.

## Why The SQLite Wrapper For C++ ?
I made project for learning `layered arhitecture` but In data_layer I use Sqlite3 during the Implementation I realise the error handling for each SQL Statement is Difficult So I decided to Make Library and create Wrapper for C++ so Whenver I or anybody who wants to use sqlite3 in c++ so this library or wrapper help a lot...

## Dependencies
* [String utils](#string-utils)
* [Sqlite3](#sqlite3-library)



## SQlite Wrapper Class Methods
* [Common things](#common-things)
* [How to open database](#how-to-open-database)
* [How to insert data](#how-to-insert-data)
* [Error-Handling](#error-handling)

   
### Common things
1 Every Time you should include `sqlite` header.
Ex:
`#include<sqlite>`

2 Always create `SQLiteDB Object`
Ex:
`SqliteDB sqliteDB;`


### How to open database
To opening the database use `open(FILE_NAME)` or just use parameterized constructor
Ex:
```c
SqliteDB sqliteDB;
sqliteDB.open(FILE_NAME);
```


### How to insert data
to Inserting data into table call `executeInsert(SQL_STATEMENT)`

Code-
```c
#include<sqlite>
#include<iostream>
using namespace std;
using namespace sqlite;
int main()
{
SqliteDB sqliteDB;
try
{
sqliteDB.open("some.db");
sqliteDB.executeInsert("insert into students values(101,'sam','M');");
cout<<"SQL statement succefully fire"<<endl;
}catch(SQLiteException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
return 0;
}
```

### Error handling
