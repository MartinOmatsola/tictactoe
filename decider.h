/*
 * structure used to decide winner
 */
 struct monitor {
	int count;
	int valid;
	char value;	 
 };
 
 void game_init();
 int check_winner(int x, int y, char c);
