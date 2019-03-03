// Gokhan Has - 161044067
// CSE 102 - HW08 - part1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
	
	S,M,T,P,B,E
	/* E means empty, it has only data number. */
} block_type;


typedef struct {
	
	char text[10];
	int data;
	block_type type;
	int pos_x;
	int	pos_y;
	int	jump_x;
	int jump_y;
} block;
/* Defining struct type */

/***************** Defining Functions ***********************/

int to_dice();
void str_copy(char *str1, char *str2);
void initialize_board(block board[][10]);
void print_board(block board[][10]);
int single_player_game(block board[][10],int move_counter,int blockNo,int pos_x,int pos_y,int control,int exDiceNumber);
int play_game_2_players();
void find_location(block board[][10], int data, int *x, int *y);

/************************************************************/

int main(){

	srand(time(NULL)); /* It is necessary to diceNumber */
	int move_counter=0,blockNo=1,pos_x=9,pos_y=9,exDiceNumber=0; /* They specify the starting position. */
	int selection;
	
	block board[10][10];
	initialize_board(board);
	print_board(board);
	/* Initializing and printing board. */
	
	printf("\n1. Single Player\n");
	printf("2. Play Game With 2 Players\n");
	printf("Your Choose > "); scanf("%d",&selection);
	printf("\n");
	/* It is a menu.Users can choose 1 or 2. */
	
	switch(selection){

		case 1: single_player_game(board,move_counter,blockNo,pos_x,pos_y,1,exDiceNumber); break;
		case 2: play_game_2_players(); break;
		default: printf("You entered wrong number !!!\n");
	}
	
	return 0;
}

/************************************************************/

