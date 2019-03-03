// Gokhan Has - 161044067
// CSE 102 - HW06

#include <stdio.h>
#define SIZE 1024

/*************************** Define Functions ********************************/
void menu();
void encrypt_open_msg();
void decrypt_secret_msg();
int find_size_of_line(char line[]);
void reverse_line(char line[], int line_lenght);
/****************************************************************************/

int main(){

	menu(); /* In main, used only menu function. */
	return 0;
}

void menu(){

	int selection;

	do{
		printf("\n****************************\n");
		printf("1. Encrypt\n");
		printf("2. Decrypt\n");
		printf("0. Exit\n");
		printf("Choice: ");  scanf("%d",&selection);
		/* Selection from the user. */
		
		switch(selection){
			/* Calling the functions, whichever selected. */
			case 1:
				encrypt_open_msg(); break;

			case 2:
				decrypt_secret_msg(); break;

			case 0:
				printf("Exiting...\n");
				selection = 0;  break;
			/* If the user selected 0, 0 is assigned to selection so 
			   the loop exits and the program ends. */
			default:
				printf("You entered wrong number !!!\n");
		}
	} while (selection != 0);
}


void encrypt_open_msg(){

	int key,line_lenght,i=0;
	FILE *fp,*fp2; /* Define file pointers. */
	char line[SIZE];

	fp = fopen("open_msg.txt", "r");
	fp2 = fopen("secret_msg.txt","w");
	/* Opening files */
	
	if(fp == NULL){
		printf("ERROR : An error occured when opening the file (open_msg.txt).\n");
	}
	/* Error message that if the files do not open. */
	if(fp2 == NULL){
		printf("ERROR : An error occured when opening the file (secret_msg.txt).\n");
	}

	else {

		printf("Enter a key : ");  scanf("%d",&key); printf("\n");
		
		while(fgets(line,SIZE,fp) != NULL){	
			/* Taking the lines one by one and writing them to the file.
			   So used fgets function. */
			line_lenght = find_size_of_line(line);
			line_lenght -= 2;
			/* English : line_lenght -= 2. Because, the fgets function reads twice the size of the line. */
			/* Turkce : line_lenght -= 2 yapilir. Cunku, fgets fonksiyonu satirin boyutunu  iki karakter fazla okudugu gozlemlenmistir.. */
			/* Bu islem yapilmadiginda, reverse isleminden sonra fazladan iki karakter basmaktadir. */
			reverse_line(line,line_lenght); /* Reverse the line. */
			
			for(i=0;i<line_lenght;i++){

				if(line[i] == '.'){
					line[i] = '*';
				}
				else if(line[i] == ' '){
					line[i] = '_';
				}
				else if(line[i] - key < 'a'){
					line[i] = (line[i] - key) + 26;
					/* If the line[i]-key is less than the ascii standart from 'a',it should be added 26. */
				}
				else if(line[i] - key > 'a'){
					line[i] = line[i] - key;
					/* If the line[i]-key is greater tahan the ascii standart from 'a',it should be subtracted 'key'a. */
				}
			}
			printf("%s",line); /* Prints the screen. */
			fprintf(fp2,"%s",line); /* Writing file "secret_msg.txt". */
		} 
	}
	fclose(fp); fclose(fp2); /* Closing files. */
}

void decrypt_secret_msg(){

	char line[SIZE];
	int i,line_lenght,key;
	FILE *fp,*fp2; /* Define file pointers. */
	
	fp = fopen("secret_msg.txt", "r");
	fp2 = fopen("open_msg.txt","w");
	/* Opening files */

	if(fp2 == NULL){
		printf("ERROR : An error occured when opening the file (open_msg.txt).\n");
	}
	/* Error message that if the files do not open. */
	if(fp == NULL){
		printf("ERROR : An error occured when opening the file (secret_msg.txt).\n");
	}

	else{
		printf("Enter a key : ");  scanf("%d",&key); printf("\n");	
		
		while(fgets(line,SIZE,fp) != NULL){
			/* Taking the lines one by one and writing them to the file.
			   So used fgets function. */
			line_lenght = find_size_of_line(line);
			line_lenght -= 2;
			/* English : line_lenght -= 2. Because, the fgets function reads twice the size of the line. */
			/* Turkce : line_lenght -= 2 yapilir. Cunku, fgets fonksiyonu satirin boyutunu  iki karakter fazla okudugu gozlemlenmistir.. */
			/* Bu islem yapilmadiginda, reverse isleminden sonra fazladan iki karakter basmaktadir. */
			reverse_line(line,line_lenght); /* Reverse the line. */
			for(i=0;i<line_lenght;i++){

				if(line[i] == '_'){
					line[i] = ' ';
				}
				else if(line[i] == '*'){
					line[i] = '.';
				}
				else if(line[i] + key > 'z'){
					line[i] = (line[i] + key) - 26;
				}
				/* The decryption process is the reverse of the encryption process. */
				/* So 'a' --> 'z' and '-' --> '+' */
				else if(line[i] + key <= 'z'){
					line[i] = line[i] + key;
				}
			}
			printf("%s",line); /* Prints the screen. */
			fprintf(fp2,"%s",line); /* Writing file "open_msg.txt". */
		}
	}
	fclose(fp); fclose(fp2); /* Closing files. */
}

int find_size_of_line(char line[]){

	int len=0;

	while(line[len] != '\0'){
		len++;
	}
	/* Finding size of line using while loop. */
	return (len);
}

void reverse_line(char line[], int line_lenght){

	int i;
	char temp_line[line_lenght];

	for(i=0;i<line_lenght;i++){
		temp_line[i] = line[line_lenght-1-i];
	}
	temp_line[line_lenght] = '\0';
	/* Reversing line using for loop and temp string. */
	for(i=0;i<line_lenght;i++){
		line[i] = temp_line[i];
	}
}