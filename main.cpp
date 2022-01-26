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
   int rows = 0, cols = 0,count=0,sec=2, round=0;
   Life configuration;
   instructions();
   askValue(rows, cols);
   // cols = askValue();
   int** arr = allocate_grid(rows, cols);
   configuration.initialize(arr, rows, cols);
   configuration.print(rows, cols);
   std::cout << "Continue viewing new generations? " <<std::endl;
   while (user_says_yes()) {
       std::cout << "How many rounds you want to be shown automaticly and" << std::endl;
       std::cout << "How many seconds you want to show one round" << std::endl;
       std::cout << "Input round and secs:" << std::endl;
       std::cin >> round >> sec;
       std::cin.ignore();

       while (count <= round) {
           configuration.update(rows, cols);
           configuration.print(rows, cols);
           std::this_thread::sleep_for(std::chrono::seconds(sec));
           count++;
       }
      count = 0;
      std::cout << "Continue viewing new generations? " << std::endl;
      
   }
   configuration.result_to_file(rows,cols);
   

   return 0;
}
