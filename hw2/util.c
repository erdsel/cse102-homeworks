/*
210104004131 - SELEN ERDOĞAN - HM1
*/
/*
This code contains several different functions and is used for different purposes. 
At the beginning of the code, the libraries "stdio.h" and "math.h" are included and another library called "util.h" is called.
These libraries contain standard input/output functions, math operations, and other auxiliary functions necessary for the program to run.
The code is named according to the purposes of the variables. Functions take parameters and act accordingly. 
Operations in the code are managed using if/else statements and switch/case statements. 
The code also includes some checks for errors.
*/


#include <stdio.h> /*First, we include the stdio.h library. This allows us to use standard input/output functions.*/
#include <math.h>
#include "util.h"
/*
The first function, "isLeapYear", checks if the year is a leap year. 
If the year is divisible by 4 and not by 100, or if it is divisible by 400 and not divisible by 4000, it is considered a leap year and 1 is returned. 
Otherwise, 0 is returned.
*/
int isLeapYear(int year) {
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0 && year % 4000 != 0)) {
        return 1;
    }
    else {
        return 0;
    }
}
/*
The second function, "isInRange", checks if a given grade is between 0 and 100. 
If the grade is in this range, 1 is returned. Otherwise, 0 is returned.
*/
int isInRange(float grade) {
    if (grade >= 0 && grade <= 100) {
        return 1;
    }
    else {
        return 0;
    }
}
/*
The third function, calculateFinalGrade, calculates a student's final grade using three exam grades and two homework grades. 
Exam grades are taken into account by 60% and homework grades by 40%. 
The final calculation result is returned as the final grade.*/
float calculateFinalGrade(float exam1, float exam2, float exam3, float assignment1, float assignment2) {
    float finalGrade;
    finalGrade = (exam1 + exam2 + exam3) / 3 * 0.6 + (assignment1 + assignment2) / 2 * 0.4;
    return finalGrade;
}
/*
The fourth function, "calculate", performs the operation between two numbers in the user-desired format and with the operator.
 First, the operation is performed according to the format (S or I) entered by the user. If the "S" format is selected, the user must also enter the values "m" and "n".
 Then, according to the operator entered by the user, the operation is performed between the given numbers and the result is printed on the screen.
*/
void calculate(char format, char operator){
    int result_int, m,n;
    double result_float, num1, num2;
    switch (format)
    {
    case 'S':
       printf("Enter m and n values: ");
       scanf("%d %d", &m, &n);
       
        break;

    case 'I':
    break;
    
    default:
    printf("Invalid format. Please enter S  or I\n");
    

        return;
    }
    printf("Enter the first operand: ");
    scanf("%lf", &num1);
    
    if (operator != '!')
    {
       printf("Enter the second operand: ");
       scanf("%lf", &num2);
       
    }
    switch (operator)
    {
    case '+':
       result_int=num1+num2;
       result_float=num1+num2;
        break;
    case '-':
       result_int=num1-num2;
       result_float=num1-num2;
        break;
    
    case '*':
       result_int=num1*num2;
       result_float=num1*num2;
        break;
    
    case '/':
      if(num2 == 0){
        printf("Error: Division by zero\n");
        return;
      }
        result_int=(int)num1/(int)num2;
        result_float= (double) num1 / (double) num2;
        break;

    case '!':
       result_int=1;
       for(int i=1;  i<= num1; i++){
        result_int *= i;
       }
       result_float = (double) result_int;
        break;

    case '^':
       result_int=pow(num1,num2);
       result_float=pow(num1,num2);
        break;

    case '%':
       result_int=(int)num1 % (int)num2;
       result_float= (double)num1 - ((double)num1 / (double)num2 ) * (double)num2;
        break;

    default:
    printf("Invalid operator. Please enter +, -, *");

        return;
    }

    if(format == 'S'){
        if(n>m){

                printf("ERROR n should be less than or equal to m/n");
                return;

        }
       

    
       printf("%0*.*fe%d\n", m,n,result_float, (int)log10(result_float));
    




    }
    else{
    	if(operator == '!'){
    	printf("%.0lf%c=%d\n",num1,operator, result_int);
    	}else{
    	printf("%.0lf%c%.0lf=%d\n",num1,operator,num2, result_int);
    	}
        
    }
    
}
