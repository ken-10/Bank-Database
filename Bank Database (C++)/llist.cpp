/*********************************************************
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
// FILE:               llist.cpp
//
// DESCRIPTION:
//  This file contains the functions to read and write
//  from the data file, add, print, delete, reverse, and
//  modify the records in the database
//
**********************************************************/

#include <iostream>
#include "llist.h"
#include "record.h"
#include <cstring>
#include <fstream>
using namespace std;

/*********************************************************
//
// FUNCTION NAME:         llist
//
// DESCRIPTION:           The class constructor that 
//                        creates a new 'llist' object
//
// PARAMETERS:            none
//
// RETURN VALUES:         none
//
*********************************************************/

llist::llist() 
{

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "llist constructor has been called with the parameters: " << endl;
        cout << "No parameters" << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif

    this->start = NULL;
    readfile();
}

/*************************************************************
//
// FUNCTION NAME:         llist
//
// DESCRIPTION:           The class constructor that 
//                        creates a new 'llist' object and
//                        reads from a specified save file
//
// PARAMETERS:            userfile (char []) : the specified
//                        save file that is passed in the
//                        readfile function
//
// RETURN VALUES:         none
//
***************************************************************/

llist::llist(char userfile[])
{

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "llist constructor parameter has been called with the parameters: " << endl;
        cout << "char userfile[]" << userfile << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif

    this->start = NULL;
    strcpy(filename, userfile);
    readfile();
}

/************************************************************************
//
// FUNCTION NAME:           ~llist
//
// DESCRIPTION:             The class destrutor that writes the
//                          records to a save file and then deletes 
//                          all the records in the database from memory
//
// PARAMETERS:              none
//
// RETURN VALUES:           none
//
************************************************************************/

llist::~llist()
{

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "~llist destructor has been called with the parameters: " << endl;
        cout << "No parameters" << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif

    writefile();
    cleanup();
}

/**********************************************************************
//
// FUNCTION NAME:           isEmpty
//
// DESCRIPTION:             Checks if the database is empty
//
// PARAMETERS:              none
//
// RETURN VALUES:           0 : empty
//                         -1 : not empty
//
**********************************************************************/

int llist::isEmpty()
{
    int empty;

    if (start == NULL)
    {
        empty = 0;
    }
    else
    {
        empty = -1;
    }
    
    return empty;
}

/*******************************************************************
//
// FUNCTION NAME:           addRecord
//
// DESCRIPTION:             Adds a new record to the database
//
// PARAMETERS:              accountno (int) : account number of
//                          the new record being added
//                          name (char []) : name of the new 
//                          record being added
//                          address (char []) : address of the new
//                          record being added
//
// RETURN VALUES:           0 : success
//                         -1 : failed
//
*******************************************************************/

int llist::addRecord(int accountno, char name[], char address[])
{
    int added;
    int run;
    struct record *current;
    struct record *prev;
    struct record *temp;

    added = -1;

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "addRecord function has been called with the parameters: " << endl;
        cout << "int accountno: " << accountno << endl;
        cout << "char name[]: " << name << endl;
        cout << "char address[]: " << address << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif

    /* empty list */
    if (start == NULL)
    {
        temp = new record();
        temp->accountno = accountno;
        strcpy(temp->name, name);
        strcpy(temp->address, address);
        start = temp;
        current = start;
        added = 0;
    }
    else if ( accountno > start->accountno )
    {
        temp = new record();
        temp->accountno = accountno;
        strcpy(temp->name, name);
        strcpy(temp->address, address);
        temp->next = start;
        start = temp;
        current = start;
        added = 0;
    }
    else
    {
        run = 1;
        current = start;
        prev = current;
        while (run == 1) 
        {
            /* duplicate account numbers */
            if (accountno == current->accountno)
            {
                cout << "accountno: " << accountno << endl;
                cout << "current: " << current->accountno << endl;
                cout << "Duplicate account numbers not allowed!" << endl << endl;
                run = 0;
            }
            /* adding in the middle of list */
            else if (accountno > current->accountno)
            {
                temp = new record();
                temp->accountno = accountno;
                strcpy(temp->name, name);
                strcpy(temp->address, address);
                temp->next = current;
                prev->next = temp;
                added = 0;
                run = 0;
            }
            /* adding at the end of the list */
            else if (current->next == NULL)
            {
                temp = new record();
                temp->accountno = accountno;
                strcpy(temp->name, name);
                strcpy(temp->address, address);
                current->next = temp;
                temp->next = NULL;
                added = 0;
                run = 0;
            }
            else
            {
                prev = current;
                current = current->next;
            }
            
        }
    }
    return added;
}

/****************************************************************
//
// FUNCITON NAME:          printRecord
//
// DESCRIPTION:            Prints a specific record in the database
//
// PARAMETERS:             accountno (int) : account number of the
//                         record being viewed
//
// RETURN VALUES:          0 : account exists
//                        -1 : failed
//
******************************************************************/

