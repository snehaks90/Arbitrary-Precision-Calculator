#include "header.h"
int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
  Dlist *new = malloc(sizeof(Dlist));
    
    if (new == NULL)
	{
		return FAILURE;
	}
   
   new->data = data;
   new->next = NULL;
   new->prev = NULL;
   
   if(*head == NULL)   //if list is empty
   {
       *head = new;
       *tail = new;
       return SUCCESS;
   }
   else   //if list is not empty
   {  
       (*head)->prev = new;
       new->next = *head;
       *head =new;
       return SUCCESS;
   }

}