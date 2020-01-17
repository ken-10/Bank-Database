/*********************************************
//
// NAME:          Ken Tung
//
// HOMEWORK:      Project 1
//
// Class:         ICS 212
//
// INSTRUCTOR:    Ravi Narayan
//
// DATE:          October 23, 2019
//
// FILE:          database.c
//
// DESCRIPTION:
//  This file contains the functions
//  for project 1 - the bank database
//  program
//
***********************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"
#include <stdlib.h>
#include "database.h"
extern int debugmode;

/***********************************************
//
// FUNCTION NAME:    addRecord
//
// DESCRIPTION:      Adds a new record to the database
//
// PARAMETERS:       struct record **: starting record in list
//                   int: account number
//                   char[]: name of the account
//                   char[]: address of the account
//
// RETURN VALUES:    int 0 : Added
//                      -1 : Failed
//
***********************************************/

int addRecord(struct record **start, int accountno, char name[], char address[])
{
    int added;
    int run;
    struct record *temp;
    struct record *current;
    struct record *prev;
    added = -1;
    
    if (debugmode == 1)
    {
        printf("\n-----------------------DEBUG MODE----------------------\n");
        printf("addRecord function has been called with the parameters:\n");
        printf("struct record **start: %p\n", (void *) &start);
        printf("int accountno: %d\n", accountno);
        printf("char name[]: %s\n", name);
        printf("char address[]: %s\n", address);
        printf("-------------------------------------------------------\n");
        printf("\n");
    }

    /* adding in empty list */ 
    if ( *start == NULL )
    {
        temp = (struct record*)malloc(sizeof(struct record));
        (*temp).accountno = accountno;
        strcpy((*temp).name, name);
        strcpy((*temp).address, address);
        (*temp).next = NULL;
        *start = temp;
        current = *start;
        added = 0;
    }
    /* adding at beginning of the list */
    else if( accountno > (**start).accountno )
    {
        temp = (struct record*)malloc(sizeof(struct record));
        (*temp).accountno = accountno;
        strcpy((*temp).name, name);
        strcpy((*temp).address, address);
        (*temp).next = *start;
        *start = temp;
        current = *start;
        added = 0;
    }
    else
    {
        run = 1;
        current = *start;
        prev = current;
        while ( run == 1 )
        {
            /* duplicate account numbers */
            if ( accountno == (*current).accountno )
            {
                printf("accountno: %d\n", accountno);
                printf("current: %d\n", (*current).accountno);
                printf("Duplicate account numbers not allowed!\n\n");
                run = 0;
            }
            /* adding in the middle of the list */
            else if ( accountno > (*current).accountno )
            {
                temp = (struct record*)malloc(sizeof(struct record));
                (*temp).accountno = accountno;
                strcpy((*temp).name, name);
                strcpy((*temp).address, address);
                (*temp).next = current;
                (*prev).next = temp;
                added = 0;
                run = 0;
            }
            /* adding at the end of the list */
            else if ( (*current).next == NULL )
            {
                temp = (struct record*)malloc(sizeof(struct record));
                (*temp).accountno = accountno;
                strcpy((*temp).name, name);
                strcpy((*temp).address, address);    
                (*current).next = temp;
                (*temp).next = NULL;
                added = 0;
                run = 0;   
            }
            /* traverse through the list */
            else
            {
                prev = current;
                current = (*current).next;
            }
        }
    }
    
    return added;
}

/***********************************************
//
// FUNCTION NAME:    printRecord
//
// DESCRIPTION:      Prints a record in the database
//
// PARAMETERS:       struct record *: starting record in list
//                   int: account number
//
// RETURN VALUES:    int 0 : Printed
//                      -1 : Failed
//
***********************************************/

int printRecord( struct record *start, int accountno )
{
    int print;
    int run;
    struct record *current;
    struct record *currentNext;
    
    run = 1;
    print = -1;

    if ( debugmode == 1)
    {
        printf("\n-----------------------DEBUG MODE----------------------\n");
        printf("printRecord function has been called with the parameters:\n");
        printf("struct record *start is: %p\n", (void *) start);
        printf("int accountno: %d\n", accountno);
        printf("-------------------------------------------------------\n");
        printf("\n");
    }

    current = start;
    
    while ( current != NULL && run == 1 )
    {
        currentNext = (*current).next;
        
        if ((*current).accountno == accountno )
        {
            printf("\nAccount number: %d\n", (*current).accountno);
            printf("Name: %s\n", (*current).name);
            printf("Address:\n");
            printf("%s\n", (*current).address);
            printf("\n");
            run = 0;
            print = 0;
        }
        else if ( (*current).next == NULL && (*current).accountno != accountno )
        {
            run = 0;
        }
        else
        {
            current = currentNext;
            currentNext = (*current).next;
        }
    }

    if ( print == -1 )
    {
        printf("\nThe record with the account number %d does not exist!\n", accountno);
        printf("\n");
    }
    

    return print;
}


