/*
 * ============================================================
 *  SUDOKU PUZZLE GAME  -  DSA Mini Project (C, console based)
 * ============================================================
 *  DSA concepts used:
 *   1. 2D Arrays  : board[9][9], given[9][9], solution[9][9]
 *   2. Recursion  : solveSudoku() calls itself for the next cell
 *   3. Backtracking: try 1..9, undo (set to 0) if it leads to a dead end
 *   4. Searching  : findEmptyCell() traverses the board row by row
 *   5. Stack      : array-based stack of moves for the Undo feature
 *   6. Functions  : each task is a separate function
 *
 *  Compile : gcc sudoku.c -o sudoku
 *  Run     : ./sudoku        (Windows: sudoku.exe)
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

#define SIZE      9
#define BOX       3
#define MAX_STACK 100   /* maximum number of moves that can be undone */

/* ---------- Global game data ---------- */
int board[SIZE][SIZE];     /* current state of the game              */
int given[SIZE][SIZE];     /* 1 = original (locked) cell, 0 = empty  */
int solution[SIZE][SIZE];  /* full solution, used for hints          */

/* ---------- Stack for Undo ---------- */
typedef struct {
    int row;
    int col;
    int oldValue;   /* value in the cell BEFORE the move */
} Move;

Move undoStack[MAX_STACK];
int  top = -1;      /* -1 means the stack is empty */

int isStackEmpty(void) { return top == -1; }
int isStackFull(void)  { return top == MAX_STACK - 1; }

void push(int row, int col, int oldValue) {
    if (isStackFull()) {
        /* Drop the oldest move by shifting everything down */
        for (int i = 1; i <= top; i++)
            undoStack[i - 1] = undoStack[i];
        top--;
    }
    top++;
    undoStack[top].row = row;
    undoStack[top].col = col;
    undoStack[top].oldValue = oldValue;
}

Move pop(void) {
    return undoStack[top--];   /* caller must check isStackEmpty() first */
}

/* ---------- Initial puzzle (0 = empty cell) ---------- */
void loadPuzzle(void) {
    int puzzle[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j]    = puzzle[i][j];
            solution[i][j] = puzzle[i][j];
            given[i][j]    = (puzzle[i][j] != 0);
        }
    }
}

/* ---------- Display the board ---------- */
void displayBoard(void) {
    printf("\n     1 2 3   4 5 6   7 8 9\n");
    printf("   +-------+-------+-------+\n");
    for (int i = 0; i < SIZE; i++) {
        printf(" %d | ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                printf(". ");
            else
                printf("%d ", board[i][j]);
            if ((j + 1) % BOX == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % BOX == 0)
            printf("   +-------+-------+-------+\n");
    }
}

/* ---------- Validation: row, column and 3x3 box ---------- */
int isValid(int grid[SIZE][SIZE], int row, int col, int num) {
    /* Check the row and the column (traversal) */
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num && i != col) return 0;
        if (grid[i][col] == num && i != row) return 0;
    }

    /* Check the 3x3 box: find its top-left corner first */
    int boxRow = row - row % BOX;
    int boxCol = col - col % BOX;
    for (int i = 0; i < BOX; i++) {
        for (int j = 0; j < BOX; j++) {
            int r = boxRow + i, c = boxCol + j;
            if (grid[r][c] == num && !(r == row && c == col))
                return 0;
        }
    }
    return 1;
}

/* ---------- Searching: find the next empty cell ---------- */
int findEmptyCell(int grid[SIZE][SIZE], int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                *row = i;
                *col = j;
                return 1;   /* found */
            }
        }
    }
    return 0;               /* board is full */
}

/* ---------- Recursion + Backtracking solver ---------- */
int solveSudoku(int grid[SIZE][SIZE]) {
    int row, col;

    /* Base case: no empty cell left -> puzzle solved */
    if (!findEmptyCell(grid, &row, &col))
        return 1;

    /* Try every number from 1 to 9 in this empty cell */
    for (int num = 1; num <= 9; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;          /* choose */

            if (solveSudoku(grid))         /* recurse on the next cell */
                return 1;

            grid[row][col] = 0;            /* BACKTRACK: undo the choice */
        }
    }
    return 0;   /* no number fits -> dead end, go back to previous cell */
}

