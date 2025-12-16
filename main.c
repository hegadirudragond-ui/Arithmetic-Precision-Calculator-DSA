/**************************************************************************************************************************************************************
*Name 			: Rudragond hegadi
*Date 			: 7/12/2025
* File name		: main.c
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
#include "apc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int main(int argc, char* argv[])
// {
// 	/* Declare the pointers */
	
// 	char option, operator;
// 	if(argc == 4)
// 	{
// 		if(strcmp(argv[2],"+")==0)
// 		{
// 			operator = '+';
// 		}
// 		else if(strcmp(argv[2],"-")==0)
// 		{
// 			operator = '-';
// 		}
// 		else if(strcmp(argv[2],"x")==0 || strcmp(argv[2],"X")==0 )
// 		{
// 			operator = '*';
// 		}
// 		else if(strcmp(argv[2],"/")==0)
// 		{
// 			operator = '/';
// 		}
// 		else
// 		{
// 			printf("Invalid Operator...\n");
// 			return FAILURE;
// 		}
// 	}
// 	else
// 	{
// 		printf("Invalid commands...\n");
// 		return FAILURE;
// 	}

// 	do
// 	{
// 		Dlist *head1=NULL, *tail1=NULL, *head2=NULL, *tail2=NULL, *headR=NULL, *tailR=NULL;
// 		/* Code for reading the inputs */

// 		/* Function for extracting the operator */

// 		switch (operator)
// 		{
// 			case '+':
// 				/* call the function to perform the addition operation */	
// 				insert_data_first(&head1, &tail1, argv[1]);
// 				insert_data_first(&head2, &tail2, argv[3]);
// 				addition(&head1,&tail1,&head2,&tail2,&headR);
// 				break;
// 			case '-':
// 				/* call the function to perform the subtraction operation */	
// 				insert_data_first(&head1, &tail1, argv[1]);
// 				insert_data_first(&head2, &tail2, argv[3]);
// 				subtraction(&head1,&tail1,&head2,&tail2,&headR,1);
// 				break;
// 			case '*':	
// 				/* call the function to perform the multiplication operation */
// 				insert_data_first(&head1, &tail1, argv[1]);
// 				insert_data_first(&head2, &tail2, argv[3]);
// 				multiplication(&head1,&tail1,&head2,&tail2,&headR,&tailR);
// 				break;
// 			case '/':	
// 				/* call the function to perform the division operation */
// 				insert_data_first(&head1, &tail1, argv[1]);
// 				insert_data_first(&head2, &tail2, argv[3]);
// 				division(&head1,&tail1,&head2,&tail2,&headR);
// 				break;
// 			default:
// 				printf("Invalid Input:-( Try again...\n");
// 		}
// 		printf("Want to continue? Press [yY | nN]: ");
// 		scanf("\n%c", &option);
// 	}while (option == 'y' || option == 'Y');

// 	return 0;
// }

// // own defined functions operations
// int insert_data_first(Dlist **head, Dlist **tail, char* argv)
// {
// 	int data;
// 	for (int i = strlen(argv) - 1; i >= 0; i--) 
// 	{
// 		data = argv[i] - '0';

// 		Dlist *new = malloc(sizeof(Dlist));

// 		new->data = data;
// 		new->prev= NULL;
// 		new->next= NULL;
// 		if(new==NULL)
// 		{
// 			printf("Memory NOt allocated.\n");
// 			return FAILURE;
// 		}
		
// 		if(*head == NULL)
// 		{
// 			*head=new;
// 			*tail=new;
// 		}
// 		else
// 		{
// 			new->next = *head;
// 			(*head)->prev = new;
// 			*head = new;
// 		}
// 	}
// 	// return SUCCESS;
// 	Dlist *temp = *head;
// 	while(temp!=NULL)
// 	{
		
// 		printf("%d ",temp->data);
// 		temp=temp->next;

// 	}
// 	printf("\n");
// 	return SUCCESS;
// }


int main(int argc, char* argv[])
{
    /* declare option and operator */
    char option, operator;

    /* check number of arguments */
    if (argc == 4)
    {
        /* check for + operator */
        if (strcmp(argv[2], "+") == 0)
            operator = '+';

        /* check for - operator */
        else if (strcmp(argv[2], "-") == 0)
            operator = '-';

        /* check for x or X operator */
        else if (strcmp(argv[2], "x") == 0 || strcmp(argv[2], "X") == 0)
            operator = '*';

        /* check for / operator */
        else if (strcmp(argv[2], "/") == 0)
            operator = '/';

        /* invalid operator */
        else
        {
            printf("Invalid Operator...\n");
            return FAILURE;
        }
    }
    else
    {
        /* invalid command count */
        printf("Invalid commands...\n");
        return FAILURE;
    }

    /* loop for repeat operations */
    do
    {
        /* declare all list pointers */
        Dlist *head1 = NULL, *tail1 = NULL;
        Dlist *head2 = NULL, *tail2 = NULL;
        Dlist *headR = NULL, *tailR = NULL;

        /* switch based on operator */
        switch (operator)
        {
            case '+':
                /* store first number in list1 */
                insert_data_first(&head1, &tail1, argv[1]);
                /* store second number in list2 */
                insert_data_first(&head2, &tail2, argv[3]);
                /* call addition function */
                addition(&head1, &tail1, &head2, &tail2, &headR);
                break;

            case '-':
                /* store numbers */
                insert_data_first(&head1, &tail1, argv[1]);
                insert_data_first(&head2, &tail2, argv[3]);
                /* perform subtraction and print result */
                subtraction(&head1, &tail1, &head2, &tail2, &headR, 1);
                break;

            case '*':
                /* store numbers */
                insert_data_first(&head1, &tail1, argv[1]);
                insert_data_first(&head2, &tail2, argv[3]);
                /* perform multiplication */
                multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                break;

            case '/':
                /* store numbers */
                insert_data_first(&head1, &tail1, argv[1]);
                insert_data_first(&head2, &tail2, argv[3]);
                /* perform division */
                division(&head1, &tail1, &head2, &tail2, &headR);
                break;

            default:
                /* invalid operator case */
                printf("Invalid Input:-( Try again...\n");
        }

        /* ask user for continuation */
        printf("Want to continue? Press [yY | nN]: ");
        scanf("\n%c", &option);

    } while (option == 'y' || option == 'Y');

    return 0;
}

/* own defined function: insert digits from string into DLL */
int insert_data_first(Dlist **head, Dlist **tail, char* argv)
{
    /* temporary variable for digit */
    int data;

    /* iterate from last character to first */
    for (int i = strlen(argv) - 1; i >= 0; i--)
    {
        /* convert char digit to int */
        data = argv[i] - '0';

        /* allocate new node */
        Dlist *new = malloc(sizeof(Dlist));

        /* assign data */
        new->data = data;
        new->prev = NULL;
        new->next = NULL;

        /* check for allocation failure */
        if (new == NULL)
        {
            printf("Memory not allocated.\n");
            return FAILURE;
        }

        /* if list empty, first node */
        if (*head == NULL)
        {
            *head = new;
            *tail = new;
        }
        else
        {
            /* insert node at beginning */
            new->next = *head;
            (*head)->prev = new;
            *head = new;
        }
    }

    /* print stored number for confirmation */
    Dlist *temp = *head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    return SUCCESS;
}