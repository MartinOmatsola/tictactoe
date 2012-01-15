#include <stdio.h>
#include <string.h>
#include "decider.h"

static char layout[3][3];

int main()
{
	int x, y, count, done = 1;
	char *player;
	char c;
	extern void show_board();
	
	printf("\n\n************************************\n");
	printf("| WELCOME TO CLASSIC X AND O       |\n");
	printf("| Developed by Martin O.           |\n");
	printf("************************************\n\n");
	game_init();
	show_board();
	count = 0;
	while(done) {
		if (count % 2 == 0) {
			player = "player 1";
			c = 'x';
		}
		else {
			player = "player 2";
			c = 'o';
		}
		printf("%s enter row # [0, 1, 2]: ", player);
		scanf("%d", &x);
		printf("%s enter column # [0, 1, 2]: ", player);
		scanf("%d", &y);
		
		if (layout[x][y] == '\0') {
			layout[x][y] = c;
			if (check_winner(x, y, c)){
				printf("\n\n%s WINS !!!\n\n", player);
				done = 0;
			}
		}
		else { 
			printf("\nOops. That spot is already taken. Try another spot\n");
			continue;
		}
		show_board();
		count++;
	}
	return (0);
}

/*
 * Displays current game status
 */
void show_board()
{	
	int i, j;
	for (i = 0;i < 3; i++) {
		for (j = 0;j < 3; j++) {
			printf(" %c ", layout[i][j]);
			if (j != 2) 
				printf("|");
			if (j == 2 && i !=2)
				printf("\n-----------\n");
		}
	}
	printf("\n\n");
}
