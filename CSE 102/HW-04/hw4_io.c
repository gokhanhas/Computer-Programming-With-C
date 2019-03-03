/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/

// Gokhan Has - 161044067
// CSE 102 - HW04

#include <stdio.h>
#include "hw4_io.h"

int read_polynomial3(double *a0, double *a1, double *a2, double *a3){

	double k0,k1,k2,k3;
	/* Burada lokal degiskenler tanimlanir daha sonra bu degiskenler
		global degiskenlere atanacak.Global degiskenler pointer 
		turunde olduğundan katsayilari return kullanmadan return etme
		imkanina sahibiz. */
	
	printf("Enter coefficients of a degree-3 polynomial >\n");
	printf("Enter a0 > "); scanf("%lf",&k0);
	printf("Enter a1 > "); scanf("%lf",&k1);
	printf("Enter a2 > "); scanf("%lf",&k2);
	printf("Enter a3 > "); scanf("%lf",&k3);
	/* Kullanicidan katsayilarin alinmasi */
	
	*a0 = k0;
	*a1 = k1;
	*a2 = k2;
	*a3 = k3;
	/* Alinan katsayilarin, global değiskenlere (pointer) atanmasi */
	
	return (0);
}


int read_polynomial4(double *a0, double *a1, double *a2, double *a3, double *a4){

	double k0,k1,k2,k3,k4;
	/* Burada lokal degiskenler tanimlanir daha sonra bu degiskenler
		global degiskenlere atanacak.Global degiskenler pointer 
		turunde olduğundan katsayilari return kullanmadan return etme
		imkanina sahibiz. */
	
	printf("Enter coefficients of a degree-4 polynomial >\n");
	printf("Enter a0 > "); scanf("%lf",&k0);
	printf("Enter a1 > "); scanf("%lf",&k1);
	printf("Enter a2 > "); scanf("%lf",&k2);
	printf("Enter a3 > "); scanf("%lf",&k3);
	printf("Enter a4 > "); scanf("%lf",&k4);
	/* Kullanicidan katsayilarin alinmasi */
	
	*a0 = k0;
	*a1 = k1;
	*a2 = k2;
	*a3 = k3;
	*a4 = k4;
	/* Alinan katsayilarin, global değiskenlere (pointer) atanmasi */
	
	return (0);
}


