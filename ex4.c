/******************
Name: Samantha Newmark
ID: 346587629
Assignment: 4
*******************/
#include <stdio.h>
#include <string.h>

#define CHUNK_SIZE 1024

void task1_robot_paths() ;
void task2_human_pyramid() ;
void task3_parenthesis_validator() ;
void task4_queens_battle() ;
void task5_crossword_generator() ;

// initialize task for main
int task = -1 ;

int main() {
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n") ;

        if (scanf(" %d", &task))
        {
            switch (task)
            {
            case 6:
                break ;
            case 1:
                task1_robot_paths() ;
                break ;
            case 2:
                task2_human_pyramid() ;
                break ;
            case 3:
                task3_parenthesis_validator() ;
                break ;
            case 4:
                task4_queens_battle() ;
                break ;
            case 5:
                task5_crossword_generator() ;
                break ;
            default:
                printf("Please choose a task number from the list.\n") ;
                break ;
            }
        }
        else
        {
            if (scanf(" %*[^\n] %*c") == EOF) { task = 6 ; }
            // scanf("%*s");
        }

    } while (task != 6) ;

    printf("Goodbye!\n") ;
}


long long getDistinctPaths(long long x, long long y) {

    if (x > y) return getDistinctPaths(x - y, y) + getDistinctPaths(y, y) ;

    else if (y > x) return getDistinctPaths(x, y - x) + getDistinctPaths(x, x) ;

    else return 2 * getDistinctPaths(x - 1, y) ;
}


void task1_robot_paths() {

    long long
        x = -1,
        y = -1,
        totalDistinctPathsHome = 0 ;
    int validCoordinates = 0 ;
    
    while (validCoordinates != 2) {
        printf("Please enter the coordinates of the robot (column, row):\n") ;

        validCoordinates = scanf(" %lld %lld%*[^\n] %*c", &x, &y) ;

        if (validCoordinates == EOF) {
            task = 6 ;
            break ;
        }

        if (validCoordinates != 2) {
            scanf(" %*[^\n] %*c");
            continue ;
        }

        if (x < 0 || y < 0) { totalDistinctPathsHome = 0 ; }

        else if (x == 0 || y == 0) { totalDistinctPathsHome = 1 ; }

        else { totalDistinctPathsHome = getDistinctPaths(x, y) ; }
    }
    printf("The total number of paths the robot can take to reach home is: %lld\n", totalDistinctPathsHome) ;
}


float dataPyramid[5][5] = {
    {-1},  // top level
    {-1, -1},  // second level
    {-1, -1, -1},  // third level
    {-1, -1, -1, -1},  // fourth level
    {-1, -1, -1, -1, -1}  // fifth level
} ;


void resetPyramidData() {

    float freshPyramid[5][5] = {
        {-1},  // top level
        {-1, -1},  // second level
        {-1, -1, -1},  // third level
        {-1, -1, -1, -1},  // fourth level
        {-1, -1, -1, -1, -1}  // fifth level
    } ;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            dataPyramid[i][j] = freshPyramid[i][j];
        }
    }
}


int getWeight(float *dataPyramid[5]) {

    printf("Please enter the weights of the cheerleaders:\n") ;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {

            // initialize nextWeight
            float nextWeight = -1.00;

            int input = scanf(" %f", &nextWeight) ;

            // task 6 exits main menu
            if (input == EOF) {
                task = 6 ;
                return 0 ;
            }

            if (input != 1 || nextWeight < 0) {
                printf("Negative weights are not supported.\n") ;
                return 0 ;
            }

            dataPyramid[i][j] = nextWeight ;
        }
    }
    return 1 ;
}


void task2_human_pyramid() {
    
    int fullData = getWeight(dataPyramid) ;
    if (!fullData) return ;

    for (int i = 0 ; i < 5 ; i++) {
        for (int j = 0 ; j <= i ; j++) {
            int
                i_alt = i,
                j_alt = j ;

            float weightOrigin = dataPyramid[i][j] ;
            
            // initialize weightLoad
            float weightLoad = weightOrigin ;

            if (i > 0) {
                float
                    weightUpLeft = (j > 0) ? dataPyramid[i_alt - 1][j_alt - 1] : 0,
                    weightUpRight = (j < i) ? dataPyramid[i_alt - 1][j] : 0 ;

                if (j == 0) { weightLoad += weightUpRight / 2 ; }
                else if (j == i) { weightLoad += weightUpLeft / 2 ; }
                else { weightLoad += (weightUpLeft + weightUpRight) / 2 ; }

                dataPyramid[i][j] = weightLoad ;
            }

            printf("%.2f ", weightLoad) ;
        }
        printf("\n") ;
    }
    resetPyramidData() ;
}


const char bracketMapDim[8] = {'(', '[', '{', '<', '>', '}', ']', ')'} ;
const int
    identityMapDim[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80},
    mirrorMapDim[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01} ;


int findIndex(char symbol) {
    for (int i = 0; i < 8; i++) {
        if (bracketMapDim[i] == symbol)
            { return i ; }
    }
    return -1 ;
}


// process input and check parentheses
int processRecursive(int depth) {
    char symbol ;

    // end of input
    int unconfirmed = scanf("%c", &symbol) ;

    // task 6 exits main menu
    if (unconfirmed == EOF) { task = 6 ; }

    if (unconfirmed != 1 || symbol == '\n') return depth == 0 ;

    int index = findIndex(symbol) ;

    // skip non-bracket
    if (index == -1) return processRecursive(depth) ;

    int identity = identityMapDim[index] ;

    // handle opening parentheses
    if (identity <= 0x08) {
        return processRecursive(depth + 1) ;
    }

    // handle closing parentheses
    else if (depth <= 0 || mirrorMapDim[index] != identityMapDim[findIndex(bracketMapDim[index ^ 7])]) {
        return 0 ;
    }

    return processRecursive(depth - 1) ;
}


void task3_parenthesis_validator() {
    printf("Please enter a term for validation:\n") ;
    
    if (processRecursive(0)) printf("The parentheses are balanced correctly.\n") ;
    
    else if (task != 6) printf("The parentheses are not balanced correctly.\n") ;
    
    scanf(" %*[^\n]"); scanf(" %*c");
}

void task4_queens_battle()
{
    // Todo
}

void task5_crossword_generator()
{
    // Todo
}
