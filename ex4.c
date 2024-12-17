/******************
Name: Samantha Newmark
ID: 346587629
Assignment: 4
*******************/
#include <stdio.h>
#include <string.h>


// task 1 macro -- overflow protection
#define LARGE 0x8000  // 0x10000
#define M 1000000007

// task 3 macro
#define MAX_DEPTH 128  // placeholder (consider 64)

// task 1 helper
void cacheInitialize();
unsigned long long factorial(long long n);
unsigned long long modMult(unsigned long long a, unsigned long long b);
unsigned long long compute_paths(long long x, long long y);

// task 1 cache
unsigned long long cacheFactorial[171] = {0};
unsigned long long cacheTask1Flag0[21][21] = {0};
unsigned long long cacheTask1Flag2x[LARGE] = {0};
unsigned long long cacheTask1Flag2y[LARGE] = {0};
unsigned long long cacheTask1Flag2Result[LARGE] = {0};

// task 2 helper
void initializePyramid();
void resetPyramidData();
int getWeight();

// task 3 helper
int findIndex(char symbol);
int processSymbol(int depth, int remainingDepth, int* globalBalance);

// task entry points
void task1_robot_paths();
void task2_human_pyramid();
void task3_parenthesis_validator();
void task4_queens_battle();
void task5_crossword_generator();

// initialize cache
void cacheInitialize() {
	cacheFactorial[0] = 1;
	cacheFactorial[1] = 1;
	cacheTask1Flag0[1][1] = 2;
}

// initialize task
int task = -1;

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
		
		int input = scanf(" %d", &task);
		
		if (input != 1) {
			if (input == EOF) {
				printf("Goodbye!\n");
				return 0;
			} else {
				scanf("%*[^\n]");
				scanf("%*c");
				printf("Please choose a task number from the list.\n");
				task = -1;
				continue;
			}
		}

		switch (task) {
			case 1:
				task1_robot_paths();
				break;
			case 2:
				task2_human_pyramid();
				setupPyramid();
				break;
			case 3:
				task3_parenthesis_validator();
				break;
			case 4:
				task4_queens_battle();
				break;
			case 5:
				task5_crossword_generator();
				break;
			case 6:
				break;
			default:
				printf("Please choose a task number from the list.\n");
				break;
		}
		scanf("%*[^\n]");
		scanf("%*c");
	} while (task != 6);

	printf("Goodbye!\n");
	return 0;
}


// TASK 1 robot paths
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
	return ((a % M) * (b % M)) % M;
}

unsigned long long compute_paths(long long x, long long y) {
	if (x < 0 || y < 0) return 0;
	if (x == 0 || y == 0) return 1;

	int flag = (x + y <= 20) ? 0 : ((x + y < 170) ? 1 : 2);

	// x + y <= 20
	if (flag == 0) {
		if (cacheTask1Flag0[x][y] != 0) {
			return cacheTask1Flag0[x][y];
		}
		cacheTask1Flag0[x][y] = compute_paths(x - 1, y) + compute_paths(x, y - 1);
		return cacheTask1Flag0[x][y] ;
	}

	// x + y < 170
	if (flag == 1) {
		unsigned long long
			numerator = -1,
			denominator1 = -1,
			denominator2 = -1;
		
		// NUMERATOR
		numerator = factorial(x + y);

		// DENOMINATOR
		denominator1 = factorial(x);
		denominator2 = factorial(y);
		unsigned long long denominator = modMult(denominator1, denominator2);

		unsigned long long
			inverse = 1,
			base = denominator,
			exp = M - 2;
		
		while (exp > 0) {
			if (exp % 2 == 1) {
				inverse = modMult(inverse, base);
			}
			base = modMult(base, base);
			exp /= 2;
		}
		return modMult(numerator, inverse);
	}

	// x + y >= 170
	if (flag == 2) {
		int index = (x + y) % LARGE;
		if (cacheTask1Flag2x[index] == x && cacheTask1Flag2y[index] == y) {
			return cacheTask1Flag2Result[index];
		}

		cacheTask1Flag2x[index] = x;
		cacheTask1Flag2y[index] = y;

		if (x > y) {
			// x-dimension segmentation to reduce recursion depth
			return cacheTask1Flag2Result[index] = modMult(compute_paths(x / 2, y), compute_paths(x - x / 2, y));
		} else {
			// y-dimension segmentation to reduce recursion depth
			return cacheTask1Flag2Result[index] = modMult(compute_paths(x, y / 2), compute_paths(x, y - y / 2));
		}
	}
	return 0;
}


