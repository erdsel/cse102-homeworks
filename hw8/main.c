#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 3
#define MAX_MOVES 100

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
    int emptyRow;
    int emptyCol;
} PuzzleBoard;
/*
initializeBoard: This function initializes the PuzzleBoard by filling it with numbers from 1 to (BOARD_SIZE^2 - 1) in row-major order. 
It sets the last element (board[BOARD_SIZE - 1][BOARD_SIZE - 1]) as 0, representing an empty space on the board.
 It also updates the emptyRow and emptyCol variables to store the row and column indices of the empty space. 
 Additionally, it attempts to clear the contents of a file named "board.txt" by opening it in write mode and closing it immediately. 
If successful, the file will be empty, indicating that the board has been initialized.
*/
void initializeBoard(PuzzleBoard *board) {
    int i, j, num = 1;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board->board[i][j] = num++;
        }
    }
    board->board[BOARD_SIZE - 1][BOARD_SIZE - 1] = 0;
    board->emptyRow = BOARD_SIZE - 1;
    board->emptyCol = BOARD_SIZE - 1;
     FILE *file = fopen("board.txt", "w");
    if (file != NULL) {
        fclose(file);
    } else {
        printf("Error: Unable to clear the board file.\n");
    }
}
/*printBoard: This function prints the current state of the PuzzleBoard. 
It iterates over the rows and columns of the board and prints the numbers stored in each cell. 
If a cell contains 0, it prints two empty spaces instead to represent the empty space. 
After printing each row, it adds a newline character to move to the next line and display the next row of the board.*/
void printBoard(PuzzleBoard *board) {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board->board[i][j] == 0) {
                printf("  ");
            } else {
                printf("%d ", board->board[i][j]);
            }
        }
        printf("\n");
    }
}

/*
saveBoardToFile: This function takes a PuzzleBoard and a filename as input. 
It opens the file in "a+" mode (append or create if the file doesn't exist) and writes the contents of the board to the file. 
Each number in the board is written followed by a space, and each row is written on a new line. 
Additionally, it adds an extra newline character between moves. 
Finally, it closes the file. This function is used to save the current state of the board to a file.
*/

