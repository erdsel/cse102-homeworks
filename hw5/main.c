/*SELEN ERDOGAN 210104004131 HM5*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26
/*PART 1 FUNCTIONS*/
/*

Here, the is_alpha function checks if a character is a letter and returns 0 or 1. 
The to_upper function returns the capitalization of the given character, or returns the same character if the given character is already uppercase. The count_letters function calculates the number of letters in the file using the is_alpha and to_upper functions. The print_counts function prints the number of letters to the screen.
I wrote the isalpha and toupper functions myself instead of using a ready-made structure.

*/
int is_alpha(int c) { //the is_alpha function checks if a character is a letter and returns 0 or 1. 
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int to_upper(int c) { //The to_upper function returns the capitalization of the given character, or returns the same character if the given character is already uppercase
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}
/*

The count_letters function takes a file pointer (FILE *) and an array of counts.
It then reads the characters from the file with the fgetc() function and loops until the EOF (end of file) character. 
Each read character is checked with the is_alpha() function, that is, it is checked whether it is a letter or not. 
If it is a letter, the character is converted to uppercase with the to_upper() function 
and the corresponding index of the counts array is incremented by one. 
The counts array can be thought of as an array that has an index for each letter and how many are found for that letter.
This process is repeated for all letters in the file.
The print_counts function takes the counts array and prints the number of each letter to the screen. ALPHABET_SIZE is a constant and is used to provide an index for each letter. Next, a loop is created and the number of each letter is printed to the screen using the printf() function. The expression 'A' + i is used to print letters, because the numeric value of the character 'A' is 65 in ASCII encoding, and the numeric values of the other letters increase in order according to the numeric value of the 'A' character. That is, the expression 'A' + i represents letters like 'A', 'B', 'C' according to the value of i. 
Finally, the counts[i] expression, i. provides the number of letters and prints the numeric value with %d.

*/
void count_letters(FILE *fp, int *counts) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (is_alpha(c)) {
            c = to_upper(c);
            counts[c - 'A']++;
        }
    }
}

void print_counts(int *counts) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c:%d\n", 'A' + i, counts[i]);
    }
}




/*PART 2 FUNCTIONS*/
/*
This code defines an enum data type Color, which represents colors, and a Vector3 structured data type, 
which holds 3-dimensional vectors. Also, a fixed array color_vectors defines a list of constant vectors containing a vector for each color, 
and a fixed array color_names defines an array containing a corresponding name for each color.
*/
typedef enum { RED, GREEN, BLUE, YELLOW, ORANGE } Color;

typedef struct {
    double x, y, z;
} Vector3;

const Vector3 color_vectors[] = {
    {1, 0, 0},      // RED
    {0, 1, 0},      // GREEN
    {0, 0, 1},      // BLUE
    {0.5, 0.5, 0},  // YELLOW
    {0.5, 0.4, 0.2} // ORANGE
};

const char* color_names[] = {
    "RED", "GREEN", "BLUE", "YELLOW", "ORANGE"
};

/*
calculating like as pdf
*/
double euclidean_distance(Vector3 v1, Vector3 v2) {
    double dx = v1.x - v2.x;
    double dy = v1.y - v2.y;
    double dz = v1.z - v2.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}
/*
user input part
*/
Color parse_color(const char* str) {
    if (strcmp(str, "r") == 0) {
        return RED;
    } else if (strcmp(str, "g") == 0) {
        return GREEN;
    } else if (strcmp(str, "b") == 0) {
        return BLUE;
    } else if (strcmp(str, "y") == 0) {
        return YELLOW;
    } else if (strcmp(str, "o") == 0) {
        return ORANGE;
    } else {
        fprintf(stderr, "Unknown color: %s\n", str);
        return RED;
    }
}

Color mix_colors(Color c1, Color c2) {
    Vector3 v1 = color_vectors[c1];
    Vector3 v2 = color_vectors[c2];
    Vector3 mix = {(v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z) / 2};
    double min_distance = INFINITY;
    Color closest_color = RED;
    for (int i = RED; i <= ORANGE; i++) {
        double distance = euclidean_distance(mix, color_vectors[i]);
        if (distance < min_distance) {
            min_distance = distance;
            closest_color = i;
        }
    }
    return closest_color;
}