void task1_robot_paths() {
	unsigned long long totalDistinctPaths = 0;
	long long x = -1, y = -1;
	int validCoordinates = 0;

	// protects against number input longer than long long limit
	// x: charsRead <= 20, y: charsRead <= 20
	// x+y: charsRead <= 40
	int charsRead = 0;

	while (validCoordinates != 2) {
		printf("Please enter the coordinates of the robot (column, row):\n");

		validCoordinates = scanf(" %lld %lld%n", &x, &y, &charsRead);

		int detectedTrailingChars = scanf("%*[^\n]");
		if (validCoordinates != 2 || detectedTrailingChars != 0 || charsRead > 40) {
			scanf(" %*c");
			if (validCoordinates == EOF || detectedTrailingChars == EOF) {
				task = 6;
				return;
			}
			continue;
		}

		if (x < 0 || y < 0) {
			totalDistinctPaths = 0;
		} else if (x == 0 || y == 0) {
			totalDistinctPaths = 1;
		} else {
			if (x >=0 && x < LARGE && y >=0 && y < LARGE && x + y < LARGE){
				totalDistinctPaths = compute_paths(x, y);
			}
			else {
				// placeholder overflow protection
				totalDistinctPaths = 0;
			}
		}
	}
	printf("The total number of paths the robot can take to reach home is: %llu\n", totalDistinctPaths);
}


// TASK 2 human pyramid
double *dataPyramid[5];
double
	level_1[1] = {0.00},
	level_2[2] = {0.00},
	level_3[3] = {0.00},
	level_4[4] = {0.00},
	level_5[5] = {0.00};


void setupPyramid() {
	// ensures pointers are initialized once
	static int initialized = 0;

	// track when needs reset
    static int pyramidNeedsReset = 1;

    if (!initialized) {
        // one-time pointer setup
        dataPyramid[0] = level_1;
        dataPyramid[1] = level_2;
        dataPyramid[2] = level_3;
        dataPyramid[3] = level_4;
        dataPyramid[4] = level_5;
        initialized = 1;
    }

    if (pyramidNeedsReset) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j <= i; j++) {
                dataPyramid[i][j] = -1.00;
            }
        }
        pyramidNeedsReset = 0;
		// pyramid is now reset
    }
}


int getWeight() {
	printf("Please enter the weights of the cheerleaders:\n");

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j <= i; j++) {

			double nextWeight = -1.00;
			int input = scanf(" %lf", &nextWeight);

			if (input == EOF) {
				// 6 exits main while-loop
				task = 6;
				return 0;
			}

			if (input != 1 || nextWeight < 0) {
				printf("Negative weights are not supported.\n");
				// scanf("%*[^\n]");
				// scanf("%*c");
				// return to main
				return 0;
			}

			// valid weight
			dataPyramid[i][j] = nextWeight;
			if (i == 0) {
				static int pyramidNeedsReset = 1;
			}
		}
	}
	return 1;
}


