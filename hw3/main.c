
/*SELEN ERDOGAN 2104004131 HW3*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LEFT 'a'
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'
#define C 'C'
#define D 'D'
/*
        print_room function prints a drawing of a room with the characters C and D. First the line length is calculated based on the room size and the lines required for the room drawing are printed. Then, using a nested loop depending on the room size, '|' based on the positions of the characters C and D and ' ' characters are printed. Finally, the lines are reprinted depending on the line length and the lower part of the room is completed.

*/
void print_room(int c_x, int c_y, int d_x, int d_y, int room_size){
    int i, j;
    int line_length = 23; // default line value
    if (room_size > 5) {
        line_length = room_size * 4 + 2; // calculating line 
    }
    for (i = 0; i < line_length; i++) {
        putchar('-'); // printing line
    }
    putchar('\n');
    for(i=0; i<room_size; i++){
        for(j=0; j<room_size; j++){
            if(i == c_y && j == c_x){
                printf("| %c ", 'C');
            } else if (i == d_y && j == d_x){
                printf("| %c ", 'D');
            } else {
                printf("|   ");
            }
        }
        printf("|\n");
    }
    for (i = 0; i < line_length; i++) {
        putchar('-'); // printing line
    }
    putchar('\n');
}




// room size controller function
int get_room_size() {
    int room_size;
    printf("Enter the room size. You cannot specify a size less than 5 or greater than 10.\n");
    scanf("%d", &room_size);
    while(room_size < 5 || room_size > 10) {
        printf("Invalid input! Please enter a value between 5 and 10.\n");
        scanf("%d", &room_size);
    }
    return room_size;
}


//  Control of Status function
int game_over_check(int c_x, int c_y, int d_x, int d_y) {
    if (c_x == d_x && c_y == d_y) {
        return 1; // game over
    } else {
        return 0; // game not over yet
    }
}

int main() {
     srand(time(NULL)); // seed the random number generator
     int c_x, c_y, d_x, d_y; // coordinates of C and D
    int move_count = 0; // number of moves taken by the user
    int choice;
    int room_size;
    
    
    do {
        printf("\n\nWELCOME THE 2D PUZZLE GAME!\n");
        printf("\n1. New Game\n2. Help\n3. Quit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                room_size = get_room_size();


    // randomly select initial positions for C and D
    c_x = rand() % room_size;
    c_y = rand() % room_size;
    d_x = rand() % room_size;
    d_y = rand() % room_size;
    
    // make sure C and D are not in the same position
    while (c_x == d_x && c_y == d_y){
        d_x = rand() % room_size;
        d_y = rand() % room_size;
    }
    
  
    print_room(c_x, c_y, d_x, d_y, room_size);
    
    // loop until C reaches D
    while(c_x != d_x || c_y != d_y){
        char move;
        printf("Enter your move (a=left, d=right, w=up, s=down): ");
        scanf(" %c", &move);
        
        int new_x = c_x;
        int new_y = c_y;
        
        // update position based on user's move
        switch(move){
            case LEFT:
                new_x--;
                break;
            case RIGHT:
                new_x++;
                break;
            case UP:
                new_y--;
                break;
            case DOWN:
                new_y++;
                break;
            default:
                printf("Invalid move! Please try again.\n");
                continue;
        }
        
        // make sure new position is within the room
        if (new_x < 0 || new_x >= room_size || new_y < 0 || new_y >= room_size){
            printf("You hit the wall! Please try again.\n");
            continue;
        }
        
        // update position of C
        c_x = new_x;
        c_y = new_y;
        move_count++;
        
        // print updated room
        print_room(c_x, c_y, d_x, d_y, room_size);
    }
    
   if(game_over_check(c_x, c_y, d_x, d_y)){
                    // printing total moves
                    printf("Congratulations! You caught D in %d moves.\n", move_count);
                    break;
                }
    
                break;
            case 2:
                printf("Help:\n");
            printf("The objective of the game is to move character C to the position of character D in the room.\n");
            printf("You can move C using the following keys:\n");
            printf("a - move left\n");
            printf("d - move right\n");
            printf("w - move up\n");
            printf("s - move down\n");
            printf("You cannot move C outside the boundaries of the room.\n");
                break;
            case 3:
                printf("Goodbye!\n");
            exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);
    
    return 0;
}

