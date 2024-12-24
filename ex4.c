/******************
Name: Samantha Newmark
ID: 346587629
Assignment: 4
*******************/
#include <stdio.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////

// main macro
#define EXIT 6

// task 1 macros -- overflow protection
#define FACTORIAL_MAX 171
#define SMALL_COORDINATE_MAX 21
#define CACHE_MAX 0x8000
#define M 1000000007

// task 3 macro
// placeholder (consider 64)
#define MAX_DEPTH 128

// task 4 macros
#define DIMENSION_MIN 1
#define DIMENSION_MAX 20
#define QUEEN "X "
#define EMPTY "* "

// task 1 helpers
long long x_1(int *valid);
long long y_1(int *valid);
void cacheInitialize();
void task1(long long leftMoves, long long downMoves);
unsigned long long compute_paths(long long leftMoves, long long downMoves);
unsigned long long modMult(unsigned long long a, unsigned long long b);
unsigned long long factorial(long long n);

// task 1 cache
unsigned long long cacheFactorial[FACTORIAL_MAX] = {0};
unsigned long long cacheT1F0[SMALL_COORDINATE_MAX][SMALL_COORDINATE_MAX] = {0};
unsigned long long cacheT1F2x[CACHE_MAX] = {0};
unsigned long long cacheT1F2y[CACHE_MAX] = {0};
unsigned long long cacheT1F2Result[CACHE_MAX] = {0};

// task 2 helpers
void setupPyramid();
int getWeight();

// task 3 helpers
int findIndex(char symbol);
int processSymbol(int position, int* globalBalance, char *expected);
void task3ParenthesisValidator();

// task 4 helpers
typedef struct {
    // color zone
    char color;
    int has_queen;
} Cell;
int validate_color_zones(int size, Cell board[][size], char mapped_colors[], int *unique_colors);
int queen_in_row(int size, Cell board[][size], int row);
int queen_in_col(int size, Cell board[][size], int col);
int queen_in_direct_diagonal(int size, Cell board[][size], int row, int col);
int is_valid_queen(int size, Cell board[][size], int row, int col, int *color_with_queen);
void mark_queen(int size, Cell board[][size], int row, int col, int *color_with_queen, char mapped_colors[]);
void mark_not_queen(int size, Cell board[][size], int row, int col, int *color_with_queen, char mapped_colors[]);
int queens_solver(int size, Cell board[][size], int assigned_queens, int start, int *color_with_queen, char mapped_colors[]);
void display_board(int size, Cell board[][size]);

// task entry points
void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();

// initialize cache
void cacheInitialize() {
    cacheFactorial[0] = 1;
    cacheFactorial[1] = 1;
    cacheT1F0[1][1] = 2;
}

// initialize
int task = 0;
int sizeRemainder = 0;
char bufferExtract[] = {0};
char nextMainTask = 0;
char remainderOfExtract[] = {0};

void full_terminate() {
	task = EXIT;
}

int main() {
	cacheInitialize();
	setupPyramid();
	do {
		printf("Choose an option:\n"
			   "1. Robot Paths\n"
			   "2. The Human Pyramid\n"
			   "3. Parenthesis Validation\n"
			   "4. Queens Battle\n"
			   "5. Crossword Generator\n"
			   "6. Exit\n");
		nextMainTask = scanf(" %d", &task);
        if (nextMainTask == EOF) {
            break;
        }
        if (nextMainTask != 1 || task < 1 || task > EXIT) {
            task = 0;
			scanf("%*[^ 1-6]");
        }
		switch (task) {
			case 1:
				task1RobotPaths();
				break;
			case 2:
				task2HumanPyramid();
				break;
			case 3:
				task3ParenthesisValidator();
				break;
			case 4:
				task4QueensBattle();
				break;
			case 5:
				task5CrosswordGenerator();
				break;
			case EXIT:
				break;
			default:
				printf("Please choose a task number from the list.\n");
				break;
		}
	} while (task != EXIT);
	printf("Goodbye!\n");
	return 0;
}

