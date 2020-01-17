/***************************************************
//
// NAME:                  Ken Tung
//
// HOMEWORK:              Project 2
//
// CLASS:                 ICS 212
//
// INSTRUCTOR:            Ravi Narayan
//
// DATE:                  December 3, 2019
//
// FILE:                  record.h
//
// DESCRIPTION:
//  This file contains the structure of the record
//  database for Project 2
//
****************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};

#endif
