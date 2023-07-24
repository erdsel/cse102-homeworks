#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// function to determine winner
int determine_winner(int user_choice, int computer_choice) {
    if (user_choice == computer_choice) {
        return 0; // tie
    }
    else if ((user_choice == 1 && computer_choice == 3) || 
             (user_choice == 2 && computer_choice == 1) ||
             (user_choice == 3 && computer_choice == 2)) {
        return 1; // user wins
    }
    else {
        return -1; // computer wins
    }
}

int main() {
    int user_choice, computer_choice, winner;
    char play_again;

    srand(time(NULL)); // seed for random number generator

    do {
        printf("Please make a choice!\n");
        printf("1: Stone, 2: Paper, 3: Scissors\n");
        scanf("%d", &user_choice);

        // validate user input
        while (user_choice < 1 || user_choice > 3) {
            printf("Invalid input! Please enter a number between 1 and 3.\n");
            scanf("%d", &user_choice);
        }

        // generate computer choice
        computer_choice = rand() % 3 + 1;

        // determine winner
        winner = determine_winner(user_choice, computer_choice);

        // print results
        printf("You chose ");
        switch(user_choice) {
            case 1:
                printf("Stone");
                break;
            case 2:
                printf("Paper");
                break;
            case 3:
                printf("Scissors");
                break;
        }
        printf(". I chose ");
        switch(computer_choice) {
            case 1:
                printf("Stone");
                break;
            case 2:
                printf("Paper");
                break;
            case 3:
                printf("Scissors");
                break;
        }
        printf(". ");

        if (winner == 0) {
            printf("It's a tie!\n");
        }
        else if (winner == 1) {
            printf("You won!\n");
        }
        else {
            printf("I won!\n");
        }

        // ask user to play again
        do {
            printf("Do you want to play again? (Y/N): ");
            scanf(" %c", &play_again);
            play_again = toupper(play_again);
        } while (play_again != 'Y' && play_again != 'N');
        
        

    } while (play_again == 'Y');

    return 0;
    
    }
