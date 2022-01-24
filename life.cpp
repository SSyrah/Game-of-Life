#include "life.h"


int** allocate_grid(int& maxrow, int& maxcol)
{
    int** arr = new int* [maxrow];
    for (int i = 0; i <=maxrow; i++)
        arr[i] = new int[maxcol];
    return arr;  
}

int Life::neighbor_count(int row, int col, int rows, int cols)
/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/

{
   int i, j;
   int count = 0;

   if (row == 1) {
       for (i = row; i <= row + 1; i++) {
           if (col == 1) {
               for (j = col; j <= cols; j++) {
                   count += grid[i][j];
               }
           }
       }
   }
   else if (row == rows) {
       for (i = row; i >= row - 1; i--) {
           if (col == 1) {
               for (j = col; j <= cols; j++) {
                   count += grid[i][j];
               }
           }
       }
   }
   else {
       for (i = row - 1; i <= row + 1; i++)
           for (j = col - 1; j <= col + 1; j++)
               count += grid[i][j];  //  Increase the count if neighbor is alive.
   }
   count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
   return count;
}

void Life::update(const int& maxrow, const int& maxcol)
/*
Pre:  The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/

{
   int row, col;
   // int new_grid[maxrow + 2][maxcol + 2];
   int** new_grid = grid;
   int rows = maxrow;
   int cols = maxcol;
   // cout << rows << "\t" << cols;
   for (row = 1; row <= maxrow; row++)
      for (col = 1; col <= maxcol; col++)
         switch (neighbor_count(row, col, rows, cols)) {
         case 2:
            new_grid[row][col] = grid[row][col];  //  Status stays the same.
            break;
         case 3:
            new_grid[row][col] = 1;                //  Cell is now alive.
            break;
         default:
            new_grid[row][col] = 0;                //  Cell is now dead.
         }

   for (row = 1; row <= maxrow; row++)
      for (col = 1; col <= maxcol; col++)
         grid[row][col] = new_grid[row][col];
   
  
}

Life::~Life()
{
    cout << endl << endl << "\t Thank you for using this program!" << endl;
}


void instructions()
/*
Pre:  None.
Post: Instructions for using the Life program have been printed.
*/

{
   cout << "Welcome to Conway's game of Life." << endl;
   //cout << "This game uses a grid of size "
   //     << maxrow << " by " << maxcol << " in which" << endl;
   cout << "each cell can either be occupied by an organism or not." << endl;
   cout << "The occupied cells change from generation to generation" << endl;
   cout << "according to the number of neighboring cells which are alive."
        << endl;
}


void Life::initialize(int** aGrid, const int &maxrow, const int &maxcol)
/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/

{
   grid = aGrid;
   int row, col;
   for (row = 0; row <= maxrow; row++)
      for (col = 0; col <= maxcol; col++)
         grid[row][col] = 0;

   cout << "List the coordinates for living cells." << endl;
   cout << "Terminate the list with the special pair -1 -1" << endl;
   cin >> row >> col;
   
   while (row != -1 || col != -1) {
      if (row >= 1 && row <= maxrow)
         if (col >= 1 && col <= maxcol)
            grid[row][col] = 1;
         else
            cout << "Column " << col << " is out of range." << endl;
      else
         cout << "Row " << row << " is out of range." << endl;
      cin >> row >> col;
   }
}


void Life::print(const int& maxrow, const int& maxcol)
/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/

{
   int row = maxrow, col = maxcol;
   cout << "\nThe current Life configuration is:" <<endl;
   for (row = 1; row <= maxrow; row++) {
      for (col = 1; col <= maxcol; col++)
         if (grid[row][col] == 1) cout << '*';
         else cout << ' ';
      cout << endl;
   }
   cout << endl;
}


bool user_says_yes()
{
	int c;
	bool initial_response = true;

	do {  //  Loop until an appropriate input is received.
		if (initial_response)
			cout << " (y,n)? " << flush;

		else
			cout << "Respond with either y or n: " << flush;

		do { //  Ignore white space.
			c = cin.get();
		} while (c == '\n' || c == ' ' || c == '\t');
		initial_response = false;
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
	return (c == 'y' || c == 'Y');
}

void askValue(int &row, int &col) {
    int temp;
    bool operand = true;
    do {
        std::cout << "Give value of rows (1-60):\n";
        cin >> temp;
        if (temp < 1 || temp > 60) {
            std::cout << "False input or out of range.\n";
            operand = false;
        }
        operand = true;
    } while (!operand);
    row = temp;

    do {
        std::cout << "Give value of cols (1-60):\n";
        cin >> temp;
        if (temp < 1 || temp > 60) {
            std::cout << "False input or out of range.\n";
            operand = false;
        }
        operand = true;
    } while (!operand);
    col = temp;
    
 }
