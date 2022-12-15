/*
ATM simulation by: Cirlg
Features:   multiple accounts & account handling
            username and password restrictions
            string counter
            number checker
platform:   Linux/Onlinegdb
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void reg();// registration function
void dep();//deposit function
void wit();//withdraw function
void bal();//balance function
void login();//log in function
int strctr(char array[]); //string checker function
int numcheck(char array[]); // number checker function
void transactions(); // transaction function

struct addbook // struct for creating multiple accounts as well to handle those accounts
{
	char user[20];
	char pin[6];
	int bal;
}; struct addbook accounts[50];

int acc_counter = 0,acc_tracker; /* acc_counter is for counting the account 
and acc tracker is for tracking the account in log in for account handling*/

void main()
{
  int choice; // variable for choosing between log in and register
    while(1)
  {
    system("clear");
    printf("\t\t\t\t\t\tBANKING SYSTEM SIMULATION PROGRAM\n\n");

    printf("\t\t\t\t\t\t\t[1] -  REGISTER\n");
    printf("\t\t\t\t\t\t\t[2] -  LOG IN\n");
    printf("\t\t\t\t\t\t\tANY NUMBER - EXIT\n\n\n");
    printf("\t\t\t\t\t\t Enter here: ");
    scanf(" %d", &choice);
    
    switch (choice) // switch for handling the function for redirecting between functions
    {
    case 1: reg();break;
    case 2: login();break;
    default: exit(0);
    }
  }
}


void reg()
{
  int usr_cnt, pin_cnt, pin_check,reg_check;
  if(acc_counter > 50) /* if the accounts that are registered has exceeded 50, 
  it means the accounts array has been full and cant handle any more accounts*/
  {
    printf("This device has reached maximun accounts, please contact the administrator(Cirlg)");
    return;
  }
  while (1) //used infinite while loop for easier looping
  {
      system("clear");
      printf("\t\t\t\t\t\tWELCOME TO THE REGISTRATION PAGE\n\n");
	  printf("\t\t\t\t\t-- please enter a username, max letters[20] --\n\n");
	  printf("\t\t\tUsername: ");
	  scanf("%s", accounts[acc_counter].user);
	  usr_cnt = strctr(accounts[acc_counter].user); // here, the usr_cnt have the value of the counts of the string in accounts[acc_counter].user
	  if(usr_cnt > 20) //username restriction if it exceeds 20
          {
            printf("\n\n\t\t\tInput exceeds the maximum requirements, Please try again\n\n");
            sleep(2);
            continue;
          }
          /*a loop for scanning all the usernames
          stored in the account array.
          'i' will have the value of acc_counter-1
          acc_counter is subtracted by 1 because the array index starts with 0*/
          for(int i = acc_counter-1; i>=0 ; i--) 
          {
            reg_check = 1; //used to break the infinite while loop
            if(acc_counter == 0) // if there are no accounts, there is no need to use this loop, thus i used break
              break;
            else if(strcmp(accounts[acc_counter].user, accounts[i].user) == 0) //comparing the inputted usernames to the usernames in accounts array
            {
              reg_check = 0; //if the inputted username match,regheck will become 0 and thus the while loop will continue
              printf("\n\n\t\t\tUsername has already been registered, please try again");
              // sometimes the output of printf goes into a large buffer and the sleep will be called first before printf
              //thats why i used fflush to flush the buffer
              fflush(stdout);
              sleep(2);
              break;
            }
            else if(!(accounts[i].user)) //blank elements in an array will be given a null/0 value of the memory
              break; // thus this statement will stop the loop if there are no registered usernames to compare
          }
          if(reg_check) // and this is the statement that uses the reg_check to stop the while loop
            break;
  }
  while (1) // while loop for inputting pin
  {	
	  printf("\n\n\t\t\t\t\t    -- please enter a six digits pin --\n\n");
	  printf("\t\t\tPin: ");
	  scanf("%s", accounts[acc_counter].pin); //i used string to scan the pin because it is possible that the pin starts with 0
	  pin_cnt = strctr(accounts[acc_counter].pin); // i stored the counts of the string in pin_cnt
	  pin_check = numcheck(accounts[acc_counter].pin); // i stored the return value (0/1) of numcheck
          if(pin_cnt != 6 || pin_check == 0) // and if pincount is not equal to 6 and pincheck is equal to false/0
          {
            printf("\n\n\t\t\t\t   Input didn't meet the requirements, Please try again\n\n");
            sleep(2);
            system("clear");
            printf("\t\t\t\t\t\tWELCOME TO THE REGISTRATION PAGE\n\n");
    	    printf("\t\t\t\t\t-- please enter a username, max letters[20] --\n\n");
    	    printf("\t\t\tUsername: %s\n", accounts[acc_counter].user);
          }
          else
            break;
  }
  accounts[acc_counter].bal = 0; // i initialized 0 to account balance here, because I cant initialized it in the struct
  acc_counter++; //here the account counter is being incremented after each registration

  printf("\n\n\t\t\t\t\t      Thank you for your registration.");
  fflush(stdout);
  sleep(2);
  system("clear");
}


