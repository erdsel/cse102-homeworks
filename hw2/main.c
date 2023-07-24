#include <stdio.h>
#include "util.h"


int main() {
  /*
The code defines a variable named "year" to store an integer value.
The user is prompted to enter a year value using the printf function and the input is read with the scanf function, which assigns the value to the "year" variable.
The code then checks whether the entered year is a leap year or not, by calling a function named "isLeapYear" 
And passing the "year" value as an argument.
If the "isLeapYear" function returns true, which indicates that the year is a leap year, the code prints a message indicating that the year is a leap year. 
Otherwise, if the "isLeapYear" function returns false, the code prints a message indicating that the year is not a leap year.
Overall, the code determines whether the entered year is a leap year or not and outputs the result to the user.
  */
 int year;
    printf("Please enter a year: ");
    scanf("%d", &year);

    if (isLeapYear(year)) {
        printf("%d is a leap year.\n", year);
    }
    else {
        printf("%d is not a leap year.\n", year);
    }

/*

This code defines a function named "calculate" that performs basic arithmetic operations on two operands based on the input format and operator provided by the user. 
The function first checks the input format, which can be either 'S' or 'I'.
If the format is 'S', the function prompts the user to enter values for 'm' and 'n', and then calculates the result using floating-point arithmetic with the specified format. 
If the format is 'I', the function calculates the result using integer arithmetic.
Next, the function prompts the user to enter two operands and performs the arithmetic operation based on the specified operator.
If the operator is '/', the function checks if the second operand is zero and outputs an error message if so. 
If the operator is '!', the function calculates the factorial of the first operand. 
Finally, the function outputs the result in the specified format based on the input format.
The main function prompts the user to enter the output format and arithmetic operator, and then calls the "calculate" function to perform the operation and output the result.

*/

 char format, operator;
    printf("Enter the format of output (S or I): ");
    scanf(" %c", &format);
    printf("Enter the operation(+,-,*,/,!,^ or %%): ");
    scanf(" %c", &operator);
    calculate(format,operator);


/*
This program takes as input the grades of 3 exams and 2 assignments from a student, calculates their final grade based on a weighted average formula, 
and determines if they passed or failed based on the final grade. 
The program ensures that all input grades are within the valid range of 0-100 using the isInRange() function. 
If any of the input grades are not within this range, the program prompts the user to enter valid grades. 
Finally, the program outputs the final grade and a pass/fail message.
*/



 float exam1, exam2, exam3, assignment1, assignment2, finalGrade;
    int validInput = 0;

    while (!validInput) {
        printf("Enter 3 exams grades of student: ");
        scanf("%f %f %f", &exam1, &exam2, &exam3);

        printf("Enter 2 assignment grades of student: ");
        scanf("%f %f", &assignment1, &assignment2);

        if (isInRange(exam1) && isInRange(exam2) && isInRange(exam3) && isInRange(assignment1) && isInRange(assignment2)) {
            validInput = 1;
        }
        else {
            printf("Invalid input! Grades must be between 0 and 100.\n");
        }
    }

    finalGrade = calculateFinalGrade(exam1, exam2, exam3, assignment1, assignment2);
    printf("Final Grade: %.1f ", finalGrade);

    if (finalGrade >= 60) {
        printf("Passed!\n");
    }
    else {
        printf("Failed!\n");
    }


    return(0);
}
