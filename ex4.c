/******************
Name: Samantha Newmark
ID: 346587629
Assignment: 4
*******************/
#include <stdio.h>
#include <string.h>

void task1_robot_paths() ;
void task2_human_pyramid() ;
void task3_parenthesis_validator() ;
void task4_queens_battle() ;
void task5_crossword_generator() ;

int task = -1 ;

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
               "6. Exit\n") ;

        if (scanf(" %d", &task))
        {
            switch (task)
            {
            case 6:
                break;
            case 1:
                task1_robot_paths() ;
                break;
            case 2:
                task2_human_pyramid() ;
                break;
            case 3:
                task3_parenthesis_validator() ;
                break;
            case 4:
                task4_queens_battle() ;
                break;
            case 5:
                task5_crossword_generator() ;
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            if (scanf(" %*[^\n] %*c") == EOF) {task = 6 ; } ;
            // scanf("%*s");
        }

    } while (task != 6);
    printf("Goodbye!\n");
}


int getDistinctPaths(int x , int y) {
    if (x == 0 || y == 0) {
        return 1 ;
    }
    return getDistinctPaths(x - 1 , y) + getDistinctPaths(x , y - 1) ;
}

void task1_robot_paths()
{
    int
        x = -1 ,
        y = -1 ,
        totalDistinctPathsHome = 0,
        validCoordinates = 0 ;

    while (validCoordinates != 2) {

        printf("Please enter the coordinates of the robot (column, row):\n") ;

        validCoordinates = scanf(" %d %d%*[^\n] %*c", &x , &y) ;

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
            totalDistinctPathsHome = getDistinctPaths(x , y) ;
        }
    }

    printf("The total number of paths the robot can take to reach home is: %d\n", totalDistinctPathsHome) ;
}


void initPyramid(float *pyramidData[5]) {
    for (int i = 0 ; i < 5 ; i++) {
        for (int j = 0 ; j <= i ; j++) {
            pyramidData[i][j] = -1 ;
		}
	}
}

void getWeight(float *pyramidData[5]) {
    int fullPyramid = 0 ;
    while ( !fullPyramid ) {
        initPyramid(pyramidData) ;
        int input = 0 ;
        float nextWeight = -1.00 ;

        printf("Please enter the weights of the cheerleaders:\n") ;

        for (int i = 0; i < 5 ; i++) {
            for (int j = 0 ; j <= i ; j++)
            {
                input = scanf(" %f", &nextWeight) ;

                if (input == EOF) {
                    task = 6 ;
                    return ;
                }
                if (input != 1 || nextWeight < 0)
                {
                    printf("Negative weights are not supported.\n") ;
                    break ;
                } else {
                    pyramidData[i][j] = nextWeight ;
                }
            }
            if (input != 1 || nextWeight < 0) break ;
        }
        if (input != 1 || nextWeight < 0) return ;

        // assumption for validation
        fullPyramid = 1 ;

        // validation
        for (int k = 0 ; k < 5 ; k++) {
            for (int l = 0 ; l <= k ; l++) {
                if (pyramidData[k][l] < 0) {
                    fullPyramid = 0 ;
                    break ;
                }
            }
            if ( !fullPyramid ) {
                break ;
            }
        }
        if ( !fullPyramid ) {
            continue ;
        }
    }
}


void task2_human_pyramid()
{
    float
        level0[1] ,
        level1[2] ,
        level2[3] ,
        level3[4] ,
        level4[5] ,
        *pyramidData[5] = { level0 ,
                            level1 ,
                            level2 ,
                            level3 ,
                            level4 } ;
    
    initPyramid(pyramidData) ;
    getWeight(pyramidData) ;

    if (pyramidData[4][4] >= 0) {
        for (int i = 0 ; i < 5 ; i++) {
            for (int j = 0 ; j <= i ; j++) {

                int 
                    iUpLevel = 0 ,
                    jUpLeft = 0 ,
                    jUpRight = 0 ,
                    i_alt = i ,
                    j_alt = j ;
                float
                    weightOrigin = pyramidData[i][j] ,
                    weightUpLeft = 0.00 ,
                    weightUpRight = 0.00 ,
                    weightLoad = 0.00 ;

                if (j == 0) {

                    iUpLevel = i_alt - 1 ;
                    jUpRight = j_alt ;
                    weightUpRight = pyramidData[iUpLevel][jUpRight] ;
                    if (i == 0 || (i != 0 && weightUpRight == 0)) {
                        weightLoad = weightOrigin ;
                    } else if (weightUpRight >= 0) {
                        weightLoad = weightOrigin + ((float)weightUpRight / 2) ;
                    } else return ;
                
                } else if (j > 0 && j < i) {

                    iUpLevel = i_alt - 1 ;
                    jUpLeft = j_alt - 1 ;
                    jUpRight = j_alt ;

                    weightUpLeft = pyramidData[iUpLevel][jUpLeft] ;
                    weightUpRight = pyramidData[iUpLevel][jUpRight] ;

                    if (weightUpLeft) {

                        if (weightUpRight) {
                            weightLoad = weightOrigin + ((float)(weightUpLeft + weightUpRight) / 2) ;
                        } else {
                            weightLoad = weightOrigin + ((float)(weightUpLeft) / 2) ;
                        }
                    
                    } else {

                        if (weightUpRight) {
                            weightLoad = weightOrigin + ((float)(weightUpRight) / 2) ;
                        } else {
                            weightLoad = weightOrigin ;
                        }
                    }
                } else if (i > 0 && j == i) {
                    iUpLevel = i_alt - 1 ;
                    jUpLeft = j_alt - 1 ;
                    weightUpLeft = pyramidData[iUpLevel][jUpLeft] ;
                    if (weightUpLeft)
                        { weightLoad = weightOrigin + ((float)weightUpLeft / 2) ; }
                    else
                        { weightLoad = weightOrigin ; }
                }
                
                if (i != 0 && j != 0) {
                    
                }
                
                printf("%.2f\n", weightLoad) ;  // placeholder
            }
	    }
    }
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