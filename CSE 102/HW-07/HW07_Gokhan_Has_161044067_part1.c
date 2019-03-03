// Gokhan Has - 161044067
// CSE 102 - HW07 - part1

#include <stdio.h>

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
int move(piece board[][8],int arr[][20], int from_x, int from_y, int to_x, int to_y, player p,int Location, int moveLocation,int control);
int move_control(piece board[][8],player p,int from_x,int from_y, int arr[][20],int newMove,int move_num);
int check_end_of_game(piece board[][8]);
void display_board(piece board[][8]);
void sample_game_1();
void sample_game_2();
void zeroArray(int arr[][20]);

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

    /* Oyunun baslangici icin fonksiyonu tanimlama. */
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){

			board[i][j] = new_board[i][j];
		}
	}
}

int find_maxWay(int arr[][20])
{
	int i,j;
	int Location;
	int maxNum=0;
	int num=0;
	/* 20'ye 20 ornek bir cift boyutlu array olusturdum.
	   max capture icin hamleler bu arraylerde tutulacak.
	   Ornegın arrayin 0. boyutunda(arr[0][i]) 2 tas yiyebiliyor, 1. boyutunda
	   (arr[1][i]) 3 tas yiyebiliyorsa arr[1][i] isleme alinacak. */
	/* 20x20 keyfi verilmistir. 20 hamleyi gecmeyecegi dusunulmustur. */
	for(i=0; i<20; i++){
		
		j=0;
		num=0;
		while(arr[i][j]!=0){
			j++;
			num++;
		}
		/* Max yeme hangi boyuttaysa o bulunuyor ve isleme o alinacak. */
		if(maxNum<num){
			maxNum=num;
			Location=i;
		}	
	}
	j=0;
	return Location; /* max yemedeki arryin boyutunu return eder. */
}

