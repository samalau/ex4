/******************
Name: Samantha Newmark
ID: 346587629
Assignment: 4
*******************/
#include <stdio.h>
#include <string.h>

// task 1 macro: overflow protection: factorial
#define FACTORIAL_MAX 171

/*
	Overflow Protection (Task 1)
	Three levels have been defined in order to mitigate the risk of improper handling of large input values.
	Each of these three levels has been designated a range of values and an identifier.
	These identifiers are A, B, and C.
	Coordinate pairs are designated to their respective levels based on the sums of their values.
	As a result, if one value of a pair is significantly higher than the other of that pair,
	the pathway taken will be that which has been optimized for the larger value,
	unless one of such values is less than or equal to 0.
	Any coordinate value being less than or equal to 0 results in that pair being handled prior to level assignment,
	thereby not neccesitating its inclusion in the level conditions.
		- Level A is the range of integers greater than 0 but less than 21 (0 < i && i < 21)
		- Level B is the range of integers greater than or equal to 21 but less than 170 (21 <= i && i < 170)
		- Level C is the range of integers greater than or equal to 170 (170 <= i)
*/
#define LEVEL_A_COORDINATE_MAX 21

/*
	Overflow Protection (Task 1)
	Three levels have been defined in order to mitigate the risk of improper handling of large input values.
	Each of these three levels has been designated a range of values and an identifier.
	These identifiers are A, B, and C.
	Coordinate pairs are designated to their respective levels based on the sums of their values.
	As a result, if one value of a pair is significantly higher than the other of that pair,
	the pathway taken will be that which has been optimized for the larger value,
	unless one of such values is less than or equal to 0.
	Any coordinate value being less than or equal to 0 results in that pair being handled prior to level assignment,
	thereby not neccesitating its inclusion in the level conditions.
		- Level A is the range of integers greater than 0 but less than 21 (0 < i && i < 21)
		- Level B is the range of integers greater than or equal to 21 but less than 170 (21 <= i && i < 170)
		- Level C is the range of integers greater than or equal to 170 (170 <= i)
*/
#define LEVEL_B_COORDINATE_MAX 170

// task 1 macro: overflow protection
#define CACHE_MAX 0x8000
// task 1 macro: overflow protection: large prime modulus 
#define M 1000000007

// task 2 macro
#define TOTAL_PYRAMID_LEVELS 5

// task 3 macro: overflow protection -- placeholder (consider 64)
#define MAX_DEPTH 128
// task 3 macro: (), [], {}, <>
#define AMOUNT_LEGAL_PARENTHESES 8


// task 4 macro: valid queen cell
#define QUEEN "X "
// task 4 macro: valid empty cell
#define EMPTY "* "
// task 4 macro: MIN ASCII for zone identity
#define PRINTABLE_MIN 33
// task 4 macro: MAX ASCII for zone identity
#define PRINTABLE_MAX 126
// task 4 macro: tool for checking zone identity
#define PRINTABLE_RANGE (PRINTABLE_MAX - PRINTABLE_MIN + 1)
// task 4 macro: MIN cells for queen board grid
#define DIMENSION_MIN 1
// task 4 macro: MAX cells for queen board grid
#define DIMENSION_MAX 20
// task 4 macro: zone bitmasking used in queen placement validation
#define ZONES_PER_MASK 64
// task 4 macro: 7 * 64 = 448 zones (20x20 sets maximum zones to 400)
#define NUM_ZONES_MASKS 7


// task 5 macro: MAX cells for word grid
#define MAX_GRID_SIZE 30
// task 5 macro: MAX slots for word in grid
#define MAX_SLOTS 100
// task 5 macro: MAX number of words accepted
#define MAX_WORDS 100
// task 5 macro: MAX word length accepted
#define MAX_WORD_LENGTH 15


// task 1 helpers

