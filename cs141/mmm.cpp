/* ----------------------------------------------
 * MiniMasterMind
 *
 * Class: cs 141, Spring 2014, Thur 4pm lab.
 * System: CentOS 6.5 x86, g++
 * Author: Brian Howe
 *
 * ToDo: Create a game that generates 3 random numbers between 1 and 10. Allow a player to guess
 *       the numbers 10 times. If the player is correct display winning message. If the player
 *       runs out of turns display the losing message.
 */

#include <iostream>
#include <stdlib.h>
using namespace std;

void compGuess(int c1, int c2, int c3, int x, int ip)
{
  if(x > 9)
  {
    cout << "Congradulations! The computer didn't guess the number!" << "\n";
  }
  else if(ip > 0 || op > 0)
  {
    int op = 0;

    if(ip == 1 && op == 0)
    {
      if(op == 0)
      {

      }
      else if(op == 1)
      {

      }
      else if(op == 2)
      {

      {
    }
    else if(ip == 2 && op == 0)
    {

    }
  }
  else
  {
    compGuess(c2, c1, c3, x+1, ip);
  }
}

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


  cout << "Author: Brina Howe\n";
  cout << "Lab: Thur 4pm\n";
  cout << "Program: #2, MiniMasterMind\n\n";

  cout << "Welcome to MiniMasterMind.\n";
  cout << "The program selects 3 distinct random digits 0..9.\n";
  cout << "On each turn you guess 3 digits. Program indicates how many are correct.\n";
  cout << "You have 10 moves to guess the number. Good luck!\n\n";

  if(argc > 1)
  {
    h1 = argv[1][0] - '0';
    h2 = argv[1][1] - '0';
    h3 = argv[1][2] - '0';
  }

  cout << "                                     In place     Out of place\n";
  cout << "                                     --------     ------------\n\n";

  int x = 0; //number of guesses
  int guess = 0; //users guess

  do{
    cout << x + 1 << ". Your guess: ";
    cin  >> guess; //retreives users guess
    int g1 = guess / 100; //sets g1 to the digit in the hundreds place of guess
    int g2 = (guess / 10) % 10; //sets g2 to the digit in the tens place of guess
    int g3 = guess % 10; //sets g3 to the digit in the ones place of guess

    ip = 0; //number of digits in the correct place
    op = 0; //number of digits in incorrect place

    //if the first digit of guess equals the first hidden number add 1 to ip
    if(g1 == h1)
    {
      ip++;
      //incase of duplicate input in the users guess
      if(g1 == g2)
      {
        if(g1 == g3)
        {
          op--;
        }
       	op--;
      }
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
      //incase of duplicate input in the users guess
      if(g2 == g1)
      {
        if(g2 == g3)
        {
          op--;
        }
       	op--;
      }

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
      //incase of duplicate input in the users guess
      if(g3 == g1)
      {
        if(g3 == g2)
        {
          op--;
        }
       	op--;
      }
    }
    //if the of g3 is equal to any other h than h3 add 1 to op
    else if(g3 == h1 || g3 == h2)
    {
      op++;
    }

    //if the guess starts with a 0 the 0 dosnt show up. This fixes it
    if(g1 == 0)
    {
      cout << "        You entered: 0" << g2 << g3 << "                   " << ip << "                " << op << "\n";
    }
    else
    {
      cout << "        You entered: " << g1 << g2 << g3 << "                   " << ip << "                " << op << "\n";
    }

    x++; //add 1 to turn number

  }while(ip < 3 && x < 10); //loop ends after 10 turns or if the users guess is correct

  //if the users guess was correct
  if(ip == 3)
  {
    cout << "*** Congradulations! You did it! ***\n\n";
  }
  //if the user ranout of turns
  else
  {
    cout << "Better luck next time. Answer was " << h1 << h2 << h3 << "\n\n";
  }

  compGuess(0, 1, 2, 0, 0);

  cout << "Thank you for playing. Exiting...\n";

  return 0;
}
