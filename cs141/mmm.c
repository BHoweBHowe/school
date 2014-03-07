/* ----------------------------------------------
 * MiniMasterMind
 *
 * Class: cs 141, Spring 2014, Thur 4pm lab.
 * System: Linux Mint 16 x64, gcc
 * Author: Brian Howe
 *
 * ToDo: Create a game that generates 3 random numbers between 1 and 10. Allow a player to guess
 *       the numbers 10 times. If the player is correct display winning message. If the player
 *       runs out of turns display the losing message.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[])
{
  int h1, h2, h3, ip, op;
  srand((int)time(0)); //seed the random number generator

  //give all hidden numbers a value between 1 and 10
  h1 = rand() % 10;
  h2 = rand() % 10;
  h3 = rand() % 10;

  //if any of the hidden nubers are the same
  while(h1 == h2 || h1 == h3 || h2 == h3)
  {
    //if h1 and h2 are the same
    if(h1 == h2)
    {
      h2 = rand() % 10; //pick new value for h2
    }
    //if h3 is the same as h1 or h2
    if(h1 == h3 || h2 == h3)
    {
      h3 = rand() % 10; //pick new value for h3
    }
  }


  printf("Author: Brina Howe\n");
  printf("Lab: Thur 4pm\n");
  printf("Program: #2, MiniMasterMind\n\n");

  printf("Welcome to MiniMasterMind.\n");
  printf("The program selects 3 distinct random digits 0..9.\n");
  printf("On each turn you guess 3 digits. Program indicates how many are correct.\n");
  printf("You have 10 moves to guess the number. Good luck!\n\n");

  if(argc > 1)
  {
    h1 = argv[1][0] - '0';
    h2 = argv[1][1] - '0';
    h3 = argv[1][2] - '0';
  }

  printf("                                     In place     Out of place\n");
  printf("                                     --------     ------------\n\n");

  int x = 0; //number of guesses
  int guess = 0; //users guess

  do{
    printf("%d. Your guess: ", x+1);
    scanf("%d", &guess); //retreives users guess
    int g1 = guess / 100; //sets g1 to the digit in the hundreds place of guess
    int g2 = (guess / 10) % 10; //sets g2 to the digit in the tens place of guess
    int g3 = guess % 10; //sets g3 to the digit in the ones place of guess

    ip = 0; //number of digits in the correct place
    op = 0; //number of digits in incorrect place

    //if the first digit of guess equals the first hidden number add 1 to ip
    if(g1 == h1)
    {
      ip++;
    }
    //if the value of g1 is equal to any other h than h1 add 1 to op
    else if(g1 == h2 || g1 == h3)
    {
      op++;
    }

    //if the second digit of guess equals the second hidden number add 1 to ip
    if(g2 == h2)
    {
      ip++;
    }
    //if the value of g2 is equal to any other h than h2 add 1 to op
    else if(g2 == h1 || g2 == h3)
    {
      op++;
    }

    //if the third digit of guess equals the third hidden number add 1 to ip
    if(g3 == h3)
    {
      ip++;
    }
    //if the of g3 is equal to any other h than h3 add 1 to op
    else if(g3 == h1 || g3 == h2)
    {
      op++;
    }

    //if the guess starts with a 0 the 0 dosnt show up. This fixes it
    if(g1 == 0)
    {
      printf("        You entered: 0%d%d                   %d                %d\n",
            g2, g3, ip, op);
    }
    else
    {
      printf("        You entered: %d%d%d                   %d                %d\n",
            g1, g2, g3, ip, op);

    }

    x++; //add 1 to turn number

  }while(ip < 3 && x < 10); //loop ends after 10 turns or if the users guess is correct

  //if the users guess was correct
  if(ip == 3)
  {
    printf("*** Congradulations! You did it! ***\n\n");
  }
  //if the user ranout of turns
  else
  {
    printf("Better luck next time. Answer was %d%d%d\n\n",
        h1, h2, h3);
  }

  printf("Thank you for playing. Exiting...\n");

  return 0;
}
