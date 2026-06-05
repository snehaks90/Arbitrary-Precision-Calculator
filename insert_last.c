#include "header.h"

int dl_insert_last(Dlist **head, Dlist **tail, int data)
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
   else        //if list is not empty
   {
       new->prev = *tail;
       (*tail)->next = new;
       *tail = new;
       return SUCCESS;
   }
   

}