int move(piece board[][8],int arr[][20], int from_x, int from_y, int to_x, int to_y, player p,int Location, int moveLocation,int control){
	
	int newMove=0;
	int move_num=0;
	int i=0,j=0;
	int n=0,bos_kontrol=0;
	
	if(p==10){ /* Eger beyaz tassa */
		
		if(board[from_x][from_y] == white_man){			
			/* Eger white_man ise */
			if(from_x==0){
				/* King olma durumunu kontrol eder. */
				board[from_x][from_y]=white_king;
				return 0;
			}

			if(board[to_x][to_y] == empty && to_y == from_y && to_x == from_x-1){
				// eger taş yeme durumu yoksa ve dikey hareket yapicaksa
				board[from_x][from_y] = empty;
				board[to_x][to_y] = white_man;
				
				if(from_x-1 == 0){
					board[from_x-1][from_y] = white_king;
					/* Hareket sonrasi king olma durumunu kontrol eder. */
				}
				
				return 0;
			}

			else if(board[to_x][to_y] == empty && to_y == from_y+1 && to_x == from_x){
				// eger taş yeme durumu yoksa ve saga hareket yapicaksa
				board[from_x][from_y] = empty;
				board[to_x][to_y] = white_man;
				return 0;
			}

			else if(board[to_x][to_y] == empty && to_y == from_y-1 && to_x == from_x){
				// eger taş yeme durumu yoksa ve sola hareket yapicaksa
				board[from_x][from_y] = empty;
				board[to_x][to_y] = white_man;
				return 0;
			}	


			if(control==0){
				/* Eger tas yeme durumu varsa yukaridaki iflere girmez ve buraya girer. */
				if(board[from_x][from_y]==black_man || board[from_x][from_y]==black_king)
					return 0;
				
				if(from_x==0){
					/* King olma durumu bir daha kontrol edilir. */
					board[from_x][from_y]=white_king;
					return 0;
				}
				
				piece tempBoard[8][8];
				for(i=0; i<8; i++)
					for(j=0; j<8 ;j++)
						tempBoard[i][j]=board[i][j];
				/* Ana boardda degisiklik yapilmamasi lazim bu yuzden temp bir board kullanilir.
				   Cunku move_control fonksiyonunda olabilecek hamleleri boardda degisiklik
				   yaparak kontrol eder. */		
				move_control(tempBoard, p, from_x, from_y, arr, newMove, move_num);
				/* move_control cagirilir ve yeme hamleleri kontrol edilir. */
				Location = find_maxWay(arr); /* En cok yemenin olduğu arr'in kismi Locatian'a atanir. */
				control=1; /* control'e 1 atanir ve assagidaki bloklarda fonksiyon tekrar cagirildigindan bu 
							  control if'ine bir daha girmemesi saglanir.move fonk. paremetre olarak control'de eklenmistir. */
				/* Boylece fonk. her cagilirdiginda tekrardan max capture'ı bulmasi engellenmistir.Sadece bir kere bulur. */
			}
			
			if(arr[Location][moveLocation]==0){
				return 0;
				/* arr'in elemaninin 0 olmasi, o Locationda baska hamle kalmamasini belirtir.
				   move_control'de her bir hamleye no atanmistir 1,2 ve 3 seklinde. */
			}
				
			else{
				
				i=0;
				while(arr[Location][i]!=0){
					i++;
					/* arr'in o Location'da (en buyuk yemenin oldugu kisim) boyutu bulunur.
					   Boylece kac hamlede en buyuk yeme oldugunu anlasilir. */
				}
					
				if(arr[Location][moveLocation]==1){
					/* 1 white_man icin yukari harekettir. bkz: move_control() */
					board[from_x-1][from_y]=empty;
					board[from_x][from_y]=empty;
					board[from_x-2][from_y]=white_man;
					move(board,arr,from_x-2,from_y, to_x, to_y, p,Location,moveLocation+1,control);
					/* moveLocation arttirilarak bir sonraki hamleyle fonk cagirilir. */
				}
				
				if(arr[Location][moveLocation]==2){
					/*2 white_man icin sola harekettir. bkz: move_control() */
					board[from_x][from_y-1]=empty;
					board[from_x][from_y]=empty;
					board[from_x][from_y-2]=white_man;
					move(board,arr,from_x,from_y-2, to_x, to_y, p,Location,moveLocation+1,control);
					/* moveLocation arttirilarak bir sonraki hamleyle fonk cagirilir. */
				}
				
				if(arr[Location][moveLocation]==3){
					/*3 white_man icin saga harekettir. bkz: move_control() */
					board[from_x][from_y+1]=empty;
					board[from_x][from_y]=empty;
					board[from_x][from_y+2]=white_man;
					move(board,arr,from_x,from_y+2, to_x, to_y, p,Location,moveLocation+1,control);
					/* moveLocation arttirilarak bir sonraki hamleyle fonk cagirilir. */
				}
				else{
					return 0;
					/* baska hamle kalmayinca 0 return eder. */
				}
			}
		}

		
		else if(board[from_x][from_y] == white_king){ /* eger secilen tas white_king ise*/

			if(from_y == to_y){ /* dikey hareket ediliyorsa */

				if(from_x - to_x > 0){ /* dikeyde yukari hareket varsa */

					for(i=from_x;i>=to_x;i--){ 

						if( (board[i][from_y] == black_man || board[i][from_y] == black_king) && ( board[i-1][from_y] == empty)
							&& (board[i+1][from_y] == empty || board[i+1][from_y] == white_man || board[i+1][from_y] == white_king)){
							/* Kac tane tas yedigi kontrol edilir. */
							board[i][from_y]= empty;
							n++;
						}

						else if(board[i][from_y] == empty){
							bos_kontrol--;
							/* bos_kontrol 0'la baslar ve azaltilir */
							/* yewnilecek tasin arkasinin bos olup olmadigini kontrol eder */
						}
					}
					if(n!=0){ /* hic tas yenilmediyse */
						board[to_x][from_y] = white_king;
						board[from_x][from_y] = empty;
					}
					else if(n == 0 && bos_kontrol != 0 ){
						board[to_x][to_y] = white_king;
						board[from_x][from_y] = empty;
						/* eger tas yenilmis ve arkasinda bos ise onu kontrol eder */
					}
					else{
						return (-2);
						/* diger turlu yanlis hamle yapilmistir */
					}
				}

				else if(from_x - to_x < 0){ /* king assagi giderse */

					for(i=from_x;i<=to_x;i++){ /* Bundan sonra yukarida uygulanan islemler uygulanir,daha da karmasik olmasin diye yorum satirlari yazilmamistir. */

						if( (board[i][from_y] == black_man || board[i][from_y] == black_king) && ( board[i+1][from_y] == empty) && (board[i-1][from_y] == empty || board[i-1][from_y] == white_man || board[i-1][from_y] == white_king)){
							
							board[i][from_y]= empty;
							n++;
						}

						else if(board[i][from_y] == empty){
							bos_kontrol--;
						}
					}
					if(n != 0){ 
						board[to_x][from_y] = white_king;
						board[from_x][from_y] = empty;
					}
					
					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = white_king;
						board[from_x][from_y] = empty;
						
					}

					else{
						return (-2);
					}
				}
			}

			else if(from_x == to_x){ /* king yatay hareket yapiyorsa */

				if(from_y - to_y > 0){ /* king sola hareket ediyorsa */

					for(j = from_y;j >= to_y; j--){

						if( (board[from_x][j] == black_man || board[from_x][j] == black_king) && (board[from_x][j-1] == empty) 
							&& (board[from_x][j+1] == empty || board[from_x][j+1] == white_man || board[from_x][j+1] == white_king) ){
							
							board[from_x][j] = empty;
							n++;
						}

						else if(board[from_x][j] == empty){
							bos_kontrol--;
						}
					}

					if(n != 0){ 
						board[from_x][to_y] = white_king;
						board[from_x][from_y] = empty;
					}

					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = white_king;
						board[from_x][from_y] = empty;
					}
					
					else{
						return (-2);
					}
				}

				else if(from_y-to_y < 0){ /* king saga hareket ediyorsa */

					for(j = from_y;j <= to_y; j++){

						if( (board[from_x][j] == black_man || board[from_x][j] == black_king) && (board[from_x][j+1] == empty)
						 && (board[from_x][j-1] == empty || board[from_x][j-1] == white_man || board[from_x][j+1] == white_king) ){
							
							board[from_x][j] = empty;
							n++;
						}

						else if(board[from_x][j] == empty){
							bos_kontrol--;
						}
					}

					if(n != 0){ 
						board[from_x][to_y] = white_king;
						board[from_x][from_y] = empty;
					}

					else if(n == 0 && bos_kontrol !=0 ){
						board[to_x][to_y] = white_king;
						board[from_x][from_y] = empty;
					}

					else{
						return (-2);
					}
				}
			}
		}
	}

	/******** NOT ! Tasin siyah olmasi ile sadece dikey hareket degisir.Yorum satirlari karmasiklik olmasin diye bir daha yazilmamistir. ********/

	else if(p == 20){ /* Eger tas black_man ise */

		if(board[from_x][from_y] == black_man){			

			if(from_x==7){
				/* King olma durumunu kontrol eder. */
				board[from_x][from_y]=black_king;
				return 0;
			}

			if(board[to_x][to_y] == empty && to_y == from_y && to_x == from_x+1){
				// eger taş yeme durumu yoksa ve dikey hareket yapicaksa
				board[from_x][from_y] = empty;
				board[to_x][to_y] = black_man;
				
				if(from_x+1 == 7){
					board[from_x+1][from_y] = black_king;
					/*Hareket sonrasi King olma durumunu kontrol eder. */
				}

				return 0;
			}

			else if(board[to_x][to_y] == empty && to_y == from_y+1 && to_x == from_x){
				
				board[from_x][from_y] = empty;
				board[to_x][to_y] = black_man;
				return 0;
			}

			else if(board[to_x][to_y] == empty && to_y == from_y-1 && to_x == from_x){
				
				board[from_x][from_y] = empty;
				board[to_x][to_y] = black_man;
				return 0;
			}	


			if(control==0){
				/* Eger tas yeme durumu varsa yukaridaki iflere girmez ve buraya girer. */
				if(board[from_x][from_y]==white_man || board[from_x][from_y]==white_king)
					return 0;
				
				if(from_x==7)
				{
					/* King olma durumu bir kez daha kontrol edilir. */
					board[from_x][from_y]=black_king;
					return 0;
				}
			
				piece tempBoard[8][8];
				for(i=0; i<8; i++)
					for(j=0; j<8 ;j++)
						tempBoard[i][j]=board[i][j];
				/* Ana boardda degisiklik yapilmamasi lazim bu yuzden temp bir board kullanilir.
				   Cunku move_control fonksiyonunda olabilecek hamleleri boardda degisiklik
				   yaparak kontrol eder. */	
						
				move_control(tempBoard, p, from_x, from_y, arr, newMove, move_num);
				/* move_control cagirilir ve yeme hamleleri kontrol edilir. */
				Location=find_maxWay(arr); /* En cok yemenin olduğu arr'in kismi Locatian'a atanir. */
				control=1; 
				/* control'e 1 atanir ve assagidaki bloklarda fonksiyon tekrar cagirildigindan bu 
				   control if'ine bir daha girmemesi saglanir.move fonk. paremetre olarak control'de eklenmistir. */
				/* Boylece fonk. her cagilirdiginda tekrardan max capture'ı bulmasi engellenmistir.Sadece bir kere bulur. */
			}
			
			if(arr[Location][moveLocation]==0){
				return 0;
				/* arr'in elemaninin 0 olmasi, o Locationda baska hamle kalmamasini belirtir.
				   move_control'de her bir hamleye no atanmistir 1,2 ve 3 seklinde. */
			}
				
			else{
				
				i=0;
				while(arr[Location][i]!=0){
					i++;
					/* arr'in o Location'da (en buyuk yemenin oldugu kisim) boyutu bulunur.
					   Boylece kac hamlede en buyuk yeme oldugunu anlasilir. */
				}
					
				if(arr[Location][moveLocation]==1){
					/* 1 black_man icin assagi harekettir. bkz: move_control() */
					board[from_x+1][from_y]=empty;
					board[from_x][from_y]=empty;
					board[from_x+2][from_y]=black_man;
					move(board,arr,from_x+2,from_y, to_x, to_y, p,Location,moveLocation+1,control);
					/* moveLocation arttirilarak bir sonraki hamleyle fonk cagirilir. */
				}
				
				if(arr[Location][moveLocation]==2){
					/* 2 black_man icin sola harekettir. bkz: move_control() */
					board[from_x][from_y-1]=empty;
					board[from_x][from_y]=empty;
					board[from_x][from_y-2]=black_man;
					move(board,arr,from_x,from_y-2, to_x, to_y, p,Location,moveLocation+1,control);
					/* moveLocation arttirilarak bir sonraki hamleyle fonk cagirilir. */
				}
				
				if(arr[Location][moveLocation]==3){
					/* 3 black_man icin saga harekettir. bkz: move_control() */
					board[from_x][from_y+1]=empty;
					board[from_x][from_y]=empty;
					board[from_x][from_y+2]=black_man;
					move(board,arr,from_x,from_y+2, to_x, to_y, p,Location,moveLocation+1,control);
					/* moveLocation arttirilarak bir sonraki hamleyle fonk cagirilir. */
				}
				
				else{
					return 0;
					/* baska hamle kalmayinca 0 return eder. */
				}
			}
		}

		/* King olma durumlari ayni olduğundan white_king'in ayni islemleridir. */
		/* Sadece black_king icin tas yeme white_man veya white_king olarak degismistir. */
		/* Yorum satirlari da bir kez daha yazilmamistir. */

		else if(board[from_x][from_y] == black_king){ 

			if(from_y == to_y){ 

				if(from_x - to_x > 0){ 

					for(i=from_x;i>=to_x;i--){ 

						if( (board[i][from_y] == white_man || board[i][from_y] == white_king) && ( board[i-1][from_y] == empty) && (board[i+1][from_y] == empty || board[i+1][from_y] == black_man || board[i+1][from_y] == black_king)){
							
							board[i][from_y]= empty;
							n++;
						}

						else if(board[i][from_y] == empty){
							bos_kontrol--;
							
						}
					}
					if(n!=0){ 
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

				else if(from_x - to_x < 0){
					
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

			else if(from_x == to_x){

				if(from_y - to_y > 0){ 

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

				else if(from_y-to_y < 0){ 

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

int move_control(piece board[][8],player p,int from_x,int from_y, int arr[][20],int newMove,int move_num ){

	int i,j;
	piece tempBoard[8][8];
			for(i=0; i<8; i++)
				for(j=0; j<8 ;j++)
					tempBoard[i][j]=board[i][j];
	/* tempBoard kullanilarak az yeme durumunun board'i degistirme olayi engellenmistir. */
	
	if(p == 10){ // eger tas beyaz ise

		if((tempBoard[from_x-1][from_y] == black_man || tempBoard[from_x-1][from_y] == black_king) && tempBoard[from_x-2][from_y] == empty){
				
			arr[newMove][move_num]=1;
			tempBoard[from_x-1][from_y]=empty;
			newMove = move_control(tempBoard, p, from_x-2, from_y, arr,newMove, move_num+1);
			/* Bir sonraki hamleyi kontrol eder. */
			}
			// beyaz icin yukari giderse 1 return etsin

		if((tempBoard[from_x][from_y-1] == black_man || tempBoard[from_x][from_y-1] == black_king) && tempBoard[from_x][from_y-2] == empty){
			
			arr[newMove][move_num]=2;
			tempBoard[from_x][from_y-1]=empty;
			newMove=move_control(tempBoard, p, from_x, from_y-2, arr,newMove, move_num+1);	
			/* Bir sonraki hamleyi kontrol eder. */
		}
			// beyaz sola giderse 2 return etsin

		if((tempBoard[from_x][from_y+1] == black_man || tempBoard[from_x][from_y+1] == black_king) && tempBoard[from_x][from_y+2] == empty){
				
			arr[newMove][move_num]=3;
			tempBoard[from_x][from_y+1]=empty;
			newMove=move_control(tempBoard, p, from_x, from_y+2, arr,newMove, move_num+1);	
			/* Bir sonraki hamleyi kontrol eder. */
		}
			
		else{
			
			for(i=0; i<8; i++)
				for(j=0; j<8 ;j++)
					board[i][j]=tempBoard[i][j];
			return (newMove+1);
			/* Yapilacak hamle kalmamissa tempBoard'i board'a atayarak son durum belirlenir. */
		}
		// beyaz saga giderse 3 return etsin
	}

	else if(p == 20){ // eger tas siyahsa

		if((board[from_x+1][from_y] == white_man || board[from_x+1][from_y] == white_king) && board[from_x+2][from_y] == empty){
				
			arr[newMove][move_num]=1;
			board[from_x+1][from_y]=empty;
			newMove=move_control(board, p, from_x+2, from_y, arr,newMove, move_num+1);
			/* Bir sonraki hamleyi kontrol eder. */	
		}
		// siyah icin assagi giderse 1 return etsin

		if((board[from_x][from_y-1] == white_man || board[from_x][from_y-1] == white_king) && board[from_x][from_y-2] == empty){
				
			arr[newMove][move_num]=2;
			board[from_x][from_y-1]=empty;
			newMove=move_control(board, p, from_x, from_y-2, arr,newMove, move_num+1);
			/* Bir sonraki hamleyi kontrol eder. */	
		}
		// siyah sola giderse 2 return etsin

		if((board[from_x][from_y+1] == white_man || board[from_x][from_y+1] == white_king) && board[from_x][from_y+2] == empty){
				
			arr[newMove][move_num]=3;
			board[from_x][from_y+1]=empty;
			newMove=move_control(board, p, from_x, from_y+2, arr,newMove, move_num+1);
			/* Bir sonraki hamleyi kontrol eder. */	
		}
			
		else{
			
			for(i=0; i<8; i++)
				for(j=0; j<8 ;j++)
					board[i][j]=tempBoard[i][j];
			return (newMove+1);
			/* Yapilacak hamle kalmamissa tempBoard'i board'a atayarak son durum belirlenir. */
		}
		// siyah saga giderse 3 return etsin
	}
	
	return (newMove+1);
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

	/* Board'da herhangi rengin tasinin kalmamasi durumuna gore kazanani return eder. */
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
	/* Board'i ekrana basar */
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(i==7 && j==3)
				printf("-");
			else if(board[i][j] == white_man)
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



int main(){
	
	int selection=1;

	do{
		printf("\n*******************\n");
		printf("1. sample_game_1\n");
		printf("2. sample_game_2\n");
		printf("0. Exit\n");
		printf("\nWhat is your selection? "); scanf("%d",&selection);
		printf("\n*******************\n");
		/* sample game 1 ve sample game 2 icin menu yapilmistir. */
		switch(selection){
			case 1: sample_game_1(); break;
			case 2: sample_game_2(); break;
			case 0: selection = 0; break;
			default: printf("You entered wrong number!!");
		}
	} while(selection != 0);
}




void sample_game_1(){

	piece board[8][8]; init_board(board);
	int arr[20][20]={0};
	
	display_board(board);
	move(board,arr,5,1,4,1,10,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,2,2,3,2,20,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,5,3,4,3,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,2,0,3,0,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,5,4,5,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,3,0,4,0,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,0,3,0,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,3,2,4,2,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,2,3,2,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,2,1,2,0,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,4,5,3,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,2,0,4,6,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,6,3,6,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,2,6,4,6,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,7,5,6,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,4,6,4,5,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,6,4,6,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,4,5,4,7,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,6,7,5,7,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,4,7,6,7,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,3,4,3,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,6,7,7,7,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,6,5,5,5,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,2,3,2,2,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,6,4,5,4,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,2,2,6,4,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,6,3,6,5,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,2,5,3,5,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,5,4,5,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,3,5,7,5,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,6,1,5,1,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,1,0,2,0,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,5,1,4,1,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,7,5,7,2,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,4,1,4,0,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,7,2,4,2,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,6,0,5,0,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,7,7,6,7,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,4,0,3,0,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,2,0,6,0,20,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,6,6,6,5,10,0,0,0); check_end_of_game(board); display_board(board);
 	zeroArray(arr); move(board,arr,6,7,6,4,20,0,0,0); check_end_of_game(board); display_board(board);
}

void sample_game_2(){

	piece board[][8] = {(empty),(empty),(empty),(empty),(empty),(empty),(empty),(empty),
						(empty),(empty),(black_man),(black_man),(black_man),(black_man),(empty),(empty),
						(empty),(black_man),(black_man),(black_man),(black_man),(empty),(black_man),(black_man),
						(black_man),(black_man),(black_man),(empty),(empty),(black_man),(empty),(black_man),
						(empty),(empty),(white_man),(white_man),(white_man),(black_man),(white_man),(white_man),
						(white_man),(white_man),(white_man),(white_man),(white_man),(empty),(white_man),(white_man),
						(empty),(empty),(white_man),(white_man),(white_man),(white_man),(empty),(empty),
						(empty),(empty),(empty),(white_man),(empty),(empty),(empty),(empty) };	

	int arr[20][20]={0};
	display_board(board);
	move(board,arr,5,1,4,1,10,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,3,1,5,1,20,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,4,3,3,3,10,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,4,5,4,1,20,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,3,3,1,1,10,0,0,0); check_end_of_game(board); display_board(board);
					move(board,arr,1,3,1,0,20,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,5,3,4,3,10,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,5,1,7,5,20,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,4,3,3,3,10,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,2,3,4,3,20,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,5,6,5,5,10,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,7,5,4,5,20,0,0,0); check_end_of_game(board); display_board(board);
	zeroArray(arr); move(board,arr,4,6,0,0,10,0,0,0); check_end_of_game(board); display_board(board);
	
}

void zeroArray(int arr[][20]){

	int i,j;
	/* arrayin tum elemanlarina 0 atar. */
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
			arr[i][j] = 0;
}