int llist::printRecord(int accountno)
{
    int print;
    int run;
    struct record *current;
    struct record *currentNext;

    run = 1;
    print = -1;

    current = start;

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "printRecord function has been called with the parameters: " << endl;
        cout << "int accountno: " << accountno << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif

    if ( start == NULL )
    {
        cout << "ERROR: The bank has no records" << endl;
    }
    else
    {
        while (current != NULL && run == 1)
        {
            currentNext = current->next;
        
            /* finds the record */
            if (current->accountno == accountno)
            {
                cout << endl << endl << "RECORD #" << accountno << endl;
                cout << endl << "Account number: " << current->accountno << endl;
                cout << "Name: " << current->name << endl;
                cout << "Address: " << endl << current->address << endl;
                run = 0;
                print = 0;
            }
            /* record not in list */
            else if (current->next == NULL && current->accountno != accountno)
            {
                run = 0;
                cout << "The record with the account number " << accountno << " does not exist!" << endl << endl;
            }
            /* iterate through the list */
            else
            {
                current = currentNext;
                currentNext = current->next;
            }
        }
    }
    return print;
}

/*********************************************************************
//
// FUNCTION NAME:             operator<<
//
// DESCRIPTION:               Prints all the records in the database.
//                           
// PARAMETERS:                output (ostream &) : the output stream
//                            that is passed by reference
//
//                            llist (llist &) : the linked list object
//                            that contains the records
//
// RETURN VALUES:             output : prints all the records
//
**********************************************************************/

ostream& operator<<(ostream& output, llist& llist)
{
    record *current;
    current = llist.start;

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "operator<< function has been called with the parameters: " << endl;
        cout << "ostream&: " << &output << endl;
        cout << "llist&: " << &llist << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif

    if ( current == NULL )
    {
        output << "ERROR: The bank has no records." << endl;
    } 
    else
    {
        output << endl << endl << "ALL DATABASES: " << endl;

        while ( current != NULL )
        {
            output << endl << "Account: " << current->accountno << endl;
            output << "Name: " << current->name << endl;
            output << "Address: " << endl << current->address << endl << endl;
            current = current->next;
        }
    }
    return output;
}

/************************************************************************
//
// FUNCTION NAME:             modifyRecord
//
// DESCRIPTION:               Modifies the address of a specific record
// 
// PARAMETERS:                accountno (int) : the account number of the
//                            record being modified
//
//                            address (char []) : the new address of the
//                            record
//
// RETURN VALUES:             0 : success
//                           -1 : failed
//
**************************************************************************/

int llist::modifyRecord(int accountno, char address[])
{
    int modded;
    int run;
    struct record *current;
    struct record *currentNext;

    modded = -1;
    run = 1;

    current = start;

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "modifyRecord function has been called with the parameters: " << endl;
        cout << "int accountno: " << accountno << endl;
        cout << "char address[]: " << address << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif   

    if ( current == NULL )
    {
        cout << endl << "ERROR: The bank has no records" << endl;
    }
    else
    {
        while ( current != NULL && run == 1 )
        {
            currentNext = current->next;

            if ( current->accountno == accountno )
            {
                strcpy( current->address, address );
                modded = 0;
                run = 0;
            } 
            else if ( current->next == NULL && current->accountno != accountno )
            {
                cout << "The record with the account number " << accountno << " does not exist!" << endl << endl;
                run = 0;
            }
            else
            {
                current = currentNext;
                currentNext = current->next;
            }
        }
    }
    return modded; 
}

/*****************************************************************************
//
// FUNCTION NAME:                 deleteRecord
//
// DESCRIPTION:                   Deletes a specific record in the database.
//
// PARAMETERS:                    accountno (int) : the account number of the
//                                record being deleted
//
// RETURN VALUES:                 0 : success
//                               -1 : failed
//
*******************************************************************************/

