#include<stdio.h>
#define MAX 9
#define ZERO 0
static int solvecount = 0;
static int solve1count = 0;
void printSudoku(int sudoku[MAX][MAX]);                       //Prints the sudoku
int checkEntries(int row,int col,int value);                  // Checks if entered integers are between 0 and 9
int solveSudoku(int sudoku[MAX][MAX]);                       //Solves the sudoku
int columnCheck(int sudoku[MAX][MAX],int col,int val);       //checks if val is present in any of the col entries
int rowCheck(int sudoku[MAX][MAX],int row,int val);          //checks if val is present in any of the row entries
int gridCheck(int sudoku[MAX][MAX],int row,int col,int val);//checks if val is pres in the 3x3 grid
int check(int sudoku[MAX][MAX],int row,int col,int val);    //checks if all the checks are true
int solve(int sudoku[MAX][MAX]);                            //Fills in each single possible solution in a cell
int solve1(int sudoku[MAX][MAX]);                           //Fills if more than one solution to a cell
int noOfPossibility(int sudoku[MAX][MAX],int row,int col);  //Gives the number of posible solutions
int singlePossibility(int sudoku[MAX][MAX],int row,int col);//Gives the value of a single possible solution to a cell


int main()
{
	int sudoku[MAX][MAX] = {ZERO};
	int row,col,i,j,n,value;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			scanf("%d",&sudoku[i][j]);
		}
	}
#ifdef COMMENT
	printf("How many values are to entered?\n");
	scanf("%d",&n);
	printf("Enter:\nROW\tCOLUMN\tVALUE\n");
	for(i = 0;i < n;i++)
	{
		scanf("%d %d %d",&row,&col,&value);
		while(checkEntries(row,col,value) == 0)
		{
			printf("Enter correctly!\n");
			scanf("%d %d %d",&row,&col,&value);
		}
		sudoku[row-1][col-1] = value;
	}
#endif
	printf("The values are:\n");
	printSudoku(sudoku);
	if(solve(sudoku) == 1)
	{
		printf("SOLUTION\n");
		printSudoku(sudoku);
	}
	else
	{
		printf("\nSolution cannot be determined\n");
	}


	return 0;
}

int checkEntries(int row,int col,int value)
{
	if(row >= 0 && row <= 9 && col >= 0 && col <= 9 && value >= 0 && value <= 9)
	{
		return 1;
	}
	return 0;
}


void printSudoku(int sudoku[MAX][MAX])
{
	int row,col;
	printf("-------------------------------------\n");
	for(row=0;row<MAX;row++)
	{
		printf("|");
		for(col=0;col<MAX;col++)
		{
			printf(" %d |",sudoku[row][col]);
		}
		printf("\n-------------------------------------");
		printf("\n");
	}
}

int columnCheck(int sudoku[MAX][MAX],int col,int val)
{
	int index;
	for(index = 0;index < MAX;index++)
	{
		if(sudoku[index][col] == val)
		{
			return 0;
		}
	}
	return 1;
}

int rowCheck(int sudoku[MAX][MAX],int row,int val)
{
        int index;
        for(index = 0;index < MAX;index++)
        {
                if(sudoku[row][index] == val)
                {
                        return 0;
                }

        }
        return 1;
}

int gridCheck(int sudoku[MAX][MAX],int row,int col,int val)
{
	int i,j;
	for(i = 0;i < 3;i++)	{
		for(j = 0;j < 3;j++)
		{
			if(sudoku[i+row][j+col] == val)
			{
				return 0;
			}
		}
	}
	return 1;
}

int check(int sudoku[MAX][MAX],int row,int col,int val)
{
	if((columnCheck(sudoku,col,val) == 1) && (rowCheck(sudoku,row,val) == 1) && (gridCheck(sudoku,(row-(row%3)),(col-(col%3)),val) == 1))
	{
		return 1;
	}
	return 0;
}

int findEmpty(int sudoku[9][9],int* row,int* col)
{
	int i = *row, j = *col;
	for(i = 0;i < MAX;i++)
	{
		for(j = 0;j < MAX;j++)
		{
			if(sudoku[i][j] == ZERO)
			{
				*row = i;
				*col = j;
				return 0;
			}
		}
	}
	return 1;
}

int solve(int sudoku[MAX][MAX])
{
	solvecount++;
	printf("\nSolve:%d\n",solvecount);
	int i,j,value;
	char flag = 0,flag1=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(sudoku[i][j] == 0)
			{
				flag = 1;
				value = singlePossibility(sudoku,i,j);
				if(value != 0)
				{
					flag1 = 1;
printf("\nROW:%d COL:%d VAL:%d\n",(i+1),(j+1),value);
					sudoku[i][j] = value;
printSudoku(sudoku);
					if(solve(sudoku) == 1)
					{
						solvecount--;
						printf("\nSolve:%d\n",solvecount);
						return 1;
					}
				}
			}
		}
	}
	if(flag == 0)
	{
		solvecount--;
		printf("\nflag 0 Solve:%d\n",solvecount);
		return 1;
	}
	else if(flag == 1 && flag1 == 0)
	{
		solvecount--;
		printf("\nflag 1 & 0 Solve:%d\n",solvecount);
		if(solve1(sudoku) == 2)
		{
			return 2;
		}
	}
}

int solve1(int sudoku[MAX][MAX])
{
	solve1count++;
	printf("\nSolve1:%d\n",solve1count);
	int n = 1,i,j,value;
	while(n <= 9)
	{
		for(i=0;i<9;i++)
		{
	                for(j=0;j<9;j++)
			{
				if(sudoku[i][j] == 0)
				{
					if(noOfPossibility(sudoku,i,j) == n)
					{
						for(value=1;value<=9;value++)
						{
							if(check(sudoku,i,j,value) == 1)
							{
								sudoku[i][j] = value;
printf("\nRow:%d Col:%d Val:%d n:%d\n",(i+1),(j+1),value,n);
printSudoku(sudoku);
								if(solve(sudoku) == 1)
								{
									solve1count--;
									printf("\nSolve1:%d",solve1count);
									return 1;
								}
														
								sudoku[i][j] = 0;
printf("\nRow:%d Col:%d Val:%d n:%d\n",(i+1),(j+1),0,n);
printSudoku(sudoku);
	

							}
						}
						return 0;
					}
				}
			}
		}
		n++;
	}
	printf("Error!!");
	solve1count--;
	printf("\nSolve1:%d\n",solve1count);
	return 0;
}

int singlePossibility(int sudoku[MAX][MAX],int row,int col)
{
	int i,count = 0,value;
	for(i = 1;i <= MAX;i++)
	{
		if(check(sudoku,row,col,i) == 1)
		{
			count++;
			value = i;
		}
	}
	if(count == 1)
	{
		return value;
	}
	else return 0;
}

int noOfPossibility(int sudoku[MAX][MAX],int row,int col)
{
        int i,count = 0;
        for(i = 1;i <= MAX;i++)
        {
                if(check(sudoku,row,col,i) == 1)
                {
                        count++;
                }
        }
	return count;

}

#ifdef COMMENT
int solveSudoku(int sudoku[MAX][MAX])
{
	int row,col,val;
	if(findEmpty(sudoku,&row,&col) == 1)
	{
		return 1;
	}
	for(val = 1;val <= MAX;val++)
	{
		if(check(sudoku,row,col,val) == 1)
		{
			sudoku[row][col] = val;
			if(solveSudoku(sudoku) == 1)
			{
				return 1;
			}

			sudoku[row][col] = ZERO;
		}
	}
	return 0;

}

#endif