///////////////////////////////////////////////////////////////////////////

// TASK 1: VALIDATE: X
long long x_1(int *valid) {
    long long x;
    int result = scanf(" %lld", &x);
    if (result != 1) {
        *valid = 0;
        return 0;
    }
    *valid = 1;
    return x;
}

// TASK 1: VALIDATE: Y
long long y_1(int *valid) {
    long long y;
    int result = scanf(" %lld", &y);
    if (result != 1) {
        *valid = 0;
        return 0;
    }
    *valid = 1;
    return y;
}

// TASK 1: ENTRY
void task1RobotPaths() {
    int valid = 0;
    printf("Please enter the coordinates of the robot (col, row):\n");
    long long x = x_1(&valid);
    if (!valid) { return; }
    long long y = y_1(&valid);
    if (!valid) { return; }
    task1(x, y);
}

// TASK 1 ROBOT PATHS

unsigned long long factorial(long long n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    if (cacheFactorial[n] != 0) {
        return cacheFactorial[n];
    }
    return cacheFactorial[n] = modMult(n, factorial(n - 1));
}

unsigned long long modMult(unsigned long long a, unsigned long long b) {
    return (a % M) * (b % M) % M;
}

unsigned long long compute_paths(long long leftMoves, long long downMoves) {
    if (leftMoves < 0 || downMoves < 0) return 0;
    if (leftMoves == 0 || downMoves == 0) return 1;

    int flag = (leftMoves + downMoves <= 20) ? 0 : ((leftMoves + downMoves < 170) ? 1 : 2);

    // x + y <= 20
    if (flag == 0) {
        if (cacheT1F0[leftMoves][downMoves] != 0){
            return cacheT1F0[leftMoves][downMoves];
        }
        return cacheT1F0[leftMoves][downMoves] = modMult(factorial(leftMoves + downMoves), modMult(factorial(leftMoves), factorial(downMoves)));
    }

    // x + y < 170
    if (flag == 1) {
        return modMult(factorial(leftMoves + downMoves), modMult(factorial(leftMoves), factorial(downMoves)));
    }

    // x + y >= 170
    if (flag == 2) {
        for (int i = 0; i < CACHE_MAX; i++) {
            if (cacheT1F2x[i] == (unsigned long long)leftMoves && cacheT1F2y[i] == (unsigned long long)downMoves) {
                return cacheT1F2Result[i];
            }
        }
        unsigned long long result = modMult(factorial(leftMoves + downMoves), modMult(factorial(leftMoves), factorial(downMoves)));
        for (int i = 0; i < CACHE_MAX; i++) {
            if (cacheT1F2x[i] == 0 && cacheT1F2y[i] == 0) {
                cacheT1F2x[i] = leftMoves;
                cacheT1F2y[i] = downMoves;
                cacheT1F2Result[i] = result;
                break;
            }
        }
        return result;
    }
    return 0;
}

void task1(long long leftMoves, long long downMoves) {
    unsigned long long totalDistinctPaths = compute_paths(leftMoves, downMoves);
    printf("The total number of paths the robot can take to reach home is: %llu\n", totalDistinctPaths);
    return;
}

///////////////////////////////////////////////////////////////////////////

// TASK 2 HUMAN PYRAMID
double *dataPyramid[5];
double level_1[1];
double level_2[2];
double level_3[3];
double level_4[4];
double level_5[5];

void setupPyramid() {

    dataPyramid[0] = level_1;
    dataPyramid[1] = level_2;
    dataPyramid[2] = level_3;
    dataPyramid[3] = level_4;
    dataPyramid[4] = level_5;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            dataPyramid[i][j] = 0.00;
        }
    }
    // pyramid is now reset
}

int getWeight() {
    printf("Please enter the weights of the cheerleaders:\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            double nextWeight = -1.00;

            int input = scanf(" %lf", &nextWeight);

            if (input == EOF) {
                full_terminate();
                return 0;
            }

            if (input != 1 || nextWeight < 0) {
                scanf("%*[^\n]");
                if (scanf("%*c") == EOF) {
					full_terminate();
                    return 0;
                }
                printf("Negative weights are not supported.\n");
                // return to main
                return 0;
            }

            // valid weight
            dataPyramid[i][j] = nextWeight;
        }
    }
    return 1;
}

