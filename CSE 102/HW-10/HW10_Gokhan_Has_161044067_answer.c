// Gokhan Has - 161044067
// CSE 102 - HW10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000000

typedef struct node{
	/* Linked List icin gerekli olan structin tanimlanmasi. */
	int number;
	struct node *next;
}node;

/************* Fonksiyonlari Tanimlama *************/

int read_integers(FILE *fp);
int find_prime_numbers(int number);
void find_prime_numbers_using_dynamicArray();
void find_prime_numbers_using_linkedList();

/**************************************************/

int main(){

	int selection;

	printf("*** MENU ***\n");
	printf("1. Dynamic Array\n");
	printf("2. Linked List\n");
	printf("Selection : "); scanf("%d",&selection);

	switch(selection){

		case 1:
			printf("** Writing File... **\n");
			find_prime_numbers_using_dynamicArray();
			printf("** Done! **\n");
			break;

		case 2:
			printf("** Writing File... **\n");
			find_prime_numbers_using_linkedList();
			printf("** Done! **\n");
			break;

		default:
			printf("\nYou entered wrong number (choose 1 or 2) !!\n");
	}

	/*  (double)(end - start) / CLOCKS_PER_SEC) * 1000.0) */
	
	/* time.h da bulunan zaman fonksiyonu kodun hem ilk basinda hem de sonunda calisir.
	Aradaki farki yine time.h'da tanimli olan CLOCKS_PER_SEC degiskenine bolunmesiyle
	kodun kac saniye calistigi bulunur.Bizden milisaniye cinsinden zaman istendiginden
	1000 ile carpilarak zaman bulunur. */

	return 0;
}

int read_integers(FILE *fp){

	int num,zero;
	fscanf(fp,"%d,%d",&num,&zero);
	/* Virgulden sonrasi zero adli degiskende tutulur.
		Boyle daha verimli ve duzgun okudugu gozlemlenmistir. */
	return num;
	/* Okunan sayi num degiskeninde tutulur ve return edilir. */
}

void find_prime_numbers_using_dynamicArray(){

	clock_t start,end,end500,end750,endGenerate;
	start = clock(); /* Zaman baslar. */
	
	int i,j,*array,count=0,result;
	int key=0;
	FILE *fp,*fpArray;
	
	fp = fopen("data.txt","r"); /* Dosyanin acilmasi. */
	if(fp == NULL)
		printf("File cannot open !\n");

	fpArray = fopen("output_prime_dynamic_array.txt","w");
	array = (int*)malloc(SIZE * sizeof(int)); /* Dinamik hafiza icin allocation yapilmasi. */

	for(i=0;i<SIZE;i++){
		array[i] = read_integers(fp);
		/* Dosyadan satir satir sayilari okuyup dinamik arraye atama. */
	}
	endGenerate = clock(); /* olusma suresinin sonunun belirtilmesi. */
	printf("\nGeneration Time is %lf milisecond.\n",((double)(endGenerate - start) / (CLOCKS_PER_SEC) * 1000.0));
	
	i=1;
	while(i != SIZE){

		result = find_prime_numbers(array[i]);
		/* Eger sayi asalsa dosyaya yazilir */
		if(result == 1)
			fprintf(fpArray,"%d\n",array[i]);
		else if (array[i] == 500000)
			end500 = clock();
		else if(array[i] == 750000)
			end750 = clock();
		i++;
	}
	end = clock();
	printf("\nWriting Time...\n");
	printf("Between 1 and  500.000 	calculation time : %lf milisecond.\n",( (double)(end500 - start) / (CLOCKS_PER_SEC) * 1000.0));
	printf("Between 1 and  750.000 	calculation time : %lf milisecond.\n",( (double)(end750 - start) / (CLOCKS_PER_SEC) * 1000.0));
	printf("Between 1 and 1.000.000	calculation time : %lf milisecond.\n",( (double)(end - start) / (CLOCKS_PER_SEC) * 1000.0));
	/* Belirtilen araliklarda zamanin terminale yazilmasi. */
	/* islemin neden boyle oldugu mainde aciklanmistir. */

	free(array); /* Dinamik hafizanin bosaltilmasi. */
	fclose(fp); /* Dosyanin Kapatilmasi. */
	fclose(fpArray); /* yazilan dosyanin kapatilmasi. */
}

void find_prime_numbers_using_linkedList(){

	clock_t start,end,end500,end750,endGenerate; /* zamanin hesaplanmasi icin degiskenlerin tanimlanmasi. */
	start = clock(); /* zamanin baslamsi. */
	int i,result;
	FILE *fp,*fpLinkedList;
	
	fp = fopen("data.txt","r"); /* Dosyanin acilmasi. */
	if(fp == NULL)
		printf("File cannot open !\n");
	fpLinkedList = fopen("output_prime_linkedList.txt","w");
	
	node *temp,*iter,*primeControl;

	node *head = (node*)malloc(sizeof(node)); /* Linked List'in basinin belirtilmesi. */
	head->number = read_integers(fp);
	head->next = NULL;
	iter = head;
	/* Linked Listin ilk elemaninin olusmasi. */

	i=0;
	while(i != SIZE){

		/* Yeni dugum olusturulur ve dosyadan alinan sayilar o dugumlere eklenir. */
		temp = (node*)malloc(sizeof(node));
		temp->number = read_integers(fp);
		temp->next = NULL;
		iter->next = temp;
		iter = iter->next;
		i++;
	}
	iter->next = NULL; /* LinkedList'in sonunun belirtilmesi. */
	
	endGenerate = clock(); /* olusma suresinin sonunun belirtilmesi. */
	printf("\nGeneration Time is %lf milisecond.\n",((double)(endGenerate - start) / (CLOCKS_PER_SEC) * 1000.0));
	
	primeControl = head;
	while( primeControl->next != NULL){

		result = find_prime_numbers(primeControl->number);

		if(primeControl->number == 1); /* Ilk sayiyi basmama kosulu (1). */
		else if(result == 1)
			fprintf(fpLinkedList,"%d\n",primeControl->number);
		else if(primeControl->number == 500000)
			end500 = clock(); /* 500.000'e kadar olanki zamanin bulunmasi. */
		else if(primeControl->number == 750000)
			end750 = clock(); /* 750.000'e kadar olanki zamanin hesaplanmasi. */
		
		primeControl = primeControl->next; /* bir sonraki dugume gecme. */
	}
	end = clock();
	printf("\nWriting Time .....\n");
	printf("Between 1 and  500.000 	calculation time : %lf milisecond.\n",( (double)(end500 - start) / (CLOCKS_PER_SEC) * 1000.0));
	printf("Between 1 and  750.000 	calculation time : %lf milisecond.\n",( (double)(end750 - start) / (CLOCKS_PER_SEC) * 1000.0));
	printf("Between 1 and 1.000.000	calculation time : %lf milisecond.\n",( (double)(end - start) / (CLOCKS_PER_SEC) * 1000.0));

	while(head->next != NULL){
		free(head->next);
		head = head->next;
		/* hafizanin bosaltilmasi. */
	}

	fclose(fp); /* data.txt dosyasinin kapatilmasi. */
	fclose(fpLinkedList); /* yazilan dosyanin kapatilmasi */
}

int find_prime_numbers(int number){

	int i,key=0;
	/* Asal sayi bulma fonksiyonu.Eger sayi asalsa 1 return edilir. */
	for(i=2;i<=(number / 2);i++){

			if(number % i == 0){
				key = 1;
				break;
			}
			else
				key = 0;
	}

	if(key == 1)
		return 0;
	else
		return 1;		
}