// Gokhan Has - 161044067
// CSE 102 - HW05

#include <stdio.h>

/****** NOTE! : The cod was a bit long because it was not used recursive and another function ***********/
/************************************* Define Enum Types ************************************************/

typedef enum {

	white_man,
	black_man,
	white_king,
	black_king,
	empty

} piece;

typedef enum {

	white = 10,
	black = 20

} player;


// ************************************************************************************
/* *************************** Define Functions **************************************/

void init_board(piece board[][8]);
int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p);
int check_end_of_game(piece board[][8]);
void display_board(piece board[][8]);
void sample_game_1();
void sample_game_2();

// ************************************************************************************



void init_board(piece board[][8]){

	int i,j;
	piece new_board[][8] = { (empty),(empty),(empty),(empty),(empty),(empty),(empty),(empty),
							  (black_man),(black_man),(black_man),(black_man),(black_man),(black_man),(black_man),(black_man),
							  (black_man),(black_man),(black_man),(black_man),(black_man),(black_man),(black_man),(black_man),
							  (empty),(empty),(empty),(empty),(empty),(empty),(empty),(empty),
							  (empty),(empty),(empty),(empty),(empty),(empty),(empty),(empty),
							  (white_man),(white_man),(white_man),(white_man),(white_man),(white_man),(white_man),(white_man),
							  (white_man),(white_man),(white_man),(white_man),(white_man),(white_man),(white_man),(white_man),
							  (empty),(empty),(empty),(empty),(empty),(empty),(empty),(empty) };

    /* This function makes the board by using extra piece board. */
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){

			board[i][j] = new_board[i][j];
		}
	}
}