/***********************************************
//
// FUNCTION NAME:    printAllRecord
//
// DESCRIPTION:      Prints all records in the database
//
// PARAMETERS:       struct record *: starting record in list
//
// RETURN VALUES:    void
//
***********************************************/

void printAllRecords(struct record *start)
{
    struct record *current;
    struct record *currentNext;
    int run;
    run = 1;
    
    if ( debugmode == 1)
    {
        printf("\n-----------------------DEBUG MODE----------------------\n");
        printf("printAllRecord function has been called with the parameters:\n");
        printf("struct record *start is: %p\n", (void *) start);
        printf("-------------------------------------------------------\n");
        printf("\n");
    }  
    
    current = start;

    while ( current != NULL && run == 1 )
    {
        currentNext = (*current).next;

        if ( currentNext == NULL )
        {
            printf("\nAccount number: %d\n", (*current).accountno);
            printf("Name: %s\n", (*current).name);
            printf("Address:\n");
            printf("%s\n", (*current).address);
            printf("\n");
            run = 0;
        }
        else
        {
            printf("\nAccount number: %d\n", (*current).accountno);
            printf("Name: %s\n", (*current).name);
            printf("Address:\n");
            printf("%s\n", (*current).address);
            printf("\n");
            current = currentNext;
            currentNext = (*current).next;
        }
    }
    
}

/*************************************************
//
// FUNCTION NAME:    modifyRecord
//
// DESCRIPTION:      Modifies the address of a record in the database
//
// PARAMETERS:       struct record *: starting record in list
//                   int: account number
//                   char[]: address of the account
//
// RETURN VALUES:    int 0 : modified
//                      -1 : Failed
//
// ***********************************************/

int modifyRecord( struct record *start, int accountno, char address[] )
{
    int modded;
    struct record *current;
    struct record *currentNext;
    int run;    
    modded = -1;
    run = 1;

    if ( debugmode == 1 )
    {
        printf("\n-----------------------DEBUG MODE----------------------\n");
        printf("modifyRecord function has been called with the parameters:\n");
        printf("struct record *start is: %p\n", (void *) start);
        printf("int accountno: %d\n", accountno);
        printf("char address[]: %s\n", address);
        printf("-------------------------------------------------------\n");
        printf("\n");
    }

    current = start;
    
    while ( current != NULL && run == 1 )
    {   
        currentNext = (*current).next;

        if ((*current).accountno == accountno )
        {
            strcpy( (*current).address, address );            
            modded = 0;
            run = 0;
        }
        else if ( (*current).next == NULL && (*current).accountno != accountno )
        {
            run = 0;
        }
        else
        {   
            current = currentNext;
            currentNext = (*current).next;
        }
    }

 
    if ( modded == -1 )
    {
            printf("\nThe record with the account number %d does not exist!\n", accountno);
    }
    
    
    return modded;
}

/***********************************************
//
// FUNCTION NAME:    deleteRecord
//
// DESCRIPTION:      Deletes a record in the database
//
// PARAMETERS:       struct record **: starting record in list
//                   int: account number
//
// RETURN VALUES:    int 0 : Deleted
//                      -1 : Failed
//
***********************************************/

int deleteRecord( struct record **start, int accountno )
{
    int deleted;
    int run;
    struct record *current;
    struct record *temp;
    struct record *prev;
    deleted = -1;
    run = 1;

    if ( debugmode == 1 )              
    {
        printf("\n-----------------------DEBUG MODE----------------------\n");
        printf("deleteRecord function has been called with the parameters:\n");
        printf("struct record *start is: %p\n", (void *) start);
        printf("int accountno: %d\n", accountno);
        printf("-------------------------------------------------------\n");
        printf("\n");
    }
    
    current = *start;
    prev = current;
    
   
     
    while ( current != NULL && run == 1 )
    {   

        if ( (*current).accountno == accountno )
        {
            if ( current == *start && (*current).next == NULL )
            {
                temp = current;
                *start = NULL;
                current = NULL;
                prev = NULL;
                free(temp);
                deleted = 0;
                run = 0;
            }
            else if ( current == *start && (*current).next != NULL )
            {
                temp = current;
                *start = (*current).next;
                current = *start;
                prev = current;
                free(temp);
                deleted = 0;
                run = 0;
            }
            else
            {
                temp = current;
                current = (*current).next;
                (*prev).next = current;
                free(temp);
                deleted = 0;
                run = 0;
            }
        }
        else
        {   
            prev = current;
            current = (*current).next;
        }
    }
    
    if ( deleted == -1 )
    {
        printf("\nThe record with the account number: %d does not exist!\n", accountno);
        printf("\n");
    }
    else
    {
        printf("\nThe record with the account number: %d has been deleted.\n", accountno);
        printf("\n");
    }

    
    return deleted;
}


