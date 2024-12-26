/******************
Name: Samantha Newmark
ID: 346587629
Assignment: 4
*******************/
#include <stdio.h>
#include <string.h>

// globally trigger exit main while loop to gracefully terminate the program
#define EXIT 6

// task 1 macros -- overflow protection
#define FACTORIAL_MAX 171

/**
    Overflow Protection (Task 1)
    Three levels have been defined in order to mitigate the risk of improper handling of large input values.
    Each of these three levels has been designated a range of values and an identifier. These identifiers are A, B, and C.
    Coordinate pairs are designated to their respective levels based on the sums of their values.
    As a result, if one value of a pair is significantly higher than the other of that pair,
    the pathway taken will be that which has been optimized for the larger value,
    unless one of such values is less than or equal to 0.
    Any coordinate value being less than or equal to 0 results in that pair being handled prior to level assignment,
    thereby not neccesitating its inclusion in the level conditions.
        - Level A is the range of integers greater than 0 but less than 21 (0 < i && i < 21)
        - Level B is the range of integers greater than or equal to 21 but less than 170 (21 <= i && i < 170)
        - Level C is the range of integers greater than or equal to 170 (170 <= i)
**/
#define LEVEL_A_COORDINATE_MAX 21

/**
    Overflow Protection (Task 1)
    Three levels have been defined in order to mitigate the risk of improper handling of large input values.
    Each of these three levels has been designated a range of values and an identifier. These identifiers are A, B, and C.
    Coordinate pairs are designated to their respective levels based on the sums of their values.
    As a result, if one value of a pair is significantly higher than the other of that pair,
    the pathway taken will be that which has been optimized for the larger value,
    unless one of such values is less than or equal to 0.
    Any coordinate value being less than or equal to 0 results in that pair being handled prior to level assignment,
    thereby not neccesitating its inclusion in the level conditions.
        - Level A is the range of integers greater than 0 but less than 21 (0 < i && i < 21)
        - Level B is the range of integers greater than or equal to 21 but less than 170 (21 <= i && i < 170)
        - Level C is the range of integers greater than or equal to 170 (170 <= i)
**/
#define LEVEL_B_COORDINATE_MAX 170

// more task 1 overflow protection
#define CACHE_MAX 0x8000
#define M 1000000007


// task 3 macro
// placeholder (consider 64)
#define MAX_DEPTH 128

// task 4 macros
#define PRINTABLE_MIN 33
#define PRINTABLE_MAX 126
#define PRINTABLE_RANGE (PRINTABLE_MAX - PRINTABLE_MIN + 1)
#define DIMENSION_MIN 1
#define DIMENSION_MAX 20
#define QUEEN "X "
#define EMPTY "* "

// task 5 macros
#define MAX_GRID_SIZE 30
#define MAX_SLOTS 100
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 15

// task 1 helpers
long long x1(int *valid);
long long y1(int *valid);
unsigned long long factorial(long long n);
unsigned long long modMult(unsigned long long a, unsigned long long b);
unsigned long long computePaths(long long goLeft, long long goDown);
void task1(long long goLeft, long long goDown);


// task 2 helpers
void setupPyramid();
int getWeight();


// task 3 helpers
int findIndex(char symbol);
int processSymbol(int position, int* globalBalance, char *expected);
void task3ParenthesisValidator();


// task 4 helpers
int abs(int x);
// int markZoneCells(char zones[DIMENSION_MAX][DIMENSION_MAX], int n,
//                             int row, int col, int visited[DIMENSION_MAX][DIMENSION_MAX],
//                             int *foundQueen, int *board, char startZone);
// int isZoneValidRec(char zones[DIMENSION_MAX][DIMENSION_MAX], int n,  int zoneRow, int zoneCol, int *board);
int isValidRec(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX],
                    int *usedZones, int i);
int isValid(int *board,  int row, int col,
                char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones);
int solveRec(int *board, int row, int n, int *usedColumns, int *usedZones,
                    char zones[DIMENSION_MAX][DIMENSION_MAX], int col);
int solve(int *board, int row,  int n, int *usedColumns, int *usedZones,
                char zones[DIMENSION_MAX][DIMENSION_MAX]);