void saveBoardToFile(PuzzleBoard *board, const char *filename) {
    FILE *file = fopen(filename, "a+");  // "a" moduyla dosyayı aç, varsa sonuna ekle
    if (file != NULL) {
        int i, j;
        for (i = 0; i < BOARD_SIZE; i++) {
            for (j = 0; j < BOARD_SIZE; j++) {
                fprintf(file, "%d ", board->board[i][j]);
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n");  // Hareketler arasına boşluk ekleyelim
        fclose(file);
    } else {
        printf("Error: Unable to save the board to file.\n");
    }
}

/*loadBoardFromFile: This function takes a PuzzleBoard and a filename as input. 
It opens the file in "r" mode (read mode) and reads the contents of the file into the board. 
It assumes that the file has the same format as produced by the saveBoardToFile function.
 It also updates the emptyRow and emptyCol variables based on the position of the empty space (0) on the board. 
Finally, it closes the file. This function is used to load a previously saved board from a file.*/
void loadBoardFromFile(PuzzleBoard *board, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        int i, j;
        for (i = 0; i < BOARD_SIZE; i++) {
            for (j = 0; j < BOARD_SIZE; j++) {
                fscanf(file, "%d", &board->board[i][j]);
                if (board->board[i][j] == 0) {
                    board->emptyRow = i;
                    board->emptyCol = j;
                }
            }
        }
        fclose(file);
    } else {
        printf("Error: Unable to load the board from file.\n");
    }
}
/*
shuffleBoard: This function shuffles the PuzzleBoard by performing a specified number of random moves. 
It uses the srand and rand functions from the standard library to generate random numbers. 
The empty space is moved in a random direction (up, down, left, or right) by swapping its position with a neighboring number.
The emptyRow and emptyCol variables are updated accordingly. This function is used to randomly shuffle the board at the beginning of the game.
*/
void shuffleBoard(PuzzleBoard *board) {
    int i, j, num, temp;
    srand(time(NULL));
    for (num = 0; num < MAX_MOVES; num++) {
        i = board->emptyRow;
        j = board->emptyCol;
        switch (rand() % 4) {
            case 0:  // Up
                i--;
                break;
            case 1:  // Down
                i++;
                break;
            case 2:  // Left
                j--;
                break;
            case 3:  // Right
                j++;
                break;
        }
        if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
            temp = board->board[i][j];
            board->board[i][j] = board->board[board->emptyRow][board->emptyCol];
            board->board[board->emptyRow][board->emptyCol] = temp;
            board->emptyRow = i;
            board->emptyCol = j;
        }
    }
}
/*
isValidMove: This function takes a PuzzleBoard, a row index, and a column index as input and checks if the specified move is valid. 
It verifies if the given row and column indices fall within the bounds of the board. 
It returns 1 if the move is valid and 0 otherwise. It is used to validate user moves before making them
*/
int isValidMove(PuzzleBoard *board, int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

/*
makeMove: This function takes a PuzzleBoard, a row index, and a column index as input. 
It checks if the specified move is valid using the isValidMove function. 
If the move is valid, it swaps the number at the specified position with the empty space (0), updates the emptyRow and emptyCol variables, and saves the updated board state to a file using the saveBoardToFile function. 
If the move is invalid, it prints an error message. This function is used to make a move on the board based on the user's input.
*/
void makeMove(PuzzleBoard *board, int row, int col) {
    if (isValidMove(board, row, col)) {
        int temp = board->board[row][col];
        board->board[row][col] = 0;
        board->board[board->emptyRow][board->emptyCol] = temp;
        board->emptyRow = row;
        board->emptyCol = col;
        saveBoardToFile(board, "board.txt");  // Her hamle sonrası durumu kaydet
    } else {
        printf("Invalid move. Please try again.\n");
    }
}
/*
isPuzzleSolved: This function takes a PuzzleBoard as input and checks if the puzzle has been solved. 
It compares each number on the board with the expected sequence of numbers (from 1 to (BOARD_SIZE^2 - 1) in row-major order),
 ensuring that the empty space (0) is at the last position. If the board matches the expected sequence, it returns 1, 
indicating that the puzzle is solved. Otherwise, it returns 0. This function is used to determine if the game has been successfully completed.
*/
int isPuzzleSolved(PuzzleBoard *board) {
    int i, j, num = 1;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (i == BOARD_SIZE - 1 && j == BOARD_SIZE - 1) {
                if (board->board[i][j] != 0) {
                    return 0;
                }
            } else {
                if (board->board[i][j] != num++) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
/*
playGameAsUser: This function allows the user to play the 8-puzzle game interactively. 
It creates a PuzzleBoard, initializes and shuffles it using the initializeBoard and shuffleBoard functions respectively. 
It also saves the initial board state to a file. 
The function then enters a loop where it prints the current state of the board, prompts the user for a move (number and direction), 
validates and makes the move using the makeMove function, and checks if the puzzle is solved using the isPuzzleSolved function. If the puzzle is solved,
it calculates and displays the score, saves it to a file if it's a new best score, and exits the loop. This function is the main entry point for the user to play the game.
*/
void playGameAsUser() {
    PuzzleBoard board;
    initializeBoard(&board);
    shuffleBoard(&board);
    saveBoardToFile(&board, "board.txt");

    printf("Welcome to the 8-puzzle game!\n");
    printf("The puzzle has been shuffled. Good luck!\n");

    int moves = 0;
    while (1) {
        printBoard(&board);

        int number, row, col;
        char direction[2];

        printf("Enter the number and direction you want to move (e.g., 5-D), or 0 to exit: ");
        scanf("%d-%s", &number, direction);
        if (number == 0) {
            printf("Game ended. Goodbye!\n");
            break;
        }

        row = board.emptyRow;
        col = board.emptyCol;

        if (direction[0] == 'D' || direction[0] == 'd') {
            row--;
        } else if (direction[0] == 'U' || direction[0] == 'u') {
            row++;
        } else if (direction[0] == 'R' || direction[0] == 'r') {
            col--;
        } else if (direction[0] == 'L' || direction[0] == 'l') {
            col++;
        } else {
            printf("Invalid direction. Please try again.\n");
            continue;
        }

        makeMove(&board, row, col);
        saveBoardToFile(&board, "board.txt");

        moves++;
        if (isPuzzleSolved(&board)) {
            int score = 1000 - (10 * moves);
            printf("Congratulations! You solved the puzzle.\n");
            printf("Total moves: %d\n", moves);
            printf("Score: %d\n", score);
            FILE *scoreFile = fopen("score.txt", "r");
            if (scoreFile != NULL) {
                int bestScore;
                fscanf(scoreFile, "%d", &bestScore);
                fclose(scoreFile);
                if (score > bestScore) {
                    scoreFile = fopen("score.txt", "w");
                    if (scoreFile != NULL) {
                        fprintf(scoreFile, "%d", score);
                        fclose(scoreFile);
                        printf("New best score! Score saved to file.\n");
                    } else {
                        printf("Error: Unable to save the score to file.\n");
                    }
                }
            } else {
                scoreFile = fopen("score.txt", "w");
                if (scoreFile != NULL) {
                    fprintf(scoreFile, "%d", score);
                    fclose(scoreFile);
                    printf("New best score! Score saved to file.\n");
                } else {
                    printf("Error: Unable to save the score to file.\n");
                }
            }
            break;
        }
    }
}
/*
shuffleDirections: This function takes a 2D array of directions as input and shuffles the order of the directions randomly. 
It uses the rand function to generate random indices and swaps the direction pairs accordingly. 
This function is used in the auto_finish function to shuffle the order in which the computer tries different directions for solving the puzzle.
*/
void shuffleDirections(int directions[4][2]) {
	int i;
    for ( i = 0; i < 4; i++) {
        int randomIndex = rand() % 4;
        int tempRow = directions[i][0];
        int tempCol = directions[i][1];
        directions[i][0] = directions[randomIndex][0];
        directions[i][1] = directions[randomIndex][1];
        directions[randomIndex][0] = tempRow;
        directions[randomIndex][1] = tempCol;
    }
}

/*
auto_finish: This function is a recursive function that attempts to solve the puzzle automatically using backtracking. 
It takes a PuzzleBoard and the current move count as input. 
It first checks if the puzzle is already solved using the isPuzzleSolved function. 
If not, it generates a shuffled order of directions using shuffleDirections and tries each direction iteratively. 
For each valid move, it makes the move on a temporary board, recursively calls itself with the updated board and incremented move count, 
and then undoes the move by restoring the original board state. 
This process continues until the puzzle is solved or all possible moves have been tried. It is used in the finishGameWithPC function to automatically solve the puzzle.
*/
void auto_finish(PuzzleBoard *board, int moveCount) {
    if (isPuzzleSolved(board)) {
        printf("Congratulations! The puzzle has been solved.\n");
        printf("Total moves taken: %d\n", moveCount);
        return;
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right
    shuffleDirections(directions);
int i;
    for ( i = 0; i < 4; i++) {
        int row = board->emptyRow + directions[i][0];
        int col = board->emptyCol + directions[i][1];

        if (isValidMove(board, row, col)) {
            PuzzleBoard tempBoard = *board; // Mevcut tahtanın bir kopyasını al

            makeMove(&tempBoard, row, col);
            printf("Computer's move %d:\n", moveCount + 1);
            printBoard(&tempBoard);
            saveBoardToFile(&tempBoard, "board.txt");

            auto_finish(&tempBoard, moveCount + 1);

            // If the puzzle has been solved, no need to try other moves
            if (isPuzzleSolved(&tempBoard))
                return;

            // Undo the move by restoring the original board state
            tempBoard = *board;
            saveBoardToFile(&tempBoard, "board.txt");
        }
    }
}
/*
finishGameWithPC: This function loads the current board state from a file using the loadBoardFromFile function. 
It then calls the auto_finish function to automatically solve the puzzle and display the steps. 
Afterward, it waits for user input to return to the main menu.
*/
void finishGameWithPC() {
    PuzzleBoard board;
    int moveCount = 0;

    loadBoardFromFile(&board, "board.txt");

    printf("Solving the puzzle with the computer...\n");
    auto_finish(&board, moveCount);

    // Return to the main menu
    printf("Press any key to continue to the main menu.\n");
    getchar();
    getchar();
}

/*
showBestScore: This function reads the best score from a file named "score.txt" and displays it. 
If the file exists and contains a valid score, it is printed. 
Otherwise, a message indicating that no best score is found is displayed. 
This function is used to show the best score achieved in the game
*/
void showBestScore() {
    FILE *scoreFile = fopen("score.txt", "r");
    if (scoreFile != NULL) {
        int bestScore;
        fscanf(scoreFile, "%d", &bestScore);
        fclose(scoreFile);
        printf("Best score: %d\n", bestScore);
    } else {
        printf("No best score found.\n");
    }
}

int main() {
srand(time(NULL));
    int choice;
    while (1) {
        printf("----- 8-Puzzle Game -----\n");
        printf("1. Play the game as a user\n");
        printf("2. Finish the game with PC\n");
        printf("3. Show the best score\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                playGameAsUser();
                break;
            case 2:
                finishGameWithPC();
                break;
            case 3:
                showBestScore();
                break;
            case 4:
                printf("Exiting the game. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

