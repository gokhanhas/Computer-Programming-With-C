/* Gokhan Has - 161044067 */

#include <stdio.h>
#include <math.h>
#define PI 3.14   /* The compiler will write PI > 3.14 at the time */

double circle_area(double radius)
{
	double radiusSquare;
	radiusSquare = pow(radius,2);
	return (PI * radiusSquare);
	/* The Circle area's formula is PI x r x r */
}

double calc_hypotenuse(int side1, int side2)
{
	double hypotenuse,op1;
	/* Here op1 means operation1, so abbreviated operation (In Turkish > Ara islem manasında) */
	
	op1 = pow(side1,2) + pow(side2,2);
	hypotenuse = sqrt(op1);
	/* The hypotenuse formula is axa = bxb + cxc , so calculating hypotenuse */ 

	return (hypotenuse);
}

double calc_radius_of_smallest_circle(int side1, int side2)
{
	double radius,op2;

	op2 = calc_hypotenuse(side1,side2);
	radius = op2 / 2.0;
	/* The radius of smallest circle is hypotenuse / 2 . Because the rectangle's diagonal(kosegen) is the diameter(cap) of the circle */

	return (radius);
}

double calc_radius_of_largest_circle(int side1, int side2)
{
	double radius;

	if(side1 >= side2)
	{
		radius = side2 / 2.0;
	}

	else
	{
		radius = side1 / 2.0;
	}

	/* Here are the decisive is short side.Because the short side is equal to the diameter of the largest circle */
	return (radius);
}

double calc_area_of_smallest_circle(int side1, int side2)
{
	double radius,area;

	radius = calc_radius_of_smallest_circle(side1, side2);
	area = circle_area(radius);
    /* The Circle area's formula is PI x r x r , it is calculating and return */
	return (area);
}

double calc_area_of_largest_circle(int side1, int side2)
{
	double radius,area;

	radius = calc_radius_of_largest_circle(side1, side2);
	area = circle_area(radius);
	/* The Circle area's formula is PI x r x r , it is calculating and return */
	return (area);
}

double calc_area_of_square (int side)
{
	double area;
	/* This function calculate area of square and return */
	area = pow(side,2);
	return (area);
}

double calc_area_of_smallest_square(int side1, int side2)
{
	double area,side;

	if(side1>=side2)
	{
		side = side1;
	}
	else
	{
		side = side2;
	}

	area = calc_area_of_square (side);
	/* Here the smallest square's side surrounding the rectangle must be the long side of the rectangle */
	/* So, calculation of the smallest square area and return */
	return (area);
}

double calc_area_of_largest_square(int side1, int side2)
{
	double area;

	if(side1 >= side2)
	{
		area = calc_area_of_square (side2);
	}
	else
	{
		area = calc_area_of_square (side1);
	}

	/* Here too, the defining side will be the short side.Because a rectangle will fit into a square at the side equal to the length of the short side. */
	return (area);
}

void display_results(double largest_circle, double largest_square, double smallest_circle, double smallest_square)
{
	int side1,side2;

	printf("Enter first side for rectangle > ");
	scanf("%d",&side1);
	printf("Enter second side for rectangle > ");
	scanf("%d",&side2);
	/* Get the side's length from user */

	
	largest_circle = calc_area_of_largest_circle(side1,side2);
	largest_square = calc_area_of_largest_square(side1, side2);
	smallest_circle = calc_area_of_smallest_circle(side1, side2);
	smallest_square = calc_area_of_smallest_square(side1, side2);
	/* Making the necessary assignment */


	printf("\nThe area of the largest circle that fits inside a rectangle > %.2lf\n", largest_circle );
	printf("The area of the largest square that fits inside the rectangle > %.2lf\n", largest_square );
	printf("The area of the smallest circle that surrounds the same rectangle > %.2lf\n", smallest_circle);
	printf("The area of the smallest square that surrounds the same rectangle > %.2lf\n", smallest_square );
	/* Print the results */
}

int main()
{
	printf("This program calculate > \n");
	printf("1. The area of the largest circle that fits inside a rectangle\n");
	printf("2. The area of the largest square that fits inside the rectangle\n");
	printf("3. The area of the smallest circle that surrounds the same rectangle\n");
	printf("4. The area of the smallest square that surrounds the same rectangle\n\n\n");
	/* Specification of the purpose of the program */
	
	double largest_circle,largest_square,smallest_circle,smallest_square;
	display_results(largest_circle,largest_square,smallest_circle,smallest_square);

	return 0;
}