int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p){

	int i,j,n=0,bos_kontrol=0;

	if(p == 10){ /* If the white is selected  */

		if(board[from_x][from_y] == black_man || board[from_x][from_y] == black_king){
			return (-1);
			/* Returns -1, if the user has selected a piece that does not belong to him. */
		}

		else if (board[to_x][to_y] != empty){
			return (-2);
			/* Returns -2, if there is no piece in the locality chosen by the user. */
		}

		else if(board[from_x][from_y] == white_man){ /* If the user selecs white_man */

			if(from_y == to_y && (from_x - to_x > 0)){ /* If you move vertically, so the white_man will move up. */
					
				if(board[from_x-1][from_y] == empty && from_x-1 == to_x){
					/* Moving without eating anything */ 
					board[from_x][from_y] = empty;
					board[from_x-1][from_y] = white_man;
					
					
					if(from_x-1 == 0){
						board[from_x-1][from_y] = white_king;
						/* Controls the state of being king */
					}

					return (1);
					/* Return 1, its means the moving is successful */
				}

				else if(board[from_x-1][from_y] == black_man || board[from_x-1][from_y] == black_king){ /* If there is an enemy piece in front of your piece */
																										/* Enemy is black for white */
					if((board[from_x-2][from_y] == empty) && (board[from_x-3][from_y] != black_man || board[from_x-3][from_y] != black_king) && to_x == from_x-2){
						/* If only one piece can be eaten and the selected location is equal to user's choise */
						/* This if block is control the x-2,x-3 location */
						board[from_x][from_y] = empty;
						board[from_x-1][from_y] = empty;
						board[from_x-2][from_y] = white_man;
						n++;
					
						if(from_x-2 == 0){
							board[from_x-2][from_y] = white_king;
							/* Controls the state of being king */
						}

						return (n);
						/* n will be returned as 1 */
					}

					else if((board[from_x-3][from_y] == black_man || board[from_x-3][from_y] == black_king) && board[from_x-4][from_y] == empty && to_x == from_x-4){
						/* If there is an enemy in x-3 and the back of the enemy is empty, 2 pieces will be eaten. */
						board[from_x][from_y] = empty;
						board[from_x-1][from_y] = empty;
						board[from_x-3][from_y] = empty;
						board[from_x-4][from_y] = white_man;
						n=2;

						if(from_x-4 == 0){
							board[from_x-4][from_y] = white_king;
							/* Controls the state of being king */
						}

						return (n);
					}

					else if((board[from_x-5][from_y] == black_man || board[from_x-5][from_y] == black_king) && board[from_x-6][from_y] == empty && to_x == from_x-6){
						/* If x-5 is also enemy piece and be x-6 is empty in a total of 3 enemies will be eaten.  */
						board[from_x][from_y] = empty;
						board[from_x-1][from_y] = empty;
						board[from_x-3][from_y] = empty;
						board[from_x-5][from_y] = empty;
						board[from_x-6][from_y] = white_man;
						n=3;

						if(from_x-6 == 0){
							board[from_x-6][from_y] = white_king;
							/* Controls the state of being king */
						}

						return (n);
					}

					else{
						return (-2);
					}
					/* Other cases will return -2 because it will be wrong for vertical motion. */
				}

				else{
					return (-2);
				/* In this case, we have our own pieces. So it can not move. */
				}			
			}

			else if(from_x == to_x && (from_y - to_y > 0)){ /* If the piece is moving to the left */

				if(board[from_x][from_y-1] == empty && to_y == from_y-1){
					/* Moving without eating anything */ 
					board[from_x][from_y] = empty;
					board[from_x][from_y-1] = white_man;
				}

				else if(board[from_x][from_y-1] == black_man || board[from_x][from_y-1] == black_king){ /* If there is an enemy piece on your left */

					if((board[from_x][from_y-2] == empty) && (board[from_x][from_y-3] != black_man || board[from_x][from_y-3] != black_king) && to_y == from_y-2){
						/* If only one enemy piece can be eaten */
						board[from_x][from_y] = empty;
						board[from_x][from_y-1] = empty;
						board[from_x][from_y-2] = white_man;
						n++;

						return (n);
					}

					else if((board[from_x][from_y-2] == empty) && (board[from_x][from_y-4] == empty) 
						&& (board[from_x][from_y-5] != black_man || board[from_x][from_y-5] != black_king) 
						&& to_y == from_y-4 && (board[from_x][from_y-3] == black_man || board[from_x][from_y-3] == black_king)){
						/* If the piece is moving to the left and the conditions are satisfied to eat 2 pieces */
						/* The conditions are y-4 empty, y-3 black piece */
						board[from_x][from_y] = empty;
						board[from_x][from_y-1] = empty;
						board[from_x][from_y-3] = empty;
						board[from_x][from_y-4] = white_man;
						n = 2;

						return (n);
					}

					else if((board[from_x][from_y-2] == empty) && (board[from_x][from_y-4] == empty) && (board[from_x][from_y-6] == empty)
						&& to_y == from_y-6 && (board[from_x][from_y-5] == black_man || board[from_x][from_y-5] == black_king)){
						/* If 3 pieces can be eaten, this else if block works. */
						/* The conditions are y-6 empty and y-5 black piece */
						board[from_x][from_y] = empty;
						board[from_x][from_y-1] = empty;
						board[from_x][from_y-3] = empty;
						board[from_x][from_y-5] = empty;
						board[from_x][from_y-6] = white_man;
						n = 3;

						return (n);
					}

					else{
						return (-2);
						/* Other cases will return -2 because it will be wrong for left motion. */
					}
				}

				else{
					return (-2);
					/* In this case, we have our own pieces. So it can not move. */
				}
			}

			else if(from_x == to_x && (from_y - to_y < 0)){ /* If the piece is moving to the right */

				if(board[from_x][from_y+1] == empty && to_y == from_y+1){
					/* Moving without eating anything */ 
					board[from_x][from_y] = empty;
					board[from_x][from_y+1] = white_man;
				}

				else if(board[from_x][from_y+1] == black_man || board[from_x][from_y+1] == black_king){ /* If there is an enemy piece on your right */

					if((board[from_x][from_y+2] == empty) && (board[from_x][from_y+3] != black_man || board[from_x][from_y+3] != black_king) && to_y == from_y+2){
  						/* If only one enemy piece can be eaten */
						board[from_x][from_y] = empty;
						board[from_x][from_y+1] = empty;
						board[from_x][from_y+2] = white_man;
						n++;

						return (n);
					}

					else if((board[from_x][from_y+2] == empty) && (board[from_x][from_y+4] == empty) 
						&& (board[from_x][from_y+5] != black_man || board[from_x][from_y+5] != black_king) 
						&& to_y == from_y+4 && (board[from_x][from_y+3] == black_man || board[from_x][from_y+3] == black_king)){
						/* If the piece is moving to the right and the conditions are satisfied to eat 2 pieces */
						/* The conditions are y+4 empty, y+3 black piece */
						board[from_x][from_y] = empty;
						board[from_x][from_y+1] = empty;
						board[from_x][from_y+3] = empty;
						board[from_x][from_y+4] = white_man;
						n = 2;

						return (n);
					}

					else if((board[from_x][from_y+2] == empty) && (board[from_x][from_y+4] == empty) && (board[from_x][from_y+6] == empty)
						&& to_y == from_y+6 && (board[from_x][from_y+5] == black_man || board[from_x][from_y+5] == black_king)){
						/* If 3 pieces can be eaten, this else if block works. */
						/* The conditions are y+6 empty and y+5 black piece */
						board[from_x][from_y] = empty;
						board[from_x][from_y+1] = empty;
						board[from_x][from_y+3] = empty;
						board[from_x][from_y+5] = empty;
						board[from_x][from_y+6] = white_man;
						n = 3;

						return (n);
					}

					else{
						return (-2);
						/* Other cases will return -2 because it will be wrong for right motion. */
					}
				}

				else{
					return (-2);
					/* In this case, we have our own pieces. So it can not move. */
				}
			}
		}

		else if(board[from_x][from_y] == white_king){ /* If the user selected white_king */

			if(from_y == to_y){ /* If you move vertically */

				if(from_x - to_x > 0){ /* If white_king moves up */

					for(i=from_x;i>=to_x;i--){ /* Loops are used because kings can move differently. */

						if( (board[i][from_y] == black_man || board[i][from_y] == black_king) && ( board[i-1][from_y] == empty)
							&& (board[i+1][from_y] == empty || board[i+1][from_y] == white_man || board[i+1][from_y] == white_king)){
							/* This if block controls the pieces which are eaten */
							board[i][from_y]= empty;
							n++;
						}

						else if(board[i][from_y] == empty){
							bos_kontrol--;
							/* bos_kontrol starts 0 and in this block assign -1,it checks empty location */
							/* It checks whether the back of the piece is empty. */
						}
					}
					if(n!=0){ /* If no piece is eaten */
						board[to_x][from_y] = white_king;
						board[from_x][from_y] = empty;
					}
					else if(n == 0 && bos_kontrol != 0 ){
						board[to_x][to_y] = white_king;
						board[from_x][from_y] = empty;
						/* if the piece is eaten and there is no other piece behind or in front of the piece */
					}
					else{
						return (-2);
						/* Otherwise, the wrong move was made. */
					}
				}

				else if(from_x - to_x < 0){ /* If white_king moves down */

					for(i=from_x;i<=to_x;i++){ /* Loops are used because kings can move differently. */

						if( (board[i][from_y] == black_man || board[i][from_y] == black_king) && ( board[i+1][from_y] == empty) && (board[i-1][from_y] == empty || board[i-1][from_y] == white_man || board[i-1][from_y] == white_king)){
							/* This if block controls the pieces which are eaten */
							board[i][from_y]= empty;
							n++;
						}

						else if(board[i][from_y] == empty){
							bos_kontrol--;
							/* bos_kontrol starts 0 and in this block assign -1,it checks empty location */
							/* It checks whether the back of the piece is empty. */
						}
					}
					if(n != 0){ /* If no piece is eaten */
						board[to_x][from_y] = white_king;
						board[from_x][from_y] = empty;
					}
					
					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = white_king;
						board[from_x][from_y] = empty;
						/* if the piece is eaten and there is no other piece behind or in front of the piece */
					}

					else{
						return (-2);
						/* Otherwise, the wrong move was made. */
					}
				}
			}

			else if(from_x == to_x){ /* If the king is moving horizontally */

				if(from_y - to_y > 0){ /* If the king is going to the left */

					for(j = from_y;j >= to_y; j--){

						if( (board[from_x][j] == black_man || board[from_x][j] == black_king) && (board[from_x][j-1] == empty) 
							&& (board[from_x][j+1] == empty || board[from_x][j+1] == white_man || board[from_x][j+1] == white_king) ){
							/* This if block controls the pieces which are eaten */
							board[from_x][j] = empty;
							n++;
						}

						else if(board[from_x][j] == empty){
							bos_kontrol--;
							/* bos_kontrol starts 0 and in this block assign -1,it checks empty location */
							/* It checks whether the back of the piece is empty. */
						}
					}

					if(n != 0){ /* If no piece is eaten */
						board[from_x][to_y] = white_king;
						board[from_x][from_y] = empty;
					}

					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = white_king;
						board[from_x][from_y] = empty;
						/* if the piece is eaten and there is no other piece behind or in front of the piece */
					}
					
					else{
						return (-2);
						/* Otherwise, the wrong move was made. */
					}
				}

				else if(from_y-to_y < 0){ /* If the king is going to the right */

					for(j = from_y;j <= to_y; j++){

						if( (board[from_x][j] == black_man || board[from_x][j] == black_king) && (board[from_x][j+1] == empty)
						 && (board[from_x][j-1] == empty || board[from_x][j-1] == white_man || board[from_x][j+1] == white_king) ){
							/* This if block controls the pieces which are eaten */
							board[from_x][j] = empty;
							n++;
						}

						else if(board[from_x][j] == empty){
							bos_kontrol--;
							/* bos_kontrol starts 0 and in this block assign -1,it checks empty location */
							/* It checks whether the back of the piece is empty. */
						}
					}

					if(n != 0){ /* If no piece is eaten */
						board[from_x][to_y] = white_king;
						board[from_x][from_y] = empty;
					}

					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = white_king;
						board[from_x][from_y] = empty;
						/* if the piece is eaten and there is no other piece behind or in front of the piece */
					}

					else{
						return (-2);
						/* Otherwise, the wrong move was made. */
					}
				}
			}
		}
	}