void initialize_board(block board[][10]){

	int i,j,k;
	/* k = data number */
	k=1;
	for(i=9; i>=0; i-=2){
		for(j=9;j>=0;j--){
			/* In this loop, the number of rows starts at 9 and goes to 7,5,3,1. */
			str_copy(board[i][j].text," "); /* This will be used in the print function. */
			board[i][j].data = k;
			board[i][j].type = E; /* First, type E is assigned. This will be fixed. */
			board[i][j].pos_x = i;
			board[i][j].pos_y = j;
			board[i][j].jump_x = i;
			board[i][j].jump_y = j-1;

			if(j == 0){
				board[i][j].jump_x = i-1;
				board[i][j].jump_y = j;
				/* If it comes to the line, an upper row is assigned. */
			}

			k++;	
		}
		k = k + 10;
	}


	k=11;
	for(i=8; i>=0; i-=2){
		for(j=0; j<10; j++){
			/* In this loop, the number of rows starts at 8 and goes to 6,4,2,0. */
			str_copy(board[i][j].text," "); /* This will be used in the print function. */
			board[i][j].data = k;
			board[i][j].type = E; /* First, type E is assigned. This will be fixed. */
			board[i][j].pos_x = i;
			board[i][j].pos_y = j;
			board[i][j].jump_x = i;
			board[i][j].jump_y = j+1;

			if(j == 9){
				if(i==0)
					break; /* can not go up from the first line. (board[0][j]) */

				else{
					board[i][j].jump_x = i-1;
					board[i][j].jump_y = j;
					/* If it comes to the line, an upper row is assigned. */
				}
			}
			k++;	
		}
		k = k + 10;
	}

	/* Exception cases are assigned one by one. */
	
	str_copy(board[9][9].text,"1(Start)"); 
	str_copy(board[9][4].text,"S{1}");    board[9][4].type = S;  board[9][4].jump_x=9;  board[9][4].jump_y=9;
	str_copy(board[9][3].text,"M{11}");   board[9][3].type = M;  board[9][3].jump_x=8;  board[9][3].jump_y=0;
	str_copy(board[8][2].text,"P");       board[8][2].type = P;	 board[8][2].jump_x=8;  board[8][2].jump_y=2;
	str_copy(board[8][6].text,"M{28}");   board[8][6].type = M;  board[8][6].jump_x=7;  board[8][6].jump_y=2;
	str_copy(board[7][1].text,"B");       board[7][1].type = B;  board[7][1].jump_x=6;  board[7][1].jump_y=3;
	str_copy(board[7][5].text,"S{12}");   board[7][5].type = S;  board[7][5].jump_x=8;  board[7][5].jump_y=1;
	str_copy(board[6][1].text,"M{52}");   board[6][1].type = M;  board[6][1].jump_x=4;  board[6][1].jump_y=1;
	str_copy(board[6][5].text,"B");       board[6][5].type = B;  board[6][5].jump_x=5;  board[6][5].jump_y=9;
	str_copy(board[6][9].text,"T");       board[6][9].type = T;  board[6][9].jump_x=6;  board[6][9].jump_y=4;
	str_copy(board[5][0].text,"B");       board[5][0].type = B;  board[5][0].jump_x=4;  board[5][0].jump_y=4;
	str_copy(board[5][2].text,"P");       board[5][2].type = P;  board[5][2].jump_x=5;  board[5][2].jump_y=2;
	str_copy(board[5][5].text,"S{22}");   board[5][5].type = S;  board[5][5].jump_x=7;  board[5][5].jump_y=8;
	str_copy(board[4][3].text,"T");       board[4][3].type = T;  board[4][3].jump_x=5;  board[4][3].jump_y=1;
	str_copy(board[4][6].text,"M{77}");   board[4][6].type = M;  board[4][6].jump_x=2;  board[4][6].jump_y=6;
	str_copy(board[4][9].text,"S{44}");   board[4][9].type = S;  board[4][9].jump_x=5;  board[4][9].jump_y=6;
	str_copy(board[3][1].text,"M{77}");   board[3][1].type = M;  board[3][1].jump_x=2;  board[3][1].jump_y=6;
	str_copy(board[3][4].text,"B");       board[3][4].type = B;  board[3][4].jump_x=2;  board[3][4].jump_y=0;
	str_copy(board[3][7].text,"S{52}");   board[3][7].type = S;  board[3][7].jump_x=4;  board[3][7].jump_y=1;
	str_copy(board[2][2].text,"S{68}");   board[2][2].type = S;  board[2][2].jump_x=3;  board[2][2].jump_y=2;
	str_copy(board[2][5].text,"M{83}");   board[2][5].type = M;  board[2][5].jump_x=1;  board[2][5].jump_y=7;
	str_copy(board[2][8].text,"T");       board[2][8].type = T;  board[2][8].jump_x=2;  board[2][8].jump_y=3;
	str_copy(board[1][1].text,"M{94}");   board[1][1].type = M;  board[1][1].jump_x=0;  board[1][1].jump_y=3;
	str_copy(board[1][5].text,"P");       board[1][5].type = P;  board[1][5].jump_x=1;  board[1][5].jump_y=5;
	str_copy(board[1][8].text,"B");       board[1][8].type = B;  board[1][8].jump_x=1;  board[1][8].jump_y=3;
	str_copy(board[0][2].text,"T");       board[0][2].type = T;  board[0][2].jump_x=1;  board[0][2].jump_y=2;
	str_copy(board[0][7].text,"S{72}");   board[0][7].type = S;  board[0][7].jump_x=2;  board[0][7].jump_y=1;
	str_copy(board[0][8].text,"S{56}");   board[0][8].type = S;  board[0][8].jump_x=4;  board[0][8].jump_y=5;
	str_copy(board[0][9].text,"100(Finish)"); 
}

void print_board(block board[][10]){

	int i,j;

	for(i=0;i<10;i++){
		for(j=0;j<10;j++){

			/* If the string is empty, it does not contain any letters. (S,M,P,T,B) */
			if(board[i][j].text[0] == ' '){
				printf("%10d ",board[i][j].data); /* Just write the number. */
			}
			/* !! Note : It would be better if the terminal was made full size !! */
			else{
				printf("%10s ",board[i][j].text);
			}
		}
		printf("\n");
	}
}

