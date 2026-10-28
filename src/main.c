#include <stdio.h>
#include <inttypes.h>
#include "pc.h"
#include "ram8.h"



typedef enum  {STAY = 1, NEXT, JUMP, RESET} REGISTER_MOVEMENT;
typedef enum  {VALIDATE_REGISTER_MOVEMENT_CHOICE, VALIDATE_REGISTER_JUMP} VALIDATION_ROUTE;

void print_bin16(uint16_t value)
{
    for (int bit = 15; bit >= 0; bit--)
        putchar(((value >> bit) & 1) ? '1' : '0');
}

void print_line(int n)
{
    printf("     +");
   
    for (int character = 0; character < n; character++)
    {
        putchar('_');
    }

    printf("+\n");
}

bool check_user_input(int *input_ptr, VALIDATION_ROUTE route)
{
    int c;  
    
    
    if (scanf("%d", input_ptr) != 1)
    
    {
        
    while (( c = getchar()) != '\n' && c != EOF)
           
             ;
        
             return 0;
    }   

   
    switch(route)
    {
        case VALIDATE_REGISTER_MOVEMENT_CHOICE:
            if (*input_ptr > 4 || *input_ptr < 1)
    
            {
        
                printf("Please enter a number 1-4 for the correct movement: \n");
        
                return 0;
    
            } 
            
            return 1;

        case VALIDATE_REGISTER_JUMP:
            if (*input_ptr > 7 || *input_ptr < 0)
            {
                printf("Please enter a valid register number (0-7): \n");

                return 0;
            }
            return 1;
        default:
            printf("Incorrect value for validation route \n");
            return 0;
    }
}


int main(void)
{ 
   
   RAM8 ram = {0};
   int register_address = 0;
   int choice;
   bool game_loop = 0; 
   bool keep_prompting = 0;
   
   while (!game_loop)
   {

     for (int register_emulated = 0; register_emulated < 8; ++register_emulated)
     {
             print_line(18);  
             printf("R%u:  | ", register_emulated);
             print_bin16(ram.registers[register_emulated]);
             printf(" |");
             printf(register_emulated == register_address ? "<- Currently Selected register\n" : "\n");
             print_line(18);
     }
   
   
      while (!keep_prompting)
      {
           printf("Please select how you would like to move between the registers\n\n");
           printf("SELECT (1 : STAY | 2: NEXT | 3: JUMP | 4 : RESET )\n\n\n");
             
           keep_prompting = check_user_input(&choice, VALIDATE_REGISTER_MOVEMENT_CHOICE);
      }    
      // Set back keep prompting to use in other while loop for user input
      keep_prompting = 0;
      REGISTER_MOVEMENT user_choice = choice;
          
     switch(user_choice)
     {
        case STAY:
            register_address = call_pc(register_address, 0, 0, 0, 0);
            break;
        case NEXT:
            register_address = call_pc(register_address, 0, 0, 0, 1);
            break;
        case JUMP:
            while (!keep_prompting)
            {    
                printf("Please enter the register address you would like to jump to: \n ");
                keep_prompting = check_user_input(&choice, VALIDATE_REGISTER_JUMP);
            }
            keep_prompting = 0;
            register_address = call_pc(register_address, choice, 0, 1, 0 );
            break;
        case RESET:
            register_address = call_pc(register_address, 0, 1, 0, 0); 
            break;
      }  
      
      uint16_t user_number;
      while(!keep_prompting)
      {
            printf("Please enter the value you would like to input at this register: \n ");
            if (scanf("%" SCNu16, &user_number) == 1)
            {
                keep_prompting = 1;
            }
            else
            {
                printf("This value must be able to be represented by 16 bits unsigned \n");
            }
      }
      
      keep_prompting = 0;

      call_ram8(&ram, user_number, register_address, 1);
      
      printf("Updated register value: \n\n\n\n"); 
     
      for (int register_emulated = 0; register_emulated < 8; ++register_emulated)
      {
             print_line(18);  
             printf("R%u:  | ", register_emulated);
             print_bin16(ram.registers[register_emulated]);
             printf(" |");
             printf(register_emulated == register_address ? "<- Currently Selected register\n" : "\n");
             print_line(18);
      }
      
      
      while (!keep_prompting)
      {  
         printf("Would you like to modify another register ? : 1 (yes) | 0 (no) \n");
         scanf("%d", &choice);

         switch (choice)
         {
            case 0:
                keep_prompting = 1;
                game_loop = 1;
                break;
            case 1:
                keep_prompting = 1;
                game_loop = 0;
                break;
            default:
              printf("Please enter a valid value: ");
              break;  


         }
            
      }
      keep_prompting = 0;
   }
}

