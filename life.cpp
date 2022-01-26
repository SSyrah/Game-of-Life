#include "life.h"


int** allocate_grid(int& maxrow, int& maxcol)
{
    int** arr = new int* [maxrow];
    for (int i = 0; i < maxrow; i++)
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

   int i_beg = row - 1 >= 0 ? row - 1 : 0;
   int i_end = row + 1 < rows ? row + 1 : rows - 1;
   int j_beg = col - 1 >= 0 ? col - 1 : 0;
   int j_end = col + 1 < cols ? col + 1 : cols - 1;
   
   
   for (i = i_beg; i <= i_end; i++)
       for (j = j_beg; j <= j_end; j++)
           if (true == legal_position(i, j, rows, cols))
               count += grid[i][j];  //  Increase the count if neighbor is alive.
   
   count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
   return count;
}

bool Life::legal_position(int row, int col, int maxr, int maxc)
{
    return (0 <= row && row < maxr && 0 <= col && col < maxc);
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
   for (row = 0; row < maxrow; row++)
      for (col = 0; col < maxcol; col++)
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

   for (row = 0; row < maxrow; row++)
      for (col = 0; col < maxcol; col++)
         grid[row][col] = new_grid[row][col];
   
  
}

Life::~Life()
{
    std::cout << std::endl << std::endl << "\t Thank you for using this program!" << std::endl;
}


void instructions()
/*
Pre:  None.
Post: Instructions for using the Life program have been printed.
*/

{
    std::cout << "Welcome to Conway's game of Life." << std::endl;
   //cout << "This game uses a grid of size "
   //     << maxrow << " by " << maxcol << " in which" << endl;
    std::cout << "each cell can either be occupied by an organism or not." << std::endl;
    std::cout << "The occupied cells change from generation to generation" << std::endl;
    std::cout << "according to the number of neighboring cells which are alive."
        << std::endl;
}


void Life::initialize(int** aGrid, const int &maxrow, const int &maxcol)
/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/

{
   std::fstream myfile;
   std::string line;
   size_t limit;
   char array[60] = {'\0'};
   char arr[60][60] = {'\0'};
   bool operand = true;
   int option;
   grid = aGrid;
   int row, col;


   for (row = 0; row < maxrow; row++)
      for (col = 0; col < maxcol; col++)
         grid[row][col] = 0;
   
   //Start to fill grid row by row until user presses just Enter:
   std::cout << "Fill rows one by one (space = dead cell / x = alive cell.\n";
   std::cout << "Pressing just Enter starting from next row concludes the filling process.\n";
   std::cout << "Do you want to read from file or fill grid by yourself?" << std::endl;
   std::cout << "Option 1 = Fill by yourself, Option 2 = read from a file." << std::endl;
   std::cout << "Choose option: ";
   std::cin >> option;
   std::cin.ignore();

   while (operand) {
       switch (option) {
       case 1:
           for (int i = 0; i < maxrow; i++) {
               std::cout << i + 1 << ":  ";
               std::getline(std::cin, line, '\n');
               limit = line.length();
               std::strcpy(array, line.c_str());
               for (int j = 0; j < maxcol; j++) {
                   if (array[j] == 'x')
                       grid[i][j] = 1;
               }
               if (line.length() == 0)
                   break;
               line = "";
               std::memset(array, 0, sizeof(array));
               
           }
           operand = false;
           break;

       case 2:
           myfile.open("grid.txt", std::ios::in);
           
           if (!myfile) {
               std::cout << "File cannot be read" << std::endl;
           }
           else {
               std::cout << "File opened succesfully." << std::endl;
               int rows = 0, cols = 0;
               std::string lim;
               std::getline(myfile, lim);
               int limits = lim.length();
                                 
               while (!myfile.eof()) {
                   for (cols; cols < limits; cols++) {
                       arr[rows][cols] = myfile.get();
                       // std::cout << arr[rows][cols];
                   }
                   cols = 0;
                   rows++;
               }
               
               for (int i = 0; i < rows; i++) {
                   for (int j = 0; j < limits; j++) {
                       if (arr[i][j] == 'x')
                           grid[i][j] = 1;
                       // std::cout << grid[i][j];
                   }
               }
               myfile.close();
           }
           operand = false;
           break;
       default:
           std::cout << "Input out of range, enter input again:" << std::endl;
           std::cin >> option;
           std::cin.ignore();

       }
   }  
   
}
       /*
      std::cout << "List the coordinates for living cells." << std::endl;
      std::cout << "Terminate the list with the special pair -1 -1" << std::endl;
      std::cin >> row >> col;


      while (row != -1 || col != -1) {
         if (row >= 1 && row <= maxrow)
            if (col >= 1 && col <= maxcol)
               grid[row][col] = 1;
            else
                std::cout << "Column " << col << " is out of range." << std::endl;
         else
             std::cout << "Row " << row << " is out of range." << std::endl;
         std::cin >> row >> col;
      }*/
 


void Life::print(const int& maxrow, const int& maxcol)
/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/

{
   int row, col;
   std::cout << "\nThe current Life configuration is:" << std::endl;
   for (row = 0; row < maxrow; row++) {
      for (col = 0; col < maxcol; col++)

          if (grid[row][col] == 1) std::cout << '*';
         else std::cout << '-';
      std::cout << std::endl;
   }
   std::cout << std::endl;
   
}


bool user_says_yes()
{
	int c;
	bool initial_response = true;

	do {  //  Loop until an appropriate input is received.
		if (initial_response)
            std::cout << " (y,n)? " << std::flush;

		else
            std::cout << "Respond with either y or n: " << std::flush;

		do { //  Ignore white space.
			c = std::cin.get();
		} while (c == '\n' || c == ' ' || c == '\t');
		initial_response = false;
	} while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
	return (c == 'y' || c == 'Y');
}

void askValue(int &row, int &col) {
    int temp;
    bool operand = true;
    do {
        std::cout << "Give value of rows (1-60): ";
        std::cin >> temp;
        if (temp < 1 || temp > 60) {
            std::cout << "False input or out of range.\n";
            operand = false;
        }
        operand = true;
    } while (!operand);
    row = temp;

    do {
        std::cout << "Give value of cols (1-60): ";
        std::cin >> temp;
        if (temp < 1 || temp > 60) {
            std::cout << "False input or out of range.\n";
            operand = false;
        }
        operand = true;
    } while (!operand);
    col = temp;
    std::cin.ignore();
      
 }

void Life::result_to_file(int& maxrow, int& maxcol) {

    std::cout << std::endl << std::endl;
    std::cout << "Writing this result of the game to file." << std::endl;
    for (int row = 0; row < maxrow; row++) {
        for ( int col = 0; col < maxcol; col++)

            if (grid[row][col] == 1) std::cout << '*';
            else std::cout << '-';
        std::cout << std::endl;
    }
    std::cout << std::endl;

    
    std::ofstream result;
    result.open("grid.txt");
    for (int i = 0; i < maxrow; i++) {
        for (int j = 0; j < maxcol; j++) {
            if (grid[i][j] == 1) {
                result << "x";}
            else {
                result << "-";
            }
        }
        result << "\n";
    }
    result.close();
}