unsigned long long factorial(long long n);
unsigned long long modMult(unsigned long long a, unsigned long long b);
// task 1: get and validate initial position y-coordinate
long long x1(int *valid);
// task 1: get and validate initial position y-coordinate
long long y1(int *valid);
// task 1: compute total paths from some point to origin
unsigned long long computePaths(long long goLeft, long long goDown);


// task 2 helpers

void setupPyramid();
int getWeight();


// task 3 helpers

// locate symbol among those valid
int findIndex(char symbol);
int processSymbol(int position, int* globalBalance, char expected);


// task 4 helpers

// task 4: generic absolute value function
int abs_val(int x);
// task 4: print valid board solution
void displayBoard(int *board, int dimension);
// task 4: check if zone is already used
int isZoneUsed(int zone_id, unsigned long long *usedZonesMasks);
// task 4: set zone as used
void setZoneUsed(int zone_id, unsigned long long *usedZonesMasks);
// task 4: function to unset zone (used during backtracking)
void unsetZoneUsed(int zone_id, unsigned long long *usedZonesMasks);
/*
task 4:
locate legal queen placements (if possible) using bitmask tracking and adjacency constraints;
prevCol: track the previous row's queen column
*/
int solveRec(int *board, int row, int dimension, 
			unsigned long long usedColumnsMask,
			unsigned long long usedMainDiagonalsMask,
			unsigned long long usedAntiDiagonalsMask,
			unsigned long long *usedZonesMasks,
			char zones[][dimension],
			int prevCol);
// task 4: wrapper for solve function
int solve(int *board, int dimension, 
		  unsigned long long usedColumnsMask,
		  unsigned long long usedMainDiagonalsMask,
		  unsigned long long usedAntiDiagonalsMask,
		  unsigned long long *usedZonesMasks,
		  char zones[][dimension]);


// task 5 helpers and initializations
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
void initializeGrid();
void displayGrid();
// task 5: word can be accepted into the grid
int validPlaceWord(int slotIndex, const char* word);
// task 5: place word in grid
void placeWord(int slotIndex, const char* word);
void removeWord(int slotIndex);
int solveCrossword(int slotIndex);


// task entry points

void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();


// macro used to trigger exit of main while loop from outside of main to gracefully terminate program
#define EXIT 6

// global initialization of main task;
int task = 0;
// global initialization of nextMainTask used in main task input;
char nextMainTask = 0;

 // set task to EXIT (6) outside of main to gracefully exit main 
void fullTerminate() {
	// EXIT = 6
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
			break;
		}
	} while (task != EXIT);
	printf("Goodbye!\n");
	return 0;
}

/*
Task 1
ROBOT PATHS
How many paths could a robot take from (x, y) to (0, 0)?
*/

// task 1: get and validate initial position X-coordinate
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

// task 1: get and validate initial position X-coordinate
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

unsigned long long modMult(unsigned long long a, unsigned long long b) {
	return (a % M) * (b % M) % M;
}

unsigned long long cacheFactorial[FACTORIAL_MAX] = {0ULL};

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
	return cacheFactorial[n] = modMult((unsigned long long)n, factorial(n - 1));
}


// 3: {goLeft, goDown, result}
unsigned long long cachePaths[CACHE_MAX][3] = {0ULL};

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
	if (cachePaths[index][0] == 0ULL
	&& cachePaths[index][1] == 0ULL)
	{
		cachePaths[index][0] = goLeft;
		cachePaths[index][1] = goDown;
		cachePaths[index][2] = result;
		return;
	}
	saveToCache(goLeft, goDown, result, index + 1);
}

/*
	Three levels have been defined in order to mitigate the risk of improper handling of large input values.
	Each of these three levels has been designated a range of values and an identifier.
	These identifiers are A, B, and C.
	Coordinate pairs are designated to their respective levels based on the sums of their values.
	As a result, if one value of a pair is significantly higher than the other of that pair,
	the pathway taken will be that which has been optimized for the larger value,
	unless one of such values is less than or equal to 0.
	Any coordinate value being less than or equal to 0 results in that pair being handled prior to level assignment,
	thereby not neccesitating its inclusion in the level conditions.
		- Level A is the range of integers greater than 0 but less than 21 (0 < i && i < 21)
		- Level B is the range of integers greater than or equal to 21 but less than 170 (21 <= i && i < 170)
		- Level C is the range of integers greater than or equal to 170 (170 <= i)
*/
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
		unsigned long long res = modMult(factorial(goLeft + goDown), modMult(factorial(goLeft), factorial(goDown)));
		saveToCache(goLeft, goDown, res, 0);
		return res;
	}
	return 0;
}

