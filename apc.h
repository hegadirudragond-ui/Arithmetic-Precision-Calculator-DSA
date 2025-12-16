/*******************************************************************************************************************************************************************
* Name        : Rudragond Hegadi
* Date        : 7/12/2025
* File Name   : apc.h
* Description : Header file for Arbitrary Precision Calculator (APC). 
*               Contains the structure definition for doubly linked list nodes and 
*               function prototypes for addition, subtraction, multiplication, and division of large numbers.
*               Also includes helper functions to insert data into lists and compare two large numbers.
*******************************************************************************************************************************************************************/
#ifndef APC_H
#define APC_H
#define SUCCESS 0
#define FAILURE -1

typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;

/* Include the prototypes here */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,int printf_flag);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR);


// own defined functions
int insert_data_first(Dlist **head, Dlist **tail, char* argv);
int compare_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2);

#endif