void login()
{
  system("clear");
  char user[20],pin[6], choice, stop = 1;
  
  if(acc_counter == 0) // if there are no accounts
  {
  printf("\n\n\n\t\t\t\t\t\tthere are 0 accounts registered");
  fflush(stdout);
  sleep(2);
  return;
  }
  while(stop)
  {
    system("clear");
    printf("\t\t\t\t\t\t\t\tLOG IN\n\n");
    printf("\n\n\t\t\tUsername: ");
    scanf(" %s", user); //I didnt use ampersand because the pointer of string automatically points at its first element
    for(int i = acc_counter-1;i>=0 ; i--) //same as the loop in the register function
      {
        if(strcmp(user, accounts[i].user) == 0)
        {
        acc_tracker = i; //this account tracker is for tracking the account to modify only its variables
        stop = 0; // this is to break the while loop
        break;
        }
        else if(i == 0) //if it scanned all the accounts and cant still find any matching usernames
        {
        printf("\n\n\t\t\tWe cant find that username in the accounts, please try again or register.");
        printf("\n\t\t\tTo go back, enter [b] button");
        printf("\n\t\t\tTo try again, enter any button\n");
        printf("\n\t\t\tENTER HERE: ");
        scanf(" %c",&choice);
        if(choice == 'b')
        return;
        }
        if(i == 0 && acc_counter == 50)
          break;
      }
   }
  while(1)
  {
    printf("\n\n\t\t\tPin: "); //no need to use a for loop in pin, because of the account tracker
    scanf(" %s", pin);
    if(strcmp(pin, accounts[acc_tracker].pin) == 0) //if pin match with the username
    {
      transactions(); 
    }
    else
    {
      printf("\n\n\t\t\tWrong PIN, please try again or register.");
      printf("\n\t\t\tTo go back, press [b] button");
      printf("\n\t\t\tTo try again, press any button");
      printf("\n\t\t\tENTER HERE: ");
      scanf(" %c",&choice);
      if(choice == 'b')
        return;
      system("clear");
      printf("\t\t\t\t\t\t\t\tLOG IN\n\n");
      printf("\n\n\t\t\tUsername: %s\n", accounts[acc_tracker].user);
    }
  }
}


void transactions()
{
  int trans;
  while(1)
  {        
    system("clear");
    printf("\n\n\t\tWELCOME@%s\n\n\t\t\t\t\t\t\tTRANSACTIONS\n\n", accounts[acc_tracker].user); 
    printf("\n\n\t\t\tINPUT [1] -  DEPOSIT\n");
    printf("\t\t\tINPUT [2] -  WITHDRAW\n");
    printf("\t\t\tINPUT [3] -  BALANCE\n");
    printf("\t\t\tINPUT [4] -  LOG OUT\n");
    printf("\t\t\tANY NUMBER  -  EXIT\n");
    printf("\t\t\tEnter desired transaction: ");
    scanf(" %d", &trans);
    
    switch (trans) //used switch to redirect to functions
    {
    case 1: dep();break;
    case 2: wit();break;
    case 3: bal();break;
    case 4: main();break;
    default: exit(0);
    }
    
  }
}

