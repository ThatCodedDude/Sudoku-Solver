// Programmed By ThatCodedDude //

// Sudoku Solver //

// With Backtracking Algorithm and Recursion //

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define NO_SOLUTION 456
#define EMPTY 0
#define MAX 9

void wait(float);
bool SolveSudoku(int*[MAX][MAX], int, int);
void PrintSudoku(int[MAX][MAX]);
bool IsEmptyCell(int);
bool SudokuRow(int[MAX][MAX], int, int);
bool SudokuColumn(int[MAX][MAX], int, int);
void GetSudokuGrid(int, int, int*, int*);
bool SudokuGrid(int[MAX][MAX], int, int);
void GetSolutions(int[MAX][MAX], int, int, int*[9], int*);
void BackTrack(int*[MAX][MAX], int, int);
void GetInputtedValues(int*[MAX][MAX], int[MAX][MAX]);
bool IsInputtedValue(int[MAX][MAX], int[MAX][MAX], int, int);
bool IsValid(int[MAX][MAX], int, int, int);

const int ValidNumbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int InputtedValues[MAX][MAX];

int main(){

    int Sudoku[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, // Input Sudoku Puzzle Here (Row By Row)
                        {0, 0, 0, 0, 0, 0, 0, 0, 0}, // Input Empty Cell as 0
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    GetInputtedValues(InputtedValues, Sudoku);

    SolveSudoku(Sudoku, 0, 0);
    PrintSudoku(Sudoku);

    return 0;
}

// Main Solve Function //

bool SolveSudoku(int* Sudoku[MAX][MAX], int IP, int KP){

    int I = IP, K = KP;

    for(int i = I; i < MAX; i++){

        for(int k = K; k < MAX; k++){

            if(k == 8){
                if(i != 8){

                    K = 0;

                }
            }

            if(IsInputtedValue(Sudoku, InputtedValues, k, i) == false){

               if(IsValid(Sudoku, k, i, Sudoku[i][k]) == false){

               int Solutions[9], NumberOf;
               GetSolutions(Sudoku, k, i, Solutions, &NumberOf);

               if(NumberOf > 0){

                 if(IsEmptyCell(Sudoku[i][k]) == false){

                    int Place = NO_SOLUTION;

                    for(int j = 0; j < NumberOf; j++){

                        if(Sudoku[i][k] == Solutions[j]){

                            Place = j;
                            break;

                        }

                    }

                    if(Place != NO_SOLUTION){

                        if(Place == NumberOf - 1){

                            Sudoku[i][k] = Solutions[0];

                        }else{

                           Sudoku[i][k] = Solutions[Place + 1];

                        }

                    }

                 }else{

                    Sudoku[i][k] = Solutions[0];

                 }

               }else{

                 BackTrack(Sudoku, k, i);

               }

            }else{

              continue;

            }

            }else{

              continue;

            }

        }

    }

    return true;

}

// Checks if Solution is Valid //

bool IsValid(int Sudoku[MAX][MAX], int Side, int Up, int Number){

   bool RowCheck = SudokuRow(Sudoku, Side, Up);
   bool ColumnCheck = SudokuColumn(Sudoku, Side, Up);
   bool GridCheck = SudokuGrid(Sudoku, Side, Up);

   if(IsEmptyCell(Number) == false){

      if(RowCheck == false || ColumnCheck == false || GridCheck == false){

       return false;

      }else{

       return true;

      }

   }else{

      return false;

   }

}

void BackTrack(int *Sudoku[MAX][MAX], int Side, int Up){ // Backtrack until Cell has a solution

  int iPlace = Up, kPlace = Side;

  for(int i = iPlace; i >= 0; i--){

    for(int k = kPlace; k >= 0; k--){

        if(k == 0){
            kPlace = MAX - 1;
        }

        //PrintSudoku(Sudoku);

        if(IsInputtedValue(Sudoku, InputtedValues, k, i) == false){

            int Solutions[9], NumberOf;
            GetSolutions(Sudoku, k, i, Solutions, &NumberOf);

                int Place = NO_SOLUTION;

                    for(int j = 0; j < NumberOf; j++){

                        if(Sudoku[i][k] == Solutions[j]){

                            Place = j;
                            break;

                        }

                    }

                    if(Place != NO_SOLUTION){

                        if(Place == NumberOf - 1){

                            Sudoku[i][k] = 0;
                            continue;

                        }else{

                           Sudoku[i][k] = Solutions[Place + 1];
                           SolveSudoku(Sudoku, i, k);
                           i = -1; k = -1;

                        }

                    }else{

                      Sudoku[i][k] = 0;
                      continue;

                    }


        }else{

          continue;

        }

    }

  }

}



// Function Gets all Possible Solutions for the Cell //

void GetSolutions(int Sudoku[MAX][MAX], int Side, int Up, int* Solutions[9], int* NumberOfSolutions){

    int Counter = 0; int Counter2 = 0;

   if(IsInputtedValue(Sudoku, InputtedValues, Side, Up) == false){

      for(int i = 0; i < 9; i++){ // Checks Row, then makes sure that each Solution is possible by checking the column and 3x3 Grid afterwards

      bool Passed = true;
      bool PassedNext = true;
      bool CanAdd = true;

      for(int x = 0; x < MAX; x++){

        if(x == Side){
        continue; // Skips the Position of The Current Cell
        }

        if(ValidNumbers[i] == Sudoku[Up][x]){

            Passed = false;
        }

      }

      if(Passed == true){

        for(int j = 0; j < MAX; j++){

            if(j == Up){
                continue; // Skips the Position of The Current Cell
            }

            if(ValidNumbers[i] == Sudoku[j][Side]){

                PassedNext = false;
                CanAdd = false;

            }

        }

      }else{

        CanAdd = false;

      }

      if(Passed == true && PassedNext == true){

        int GridSide, GridUp;

        GetSudokuGrid(Side, Up, &GridSide, &GridUp);

      for(int h = GridUp - 3; h < GridUp; h++){

        for(int j = GridSide - 3; j < GridSide; j++){

         if(h == Up && j == Side){
             continue;
         }

         if(Sudoku[h][j] == ValidNumbers[i])

          CanAdd = false;

         }

    }

}

  if(CanAdd == true){


        Solutions[Counter] = ValidNumbers[i];

        Counter++;

  }else{

     Counter2++;

     if(Counter2 == 9){

        Solutions[0] = NO_SOLUTION;

     }

  }

}

   }

*NumberOfSolutions = Counter;

}




// Helper Functions for the IsValid() Function //

bool SudokuRow(int Sudoku[MAX][MAX], int Side, int Up){

   bool IsAlright = true;

   for(int i = 0; i < MAX; i++){

      if(i == Side){
        continue; // Skips the Position of The Current Cell
      }

      if(Sudoku[Up][Side] == Sudoku[Up][i]){

        IsAlright = false;

      }

   }

   return IsAlright;

}

bool SudokuColumn(int Sudoku[MAX][MAX], int Side, int Up){

   bool IsAlright = true;

   for(int i = 0; i < MAX; i++){

      if(i == Up){

        continue; // Skips the Position of the Current Cell

      }

      if(Sudoku[Up][Side] == Sudoku[i][Side]){

        IsAlright = false;

      }

   }

   return IsAlright;

}

bool SudokuGrid(int Sudoku[MAX][MAX], int Side, int Up){

  bool CanPass = true;

  int GridSide, GridUp;

  GetSudokuGrid(Side, Up, &GridSide, &GridUp);

  for(int i = GridUp - 3; i < GridUp; i++){

    for(int j = GridSide - 3; j < GridSide; j++){

        if(i == Up && j == Side){
            continue;
         }

       if(Sudoku[i][j] == Sudoku[Up][Side])

         CanPass = false;

       }

       }

    return CanPass;

}



void GetSudokuGrid(int Side, int Up, int *GridSide, int* GridUp){

  bool IsAlright = true;

  // Getting the Sudoku Grid //

  if(Side < 3){

    *GridSide = 3;

  }else if(Side < 6 && Side >= 3){

     *GridSide = 6;

  }else if(Side < 9 && Side >= 6){

      *GridSide = 9;

  }

  if(Up < 3){

    *GridUp = 3;

  }else if(Up < 6 && Up >= 3){

    *GridUp = 6;

  }else if(Up < 9 && Up >= 6){

    *GridUp = 9;

  }

}

// Checks if the Cell is empty

bool IsEmptyCell(int Number){

   if(Number == EMPTY){

     return true;

   }else{

     return false;

   }

}

void GetInputtedValues(int* InputtedArray[MAX][MAX], int Sudoku[MAX][MAX]){ // Gets Inputted Values //

   for(int i = 0; i < MAX; i++){

      for(int k = 0; k < MAX; k++){

        if(IsEmptyCell(Sudoku[i][k]) == false){

            InputtedArray[i][k] = Sudoku[i][k];

        }

      }

   }

}

bool IsInputtedValue(int Sudoku[MAX][MAX], int InputtedArray[MAX][MAX], int Side, int Up){

   bool Passed = false;

  for(int i = 0; i < MAX; i++){

    if(Sudoku[Up][Side] == InputtedArray[Up][i] && Side == i && IsEmptyCell(Sudoku[Up][Side]) == false){

        Passed = true;

    }

  }

  return Passed;

}

// Prints out the inputted Sudoku Puzzle //

void PrintSudoku(int PrintSudoku[MAX][MAX]){

    printf("Sudoku Puzzle: \n\n");

  int i, k;

  for(i = 0; i < MAX; i++){

    for(k = 0; k < MAX; k++){

        if(k == 0){
            printf("\t");
        }

        printf("%d  ", PrintSudoku[i][k]);

        if(k == MAX - 1){
            printf("\n");
        }

    }

  }

}

// Self-Made Wait Function for Testing (Useless)

void wait(float Seconds){

  sleep(Seconds * 1000);

}
