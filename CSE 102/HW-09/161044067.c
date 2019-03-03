// Gokhan Has - 161044067
// CSE 102 - HW09

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1024

typedef struct{
	
	char **map;
	int width;
	int height;
	int flower_x;
	int flower_y;	
} Forest;

typedef struct{

	int coord_x;
	int coord_y;
	int water_bottle_size;
} Botanist;

/************** Defining Functions **************/

void init_game(Forest *forest, Botanist *botanist);
void print_map(Forest *forest);
void search(Forest forest,Botanist botanist,int water_bottle_size);
void free_map(Forest forest);
int randomNumber();

/***********************************************/

int main(){

	srand(time(NULL));
	Forest forest;
	Botanist botanist;
	int water_bottle_size;

	init_game(&forest,&botanist);
	print_map(&forest);
	water_bottle_size = botanist.water_bottle_size;
	search(forest,botanist,water_bottle_size);
	print_map(&forest);
	
	
	free_map(forest);
	return 0;
}

void search(Forest forest,Botanist botanist,int water_bottle_size){

	int select;
	select =randomNumber();
	/* Where he/she goes will be determined randomly. */
	
	if(water_bottle_size == 0){
		printf("Help! I am on (%d,%d).\n",botanist.coord_x,botanist.coord_y);
	/* Recursion exit condition. */	
	}
	
	else if(select == 1){ /* Go upstairs. */
		
		if(forest.map[botanist.coord_x-1][botanist.coord_y] == ' '){
			/* If the bostanist can move. */
			forest.map[botanist.coord_x][botanist.coord_y] = ' ';
			forest.map[botanist.coord_x-1][botanist.coord_y] = 'B';
			botanist.coord_x -= 1;
			water_bottle_size--;
			search(forest,botanist,water_bottle_size);
		}
		else if(forest.map[botanist.coord_x-1][botanist.coord_y] == 'F'){
			/* Checks if he/she finds a flower. */
			forest.map[botanist.coord_x][botanist.coord_y] = ' ';
			botanist.coord_x -= 1;
			printf("I have found it in (%d,%d)\n",botanist.coord_x,botanist.coord_y);
			return;
		}
		else{
			search(forest,botanist,water_bottle_size);
		}
	}

	else if(select == 2){ /* Go downstairs. */
		
		if(botanist.coord_x==forest.height-1){
			/* If this is not the case, if the map comes in the 9th line and it goes downstairs, 
			 	it will give an error (segmentation fault). */
			search(forest,botanist,water_bottle_size);
		}
		else if(forest.map[botanist.coord_x+1][botanist.coord_y] == ' '){
			/* If the bostanist can move. */
			forest.map[botanist.coord_x][botanist.coord_y] = ' ';
			forest.map[botanist.coord_x+1][botanist.coord_y] = 'B';
			botanist.coord_x += 1;
			water_bottle_size--;
			search(forest,botanist,water_bottle_size);
		}
		else if(forest.map[botanist.coord_x+1][botanist.coord_y] == 'F'){
			/* Checks if he/she finds a flower. */
			forest.map[botanist.coord_x][botanist.coord_y] = ' ';
			botanist.coord_x += 1;
			printf("I have found it in (%d,%d)\n",botanist.coord_x,botanist.coord_y);
			return;
		}
		else{
			search(forest,botanist,water_bottle_size);
		}
	} 

	else if(select == 3){ /* Go right. */
	
		
		if(forest.map[botanist.coord_x][botanist.coord_y+1] == ' '){
			/* If the bostanist can move. */
			forest.map[botanist.coord_x][botanist.coord_y] = ' ';
			forest.map[botanist.coord_x][botanist.coord_y+1] = 'B';
			botanist.coord_y += 1;
			water_bottle_size--;
			search(forest,botanist,water_bottle_size);
		}
		else if(forest.map[botanist.coord_x][botanist.coord_y+1] == 'F') {
			/* Checks if he/she finds a flower. */
			forest.map[botanist.coord_x][botanist.coord_y] = ' ';
			botanist.coord_y += 1;
			printf("I have found it in (%d,%d)\n",botanist.coord_x,botanist.coord_y);
			return;
		}
		else{
			search(forest,botanist,water_bottle_size);
		}
	} 

	else if(select == 4){ /* Go left. */

		if(forest.map[botanist.coord_x][botanist.coord_y-1] == ' '){
			/* If the bostanist can move. */
			forest.map[botanist.coord_x][botanist.coord_y] = ' ';
			forest.map[botanist.coord_x][botanist.coord_y-1] = 'B';
			botanist.coord_y -= 1;
			water_bottle_size--;
			search(forest,botanist,water_bottle_size);
		}
		
		else if(forest.map[botanist.coord_x][botanist.coord_y-1] == 'F'){
			/* Checks if he/she finds a flower. */
			forest.map[botanist.coord_x][botanist.coord_y] = ' ';
			botanist.coord_y -= 1;
			printf("I have found it in (%d,%d)\n",botanist.coord_x,botanist.coord_y);
			return;
		}
		else{
			search(forest,botanist,water_bottle_size);
		}
	}
	return;
}


