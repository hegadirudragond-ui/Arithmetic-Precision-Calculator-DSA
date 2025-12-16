/*******************************************************************************************************************************************************************
*Name			: Rudragond Hegadi
*Date			: 7/12/2025
*file			: multiplication.c
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "apc.h"

int insert_first(Dlist **head, Dlist **tail, int data)
{
    // allocate new node
    Dlist *new = malloc(sizeof(Dlist));

    // check allocation failure
    if (new == NULL)
    {
        return FAILURE;
    }

    // store data
    new->data = data;

    // new node prev = NULL (first node)
    new->prev = NULL;

    // new node next = old head
    new->next = *head;

    // if list not empty, update old head prev
    if (*head != NULL)
    {
        (*head)->prev = new;
    }
    else
    {
        // if first element, tail also new node
        *tail = new;
    }

    // update head
    *head = new;

    return SUCCESS;
}


int insert_last(Dlist **head, Dlist **tail, int data)
{
    // allocate new node
    Dlist *new = malloc(sizeof(Dlist));

    // check allocation failure
    if (new == NULL)
    {
        return FAILURE;
    }

    // store data
    new->data = data;

    // last node next = NULL
    new->next = NULL;

    // new node prev = old tail
    new->prev = *tail;

    // if list not empty, update old tail next
    if (*tail != NULL)
    {
        (*tail)->next = new;
    }
    else
    {
        // if list empty, head becomes new
        *head = new;
    }

    // update tail
    *tail = new;

    return SUCCESS;
}


void free_list(Dlist **head, Dlist **tail)
{
    // start from head
    Dlist *temp = *head;

    // traverse list
    while (temp != NULL)
    {
        // store next pointer
        Dlist *next = temp->next;

        // free current node
        free(temp);

        // move to next
        temp = next;
    }

    // empty list → set to NULL
    *head = NULL;
    *tail = NULL;
}


int addition_mul(Dlist **head1, Dlist **tail1,
                 Dlist **head2, Dlist **tail2,
                 Dlist **headR, Dlist **tailR)
{
    // initialize result list empty
    *headR = NULL;
    *tailR = NULL;

    // pointers to last digits
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    // initial carry = 0
    int carry = 0;

    // loop until both lists + carry end
    while (temp1 != NULL || temp2 != NULL || carry)
    {
        // start with carry
        int sum = carry;

        // add digit from number1
        if (temp1 != NULL)
        {
            sum += temp1->data;
            temp1 = temp1->prev;
        }

        // add digit from number2
        if (temp2 != NULL)
        {
            sum += temp2->data;
            temp2 = temp2->prev;
        }

        // compute new carry
        carry = sum / 10;

        // insert digit at front
        insert_first(headR, tailR, sum % 10);
    }

    return SUCCESS;
}


int multiplication(Dlist **head1, Dlist **tail1,
                   Dlist **head2, Dlist **tail2,
                   Dlist **headR, Dlist **tailR)
{
    // check lists empty
    if (*head1 == NULL || *head2 == NULL)
        return FAILURE;

    // temporary result lists
    Dlist *head_R1 = NULL, *tail_R1 = NULL;
    Dlist *head_R2 = NULL, *tail_R2 = NULL;

    // pointers and variables
    Dlist *temp1, *temp2 = *tail2;
    int carry, count = 0, result, data;

    // if previous result exists, free it
    if (*headR != NULL)
        free_list(headR, tailR);

    // initialize result empty
    *headR = NULL;
    *tailR = NULL;

    // process each digit of number2
    while (temp2)
    {
        // pointer to number1 last digit
        temp1 = *tail1;
        carry = 0;

        // multiply each digit of number1
        while (temp1)
        {
            // multiply digits + carry
            result = (temp1->data * temp2->data) + carry;

            // compute new carry
            carry = result / 10;

            // digit to store
            data = result % 10;

            // insert digit at front
            insert_first(&head_R1, &tail_R1, data);

            // move prev
            temp1 = temp1->prev;
        }

        // leftover carry
        if (carry != 0)
        {
            insert_first(&head_R1, &tail_R1, carry);
        }

        // add trailing zeros based on digit position
        for (int i = 0; i < count; i++)
            insert_last(&head_R1, &tail_R1, 0);

        // if first partial result, copy directly
        if (*headR == NULL)
        {
            *headR = head_R1;
            *tailR = tail_R1;
        }
        else
        {
            // add partial result with existing result
            addition_mul(headR, tailR, &head_R1, &tail_R1, &head_R2, &tail_R2);

            // free old result
            free_list(headR, tailR);

            // update result to new sum
            *headR = head_R2;
            *tailR = tail_R2;

            // reset temporary list
            head_R2 = NULL;
            tail_R2 = NULL;
        }

        // clear partial list
        head_R1 = NULL;
        tail_R1 = NULL;

        // increase trailing zero count
        count++;

        // move to next digit of number2
        temp2 = temp2->prev;
    }

    // print result
    printf("Result = ");

    // pointer to print
    Dlist *tempR = *headR;

    // print digits
    while (tempR)
    {
        printf("%d ", tempR->data);
        tempR = tempR->next;
    }

    printf("\n");

    return SUCCESS;
}
