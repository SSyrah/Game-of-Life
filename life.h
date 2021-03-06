#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <thread>
#include <chrono>
//using namespace std;



enum Error_code {
	success, fail, utility_range_error, underflow, overflow, fatal,
	not_present, duplicate_error, entry_inserted, entry_found,
	internal_error
};


void instructions();
bool user_says_yes();
int** allocate_grid(int&, int&);
void askValue(int&, int&);


class Life {
public:

   void initialize(int**, const int&, const int&);
   void print(const int&, const int&); 
   void update(const int&, const int&);
    ~Life();
	void result_to_file(int&, int&);

   
  
private:
	bool legal_position(int, int, int, int);
	int** grid;
    int neighbor_count(int row, int col, int rows, int cols);
};