void write_polynomial3(double a0, double a1, double a2, double a3){

	/* 
	   
	   *************************** NOT *******************************
	   * Buradaki a0 --> x^4 lu terimin katsayisini belirtir.        *
	   * a1 ise x^3 lu terimin katsayisini belirtir....				 *
	   ***************************************************************

	*/

	int size=4;
	double array[4]={a0,a1,a2,a3};
	double array2[4]={a0,a1,a2,a3};
	int i,pow;
	/* Gerekli degiskenlerin tanimlanmasi.Burda 2 tane array kullandım.
		Cunku, birinde gercek degerleri tutarken,digerinde ise sayinin
		pozitif ve negatif olma durumuna göre mod alarak arrayde tuttum. */
	/* 	Yani array[4] de modlarini alarak sayiyi tuttum. 				 */


	for(i=0;i<4;i++){

		if(array[i] > 0){
			/* Sayi pozitifse 1'e gore modu alinir.Burdaki amac tamsayi oldugunu
				bulmaktir.Ornegin 5.0 girilirse bunu 5 basmak icindir.  */
			while(array[i] >= 1)
				array[i] -= 1;
		}

		else if(array[i] < 0){
			/* Sayi negatifse  -1'e gore modu alinir.Burdaki amac tamsayi oldugunu
				bulmaktir.Ornegin -4.0 girilirse bunu -4 basmak icindir.  */
			while(array[i] <= -1)
				array[i] += 1;
		}

		else{
			array[i] = array[i];
			/* Eger sayi sifirsa, yine kendisine esitler. */
		}
	}

	
	pow = 3;
	// Burdaki for dongusu x^3, x^2'li terimleri basmak icin kullanilir.
	// Her islemden sonra pow 1 azaltilir.Ama for dongusu "size-2" ye kadar
	// gider.Yani size=4 oldugundan en son x^2 li terim basilir.
	for(i=0;i<size-2;i++){
		
		if(array2[i] == 1.0){
			printf("+x^%d ",pow);
			pow--;
		}
		else if(array2[i] == -1.0){
			printf("-x^%d ",pow);
			pow--;
		}
		else if(array2[i] == 0.0){
			pow--;
		}
		/* Yukaridaki if-else kod bloklarinda ozel durum olan katsayinin
			1.0,-1.0 veya 0.0 olma durumuna bakilir.			*/

		/* Asagidaki else blogunda ise diger durumlara bakilir */
		else{
		
			if(array[i] == 0.0 && array2[i] > 0){
				printf("+%dx^%d ",(int)array2[i],pow);
				pow--;
			/* Sayinin modu 0.0 ve sayi pozitif ise anliyoruzki tam sayi
				girilmistir.Ornegin 6.0 gibi.Dolayisiyla katsayilarin
				bulundugu arrayde (array2[]) o elemani int'a cast ederek
				basiyoruz.Burdaki ornekte 6 basicak.       				*/
			}

			else if(array[i] == 0.0 && array2[i] < 0){
				printf("%dx^%d ",(int)array2[i],pow);
				pow--;
			/*	Sayinin modu 0.0 ve sayi negatif ise anliyoruzki tam sayi
				girilmistir.Ornegin -4.0 gibi.Dolayisiyla katsayilarin
				bulundugu arrayde (array2[]) o elemani int'a cast ederek
				basiyoruz.Burdaki ornekte -4 basicak.                   */
			}
		
			else if(array2[i] > 0){
				printf("+ %.1lfx^%d ",array2[i],pow);
				pow--;
			/* Eger sayinin modu 0.0 degil (yani tam sayi degil) ve 0'dan da
				buyuk oldugu icin '+' operatoruyle birlikte basicak.Ornegin
				4.5 girildiginde 4.5x^%d basicak.(%d == pow)           */
			}

			else{
				printf("%.1lfx^%d ",array2[i],pow);
				pow--;
			/*	Burda ise sayinin negatif ama tam sayi olmadigini anliyoruz.
				Ornegin -3.2 gibi.                     */
			}
		}
	}

// ******************************************************************
	/*  Assagidaki kod blogu x^1 li ifadeleri sadece x li
		sekilde basmak icin yazilmistir.Yukaridaki kod ile
		aynidir.Sadece pow kullanilmamistir.Aciklamalar ise yukarda
		for dongusunde yapildigindan bir daha yazilmamistir.   */
// *******************************************************************

	if(a2 == 1.0)
		printf("+x ");
	else if(a2 == -1.0)
		printf("-x ");
	else if(a2 == 0.0)
			;
	else{
		
		if(array[2] == 0.0 && a2 > 0)
			printf("+%dx ",(int)a2);

		else if(array[2] == 0.0 && a2 < 0)
			printf("%dx ",(int)a2);
		
		else if(a2 > 0)
			printf("+%.1lfx ",a2);

		else
			printf("%.1lfx ",a2);
	}

// *******************************************************************
	/*  Assagidaki kod blogu x li ifadeleri sadece katsayili
		sekilde basmak icin yazilmistir.Yukaridaki kod ile
		aynidir.Sadece pow kullanilmamistir.Aciklamalar ise yukarda
		for dongusunde yapildigindan bir daha yazilmamistir.   */
// *******************************************************************
	if(a3 == 1.0)
		printf("+1 ");
	else if(a3 == -1.0)
		printf("-1 ");
	else if(a3 == 0.0)
			;
	else{
		
		if(array[3] == 0.0 && a3 > 0)
			printf("+%d ",(int)a3);

		else if(array[3] == 0.0 && a3 < 0)
			printf("%d ",(int)a3);
		
		else if(a3 > 0)
			printf("+%.1lf ",a3);

		else
			printf("%.1lf ",a3);
	}
		
	printf("\n");
}



