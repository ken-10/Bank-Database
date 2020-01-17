/************************************************************
//
// NAME:               Ken Tung
//
// HOMEWORK:           Project 2
//
// CLASS:              ICS 212
// 
// INSTRUCTOR:         Ravi Narayan
//
// DATE:               December 4, 2019
//
// FILE:               user_interface.cpp
//
// DESCRIPTION:
//  This file contains the getaddress function and the main
//  function to run the banh database with or without debug
//  mode for Project 2 - the bank database program
//
**************************************************************/ 

#include <iostream>
#include "record.h"
#include "llist.h"
#include <cstring>
#include <fstream>

using namespace std;

void getaddress(char [], int);

/***********************************************************************
//
// FUNCTION NAME:              getaddress
//
// DESCRIPTION:                Obtains the address for a record
//
// PARAMETERS:                 address (char []) : the address
//                             size (int) : max length of the address
//
// RETURN VALUES:              none
//
***********************************************************************/

void getaddress(char address[], int size)
{
    cout << "Enter the address ( ';' then 'ENTER' to quit )" << endl;
    cin.getline(address, 80, ';');

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "getaddress function has been called with the parameters: " << endl;
        cout << "char address[]" << address << endl;
        cout << "int size" << size << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif
}

/*************************************************************************
//
// FUNCTION NAME:               main
//
// DESCRIPTION:                 User interface of the program where the
//                              user can choose between the different
//                              functions
//
// PARAMETERS:                  argc (int) : contains the number of 
//                              arguments being processed
//
//                              argv (char *[]) : pointer character 
//                              array containing each argument passed to
//                              the program
//
// RETURN VALUES:               0 : success
//
**************************************************************************/

int main(int argc, char *argv[])
{
    ifstream file;
    char address[80], name[25];
    int menuIn;
    int run;
    int accountno;
    int redirect;
    llist mylist;

    run = 1;
    redirect = 1;

    while (run == 1)
    {
        cout << endl << "---------------Welcome to UH Manoa Banking---------------" << endl << endl;
        cout << "Choose an option by entering the corresponding number: " << endl << endl;
        cout << "Type 1 to add a new record" << endl;
        cout << "Type 2 to view a record" << endl;
        cout << "Type 3 to view all records." << endl;
        cout << "Type 4 to edit a record." << endl;
        cout << "Type 5 to delete a record." << endl;
        cout << "Type 6 to reverse the database." << endl;
        cout << "Type 0 to quit the program." << endl;

        cin >> menuIn;

        if (cin.fail())
        {
            cout << endl << "ERROR: Invalid input - Input not an integer" << endl;
            cin.clear();
            cin.ignore();
        }
        else if ( menuIn < 0 )
        {
            cout << endl << "ERROR: Invalid input" << endl;
            cin.clear();
            cin.ignore();
        }
        else if ( menuIn == 0 )
        {
            run = 0;
            cout << "Quitting the program..." << endl;
        }
        else if ( menuIn == 1 )
        {
            redirect = 1;
            while (redirect == 1)
            {
                cout << "Enter the new account number: " << endl;
                
                if (cin >> accountno)
                {
                    if (accountno < 1)
                    {
                        cout << "The account number must be greater than 0!" << endl;
                        cin.clear();
                        cin.ignore();
                    }
                    else
                    {
                        redirect = 0;
                    }
                }
                else
                {
                    cout << "Numbers only." << endl;
                    cin.clear();
                    cin.ignore();
                }
            }
            cin.clear(); 
            cin.ignore();
            cout << "Enter name: " << endl;
            cin.get(name, 25);
            cin.clear();
            cin.ignore();
            getaddress(address, 80);
            cin.clear();
            cin.ignore();
 
            if (mylist.addRecord(accountno, name, address) == 0)
            {
                cout << "The new account: " << accountno << " has been successfully added!" << endl;
            }
        }
        else if ( menuIn == 2 )
        {
            if (mylist.isEmpty() == 0)
            {
                cout << endl << "ERROR: The bank database is empty" << endl;
                cin.clear();
                cin.ignore();
            }
            else
            {
                cout << "Enter an account number: " << endl;
                cin >> accountno;
                cin.clear();
                cin.ignore();
                mylist.printRecord(accountno);
            }
        }
        else if ( menuIn == 3 )
        {
            cout << mylist;
        }
        else if ( menuIn == 5 )
        {
            if (mylist.isEmpty() == 0)
            {
                cout << endl << "ERROR: The bank database is empty" << endl;
                cin.clear();
                cin.ignore();
            }
            else
            {
                cout << "Enter an account number: " << endl;
                cin >> accountno;
                cin.clear();
                cin.ignore();
                if (mylist.deleteRecord(accountno) == 0)
                {
                    cout << endl << "The record has been deleted" << endl;
                }
            }
                
        }
        else if ( menuIn == 4 )
        {
            if (mylist.isEmpty() == 0)
            {
                cout << endl << "ERROR: The bank database is empty" << endl;
                cin.clear();
                cin.ignore();
            }
            else
            {
                cout << "Enter an account number: " << endl;
                cin >> accountno;
                cin.clear();
                cin.ignore(); 
                getaddress(address, 80);
                cin.clear();
                cin.ignore();
                if (mylist.modifyRecord(accountno, address) == 0)
                {
                    cout << endl << "The address has been modified." << endl;
                }
            }
        }
        else if ( menuIn == 6 )
        {
            mylist.reverse();
            cin.clear();
            cin.ignore();
        }
    }
    return 0;
}

