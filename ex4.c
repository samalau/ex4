/******************
Name: Samantha Newmark
ID: 346587629
Assignment: 4
*******************/
#include <stdio.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////

// task 1 macro -- overflow protection
#define LARGE 0x8000  // 0x10000
#define M 1000000007

// task 3 macro
#define MAX_DEPTH 128  // placeholder (consider 64)

// task 1 helper
void task1(long long x, long long y);
long long x_1(int *valid);
long long y_1(int *valid);
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
void setupPyramid();
int getWeight();

// task 3 helper
int findIndex(char symbol);
int processSymbol(int position, int* globalBalance, char *expected);

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

// initialize pointers
int task = 0;
int sizeRemainder = 0;
char bufferExtract[] = {0};
char nextMainTask = 0;
char remainderOfExtract[] = {0};


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
        if (nextMainTask != 1 || task < 1 || task > 6) {
            task = 0;
        }
		// scanf("%*[^\n]");
		// scanf("%*[^ ]");
		// scanf("%*c");
		switch (task) {
			case 1:
				task1_robot_paths();
				break;
			case 2:
				task2_human_pyramid();
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
	} while (task != 6);
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
void task1_robot_paths() {
    int valid = 0;
    printf("Please enter the coordinates of the robot (column, row):\n");
    long long x = x_1(&valid);
    if (!valid) { return; }
    long long y = y_1(&valid);
    if (!valid) { return; }
    task1(x, y);
}


// TASK 1 robot paths
unsigned long long factorial(long long n) {
    if (n < 0) { return 0; }
    if (n == 0) { return 1; }
    if (cacheFactorial[n] != 0) { return cacheFactorial[n]; }
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
        if (cacheTask1Flag0[x][y] != 0) return cacheTask1Flag0[x][y];
        return cacheTask1Flag0[x][y] = modMult(factorial(x + y), modMult(factorial(x), factorial(y)));
    }

    // x + y < 170
    if (flag == 1) {
        return modMult(factorial(x + y), modMult(factorial(x), factorial(y)));
    }

    // x + y >= 170
    if (flag == 2) {
        for (int i = 0; i < LARGE; i++) {
            if (cacheTask1Flag2x[i] == x && cacheTask1Flag2y[i] == y) {
                return cacheTask1Flag2Result[i];
            }
        }
        unsigned long long result = modMult(factorial(x + y), modMult(factorial(x), factorial(y)));
        for (int i = 0; i < LARGE; i++) {
            if (cacheTask1Flag2x[i] == 0 && cacheTask1Flag2y[i] == 0) {
                cacheTask1Flag2x[i] = x;
                cacheTask1Flag2y[i] = y;
                cacheTask1Flag2Result[i] = result;
                break;
            }
        }
        return result;
    }
    return 0;
}


void task1(long long x, long long y) {
    unsigned long long totalDistinctPaths = compute_paths(x, y);
    printf("The total number of paths the robot can take to reach home is: %llu\n", totalDistinctPaths);
    return;
}


///////////////////////////////////////////////////////////////////////////


void validateInput_2() {}

// TASK 2 human pyramid
double *dataPyramid[5];
double level_1[1];
double level_2[2];
double level_3[3];
double level_4[4];
double level_5[5];


void setupPyramid() {
    // ensures pointers are initialized once
    static int initialized = 0;

    if (!initialized) {
        dataPyramid[0] = level_1;
        dataPyramid[1] = level_2;
        dataPyramid[2] = level_3;
        dataPyramid[3] = level_4;
        dataPyramid[4] = level_5;
        initialized = 1;
    }

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
                // task is 6 exits main while-loop
                task = 6;
                return 0;
            }

            if (input != 1 || nextWeight < 0) {
                scanf("%*[^\n]");
                if (scanf("%*c") == EOF) {
                    task = 6;
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


void task2_human_pyramid() {
    int fullData = getWeight();

    if (!fullData) return;

    printf("The total weight on each cheerleader is:\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            double weightLoad = dataPyramid[i][j];

            if (i > 0) {
                double weightUpLeft = (j > 0) ? dataPyramid[i - 1][j - 1] / 2.0 : 0;
                double weightUpRight = (j < i) ? dataPyramid[i - 1][j] / 2.0 : 0;
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


void validateInput_3() {}

// TASK 3 parenthesis validation
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
	static int reachedNewline = -1;
    char symbol;
    int input = scanf("%c", &symbol);

    if (input == EOF) {
        return 0;
    }

    if (symbol == '\n') {
		++reachedNewline;
		if (!reachedNewline) {
			return processSymbol(position + 1, globalBalance, expected);
		}
		reachedNewline = -1;
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

void task3_parenthesis_validator() {
    // initialize globalBalance
    int globalBalance = 0;

    // initialize expected
    char expected = '\0';

    printf("Please enter a term for validation:\n");

	// if (scanf("%*[^\n]") == EOF || scanf("%*c") == EOF) {
	// 	return;
	// }

	int isBalanced = processSymbol(0, &globalBalance, &expected);

	// scanf("%*[^\n]");
	// scanf("%*c");

    if (!isBalanced) {
        printf("The parentheses are not balanced correctly.\n");
    } else {
        printf("The parentheses are balanced correctly.\n");
    }
}

///////////////////////////////////////////////////////////////////////////

void validateInput_4() {}

// TASK 4 QUEEN BATTLE
void task4_queens_battle() {
    // Implementation for task 4
}

///////////////////////////////////////////////////////////////////////////

void validateInput_5() {}

// TASK 5 CROSSWORD
void task5_crossword_generator() {
    // Implementation for task 5
}
