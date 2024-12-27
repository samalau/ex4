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
#define MANAGER_MAX 0x8000
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
// Restricted to traveling only left and/or down, how many paths could a robot take from some (x, y) to (0, 0)?
*/

// task 1: get and validate initial position X-coordinate
long long x1(int *valid) {
	long long x;
	int result = scanf(" %lld", &x);
	if (result != 1) {
		if (result == EOF) {
			// exit main
			fullTerminate();
		}
		return (*valid = 0);
	}
	*valid = 1;
	return x;
}

// task 1: get and validate initial position X-coordinate
long long y1(int *valid) {
	long long y;
	int result = scanf(" %lld", &y);
	if (result != 1) {
		if (result == EOF) {
			// exit main
			fullTerminate();
		}
		return (*valid = 0);
	}
	*valid = 1;
	return y;
}

unsigned long long modMult(unsigned long long a, unsigned long long b) {
	return (a % M) * (b % M) % M;
}

unsigned long long managerFactorial[FACTORIAL_MAX] = {0ULL};

unsigned long long factorial(long long n) {
	if (n < 0 || n >= FACTORIAL_MAX) {
		return 0;
	}
	if (n == 0) {
		return 1;
	}
	if (managerFactorial[n] != 0) {
		return managerFactorial[n];
	}
	return managerFactorial[n] = modMult((unsigned long long)n, factorial(n - 1));
}

// 3: {goLeft, goDown, result}
unsigned long long managerPaths[MANAGER_MAX][3] = {0ULL};

unsigned long long findInManager(unsigned long long goLeft, unsigned long long goDown, int index) {
	if (index >= MANAGER_MAX) {
		return 0;
	}
	if (managerPaths[index][0] == goLeft
	&& managerPaths[index][1] == goDown) {
		return managerPaths[index][2];
	}
	return findInManager(goLeft, goDown, index + 1);
}

void saveToManager(unsigned long long goLeft, unsigned long long goDown,
							unsigned long long result, unsigned int index) {
	if (index >= MANAGER_MAX) {
		return;
	}
	if (managerPaths[index][0] == 0ULL
	&& managerPaths[index][1] == 0ULL)
	{
		managerPaths[index][0] = goLeft;
		managerPaths[index][1] = goDown;
		managerPaths[index][2] = result;
		return;
	}
	saveToManager(goLeft, goDown, result, index + 1);
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
		unsigned long long managerdResult = findInManager(goLeft, goDown, 0);
		if (managerdResult != 0) {
			return managerdResult;
		}
		unsigned long long res = modMult(factorial(goLeft + goDown), modMult(factorial(goLeft), factorial(goDown)));
		saveToManager(goLeft, goDown, res, 0);
		return res;
	}
	return 0;
}

// Restricted to traveling only left and/or down, how many paths could a robot take from some (x, y) to (0, 0)?
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

	// determine paths
	unsigned long long totalDistinctPaths = computePaths(x, y);

	// result
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

	// compute and output result
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
	
	// process and result
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
	// prevCol is initialized as -2 to avoid adjacency in the first row
	return solveRec(board, 0, dimension,
							usedColumnsMask,
							usedMainDiagonalsMask,
							usedAntiDiagonalsMask,
							usedZonesMasks,
							zones, -2);
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
	if (solve(board, dimension, usedColumnsMask,
				usedMainDiagonalsMask, usedAntiDiagonalsMask,
				usedZonesMasks, zones)) {
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

	// final output / result
	if (solveCrossword(0)) {
		displayGrid();
	} else {
		printf("This crossword cannot be solved.\n");
	}
}
