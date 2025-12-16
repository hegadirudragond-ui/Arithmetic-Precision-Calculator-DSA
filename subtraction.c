/*******************************************************************************************************************************************************************
*Name			: Rudragond Hegadi
*Date			: 7/12/2025
*file			: substraction.c
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, int printf_flag)
{
    // initialize result head as NULL
    *headR = NULL;

    // compare the two lists to know which is bigger
    int cmp = compare_list(head1, tail1, head2, tail2);

    // borrow flag and difference variable
    int barrow = 0, differ;

    // pointers to traverse from last digit
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    // values of current nodes
    int value1, value2;

    // loop until both lists are fully processed
    while (temp1 != NULL || temp2 != NULL)
    {
        // if list1 > list2
        if (cmp == 1)
        {
            // get temp1 value or 0 if null
            value1 = (temp1 != NULL) ? temp1->data : 0;

            // get temp2 value or 0 if null
            value2 = (temp2 != NULL) ? temp2->data : 0;
        }
        // if list2 > list1
        else if (cmp == -1)
        {
            // swap roles for subtraction
            value1 = (temp2 != NULL) ? temp2->data : 0;
            value2 = (temp1 != NULL) ? temp1->data : 0;
        }

        // perform subtraction with borrow
        differ = value1 - value2 - barrow;

        // check if borrow needed
        if (differ < 0)
        {
            barrow = 1;
            differ = differ + 10;
        }
        else
        {
            barrow = 0;
        }

        // allocate new node for result
        Dlist *newnode = malloc(sizeof(Dlist));
        if (newnode == NULL)
        {
            printf("Memory not allocated.\n");
            return FAILURE;
        }

        // store digit
        newnode->data = differ;

        // insert at beginning
        newnode->prev = NULL;
        newnode->next = *headR;

        // adjust previous pointer
        if (*headR != NULL)
            (*headR)->prev = newnode;

        // update headR
        *headR = newnode;

        // move temp pointers backward
        if (temp1 != NULL) temp1 = temp1->prev;
        if (temp2 != NULL) temp2 = temp2->prev;
    }

    // print 0 if numbers are equal
    if (cmp == 0)
    {
        printf("Result = 0\n");
        return 1;
    }

    // printing result if flag enabled
    if (printf_flag)
    {
        cmp == 1 ? printf("Result = ") : printf("Result = - ");

        Dlist *tempR = *headR;

        // print each digit
        while (tempR != NULL)
        {
            printf("%d ", tempR->data);
            tempR = tempR->next;
        }
        printf("\n");
    }

    return SUCCESS;
}

int compare_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
    // temp pointers to calculate lengths
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    int len1 = 0, len2 = 0;

    // count length of list 1
    while (temp1 != NULL)
    {
        len1++;
        temp1 = temp1->prev;
    }

    // count length of list 2
    while (temp2 != NULL)
    {
        len2++;
        temp2 = temp2->prev;
    }

    // if lengths differ, larger length means larger number
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    // if lengths equal, compare digits from head
    temp1 = *head1;
    temp2 = *head2;

    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data)
            return 1;

        else if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    // numbers are equal
    return 0;
}