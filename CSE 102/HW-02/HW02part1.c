// Gokhan Has - 161044067
// Part 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int control();
void printMenu(int student_count);
void printCase1_OR_2(int index, int max_min, char grade);
void printCase3(int countA, int countB, int countC, int countD, int countF);
void printCase4(double avg, double sum, int student_count);
void printCase5(int indexMax, int max , char gradeMax, int indexMin, int min, char gradeMin,
	            int countA, int countB, int countC, int countD, int countF,
	            double avg, double sum, int student_count);
/* Defining th functions which are going the use in code */


int main()
{
	srand(time(NULL);
	/* It must be used for random number */

	int student_count;
	int control2,grade,i,selection;
	char letter_grade;
	double avg=0,sum=0;
	int count=0,countA=0,countB=0,countC=0,countD=0,countF=0;
	int max=0,indexMax;
	int min=100,indexMin;
	char gradeMax,gradeMin;
	/* Defining variables */
	
	
	student_count = control();
	/* This is control the student_count's range */

	

	for(i=0;i<student_count;i++)
	{
		grade = rand() % 100;
		/* Assign random numbers to grades */
		
		
		if(count==10)
		{
			printf("\n");
			count=0;
		}
		count++;
		/* This if block and counter are used to print 10x10 grades */



		if(grade >= 90 && grade <= 100)
		{
			letter_grade = 'A';
			countA++;
			/* This is the counter that counts to which student get 'A' */
			/* The same way, below there are counters that count who gets the other grades */
		}
		else if(grade >= 80 && grade <= 89)
		{
			letter_grade = 'B';
			countB++;
		}
		else if(grade >= 70 && grade <= 79)
		{
			letter_grade = 'C';
			countC++;
		}
		else if(grade >= 60 && grade <= 69)
		{
			letter_grade = 'D';
			countD++;
		}
		else
		{
			letter_grade = 'F';
			countF++;
		}
		
		printf("%3.d  ",grade);
		/* Here, .3 used to look nice */
			

		sum = sum + grade;
		/* This sum will be used when calculating the average */

		if(grade > max)
		{
			max = grade;
			indexMax = i+1; 
			// index must be i+1.Because i starts from 0.
			gradeMax = letter_grade;
			/* This code block find a maxscore,index and grade*/
		}

		if(grade < min)
		{
			min = grade;
			indexMin = i+1; 
			// index must be i+1.Because i starts from 0.
			gradeMin = letter_grade;
			/* This code block find a minscore,index and grade */
		}

	}
	printf("\n");
	

	control2 = 0;
	while(control2 >= 0)
	{
		printMenu(student_count);

		printf("\t\t\tMake Selection > ");
		scanf("%d",&selection);
		/* Selection from the user */

		
		switch(selection)
		{
			case 1:
				printf("\nMost Succesfully Student : \n");
				printCase1_OR_2(indexMax,max,gradeMax);
				break;

			case 2:
				printf("\nMost Unsuccesfully Student : \n");
				printCase1_OR_2(indexMin, min, gradeMin);
				break;
			
			case 3:
				printCase3(countA, countB, countC, countD, countF);
				break;

			case 4:
				printCase4(avg, sum, student_count);
				break;

			case 5:
				printCase5(indexMax, max , gradeMax, indexMin, min,  gradeMin,
	            		 	countA, countB, countC, countD, countF,
	            			avg, sum, student_count);

				break;
			
			case -1:
				control2--;
				break;

			default:
				printf("\nFalse Selection !!!\n");
				break;

			// Here, this code block is menu
			// If the user select 1 or 2, this program calls printCase1_OR_2 function
			// If the user select 3 --> printCase3 , 4 --> printCase4 and 5 --> printCase5
			// If the user select -1, this program will exit.
			// For other number, this program give an error 'False Selection'
			
		}
	}
	return 0;
}

int control()
{
	int control=0;
	int student_count;
	while(control >= 0)
	{
		/* This is the control function if the student_count between 3 and 50 */
		/* If it is not, again the enter a student_count */
		printf("Enter student count > ");
		scanf("%d",&student_count);

		if(student_count >=3 && student_count <=50)
		{
			control--;
		}
		else
		{
			printf("\nNot in range!!\n");
		}
	}
	return student_count;
}


void printMenu(int student_count)
{
	printf("\n----------------------------------------------\n");
	printf("\nStudents Score Calculator Menu for %d Students\n",student_count);
	printf("1-) Most Succesfull Student\n");
	printf("2-) Most Unsuccesfull Student\n");
	printf("3-) Letter Grade Statistics\n");
	printf("4-) Calculate Average\n");
	printf("5-) Show all Datas\n");
	/* Print the menu function */
}

void printCase1_OR_2(int index, int max_min, char grade)
{
	printf("Index : %d\n",index);
	printf("Score : %d\n",max_min);
	printf("Letter Grade : %c\n",grade);
	/* This is the function which prints case 1 or case 2*/
}


void printCase3(int countA, int countB, int countC, int countD, int countF)
{
	printf("\n%d student got letter grade 'A'\n",countA);
	printf("%d student got letter grade 'B'\n",countB);
	printf("%d student got letter grade 'C'\n",countC);
	printf("%d student got letter grade 'D'\n",countD);
	printf("%d student got letter grade 'F'\n",countF);
	/* This is the function which prints case 3 */
}

void printCase4(double avg, double sum, int student_count)
{
	avg = sum / student_count;
	printf("\nThe Avarage Score of %d Student is %.2lf\n",student_count, avg);
	/* This is the function which prints case 4 */
}


void printCase5(int indexMax, int max , char gradeMax, int indexMin, int min, char gradeMin,
	            int countA, int countB, int countC, int countD, int countF,
	            double avg, double sum, int student_count)
{
	printf("\nMost Succesfully Student : \n");
	printCase1_OR_2(indexMax,max,gradeMax);
	printf("\nMost Unsuccesfully Student : \n");
	printCase1_OR_2(indexMin, min, gradeMin);
	printCase3(countA, countB, countC, countD, countF);
	printCase4(avg, sum, student_count);
	/* This is the function which prints case 5 */
}
