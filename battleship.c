#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SHIP_TYPES 1

struct ship
{
	char *name_plural;
	char *name_singular;
	int dimension;
	int number;
};

struct ship ships[] =
{
	{
		"aircraft carrier",
		"aircraft carriers",
		4,
		2
	}/*,
	{
		"ironclad",
		"ironclads",
		3,
		2
	},
	{
		"cruiser",
		"cruisers",
		2,
		3
	},
	{
		"submarine",
		"submarines",
		1,
		2
	}*/
};

/*
   Prints a table with the ships placed. A ship-box is represented in the table with its dimension n, and the same ship-box
   is repetead n-times in some direction to form a full ship. This function is called at the beginning of the game,
   to place the ships of both players.
           
		   1  2  3  4  5  6  7  8
   		A {0, 0, 0, 0, 0, 0, 0, 3},
		B {0, 0, 0, 0, 0, 0, 0, 3},
		C {0, 0, 0, 0, 0, 0, 0, 3},
		D {0, 4, 4, 4, 4, 0, 0, 0},
		E {0, 0, 0, 0, 0, 0, 0, 0},
		F {0, 0, 0, 0, 0, 1, 0, 0},
		G {0, 0, 0, 0, 0, 0, 0, 0},
		H {0, 0, 0, 0, 0, 0, 0, 0},
		
	In this example, the table contains 3 ships. A ship of size for horizzontally placed, a ship of size 3 vertically placed
	and a ship of size 1.
*/

void print_ships(int matrix[][8])
{
	printf("\n       ---------------------------------\n");
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(j == 0)
				printf("       ");
			if(matrix[i][j] > 0)
				printf("| %d ", 
					   matrix[i][j]);
			else
				printf("|   ");
			
			if(j == 7)
				printf("|");
		}
		printf("\n       ---------------------------------\n");
	}
	printf("\n");
}

/*
	Prints a table with the shots fired by the player. A good shot is represented by a 'X' and a missed shot by a 'o'.
*/

void print_shots_table(char matrix[][8], int player)
{
	printf("       -------------Player%d-------------\n",
		   player);
	printf("       ---------------------------------\n");
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(j == 0)
				printf("       ");
			if(matrix[i][j] == 'x')
				printf("| X ");
			else if(matrix[i][j] == 'o')
				printf("| o ");
			else
				printf("|   ");
			
			if(j == 7)
				printf("|");
		}
		printf("\n       ---------------------------------\n");
	}
	printf("\n");
}

/*
	Takes the position by the player. The user is asked for a string containing a letter A-H and a number 1-8. 
*/

void take_position(int *row, int *column)
{
	char position[20];
	char row_letter;   
	int  column_number;
	
	do
	{	
		scanf("%s", 
			  position);
		row_letter = position[0];
		column_number = atoi(&position[1]);
		
		if(strlen(position) > 2                     ||
		  (row_letter < 97 || row_letter > 104) ||
		  (column_number < 1 || column_number > 8))
		{
			printf("Position not valid. Retry: ");
		}
		else 
		{
			
			// trasformare lettera riga e numero colonna nei rispettivi indici della matrice
			
			*row = row_letter - 'a';
			*column = column_number - 1;	
		}
		//while(getchar() != '\n');
	}
	while((strlen(position) != 2)                  ||
		  (row_letter < 97 || row_letter > 104) ||
		  (column_number < 1 || column_number > 8));
}

/*
	Checks the validity of the ship placement. The ships must be inside the table e and they shouldn't collide with
	other ships already placed by the player.
*/

int check_positioning(int matrix[][8],
							 int row,
							 int column,
							 int ship_length,
							 int direction)
{
	int is_inside = 0;
	int no_collisions = 0;
	int empty_boxes = 0;
	
	// checks that the ship is within the boundaries of the table
	
	switch(direction)
	{
		// up
		
		case 'w':
			if(row - (ship_length - 1) >= 0)
				is_inside = 1;
			break;
			
		// down
		
		case 's':
			if(row + (ship_length - 1) <= 7)
				is_inside = 1;
			break;
			
		// right 
			
		case 'd':
			if(column + (ship_length - 1) <= 7)  
				is_inside = 1;
			break;
			
		// left
		
		case 'a':
			if(column - (ship_length - 1) >= 0)
				is_inside = 1;
			break;			
	}
	
	// checks that the ship doesn't collide with other ships already placed
	
	for(int i = 0; i < ship_length; i++)
	{
		if(matrix[row][column] == 0)
			empty_boxes++;
		
		switch(direction)
		{
			case 'w':
				row--;
				break;
			case 's':
				row++;
				break;
			case 'a':
				column--;
				break;
			case 'd':
				column++;
				break;
		}
	}
	
	if(empty_boxes == ship_length)
		no_collisions = 1;
	
	return is_inside && no_collisions;
}

/*
	Inserts the ships identifiers inside the table. 
*/

