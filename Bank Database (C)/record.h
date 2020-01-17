/*******************************************
// 
// NAME:           Ken Tung
//
// HOMEWORK:       Project 1
//
// CLASS:          ICS 212
//
// INSTRUCTOR:     Ravi Narayan
//
// DATE:           October 23, 2019
//
// FILE:           record.h
//
// DESCRIPTION:
//  This file contains the structure of the bank
//  database for Project 1
//
********************************************/

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};
