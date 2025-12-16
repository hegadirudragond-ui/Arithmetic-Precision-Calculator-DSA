
/*******************************************************************************************************************************************************************
*Name                   : Rudragond Hegadi
*Date                   : 7/12/2025
*File                   : division.c
*Title                  : Division
*Description            : This function performs division of two large numbers using double linked lists.
*******************************************************************************************************************************************************************/

#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

// Remove all leading zeros from the number list
void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    // loop to remove starting zeros
    while (*head != NULL && (*head)->data == 0 && (*head)->next != NULL)
    {
        // store current head
        Dlist *temp = *head;

        // move head to next node
        *head = (*head)->next;

        // new head prev becomes NULL
        (*head)->prev = NULL;

        // delete old head node
        free(temp);
    }

    // set tail to head (start)
    *tail = *head;

    // find the last node to update tail
    if (*tail != NULL)
    {
        // move till last node
        while ((*tail)->next)
            *tail = (*tail)->next;
    }
}

// Compare two numbers stored in DLL
int compare(Dlist *head1, Dlist *head2)
{
    // length counters
    int len1 = 0, len2 = 0;

    // temp pointers
    Dlist *temp1 = head1, *temp2 = head2;

    // count digits of first number
    while (temp1 != NULL)
    {
        len1++;              // increase count
        temp1 = temp1->next; // move next
    }

    // count digits of second number
    while (temp2 != NULL)
    {
        len2++;              // increase count
        temp2 = temp2->next; // move next
    }

    // compare lengths first
    if (len1 < len2) return -1; // first smaller
    if (len1 > len2) return 1;  // first bigger

    // same length → compare digit by digit
    temp1 = head1;
    temp2 = head2;

    // loop through digits
    while (temp1 != NULL && temp2 != NULL)
    {
        // compare digits
        if (temp1->data < temp2->data) return -1;
        if (temp1->data > temp2->data) return 1;

        // move next
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    // both same
    return 0;
}


int division(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR)
{
    // check if lists are empty
    if (*head1 == NULL || *head2 == NULL)
        return FAILURE;

    // pointer for divisor check
    Dlist *t = *head2;

    // assume divisor is zero
    int isZero = 1;

    // check each digit of divisor
    while (t)
    {
        if (t->data != 0)
        {
            isZero = 0; // divisor not zero
            break;
        }
        t = t->next; // move next
    }

    // error if divisor is zero
    if (isZero)
    {
        printf("Error: Division by zero!\n");
        return FAILURE;
    }

    // store quotient value
    int quotient = 0;

    // loop until dividend becomes smaller than divisor
    while (1)
    {
        // remove extra zeros from dividend
        remove_leading_zeros(head1, tail1);

        // compare dividend and divisor
        int cmp = compare(*head1, *head2);

        // dividend < divisor → stop
        if (cmp == -1)
            break;

        // dividend == divisor
        if (cmp == 0)
        {
            quotient++; // add 1 to quotient

            // create new node = 0 (dividend becomes zero)
            Dlist *newnode = malloc(sizeof(Dlist));
            newnode->data = 0;
            newnode->next = newnode->prev = NULL;

            // update dividend to 0
            *head1 = newnode;
            *tail1 = newnode;

            break;
        }

        // new head pointer after subtraction
        Dlist *new_head = NULL;

        // subtract divisor once
        subtraction(head1, tail1, head2, tail2, &new_head, 0);

        // update dividend list
        *head1 = new_head;

        // remove zeros again
        remove_leading_zeros(head1, tail1);

        // increase quotient count
        quotient++;
    }

    // if quotient is 0 → store 0 in result list
    if (quotient == 0)
    {
        // create node with value 0
        Dlist *node = malloc(sizeof(Dlist));
        node->data = 0;
        node->prev = node->next = NULL;

        // quotient list head
        *headR = node;

        printf("Result: 0\n");
        return SUCCESS;
    }

    // start quotient list
    *headR = NULL;

    // tail pointer for quotient digits
    Dlist *tailR = NULL;

    // convert quotient integer to DLL
    while (quotient > 0)
    {
        // get last digit
        int digit = quotient % 10;

        // create new digit node
        Dlist *newnode = malloc(sizeof(Dlist));
        newnode->data = digit;
        newnode->prev = NULL;
        newnode->next = *headR;

        // adjust links
        if (*headR != NULL)
            (*headR)->prev = newnode;
        else
            tailR = newnode;

        // set new head
        *headR = newnode;

        // remove last digit
        quotient /= 10;
    }

    // print result
    printf("Result: ");

    // temp pointer to print
    Dlist *tmpR = *headR;

    // traverse and print each digit
    while (tmpR != NULL)
    {
        printf("%d", tmpR->data); // print digit
        tmpR = tmpR->next;        // move next
    }
    printf("\n");

    return SUCCESS;
}
