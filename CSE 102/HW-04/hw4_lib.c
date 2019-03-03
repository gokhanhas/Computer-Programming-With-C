/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/

// Gokhan Has - 161044067
// CSE 102 - HW04

#include <stdio.h>
 
#include "hw4_lib.h"


double integral(double f(double x), double xs, double xe, double delta){

	/*  ********************** NOT **********************
		Delta ne kadar büyükse sonuc o kadar dogru cikar.
	*/

	/* Dikdortgenler yontemi kullanilarak integral hesaplama kullanilmistir.
	   Bu yöntemde,fonksiyon ile eksen arasinda kalan bolge,kucuk dikdortgenlere
	   ayrilmakta ve olusan bu dikdortgenlerin alanlari toplanmaktadir.
	*/
	
	double result=0.0;
	int k;
	double dx = ( xe - xs ) / delta;

	/* Integral hesaplanirken [xs,xe] araligi delta kadar parcaya bolunur ve dx'e atanir.  */
	/* Dikdortgenlerin alani sol toplamlar,sag toplamlar ve orta toplamlara gore bulunabiliyorken
	   bu kod sag toplamlara gore hesaplamistir.    */
	
	for(k=1;k <= delta;k++){

		result += ( dx ) * ( f(xs + k * dx) );
		/* Burdaki xs + k*dx sag toplamlara gore hesaplandigindan formulden oyle yazilmistir.  */
		/* k hangi dikdortgenin alaninin hesaplandigini isaret eder.k=1 ken 1. dikdortgenin
		   alani hesaplanmaktadir.  */
		/* Bu islem deltaya kadar tekrarlanir ve integrale yakin bir deger bulunur  */
	}

	return result;
	/* Sonucun dondurulmesi */
	/* Delta'ya genelde 10000 verilmesi durumunda integralin sonucuna daha yakin bir deger ciktigi gozlemlenmistir. */

}


double integral2(double f(double x, double y), double xs, double xe, double ys, double ye, double delta){

	double hx = (xe - xs) / delta;
	double hy = (ye - ys) / delta;
	/* Cift katli integralde de normal integraldeki formul kullanilmistir. */
	/* Burda ilk once x'e gore integral hesaplanir, daha sonra ise y'ye göre hesaplanir. */
	/* Delta, ne kadar buyurse sonuc o kadar dogru cikar.10000 makul degerdir. */
	double result = 0.0,result2=0.0;
	int i,j;
	double dx,dy;

	for(i=1; i <= delta; i++){
		for(j=1;j <= delta;j++){
			/* Yukaridaki normal integral hesabi sag toplamlar yontemine gore hesaplanirken
			   burdaki cift katli integralde orta toplamlar yontemine gore hesapladim.Assagidaki
			   formulde '/2' yani 2'ye bolmemizin sebebi orta toplamlar yontemine gore cozuldugundendir.  */
			dx = xs + (hx / 2) + (i * hx);
			dy = ys + (hy / 2) + (j * hy);
			result += hy * hx  * (f(dx,dy));
			/* Tekrar fonksiyonda f(dx,dy) yazilmasinin sebebi dikdortgenlerin tekrarlanarak toplanmasidir.  */
 		}
 		
	}

	return (result);
}


int derivatives(double f(double a), double x, double eps, double *d1, double *d2){


	if (eps == 0.0){
		*d1 = 0.000001;
		*d2 = 0.000001;
		return (-1);
		/* Turev formulunde eps degeri paydaya yazildigindan eger sifir girerse kullanici,
		   bolme hatasi olusur.Bundan dolayi (-1) return eder.Ve turevlere direk (0.000001)
		   atanir.Bu sayinin atanmasi hata oldugunu anlamamizi saglar.   */ 
	}

	else{

		*d1 = ( f(x+eps) - f(x-eps) ) / (2*eps);

		*d2 = ( f(x+eps) - 2*f(x) + f(x-eps)) / (eps*eps);
		
		/* Diger durumda birinci turev (*d1) ve ikinci turev(*d2), pdf'te yazilmis olan
		   formulle bulunur ve (1) return edilir.   */
		
		return (1);
	}
}


int compare_derivatives(double f(double a), double d1(double b), double d2(double b), double x, double eps, double *e1, double *e2){

	double t1,t2,a;
	a = derivatives(f,x,eps,&t1,&t2);
	/* Kullanicinin hesaplamis oldugu turevle fonksiyonun buldugu turev karsilastirildigindan, ilk once
	   derivatives() fonksiyonunda turevler hesaplanir. t1 ve t2 degiskenlerine atanir.   */

	if(a == -1){
		printf("Derivatives() fonk. -1 return etmistir.Yani hatali değer girilmistir!!!\n");
		/* Eger derivatives() fonk. -1 ise hatali deger vardir ve bu kullaniciya bildirilir.  */
	}

	
	else if(a == 1){
		
		if(d1(x) > t1)
			*e1 = d1(x) - t1;
		else if(d1(x) <= t1)
			*e1 = t1 - d1(x);

		/* Bir nevi mutlak deger uygulanip farkin negatif olmasi engellenmistir. */

		if(d2(x) > t2)
			*e2 = d2(x) - t2;
		else if(d2(x) <= t2)
			*e2 = t2 - d2(x);

	}
	
	return (0);
}


int find_roots(double f(double x), double * x1, double * x2, double * x3, double * x4){

	
}