// ***********************************************************************************************************************************************
/******** IF THE USER SELECT BLACK PIECE ******************/
/**** Processes applied for white are applied in black ****/
/**** Only vertical movement is different.Because black starts from the top *****/	
	

	else if(p == 20){

		if(board[from_x][from_y] == white_man || board[from_x][from_y] == white_king){
			return (-1);
			/* Returns -1, if the user has selected a piece that does not belong to him. */
		}

		else if (board[to_x][to_y] != empty){
			return (-2);
			/* Returns -2, if there is no piece in the locality chosen by the user. */
		}

		else if(board[from_x][from_y] == black_man){ /* If the user selected black_man */

			if(from_y == to_y && (from_x - to_x < 0)){ /* If you move vertically, so the black_man will move down. */

				if(board[from_x+1][from_y] == empty && from_x+1 == to_x){
					/* Moving without eating anything */ 
					board[from_x][from_y] = empty;
					board[from_x+1][from_y] = black_man;

					if(from_x+1 == 7){ /* Controls the state of being king */
						board[from_x+1][from_y] = black_king;
					}

					return (1); /* Return 1, its means the moving is successful */
				}

				else if(board[from_x+1][from_y] == white_man || board[from_x+1][from_y] == white_king){	 /* If there is an enemy piece in front of your piece */
																										/* Enemy is white for black */

					if((board[from_x+2][from_y] == empty) && (board[from_x+3][from_y] != white_man || board[from_x+3][from_y] != white_king) && to_x == from_x+2){
						/* If only one piece can be eaten and the selected location is equal to user's choise */
						/* This if block is control the x+2,x+3 location */
						board[from_x][from_y] = empty;
						board[from_x+1][from_y] = empty;
						board[from_x+2][from_y] = black_man;
						n++;
					
						if(from_x+2 == 7){ /* Controls the state of being king */
							board[from_x+2][from_y] = black_king;
						}

						return n;
					}

					else if((board[from_x+3][from_y] == white_man || board[from_x+3][from_y] == white_king) && board[from_x+4][from_y] == empty && to_x == from_x+4){
						/* If there is an enemy in x+3 and the back of the enemy is empty, 2 pieces will be eaten. */
						board[from_x][from_y] = empty;
						board[from_x+1][from_y] = empty;
						board[from_x+3][from_y] = empty;
						board[from_x+4][from_y] = black_man;
						n=2;

						if(from_x+4 == 7){ /* Controls the state of being king */
							board[from_x+4][from_y] = black_king;
						}

						return n;
					}

					else if((board[from_x+5][from_y] == white_man || board[from_x+5][from_y] == white_king) && board[from_x+6][from_y] == empty && to_x == from_x+6){
						/* If x+5 is also enemy piece and be x+6 is empty in a total of 3 enemies will be eaten.  */
						board[from_x][from_y] = empty;
						board[from_x+1][from_y] = empty;
						board[from_x+3][from_y] = empty;
						board[from_x+5][from_y] = empty;
						board[from_x+6][from_y] = black_man;
						n=3;

						if(from_x+6 == 7){ /* Controls the state of being king */
							board[from_x+6][from_y] = black_king;
						}

						return (n);
					}

					else{
						return (-2);
						/* Other cases will return -2 because it will be wrong for vertical motion. */
					}
				}

				else{
					return (-2);
					/* In this case, we have our own pieces. So it can not move. */
				}
			}

			else if(from_x == to_x && (from_y - to_y > 0)){ /* If the piece moves left */

				if(board[from_x][from_y-1] == empty && to_y == from_y-1){
					/* Moving without eating anything */ 
					board[from_x][from_y] = empty;
					board[from_x][from_y-1] = black_man;
				}

				else if(board[from_x][from_y-1] == white_man || board[from_x][from_y-1] == white_king){ /* If there is an enemy piece on your left */

					if((board[from_x][from_y-2] == empty) && 
						(board[from_x][from_y-3] != white_man || board[from_x][from_y-3] != white_king) && to_y == from_y-2){
						/* If only one enemy piece can be eaten */
						board[from_x][from_y] = empty;
						board[from_x][from_y-1] = empty;
						board[from_x][from_y-2] = black_man;
						n++;

						return (n);
					}

					else if((board[from_x][from_y-2] == empty) && (board[from_x][from_y-4] == empty) 
						&& (board[from_x][from_y-5] != white_man || board[from_x][from_y-5] != white_king) 
						&& to_y == from_y-4 && (board[from_x][from_y-3] == white_man || board[from_x][from_y-3] == white_king)){
						/* If the piece is moving to the left and the conditions are satisfied to eat 2 pieces */
						/* The conditions are y-4 empty, y-3 black piece */
						board[from_x][from_y] = empty;
						board[from_x][from_y-1] = empty;
						board[from_x][from_y-3] = empty;
						board[from_x][from_y-4] = black_man;
						n = 2;

						return (n);
					}

					else if((board[from_x][from_y-2] == empty) && (board[from_x][from_y-4] == empty) && (board[from_x][from_y-6] == empty)
						&& to_y == from_y-6 && (board[from_x][from_y-5] == white_man || board[from_x][from_y-5] == white_king)){
						/* If 3 pieces can be eaten, this else if block works. */
						/* The conditions are y-6 empty and y-5 black piece */
						board[from_x][from_y] = empty;
						board[from_x][from_y-1] = empty;
						board[from_x][from_y-3] = empty;
						board[from_x][from_y-5] = empty;
						board[from_x][from_y-6] = black_man;
						n = 3;

						return (n);
					}

					else{
						return (-2); /* Other cases will return -2 because it will be wrong for left motion. */
					}
				}

				else{
					return (-2); /* In this case, we have our own pieces. So it can not move. */
				}
			}

			else if(from_x == to_x && (from_y - to_y < 0)){ /* If the piece moves right */

				if(board[from_x][from_y+1] == empty && to_y == from_y+1){
					/* Moving without eating anything */ 
					board[from_x][from_y] = empty;
					board[from_x][from_y+1] = black_man;
				}

				else if(board[from_x][from_y+1] == white_man || board[from_x][from_y+1] == white_king){ /* If there is an enemy piece on your right */

					if((board[from_x][from_y+2] == empty) && (board[from_x][from_y+3] != white_man || board[from_x][from_y+3] != white_king) && to_y == from_y+2){
						/* If only one enemy piece can be eaten */
						board[from_x][from_y] = empty;
						board[from_x][from_y+1] = empty;
						board[from_x][from_y+2] = black_man;
						n++;

						return (n);
					}

					else if((board[from_x][from_y+2] == empty) && (board[from_x][from_y+4] == empty) 
						&& (board[from_x][from_y+5] != white_man || board[from_x][from_y+5] != white_king) 
						&& to_y == from_y+4 && (board[from_x][from_y+3] == white_man || board[from_x][from_y+3] == white_king)){
						/* If the piece is moving to the right and the conditions are satisfied to eat 2 pieces */
						/* The conditions are y+4 empty, y+3 black piece */
						board[from_x][from_y] = empty;
						board[from_x][from_y+1] = empty;
						board[from_x][from_y+3] = empty;
						board[from_x][from_y+4] = black_man;
						n = 2;

						return (n);
					}

					else if((board[from_x][from_y+2] == empty) && (board[from_x][from_y+4] == empty) && (board[from_x][from_y+6] == empty)
						&& to_y == from_y+6 && (board[from_x][from_y+5] == white_man || board[from_x][from_y+5] == white_king)){
						/* If 3 pieces can be eaten, this else if block works. */
						/* The conditions are y+6 empty and y+5 black piece */
						board[from_x][from_y] = empty;
						board[from_x][from_y+1] = empty;
						board[from_x][from_y+3] = empty;
						board[from_x][from_y+5] = empty;
						board[from_x][from_y+6] = black_man;
						n = 3;

						return (n);
					}

					else{
						return (-2); /* Other cases will return -2 because it will be wrong for right motion. */
					}
				}

				else{
					return (-2); /* In this case, we have our own pieces. So it can not move. */
				}
			}
		}

		else if(board[from_x][from_y] == black_king){ /* If the user selected black_king */

			if(from_y == to_y){ /* If you move vertically */

				if(from_x - to_x > 0){ /* If black_king moves up */

					for(i=from_x;i>=to_x;i--){ /* Loops are used because kings can move differently. */

						if( (board[i][from_y] == white_man || board[i][from_y] == white_king) && ( board[i-1][from_y] == empty) && (board[i+1][from_y] == empty || board[i+1][from_y] == black_man || board[i+1][from_y] == black_king)){
							/* This if block controls the pieces which are eaten */
							board[i][from_y]= empty;
							n++;
						}

						else if(board[i][from_y] == empty){
							bos_kontrol--;
							/* bos_kontrol starts 0 and in this block assign -1,it checks empty location */
							/* It checks whether the back of the piece is empty. */
						}
					}
					if(n!=0){ /* If no piece is eaten */
						board[to_x][from_y] = black_king;
						board[from_x][from_y] = empty;
					}
					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = black_king;
						board[from_x][from_y] = empty;
						/* if the piece is eaten and there is no other piece behind or in front of the piece */
					}
					else
						return (-2); /* Otherwise, the wrong move was made. */
				}

				else if(from_x - to_x < 0){  /* If black_king moves down */

/********** NOTE ! : Comments are not written again because the processes are the same. *************/
					
					for(i=from_x;i<=to_x;i++){

						if( (board[i][from_y] == white_man || board[i][from_y] == white_king) 
							&& ( board[i+1][from_y] == empty) && (board[i-1][from_y] == empty || board[i-1][from_y] == black_man || board[i-1][from_y] == black_king)){

							board[i][from_y]= empty;
							n++;
						}

						else if(board[i][from_y] == empty){
							bos_kontrol--;
						}
					}
					if(n != 0){
						board[to_x][from_y] = black_king;
						board[from_x][from_y] = empty;
					}
					
					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = black_king;
						board[from_x][from_y] = empty;
					}

					else
						return (-2);
				}
			}

			else if(from_x == to_x){ /* If the king is moving horizontally */

				if(from_y - to_y > 0){ /* If the king is going to the left */

					for(j = from_y;j >= to_y; j--){

						if( (board[from_x][j] == white_man || board[from_x][j] == white_king) && (board[from_x][j-1] == empty) && (board[from_x][j+1] == empty || board[from_x][j+1] == black_man || board[from_x][j+1] == black_king) ){

							board[from_x][j] = empty;
							n++;
						}

						else if(board[from_x][j] == empty){
							bos_kontrol--;
						}
					}

					if(n != 0){
						board[from_x][to_y] = black_king;
						board[from_x][from_y] = empty;
					}

					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = black_king;
						board[from_x][from_y] = empty;
					}
					
					else{
						return (-2);
					}
				}

				else if(from_y-to_y < 0){ /* If the king is going to the right */

					for(j = from_y;j <= to_y; j++){

						if( (board[from_x][j] == white_man || board[from_x][j] == white_king) && (board[from_x][j+1] == empty) && (board[from_x][j-1] == empty || board[from_x][j-1] == black_man || board[from_x][j+1] == black_king) ){

							board[from_x][j] = empty;
							n++;
						}

						else if(board[from_x][j] == empty){
							bos_kontrol--;
						}
					}

					if(n != 0){
						board[from_x][to_y] = black_king;
						board[from_x][from_y] = empty;
					}

					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = black_king;
						board[from_x][from_y] = empty;
					}

					else{
						return (-2);
					}
				}
			}
		}
	}
}