void task2HumanPyramid() {
    int fullData = getWeight();

    if (!fullData) return;

    printf("The total weight on each cheerleader is:\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            double weightLoad = dataPyramid[i][j];

            if (i > 0) {
                double weightUpLeft = (j > 0) ? (double)dataPyramid[i - 1][j - 1] / 2.0 : 0;
                double weightUpRight = (j < i) ? (double)dataPyramid[i - 1][j] / 2.0 : 0;
                weightLoad += weightUpLeft + weightUpRight;
            }

            dataPyramid[i][j] = weightLoad;
            printf("%.2f ", weightLoad);
        }
        printf("\n");
    }
    return;
}

///////////////////////////////////////////////////////////////////////////

// TASK 3 PARENTHESIS VALIDATION

char validSymbols[8] = {
	'(', ')',
	'[', ']',
	'{', '}',
	'<', '>'
};

int findIndex(char symbol) { 
    for (int i = 0; i < 8; i++) {
        if (validSymbols[i] == symbol) {
            return i;
        }
    }
    return -1;
}

// recursively extract parentheses
// 0: unbalanced
// 1: balanced
int processSymbol(int position, int* globalBalance, char *expected) {
    char symbol;
    int input = scanf("%c", &symbol);

    if (input == EOF) {
        return 0;
    }

    if (symbol == '\n') {
        return (*globalBalance == 0);
    }

	int index = findIndex(symbol);
	
    // skip invalid chars
    if (symbol == ' ' || index == -1) {
        return processSymbol(position + 1, globalBalance, expected);
    }

    // handle opening parentheses
    if (index % 2 == 0) {
        (*globalBalance)++;
        *expected = validSymbols[index + 1];
        return processSymbol(position + 1, globalBalance, expected);
    }

    // handle closing parentheses
    else {
        if (*globalBalance == 0 || symbol != *expected) {
			scanf("%*[^\n]");
			scanf("%*c");
            return 0;
        }
        (*globalBalance)--;
        return processSymbol(position + 1, globalBalance, expected);
    }
}

void task3ParenthesisValidator() {
    // initialize globalBalance
    int globalBalance = 0;
    // initialize expected
    char expected = '\0';
    printf("Please enter a term for validation:\n");
	int isBalanced = processSymbol(0, &globalBalance, &expected);
    if (!isBalanced) {
		if (task != EXIT) {
        	printf("The parentheses are not balanced correctly.\n");
		}
    } else {
        printf("The parentheses are balanced correctly.\n");
    }
}

///////////////////////////////////////////////////////////////////////////

// TASK 4 QUEEN BATTLE

// Custom implementation of abs
int abs(int x) {
    return x < 0 ? -x : x;
}

// Recursive function to validate a queen's placement
int isValidRec(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int usedZones, int i) {
    if (i >= row) {
        unsigned char zone = (unsigned char)zones[row][col];
        // Zone uniqueness
        return !(usedZones & (1 << zone));
    }

    int x1 = i + 1, y1 = board[i];
    int x2 = row + 1, y2 = col + 1;

    // Check adjacency
    if (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1) return 0;

    // Check row/column exclusivity
    if (y1 == y2) return 0;

    // Check diagonal validity
    if ((x2 - x1 == y2 - y1 || x2 - x1 == -(y2 - y1)) &&
        (abs(x2 - x1) == 1 && abs(y2 - y1) == 1)) return 0;

    return isValidRec(board, row, col, zones, usedZones, i + 1);
}

// Wrapper function for validation
int isValid(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int usedZones) {
    return isValidRec(board, row, col, zones, usedZones, 0);
}

