#include "life.h"

int main()  //  Program to play Conway's game of Life.
/*
Pre:  The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print(), and update().
      The functions  instructions(),  user_says_yes().
*/

{
   int rows = 0, cols = 0;
   Life configuration;
   instructions();
   askValue(rows, cols);
   // cols = askValue();
   int** arr = allocate_grid(rows, cols);
   configuration.initialize(arr, rows, cols);
   configuration.print(rows, cols);
   std::cout << "Continue viewing new generations? " <<std::endl;
   while (user_says_yes()) {
      configuration.update(rows,cols);
      configuration.print(rows,cols);
      std::cout << "Continue viewing new generations? " << std::endl;
   }
   return 0;
}
