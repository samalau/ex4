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
#define MIN_BOARD_SIZE 1
#define MAX_BOARD_SIZE 20
#define EMPTY_CELL '*'
#define QUEEN_CELL 'X'

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

int validate_color_zones(int size, Cell board[][size], char mapped_colors[], int *unique_colors) {
      // count occurrences of each color
    int color_count[MAX_BOARD_SIZE];

    // track number of unique colors
    *unique_colors = 0;

    // initialize color_count
    for (int i = 0; i < size; i++) {
        color_count[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char color = board[i][j].color;
            int mapped_index = -1;
            for (int k = 0; k < *unique_colors; k++) {
                if (mapped_colors[k] == color) {
                    mapped_index = k;
                    break;
                }
            }

            if (mapped_index == -1) {
                if (*unique_colors >= size) {
                    // too many unique colors for the board size
                    return 0;
                }
                mapped_index = (*unique_colors)++;
                mapped_colors[mapped_index] = color;
            }

            color_count[mapped_index]++;
        }
    }

    return *unique_colors == size;
}

int queen_in_row(int size, Cell board[][size], int row) {
    for (int col = 0; col < size; col++) {
        if (board[row][col].has_queen) {
            return 1;
        }
    }
    return 0;
}

int queen_in_col(int size, Cell board[][size], int col) {
    for (int row = 0; row < size; row++) {
        if (board[row][col].has_queen) {
            return 1;
        }
    }
    return 0;
}

int queen_in_direct_diagonal(int size, Cell board[][size], int row, int col) {
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int i = 0; i < 4; i++) {
        int new_row = row + directions[i][0];
        int new_col = col + directions[i][1];
        if (new_row >= 0 && new_row < size && new_col >= 0 && new_col < size && board[new_row][new_col].has_queen) {
             return 1;
        }
    }
    return 0;
}

int is_valid_queen(int size, Cell board[][size], int row, int col, int *color_with_queen) {
    // initialize
    int color_map[size];
    for (int i = 0; i < size; i++) {
        color_map[i] = -1;
    }

    char color = board[row][col].color;

    // map character to index
    if (color_map[(unsigned char)color] == -1) {
        static int next_index = 0;
        color_map[(unsigned char)color] = next_index++;
    }

    int index = color_map[(unsigned char)color];
    return !queen_in_row(size, board, row) &&
           !queen_in_col(size, board, col) &&
           !queen_in_direct_diagonal(size, board, row, col) &&
           color_with_queen[index] == 0;
}

void mark_queen(int size, Cell board[][size], int row, int col, int *color_with_queen, char mapped_colors[]) {
    board[row][col].has_queen = 1;
    char color = board[row][col].color;

    // find mapped index for color
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (mapped_colors[i] == color) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        color_with_queen[index] = 1;
    }
}

void mark_not_queen(int size, Cell board[][size], int row, int col, int *color_with_queen, char mapped_colors[]) {
    board[row][col].has_queen = 0;
    char color = board[row][col].color;

    // find mapped index for color
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (mapped_colors[i] == color) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        color_with_queen[index] = 0;
    }
}

int queens_solver(int size, Cell board[][size], int assigned_queens, int start, int *color_with_queen, char mapped_colors[]) {
    if (assigned_queens == size) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        if (is_valid_queen(size, board, start, i, color_with_queen)) {
            mark_queen(size, board, start, i, color_with_queen, mapped_colors);

            if (queens_solver(size, board, assigned_queens + 1, start + 1, color_with_queen, mapped_colors)) {
                return 1;
            }
            // backtrack
            mark_not_queen(size, board, start, i, color_with_queen, mapped_colors);
        }
    }
    return 0;
}

void display_board(int size, Cell board[][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c ", board[i][j].has_queen ? QUEEN_CELL : EMPTY_CELL);
        }
        printf("\n");
    }
}

void task4QueensBattle() {
    int size;
    printf("Please enter the dimensions of the board:\n");
    int inputSize = scanf(" %d", &size);
    if (inputSize == EOF) {
        full_terminate();
        return;
    }

    if(inputSize != 1) {
        scanf("%*[^\n]");
        return;
    }

    if (size < MIN_BOARD_SIZE || size > MAX_BOARD_SIZE) {
        printf("This puzzle cannot be solved.\n");
        return;
    }

    Cell board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    char mapped_colors[MAX_BOARD_SIZE];
    int unique_colors;

    printf("Please enter the %d*%d puzzle board:\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int input_zone = scanf(" %c", &board[i][j].color);
            if (input_zone == EOF) {
                full_terminate();
                return;
            }
            if (input_zone != 1) {
                scanf("%*[^\n]");
                return;
            }
            board[i][j].has_queen = 0;
        }
    }

    if (!validate_color_zones(size, board, mapped_colors, &unique_colors)) {
        printf("This puzzle cannot be solved.\n");
        return;
    }

    // Initialize to 0
    int color_with_queen[MAX_BOARD_SIZE] = {0};

    if (queens_solver(size, board, 0, 0, color_with_queen, mapped_colors)) {
        display_board(size, board);
    } else {
        printf("This puzzle cannot be solved.\n");
    }
}

///////////////////////////////////////////////////////////////////////////

// TASK 5 CROSSWORD
void task5CrosswordGenerator() {

}
