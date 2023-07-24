/*
210104004131 - SELEN ERDOĞAN - HM1
*/

#include <stdio.h> /*First, we include the stdio.h library. This allows us to use standard input/output functions.*/
#include <string.h> /*Contains functions necessary for working with strings. */
#include <stdlib.h> 
#include "util.h"

int part1(int a, int b) {  /*  While loop to find the GCD using the Euclidean algorithm*/
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

char* part2(char number1[], char number2[]) {
    static char sonuc[6]; // we create a six character field for the result
    int length1, length2, remainder = 0, result;
    memset(sonuc, '0', 5); //we initialize the result as '000000'
    sonuc[5] = '\0'; //the last character of the result must be a null character

    length1 = strlen(number1);
    length2 = strlen(number2);

    for (int i = 0; i < 5; i++) { // we need to add a 5 times
        result = remainder;
        if (length1 - i > 0) {
            result += number1[length1 - i - 1] - '0';
        }
        if (length2 - i > 0) {
            result += number2[length2 - i - 1] - '0';
        }
        if (result > 9) {
            remainder = 1;
            result -= 10;
        }
        else {
            remainder = 0;
        }
        sonuc[4 - i] = result + '0'; // we construct the result in reverse
    }
    if (remainder == 1) {
        sonuc[0] = '1'; // if there is a remainder at the end of adding, we add '1' to the beginning of the result
    }
    int sifirIndeksi = 0;
    for (int i = 0; i < 5; i++) {
        if (sonuc[i] != '0') {
            sifirIndeksi = i;
            break;
        }
    }
    return sonuc + sifirIndeksi;
}

void part3(int a, int b) {
    int result = a * b;
    int partial1 = a * (b % 10);
    int partial2 = a * ((b / 10) % 10);
    int partial3 = a * (b / 100);
    
    
    printf("%7d\n", a);
    printf("%7d\n", b);
    printf("*\n");
    printf("--------\n");
    if(partial1==0){partial1=0;
    printf("%7d\n", partial1);
    
    }
    if(partial1 > 0 ){printf("%7d\n", partial1);}
    if(partial2==0){partial2=0;
    printf("%6d\n", partial2);
    
    }
    if(partial2 > 0){printf("%6d \n", partial2);}
    if(partial3 > 0){printf("%5d   \n", partial3);}
    printf("+\n");
    printf("--------\n");
    printf("%7d\n", result);
}

void part4(int number) {
    if (number < 1 || number > 10) {
        printf("Invalid input\n");
        exit(0);
    }
    if (number > 5) {
        printf("The integer you entered is greater than 5\n");
    } else {
        printf("The integer you entered is less than or equal to 5\n");
    }
}


