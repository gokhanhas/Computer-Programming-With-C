// Gokhan Has - 161044067
// CSE 102 - HW07 - part2

#include <stdio.h>

/* Define Functions */
void printDates();
void printWeekday();

int main(){

	int selection;
	int control = 1;
	/* Menu. If user's select 1 --> calling function 1.
			 If user's select 2 --> calling function 2.
			 and selected 0 is exit. */
	do{

		printf("***********************\n");
		printf("1. PrintDates\n");
		printf("2. PrintWeekday\n");
		printf("0. Exit\n");

		printf("Enter a number > "); scanf("%d",&selection);

		switch(selection){
			case 1: printDates(); printf("OK...\n\n"); break;
			case 2: printWeekday(); printf("OK...\n\n"); break;
			case 0: control = 0; printf("Exiting...\n"); break;
		}
	} while(control != 0);
} 

void printDates(){

	FILE *fp;
	int month,year,day,numDays,control = 1,control2=1;
	int start_day,start_month,start_year;
	int finish_day,finish_month,finish_year;
	char ch;

	printf("Enter first date (dd/MM/yy format) > "); scanf("%d%c%d%c%d",&start_day,&ch,&start_month,&ch,&start_year);
	printf("Enter last date (dd/MM/yy format) > ");  scanf("%d%c%d%c%d",&finish_day,&ch,&finish_month,&ch,&finish_year);
	/* Entering first and last date. Format is dd/MM/yy. Ex: 05/01/2015 (enter \n) 23/04/2018 (enter). */

	fp = fopen("input_date.txt","w"); /* Creating file */
	
	day= start_day;
	month = start_month;
	year = start_year;
	
	while(control != 0){

		month %= 12;
		if(month == 0)
			month = 12;

		switch(month){
			/* Finding the number of days according to the months. */
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
					numDays = 31; break;

			case 4:
			case 6:
			case 9:
			case 11:
					numDays = 30; break;
			case 2:
					if(year % 4 == 0)
						numDays = 29;
					else
						numDays = 28;
					break;
		}

		for(day = 1; day  <= numDays ; day++){
			
			while(control2 != 0){
				day = start_day;
				control2=0;
				/* This control only works once. */
				/* The first entry of the user is to write to the file from the date. */
				/* If not, it always started at 1.Because of for loop day=1. */
			}

			if(day == finish_day && year == finish_year && month == finish_month){
				if(day < 10 && month >= 10)
					fprintf(fp,"0%d/%d/%d\n",day,month,year);
				else if(day < 10 && month < 10)
					fprintf(fp,"0%d/0%d/%d\n",day,month,year);
				else if(day >= 10 && month < 10 )
					fprintf(fp,"%d/0%d/%d\n",day,month,year);
				else
					fprintf(fp,"%d/%d/%d\n",day,month,year);
				control = 0;
				break;
				/* If it comes to the last day, it will be out of the loop. */
			}
			else{
				if(day < 10 && month >= 10)
					fprintf(fp,"0%d/%d/%d\n",day,month,year);
				else if(day < 10 && month < 10)
					fprintf(fp,"0%d/0%d/%d\n",day,month,year);
				else if(day >= 10 && month < 10 )
					fprintf(fp,"%d/0%d/%d\n",day,month,year);
				else
					fprintf(fp,"%d/%d/%d\n",day,month,year);
				/* Otherwise, writing to the file continues. */
			}
		}
		if(month == 12){
			year++;
			/* If the month is December the year is increased. */
		}
		month++; /* Month increases. */
	}
	fclose(fp); /* Closing File */
}