// How many paths could a robot take from (x, y) to (0, 0)?
void task1RobotPaths() {
	int valid = 0;
	printf("Please enter the coordinates of the robot (column, row):\n");
	long long x = x1(&valid);
	if (!valid) {
		scanf("%*[^\n]");
		scanf("%*c");
		return;
	}
	long long y = y1(&valid);
	if (!valid) {
		scanf("%*[^\n]");
		scanf("%*c");
		return;
	}
	unsigned long long totalDistinctPaths = computePaths(x, y);
	printf("The total number of paths the robot can take to reach home is: %llu\n", totalDistinctPaths);
}


/*
Task 2
HUMAN PYRAMID
What is the total weight load of each cheerleader in a pyramid formation?
*/

// task 2: pyramid has 5 levels
double *dataPyramid[TOTAL_PYRAMID_LEVELS];
double level1[1];
double level2[2];
double level3[3];
double level4[4];
double level5[5];

// task 2: initialize empty pyramid
void setupPyramid() {
	dataPyramid[0] = level1;
	dataPyramid[1] = level2;
	dataPyramid[2] = level3;
	dataPyramid[3] = level4;
	dataPyramid[4] = level5;

	// pyramid initialization/reset
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j <= i; j++) {
			dataPyramid[i][j] = 0.00;
		}
	}   
}

// task 2: input and validate weight of cheerleaders
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

// What is the total weight load of each cheerleader in a pyramid formation?
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

			// print result rounded to the hundredth place
			printf("%.2f ", weightLoad);
		}
		printf("\n");
	}
	return;
}

/*
Task 3
PARENTHESIS VALIDATION
Has every opening parenthesis been properly closed?
Legal: (), [], {}, <>
*/

/*
8 legal symbols
4 valid pairs
( ... )
[ ... ]
{ ... }
< ... >
*/
char validSymbols[AMOUNT_LEGAL_PARENTHESES] = {
	'(', ')',
	'[', ']',
	'{', '}',
	'<', '>'
};

// task 3: locate symbol among those valid
int findIndex(char symbol) { 
	for (int i = 0; i < 8; i++) {
		if (validSymbols[i] == symbol) {
			return i;
		}
	}
	return -1;
}

/*
task 3: extract parentheses
0: unbalanced
1: balanced
*/
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

// Has every opening parenthesis been properly closed? (), [], {}, <>
void task3ParenthesisValidator() {
	int globalBalance = 0;
	char expected = '\0';

	scanf("%*c");
	printf("Please enter a term for validation:\n");
	
	if (!processSymbol(0, &globalBalance, expected)) {
		if (task == EXIT) {
			return;
		}
		scanf("%*[^\n]");
		// scanf("%*c");
		printf("The parentheses are not balanced correctly.\n");
	} else {
		printf("The parentheses are balanced correctly.\n");
	}
}


/*Task 4
QUEEN BATTLE
For a square grid of dimensions N x N and exactly N queens,
is there a legal configuration of queens such that
there exists exactly one queen in every row and every column
as well as only empty cells for every of the 8 cells
immediately contiguous to that of every queen?
*/ 

// task 4: compute absolute value
int abs_val(int x) {
	return x < 0 ? -x : x;
}

// task 4: display completed board
void displayBoard(int *board, int dimension) {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (board[i] == (j + 1)) {
				printf(QUEEN);
			} else {
				printf(EMPTY);
			}
		}
		printf("\n");
	}
}

