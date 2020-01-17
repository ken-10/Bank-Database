/*****************************************
//
// NAME:          Ken Tung
//
// HOMEWORK:      Project 1
//
// CLASS:         ICS 212
//
// INSTRUCTOR:    Ravi Narayan
//
// DATE:          October 23, 2019
//
// FILE:          database.h
//
// DESCRIPTION:
//  the header file containg function prototypes for databse.c
//
*******************************************/

#include <stdio.h>

int addRecord (struct record **, int, char *,char *);
int printRecord (struct record *, int);
void printAllRecords(struct record *);
int modifyRecord (struct record *, int, char *);
int deleteRecord(struct record **, int);
int readfile(struct record **, char *);
int writefile(struct record *, char *);
void cleanup(struct record **);
