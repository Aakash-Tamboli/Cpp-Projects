#include <iostream>
#include <stdlib.h> // for clearing Terminal Screen Of Previous functions output
using namespace std;
class reg
{
private:
    string name, roll_no, teacher_name, Course; // declearing variables
    static int count;                           // for maintaining how many Students are  recorded Right now

public:
    reg() //Constructor if user read data but Register is empty.
    {
        name = "No Name assign";
        roll_no = "No Roll Number";
        Course = "NULL";
    }
    void setData() // for setting data.
    {

        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Roll No.: ";
        getline(cin, roll_no);
        cout << "Enter Teacher Name.: ";
        getline(cin, teacher_name);
        cout << "Enter Course Name.: ";
        getline(cin, Course);
        this->count = this->count + 1;
        system("CLS");
    }
    void Getdata() // for getting data.
    {
        cout << "***************************************************************************" << endl;
        cout << "Student name is: " << name << endl;
        cout << "Student Roll Number is: " << roll_no << endl;
        cout << "Student Class Teacher is: " << teacher_name << endl;
        cout << "Student Course  is: " << Course << endl;
        cout << "***************************************************************************" << endl;
        system("PAUSE");
        system("CLS");
    }
    static int getcount() // everytime that show student count in our Homescreen
    {
        return (count);
    }
    static void DecreaseCount() // for deleting data for aknowlegment that we deleted the dat.
    {
        count--;
    }
    string getroll()
    {
        return (this->roll_no);
    }
    void UpdatingName()
    {
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Your Name is Updated Your Full Detail Check If You Want" << endl;
        cout << "Press 1 For See Deatail" << endl;
        int n = -1;
        cin >> n;
        if (n == 1)
        {
            system("CLS");
            this->Getdata();
        }
    }
    void UpdatingRollNo()
    {
        cout << "Enter Roll: ";
        getline(cin, roll_no);
        cout << "Your Roll No is Updated Your Full Detail Check If You Want" << endl;
        cout << "Press 1 For See Deatail" << endl;
        int n = -1;
        cin >> n;
        if (n == 1)
        {
            system("CLS");
            this->Getdata();
        }
    }
    void UpdatingTeacherName()
    {
        cout << "Enter Teacher Name: ";
        getline(cin, teacher_name);
        cout << "Your Name is Updated Your Full Detail Check If You Want" << endl;
        cout << "Press 1 For See Deatail" << endl;
        int n = -1;
        cin >> n;
        if (n == 1)
        {
            system("CLS");
            this->Getdata();
        }
    }
    void UpdatingCourseName()
    {
        cout << "Enter Course Name: ";
        getline(cin, Course);
        cout << "Your Course Name is Updated Your Full Detail Check If You Want" << endl;
        cout << "Press 1 For See Deatail" << endl;
        int n = -1;
        cin >> n;
        if (n == 1)
        {
            system("CLS");
            this->Getdata();
        }
    }
};
int reg::count = 0;          // intialization of Student Data.
void func(reg obj[], int op) // main class driver code or we can say that is the Flow contorller.
{
    if (op == 1)
    {

        obj[obj->getcount()].setData();
    }
    else if (op == 2) // Show all data entered by user
    {
        if (obj->getcount() != 0)
        {
            for (int i = 0; i < obj->getcount(); i++)
            {
                obj[i].Getdata();
            }
        }
        else // show message if user wants to access 0 data state application..
        {
            cout << "***************************************************************************" << endl;
            cout << "Your Register is Empty" << endl;
            cout << "***************************************************************************" << endl;
            system("PAUSE");
            system("CLS");
        }
    }
    else if (op == 3)
    {
        if (obj->getcount() > 0) // avoid stack Overflow..
        {
            obj->DecreaseCount();
            cout << "Data is Deleted" << endl;
            system("PAUSE");
            system("CLS");
        }
        else
        {
            cout << "Sorry Your Register is already Empty please Fill first.." << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            system("PAUSE");
            system("CLS");
        }
    }
    else if (op == 4)
    {
        if (obj->getcount() != 0)
        {
            string rollnumber;
            cout << "Give me Roll Number" << endl;
            getline(cin, rollnumber);
            bool flag = false;
            for (int i = 0; i < obj->getcount(); i++)
            {
                if (rollnumber == obj[i].getroll())
                {
                    flag = true;
                    system("CLS");
                    obj[i].Getdata();
                    break;
                }
            }
            if (!flag) //data not found condition.
            {
                cout << "***************************************************************************" << endl;
                cout << "Data is Not Found" << endl;
                cout << "***************************************************************************" << endl;
                system("PAUSE");
                system("CLS");
            }
        }
        else //if user try to search no data state application
        {
            cout << "***************************************************************************" << endl;
            cout << "Data is Not Found Because Of No Student Registered Please Registered First" << endl;
            cout << "***************************************************************************" << endl;
            system("PAUSE");
            system("CLS");
        }
    }
    else if (op == 5) // Flow control decides the Flow of Edititing of data.
    {
        string rollnumber;
        cout << "Which Student wants To edit Detail" << endl;
        cout << "Enter The Student Roll No" << endl;
        getline(cin, rollnumber);
        bool flag = false;
        int i;
        for (i = 0; i < obj->getcount(); i++)
        {
            if (rollnumber == obj[i].getroll())
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            cout << "***************************************************************************" << endl;
            cout << "Data is Not Found" << endl;
            cout << "***************************************************************************" << endl;
            system("PAUSE");
            system("CLS");
        }
        else
        {
            system("CLS");
            int anotheroption = -1;
            cout << "Press 1 for Updating Name" << endl;
            cout << "Press 2 for Updating RollNo" << endl;
            cout << "Press 3 for Updating Teacher Name" << endl;
            cout << "Press 4 for Updating Course Name" << endl;
            cin >> anotheroption;
            cin.ignore();
            switch (anotheroption)
            {
            case 1:
                system("CLS");
                obj[i].UpdatingName();
                break;
            case 2:
                system("CLS");
                obj[i].UpdatingRollNo();
                break;
            case 3:
                system("CLS");
                obj[i].UpdatingTeacherName();
                break;
            case 4:
                system("CLS");
                obj[i].UpdatingCourseName();
                break;

            default:
                cout << "***************************************************************************" << endl;
                cout << "Sorry Your Input is Wrong.." << endl;
                cout << "***************************************************************************" << endl;
                system("PAUSE");
                system("CLS");
            }
        }
    }
}

int main() // main driver Code..
{
    reg obj[1000];
    int op = 0;
    while (true)
    {
        cout << "Currently Student record is: " << obj->getcount() << "                                    " << endl;
        cout << "Press 1 for Enter the data" << endl;
        cout << "Press 2 for Show data" << endl;
        cout << "Press 3 for Delete Data" << endl;
        cout << "Press 4 for Searching data" << endl;
        cout << "Press 5 for Edit data" << endl;
        cout << "Press 6 for Exit " << endl;
        cin >> op;
        if (op == 6)
        {
            system("CLS");
            cout << "Thank You For Using" << endl;
            system("PAUSE");
            break;
        }
        cin.ignore();
        system("CLS");
        func(obj, op);
    }

    return 0;
}
