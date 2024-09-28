/*Chess game
 * Version 4*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"



char board[9][9] =
{
{' ', '1', '2', '3', '4', '5', '6', '7','8'},
{'1', 'r', 'k', 'b', '+', 'q', 'b', 'k','r'},
{'2', 'p', 'p', 'p', 'p', 'p', 'p', 'p','p'},
{'3', '_', '_', '_', '_', '_', '_', '_','_'},
{'4', '_', '_', '_', '_', '_', '_', '_','_'},
{'5', '_', '_', '_', '_', '_', '_', '_','_'},
{'6', '_', '_', '_', '_', '_', '_', '_','_'},
{'7', 'P', 'P', 'P', 'P', 'P', 'P', 'P','P'},
{'8', 'R', 'K', 'B', 'Q', '$', 'B', 'K','R'}
};

int check_move(char p, int* move);
int check_winner();
int* get_moves();
void print_grid();

int main()
{
	while (1)
	{
		//starting grid
		print_grid();

		//user input to move the piece
		int* m = get_moves();

		char piece = board[m[0]][m[1]];
		//checking the piece
		while (1)
		{
			if (piece == '_')
			{
				printf("Invalid piece. Move again\n");
				free(m);
				m = get_moves();
				piece = board[m[0]][m[1]];
			}
			else
				break;
		}
		//making the movement rules
		int check = check_move(piece, m);
		//making the movement
		if (check == 1)
		{
			board[m[2]][m[3]] = piece;
			board[m[0]][m[1]] = '_';
		}
		else
		{
			printf("Invalid move. Play again\n \n");
			continue;
		}
		if (check_winner() == 0)
		{
			print_grid();
			return 0;
		}
	}
}

int* get_moves()
{
	int* moves = (int*)malloc(4 * sizeof(int));
	printf("Move from: ");
	scanf("%d %d", moves, (moves + 1));  //(x,y) initial
	printf("Move to: ");
	scanf("%d %d", (moves + 2), (moves + 3)); //(x1, y1) final
	return moves;
}

void print_grid(void)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] == 'r' || board[i][j] == 'k' || board[i][j] == 'b' || board[i][j] == 'q' || board[i][j] == '+' || board[i][j] == 'p')
			{
				printf(ANSI_COLOR_MAGENTA "%c\t" ANSI_COLOR_RESET, toupper(board[i][j]));
			}
			else if (board[i][j] == 'R' || board[i][j] == 'K' || board[i][j] == 'B' || board[i][j] == 'Q' || board[i][j] == '$' || board[i][j] == 'P')
			{
				printf(ANSI_COLOR_GREEN "%c\t" ANSI_COLOR_RESET, toupper(board[i][j]));
			}
			else
				printf("%c\t", board[i][j]);
		}
		printf("\n\n\n");
	}
}

int check_move(char p, int* move)
{
	int from_x = move[0];
	int from_y = move[1];
	int to_x = move[2];
	int to_y = move[3];

	switch (p)
	{
	case 'p':
		if (board[to_x][to_y] == '_') //non kill scenario
		{
			if (to_y == from_y)
			{
				if (to_x == from_x + 1)
					return 1;
				else { return 0; }
			}
			else { return 0; }
		}
		else	//kill scenario
		{
			if (to_x - from_x == 1 && abs(to_y - from_y) == 1)
				return 1;
			else { return 0; }
		}
		break;
	case 'r':
		if (to_x == from_x || to_y == from_y)
			return 1;
		else
			return 0;
		break;
	case '+':
		if ((to_y - from_y) <= 1 && (to_x - from_x) <= 1)
			return 1;
		else { return 0; }
		break;
	case 'b':
		if (abs(to_x - from_x) == abs(to_y - from_y))
			return 1;
		else { return 0; }
	case 'k':
		if ((abs(to_x - from_x) == 2 && abs(to_y - from_y) == 1) || (abs(to_x - from_x) == 1 && abs(to_y - from_y) == 2))
			return 1;
		else { return 0; }
	case 'q':
		if (abs(to_x - from_x) == abs(to_y - from_y) || to_x == from_x || to_y == from_y)
			return 1;
		else { return 0; }

	case 'P':
		if (board[to_x][to_y] == '_') //non kill scenario
		{
			if (to_y == from_y)
			{
				if (to_x == from_x - 1)
					return 1;
				else { return 0; }
			}
			else { return 0; }
		}
		else    //kill scenario
		{
			if (to_x - from_x == -1 && abs(to_y - from_y) == 1)
				return 1;
			else { return 0; }
		}
		break;
	case 'R':
		if (to_x == from_x || to_y == from_y)
			return 1;
		else
			return 0;
		break;
	case '$':
		if ((to_y - from_y) <= 1 && (to_x - from_x) <= 1)
			return 1;
		else { return 0; }
		break;
	case 'B':
		if (abs(to_x - from_x) == abs(to_y - from_y))
			return 1;
		else { return 0; }
	case 'K':
		if ((abs(to_x - from_x) == 2 && abs(to_y - from_y) == 1) || (abs(to_x - from_x) == 1 && abs(to_y - from_y) == 2))
			return 1;
		else { return 0; }
	case 'Q':
		if (abs(to_x - from_x) == abs(to_y - from_y) || to_x == from_x || to_y == from_y)
			return 1;
		else { return 0; }

	}
}

int check_winner(void)
{
	int B_king = 0, W_king = 0;
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			if (board[i][j] == '+')
				B_king++;
			if (board[i][j] == '$')
				W_king++;
		}
	}
	if (B_king == 1 && W_king == 1)
		return 1;
	else if (B_king != 1 && W_king == 1)
	{
		printf("\nGreen wins\n");
		return 0;
	}
	else if (B_king == 1 && W_king != 1)
	{
		printf("\nMagneta wins\n");
		return 0;
	}
}
