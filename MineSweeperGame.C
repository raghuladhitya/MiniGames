#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h> 

int side;  
int mine; 

void makeMove(int *x, int *y) {                   // To get input from user as coordinates
	printf("Enter which tile to choose\nx, y coordinates: "); 
	scanf("%d %d", x, y); 
	return; 
} 

void printBoard(char virtualBoard[][30]) {        // to print or display the game board
	int i, j; 
	printf(""); 
	for(int i=0; i<side; i++) {  
	     for(j=0; j<side; j++) {
		printf ("%c ", virtualBoard[i][j]); 
	     }
	     printf ("\n"); 
	} 
	return; 
} 

bool Validate(int row, int col) {                   // to check there is no array index out of bounds
  if((row >= 0) && (row < side) && (col >= 0) && (col < mine))
    return true;
  else
    return false;
} 

 
bool isMine(int row, int col, char board[][30]) {    // to check the chosed coordinate is mine or not
     if(board[row][col] == '*') 
	  return true; 
     else
	  return false; 
} 

int countAdjacentMines(int row, int col, int mines[][2], char originalBoard[][30]){ 

	int count = 0;                             // To validate adjacent 8 possible cases of mines or not 
 
	if(Validate(row-1, col) == true) { 
	         if(isMine(row-1, col, originalBoard) == true) {
			count++; 
                 }
	} 

	if(Validate(row+1, col) == true) { 
		if(isMine(row+1, col, originalBoard) == true) {
			count++; 
		}
	} 

	if(Validate(row, col+1) == true) { 
		if(isMine(row, col+1, originalBoard) == true) {
		  count++;
		}
	} 

	if(Validate(row, col-1) == true) { 
		if(isMine(row, col-1, originalBoard) == true) {
		  count++; 
		}
	} 

	if(Validate(row-1, col+1) == true) { 
		if(isMine(row-1, col+1, originalBoard) == true) {
		  count++; 
		}
	} 

	if(Validate(row-1, col-1) == true) { 
		if(isMine(row-1, col-1, originalBoard) == true) {
		  count++; 
		}
	} 
 
	if(Validate(row+1, col+1) == true) { 
		if(isMine(row+1, col+1, originalBoard) == true) {
		  count++; 
		}
	} 

	if(Validate(row+1, col-1) == true) { 
		if(isMine(row+1, col-1, originalBoard) == true) {
		  count++; 
		}
	} 

	return count; 
} 


bool startMinesweeperUntil(char virtualBoard[][30], char originalBoard[][30], int mines[][2], int row, int col, int *remainingMoves) { 
	if(virtualBoard[row][col] != '-')                     
		return false; 
	if(originalBoard[row][col] == '*') {    // checking mine is encountered or not while choosing the position
		virtualBoard[row][col]='*'; 

		for(int i=0; i<mine; i++) {
			virtualBoard[mines[i][0]][mines[i][1]]='*'; 
		}
		printBoard(virtualBoard); 
		printf ("\nYou lost!\n"); 
		return true; 
	} 

	else{                                       //
		int count = countAdjacentMines(row, col, mines, originalBoard); 
		(*remainingMoves)--; 
		virtualBoard[row][col] = count + '0'; 

		if(!count) { 
			if(Validate(row-1, col-1) == true) { 
				if(isMine(row-1, col-1, originalBoard) == false) {
					startMinesweeperUntil(virtualBoard, originalBoard, mines, row-1, col-1, remainingMoves);
				}
			} 

			if(Validate(row-1, col) == true) { 
				if(isMine(row-1, col, originalBoard) == false) {
				  startMinesweeperUntil(virtualBoard, originalBoard, mines, row-1, col, remainingMoves); 
				}
			} 
      
			if(Validate(row-1, col+1) == true) { 
				if(isMine(row-1, col+1, originalBoard) == false) {
					startMinesweeperUntil(virtualBoard, originalBoard, mines, row-1, col+1, remainingMoves); 
				}
			} 

			if(Validate(row, col+1) == true) { 
				if(isMine(row, col+1, originalBoard) == false) {
					startMinesweeperUntil(virtualBoard, originalBoard, mines, row, col+1, remainingMoves); 
				}
			} 
      
			if(Validate(row+1, col+1) == true) { 
				if(isMine(row+1, col+1, originalBoard) == false) {
					startMinesweeperUntil(virtualBoard, originalBoard, mines, row+1, col+1, remainingMoves); 
				}
			} 

			if(Validate(row+1, col) == true) { 
				if(isMine(row+1, col, originalBoard) == false) {
					startMinesweeperUntil(virtualBoard, originalBoard, mines, row+1, col, remainingMoves); 
				}
			} 
                        if (Validate(row+1, col-1) == true) { 
				if (isMine(row+1, col-1, originalBoard) == false) {
					startMinesweeperUntil(virtualBoard, originalBoard, mines, row+1, col-1, remainingMoves); 
				}
			} 
			if(Validate(row, col-1) == true) { 
				if(isMine(row, col-1, originalBoard) == false) {
					startMinesweeperUntil(virtualBoard, originalBoard, mines, row, col-1, remainingMoves); 
				}
			} 
		} 
		return false; 
	} 
} 
 
