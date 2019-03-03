// Gokhan Has - 161044067
// CSE 102 - HW11

#include <stdio.h>
#include <stdlib.h>
#define SIZE 256

typedef struct Customers{

	char name[15];
	char surname[15];
	int age;
	char gender[6];
	struct Customers *next;
}Customers;
/* Defining structs type. */
typedef struct Rooms{

	int number;
	int capacity;
	int floor;
	Customers *customers;
	struct Rooms *next;
}Rooms;

/**************** Defining Functions ****************/

void add_room_to_end(Rooms *head,int r_number,int r_capacity,int r_floor);
void add_room_after_room_number(Rooms *head,int index,int r_number,int r_capacity,int r_floor);
Rooms *add_customer_to_end(Rooms *headRooms,int room_number,char *c_name,char *c_surname,int c_age,char *c_gender);
Rooms * link_customers_to_room(Rooms *headRooms,Customers *customers);
void remove_room(Rooms *head,int room_number);
void show_vacancy(Rooms *head);
void get_by_floor(Rooms *head,int floor_number);
void print_list(Rooms *head);
int stringLen(char *inputString);
char* stringCopy(char *destination, char *source);

/****************************************************/

int main(){

	FILE *fptrCustomers,*fptrRooms;
	Customers *headCustomers,*customers;
	Customers customers_list[34]; /* creatinig customers struct array. */
	Rooms *headRooms,*rooms,*tempRoom;
	
	char line[SIZE] = {0}; /* it is used reading customers.txt */
	int customers_room_number,customers_age,customers_line_size;
	char customers_name[SIZE],customers_surname[SIZE],customers_gender[7];
	int index = 0,i,counter=0;
	
	fptrCustomers = fopen("customers.txt","r");
	fptrRooms = fopen("rooms.txt","r"); /* Opening files. */
	
	headRooms = (Rooms*)malloc(sizeof(Rooms));
	fscanf(fptrRooms,"%d,%d,%d",&headRooms->number,&headRooms->capacity,&headRooms->floor);
	headRooms->next = NULL;
	rooms = headRooms;
	tempRoom = headRooms;/* it is head of room linked list */
	
	while( !feof(fptrRooms) ){
	
		rooms->customers = (Customers*)malloc(sizeof(Customers));
		rooms->customers = NULL;
		rooms->next = (Rooms*)malloc(sizeof(Rooms));
		rooms = rooms->next;
		/* reading room.txt to room struct. */
		fscanf(fptrRooms,"%d,%d,%d",&rooms->number,&rooms->capacity,&rooms->floor);
	}
	rooms->next = NULL;
	
	customers = (Customers*)malloc(sizeof(Customers));
	customers->next = NULL;
	while(!feof(fptrCustomers)){	
		fgets(line,sizeof(line),fptrCustomers);
		/* reading customers.txt using string and separating the pieces 
			and throwing them into variables. */
		if(line[stringLen(line) - 1] == '\n'){
			line[stringLen(line) - 1] = 0;
		}
		/* Assignment is made by separating by comma. */
		int j=0,z=0,k=0;
		for(i=0;i<stringLen(line);i++){

			if(j==0){
				if(line[i] == ','){
					sscanf(line,"%d",&customers_room_number);
					j++;
				}
			}
			else if(j==1){
				if(line[i-1] == ','){
					z = i; k=0;
					while(line[z] != ' '){
						customers_surname[k] = line[z];
						k++; z++;
					}
					customers_surname[k] = '\0';
					stringCopy(customers_list[index].surname,customers_surname);
					j++;
				}
			}
			
			else if(j==2){
				if(line[i-1] == ' '){
					z = i; k=0;
					while(line[z] != ','){
						customers_name[k] = line[z];
						k++; z++;
					}
					customers_name[k] = '\0';
					stringCopy(customers_list[index].name,customers_name);
					j++;
				}
			}
			else if(j==3){
				if(line[i-1] == ','){
					customers_age = atoi(&line[i]);
					customers_list[index].age = customers_age;
					j++;
				}
			}
			else if(j==4){
				if(line[i-1] == ','){
					z=i; k=0;
					while(line[z] != '\0'){
						customers_gender[k] = line[z];
						k++; z++;
					}
					customers_gender[k-1] = '\0';
					stringCopy(customers_list[index].gender,customers_gender);
				}
			}
		}
		index++;
		/* The customer array is assigned. */
	}
	
	/* Belirtilen fonksiyonlarin denenmesi icin yazilmistir. */

	rooms = headRooms;
	rooms = link_customers_to_room(rooms,customers_list); /* olusturup basma. */
	print_list(rooms);
	rooms = link_customers_to_room(rooms,customers_list);

	show_vacancy(rooms); printf("\n\n"); /* hangi odaların bos oldugunu basma */
	add_room_to_end(rooms,500,3,5); /* sona oda ekleyip basma. */
	show_vacancy(rooms); /* hangi odaların bos oldugunu basma */
	
	printf("\n\n");

	print_list(rooms); printf("****************\n");
	add_room_after_room_number(rooms,5,505,3,5); /* araya oda ekleyip basma. */
	
	printf("\n\n");

	rooms = link_customers_to_room(rooms,customers_list);
	print_list(rooms);
	
	printf("\n\n");

	remove_room(rooms,408); /* oda silip basma. */
	rooms = link_customers_to_room(rooms,customers_list);
	print_list(rooms);

	fclose(fptrCustomers); fclose(fptrRooms);
	/* Closing files. */ 
}