// task 4: check if a zone is already used
int isZoneUsed(int zone_id, unsigned long long *usedZonesMasks) {
	int index = zone_id / ZONES_PER_MASK;
	int bit = zone_id % ZONES_PER_MASK;

	if (index >= NUM_ZONES_MASKS) {
		// out of range zones treated as used to prevent placement
		return 1;
	}

	return (usedZonesMasks[index] & (1ULL << bit)) != 0;
}

// task 4: set zone as used
void setZoneUsed(int zone_id, unsigned long long *usedZonesMasks) {
	int index = zone_id / ZONES_PER_MASK;
	int bit = zone_id % ZONES_PER_MASK;

	if (index < NUM_ZONES_MASKS) {
		usedZonesMasks[index] |= (1ULL << bit);
	}
}

// task 4: unset zone (used during backtracking)
void unsetZoneUsed(int zone_id, unsigned long long *usedZonesMasks) {
	int index = zone_id / ZONES_PER_MASK;
	int bit = zone_id % ZONES_PER_MASK;

	if (index < NUM_ZONES_MASKS) {
		usedZonesMasks[index] &= ~(1ULL << bit);
	}
}

/*
task 4:
locate legal queen placements (if possible) using bitmask tracking and adjacency constraints;
prevCol: track the previous row's queen column
*/
int solveRec(int *board, int row, int dimension, 
			unsigned long long usedColumnsMask,
			unsigned long long usedMainDiagonalsMask,
			unsigned long long usedAntiDiagonalsMask,
			unsigned long long *usedZonesMasks,
			char zones[][dimension],
			int prevCol) {

	// all rows filled
	if (row == dimension) {
		return 1;
	}

	for (int col = 0; col < dimension; col++) {
		// calculate the indices for diagonals
		int mainDiagonal = row - col + dimension - 1;
		int antiDiagonal = row + col;

		// check if column and diagonals are not used
		if (!(usedColumnsMask & (1ULL << col)) &&
			!(usedMainDiagonalsMask & (1ULL << mainDiagonal)) &&
			!(usedAntiDiagonalsMask & (1ULL << antiDiagonal))) {

			// check adjacency with the previous row
			if (row > 0) {
				if (abs_val(col - prevCol) <= 1) {
					// adjacent to a queen in the previous row
					continue;
				}
			}

			// check if the zone is already used
			int zone_id = zones[row][col];
			if (isZoneUsed(zone_id, usedZonesMasks)) {
				// zone already occupied
				continue;
			}

			// place queen
			// store as 1-based index
			board[row] = col + 1; 

			// update masks
			unsigned long long newUsedColumnsMask = usedColumnsMask | (1ULL << col);
			unsigned long long newUsedMainDiagonalsMask = usedMainDiagonalsMask | (1ULL << mainDiagonal);
			unsigned long long newUsedAntiDiagonalsMask = usedAntiDiagonalsMask | (1ULL << antiDiagonal);

			// update usedZonesMasks
			setZoneUsed(zone_id, usedZonesMasks);

			// recurse for next row with updated masks and current column as prevCol
			if (solveRec(board, row + 1, dimension,
								newUsedColumnsMask, newUsedMainDiagonalsMask,
								newUsedAntiDiagonalsMask, usedZonesMasks, zones, col)) {
				// valid thusfar
				return 1;
			}

			// backtrack: remove queen / vacate zone
			board[row] = 0;
			unsetZoneUsed(zone_id, usedZonesMasks);
		}
	}
	// no solution in this path
	return 0; 
}

// task 4: wrapper for solve function
int solve(int *board, int dimension, 
		  unsigned long long usedColumnsMask,
		  unsigned long long usedMainDiagonalsMask,
		  unsigned long long usedAntiDiagonalsMask,
		  unsigned long long *usedZonesMasks,
		  char zones[][dimension]) {
	// initialize prevCol with -2 to avoid adjacency in the first row
	return solveRec(board, 0, dimension, usedColumnsMask, usedMainDiagonalsMask, usedAntiDiagonalsMask, usedZonesMasks, zones, -2);
}

