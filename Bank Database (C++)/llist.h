/***************************************************************
//
// NAME:                  Ken Tung
//
// HOMEWORK:              Project 2
//
// CLASS:                 ICS 212
//
// INSTRUCTOR:            Ravi Narayan
//
// DATE:                  December 4, 2019
//
// FILE:                  llist.h
//
// DESCRIPTION:
//  This file contains the class definition for llist.cpp for 
//  Project 2 - the bank database program
//
****************************************************************/

#ifndef llist_h
#define llist_h

#include <iostream>
#include "record.h"
using namespace std;

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    record *    reverse(record * );
    void        cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    int isEmpty();
    int addRecord(int, char [ ],char [ ]);
    int printRecord(int);
    // replace printAllRecords() with the << operator
    friend ostream& operator<<(ostream&, llist&);
    int modifyRecord(int, char [ ]);
    int deleteRecord(int);
    void reverse();
};

#endif