void add_room_to_end(Rooms *head,int r_number,int r_capacity,int r_floor){
	/* This function adds a room at the end of the room list. */
	while(head->next != NULL)
		head = head->next;

	head->next = (Rooms*)malloc(sizeof(Rooms));
	head->next->number = r_number;
	head->next->capacity = r_capacity;
	head->next->floor = r_floor;
	head->next->customers = NULL;
	head->next->next = NULL;
}

void add_room_after_room_number(Rooms *head,int index,int r_number,int r_capacity,int r_floor){
	/* This function adds the specified indexed room. */
	int i=0;
	Rooms *temp = (Rooms*)malloc(sizeof(Rooms));
	temp = head;
	
	while(temp->next != NULL){
		i++;
		temp = temp->next;
	}
	i++;
	
	if(index >= i){
		/* If the index is the last, it adds to the end. */
		add_room_to_end(head,r_number,r_capacity,r_floor);
	}

	else{
		for(i=1;i<index;i++)
			head = head->next;
		Rooms *temp2 = (Rooms*)malloc(sizeof(Rooms));
		temp2->next = head->next;
		head->next = temp2;

		temp2->number = r_number;
		temp2->capacity = r_capacity;
		temp2->floor = r_floor;
	}
}

Rooms * add_customer_to_end(Rooms *headRooms,int room_number,
	char *c_name,char *c_surname,int c_age,char *c_gender){

	/* This function adds a customer to the specified room. */
	Customers *temp;

	while(headRooms->number != room_number)
		headRooms= headRooms->next;

	while(headRooms->customers->next != NULL){
		headRooms->customers = headRooms->customers->next;
	}

	
	temp = (Customers*)malloc(sizeof(Customers));
	stringCopy(temp->name,c_name);
	stringCopy(temp->surname,c_surname);
	temp->age = c_age;
	stringCopy(temp->gender,c_gender);
	temp->next = NULL;

	headRooms->customers->next = temp;
	headRooms->customers = headRooms->customers->next;

	return headRooms;
}

void remove_room(Rooms *head,int room_number){
	/* This function deletes the specified room. */
	Rooms *temp = (Rooms*)malloc(sizeof(Rooms));

	while(head->next->number != room_number){
		head = head->next;
	}

	temp = head->next;
	head->next = head->next->next;
	free(temp);
}

void show_vacancy(Rooms *head){
	/* This function shows rooms that have no customer at all. */
	int i=0;
	while(head != NULL){

		if(head->customers == NULL){
			printf("%d. Room don't have any customer.\n",head->number);
			i++;
		}
		head = head->next;
	}

	if(i == 0){
		printf("All rooms are full!\n");
	}
}