/******************************************************************
//
// FUNCTION NAME:         cleanup
//
// DESCRIPTION:           deletes all records in the database
//
// PARAMETERS:            start (record *): the start record
//                        
// RETURN:                void
//
*****************************************************************/

void cleanup( struct record **start)
{
    struct record *current;
    struct record *currentNext;
    struct record *temp;
    int run;
    run = 1;

    if ( debugmode == 1)
    {
        printf("\n-----------------------DEBUG MODE----------------------\n");
        printf("cleanup function has been called with the parameters:\n");
        printf("struct record *start is: %p\n", (void *) start);
        printf("-------------------------------------------------------\n");
        printf("\n");
    }

    current = *start;
    
    while ( current != NULL && run == 1 )
    {
        currentNext = (*current).next;

        if ( currentNext == NULL )
        {
            temp = current;
            *start = NULL;
            current = *start;
            currentNext = current;
            free(temp);
            run = 0;
        }
        else
        {
            temp = current;
            current = currentNext;
            currentNext = (*current).next;
            free(temp);
        }
    }
}



/******************************************************************
//
// FUNCTION NAME:         readfile
//
// DESCRIPTION:           reads records from data file
//
// PARAMETERS:            struct record **: start of the list
//                        char[]: name of file that is being read
//
// RETURN:            int 0: success
//                       -1: failure
//
********************************************************************/

int readfile( struct record **start, char filename[] )
{
    FILE *inputfile;   
    int accountno;
    char name[25], address[80], temp[2];
    int success;
    
    success = 0;

    if ( debugmode == 1)
    {
        printf("\n-----------------------DEBUG MODE----------------------\n");
        printf("readfile function has been called with the parameters:\n");
        printf("struct record **start is: %p\n", (void *) start);
        printf("char filename[]: %s\n", filename);
        printf("-------------------------------------------------------\n");
        printf("\n");
    }
    
    inputfile = fopen("database.txt", "r");
    


    if (inputfile == NULL )
    { 
        success = -1;
    }
    else
    {
        while ( fgetc(inputfile) != EOF )
        {
            fscanf(inputfile, "%i[^\n]", &accountno);
            fscanf(inputfile, "%c", temp);
            fscanf(inputfile, "%[^\n]", name);
            fscanf(inputfile, "%c", temp);
            fscanf(inputfile, "%[^$]", address);
            fscanf(inputfile, "%c", temp);

            addRecord(start, accountno, name, address);
        }  
    
    fclose(inputfile);
    }
    return success;
}

/*****************************************************************
//
// FUNCTION NAME:       writefile
//
// DESCRIPTION:         writes any modifications to the linked list
//                      to the save file
//
// PARAMETERS:          start (record *): the start of the list
//                      filename (char []): the file that is written on
//
// RETURN:              0: success
//                     -1: failure
//
*****************************************************************/

int writefile( struct record *start, char filename[] )
{
    FILE *outputfile;
    struct record *current;
    struct record *currentNext;
    int run;
    int success;

    success = 0;
    run = 1;

    if ( debugmode == 1)
    {
        printf("\n-----------------------DEBUG MODE----------------------\n");
        printf("writefile function has been called with the parameters:\n");
        printf("struct record *start is: %p\n", (void *) start);
        printf("char filename[]: %s\n", filename);
        printf("-------------------------------------------------------\n");
        printf("\n");
    }   
    
    outputfile = fopen("database.txt", "w");
    
    current = start;

    if ( outputfile == NULL )
    {
        success = -1;
    }
    else
    {   
        while ( current != NULL && run == 1 )
        {   
            currentNext = (*current).next;

            if ( currentNext == NULL )
            {
                fprintf(outputfile, "0%i\n", (*current).accountno);
                fprintf(outputfile, "%s\n", (*current).name);
                fprintf(outputfile, "%s$", (*current).address);   
                fclose(outputfile);
                run = 0;
            }
            else
            {   
                fprintf(outputfile, "0%i\n", (*current).accountno);
                fprintf(outputfile, "%s\n", (*current).name);
                fprintf(outputfile, "%s$", (*current).address);
                current = currentNext;
                currentNext = (*current).next;
            }
        }
    }     
    return success;
}

