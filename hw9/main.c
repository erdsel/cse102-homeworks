#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct point {
    int row;
    int col;
} Point;

typedef struct block {
    char type;
    int value;
} Block;

typedef struct snake {
    Point* body;
    int length;
} Snake;

void draw_board(Block*** board, Snake* snake) {
    int i, j, k;

    // First draw the upper edge
    for (i = 0; i < 10; i++) {
        printf("----");
    }
    printf("-\n");

    // Draw the cells
    for (i = 0; i < 10; i++) {
        printf("|");
        for (j = 0; j < 10; j++) {
            // Check if the cell is occupied by the snake
            char cell = ' '; // default to empty
            for (k = 0; k < snake->length; k++) {
                if (snake->body[k].row == i && snake->body[k].col == j) {
                    // The cell is occupied by the snake
                    cell = (k == 0) ? 'O' : 'X'; // 'O' for the head, 'X' for the body
                    break;
                }
            }
            if (cell == ' ') {
                // The cell is not occupied by the snake
                switch (board[i][j][0].type) {
                    case 'b':
                        cell = '.';
                        break;
                    case 'o':
                        cell = '0' + board[i][j][0].value; // assume value is a single digit
                        break;
                    case 'e':
                        break;
                }
            }
            printf(" %c |", cell);
        }
        printf("\n");

        // Draw the horizontal lines
        for (k = 0; k < 10; k++) {
            printf("----");
        }
        printf("-\n");
    }
}

Block*** init_board() {
    int i, j, k;
    Block*** board;

    // Dynamically allocate memory for 3D board
    board = (Block***)malloc(10 * sizeof(Block**));
    for (i = 0; i < 10; i++) {
        board[i] = (Block**)malloc(10 * sizeof(Block*));
        for (j = 0; j < 10; j++) {
            board[i][j] = (Block*)malloc(10 * sizeof(Block));
            for (k = 0; k < 10; k++) {
                // Initialize with empty blocks
                board[i][j][k].type = 'e';
                board[i][j][k].value = 0;
            }
        }
    }

    // Generate random positions for bait and obstacle
    srand(time(NULL));
    int obstacleRow, obstacleCol, baitRow, baitCol;

    do {
        obstacleRow = rand() % 10;
        obstacleCol = rand() % 10;
    } while (obstacleRow == 0 && obstacleCol == 0); // avoid top-left cell

    do {
        baitRow = rand() % 10;
        baitCol = rand() % 10;
    } while ((baitRow == 0 && baitCol == 0) || (baitRow == obstacleRow && baitCol == obstacleCol)); // avoid top-left cell and obstacle cell

    // Place bait and obstacle
    board[obstacleRow][obstacleCol][0].type = 'o';
    board[obstacleRow][obstacleCol][0].value = rand() % 10 + 1; // obstacle height between 1 and 10
    board[baitRow][baitCol][0].type = 'b';
    board[baitRow][baitCol][0].value = 0; // bait has no height

    return board;
}
bool isValidMove(Point newHead, Snake* snake, Block*** board) {
    // Check if the new position is within the board boundaries
    if (newHead.row < 0 || newHead.row >= 10 || newHead.col < 0 || newHead.col >= 10) {
        return false;
    }

    // Check if the new position overlaps with the snake's body
    for (int i = 1; i < snake->length; i++) {
        if (newHead.row == snake->body[i].row && newHead.col == snake->body[i].col) {
            return false;
        }
    }

    // Check if the new position is an obstacle
    if (board[newHead.row][newHead.col][0].type == 'o') {
        return false;
    }

    // The move is valid if none of the above conditions are true
    return true;
}

void move(Snake* snake) {
    char direction;
    Point newHead = snake->body[0];
    printf("Enter the next move (w: up, a: left, s: down, d: right): ");
    scanf(" %c", &direction);

    switch (direction) {
        case 'w':
            newHead.row--;
            break;
        case 'a':
            newHead.col--;
            break;
        case 's':
            newHead.row++;
            break;
        case 'd':
            newHead.col++;
            break;
        default:
            printf("Invalid move! Try again.\n");
            return;
    }

    // Move each segment of the snake to the position of the previous segment
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    // Move the head of the snake
    snake->body[0] = newHead;
}



void update(Snake* snake, Block*** board) {
    // Check if the snake moved outside the board
    if (snake->body[0].row < 0 || snake->body[0].row >= 10 || snake->body[0].col < 0 || snake->body[0].col >= 10) {
        printf("Game over! The snake went outside the board.\n");
        exit(0); // End the game
    }

    // Check if the snake collided with its body
    for (int i = 1; i < snake->length; i++) {
        if (snake->body[0].row == snake->body[i].row && snake->body[0].col == snake->body[i].col) {
            printf("Game over! The snake collided with itself.\n");
            exit(0); // End the game
        }
    }

    // Check if the snake ate a bait
    if (board[snake->body[0].row][snake->body[0].col][0].type == 'b') {
        // Increase the length of the snake
        snake->length++;
        snake->body = realloc(snake->body, snake->length * sizeof(Point));
        
        // Move the new segment to the old position of the tail
        snake->body[snake->length - 1] = snake->body[snake->length - 2];
        
        // Replace the bait with an empty block
        board[snake->body[0].row][snake->body[0].col][0].type = 'e';
        board[snake->body[0].row][snake->body[0].col][0].value = 0;

        // Generate a new bait and obstacle
        int newRow, newCol;
        bool validPosition;
        for(int n=0; n<2; n++){
            do {
                newRow = rand() % 10;
                newCol = rand() % 10;
                validPosition = true;

                // Check if the new position is not occupied by the snake
                for (int i = 0; i < snake->length; i++) {
                    if (snake->body[i].row == newRow && snake->body[i].col == newCol) {
                        validPosition = false;
                        break;
                    }
                }
            } while (!validPosition);

            // Place the new bait or obstacle
            if(n == 0){ // place bait
                board[newRow][newCol][0].type = 'b';
                board[newRow][newCol][0].value = 0;
            }else{ // place obstacle
                board[newRow][newCol][0].type = 'o';
                board[newRow][newCol][0].value = rand() % 10 + 1; // obstacle height between 1 and 10
            }
        }
    }

    // Check if the snake collided with an obstacle
    else if (board[snake->body[0].row][snake->body[0].col][0].type == 'o') {
        printf("Game over! The snake collided with an obstacle.\n");
        exit(0); // End the game
    }
}





int check_status(Snake* snake, Block*** board) {
    // Check for self-collision
    for (int i = 1; i < snake->length; i++) {
        if (snake->body[0].row == snake->body[i].row && snake->body[0].col == snake->body[i].col) {
            printf("Game over! The snake collided with itself.\n");
            return 1; // Collision with self
        }
    }

    // Check for obstacle collision
    if (board[snake->body[0].row][snake->body[0].col][0].type == 'o') {
        printf("Game over! The snake collided with an obstacle.\n");
        return 1; // Collision with obstacle
    }

    // No collision
    return 0;
}


void play(Block*** board) {
    Snake snake;
    snake.length = 1;
    snake.body = malloc(snake.length * sizeof(Point));
    snake.body[0].row = 0;
    snake.body[0].col = 0;

    while (1) {
        draw_board(board, &snake);
        move(&snake);
        update(&snake, board);
    }

    free(snake.body);
}



int main() {
    Block*** board = init_board();
    play(board);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);

    return 0;
}