void place_ships(int matrix[][8], int player)
{
	char continuation_answer = 's';
	
	for(int i = 0; i < SHIP_TYPES; i++)
	{
		int  row;		 
		int  column;     
		char direction;
		int position_is_valid;
		int count = ships[i].number;	
		
		system("cls");
		print_ships(matrix);
	
		while(count)
		{
			do
			{
				// choose the starting square for the ship
				
				printf("Player %d place %d %s: ",
						player,
						count,
						count == 1 ? ships[i].name_plural : ships[i].name_singular);
				take_position(&row, &column);
				getchar(); // remove the \n character after the first scanf
				
				// choose the direction of the ship
				
				do
				{
					printf("Player %d choose the direction of the ship.\n",
					   player);
					   printf("up = w, down = s, left = a, right = d - w/a/s/d?: ");
					scanf("%c",
						&direction);
					if((direction != 'w') && 
					   (direction != 'a') && 
					   (direction != 's') && 
					   (direction != 'd'))
						printf("Direction not valid. Retry.\n");
					  
					while(getchar() != '\n');
				}
				while((direction != 'w') && 
					  (direction != 'a') && 
					  (direction != 's') && 
					  (direction != 'd'));
					  
				// checks that the positioning of the ships is valid 
				
				position_is_valid = check_positioning(matrix,
															row, 
															column, 
															ships[i].dimension, 
															direction);
				if(!position_is_valid)
					printf("Position not valid. Insert the position again.\n");
			}
			while(!position_is_valid);
			
			// insert in the table the ship-boxes, represented by the size of the ships along the direction

			for(int j = 0; j < ships[i].dimension; j++)
			{
				matrix[row][column] = ships[i].dimension;
				
				switch(direction)
				{
					case 'w':
						row--;
						break;
					case 's':
						row++;
						break;
					case 'a':
						column--;
						break;
					case 'd':
						column++;
						break;
				}
			}
			
			system("cls");
			print_ships(matrix);
			count--;
		}
	}
				
			// ask if the player wants to continue after with his placement of the ships. If not, the program reset the table and 
			// recall the function place_ships()
				
			do{
				printf("Continue? y/n?: ");
				scanf("%c", 
					  &continuation_answer);	
				if(continuation_answer != 'y' && continuation_answer != 'n')
					printf("Answer not valid. Retry.\n");	
				while(getchar() != '\n');
			}
			while(continuation_answer != 'y' && continuation_answer != 'n');
			if(continuation_answer == 'n')
			{
				
				// reset table and call this function again
				
				for(int i = 0; i < 8; i++)
				{
					for(int j = 0; j < 8; j++)
					{
						matrix[i][j] = 0;
					}
				}
				place_ships(matrix, player);
			}
			else 
				system("cls");
}

/*
	Asks the player the position of the shot, and add the result in the shots table
*/

void shoot_shot(int initial_placement[][8], char shots_table[][8], int player)
{
	int row,
		column;
	printf("Player %d choose where to fire the shot: ",
		   player);
	take_position(&row, &column);
	if(initial_placement[row][column] > 0)
		shots_table[row][column] = 'x';     // x = ship box hit
	else 
		shots_table[row][column] = 'o';	  	// o = empty box hit
}

/*
	Iterate through all elements of the shots table. If the number of ship boxes hit is the same as the total number of ship boxes
	return 1, 0 otherwise.
*/

int check_victory(char shots_table[][8], int player)
{
	
	// counts enemy's ship boxes hit
	
	int ship_boxes_hit = 0;
	int ship_boxes_total = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(shots_table[i][j] == 'x')
				ship_boxes_hit++;
		}
	}
	
	// counts all ship boxes placed
	
	for(int i = 0; i < SHIP_TYPES; i++)
	{
		ship_boxes_total += ships[i].number * ships[i].dimension;
	}

	if(ship_boxes_hit == ship_boxes_total)
	{
		system("cls");
		print_shots_table(shots_table, player);
		printf("Game over! Player %d destroyed all ships of the enemy!\n",
			   player);
		return 1;
	}
	return 0;
}

int main(void)
{
	int initial_placement_p1[8][8];
	int initial_placement_p2[8][8];
	char shots_table_p1[8][8];
	char shots_table_p2[8][8];
	int current_player = 1;
	
	int victory = 0;
	
	// initalizes arrays
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			initial_placement_p1[i][j] = 0;
			initial_placement_p2[i][j] = 0;
			shots_table_p1[i][j] = 0;
			shots_table_p2[i][j] = 0;
		}
	}

	// place ships
	
	place_ships(initial_placement_p1, 1);
	place_ships(initial_placement_p2, 2);
	
	// game loop
	
	while(!victory)
	{
		if(current_player == 1)
		{
			print_shots_table(shots_table_p1, current_player);
			shoot_shot(initial_placement_p2, shots_table_p1, current_player);
			print_shots_table(shots_table_p1, current_player);
			victory = check_victory(shots_table_p1, current_player);
			printf("\n\n\n\n\n");
			current_player = 2;
		}
		else
		{
			print_shots_table(shots_table_p2, current_player);
			shoot_shot(initial_placement_p1, shots_table_p2, current_player);
			print_shots_table(shots_table_p2, current_player);
			victory = check_victory(shots_table_p2, current_player);
			printf("\n\n\n\n\n");
			current_player = 1;
		}
	}
	return (0);
}