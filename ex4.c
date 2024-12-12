/******************
Name: Samantha Newmark
ID: 346587629
Assignment: 4
*******************/
#include <stdio.h>
#include <string.h>

void task1_robot_paths();
void task2_human_pyramid();
void task3_parenthesis_validator();
void task4_queens_battle();
void task5_crossword_generator();

int task = -1;

int main()
{   
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf(" %d", &task))
        {
            switch (task)
            {
            case 6:
                break;
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
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            if (scanf(" %*[^\n] %*c") == EOF) task = 6 ;
            // scanf("%*s");
        }

    } while (task != 6);
    printf("Goodbye!\n");
}

int getDistinctPaths(int x, int y) {
    if (x == 0 || y == 0) {
        return 1 ;
    }
    return getDistinctPaths(x - 1, y) + getDistinctPaths(x, y - 1) ;
}

void task1_robot_paths()
{
    int x, y;
    int totalDistinctPathsHome = 0 ;
    int validCoordinates = 0 ;

    while (validCoordinates != 2) {

        printf("Please enter the coordinates of the robot (column, row):\n") ;

        validCoordinates = scanf(" %d %d%*[^\n] %*c", &x, &y) ;

        if (validCoordinates == EOF) {
            task = 6 ;
            break ;
        }

        if (validCoordinates != 2) {
            scanf(" %*[^\n] %*c");
            continue ;
        }

        if (x < 0 || y < 0) {
            totalDistinctPathsHome = 0 ;
        } else {
            totalDistinctPathsHome = getDistinctPaths(x, y) ;
        }
    }

    printf("The total number of paths the robot can take to reach home is: %d\n", totalDistinctPathsHome) ;
}


void initPyramid(float *pyramidData[5]) {
    for (int i = 0 ; i < 5 ; i++) {
        for (int j = i ; j < i + 1 ; j++) {
            pyramidData[i][j] = -1 ;
		}
	}
}


int getWeight() {
    float level0[1], level1[2], level2[3], level3[4], level4[5] ;
    float *pyramidData[5] = {level0, level1, level2, level3, level4} ;
    initPyramid(pyramidData) ;

    int input = 0 ;
    int nextWeight = -1 ;
    int fullPyramid = 0 ;
    while (!fullPyramid) {
        printf("Please enter the weights of the cheerleaders:\n") ;

        for (int i = 0; i < 5 ; i++) {
            for (int j = i ; j < i + 1 ; j++)
            {
                input = scanf(" %.2f", &nextWeight) ;

                if (input == EOF) return NULL ;

                if (input != 1 || nextWeight < 0)
                {
                    scanf(" %*[^\n]") ;
                    scanf(" %*c");
                    prinf("Negative weights are not supported.\n") ;
                    break ;
                }
                pyramidData[i][j] = nextWeight ;
            }
            if (input != 1 || nextWeight < 0) break;
            
        }
    }
}


void task2_human_pyramid()
{
     
    getWeight() ;


}

void task3_parenthesis_validator()
{
    // Todo
}

void task4_queens_battle()
{
    // Todo
}

void task5_crossword_generator()
{
    // Todo
}