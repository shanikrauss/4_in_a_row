//SHANI KRAUSS

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h>

// This program is the game 4 in row.
// The game has 2 players
// The goal of the game is to connect 4 identical symbols in a row / column / diagonal.
// The first player to do so wins the game
// If no player succeeds and the board fills the game is over with a tie.
// Each turn the player chooses which column he wants to play(meaning to put his X or O symbol)
// If a column fills up and a player tries to choose it, the program will print an error message
// If a player tries to put a symbol in a column that does not exist (col>7 or col<1),the program will print an error message.

/*************** Board ***************/
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];


/*********** Declarations ************/

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function clears the screen.
void clearScreen();

//This function gets a number of rows, and a number columns and prints the current board.
//The rows are displayed with capital letters
//The columns are displayed with numbers
void printBoard(int numOfCols, int numOfRows);

//This function checks if the column input is vlaid (between 1-7)  and if it is full. 
//if it is full/not valid it asks from the player for a new column
//func returns the column.
int promptValidCol();

//This function checks which row in the column that the player chose is available
//and puts his move in the right row in the choosen column
//returns the available row.
int makeMove(int playersMoveValidCol, char symbolOfPlayer);

//This function checks who is the active player and returns the symbol of the active player X or O
char smybolOfActivePlayer(int currentPlayerNumber);

//This function toggles the current player
int switchPlayer(int currentPlayerNumber);

//This function checks if there 4 in row of the same symbol
bool is4InARow(int playerRow);

//This function checks if there 4 in column of the same symbol
bool is4InACol(int playerCol);

//This function checks if there 4 in diagonal down right of the same symbol
bool is4InDiagonalDownRight(int playerRow, int playerCol);

//This function checks if there 4 in diagonal down left of the same symbol
bool is4InDiagonalDownLeft(int playerRow, int playerCol);

//This function checks if there is a tie
//meaning if the boars is full and there is no winner with 4 in a row/column/diagonals
bool isTie();

//This function checks if there is a winner 
//meaning if there is 4 in a row/column/diagonals
bool isWinner(int playerRow, int playerCol);


const int PLAYER1 = 1;
const int PLAYER2 = 2;

/*************** Main ****************/
int main()
{
	printBoard(COLS, ROWS);
	initBoard();

	bool theGameIsNotOver;
	theGameIsNotOver = true;
	int whoIsActivePlayer;
	whoIsActivePlayer = PLAYER1;

	while (theGameIsNotOver)
	{
		printf("Player number %d:\n", whoIsActivePlayer);

		int chosenColumn;
		chosenColumn = promptValidCol();

		char symbActivePlayer;
		symbActivePlayer = smybolOfActivePlayer(whoIsActivePlayer);

		int rowOfLastMove;
		rowOfLastMove = makeMove(chosenColumn, symbActivePlayer);

		clearScreen();

		printBoard(COLS, ROWS);

		if (isWinner(rowOfLastMove, chosenColumn))
		{
			printf("Player number %d won! :)", whoIsActivePlayer);
			theGameIsNotOver = false;
		}
		else if (isTie())
		{
			printf("There's a tie!");
			theGameIsNotOver = false;
		}

		whoIsActivePlayer = switchPlayer(whoIsActivePlayer); //swithching the player

	}
}