void placeMines(int mines[][2], char originalBoard[][30]){ 
	bool mark[30*30];                               

	for (int i=0; i<mine; ) { 
		int randomValue = rand() % (side*side); 
		int x = randomValue / side; 
		int y = randomValue % side; 
		if(mark[randomValue] == false) {                    // To prevent repeated location of the same mine 
			mines[i][0]= x;  
			mines[i][1] = y; 
			originalBoard[mines[i][0]][mines[i][1]] = '*'; 
			mark[randomValue] = true; 
			i++;                                             // If it doesn't then it increments
		} 
	} 
} 

void setup(char originalBoard[][30], char virtualBoard[][30]) {  
	srand(time (0)); 
	for (int i=0; i<side; i++) { 
		for (int j=0; j<side; j++) { 
			virtualBoard[i][j] = originalBoard[i][j] = '-'; 
		} 
	} 
} 

void replaceMine(int row, int col, char board[][30]){ 
	for (int i=0; i<side; i++){ 
		for (int j=0; j<side; j++){  
			if(board[i][j] != '*') { 
				board[i][j] = '*'; 
				board[row][col] = '-'; 
				return; 
			} 
		} 
	} 
} 
 
void startMinesweeper() {      // 2nd this fn is called to start the game

	bool gameover = false; 
	char originalBoard[30][30], virtualBoard[30][30]; 

	int remainingMoves = side * side - mine, x, y; 
	int mines[100][2];  

	setup(originalBoard, virtualBoard); 
	placeMines(mines, originalBoard);

	int indexPos = 0; 
	while(gameover == false) { 
		printf("Game Board: \n"); 
		printBoard(virtualBoard);         //All changes are saved in virtual board
		makeMove (&x, &y); 

		if(indexPos == 0) { 
			if(isMine(x, y, originalBoard) == true) 
				replaceMine (x, y, originalBoard); 
		} 

		indexPos ++;    

		gameover = startMinesweeperUntil(virtualBoard, originalBoard, mines, x, y, &remainingMoves);  //this function is recursive and runs all the edge cases and saves the result as boolean

		if((gameover == false) && (remainingMoves == 0)) { 
			printf ("\nYou completed the game \n"); 
			gameover = true; 
		} 
	} 
} 
void difficultyLevel () { 
	int level; 

	printf("Enter the Difficulty Level\n"); 
	printf("1.Easy\n"); 
	printf("2.Medium\n"); 
	printf("3.Hard\n"); 

	scanf("%d", &level); 
	if(level == 1) { 
		side = 9; 
		mine = 10; 
	} else if(level == 2) { 
		side = 16; 
		mine = 40; 
	} else if(level == 3) { 
		side = 24; 
		mine = 100; 
	} 
} 

int main() { 
	difficultyLevel(); 
	startMinesweeper(); 
	return 0; 
}