void bal()
{
    char choice;
    system("clear");
    printf("\n\n\t\tWELCOME@%s", accounts[acc_tracker].user);
    printf("\n\n\n\t\t\t\t\t\tyour current balance is: %d", accounts[acc_tracker].bal); 
    fflush(stdout);
    sleep(2);
    printf("\n\n\n\t\t\t\t\t\t enter [b] to go back and any key to exit: ");
    scanf(" %c", &choice);
    if(choice == 'b')
        transactions();
    else
        exit(0);
}

void dep()
{
  char choice, dep[10];
  int checker;
  while(1)
  {
    system("clear");
    printf("\n\n\t\tWELCOME@%s\n\n\n", accounts[acc_tracker].user);
    printf("\t\t\t\t\t\t\t\tDEPOSIT\n\n");
    printf("\t\t\t\tEnter amount to deposit: ");
    scanf(" %s", dep); /*i used string because the user might enter characters and characters will be stored as a number(binary) in int*/
    checker = numcheck(dep); //used checker to get the return value of numcheck
    if(!(checker)) //if checker is false
    {
    printf("\n\n\t\t\t\tERROR: --deposit error, please try again");
    fflush(stdout);
    sleep(2);
    continue;
    }
    else //if checker is true
        accounts[acc_tracker].bal = atoi(dep); // input will be converted to int and will be stored in accounts[acc_tracker].bal
    if(accounts[acc_tracker].bal > 0) //and if the input is greater than 0
    {
    printf("\n\n\t\t\t\tDeposit success, enter [b] to go back and any key to exit: ");
    scanf(" %c", &choice);
    if(choice == 'b')
      transactions();
    else
      exit(0);
    }
    else
    {
      printf("\n\n\t\t\t\tERROR: --deposit error, please try again");
      fflush(stdout);
      sleep(2);
      continue;
    }
    }
}


void wit()
{
  char withdraw [10];
  int checker, withconvert;
  if(accounts[acc_tracker].bal == 0)
  {
    system("clear");
    printf("\n\n\n\t\t\t\t\t\tThis account have 0 balance, Please deposit");
    fflush(stdout);
    sleep(2);
    system("clear");
    transactions();
  }
  while(1)
  {
     /*many codes are same as dep() function*/
    system("clear");
    printf("\n\n\t\tWELCOME@%s\n\n\n", accounts[acc_tracker].user);
    printf("\t\t\tEnter amount to withdraw: ");
    scanf(" %s", withdraw);
    checker = numcheck(withdraw);
    if(!(checker))
    {
        printf("\n\n\t\t\t\tERROR: --withdraw error, please try again");
        fflush(stdout);
        sleep(2);
        continue;
    }
    else
        withconvert = atoi(withdraw);
    if(withconvert > accounts[acc_tracker].bal || withconvert <1) //if input is greater than account balance or input is smaller than 1
    {
        printf("\n\n\t\t\t\tERROR: --withdraw error, please try again");
        fflush(stdout);
        sleep(2);
        continue;
    }
    else
    {
        accounts[acc_tracker].bal -= withconvert; //account balance will be subtracted by input
        printf("\n\n\t\t\t\tOPERATION SUCCESS\n\t\t\t\tPlease wait for a few seconds..........");
        fflush(stdout);
        sleep(3);
        transactions();
    }
  
  }
  
}



int strctr(char array[]) //the string counter function
{
    //if the element of the array is null/0 the loop will stop and return how many times the loop occurs
  int ctr = 0;
  while(1)
  {
    ctr++;
    if(!(array[ctr]))
    break;
  }
  return ctr;
}


int numcheck(char array[])//number checker function
{
  int ctr = 0;
  while(1)
  {
  
  if(!(array[ctr])) //this means all the elemts doesnt have characters
  return 1;
  
  if(!(array[ctr] == '1' || array[ctr] == '2' || array[ctr] == '3' || array[ctr] == '4' || array[ctr] == '5' || array[ctr] == '6' || array[ctr] == '7' || array[ctr] == '8' || array[ctr] == '9' || array[ctr] == '0'))
  {
    //this means the loop have characters
    return 0;
  }
  ctr++;
  }
  
}