int llist::deleteRecord(int accountno)
{
    int deleted;
    int run;
    struct record *current;
    struct record *temp;
    struct record *prev;

    deleted = -1;
    run = 1;

    current = start;
    prev = current;

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "deleteRecord function has been called with the parameters: " << endl;
        cout << "int accountno: " << accountno << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif 
    
    if ( current == NULL )
    {
        cout << endl << "ERROR: The bank database is empty" << endl;
    }
    else
    {    
        while ( current != NULL && run == 1 )
        {
            if ( current->accountno == accountno )
            {
                if ( current == start && current->next == NULL )
                {
                    temp = current;
                    start = NULL;
                    current = NULL;
                    prev = NULL;
                    delete temp;
                    deleted = 0;
                    run = 0;
                }
                else if ( current == start && current->next != NULL )
                {
                    temp = current;
                    start = current->next;
                    current = start;
                    prev = current;
                    delete temp;
                    deleted = 0;
                    run = 0;
                }
                else
                {
                    temp = current;
                    current = current->next;
                    prev->next = current;
                    delete temp;
                    deleted = 0;
                    run = 0;
                }
            }
            else if ( current->next == NULL && current->accountno != accountno )
            {
                cout << "The record with the account number " << accountno << " does not exist!" << endl << endl;    
                run = 0;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
    }

    return deleted;
}

/**********************************************************************
//
// FUNCTION NAME:                  reverse
//
// DESCRIPTION:                    Reverses the order of the records
//                                 in the database
//
// PARAMETERS:                     start (record *) : the starting
//                                 pointer of the linked list
//
// RETURN VALUES:                  temp : the new head of the list
//
**********************************************************************/

record * llist::reverse(record *start)
{
    record *current;
    record *temp;

    current = start;
    temp = current;

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "reverse function has been called with the parameters: " << endl;
        cout << "record *start " << start << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif 

    if ( current == NULL )
    {
        temp = current;
    }
    else if ( current->next == NULL )
    {
        temp = current;
    }
    else
    {
        temp = reverse(start->next);
        start->next->next = start;
        start->next = NULL;
    }
    
    return temp;
}

/**********************************************************************
//
// FUNCTION NAME:                  reverse
//
// DESCRIPTION:                    A user interface function that
//                                 reverse the order of the records
//
// PARAMETERS:                     none
//
// RETURN VALUES:                  none
//
**********************************************************************/

void llist::reverse()
{

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "reverse function (non-recursive) has been called with the parameters: " << endl;
        cout << "No parameters" << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif 

    if ( start == NULL )
    {
        cout << endl << "ERROR: The bank has no records" << endl;
    }
    else
    {
        start = reverse(start);        
        cout << endl << "The database order has been reversed" << endl;
    }
}

/*************************************************************************
//
// FUNCTION NAME:                 cleanup
//
// DESCRIPTION:                   Deletes all the records in the database.
//
// PARAMETERS:                    none
//
// RETURN VALUES:                 none
//
***************************************************************************/

void llist::cleanup()
{
    struct record *current;
    struct record *currentNext;
    struct record *temp;
    int run;

    run = 1;

    current = start;


    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "cleanup function has been called with the parameters: " << endl;
        cout << "No parameters" << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif 

    while (current != NULL && run == 1)
    {
        currentNext = current->next;
        /* end of list */
        if (currentNext == NULL)
        {
            temp = current;
            start = NULL;
            current = start;
            currentNext = current;
            delete(temp);
            run = 0;
        }
        else
        {
            temp = current;
            current = currentNext;
            currentNext = current->next;
            delete(temp);
        }
    }
}

/**************************************************************************
// 
// FUNCTION NAME:                  readfile
//
// DESCRIPTION:                    Reads the data from a save file and
//                                 uses the addRecord function to create
//                                 the database
//
// PARAMETERS:                     none
//
// RETURN VALUES:                  0 : success
//                                -1 : failed
//
***************************************************************************/

int llist::readfile()
{
    int success;
    int accountno;
    string name;
    string address;
    string temp;
    char name2[25];
    char address2[80];

    success = 0;


    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "readfile function has been called with the parameters: " << endl;
        cout << "No parameters" << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif

    ifstream inputfile;
    inputfile.open("database.txt");
    if (inputfile == NULL)
    {
        success = -1;
    }
    else
    {
        while(inputfile >> accountno)
        {
            inputfile.clear();
            inputfile.ignore();
            getline(inputfile, name);
            getline(inputfile, address, '$');
            strcpy(name2, name.c_str());
            strcpy(address2, address.c_str());
            addRecord(accountno, name2, address2);
        }
    inputfile.close();
    }
    return success;
}

/***************************************************************************
//
// FUNCTION NAME:                  writefile
//
// DESCRIPTION:                    Writes the data from the database into
//                                 a save file.
//
// PARAMETERS:                     none
//
// RETURN VALUES:                  0 : success
//                                -1 : failed
//
*****************************************************************************/

int llist::writefile()
{
    ofstream outfile;
    struct record *current;
    struct record *currentNext;
    int run;
    int success;

    success = 0;
    run = 1;

    #ifdef DEBUG
        cout << endl << "-----------------------DEBUG MODE----------------------" << endl;
        cout << "writefile function has been called with the parameters: " << endl;
        cout << "No parameters" << endl;
        cout << "-------------------------------------------------------" << endl << endl;
    #endif
   
    outfile.open("database.txt");

    current = start;
    
    if (outfile == NULL)
    {
        success = -1;
    }
    else
    {
        while (current != NULL && run == 1)
        {
            currentNext = current->next;
            if (currentNext == NULL)
            {
                outfile << current->accountno << endl;
                outfile << current->name << endl;
                outfile << current->address << "$";
                outfile.close();
                run = 0;
            }
            else
            {
                outfile << current->accountno << endl;
                outfile << current->name << endl;
                outfile << current->address << "$";
                current = currentNext;
                currentNext = current->next;
            }
        }
    }
    return success;
}