// Recursive function to solve the board
int solveRec(int *board, int row, int n, int usedColumns, int usedZones, char zones[DIMENSION_MAX][DIMENSION_MAX], int col) {
    // Base case: all rows filled
    if (row == n) return 1;
    // No columns left
    if (col >= n) return 0;

    if (!(usedColumns & (1 << col)) && isValid(board, row, col, zones, usedZones)) {
        board[row] = col + 1;
        usedColumns |= (1 << col);
        unsigned char zone = (unsigned char)zones[row][col];
        usedZones |= (1 << zone);

        if (solveRec(board, row + 1, n, usedColumns, usedZones, zones, 0)) return 1;

        usedColumns &= ~(1 << col);
        usedZones &= ~(1 << zone);
    }

    return solveRec(board, row, n, usedColumns, usedZones, zones, col + 1);
}

// int solveRec(int *board, int row, int n, int *usedColumns, int *usedZones, char zones[DIMENSION_MAX][DIMENSION_MAX], int col) {
//     // Base case: all rows filled
// 	if (row == n) return 1;
// 	// No columns left
//     if (col >= n) return 0;

//     if (!usedColumns[col] && isValid(board, row, col, zones, usedZones)) {
//         board[row] = col + 1;
//         usedColumns[col] = 1;
//         unsigned char zone = (unsigned char)zones[row][col];
//         usedZones[zone] = 1;

//         if (solveRec(board, row + 1, n, usedColumns, usedZones, zones, 0)) return 1;

//         usedColumns[col] = 0;
//         usedZones[zone] = 0;
//     }

//     return solveRec(board, row, n, usedColumns, usedZones, zones, col + 1);
// }

// Wrapper for the solve function
int solve(int *board, int row, int n, int usedColumns, int usedZones, char zones[DIMENSION_MAX][DIMENSION_MAX]) {
    return solveRec(board, row, n, usedColumns, usedZones, zones, 0);
}

// Recursive function to read the zones
void readZonesRec(char zones[DIMENSION_MAX][DIMENSION_MAX], int n, int filled) {
    // Base case: all cells filled
	if (filled >= n * n) return;
	char c;
	scanf("%c", &c);
    if (c == ' ' || c == '\n') {
		// Skip spaces and newlines
        readZonesRec(zones, n, filled);
    } else {
		// Fill the zones
        zones[filled / n][filled % n] = c;
        readZonesRec(zones, n, filled + 1);
    }
}

// Wrapper for the zone reader
void readZones(char zones[DIMENSION_MAX][DIMENSION_MAX], int n) {
    readZonesRec(zones, n, 0);
}

void task4QueensBattle() {
    int n;
    printf("Please enter the dimensions of the board:\n");
	int getSize = scanf(" %d", &n);

    if (!getSize || DIMENSION_MIN < 1 || n > DIMENSION_MAX) {
		if (getSize == EOF) {
			full_terminate();
		} else {
			printf("This puzzle cannot be solved.\n");
		}
        return;
    }

	// Consume leftover newline from input buffer
	scanf("%*c");

    printf("Please enter the %d*%d puzzle board:\n", n, n);

    // Create the zones 2D array (static allocation)
    char zones[DIMENSION_MAX][DIMENSION_MAX];
    readZones(zones, n);

    // Initialize board and tracking variables
    int board[DIMENSION_MAX] = {0};
    int usedColumns = 0; // Bitmask for columns
    int usedZones = 0;   // Bitmask for zones

    // // Initialize board and tracking arrays (static allocation)
    // int board[DIMENSION_MAX] = {0};
    // int usedColumns[DIMENSION_MAX] = {0};
	// // Allow all ASCII characters as zone labels
    // int usedZones[256] = {0};

    if (solve(board, 0, n, usedColumns, usedZones, zones)) {
        printf("Solution:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= n; j++) {
                if (board[i] == j) printf(QUEEN);
                else printf(EMPTY);
            }
            printf("\n");
        }
    } else {
        printf("This puzzle cannot be solved.\n");
    }

    return;
}

///////////////////////////////////////////////////////////////////////////

// TASK 5 CROSSWORD
void task5CrosswordGenerator() {

}
