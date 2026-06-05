#include "header.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **res_head, Dlist **res_tail)
{  
  // Create a NEW result list every time  for multplication
    Dlist *temp_res_head = NULL;
    Dlist *temp_res_tail = NULL; 

    // Start from the last digits of both numbers
    Dlist *temp1 = *tail1;  // last digit of number 1
    Dlist *temp2 = *tail2;   // last digit of number 2
   

    int carry = 0;
 /*  
       Continue addition until both lists are fully processed.
       If one list is shorter, remaining digits are treated as 0.
    */

    while(temp1 != NULL || temp2 != NULL)
    {   
      int n1 = 0, n2 = 0;

      // If temp1 is valid, take its digit
       if(temp1 != NULL)
         n1 = temp1->data;
       else                // if list1 is shorter, use 0
        n1 = 0;
      
       if(temp2 != NULL)
         n2 = temp2->data; 
       else
        n2 = 0;

       int num = n1 + n2 + carry;  //add operation
        
       if(num > 9)
       {
        carry = 1;
        num = num % 10;    // keep only the last digit
       }
       else
         carry = 0;

       // dl_insert_first(res_head, res_tail, num);
        dl_insert_first(&temp_res_head, &temp_res_tail, num);

          if(temp1 != NULL)     //move backward
             temp1 = temp1->prev;
          if(temp2 != NULL)
             temp2 = temp2->prev;

     }

     // If carry is left after loop, insert it
     if(carry == 1)
      dl_insert_first(&temp_res_head, &temp_res_tail, carry);

     // Delete old result list if not empty
    dl_delete_list(res_head, res_tail);  // in addition nothing happens beacuse already empty

    // must Store new result
    *res_head = temp_res_head;
    *res_tail = temp_res_tail;

    leading_zero(res_head);

    return SUCCESS;  

    
}

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **res_head, Dlist **res_tail)
{  
   
 if(compare_sub(head1, head2) == 2)  // If num1 < num2 → result will be negative → swap lists
  {  

     Dlist *h = *head1;
     Dlist *t = *tail1;

     *head1 = *head2;
     *tail1 = *tail2;

     *head2 = h;
     *tail2 = t;
  }
   
  // Create a NEW result list every time  for division
    Dlist *temp_res_head = NULL;
    Dlist *temp_res_tail = NULL; 


    // Start from the last digits of both numbers
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
   
    int borrow = 0;

     while(temp1 != NULL || temp2 != NULL)
    {   
      int n1 = 0, n2 = 0, num;

      // If temp1 is valid, take its digit
       if(temp1 != NULL)
         n1 = temp1->data;
       else                // if list1 is shorter, use 0
        n1 = 0;
      
       if(temp2 != NULL)
         n2 = temp2->data; 
       else
        n2 = 0;

    n1 = n1 - borrow;    // Apply previous borrow

    if(n1 < n2)  // If n1 < n2, we borrow from next digit
    {
     n1 = n1 + 10;
     borrow = 1;
    }
    else
    {
    borrow = 0;
    }

   // Actual subtraction digit
   num = n1 - n2;   

   //dl_insert_first(res_head, res_tail, num);
   dl_insert_first(&temp_res_head, &temp_res_tail, num);

    if(temp1 != NULL)     //move backward
         temp1 = temp1->prev;
     if(temp2 != NULL)
          temp2 = temp2->prev;
    }
      
    if(temp_res_head== NULL)
   {
   dl_insert_first(&temp_res_head, &temp_res_tail, 0);
   }

    // Delete old result list
    dl_delete_list(res_head, res_tail);  

  // must Store new result
    *res_head = temp_res_head;
    *res_tail = temp_res_tail;

  leading_zero(res_head);

  return SUCCESS;
}

// ---------------------------------------------------------------------------
// Function to compare two numbers stored as linked lists
// Return: 1 → head1 > head2
//         2 → head1 < head2
//         0 → equal
// ---------------------------------------------------------------------------

