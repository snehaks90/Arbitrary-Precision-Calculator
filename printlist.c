#include "header.h"

void print_list(Dlist *head)
{
	/* Cheking the list is empty or not */
	/*if (head == NULL)
	{
		printf("0");
		return;
	}*/   //optional
	   
	while (head != NULL)		
   { 	   
	 printf("%d", head -> data);
     head = head -> next;	   
   }
   printf("\n");
		
}
