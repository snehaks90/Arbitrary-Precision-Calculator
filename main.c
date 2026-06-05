#include<stdio.h>
#include<ctype.h>
#include<string.h>

#include "header.h"


int main(int argc, char *argv[])
{ 
    // validations
    if(argc != 4)
    {
        printf("Error: Insufficient arguments\n");
        return 0;
    }
   
    if(isInteger(argv[1]) == 0)  //checking argv[1] is a number
    {
        printf("First operand is not  a number\n");
        return 0;
    }
    if(isInteger(argv[3]) == 0)
    {
        printf("Second operand is not  a number\n");
        return 0;
    }

    if((argv[2][0] != '+' &&  argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != 'X' && argv[2][0] !=  '/' )|| (strlen(argv[2]) != 1))
    {
      printf("Error: Invalid operator\n");
      return 0;
    }
   
    


    Dlist *head1 = NULL; //initialize the header to NULL
	Dlist *tail1 = NULL; //initialize the tail to NULL
     
    Dlist *head2 = NULL; 
	Dlist *tail2 = NULL; 

     Dlist *res_head = NULL;
    Dlist *res_tail = NULL;

    char *num1 = argv[1];  //store first operand to character array num1
    char op = argv[2][0];  // stores operator
    char *num2 = argv[3];  //store 2nd operand to character array num1

    int sign1 = 1, sign2 = 1;

    // ----------- SIGN EXTRACTION START -----------
    //for num1
    if(num1[0] == '-')
    {
        sign1 = -1;
        num1++;   // skip '-' before storing to list
    }
    else if(num1[0] == '+')
    {
        sign1 = 1;
        num1++;    // skip '+' 
    }
    //for num2
    if(num2[0] == '-')
    {
        sign2 = -1;
        num2++;
    }
    else if(num2[0] == '+')
    {
        sign2 = 1;
        num2++;
    }


    int digit, i = 0;

    // Store first number
    while(num1[i] != '\0')
    {  
        digit = num1[i] - '0';
        dl_insert_last(&head1, &tail1, digit);
        i++;
    }

    i = 0;         // Store second number
    while(num2[i] != '\0')
    {  
        digit = num2[i] - '0';
        dl_insert_last(&head2, &tail2, digit);
        i++;
    }

    leading_zero(&head1);
    leading_zero(&head2);
   
  switch(op)
  {
    case '+':
         
      if(sign1 == sign2)            // Same sign → normal addition
      {
          if(addition(&head1, &tail1, &head2, &tail2, &res_head, &res_tail) == SUCCESS)
         {  
            if(sign1 == -1) 
              printf("-");

            print_list(res_head);
         }
          else
         {
             printf("Addition failed\n");
         }
         
     }
     else  
     {       
        subtraction(&head1, &tail1, &head2, &tail2, &res_head, &res_tail);
        if(sign1 == -1)
        printf("-");
        print_list(res_head);
     }
     
    break;


    
   case '-':
    if(sign1 == sign2)  // Both positive or both negative
    {   
        int cmp = compare_sub(&head1, &head2);
        
        if(subtraction(&head1, &tail1, &head2, &tail2, &res_head, &res_tail) == SUCCESS)
        {  
            // For same signs: 
            // If both positive: result sign depends on comparison
            // If both negative: result sign is opposite of comparison
            
            if(sign1 == 1)  // Both positive: (+a) - (+b)
            {
                if(cmp == 2)  // a < b, so result is negative
                    printf("-");
            }
            else  // Both negative: (-a) - (-b) = -a + b = b - a
            {
                if(cmp == 1)  // a > b, so -(a-b) is negative
                    printf("-");
                // if cmp == 2, a < b, so -(a-b) = b-a is positive
            }
        }
        print_list(res_head);
    }
    else if(sign1 == 1 && sign2 == -1)  // (+a) - (-b) = a + b (positive)
    {       
        addition(&head1, &tail1, &head2, &tail2, &res_head, &res_tail);
        print_list(res_head);
    }
    else if(sign1 == -1 && sign2 == 1)  // (-a) - (+b) = -(a + b) (negative)
    {
        addition(&head1, &tail1, &head2, &tail2, &res_head, &res_tail);
        printf("-");
        print_list(res_head);
    }
    break;

    case 'x':
    case 'X':
            
               int result_sign = 1;
               if(sign1 != sign2)
               result_sign = -1;

           if(multiplication(&head1, &tail1, &head2, &tail2, &res_head, &res_tail) == SUCCESS)
           {    
            // Check if result is zero (single digit 0)
              int is_zero = (res_head->data == 0 && res_head->next == NULL);

               if (result_sign == -1 && !is_zero)
               printf("-");
               print_list(res_head);
           }
           else
           {
               printf("Multiplication failed\n");
           }
           break;

     case '/':
              result_sign = 1;
               if(sign1 != sign2)
               result_sign = -1;
             if(division(&head1, &tail1, &head2, &tail2, &res_head, &res_tail) == SUCCESS)
             {   
                int is_zero = (res_head->data == 0 && res_head->next == NULL);

               if (result_sign == -1 && !is_zero)
               printf("-");
               print_list(res_head);
             }
             break;
     
     default:
              printf("Invalid operator\n");
            
}
}





int leading_zero(Dlist **head)
{  
   Dlist *temp;

    while((*head)->next != NULL)
    {
        temp = *head;
       if(temp->data != 0)
       break;
       
       if(temp->data == 0)
       {
        *head = temp->next;
        (*head)->prev = NULL;
        free(temp);
       }
    }
   
   //  temp->prev = NULL;
    return  SUCCESS;
}





int isInteger(char *str)
{
    int i = 0;

    // If first character is '-', allow it
    if(str[i] == '-' || str[i] == '+')
        i++;

    while(str[i] != '\0')
    {
        if(isdigit(str[i]) == 0)
         {
            return 0;
         }
        i++;
    }
    return 1;
}
 