int check_end_of_game(piece board[][8]){

	int i,j;
	int blackCount=0,whiteCount=0;

	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j] == black_man || board[i][j] == black_king){
				blackCount++;
			}

			else if(board[i][j] == white_man || board[i][j] == white_king){
				whiteCount++;
			}
		}
	}

	/* This function checks the board and print the result */
	if(blackCount == 0 && whiteCount != 0){
		printf("Winner : White\n");
		return (white);
	}

	else if(whiteCount == 0 && blackCount != 0){
		printf("Winner : Black\n");
		return (black);
	}

	else{
		printf("Game Continues...\n");
		return (-1);
	}
}


void display_board(piece board[][8]){

	int i,j;
	/* Printing board state */
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j] == white_man)
				printf("w");
			else if(board[i][j] == black_man)
				printf("b");
			else if(board[i][j] == white_king)
				printf("W");
			else if(board[i][j] == black_king)
				printf("B");
			else if(board[i][j] == empty)
				printf("-");
		}
		printf("\n");
	}
}

void sample_game_1(){

	/* Game's video : https://www.youtube.com/watch?v=8dmpR8NdzK8  */
	piece board[8][8]; init_board(board);

	display_board(board);
    move(board,2,6,3,6,20); check_end_of_game(board); display_board(board);
    move(board,5,7,4,7,10); check_end_of_game(board); display_board(board);
    move(board,2,0,3,0,20); check_end_of_game(board); display_board(board);
    move(board,5,1,4,1,10); check_end_of_game(board); display_board(board);
    move(board,2,2,3,2,20); check_end_of_game(board); display_board(board);
    move(board,5,3,4,3,10); check_end_of_game(board); display_board(board);
    move(board,2,4,3,4,20); check_end_of_game(board); display_board(board);
    move(board,5,5,4,5,10); check_end_of_game(board); display_board(board);
    move(board,3,4,3,5,20); check_end_of_game(board); display_board(board);
    move(board,5,6,5,5,10); check_end_of_game(board); display_board(board);
    move(board,3,5,3,4,20); check_end_of_game(board); display_board(board);
    move(board,5,5,5,6,10); check_end_of_game(board); display_board(board);
    move(board,3,4,3,3,20); check_end_of_game(board); display_board(board);
    move(board,5,6,5,7,10); check_end_of_game(board); display_board(board);
    move(board,3,3,5,3,20); check_end_of_game(board); display_board(board);
    move(board,5,3,5,5,20); check_end_of_game(board); display_board(board);
    move(board,5,5,7,5,20); check_end_of_game(board); display_board(board);
    move(board,4,7,3,7,10); check_end_of_game(board); display_board(board);
    move(board,7,5,3,5,20); check_end_of_game(board); display_board(board);
    move(board,4,1,4,0,10); check_end_of_game(board); display_board(board);
    move(board,2,7,4,7,20); check_end_of_game(board); display_board(board);
    move(board,4,0,2,0,10); check_end_of_game(board); display_board(board);
    move(board,2,0,2,6,10); check_end_of_game(board); display_board(board);
    move(board,2,6,0,6,10); check_end_of_game(board); display_board(board);
    move(board,1,7,2,7,20); check_end_of_game(board); display_board(board);
    move(board,5,7,1,7,10); check_end_of_game(board); display_board(board);
    move(board,1,5,1,6,20); check_end_of_game(board); display_board(board);
    move(board,0,6,4,6,10); check_end_of_game(board); display_board(board);
    move(board,1,1,2,1,20); check_end_of_game(board); display_board(board);
    move(board,5,0,4,0,10); check_end_of_game(board); display_board(board);
    move(board,1,3,2,3,20); check_end_of_game(board); display_board(board);
    move(board,1,7,0,7,10); check_end_of_game(board); display_board(board);
    move(board,3,5,1,5,20); check_end_of_game(board); display_board(board);
    move(board,0,7,0,0,10); check_end_of_game(board); display_board(board);
    move(board,1,5,1,6,20); check_end_of_game(board); display_board(board);
    move(board,0,0,3,0,10); check_end_of_game(board); display_board(board);
    move(board,3,0,3,3,10); check_end_of_game(board); display_board(board);
    move(board,3,3,1,3,10); check_end_of_game(board); display_board(board);
    move(board,1,3,1,7,10); check_end_of_game(board); display_board(board);
    move(board,2,1,2,0,20); check_end_of_game(board); display_board(board);
    move(board,1,7,1,0,10); check_end_of_game(board); display_board(board);
    move(board,1,0,3,0,10); check_end_of_game(board); display_board(board);
}