/* For a square grid of dimensions N x N and exactly N queens,
is there a legal configuration of queens such that
there exists exactly one queen in every row and every column
as well as only empty cells for every of the 8 cells
immediately contiguous to that of every queen?
*/
void task4QueensBattle() {
	int dimension;
	printf("Please enter the board dimensions:\n");
	int getSize = scanf(" %d", &dimension);

	if (getSize != 1 || dimension < DIMENSION_MIN || dimension > DIMENSION_MAX) {
		if (getSize == EOF) {
			// exit main
			fullTerminate();
		} else {
			scanf("%*[^\n]");
			scanf("%*c");
			printf("This puzzle cannot be solved.\n");
		}
		return;
	}

	// declare the board array (1-based indexing for columns)
	int board[dimension];
	for (int i = 0; i < dimension; i++) {
		board[i] = 0;
	}

	// clear newline from input buffer
	scanf("%*c");

	// declare and initialize zones
	int inputZone = 0;
	char zones[dimension][dimension];

	printf("Please enter a %d*%d puzzle board:\n", dimension, dimension);

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			inputZone = scanf(" %c", &zones[i][j]);
			if (inputZone != 1) {
				if (inputZone == EOF) {
					// exit main
					fullTerminate();
				} else {
					// early output
					printf("This puzzle cannot be solved.\n");
				}
				return;
			}
		}
	}

	// initialize bitmask variables
	unsigned long long usedColumnsMask = 0;
	unsigned long long usedMainDiagonalsMask = 0;
	unsigned long long usedAntiDiagonalsMask = 0;
	
	// initialize usedZonesMasks array to track zone occupancy
	unsigned long long usedZonesMasks[NUM_ZONES_MASKS];
	for (int i = 0; i < NUM_ZONES_MASKS; i++) {
		usedZonesMasks[i] = 0;
	}

	// final output / result
	if (solve(board, dimension, usedColumnsMask, usedMainDiagonalsMask, usedAntiDiagonalsMask, usedZonesMasks, zones)) {
		printf("Solution:\n");
		displayBoard(board, dimension);
	} else if (task == EXIT) {
		// exit main
		return;
	} else {
		printf("This puzzle cannot be solved.\n");
	}
	scanf("%*[^\n]");
	scanf("%*c");
}


		
// 		clock();

// 		// exit main
// 		return;
// 	}



// // compute absolute value
// int abs(int x) {
// 	return x < 0 ? -x : x;
// }

// // check current cell's zone and adjacent cells for existing queens
// int isValidRec(int *board, int row, int col, int dimension,
// 					char zones[dimension][dimension], int *usedZones, int i) {
// // int isValidRec(int *board, int row, int col,
// // 					char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones, int i) {
// 	if (i >= row) {
// 		unsigned char zone = (unsigned char)zones[row][col];
// 		// zone uniqueness
// 		return !(usedZones[zone]);
// 	}

// 	// Check if the i-th bit is set
// 	if (((tracker >> i) & 1U) == 1U) {
// 		// Bit i is on
// 	}

// 	// Initialize new forbidden columns for the next row
// 	unsigned int newForbiddenColumns = 0;

// 	// Set the bit for the left adjacent column if not in the first column
// 	if (col > 0) {
// 		newForbiddenColumns |= (1U << (col - 1));
// 	}

// 	// Set the bit for the right adjacent column if not in the last column
// 	if (col < dimension - 1) {
// 		newForbiddenColumns |= (1U << (col + 1));
// 	}

// 	// Update the forbiddenColumnsMask for the next recursion
// 	unsigned int updatedForbiddenColumns = forbiddenColumnsMask | newForbiddenColumns;




// 	int x1 = i + 1, y1 = board[i];
// 	int x2 = row + 1, y2 = col + 1;

// 	// check adjacency
// 	if (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1) {
// 		return 0;
// 	}

// 	// check row/column exclusivity
// 	if (y1 == y2) {
// 		return 0;
// 	}

