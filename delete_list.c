#include "header.h"
int dl_delete_list(Dlist **head, Dlist **tail)
{
  //CASE 1- list is empty
   if(*head == NULL)  
       return FAILURE;
      
       Dlist *temp = *head;
    
    //CASE 2- if only 1 node
    if(*head == *tail)  
    {  
        *head = NULL;
        *tail = NULL;
       free(temp); 
       return SUCCESS;
    }
    else           //CASE 3- if more than 1 node
    {
        while(temp != NULL)
        {
            (*head) = temp->next;
            free(temp);
            temp = *head;
        }
        *tail = NULL;
        return SUCCESS;
    }
}