/*PART3 FUNCTIONS*/
// initializes the board with empty spaces
void initialize_board(char board[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// displays the current state of the board
void display_board(char board[3][3])
{
    printf("\n%c  %c  %c\n", board[0][0], board[0][1], board[0][2]);
    printf("_  _  _\n");
    printf("%c  %c  %c\n", board[1][0], board[1][1], board[1][2]);
    printf("_  _  _\n");
    printf("%c  %c  %c\n", board[2][0], board[2][1], board[2][2]);
    printf("_  _  _\n");
}


// checks if a move is valid
bool validate_move(char board[3][3], int row, int col)
{
// check if the row and column are within bounds
if (row < 0 || row > 2 || col < 0 || col > 2) {
return false;
}


// check if the spot is empty
if (board[row][col] != ' ') {
    return false;
}

// the move is valid
return true;
}

// checks if a player has won the game
bool check_win(char board[3][3], char symbol)
{
int i, j;
bool win;

// check rows
for (i = 0; i < 3; i++) {
    win = true;
    for (j = 0; j < 3; j++) {
        if (board[i][j] != symbol) {
            win = false;
            break;
        }
    }
    if (win) {
        return true;
    }
}

// check columns
for (j = 0; j < 3; j++) {
    win = true;
    for (i = 0; i < 3; i++) {
        if (board[i][j] != symbol) {
            win = false;
            break;
        }
    }
    if (win) {
        return true;
    }
}

// check diagonals
if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
    return true;
}
if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
    return true;
}

// no win
return false;
}

// checks if the game is a draw
bool check_draw(char board[3][3])
{
int i, j;
bool draw = true;
// check if the board is full
for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
        if (board[i][j] == ' ') {
            draw = false;
            break;
        }
    }
    if (!draw) {
        break;
    }
}

// check if there is a winner
if (check_win(board, 'X') || check_win(board, 'O')) {
    draw = false;
}

return draw;
}










int main() {
    printf("\n******Part 1******\n ");
    char filename[256];
    printf("Enter the name of the input file: ");
    scanf("%255s", filename);
    printf("\nLetter Frequency:\n");

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return 1;
    }

    int counts[ALPHABET_SIZE] = {0};
    count_letters(fp, counts);
    print_counts(counts);

    fclose(fp);
    printf("\n******Part 2******\n ");
    char color_str[2];
    printf("Enter the first color (r/g/b/y/o): ");
    scanf("%s", color_str);
    Color c1 = parse_color(color_str);
    printf("Enter the second color (r/g/b/y/o): ");
    scanf("%s", color_str);
    Color c2 = parse_color(color_str);
    Color result = mix_colors(c1, c2);
    printf("Mixed color: %s [%.1f, %.1f, %.1f]\n", color_names[result], color_vectors[result].x, color_vectors[result].y, color_vectors[result].z);
    printf("\n******Part 3******\n ");
     char board[3][3];   // the tic-tac-toe board
    char player1 = 'X'; // the symbol for player 1
    char player2 = 'O'; // the symbol for player 2
    char current_player = player1; // the player who is currently playing
    int row, col;       // the row and column of the current move
    bool game_over = false; // indicates whether the game is over or not
    char play_again;    // indicates whether the players want to play again or not

    // initialize the board
    initialize_board(board);

    // loop until the game is over
    do {
        // display the board
        display_board(board);

        // ask the current player for their move
       // printf("\nPlayer %c's turn.\n", current_player);
        printf("Player (%c), enter your move (row,col): ", current_player);
      
        scanf("%d %d", &row, &col);

        // validate the move
        while (!validate_move(board, row, col)) {
            printf("Invalid move. Please try again.\n");
            printf("Player (%c), enter your move (row,col): ", current_player);
            scanf("%d %d", &row, &col);
        }

        // update the board
        board[row][col] = current_player;

        // check for a win
        if (check_win(board, current_player)) {
            printf("\nPlayer %c wins!\n", current_player);
            game_over = true;
        }
        // check for a draw
        else if (check_draw(board)) {
            printf("\nThe game is a draw.\n");
            game_over = true;
        }
        // switch to the other player
        else {
            if (current_player == player1) {
                current_player = player2;
            }
            else {
                current_player = player1;
            }
        }
    } while (!game_over);

    // ask if the players want to play again
    printf("\nDo you want to play again? (y/n) ");
    scanf(" %c", &play_again);

    if (play_again == 'y' || play_again == 'Y') {
        main(); // restart the game
    }
    else {
        printf("\nThanks for playing!\n");
    }
    return 0;
}