// 	// check diagonal validity
// 	if ((x2 - x1 == y2 - y1 || x2 - x1 == -(y2 - y1)) &&
// 		(abs(x2 - x1) == 1 && abs(y2 - y1) == 1)) {
// 			return 0;
// 		}

// 	return isValidRec(board, row, col, dimension, zones, usedZones, i + 1);
// }

// // wrapper function for validation
// int isValid(int *board, int row, int col, int dimension, char zones[dimension][dimension], int *usedZones) {
// // int isValid(int *board, int row, int col, char zones[DIMENSION_MAX][DIMENSION_MAX], int *usedZones) {
// 	return isValidRec(board, row, col, dimension, zones, usedZones, 0);
// }

// int solveRec(int *board, int row, int dimension, int *usedColumns,
// 					int *usedZones, char zones[dimension][dimension], int col) {
// // int solveRec(int *board, int row, int dimension, int *usedColumns,
// // 					int *usedZones, char zones[DIMENSION_MAX][DIMENSION_MAX], int col) {
// 	// all rows filled
// 	if (row == dimension) {
// 		return 1;
// 	}
// 	// no columns left
// 	if (col >= dimension) {
// 		return 0;
// 	}

// 	// Check if the column is not used, not forbidden, and its zone is not used
// 	if (   !(usedColumnsMask & (1U << col))
// 		&& !(forbiddenColumnsMask & (1U << col))
// 		&& !(usedZonesMask & (1U << zone))) {
// 		// Column is available for placing a queen
// 			// Mark the zone as used
// 			usedZonesMask |= (1U << zone);
// 	}

// 	if (!usedColumns[col] && isValid(board, row, col, dimension, zones, usedZones)) {
// 		board[row] = col + 1;
// 		usedColumns[col] = 1;
// 		unsigned char zone = (unsigned char)zones[row][col];
// 		usedZones[zone] = 1;
// 		if (solveRec(board, row + 1, dimension, usedColumns, usedZones, zones, 0)) {
// 			return 1;
// 		}
// 		usedColumns[col] = 0;
// 		usedZones[zone] = 0;
// 	}
// 	// Mark column 'col' as used
// 	usedColumnsMask |= (1U << col);

// 	// Mark zone 'zone' as used
// 	usedZonesMask |= (1U << zone);
// 	return solveRec(board, row, dimension, usedColumns, usedZones, zones, col + 1);
// }

// // wrapper for solve function
// int solve(int *board, int row, int dimension, int *usedColumns,
// 			int *usedZones, char zones[dimension][dimension]) {
// // int solve(int *board, int row, int dimension, int *usedColumns,
// // 			int *usedZones, char zones[DIMENSION_MAX][DIMENSION_MAX]) {
// 	// track used columns
// 	unsigned int usedColumnsMask = 0;
// 	// track illegal columns due to adjacency
// 	unsigned int forbiddenColumnsMask = 0;
// 	// tracks used zones
// 	unsigned int usedZonesMask = 0;
// 	return solveRec(board, row, dimension, usedColumns, usedZones, zones, 0);
// }

// // recursive function to read zones
// void readZonesRec(int dimension, char zones[dimension][dimension], int filled) {
// // void readZonesRec(char zones[DIMENSION_MAX][DIMENSION_MAX], int dimension, int filled) {
// 	// all cells filled
// 	if (filled >= dimension * dimension) {
// 		return;
// 	}
// 	char c;
// 	int input = scanf("%c", &c);
// 	if (input != 1) {
// 		if (input == EOF) {
// 			// exit main
// 			fullTerminate();
// 		}
// 		return;
// 	}
// 	if (c == ' ' || c == '\n') {
// 		// skip spaces and newlines
// 		readZonesRec(dimension, zones, filled);
// 	} else {
// 		// fill zones
// 		zones[filled / dimension][filled % dimension] = c;
// 		readZonesRec(dimension, zones, filled + 1);
// 	}
// }