void sample_game_2(){

	piece board[][8] = {(empty),(empty),(empty),(empty),(empty),(empty),(empty),(empty),
						(empty),(empty),(black_man),(black_man),(black_man),(black_man),(empty),(empty),
						(empty),(black_man),(black_man),(black_man),(black_man),(empty),(black_man),(black_man),
						(black_man),(black_man),(black_man),(empty),(empty),(black_man),(empty),(black_man),
						(empty),(empty),(white_man),(white_man),(white_man),(black_man),(white_man),(white_man),
						(white_man),(white_man),(white_man),(white_man),(white_man),(empty),(white_man),(white_man),
						(empty),(empty),(white_man),(white_man),(white_man),(white_man),(empty),(empty),
						(empty),(empty),(empty),(empty),(empty),(empty),(empty),(empty) };	


    display_board(board);
    move(board,5,1,4,1,10); check_end_of_game(board); display_board(board);
    move(board,3,1,5,1,20); check_end_of_game(board); display_board(board);
    move(board,4,3,3,3,10); check_end_of_game(board); display_board(board);
    move(board,4,5,4,1,20); check_end_of_game(board); display_board(board);
    move(board,3,3,3,1,10); check_end_of_game(board); display_board(board);
    move(board,3,1,1,1,10); check_end_of_game(board); display_board(board);
    move(board,1,2,1,0,20); check_end_of_game(board); display_board(board);
    move(board,5,3,4,3,10); check_end_of_game(board); display_board(board);
    move(board,5,1,5,5,20); check_end_of_game(board); display_board(board);
    move(board,5,5,7,5,20); check_end_of_game(board); display_board(board);
    move(board,4,3,3,3,10); check_end_of_game(board); display_board(board);
    move(board,2,3,4,3,20); check_end_of_game(board); display_board(board);
    move(board,5,6,5,5,10); check_end_of_game(board); display_board(board);
    move(board,7,5,4,5,20); check_end_of_game(board); display_board(board);
    move(board,4,6,4,0,10); check_end_of_game(board); display_board(board);
    move(board,4,0,0,0,10); check_end_of_game(board); display_board(board);
}

int main(){
	
	/* If you control the sample_game_2() function, please delete the comment line operator '//'. */
	sample_game_1();
	// sample_game_2();
}