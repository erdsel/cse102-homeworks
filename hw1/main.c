/*
210104004131 - SELEN ERDOĞAN - HM1
*/

#include <stdio.h>
#include "util.h"


int main() {
  

    /*PART 1*/
    
    int num1, num2, result;
   
    printf("Enter the first integer for GCD: ");
    scanf("%d", &num1);
    printf("Enter the second integer for GCD: ");
    scanf("%d", &num2);
    result = part1(num1, num2);
    printf("GCD: %d\n", result);

    /*PART 2*/
     char number1[5], number2[5], *number3;
    
    printf("Enter first number for summing: ");
    scanf("%s", number1);
    printf("Enter second number for summing: ");
    scanf("%s", number2);
    printf("\nFirst number: %s", number1);
    printf("\nSecond number: %s", number2);
    printf("\n");
    printf("Result:\n");
    printf("%5s\n", number1);
    printf("+%4s\n", number2);
    printf("-----\n");
    number3 = part2(number1, number2);
    printf("%5s \n", number3);
    
    /*PART 3*/
    int a, b;
    printf("Enter first number for multiplying: ");
    scanf("%d", &a);
    printf("Enter second number for multiplying: ");
    scanf("%d", &b);
    printf("\nFirst number: %d\nSecond number: %d\n", a,b);
    printf("Result:\n");
    part3(a, b);
    
    /*PART 4*/
    int number;
    printf("Please enter an integer between 1 and 10 (inclusive): ");
    scanf("%d", &number);
    part4(number);

    return(0);
}