// // wrapper for zone reader
// void readZones(int dimension, char zones[dimension][dimension]) {
// // void readZones(int dimension, char zones[DIMENSION_MAX][DIMENSION_MAX]) {
// 	readZonesRec(dimension, zones, 0);
// }

// void setupMonitors(int m, int dimension, int *board, int *usedColumns) {
// 	if (m < dimension) {
// 		board[m] = 0;
// 		usedColumns[m] = 0;
// 		setupMonitors(m + 1, dimension, board, usedColumns);
// 	}
// }


// void task4QueensBattle() {
// 	int dimension;
// 	printf("Please enter the board dimensions:\n");
// 	int getSize = scanf(" %d", &dimension);

// 	if (getSize != 1 || dimension < DIMENSION_MIN || dimension > DIMENSION_MAX) {
// 		if (getSize == EOF) {
// 			// exit main
// 			fullTerminate();
// 		} else {
// 			scanf("%*[^\n]");
// 			scanf("%*c");
// 			printf("This puzzle cannot be solved.\n");
// 		}
// 		return;
// 	}

// 	scanf("%*c");
// 	printf("Please enter a %d*%d puzzle board:\n", dimension, dimension);

// 	clock_t start = clock();

// 	char zones[dimension][dimension];
// 	// char zones[dimension];
// 	// char zones[DIMENSION_MAX][DIMENSION_MAX];
// 	readZones(dimension, zones);
// 	if (task == EXIT) {
// 		// exit main
// 		return;
// 	}
// 	int board[dimension];
// 	// int board[DIMENSION_MAX] = {0};

// 	int usedColumns[dimension];
// 	// int usedColumns[DIMENSION_MAX] = {0};

// 	setupMonitors(0, dimension, board, usedColumns);

// 	// allow all ASCII characters as zone labels (not all are legal -- handled after input)
// 	int usedZones[256] = {0};

// 	if (solve(board, 0, dimension, usedColumns, usedZones, zones)) {
// 	// if (solve(board, 0, dimension, usedColumns, usedZones, zones)) {
// 		printf("Solution:\n");
// 		for (int i = 0; i < dimension; i++) {
// 			for (int j = 1; j <= dimension; j++) {
// 				if (board[i] == j) {
// 					printf(QUEEN);
// 				}
// 				else {
// 					printf(EMPTY);
// 				}
// 			}
// 			printf("\n");
// 		}
// 	} else {
// 		printf("This puzzle cannot be solved.\n");
// 	}
// 	if (task == EXIT) {
		
// 		clock();

// 		// exit main
// 		return;
// 	}
// 	scanf("%*[^\n]");
// 	scanf("%*c");
// 	clock_t end = clock();
//     double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
//     printf("Time taken: %.2f seconds\n", time_spent);
// }


/*
Task 5
CROSSWORD
?
*/ 

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

/* 'H' for horizontal
'V' for vertical
*/
void placeWord(int slotIndex, const char* word) {
	Slot slot = slots[slotIndex];
	for (int i = 0; i < slot.length; i++) {
		int r = slot.row + (slot.direction == 'V' ? i : 0);
		int c = slot.col + (slot.direction == 'H' ? i : 0);
		grid[r][c] = word[i];
	}
}

/* 'H' for horizontal
'V' for vertical
*/
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

/*
?
*/
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

	// scanf("%*c");
	printf("Please enter the number of slots in the crossword:\n");
	input = scanf(" %d", &numSlots);
	if (input == EOF) {
		// exit main
		fullTerminate();
		return;
	}

	// scanf("%*c");
	printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
	for  (int i = 0; i < numSlots; i++) {
		input = (scanf(" %d %d %d %c", &slots[i].row, &slots[i].col, &slots[i].length, &slots[i].direction));
		if (input == EOF) {
			// exit main
			fullTerminate();
			return;
		}
	}

	// scanf("%*c");
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
			// scanf("%*c");
			printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", numSlots);
		}
	} while (numWords < numSlots);

	// scanf("%*c");
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