void get_by_floor(Rooms *head,int floor_number){
	/* This function shows which rooms are located on the specified floor. */
	int i=0;
	while(head != NULL){

		if(head->floor == floor_number){
			printf("Room %d \n",head->number);
			i++;
		}
		head = head->next;
	}

	if(i == 0){
		/* If there is no room, it shows this message. */
		printf("No rooms were found on the %d. floor!\n",floor_number);
	}
}

void print_list(Rooms *head){
	/* It prints the screen in the specified format. */
	while(head != NULL){

		if(head->customers == NULL){
			printf("Room %d (Floor %d - capacity %dx):\n",head->number,head->floor,head->capacity);
			printf("-> Empty\n\n");
		}

		else{

			printf("Room %d (Floor %d - capacity %dx):\n",head->number,head->floor,head->capacity);
			while(head->customers != NULL){

				
				printf("-> %s %s (%d - %s)\n",head->customers->name,head->customers->surname,
					head->customers->age,head->customers->gender);
				head->customers = head->customers->next;			
			}
			printf("\n");
		}
		head = head->next;
	}
}

Rooms * link_customers_to_room(Rooms *headRooms,Customers *customers){

	int i;
	Rooms *temp;
	temp = headRooms;
	/* Link linkedlist to room->customers linked list. */
	/* Customers.txt customers connect to the rooms they are in. */
	while(temp != NULL){

		if(temp->number == 105){
			temp->customers = &customers[1];
			temp->customers->next = &customers[19];
			temp->customers->next->next = NULL;
		}
		
		else if(temp->number == 203){
			temp->customers = &customers[2];
			temp->customers->next = &customers[21];
			temp->customers->next->next = NULL;
		}
		
		else if(temp->number == 403){
			temp->customers = &customers[3];
			temp->customers->next = &customers[22];
			temp->customers->next->next = NULL;
		}
		
		else if(temp->number == 402){
			temp->customers = &customers[6];
			temp->customers->next = &customers[11];
			temp->customers->next->next = &customers[23];
			temp->customers->next->next->next = &customers[26];
			temp->customers->next->next->next->next = NULL;
		}
		
		else if(temp->number == 301){
			temp->customers = &customers[7];
			temp->customers->next = &customers[20];
			temp->customers->next->next = NULL;
		}

		else if(temp->number == 302){
			temp->customers = &customers[9];
			temp->customers->next = &customers[32];
			temp->customers->next->next = NULL;
		}

		else if(temp->number == 208){
			temp->customers = &customers[10];
			temp->customers->next = &customers[27];
			temp->customers->next->next = &customers[33];
			temp->customers->next->next->next = NULL;
		}

		else if(temp->number == 406){
			temp->customers = &customers[12];
			temp->customers->next = &customers[17];
			temp->customers->next->next = NULL;
		}

		else if(temp->number == 207){
			temp->customers = &customers[13];
			temp->customers->next = &customers[25];
			temp->customers->next->next = NULL;
		}

		else if(temp->number == 107){
			temp->customers = &customers[14];
			temp->customers->next = &customers[28];
			temp->customers->next->next = NULL;
		}

		else if(temp->number == 404){
			temp->customers = &customers[15];
			temp->customers->next = &customers[18];
			temp->customers->next->next = &customers[29];
			temp->customers->next->next->next = NULL;
		}

		else if(temp->number == 305){
			temp->customers = &customers[24];
			temp->customers->next = &customers[30];
			temp->customers->next->next = &customers[31];
			temp->customers->next->next->next = NULL;
		}
		else{
			temp->customers = NULL;
		}
		
		temp = temp->next;
	}
	return headRooms;
}

int stringLen(char *inputString){
    int length = 0;
    /*user define strlen */
    while(inputString[length] != '\0'){
        length++;
    }
    return length;
}

char* stringCopy(char *destination, char *source){
    int index = 0;
    /* user define strcpy.*/
    while(source[index] != '\0'){
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0';
    return destination;
}