/* ---------- Check whether the player has won ---------- */
int isSolved(void) {
    int r, c;
    return !findEmptyCell(board, &r, &c);   /* every move was validated */
}

/* ---------- Safe integer input ---------- */
int readInt(const char *prompt, int *value) {
    printf("%s", prompt);
    if (scanf("%d", value) != 1) {
        scanf("%*[^\n]");   /* discard bad input */
        return 0;
    }
    return 1;
}

/* ---------- Feature: place a number ---------- */
void makeMove(void) {
    int row, col, num;

    if (!readInt("Enter row (1-9): ", &row) ||
        !readInt("Enter column (1-9): ", &col) ||
        !readInt("Enter number (1-9, or 0 to erase): ", &num)) {
        printf("\n[!] Please enter numbers only.\n");
        return;
    }

    if (row < 1 || row > 9 || col < 1 || col > 9 || num < 0 || num > 9) {
        printf("\n[!] Row/column must be 1-9 and number must be 0-9.\n");
        return;
    }

    row--; col--;   /* convert to 0-based index */

    if (given[row][col]) {
        printf("\n[!] That cell is part of the original puzzle and cannot be changed.\n");
        return;
    }

    if (num != 0 && !isValid(board, row, col, num)) {
        printf("\n[X] Invalid move: %d already exists in that row, column or 3x3 box.\n", num);
        return;
    }

    push(row, col, board[row][col]);   /* save old value on the stack */
    board[row][col] = num;

    if (num == 0)
        printf("\n[OK] Cell (%d,%d) erased.\n", row + 1, col + 1);
    else
        printf("\n[OK] Placed %d at (%d,%d).\n", num, row + 1, col + 1);
}

/* ---------- Feature: undo last move (stack pop) ---------- */
void undoMove(void) {
    if (isStackEmpty()) {
        printf("\n[!] Nothing to undo.\n");
        return;
    }
    Move m = pop();
    board[m.row][m.col] = m.oldValue;
    printf("\n[OK] Undid move at (%d,%d).\n", m.row + 1, m.col + 1);
}

/* ---------- Feature: hint ---------- */
void giveHint(void) {
    int r, c;

    /* Traverse the board to find the first empty cell */
    if (!findEmptyCell(board, &r, &c)) {
        printf("\n[!] The board is already full.\n");
        return;
    }

    /* The hint comes from the pre-computed solution */
    printf("\n[HINT] Try %d at row %d, column %d.\n",
           solution[r][c], r + 1, c + 1);
}

/* ---------- Feature: solve automatically ---------- */
void autoSolve(void) {
    /* Reset to the original puzzle (keep only given cells) */
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (!given[i][j]) board[i][j] = 0;

    solveSudoku(board);
    top = -1;   /* clear the undo stack */
    printf("\n[SOLVED] Here is the complete solution:\n");
}

/* ---------- Menu ---------- */
void showMenu(void) {
    printf("\n-------------- MENU --------------\n");
    printf("  1. Place a number\n");
    printf("  2. Undo last move\n");
    printf("  3. Get a hint\n");
    printf("  4. Show solution (solver)\n");
    printf("  5. Quit\n");
    printf("----------------------------------\n");
}

/* ---------- Game manager ---------- */
void playGame(void) {
    int choice;

    loadPuzzle();
    solveSudoku(solution);   /* compute the answer once, for hints */

    printf("=====================================\n");
    printf("        WELCOME TO SUDOKU GAME       \n");
    printf("=====================================\n");
    printf("Fill every empty cell (.) so each row, column\n");
    printf("and 3x3 box contains the digits 1 to 9.\n");

    while (1) {
        displayBoard();

        if (isSolved()) {
            printf("\n*** CONGRATULATIONS! You solved the Sudoku! ***\n");
            break;
        }

        showMenu();
        if (!readInt("Enter your choice: ", &choice)) {
            printf("\n[!] Invalid input. Enter a number from the menu.\n");
            continue;
        }

        switch (choice) {
            case 1: makeMove();  break;
            case 2: undoMove();  break;
            case 3: giveHint();  break;
            case 4: autoSolve(); displayBoard(); return;
            case 5: printf("\nThanks for playing. Goodbye!\n"); return;
            default: printf("\n[!] Invalid choice. Choose 1-5.\n");
        }
    }
}

int main(void) {
    playGame();
    return 0;
}