/***********************************************/

void init_game(Forest *forest, Botanist *botanist){

	FILE *fp;
	char comma;
	int i,j,k;
	
	fp = fopen("init.csv","r"); /* Opening File */
	if(fp == NULL){
		printf("Error ! This file cannot open!!\n");
		return;
	}

	fscanf(fp,"%d",&botanist->water_bottle_size);
	fscanf(fp,"%d%c%d",&forest->height,&comma,&forest->width);
	/* First, scan simple variables such as bottle_size, height and width */
	
	char str[2*forest->width-1];
	/* Bu string harita icin kullanilacak.Haritanın sutununun boyutu ne ise
		onun iki katindan 1 eksik boyutta olmali.Cunku virguller de var.
		Mesela 10 oldugunda sutun sayisi stringin boyutu 19 olmali.Cunku bir 
		satirda virguller dahil 19 eleman olacak. */
	
	forest->map = (char**)malloc((forest->height) * sizeof(char*));
	for(i=0;i<forest->height;i++){
		forest->map[i] = (char *)malloc((forest->width) * sizeof(char));
	}
	/* Allocating 2D char array. */

	fgets(str,SIZE,fp); /* If this does not happen, the first character gets an enter(\n). */
	
	i=0;
	while(fgets(str,SIZE,fp) != NULL){ /* Reading until the end of the file. */

		j=0; k=0;
		for(j=0;j<(2*forest->width-1);j=j+2){

			if(str[j] == 'F'){
				forest->flower_x = i;
				forest->flower_y = k;

			}
			/* Save the location of the flower and the botanist's place. */
			else if(str[j] == 'B'){
				botanist->coord_x = i;
				botanist->coord_y = k;
			}
			forest->map[i][k] = str[j]; /* double - string assignment. */
			k++;
		}
		i++;	
	}
	fclose(fp); /* Closing file */
}

/***********************************************/

void print_map(Forest *forest){

	int i,j;
	
	for(i=0;i<forest->height;i++){
		for(j=0;j<forest->width;j++){
			if(j==0)
				printf("%c",forest->map[i][j]);
			/* Do not print a space in the first element of each line. */
			else
				printf(" %c",forest->map[i][j]);
		}
		printf("\n");
	}	
}

/***********************************************/

void free_map(Forest forest){

	int i,j;
	/* Free char **map in memory. */
	for(i=0;i<forest.height;i++)
		free(forest.map[i]);
	free(forest.map);
}

/***********************************************/

int randomNumber(){

	int number;
	/* Return random number such as 1,2,3 or 4. */
	number = rand() % 4;
	if(number == 0)
		number = 4;

	return number;
}
