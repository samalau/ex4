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
// locate symbol among those valid
int findIndex(char symbol);
int processSymbol(int position, int* globalBalance, char expected);
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

 // exit main, 'EXIT' for global clarity, main task = 6
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
        if (nextMainTask == EOF || task == EXIT) {
            // exit main
            break;
        }
        if (nextMainTask != 1 || task < 1 || task > EXIT) {
            // ensure default switch case
            task = 0;
            scanf("%*[^\n]");
            printf("Please choose a task number from the list.\n");
            continue;
        }
        // scanf("%*c");
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
        if (task == EXIT) {
            // scanf("%*c");
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
                 // exit main
                fullTerminate();
                return 0;
            }

            if (input != 1
            || nextWeight < 0) {
                scanf("%*[^\n]");
                if (scanf("%*c") == EOF) {
                    // exit main
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
/*
8 valid symbols, 4 valid pairs
'(', ')' (2, 1)
'[', ']' (4, 2)
'{', '}' (6, 3)
'<', '>' (8, 4)
*/
char validSymbols[8] = {
	'(', ')',
	'[', ']',
	'{', '}',
	'<', '>'
};

// locate symbol among those valid
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
int processSymbol(int position, int* globalBalance, char expected) {
    char symbol;
    int input = scanf("%c", &symbol);

    // end of input
    if (input == EOF) {
        fullTerminate();
        return 0;
    }
    if (symbol == '\n') {
        return (*globalBalance == 0);
    }

    // identify symbol validity
    int index = findIndex(symbol);

    // skip invalid characters
    if (symbol == ' ' || index == -1) {
        return processSymbol(position + 1, globalBalance, expected);
    }

    // handle opening parentheses
    if (index % 2 == 0) {
        (*globalBalance)++;
        // pass new expected closing parenthesis for this level
        char newExpected = validSymbols[index + 1];
        if (!processSymbol(position + 1, globalBalance, newExpected)) {
            return 0;
        }
        return processSymbol(position + 1, globalBalance, expected);
    }

    // handle closing parentheses
    if (*globalBalance == 0 || symbol != expected) {
        return 0;
    }

    // valid closing parenthesis
    (*globalBalance)--;
    return 1;
}

void task3ParenthesisValidator() {
    int globalBalance = 0;
    char expected = '\0';

    scanf("%*c");
    printf("Please enter a term for validation:\n");
    
    if (!processSymbol(0, &globalBalance, expected)) {
    // if (!processSymbol(0, &globalBalance, &expected)) {
        if (task == EXIT) {
            return;
        }
        printf("The parentheses are not balanced correctly.\n");
    } else {
        printf("The parentheses are balanced correctly.\n");
    }
}


// TASK 4 QUEEN BATTLE
// compute absolute value
int abs(int x) {
    return x < 0 ? -x : x;
}

// check current cell's zone and adjacent cells for existing queens
int isValidRec(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones, int i) {
    if (i >= row) {
        unsigned char zone = (unsigned char)zones[row][col];
        // zone uniqueness
        return !(usedZones[zone]);
    }

    int x1 = i + 1, y1 = board[i];
    int x2 = row + 1, y2 = col + 1;

    // check adjacency
    if (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1) return 0;

    // check row/column exclusivity
    if (y1 == y2) return 0;

    // check diagonal validity
    if ((x2 - x1 == y2 - y1 || x2 - x1 == -(y2 - y1)) &&
        (abs(x2 - x1) == 1 && abs(y2 - y1) == 1)) return 0;

    return isValidRec(board, row, col, zones, usedZones, i + 1);
}

// wrapper function for validation
int isValid(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones) {
    return isValidRec(board, row, col, zones, usedZones, 0);
}

int solveRec(int *board, int row, int n, int *usedColumns, int *usedZones, char zones[DIMENSION_MAX][DIMENSION_MAX], int col) {
    // all rows filled
	if (row == n) {
        return 1;
    }
	// no columns left
    if (col >= n) {
        return 0;
    }

    if (!usedColumns[col] && isValid(board, row, col, zones, usedZones)) {
        board[row] = col + 1;
        usedColumns[col] = 1;
        unsigned char zone = (unsigned char)zones[row][col];
        usedZones[zone] = 1;
        if (solveRec(board, row + 1, n, usedColumns, usedZones, zones, 0)) {
            return 1;
        }
        usedColumns[col] = 0;
        usedZones[zone] = 0;
    }

    return solveRec(board, row, n, usedColumns, usedZones, zones, col + 1);
}

// wrapper for solve function
int solve(int *board, int row, int n, int *usedColumns, int *usedZones, char zones[DIMENSION_MAX][DIMENSION_MAX]) {
    return solveRec(board, row, n, usedColumns, usedZones, zones, 0);
}

// recursive function to read zones
void readZonesRec(char zones[DIMENSION_MAX][DIMENSION_MAX], int n, int filled) {
    // Base case: all cells filled
	if (filled >= n * n) return;
	char c;
	int input = scanf("%c", &c);
    if (input != 1) {
        if (input == EOF) {
            // exit main
            fullTerminate();
        }
        return;
    }
    if (c == ' ' || c == '\n') {
		// skip spaces and newlines
        readZonesRec(zones, n, filled);
    } else {
		// fill zones
        zones[filled / n][filled % n] = c;
        readZonesRec(zones, n, filled + 1);
    }
}

// wrapper for zone reader
void readZones(char zones[DIMENSION_MAX][DIMENSION_MAX], int n) {
    readZonesRec(zones, n, 0);
}

void task4QueensBattle() {
    int n;
    printf("Please enter the board dimensions:\n");
	int getSize = scanf(" %d", &n);

    if (!getSize || n < DIMENSION_MIN || n > DIMENSION_MAX) {
		if (getSize == EOF) {
            // exit main
			fullTerminate();
		} else {
			printf("This puzzle cannot be solved.\n");
		}
        return;
    }

	// consume newline from input buffer
	scanf("%*c");

    printf("Please enter a %d*%d puzzle board:\n", n, n);

    char zones[DIMENSION_MAX][DIMENSION_MAX];
    readZones(zones, n);
    if (task == EXIT) {
        // exit main
        return;
    }

    int board[DIMENSION_MAX] = {0};
    int usedColumns[DIMENSION_MAX] = {0};
	// allow all ASCII characters as zone labels (not all are legal -- handled after input)
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
    if (task == EXIT) {
        // exit main
        return;
    }
    scanf("%*[^\n]");
    scanf("%*c");
}


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
        // exit main
		fullTerminate();
		return;
	}

    initializeGrid();

	scanf("%*c");
    printf("Please enter the number of slots in the crossword:\n");
    input = scanf(" %d", &numSlots);
	if (input == EOF) {
        // exit main
		fullTerminate();
        return;
	}

	scanf("%*c");
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
	for  (int i = 0; i < numSlots; i++) {
		input = (scanf(" %d %d %d %c", &slots[i].row, &slots[i].col, &slots[i].length, &slots[i].direction));
		if (input == EOF) {
            // exit main
			fullTerminate();
			return;
		}
	}

	scanf("%*c");
    printf("Please enter the number of words in the dictionary:\n");
    do {
		input = scanf(" %d", &numWords);
		if (input == EOF) {
            // exit main
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
            // exit main
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