void readZonesRec(char zones[DIMENSION_MAX][DIMENSION_MAX], int n, int filled);
void readZones(char zones[DIMENSION_MAX][DIMENSION_MAX], int n);

// task 5 helpers
typedef struct {
    int row, col, length;
    char direction;
} Slot;

int gridSize;
char grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
Slot slots[MAX_SLOTS];
int numSlots;
char dictionary[MAX_WORDS][MAX_WORD_LENGTH + 1];
int numWords;
int usedWords[MAX_WORDS];

void task5CrosswordGenerator();
void initializeGrid();
void displayGrid();
int validPlaceWord(int slotIndex, const char* word);
void placeWord(int slotIndex, const char* word);
void removeWord(int slotIndex);
int solveCrossword(int slotIndex);

// task entry points
void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();

// initialize
int task = 0;
int sizeRemainder = 0;
char bufferExtract[] = {0};
char nextMainTask = 0;
char remainderOfExtract[] = {0};

// 'fullTerminate', 'EXIT' for global clarity (main task = 6)
void fullTerminate() {
	task = EXIT;
}

int main() {
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
        if (nextMainTask != 1
        || task < 1
        || task > EXIT) {
            // ensure default switch case
            task = 0;
            scanf("%*[^\n]");
            printf("Please choose a task number from the list.\n");
            continue;
        }
        scanf("%*c");
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
            // macro 'EXIT' for global clarity (task = 6)
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

// TASK 1 ROBOT PATHS
// TASK 1: VALIDATE: X COORDINATE
long long x1(int *valid) {
    long long x;
    int result = scanf(" %lld", &x);
    if (result != 1) {
        *valid = 0;
        return 0;
    }
    *valid = 1;
    return x;
}

// TASK 1: VALIDATE: Y COORDINATE
long long y1(int *valid) {
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
    printf("Please enter the coordinates of the robot (column, row):\n");
    long long x = x1(&valid);
    if (!valid) {
        return;
    }
    long long y = y1(&valid);
    if (!valid) {
        return;
    }
    task1(x, y);
}

unsigned long long modMult(unsigned long long a, unsigned long long b) {
    return (a % M) * (b % M) % M;
}

unsigned long long cacheFactorial[FACTORIAL_MAX] = {0};

unsigned long long factorial(long long n) {
    if (n < 0 || n >= FACTORIAL_MAX) {
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

/**
CACHE_MAX: overflow protection
3: goLeft, goDown, result
**/
unsigned long long cachePaths[CACHE_MAX][3] = {0};

unsigned long long findInCache(unsigned long long goLeft, unsigned long long goDown, int index) {
    if (index >= CACHE_MAX) {
        return 0;
    }
    if (cachePaths[index][0] == goLeft
    && cachePaths[index][1] == goDown) {
        return cachePaths[index][2];
    }
    return findInCache(goLeft, goDown, index + 1);
}

void saveToCache(unsigned long long goLeft, unsigned long long goDown,
                            unsigned long long result, unsigned int index) {
    if (index >= CACHE_MAX) {
        return;
    }
    if (cachePaths[index][0] == 0
    && cachePaths[index][1] == 0)
    {
        cachePaths[index][0] = goLeft;
        cachePaths[index][1] = goDown;
        cachePaths[index][2] = result;
        return;
    }
    saveToCache(goLeft, goDown, result, index + 1);
}

/**
    Three levels have been defined in order to mitigate the risk of improper handling of large input values.
    Each of these three levels has been designated a range of values and an identifier. These identifiers are A, B, C.
    Coordinate pairs are designated to their respective levels based on the sums of their values.
    As a result, if one value of a pair is significantly higher than the other of that pair,
    the pathway taken will be that which has been optimized for the larger value,
    unless one of such values is less than or equal to 0.
    Any coordinate value being less than or equal to 0 results in that pair being handled prior to level assignment,
    thereby not neccesitating its inclusion in the level conditions.
        - Level A is the range of integers greater than 0 but less than 21 (0 < i && i < 21)
        - Level B is the range of integers greater than or equal to 21 but less than 170 (21 <= i && i < 170)
        - Level C is the range of integers greater than or equal to 170 (170 <= i)
**/
unsigned long long computePaths(long long goLeft, long long goDown) {
    if (goLeft < 0
    || goDown < 0) {
        return 0;
    }
    if (goLeft == 0
    || goDown == 0) {
        return 1;
    }
    int level = (goLeft + goDown < LEVEL_A_COORDINATE_MAX) ? 0 : (
                        (goLeft + goDown < LEVEL_B_COORDINATE_MAX) ? 1 : 2);
    // LEVEL A
    if (level == 0) {
        return computePaths(goLeft - 1, goDown) + computePaths(goLeft, goDown - 1);
    }
    // LEVEL B
    if (level == 1) {
        return modMult(factorial(goLeft + goDown), modMult(factorial(goLeft), factorial(goDown)));
    }
    // LEVEL C
    if (level == 2) {
        unsigned long long cachedResult = findInCache(goLeft, goDown, 0);
        if (cachedResult != 0) {
            return cachedResult;
        }
        unsigned long long result = modMult(factorial(goLeft + goDown), modMult(factorial(goLeft), factorial(goDown)));
        saveToCache(goLeft, goDown, result, 0);
        return result;
    }
    return 0;
}

void task1(long long goLeft, long long goDown) {
    unsigned long long totalDistinctPaths = computePaths(goLeft, goDown);
    printf("The total number of paths the robot can take to reach home is: %llu\n", totalDistinctPaths);
}

// TASK 2 HUMAN PYRAMID
double *dataPyramid[5];
double level1[1];
double level2[2];
double level3[3];
double level4[4];
double level5[5];

void setupPyramid() {
    dataPyramid[0] = level1;
    dataPyramid[1] = level2;
    dataPyramid[2] = level3;
    dataPyramid[3] = level4;
    dataPyramid[4] = level5;

    // grid initialization/reset
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            dataPyramid[i][j] = 0.00;
        }
    }   
}

int getWeight() {
    printf("Please enter the weights of the cheerleaders:\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            double nextWeight = -1.00;

            int input = scanf(" %lf", &nextWeight);

            if (input == EOF) {
                fullTerminate();
                return 0;
            }

            if (input != 1
            || nextWeight < 0) {
                scanf("%*[^\n]");
                if (scanf("%*c") == EOF) {
					fullTerminate();
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
    if (!fullData) {
        return;
    }
    printf("The total weight on each cheerleader is:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            float weightLoad = dataPyramid[i][j];
            if (i > 0) {
                float weightUpLeft = (j > 0) ? (float)dataPyramid[i - 1][j - 1] / 2.0 : 0;
                float weightUpRight = (j < i) ? (float)dataPyramid[i - 1][j] / 2.0 : 0;
                weightLoad += weightUpLeft + weightUpRight;
            }
            dataPyramid[i][j] = weightLoad;
            printf("%.2f ", weightLoad);
        }
        printf("\n");
    }
    return;
}

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

/**
extract parentheses
0: unbalanced
1: balanced
**/
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
    if (symbol == ' '
    || index == -1) {
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
        if (*globalBalance == 0
        || symbol != *expected) {
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


// TASK 4 QUEEN BATTLE

// Custom implementation of abs
int abs(int x) {
    return x < 0 ? -x : x;
}

// Recursive function to validate a queen's placement
int isValidRec(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones, int i) {
    if (i >= row) {
        unsigned char zone = (unsigned char)zones[row][col];
        // Zone uniqueness
        return !(usedZones[zone]);
        // return !(usedZones & (1 << zone));
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
int isValid(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones) {
    return isValidRec(board, row, col, zones, usedZones, 0);
}

int solveRec(int *board, int row, int n, int *usedColumns, int *usedZones, char zones[DIMENSION_MAX][DIMENSION_MAX], int col) {
    // Base case: all rows filled
	if (row == n) return 1;
	// No columns left
    if (col >= n) return 0;

    if (!usedColumns[col] && isValid(board, row, col, zones, usedZones)) {
        board[row] = col + 1;
        usedColumns[col] = 1;
        unsigned char zone = (unsigned char)zones[row][col];
        usedZones[zone] = 1;

        if (solveRec(board, row + 1, n, usedColumns, usedZones, zones, 0)) return 1;

        usedColumns[col] = 0;
        usedZones[zone] = 0;
    }

    return solveRec(board, row, n, usedColumns, usedZones, zones, col + 1);
}

// Wrapper for the solve function
int solve(int *board, int row, int n, int *usedColumns, int *usedZones, char zones[DIMENSION_MAX][DIMENSION_MAX]) {
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

    if (!getSize || n < DIMENSION_MIN || n > DIMENSION_MAX) {
		if (getSize == EOF) {
			fullTerminate();
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

    // Initialize board and tracking arrays (static allocation)
    int board[DIMENSION_MAX] = {0};
    int usedColumns[DIMENSION_MAX] = {0};
	// Allow all ASCII characters as zone labels
    int usedZones[256] = {0};

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
}

/**
// // TASK 4 QUEEN BATTLE
// // compute absolute val
// int abs(int x) {
//     return x < 0 ? -x : x;
// }
// // check current cell's zone and adjacent cells for existing queens
// int markZoneCells(char zones[DIMENSION_MAX][DIMENSION_MAX], int n, int row, int col,
//                             int visited[DIMENSION_MAX][DIMENSION_MAX], int *foundQueen, int *board, char startZone) {
//     if (
//     // out of bounds
//     row < 0 || row >= n || col < 0 || col >= n
//     // already visited
//     || visited[row][col]
//     // different zone
//     || zones[row][col] != startZone) {
//         return 0;
//     }
//     // mark cell as visited
//     visited[row][col] = 1;
//     // check if cell has queen
//     if (board[row] == col + 1) {
//         (*foundQueen)++;
//         // return immediately if more than one queen found in zone
//         if (*foundQueen > 1) {
//             return 1;
//         }
//     }
//     // UP
//     if (markZoneCells(zones, n, row - 1, col, visited, foundQueen, board, startZone)) {
//         return 1;
//     }
//      // DOWN
//     if (markZoneCells(zones, n, row + 1, col, visited, foundQueen, board, startZone)) {
//         return 1;
//     }
//     // LEFT
//     if (markZoneCells(zones, n, row, col - 1, visited, foundQueen, board, startZone)) {
//         return 1;
//     }
//     // RIGHT
//     if (markZoneCells(zones, n, row, col + 1, visited, foundQueen, board, startZone)) {
//         return 1;
//     }
//     // UP-LEFT DIAGONAL
//     if (markZoneCells(zones, n, row - 1, col - 1, visited, foundQueen, board, startZone)) {
//         return 1;
//     }
//     // UP-RIGHT DIAGONAL
//     if (markZoneCells(zones, n, row - 1, col + 1, visited, foundQueen, board, startZone)) {
//         return 1;
//     }
//     // DOWN-LEFT DIAGONAL
//     if (markZoneCells(zones, n, row + 1, col - 1, visited, foundQueen, board, startZone)) {
//         return 1;
//     }
//     // DOWN-RIGHT DIAGONAL
//     if (markZoneCells(zones, n, row + 1, col + 1, visited, foundQueen, board, startZone)) {
//         return 1;
//     }
//     return 0;
// }

// int isZoneValidRec(char zones[DIMENSION_MAX][DIMENSION_MAX], int n, int zoneRow, int zoneCol, int *board) {
//     // track the visited cells
//     int visited[DIMENSION_MAX][DIMENSION_MAX] = {0};
//     // count the queens found in zone
//     int foundQueen = 0; 
//     // set the starting zone label
//     char startZone = zones[zoneRow][zoneCol]; 
//     // check current cell's zone and adjacent cells for existing queens
//     markZoneCells(zones, n, zoneRow, zoneCol, visited, &foundQueen, board, startZone);
//     // return invalid if more than one queen found in zone
//     return (foundQueen <= 1);
// }

// int isValidRec(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones, int i) {
//     if (i >= row) {
//         unsigned char zone = zones[row][col];
//         // zone uniqueness
//         return !(usedZones[zone]);
//     }
//     int x1 = i + 1, y1 = board[i];
//     int x2 = row + 1, y2 = col + 1;
//     // check adjacency
//     if (x1 == x2 || y1 == y2
//     || abs(x2 - x1) <= 1 || abs(y2 - y1) <= 1) {
//         return 0;
//     }
//     if ((x2 - x1 == y2 - y1 || x2 - x1 == -(y2 - y1))
//     && (abs(x2 - x1) == 1 && abs(y2 - y1) == 1)) {
//         return 0;
//     }
//     return isValidRec(board, row, col, zones, usedZones, i + 1);
// }

// // // check current cell's zone and adjacent cells for existing queens
// // int isValidRec(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones, int i) {
// //     // if (zones[row][col] < PRINTABLE_MIN || zones[row][col] > PRINTABLE_MAX) {
// //     //     return 0;
// //     // }
// //     if (i >= row) {
// //         unsigned char zone = zones[row][col];
// //         // zone uniqueness
// //         return !(usedZones[zone]);
// //     }
// //     int x1 = i + 1, y1 = board[i];
// //     int x2 = row + 1, y2 = col + 1;
// //     // check adjacency
// //     if (x1 == x2 || y1 == y2
// //     || abs(x2 - x1) <= 1 || abs(y2 - y1) <= 1) {
// //         return 0;
// //     }
// //     // if (abs(x2 - x1) <= 1
// //     // && abs(y2 - y1) <= 1) {
// //     //     return 0;
// //     // }
// //     // // check row/column exclusivity
// //     // if (x1 == x2 || y1 == y2) {
// //     //     return 0;
// //     // }
// //     // // check diagonal validity
// //     // int dx = abs(x2 - x1);
// //     // int dy = abs(y2 - y1);
// //     // // if (dx <= 1 && dy <= 1 && (dx != 0 || dy != 0)) {
// //     // if (dx != 0 || dy != 0) {
// //     //     return 0;
// //     // }
// //     if ((x2 - x1 == y2 - y1 || x2 - x1 == -(y2 - y1))
// //     && (abs(x2 - x1) == 1 && abs(y2 - y1) == 1)) {
// //         return 0;
// //     }
// //     return isValidRec(board, row, col, zones, usedZones, i + 1);
// // }

// int isValid(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones) {
//     if (!isValidRec(board, row, col, zones, usedZones, 0)) {
//         return 0;
//     }
//     // validate current zone
//     return isZoneValidRec(zones, DIMENSION_MAX, row, col, board);
// }

// // // wrapper for zone validation
// // int isValid(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones) {
// //     if (!isValidRec(board, row, col, zones, usedZones, 0)) {
// //         return 0;
// //     }
// //     // validate current zone
// //     return isZoneValidRec(zones, DIMENSION_MAX, row, col, board);
// // }

// int solveRec(int *board, int row, int n, int *usedColumns, int *usedZones,
//                     char zones[DIMENSION_MAX][DIMENSION_MAX], int col) {
//     // all rows filled
//     if (row == n) {
//         return 1;
//     }
//     // no columns left
//     if (col >= n) {
//         return 0;
//     }
//     if (!usedColumns[col] && isValid(board, row, col, zones, usedZones)) {
//         unsigned char zone = (unsigned char)zones[row][col];
//         board[row] = col + 1;
//         usedColumns[col] = 1;
//         usedZones[zone] = 1;
//         if (solveRec(board, row + 1, n, usedColumns, usedZones, zones, 0)) {
//             return 1;
//         }
//         board[row] = 0;
//         usedColumns[col] = 0;
//         usedZones[zone] = 0;
//     }
//     return solveRec(board, row, n, usedColumns, usedZones, zones, col + 1);
// }

// // int solveRec(int *board, int row, int n, int *usedColumns, int *usedZones,
// //                     char zones[DIMENSION_MAX][DIMENSION_MAX], int col) {
// //     // all rows filled
// // 	if (row == n) {
// //         return 1;
// //     }
// // 	// no columns left
// //     if (col >= n) {
// //         return 0;
// //     }
// //     // if (zones[row][col] == '\0'
// //     // || zones[row][col] == '\n'
// //     // || zones[row][col] == '\t'
// //     // || zones[row][col] < 33
// //     // || zones[row][col] > 126) {
// //     //     // invalid char
// //     //     return 0;
// //     // }
// //     if (!usedColumns[col] && isValid(board, row, col, zones, usedZones)) {
// //         unsigned char zone = (unsigned char)zones[row][col];
// //         board[row] = col + 1;
// //         usedColumns[col] = 1;
// //         usedZones[zone] = 1;
// //         if (solveRec(board, row + 1, n, usedColumns, usedZones, zones, 0)) {
// //             return 1;
// //         }
// //         board[row] = 0;
// //         usedColumns[col] = 0;
// //         usedZones[zone] = 0;
// //     }
// //     return solveRec(board, row, n, usedColumns, usedZones, zones, col + 1);
// // }

// int readZonesRec(char zones[DIMENSION_MAX][DIMENSION_MAX], int n, int row, int col, int *uniqueZones, int *usedZones) {
//     // all cells filled
//     if (*uniqueZones == n || row == n) {
//         return 1;
//     }

//     char c;
//     int input = scanf(" %c", &c);
//     if (input != 1) {
//         if (input == EOF) {
//             fullTerminate();
//             return 0;
//         }
//         return readZonesRec(zones, n, row, col, uniqueZones, usedZones);
//     }

//     // validate zones requirements
//     if (c < PRINTABLE_MIN || c > PRINTABLE_MAX) {
//         return 0;
//     }

//     // place the valid character in the zone
//     zones[row][col] = c;
//     int index = c - PRINTABLE_MIN;
//     if (index < 0 || index >= PRINTABLE_RANGE) {
//         return 0;
//     }

//     // track unique zones
//     if (!usedZones[index]) {
//         usedZones[index] = 1;
//         (*uniqueZones)++;
//     }

//     // move to the next cell
//     int nextRow = row + (col + 1 == n);
//     int nextCol = (col + 1) % n;
//     return readZonesRec(zones, n, nextRow, nextCol, uniqueZones, usedZones);
// }

// // int readZonesRec(char zones[DIMENSION_MAX][DIMENSION_MAX],
// //                             int n, int row, int col, int *uniqueZones, int *usedZones) {
// //     // all cells filled
// //     if (*uniqueZones == n || row == n) {
// //         return 1;
// //     }

// //     char c;
// //     int input = scanf(" %c", &c);
// //     // printf("%c", c);
// //     if (input != 1) {
// //         if (input == EOF) {
// //             fullTerminate();
// //             return 0;
// //         }
// //         // scanf("%*[^\n]");
// //         // scanf("%*c");
// //         return readZonesRec(zones, n, row, col, uniqueZones, usedZones);
// //         // return 0;
// //     }

// //     // skip spaces, newlines, and tabs
// //     // if (c == ' ' || c == '\n' || c == '\t') {
// //     //     return readZonesRec(zones, n, row, col, uniqueZones, usedZones);
// //     // }

// //     // validate zones requirements
// //     if (c < PRINTABLE_MIN || c > PRINTABLE_MAX) {
// //         return 0;
// //     }

// //     // place the valid character in the zone
// //     zones[row][col] = c;
// //     int index = c - PRINTABLE_MIN;
// //     if (index < 0 || index >= PRINTABLE_RANGE) {
// //         return 0;
// //     }

// //     // track unique zones
// //     if (!usedZones[index]) {
// //         usedZones[index] = 1;
// //         (*uniqueZones)++;
// //     }

// //     // move to the next cell
// //     int nextRow = row + (col + 1 == n);
// //     int nextCol = (col + 1) % n;
// //     return readZonesRec(zones, n, nextRow, nextCol, uniqueZones, usedZones);
// // }


// // // scan zones
// // int readZonesRec(char zones[DIMENSION_MAX][DIMENSION_MAX],
// //                             int n, int row, int col, int *uniqueZones, int *usedZones) {
// //     // all cells filled
// // 	if (row == n || *uniqueZones == n) {
// //         return 1;
// //     }
// // 	char c;
// //     int input = scanf("%c", &c);
// //     if (input != 1) {
// //         if (input == EOF) {
// //             fullTerminate();
// //         }
// //         return 0;
// //     }
// //     // skip spaces and newlines
// //     if (c == ' ' || c == '\n' || c == '\t') {
// //         return readZonesRec(zones, n, row, col, uniqueZones, usedZones);
// //     }
// //     // validate zones requirements
// //     if (c < PRINTABLE_MIN || c > PRINTABLE_MAX) {
// //         return 0;
// //     }
// //     zones[row][col] = c;
// //     int index = c - PRINTABLE_MIN;
// //     if (index < 0 || index >= PRINTABLE_RANGE) {
// //         return 0;
// //     }
// //     // track unique zones
// //     if (!usedZones[index]) {
// //         usedZones[index] = 1;
// //         (*uniqueZones)++;
// //     }
// //    return readZonesRec(zones, n, row + (col + 1 == n), (col + 1) % n, uniqueZones, usedZones);
// // }

// int readZones(char zones[DIMENSION_MAX][DIMENSION_MAX], int n) {
//     // count number of unique zones
//     int uniqueZones = 0;
//     // zone label (ASCII) character tracker
//     int usedZones[PRINTABLE_RANGE] = {0};
//     // process zones from input and validate number of unique zones
//     if (!readZonesRec(zones, n, 0, 0, &uniqueZones, usedZones) || uniqueZones != n) {
//         scanf("%*[^\n]");
//         scanf("%*c");
//         return 0;
//     }
//     return 1;
// }

// // int readZones(char zones[DIMENSION_MAX][DIMENSION_MAX], int n) {
// //     // count number of unique zones
// //     int uniqueZones = 0;
// //     // zone label (ASCII) character tracker
// //     int usedZones[PRINTABLE_RANGE] = {0};
// //     // process zones from input and validate number of unique zones
// //     if (!readZonesRec(zones, n, 0, 0, &uniqueZones, usedZones) || task == EXIT || uniqueZones != n) {
// //         scanf("%*[^\n]");
// //         scanf("%*c");
// //         return 0;
// //     }
// //     return 1;
// // }

// void task4QueensBattle() {
//     printf("Please enter the dimensions of the board:\n");
//     int n;
//     int getSize = scanf(" %d", &n);
//     if (!getSize || n < DIMENSION_MIN || n > DIMENSION_MAX) {
//         if (getSize == EOF) {
//             fullTerminate();
//         } else {
//             scanf("%*[^\n]");
//             printf("This puzzle cannot be solved.\n");
//         }
//         return;
//     }

//     printf("Please enter the %d*%d puzzle board:\n", n, n);
//     char zones[DIMENSION_MAX][DIMENSION_MAX];
//     if (!readZones(zones, n)) {
//         printf("This puzzle cannot be solved.\n");
//         return;
//     }
//     // initialize board and tracking arrays
//     int board[DIMENSION_MAX] = {0};
//     int usedColumns[DIMENSION_MAX] = {0};
//     // allow all ASCII characters as zone labels (empty char will be skipped upon scan)
//     int usedZones[PRINTABLE_RANGE] = {0};
//     if (solveRec(board, 0, n, usedColumns, usedZones, zones, 0)) {
//         printf("Solution:\n");
//         for (int i = 0; i < n; i++) {
//             for (int j = 1; j <= n; j++) {
//                 if (board[i] == j) {
//                     printf("X ");
//                 } else {
//                     printf("* ");
//                 }
//             }
//             printf("\n");
//         }
//     } else {
//         printf("This puzzle cannot be solved.\n");
//     }
// }

// // void task4QueensBattle() {
// //     printf("Please enter the dimensions of the board:\n");
// //     int n;
// // 	int getSize = scanf(" %d", &n);
// //     if (!getSize
// //     || n < DIMENSION_MIN
// //     || n > DIMENSION_MAX) {
// // 		if (getSize == EOF) {
// // 			fullTerminate();
// // 		} else {
// //             scanf("%*[^\n]");
// // 			printf("This puzzle cannot be solved.\n");
// // 		}
// //         return;
// //     }

// //     printf("Please enter the %d*%d puzzle board:\n", n, n);
// //     char zones[DIMENSION_MAX][DIMENSION_MAX];
// //     if (!readZones(zones, n)) {
// //         printf("This puzzle cannot be solved.\n");
// //         return;
// //     }
// //     // initialize board and tracking arrays
// //     int board[DIMENSION_MAX] = {0};
// //     int usedColumns[DIMENSION_MAX] = {0};
// // 	// allow all ASCII characters as zone labels (empty char will be skipped upon scan)
// //     int usedZones[PRINTABLE_RANGE] = {0};
// //     if (solveRec(board, 0, n, usedColumns, usedZones, zones, 0)) {
// //         printf("Solution:\n");
// //         for (int i = 0; i < n; i++) {
// //             for (int j = 1; j <= n; j++) {
// //                 if (board[i] == j) {
// //                     printf(QUEEN);
// //                 } else {
// //                     printf(EMPTY);
// //                 }
// //             }
// //             printf("\n");
// //         }
// //     } else {
// //         printf("This puzzle cannot be solved.\n");
// //     }
// // }
**/

// TASK 5 CROSSWORD
void initializeGrid() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = '#';
        }
    }
}

void displayGrid() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            printf("| %c ", grid[i][j]);
        }
        printf("|\n");
    }
}

int validPlaceWord(int slotIndex, const char* word) {
    Slot slot = slots[slotIndex];
    if ((int)strlen(word) != slot.length) {
		return 0;
	}
    for (int i = 0; i < slot.length; i++) {
        int r = slot.row + (slot.direction == 'V' ? i : 0);
        int c = slot.col + (slot.direction == 'H' ? i : 0);
        if (grid[r][c] != '#' && grid[r][c] != word[i]) {
			return 0;
		}
    }
    return 1;
}

/** 'H' for horizontal
'V' for vertical
**/
void placeWord(int slotIndex, const char* word) {
    Slot slot = slots[slotIndex];
    for (int i = 0; i < slot.length; i++) {
        int r = slot.row + (slot.direction == 'V' ? i : 0);
        int c = slot.col + (slot.direction == 'H' ? i : 0);
        grid[r][c] = word[i];
    }
}

/** 'H' for horizontal
'V' for vertical
**/
void removeWord(int slotIndex) {
    Slot slot = slots[slotIndex];
    for (int i = 0; i < slot.length; i++) {
        int r = slot.row + (slot.direction == 'V' ? i : 0);
        int c = slot.col + (slot.direction == 'H' ? i : 0);
        grid[r][c] = '#';
    }
}

int solveCrossword(int slotIndex) {
    if (slotIndex == numSlots) {
		return 1;
	}
    for (int i = 0; i < numWords; i++) {
        if (!usedWords[i] && validPlaceWord(slotIndex, dictionary[i])) {
            usedWords[i] = 1;
            placeWord(slotIndex, dictionary[i]);

            if (solveCrossword(slotIndex + 1)) {
				return 1;
			}
            removeWord(slotIndex);
            usedWords[i] = 0;
        }
    }
    return 0;
}

void task5CrosswordGenerator() {
	int input = 0;

    printf("Please enter the dimensions of the crossword grid:\n");
    input = scanf(" %d", &gridSize);
	if (input == EOF) {
		fullTerminate();
		return;
	}

    initializeGrid();

	scanf("%*c");
    printf("Please enter the number of slots in the crossword:\n");
    input = scanf(" %d", &numSlots);
	if (input == EOF) {
		fullTerminate();
        return;
	}

	scanf("%*c");
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
	for  (int i = 0; i < numSlots; i++) {
		input = (scanf(" %d %d %d %c", &slots[i].row, &slots[i].col, &slots[i].length, &slots[i].direction));
		if (input == EOF) {
			fullTerminate();
			return;
		}
	}

	scanf("%*c");
    printf("Please enter the number of words in the dictionary:\n");
    do {
		input = scanf(" %d", &numWords);
		if (input == EOF) {
			fullTerminate();
			return;
		}
        if (numWords < numSlots) {
			scanf("%*[^\n]");
			scanf("%*c");
            printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", numSlots);
        }
    } while (numWords < numSlots);

	scanf("%*c");
    printf("Please enter the words for the dictionary:\n");
    for (int i = 0; i < numWords; i++) {
        input = scanf(" %s", dictionary[i]);
		if (input == EOF) {
			fullTerminate();
			return;
		}
    }

    if (solveCrossword(0)) {
        displayGrid();
    } else {
        printf("This crossword cannot be solved.\n");
    }
}
