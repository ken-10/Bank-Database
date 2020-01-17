/**************************************************************
//
// NAME:        Ken Tung
//
// HOMEWORK:    Project 1
//
// CLASS:       ICS 212
//
// INSTRUCTOR:  Ravi Narayan
//
// DATE:        October 23, 2019
//
// FILE:        user_interface.c
//
// DESCRIPTION:
//  This file contains the getaddress function and the main
//  function to run the bank database with or without debug
//  mode for Project 1 - the bank database program
//
***************************************************************/

#include <stdio.h>
#include "record.h"
#include "database.h"
#include "string.h"
#define ESC 27

int debugmode = 0;
void getaddress(char [], int);

/***************************************************************
// 
// FUNCTION NAME:         getaddress
//
// DESCRIPTION:           gets user's address for new record
//
// PARAMETERS:            address (char[]): the inputted address
//                        size (int): length of the address
//
// RETURN VALUES:         void
//
*****************************************************************/

void getaddress(char address[], int size)
{
    char temp;
    int i;

    i = 0;

    printf("Enter your address (ESC then ENTER to quit): \n");
    while ( (temp = getchar()) != 27 )
    {
        address[i] = temp;
        i++;
    }
    
    address[i] = '\0';

    if ( debugmode == 1 )
    {   
        printf("--------------------DEBUG MODE-----------------------\n");
        printf("getaddress function was called with the parameters: \n");
        printf("char address[]: %s\n", address);
        printf("int size: %d\n", size);
        printf("-----------------------------------------------------\n");
    }    

}
/************************************************************************
//
// FUNCTION NAME:         main
//
// DESCRIPTION:           user interface of the program where user
//                        can choose between the different functions
//
// PARAMETERS:            argc (int): contains the number of argurments
//                        being processed
//                        argv (char *[]): pointer character array 
//                        containing each argument passed to the program
//
// RETURN VALUES:         0 : success
//
**************************************************************************/

int main(int argc, char *argv[])
{
    struct record *start;
    char address[100], name[50], newAddress[100], temp[20];
    int true, acctNum, i, redirect;
    char add[3], view[3], viewAll[3], edit[3], del[3], quit[3], menuIn[3]; 
    
    start = NULL;
    
    strcpy(add, "1\n");
    strcpy(view, "2\n");
    strcpy(viewAll, "3\n");
    strcpy(edit, "4\n");
    strcpy(del, "5\n");
    strcpy(quit, "0\n");
    
    true = 1;
    redirect = 1;

    if ( argc == 2 )
    {
        if ( strcmp(argv[1], "debug") == 0 )
        {
            debugmode = 1;
        }
        else
        {
            true = 0;
            printf("Unknown command. './project1 debug' to run in debug mode\n");
        }
    }
    else if ( argc > 2 )
    {
        true = 0;
        printf("Unknown comand. './project1 debug' to run in debug mode\n");
    } 
    
    readfile(&start, "database.txt");
        
    while (true == 1)
    {

        printf("\n-----------------Welcome to UH Manoa Banking-------------------\n");
        printf("\n");
        printf("Choose an option by entering the corresponding number:\n");
        printf("\n");
        printf("Type 1 to add a new record.\n");
        printf("Type 2 to view a record.\n");
        printf("Type 3 to view all records.\n");
        printf("Type 4 to edit a record.\n");
        printf("Type 5 to delete a record.\n");
        printf("Type 0 to quit the program.\n");
        
        fgets(menuIn, 3, stdin);
        
        if (strcmp(menuIn, quit) == 0)
        {
            true = 0;
            printf("Quitting the program...\n");
        }
        else if (strcmp(menuIn, add) == 0)
        {
            redirect = 1;

            while (redirect == 1)
            {
                printf("Enter the new account number: ");

                if (scanf("%d", &acctNum) == 1)
                {
                    if (acctNum < 1)
                    {
                        printf("The account number must be greater than 0!\n");
                        fgets(temp, 19, stdin);
                    }
                    else
                    {
                        redirect = 0;
                    }
                }
                else
                {
                    printf("Numbers only.\n");
                    fgets(temp, 19, stdin);
                }
            }
            
            fgets(temp, 19, stdin);
            printf("Enter name: ");
            fgets(name, 49, stdin);
            getaddress(address, 80);
            fgets(temp, 19, stdin);
            
            for (i = 0; name[i] != '\0'; i++)
            {
                if (name[i] == '\n')
                {
                    name[i] = ' ';
                }
            }
         
            if (addRecord(&start, acctNum, name, address) == 0)
            {
                printf("The new account: %d has been successfully added!\n", acctNum);
            }
        }
        else if (strcmp(menuIn, view) == 0)
        {
            if (start == NULL)
            {
                printf("The bank has no records.\n");
            }
            else
            {
                printf("Enter the account number of the account you want to view: ");
                scanf("%d", &acctNum);
                fgets(temp, 19, stdin);
                printRecord(start, acctNum);
            }
        }
        else if (strcmp(menuIn, viewAll) == 0)
        {
            if (start == NULL)
            {
                printf("The bank has no records.\n");
            }
            else
            {
                printAllRecords(start);
            }
        }
        else if (strcmp(menuIn, edit) == 0)
        {
            if (start == NULL) 
            {
                printf("The bank has no records.\n");
            }
            else
            {
                printf("Enter the account number of the account you want to change: ");
                scanf("%d", &acctNum);
                fgets(temp, 19, stdin);
                getaddress(newAddress, 80);
                if ( modifyRecord(start, acctNum, newAddress) == 0 )
                {
                    printf("\nAddress has been modified.\n");
                }
                fgets(temp, 19, stdin);
            }
        }
        else if (strcmp(menuIn, del) == 0)
        {
            if (start == NULL)
            {
                printf("The bank has no records.\n");
            }
            else
            {
                printf("Enter the account number of the account you want to delete: ");
                scanf("%d", &acctNum);
                fgets(temp, 19, stdin);
                deleteRecord(&start, acctNum);
            }
        }
    }
   
    writefile(start, "database.txt"); 
    cleanup(&start); 
    return 0;
}