void write_polynomial4(double a0, double a1, double a2, double a3, double a4){

	double array[5]={a0,a1,a2,a3,a4};
	double array2[5]={a0,a1,a2,a3,a4};
	int i,pow;
	int size=5;

	/* 	
		*********************************** NOT *************************************
		* write_polynomial3' de her seyin acik acik yazildiginden ayni aciklamalari *
		* bu fonksiyonda da yazip kodu daha karmasik hale getirmemek icin daha az   *
		* aciklamalar eklenmistir.Soru isaretleri varsa write_polynomial3'deki      *
		* aciklamalara bakilabilir.						    *
		*****************************************************************************
	*/

	for(i=0;i<5;i++){
		/* Sayinin tam sayi olup, olmadigini anlamak icin modunun alinmasi */
		if(array[i] > 0){

			while(array[i] >= 1)
				array[i] -= 1;
		}

		else if(array[i] < 0){

			while(array[i] <= -1)
				array[i] += 1;
		}

		else{
			array[i] = array[i];
		}
	}

	
	pow = 4;
	/* Dongu icinde x^4, x^3 ve x^2 li terimlerin katsayilariyla birlikte basilmasi */
	/* Soru isaretleri varsa write_polynomial3 fonksiyonundaki aciklamalara bakilabilir. */
	for(i=0;i<size-2;i++){
		
		if(array2[i] == 1.0){
			printf("+x^%d ",pow);
			pow--;
		}
		else if(array2[i] == -1.0){
			printf("-x^%d ",pow);
			pow--;
		}
		else if(array2[i] == 0.0){
			pow--;
		}
		else{
		
			if(array[i] == 0.0 && array2[i] > 0){
				printf("+%dx^%d ",(int)array2[i],pow);
				pow--;
			}

			else if(array[i] == 0.0 && array2[i] < 0){
				printf("%dx^%d ",(int)array2[i],pow);
				pow--;
			}
		
			else if(array2[i] > 0){
				printf("+ %.1lfx^%d ",array2[i],pow);
				pow--;
			}

			else{
				printf("%.1lfx^%d ",array2[i],pow);
				pow--;
			}
		}
	}
// *****************************************************
	/* x^1 seklinde basmamak icin yapilan islemler */
	/* Soru isaretleri varsa write_polynomial3 fonksiyonundaki aciklamalara bakilabilir. */
	if(a3 == 1.0)
		printf("+x ");
	else if(a3 == -1.0)
		printf("-x ");
	else if(a3 == 0.0)
		;
	else{
		
		if(array[3] == 0.0 && a3 > 0)
			printf("+%dx ",(int)a3);

		else if(array[3] == 0.0 && a3 < 0)
			printf("%dx ",(int)a3);
		
		else if(a3 > 0)
			printf("+%.1lfx ",a3);

		else
			printf("%.1lfx ",a3);
	}

// ****************************************************
	/* x^0 basmamak icin yani sadece katsayiyi basmak icin yapilan islemler. */
	/* Soru isaretleri varsa write_polynomial3 fonksiyonundaki aciklamalara bakilabilir. */
	if(a4 == 1.0)
		printf("+1 ");
	else if(a4 == -1.0)
		printf("-1 ");
	else if(a4 == 0.0)
		;
	else{
		
		if(array[4] == 0.0 && a4 > 0)
			printf("+%d ",(int)a4);

		else if(array[4] == 0.0 && a4 < 0)
			printf("%d ",(int)a4);
		
		else if(a4 > 0)
			printf("+%.1lf ",a4);

		else
			printf("%.1lf ",a4);
	}

	printf("\n");
}



/* 

*********************   ORNEK MAIN FONKSIYONU ****************************
																				 
	#include <stdio.h>
	#include "hw4_io.h"
	
	int main(){																	 
			
		double a0,a1,a2,a3,a4;                                                        
                                                                                            
		read_polynomial3(&a0,&a1,&a2,&a3);                                                               
		write_polynomial3(a0,a1,a2,a3);                                          
                                                                                             
		read_polynomial4(&a0,&a1,&a2,&a3,&a4);                                            
		write_polynomial4(a0,a1,a2,a3,a4);                                               
                                                                             
		return (0);                                                                       
	}                                                                                                 


*************************************************************************


*/
