/*
** main.c:
**
** The test program for the homework.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.14
** 
*/

// Gokhan Has - 161044067
// CSE 102 - HW04

#include <stdio.h>


#include "hw4_lib.h"
#include "hw4_io.h"

/*
**
**    !!! Bu kodda diger test fonksiyonlari yorum
**	      satiri seklinde alt kisimlara eklenmistir. !!!
**
**
*/

/*
** Testing derivative calculations..
**
*/
void test_compare_derivatives() {
	double f(double x) { return x*x; }
	double d1(double x) { return 2.0*x; }
	double d2(double x) { return 2.0; }
	double e1, e2;
	int res = compare_derivatives(f, d1, d2, 1.0, 0.0001, &e1, &e2);
	printf("%f %f\n",e1,e2);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_compare_derivatives();
	return (0);
} /* end main */



/*
**  
	Testing integral calculations....
	**********************************
	
	void test_compare_integral()
	{
		double xs=1.0, xe=3.0;
		double f(double x) {return x*x;}
		double integral_sonucu = (((xe*xe*xe)-(xs*xs*xs)) / 3); // Buraya direk integralin sonucu olan 8.67'de yazilabilirdi.
		double error,result;
	
		result = integral(f,xs,xe,10000);
		error = result - integral_sonucu;
		printf("\nResult : %lf\nError Integral : %lf\n",result,error);
	}

	// ******************************************************************************
	// Bu fonksiyonda integral sinirlari girilir ve integral_sonucu degiskeninde 
	// gercek cozum yazilir.Ornegin x*x fonksiyonunun integrali x*x*x / 3 dür.
	// üst sinirdan alt sinir cikarilarak gercek deger bulunur.
	// integral_sonucu degiskenine direk sonucta atanabilir.Delta 10000 girilmistir.
	// ******************************************************************************
**
*/


/*
**
	Testing integral2 calculations.......
	**************************************

	void test_compare_integral2()
	{
		double xs=1.5, xe=3.0;
		double ys=4.5, ye=7.0;
		double f(double x, double y) {return (5*x*x*y + x*y);}

		double integral_sonucu = 614.531;
		// Bu integralin sonucu https://www.symbolab.com/solver/double-integrals-calculator/ sitesinden
	    // hesaplanmistir.Sitede ilk x'e gore integral daha sonra y'e gore integral alinmaktadir.

		double error,result;

		result = integral2(f,xs,xe, ys,ye,10000);
		error = result - integral_sonucu;
		printf("\nResult : %lf\nError Double Integral : %lf\n",result,error);
	}
		
	// ***************************************************************************************************
	// Bu fonksiyonda onceden integralin sonucunu bilmek gerekir.Ornekteki f fonksiyonu (5*x*x*y+x*y)
	// belirtilen araliklarda hesaplanip 614.531 bulunmustur.Daha sonra integral2() fonksiyonuna 
	// parametreler gonderilmis ve fonksiyonun hesapladigi deger result degiskenine atanamistir.
	// Aradaki fark ise error degiskenine atanmis olup, ekrana basilmistir.
	// ***************************************************************************************************
**
*/


/*
**
	Testing polynomial functions.......
	*************************************


	void test_all_polynomial_functions()
	{
		// a0 --- en buyuk x'li terimin katsayisini temsil eder.Ornegin write_polynomial3
		// icin a0, x^3 lu terimin katsayisidir.

		double a0,a1,a2,a3,a4;

		read_polynomial3(&a0,&a1,&a2,&a3);
		write_polynomial3( a0,  a1,  a2,  a3);

		read_polynomial4(&a0,&a1,&a2,&a3,&a4);
		write_polynomial4( a0,  a1,  a2,  a3,  a4);
	}
	

	// ********************************************************************************
	// hw4_io.c deki fonksiyonlarin hepsi bu fonksiyonda test edilmistir.
	// ilk once lokal degiskenler tanimlanmistir.Her bir derecedeki fonksiyonlar icin
	// ilk once katsayilar alinmis, daha sonra polinom ekrana basilmistir.
	// ********************************************************************************

**
*/