void printWeekday(){

	/********************************************************************** 

	## Takvimler her 400 yilda bir kendilerini tekrar ederler,yani her 400
	  	yilda bir aynı tarihler ayni gune denk gelir. 
	## 1600 , 1700 , 1800 , 1900
	## Yukaridaki yillar ozel yillardir .
	## Ornegin 2000 yili, 1600 yilindakine esit olur.Cunku 400 yil
		gecmistir ve takvim kendini tekrarlayacaktir.

	## Hesaplamada kullanilan formuller, formullerin altinda detaylica 
		aciklanmistir.

	************************************************************************/
	FILE *fp,*fp2;
	int day;
	int year,new_year;
	int month,new_month;
	int result;
	double G;
	char ch,*weekday,*monthName,*temp;
	int control = 1;
	
	
	fp = fopen("input_date.txt","r");
	fp2 = fopen("new_date.txt","w");
	/* Opening files. */
	
	if(fp == NULL){
		printf("ERROR : An error occured when opening the file. (input_date.txt)\n");
	} /* Eger input_date.txt dosyasi olmadan bu fonksiyon calisirsa hata verecektir. */	
	
	do{

		fscanf(fp,"%d%c%d%c%d",&day,&ch,&month,&ch,&year);


		if(month == 1 || month == 2){
			new_year = year - 1;
			/* Eger Ocak veya Subat ayiysa bu aylar artik yila denk gelebileceginden dolayi
				bir önceki yilin 11. ve 12. aylari hesaplamaya dahil olacaktir. */
		}
		else{
			new_year = year;
		}

		switch(month){
			case 1: new_month = 11; monthName = "January"; break;
			case 2: new_month = 12; monthName = "February"; break;
			case 3: new_month = 1; monthName = "March"; break;
			case 4: new_month = 2; monthName = "April"; break;
			case 5: new_month = 3; monthName = "May"; break;
			case 6: new_month = 4; monthName = "June"; break;
			case 7: new_month = 5; monthName = "July"; break;
			case 8: new_month = 6; monthName = "August"; break;
			case 9: new_month = 7; monthName = "September"; break;
			case 10: new_month = 8; monthName = "October"; break;
			case 11: new_month = 9; monthName = "November"; break;
			case 12: new_month = 10; monthName = "December"; break;
		}
		
		
		
		G = ((3 + (new_year - 1600) + (new_year/4) - (new_year/100) + (new_year/400) - 388 + (day-1) + (((2.6) * new_month) - 0.2)) - 2);
		result = ((int)G % 7);
		
		
		
		/*
		**
		**   Ilk oncelikle gunumuzde kullandigimiz takvimin 1600'lu yillardan itibaren tam olarak oturturuldugunu
		**  bilmemiz lazim.Dolayisiyla hesaplamalar 1600 yilina gore yapilmistir.
		**	 Ilk once 1600 yili ile hesaplayacagimiz yil arasinda kac tane artik gun oldugunu bulmamiz lazim.
		**	Bundan dolayi her 4 yilda bir gün olan artik yillarin sayisini bulacagız. +(year - 1600 / 4)
		**	Sonra yüz yildan kaynaklanan hatanin duzeltilmesi icin fazlalik olan gunleri cıkaracagız. -(year - 1600 / 100) !! Yani 100 ile bolunebilen yillar artik yil degildir !!
		** 	Daha sonra kalan yillar icin de her 400 yilda 1 gün ekleyecegiz. +(year - 1600)/400
		** 	 4 ile bolunebilen yillarin sayisi = (year-1600) / 4 = (year/4 - 400) = (year/4) - 400
		** 	 4 ile bolunebilen yuzyillarin sayisi = (year-1600) / 400 = (year/400 - 4) == (year/400) - 4
		**	 400 ile bolunebilen yuzyil sayisi = (year-1600) / 400 = (year/400 - 4) = (year/400) - 4
		**	 Tum bunlari birlestirirsek su formul ortaya cikar = *** L *** = ((year/4) - (year/100) + (year/400) - 388) !! L daha sonraki islemlerde kullanilacak !!
		**	 Burda bir referans gunu lazim. Referans gununu 1 Mart secelim. 1 Mart 1600 Carsamba gunune denk gelmekte.
		**	Yani carsambanın alttaki switch case yapisinda 3'e denk geldigini goruruz.Formulun basindaki 3 buradan gelmekte.
		**	 Simdi herhangi bir yilin 1 Mart Gununu su formulle hesaplariz : 
		**		G = (3 + (year-1600) + (year/4) - (year/100) + (year/400) - 388) isleminin 7'den modudur.
		**
		**	 Daha sonra herhangi bir yilin herhangi bir ayinin birinci gunune karsilik gelen günü de bulabiliriz:
		**		3 + (year - 1600) + L + ((2.6)*Month-0.2) 'nin 7 ile modunun alinmasi seklinde bulunur.
		**
		**	Son olarak aradigimiz gune bakicak olursak: Pazar 0'inci gune denk geldiginde gun-1'e bakariz.
		** 	Yani formul:  G = ((3 + (year - 1600) + (int)(year/4) - (int)(year/100) + (int)(year/400) - 388 + (day - 1) + 28 +((2.6)*month - 0.2)) - 2) seklinde olacaktir.
		**
		**
		*/

		/* !! Burada onemli olan aylarin mart,nisan,mayis,haziran,temmuz,agustos,eylul,ekim,kasim,aralik,ocak,subat diye gittigidir.
			Ocak ve Subat'ta artik yil olabileceginden bir onceki yilin 11. ve 12. aylarina bakilir. */

		switch(result){

				case 0: weekday = "Sunday"; break;
				case 1: weekday = "Monday"; break;
				case 2: weekday = "Tuesday"; break;
				case 3: weekday = "Wednesday"; break;
				case 4: weekday = "Thursday"; break;
				case 5: weekday = "Friday"; break;
				case 6: weekday = "Saturday"; break;
		}
		if(temp == weekday); 
		/* feof kullanildiginda son satiri iki kere dosyaya yazmasini engeller. */
		else{
			fprintf(fp2,"%9s,%9s %2d, %d\n",weekday,monthName,day,year);
		}

		temp = weekday; /* Dosya sonuna iki kere yazmayi onlemek icin kullanilir. */
	} while(!feof(fp));
	
	fclose(fp); fclose(fp2); /* Closing files. */
}