void task2_human_pyramid() {
	int fullData = getWeight();
	
	if (!fullData) return;

	printf("The total weight on each cheerleader is:\n");

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j <= i; j++) {

			int i_alt = i,
				j_alt = j;

			double weightOrigin = dataPyramid[i][j];
			
			// initialize weightLoad
			double weightLoad = weightOrigin;

			if (i > 0) {
				double
					weightUpLeft = (i_alt > 0 && j_alt > 0) ? dataPyramid[i_alt - 1][j_alt - 1] : 0,
					weightUpRight = (i_alt > 0 && j_alt < i_alt) ? dataPyramid[i_alt - 1][j_alt] : 0;

				if (j == 0) {
					weightLoad += weightUpRight;
				} else if (j == i) {
					weightLoad += weightUpLeft;
				} else {
					weightLoad += (weightUpLeft + weightUpRight);
				}
				double weightLoad = (weightLoad * 100.0 + 0.5) / 100.0;
				dataPyramid[i][j] = weightLoad;
			}
			printf("%.2f ", weightLoad);
		}
		printf("\n");
	}
}


// TASK 3 parenthesis validation
const char validSymbols[8] = {
	'(', ')',    // 0x01, 0x80
	'[', ']',    // 0x02, 0x40
	'{', '}',    // 0x04, 0x20
	'<', '>'     // 0x08, 0x10
};

const int symbolBitmask[8] = {
	0x01, 0x80,    // '(', ')'
	0x02, 0x40,    // '[', ']'
	0x04, 0x20,    // '{', '}'
	0x08, 0x10     // '<', '>'
};

const int symbolMirrormask[8] = {
	0x80, 0x01,    // ')', '('
	0x40, 0x02,    // ']', '['
	0x20, 0x04,    // '}', '{'
	0x10, 0x08     // '>', '<'
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
// balanced is 1, unbalanced is 0
int processSymbol(int depth, int remainingDepth, int* globalBalance) {
	// depth reset --overflow protection
	if (remainingDepth < 0) return (depth == 0 && *globalBalance == 0) ? 1 : 0;

	char symbol;
	int unconfirmed;

	while ((unconfirmed = scanf(" %*[^()[]{}<>\n]%c", &symbol)) == 1) {

		if (symbol == '\n') {
			return (depth == 0 && *globalBalance == 0) ? 1 : 0;
		}

		// char validation, identification in validSymbols
		int index = findIndex(symbol);

		// protection against any remaining invalid chars
		if (index == -1) {
			scanf("%*[^()[]{}<>\n]");
			continue;
		}

		// handle opening parentheses
		if (symbolBitmask[index] <= 0x08) {
			// increase global balance for opening parentheses
			(*globalBalance)++;
			if (!processSymbol(depth + 1, remainingDepth - 1, globalBalance)) {
				// unbalanced
				return 0;
			}
		}

		// handle closing parentheses
		else {
			// mirrormask identification, validaton
			// int expectedIndex = validSymbols;
			// validate mirror match to bitmask
			if (*globalBalance <= 0 || symbolMirrormask[index] != symbolBitmask[findIndex(validSymbols[index ^ 1])]) {
				// unbalanced
				return 0;
			}
			// decrease global balance for closing parentheses
			(*globalBalance)--;
			if (!processSymbol(depth - 1, remainingDepth - 1, globalBalance)) {
				// unbalanced
				return 0;
			}
		}
	}

	// end of input
	if (unconfirmed == EOF) {
		// 6 exits main while-loop
		task = 6;
		return (*globalBalance == 0);
	}

	return (depth == 0 && *globalBalance == 0) ? 1 : 0;
}


void task3_parenthesis_validator() {
	// initialize remainingDepth
	int remainingDepth = MAX_DEPTH;

	// initialize globalBalance
	int globalBalance = 0;

	printf("Please enter a term for validation:\n");

	if (processSymbol(0, remainingDepth - 1, &globalBalance)) {
		printf("The parentheses are balanced correctly.\n");
	} else {
		// nothing prints for EOF, task has been reassigned 6
		if (task != 6) {
			printf("The parentheses are not balanced correctly.\n");
		}
	}
}


// TASK 4 QUEEN BATTLE
void task4_queens_battle()
{
	// Todo
}


// TASK 5 CROSSWORD
void task5_crossword_generator()
{
	// Todo
}