bool isWinner(int playerRow, int playerCol)
{
	if (is4InARow(playerRow))
	{
		return (true);
	}
	if (is4InACol(playerCol))
	{
		return (true);

	}
	if (is4InDiagonalDownRight(playerRow, playerCol))
	{
		return (true);

	}
	if (is4InDiagonalDownLeft(playerRow, playerCol))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool isTie()
{
	int i, countRowA;
	char rowA;
	countRowA = 0;

	for (i = 1; i <= COLS; i++)
	{
		rowA = getCell(1, i);
		if (rowA != ' ')
		{
			countRowA++;
		}

	}
	if (countRowA == COLS)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool is4InDiagonalDownLeft(int playerRow, int playerCol)
{
	char firstSymbol, secondSymbol;
	int countPairSymbol = 0;
	int row, col;

	row = playerRow;
	col = playerCol;

	while ((row < ROWS) && (col > 1))
	{
		firstSymbol = getCell(row, col);
		row++;
		col--;
		secondSymbol = getCell(row, col);

		if (firstSymbol != secondSymbol)
		{
			countPairSymbol = 0;
		}

		else if ((firstSymbol == secondSymbol) && (firstSymbol != ' '))
		{
			countPairSymbol++;
			if (countPairSymbol == 3)
			{
				return (true);
			}
		}
	}
	while ((playerRow > 1) && (playerCol < COLS))
	{
		firstSymbol = getCell(playerRow, playerCol);
		playerRow--;
		playerCol++;
		secondSymbol = getCell(playerRow, playerCol);

		if (firstSymbol != secondSymbol)
		{
			countPairSymbol = 0;
		}

		else if ((firstSymbol == secondSymbol) && (firstSymbol != ' '))
		{
			countPairSymbol++;
			if (countPairSymbol == 3)
			{
				return (true);
			}
		}
	}
	if (countPairSymbol == 3)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool is4InDiagonalDownRight(int playerRow, int playerCol)
{
	char firstSymbol, secondSymbol;
	int countPairSymbol = 0;
	int row, col;

	row = playerRow;
	col = playerCol;

	while ((row < ROWS) && (col < COLS))
	{
		firstSymbol = getCell(row, col);
		row++;
		col++;
		secondSymbol = getCell(row, col);

		if (firstSymbol != secondSymbol)
		{
			countPairSymbol = 0;
		}

		else if ((firstSymbol == secondSymbol) && (firstSymbol != ' '))
		{
			countPairSymbol++;
			if (countPairSymbol == 3)
			{
				return (true);
			}
		}
	}
	while ((playerRow > 1) && (playerCol > 1))
	{
		firstSymbol = getCell(playerRow, playerCol);
		playerRow--;
		playerCol--;
		secondSymbol = getCell(playerRow, playerCol);

		if ((firstSymbol == ' ') || (secondSymbol == ' '))
		{
			countPairSymbol = 0;
		}

		else if (firstSymbol == secondSymbol)
		{
			countPairSymbol++;
			if (countPairSymbol == 3)
			{
				return (true);
			}
		}
	}
	if (countPairSymbol == 3)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool is4InACol(int playerCol)
{
	char firstSymbol, secondSymbol;
	int i, countPairSymbol = 0;

	for (i = 1; i < ROWS; i++)
	{
		firstSymbol = getCell(i, playerCol);
		secondSymbol = getCell(i + 1, playerCol);

		if (firstSymbol != secondSymbol)
		{
			countPairSymbol = 0;
		}

		else if ((firstSymbol == secondSymbol) && (firstSymbol != ' '))
		{
			countPairSymbol++;
			if (countPairSymbol == 3)
			{
				return (true);
			}
		}
	}
	return (false);
}

bool is4InARow(int playerRow)
{
	char firstSymbol, secondSymbol;
	int i, countPairSymbol = 0;

	for (i = 1; i < COLS; i++)
	{
		firstSymbol = getCell(playerRow, i);
		secondSymbol = getCell(playerRow, i + 1);

		if (firstSymbol != secondSymbol)
		{
			countPairSymbol = 0;
		}

		else if ((firstSymbol == secondSymbol) && (firstSymbol != ' '))
		{
			countPairSymbol++;
			if (countPairSymbol == 3)
			{
				return (true);
			}
		}

	}
	return (false);
}

char smybolOfActivePlayer(int currentPlayerNumber)
{
	if (currentPlayerNumber == PLAYER1)
	{
		return ('X');
	}
	else
	{
		return ('O');
	}
}

int switchPlayer(int currentPlayerNumber)
{
	if (currentPlayerNumber == PLAYER1)
	{
		return PLAYER2;
	}
	else
	{
		return PLAYER1;
	}
}

int promptValidCol()
{
	int playersChosenCol;
	printf("Please enter column input (a number between 1-7): ");

	scanf("%d", &playersChosenCol);

	while ((playersChosenCol > COLS) || (playersChosenCol < 1) || (getCell(1, playersChosenCol) != ' '))
	{
		if ((playersChosenCol > COLS) || (playersChosenCol < 1))
		{
			printf("The col you entered is not between 1-7.\n");
		}
		else if (getCell(1, playersChosenCol) != ' ')
		{
			printf("The col you entered is full.\n");
		}
		
		printf("Please enter column input (a number between 1-7): ");
		scanf("%d", &playersChosenCol);

	}
	return (playersChosenCol);// returns a valid col
}

int makeMove(int playersMoveValidCol, char symbolOfPlayer)
{
	char validRow;
	int  i, countRow = 6;

	validRow = getCell(ROWS, playersMoveValidCol);

	for (i = 0; (i < ROWS) && (validRow != ' ') && (countRow >= 1); i++) // checks where to put the move, which row is avilable
	{
		countRow--;
		validRow = getCell(countRow, playersMoveValidCol);


	}
	setCell(countRow, playersMoveValidCol, symbolOfPlayer);//puts the move in the right point on board	
	return countRow; //returns the avilable row
}

void printBoard(int numOfCols, int numOfRows)
{
	int countCol, i, j, k;
	char countRows;
	countCol = 1;
	printf(" ");
	for (i = 1; i <= numOfCols; i++, countCol++)
	{
		printf("    %d", countCol);
	}
	printf("\n");

	countRows = 'A';
	char pointOnTheBoard;
	int row = 1;
	int col = 1;
	pointOnTheBoard = getCell(row, col);

	for (j = 1; j <= numOfRows; j++, countRows++)
	{

		printf("%c    ", countRows);
		for (k = 1; k < 28; k = k + 4)
		{
			col++;
			printf("%c    ", pointOnTheBoard);
			pointOnTheBoard = getCell(row, col);
		}
		printf("\n");
	}
}

char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}

void initBoard()
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}

void clearScreen()
{
	system("cls");
}