int compare_sub(Dlist **head1, Dlist **head2)
{
  int c1 = 0, c2 = 0;

  Dlist *temp1 = *head1;
  Dlist *temp2 = *head2;

  // Count digits in number1
  while(temp1 != NULL)
  {
    c1++;
    temp1 = temp1->next;
  }
  // Count digits in number2
  while(temp2 != NULL)
  {
    c2++;
    temp2 = temp2->next;
  }

// If num1 has more digits → larger
  if(c1 > c2)
    return 1;
  // If num1 has fewer digits → smaller
  else if(c1 < c2)
     return 2;
  
  else if(c1 == c2)  // If same digits, compare digit by digit from MSB
  {  
        temp1 = *head1;
        temp2 = *head2;

   while(temp1 != NULL && temp2 != NULL)
    {
        if(temp1->data > temp2->data)
            return 1;

        else if(temp1->data < temp2->data)
            return 2;

        temp1 = temp1->next;  // Move forward
        temp2 = temp2->next;
    }

    return 0;  // both numbers equal
      
  }
   
}

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **res_head, Dlist **res_tail)
{  

    
    // Clear previous result
    if (*res_head != NULL)
        dl_delete_list(res_head, res_tail);

    // Clear result list
    *res_head = NULL;
    *res_tail = NULL;
    
    // Start from the last digit
    Dlist *temp2 = *tail2;
    int count = 0;

    while(temp2 != NULL)
    { 
       Dlist *temp1 = *tail1;   // reset temp1 for each temp2 digit

       int carry = 0;
      
        // Temporary list for each partial product
       Dlist *temphead = NULL;
       Dlist *temptail = NULL;
     
       //shift zeros
       for(int i = 0; i < count; i++)
       {
         dl_insert_first(&temphead, &temptail, 0);
       }

       // Multiply current row , Multiply current digit of number2 with entire number1
        while(temp1 != NULL)
        {
          int data = (temp1->data * temp2->data) + carry;
          
          if(data > 9)
          {
          carry = data/10;
          data = data % 10;
          }
          else
            carry = 0;
          
             dl_insert_first(&temphead, &temptail, data);
             temp1 = temp1->prev;
        }
        if(carry)
          dl_insert_first(&temphead, &temptail, carry);

        // Add this partial row to result
        addition(res_head,  res_tail, &temphead, &temptail,  res_head, res_tail);

        // Clear partial list
        dl_delete_list(&temphead, &temptail);

        count++;      // increase shift for next row
        temp2 = temp2->prev;   // move to next digit of number2
    }

    
    return SUCCESS;
}
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **res_head, Dlist **res_tail)
{  
      // Division by zero check 
  if (*head2 == NULL || (*head2)->data == 0 && (*head2)->next == NULL)
{
    printf("Error: Division by zero\n");
    return FAILURE;   // Dividing by zero
}

    // If divisor > dividend → result = 0
  if(compare_sub( head1, head2) == 2)
  {
     dl_insert_first(res_head, res_tail, 0);
     return SUCCESS;
  }
   
    *res_head = NULL;
    *res_tail = NULL;
  
// temp storage for subtraction output
   Dlist *temphead = NULL;  //temphead must store subtraction output because temphead is NEW DIVIDEND.
   Dlist *temptail = NULL;

   Dlist * one_h = NULL;
   Dlist * one_t = NULL;
   dl_insert_first(&one_h, &one_t, 1);
 

// Repeat subtraction until dividend < divisor
   while(compare_sub( head1, head2) != 2)
   {  
       // Perform subtraction: dividend = dividend - divisor
       subtraction(head1, tail1, head2, tail2, &temphead, &temptail);

       // Free old dividend before replacing to avoid memory leak
        dl_delete_list(head1, tail1);

       // UPDATE dividend to new value
        *head1 = temphead;
        *tail1 = temptail;

        // Add 1 to quotient
       addition(res_head, res_tail, &one_h , &one_t, res_head, res_tail);
      
       // Reset for next loop
        temphead = NULL;
        temptail = NULL;
   }


return SUCCESS;
}
