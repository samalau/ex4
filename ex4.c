/******************
Name: Samantha Newmark
ID: 346587629
Assignment: 4
*******************/
#include <stdio.h>
#include <string.h>

// task 1 macro
// modulus to prevent overflow
#define M 1000000007

// tasks 1, 3 macro
// placeholder (consider 128)
#define MAX_DEPTH 64


// task 1 helper
void cacheInitialize();
unsigned long long compute_paths(long long x, long long y);
unsigned long long factorial(long long n);

// task 1 cache
unsigned long long cacheFactorial[171] = {0};
unsigned long long cacheTask1Flag0[21][21] = {0};

// task 2 helper
void initializePyramid();
void resetPyramidData();
int getWeight();

// task 3 helper
int findIndex(char symbol);
int processSymbol(int depth);


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
            if (input == EOF){
                task = 6;
            } else {
                task = -1;
            }
            scanf("%*[^\n]");
            scanf(" %*c");
            continue;
        }

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
    return cacheFactorial[n] = (n * factorial(n - 1)) % M;
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
        unsigned long long denominator = (denominator1 * denominator2) % M;

        unsigned long long
            inverse = 1,
            base = denominator,
            exp = M - 2;
        
        while (exp > 0) {
            if (exp % 2 == 1) {
                inverse = (inverse * base) % M;
            }
            base = (base * base) % M;
            exp /= 2;
        }
        return (numerator * inverse) % M;
    }

    // x + y >= 170
    if (flag == 2) {
        if (x > y) {
            // x-dimension segmentation to reduce recursion depth
            return (compute_paths(x / 2, y) * compute_paths(x - x / 2, y)) % M;
        } else {
            // y-dimension segmentation to reduce recursion depth
            return (compute_paths(x, y / 2) * compute_paths(x, y - y / 2)) % M;
        }
    }
    return 0;
}


void task1_robot_paths() {
    long long
        x = -1,
        y = -1;

    unsigned long long totalDistinctPaths = 0;
    int validCoordinates = 0;
    
    while (validCoordinates != 2) {
        printf("Please enter the coordinates of the robot (column, row):\n");

        validCoordinates = scanf(" %lld %lld", &x, &y);
        if (validCoordinates != 2) {
            scanf("%*[^\n]");
            scanf(" %*c");
            if (validCoordinates == EOF) {
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
            totalDistinctPaths = compute_paths(x, y);
        }
    }
    printf("The total number of paths the robot can take to reach home is: %lld\n", totalDistinctPaths);
}


// TASK 2 human pyramid
float *dataPyramid[5];

float
    level_1[] = {-1},  
    level_2[] = {-1, -1},
    level_3[] = {-1, -1, -1},
    level_4[] = {-1, -1, -1, -1},
    level_5[] = {-1, -1, -1, -1, -1};


void initializePyramid() {
    dataPyramid[0] = level_1;
    dataPyramid[1] = level_2;
    dataPyramid[2] = level_3;
    dataPyramid[3] = level_4;
    dataPyramid[4] = level_5;
}


void resetPyramidData() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            dataPyramid[i][j] = -1;
        }
    }
}


int getWeight() {
    printf("Please enter the weights of the cheerleaders:\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            double nextWeight = -1;
            int input = scanf(" %f", &nextWeight);

            if (input == EOF) {
                // 6 exits main while-loop
                task = 6;
                return 0;
            }
            if (input != 1 || nextWeight < 0) {
                printf("Negative weights are not supported.\n");
                // return to main
                return 0;
            }

            dataPyramid[i][j] = nextWeight;
        }
    }
    return 1;
}


void task2_human_pyramid() {
    int fullData = getWeight();
    if (!fullData) return;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {

            int i_alt = i,
                j_alt = j;

            double weightOrigin = dataPyramid[i][j];
            
            // initialize weightLoad
            double weightLoad = weightOrigin;

            if (i > 0) {
                double
                    weightUpLeft = (j > 0) ? dataPyramid[i_alt - 1][j_alt - 1] : 0,
                    weightUpRight = (j < i) ? dataPyramid[i_alt - 1][j] : 0;

                if (j == 0) {
                    weightLoad += weightUpRight / 2;
                } else if (j == i) {
                    weightLoad += weightUpLeft / 2;
                } else {
                    weightLoad += (weightUpLeft + weightUpRight) / 2;
                }
                dataPyramid[i][j] = weightLoad;
            }
            printf("%.2f ", weightLoad);
        }
        printf("\n");
    }
    resetPyramidData();
}


// TASK 3 parenthesis validation
const char bracketMapDim[8] = {'(', '[', '{', '<', '>', '}', ']', ')'};

const int
    identityMapDim[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
    mirrorMapDim[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};


int findIndex(char symbol) { 
    for (int i = 0; i < 8; i++) {
        if (bracketMapDim[i] == symbol) {
            return i;
        }
    }
    return -1;
}


// recursively extract parentheses
int processSymbol(int depth) {
    
    // reset depth if needed
    if (depth >= MAX_DEPTH) {
        depth = 0;
    }

    // buffer index 1 is \0
    char buffer[2];
    int unconfirmed = scanf(" %1[()[]{}<>\n]", buffer);
    char symbol = buffer[0];

    // end of input
    if (unconfirmed != 1 || symbol == '\n') {
        if (unconfirmed == EOF) {
            // 6 exits main while-loop
            task = 6;
        }
        return depth == 0;
    }

    int index = findIndex(symbol);

    if (index == -1) return 0;

    int identity = identityMapDim[index];

    // handle opening parentheses
    if (identity <= 0x08) return processSymbol(depth + 1);

    // handle closing parentheses
    int expectedIndex = findIndex(bracketMapDim[index ^ 7]);
    if (depth <= 0 || mirrorMapDim[index] != identityMapDim[expectedIndex]) {
        return 0;
    }

    return processSymbol(depth - 1);
}


void task3_parenthesis_validator() {
    printf("Please enter a term for validation:\n");

    if (processSymbol(0)) {
        printf("The parentheses are balanced correctly.\n");
    } else if (task != 6) {
        printf("The parentheses are not balanced correctly.\n");
    }
    // task = 6 exits main while-loop

    scanf("%*[^\n]");
    scanf(" %*c");
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