int single_player_game(block board[][10],int move_counter,int blockNo,int pos_x,int pos_y,int control,int exDiceNumber){

	int diceNumber;
	int x,y;
	
	diceNumber = to_dice(); /* to dice */
	control = blockNo - exDiceNumber; /* If the player comes in type P, it will be used.*/
	
	if(blockNo == 100){
		return move_counter; /* Checks whether the game is finished. */
	}

	exDiceNumber = diceNumber;
	if(blockNo + diceNumber > 100){
		move_counter++;
		single_player_game(board,move_counter,blockNo,pos_x,pos_y,control,exDiceNumber);
		/* If it is greater than 100, the function is called again. */
	}
	
	
	else if(board[pos_x][pos_y].type == P){
		printf("**PPPPP**\n");
		move_counter += 1;
		/* If the type is P, the number of moves is increased by 1 because one hand is expected. */
		blockNo = control;
		find_location(board,blockNo,&x,&y);
		/* Then the dice are discarded and the new block location is determined. */
		printf("Dice Number: %d\nBlockNo: %d\nmove_counter: %d\n\n",diceNumber,blockNo,move_counter);
		single_player_game(board,move_counter,blockNo,x,y,control,exDiceNumber);
	}

	else if(board[pos_x][pos_y].type == E){
		blockNo += diceNumber; 
		/* If type is E, it goes to the new block location and calls the function again. */
		find_location(board,blockNo,&x,&y);
		move_counter++;
		printf("Dice Number: %d\nBlockNo: %d\nmove_counter: %d\n\n",diceNumber,blockNo,move_counter);
		single_player_game(board,move_counter,blockNo,x,y,control,exDiceNumber);
	}

	else{
		move_counter++;
		x = board[pos_x][pos_y].jump_x;
		y = board[pos_x][pos_y].jump_y;
		/* Other types go to jump_x and jump_y locations. */
		blockNo = board[x][y].data;
		/* The data for the new location is assign to blockNo. */
		printf("Dice Number: %d\nBlockNo: %d\nmove_counter: %d\n\n",diceNumber,blockNo,move_counter);
		single_player_game(board,move_counter,blockNo,x,y,control,exDiceNumber);
	}
}

int play_game_2_players(){

	int player1,player2;
	int move_counter=0,blockNo=1,pos_x=9,pos_y=9,control=1,exDiceNumber=0;
	block board[10][10];
	
	initialize_board(board);
	
	printf("\n\n********** Player 1 **********\n\n");
	player1 = single_player_game(board,move_counter,blockNo,pos_x,pos_y,control,exDiceNumber);
	/* The number of moves for player 1 is found. */

	move_counter=0,blockNo=1,pos_x=9,pos_y=9;
	initialize_board(board);

	printf("\n\n********** Player 2 **********\n\n");
	player2 = single_player_game(board,move_counter,blockNo,pos_x,pos_y,control,exDiceNumber);
	/* The number of moves for player 2 is found. */

	if(player1 <= player2)
		printf("\nWinner : Player 1.\n");
	else if(player2 < player1)
		printf("\nWinner : Player 2.\n");

	/* If the number of moves is the same as the first player starts, 
	   the first player is deemed to be the winner. */

	/* !! NOTE : The status of any player's type P has been 
	 			 checked in the single_player_game_function. */

	return 0;
}

int to_dice(){

	int diceNumber;
	diceNumber = rand() % 6;
	
	if(diceNumber == 0){
		diceNumber = 6;
	}
	/* the dice are thrown and returning diceNumber. */
	return diceNumber;
}

void str_copy(char *str1, char *str2){

	int i,str_len;
	/* Copying the second string (str2) to first string (str1). */
	str_len=0;
	while(str2[str_len] != '\0')
		str_len++;

	for(i=0;i<str_len;i++){
		str1[i] = str2[i];
	}
	str1[str_len] = '\0';
}

void find_location(block board[][10], int data, int *x, int *y){

	*y = 0;
	/* There is a location according to the entered data in board[][10]. */
	if(data <= 10){
		*x = 9; 
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
	else if(data >= 11 && data <= 20){
		*x = 8; 
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
	else if(data >= 21 && data <= 30){
		*x = 7; 
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
	else if(data >= 31 && data <= 40){
		*x = 6; 
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
	else if(data >= 41 && data <= 50){
		*x = 5; 
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
	else if(data >= 51 && data <= 60){
		*x = 4; 
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
	else if(data >= 61 && data <= 70){
		*x = 3; 
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
	else if(data >= 71 && data <= 80){
		*x = 2; 
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
	else if(data >= 11 && data <= 90){
		*x = 1;  
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
	else if(data >= 91 && data <= 100){
		*x = 0;                              
		while(board[*x][*y].data != data){
			*y = *y + 1;
		}
	}
}
