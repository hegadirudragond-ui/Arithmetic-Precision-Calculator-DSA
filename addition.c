/*******************************************************************************************************************************************************************
*Name			: Rudragond Hegadi
*Date			: 7/12/2025
*file			: addition.c
*Title			: Addition
*Description	: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
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

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    /* initialize carry and sum */
    int carry = 0, sum;

    /* point to last digits of both lists */
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    /* loop until both lists and carry are processed */
    while (temp1 != NULL || temp2 != NULL)
    {
        /* start sum with carry */
        sum = carry;

        /* add both digits if present */
        if (temp1 != NULL && temp2 != NULL)
            sum += temp1->data + temp2->data;

        /* add only list1 digit */
        else if (temp1 != NULL && temp2 == NULL)
            sum += temp1->data;

        /* add only list2 digit */
        else if (temp2 != NULL && temp1 == NULL)
            sum += temp2->data;

        /* check for carry generation */
        if (sum > 9)
        {
            carry = 1;
            sum = sum % 10;     /* extract single digit */
        }
        else
        {
            carry = 0;
        }

        /* create new result node */
        Dlist *newnode = malloc(sizeof(Dlist));
        if (newnode == NULL)
        {
            printf("Memory not allocated.\n");
            return FAILURE;
        }

        /* store sum digit */
        newnode->data = sum;
        newnode->prev = NULL;
        newnode->next = *headR;

        /* if result not empty, link back pointer */
        if (*headR != NULL)
            (*headR)->prev = newnode;

        /* update head of result */
        *headR = newnode;

        /* move pointers backward */
        if (temp1 != NULL)
            temp1 = temp1->prev;
        if (temp2 != NULL)
            temp2 = temp2->prev;
    }

    /* if carry remains, insert at beginning */
    if (carry == 1)
    {
        Dlist *newnode = malloc(sizeof(Dlist));
        if (newnode == NULL)
        {
            printf("memory not allocated...\n");
            return FAILURE;
        }

        newnode->data = carry;
        newnode->prev = NULL;
        newnode->next = *headR;

        if (*headR != NULL)
            (*headR)->prev = newnode;

        *headR = newnode;
    }

    /* print the final result */
    Dlist *tempR = *headR;
    printf("Result = ");
    while (tempR != NULL)
    {
        printf("%d ", tempR->data);
        tempR = tempR->next;
    }
    printf("\n");

    return SUCCESS;
}
