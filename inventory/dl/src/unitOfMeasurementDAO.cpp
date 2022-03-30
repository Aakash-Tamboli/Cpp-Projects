#include<iuom>
#include<uom>
#include<iuomdao>
#include<uomdao>
using namespace inventory;
using namespace data_layer;
void add(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
}
void update(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
}
void remove(int code) throw(DAOException)
{
}
abc::IUnitOfMeasurement *getByCode(int code) throw(DAOException)
{
}
abc::IUnitOfMeasurement *getByTitle(string Title) throw(DAOException)
{
}
forward_list<abc::IUnitOfMeasurement *> * getAll() throw(DAOException)
{
}
int getCount() throw(DAOException)
{
}
int codeExist(int code) throw(DAOException)
{
}
int titleExist(string title) throw(DAOException)
{
}
int main()
{

return 0;
}