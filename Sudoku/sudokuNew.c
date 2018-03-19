#include<stdio.h>
#define MAX 9
#define ZERO 0
void printSudoku(int sudoku[MAX][MAX]);                       //Prints the sudoku
int checkEntries(int row,int col,int value);                  // Checks if entered integers are between 0 and 9
int columnCheck(int sudoku[MAX][MAX],int col,int val);       //checks if val is present in any of the col entries
int rowCheck(int sudoku[MAX][MAX],int row,int val);          //checks if val is present in any of the row entries
int gridCheck(int sudoku[MAX][MAX],int row,int col,int val);//checks if val is pres in the 3x3 grid
int check(int sudoku[MAX][MAX],int row,int col,int val);    //checks if all the checks are true
int solveSingle(int sudoku[MAX][MAX],int a);                //Fills in each single possible solution in a cell
int solve(int sudoku[MAX][MAX]);                           //Fills if more than one solution to a cell
int noOfPossibility(int sudoku[MAX][MAX],int row,int col);  //Gives the number of posible solutions
int singlePossibility(int sudoku[MAX][MAX],int row,int col);//Gives the value of a single possible solution to a cell
int isEmpty(int sudoku[9][9]);

int main()
{
	int sudoku[MAX][MAX] = {ZERO};
	int row,col,i,j,n,value;
	printf("Enter the data:\n");
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
	if(solveSingle(sudoku,0) == 1)
	{
		printf("SOLUTION\n");
		printSudoku(sudoku);
	}
	else
	{
		printf("\nSolution cannot be determined\n");
	}
	//printSudoku(sudoku);

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
	else
	{
		return 0;
	}
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
int isEmpty(int sudoku[MAX][MAX])
{
	int i,j;
	for(i = 0;i < MAX;i++)
	{
		for(j = 0;j < MAX;j++)
		{
			if(sudoku[i][j] == ZERO)
			{
				return 1;
			}
		}
	}
	return 0;
}

int solveSingle(int sudoku[MAX][MAX],int a)
{
	int i,j,value;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(sudoku[i][j] == ZERO)
			{
				value = singlePossibility(sudoku,i,j);
				if(value != 0)
				{
				//printf("\nROW:%d COL:%d VAL:%d\n",(i+1),(j+1),value);
					sudoku[i][j] = value;
					//printSudoku(sudoku);
					if(solveSingle(sudoku,a) == 1)
					{
						return 1;
					}
					if(a == 1)
					{
						sudoku[i][j] = ZERO;
						return 0;
					}
				}
			}
		}
	}
	if(isEmpty(sudoku))
	{
		return solve(sudoku);
	}
	else
	{ 
		return 1;
	}
}

int solve(int sudoku[MAX][MAX])
{
	int n = 2,i,j,value;
	while(n <= 9)
	{
		for(i=0;i<MAX;i++)
		{
			for(j=0;j<MAX;j++)
			{
				if(sudoku[i][j] == ZERO)
				{
					if(noOfPossibility(sudoku,i,j) == n)
					{
						for(value=1;value<=MAX;value++)
						{
							if(check(sudoku,i,j,value) == 1)
							{
							//printf("\nROW:%d COL:%d VAL:%d\n",(i+1),(j+1),value);
								sudoku[i][j] = value;
								//printSudoku(sudoku);
								if(solveSingle(sudoku,1) == 1)
								{
									return 1;
								}
							//printf("\nROW:%d COL:%d VAL:%d\n",(i+1),(j+1),0);	
								sudoku[i][j] = ZERO;
								//printSudoku(sudoku);
							}
						}
						return 0;
					}
				}
			}
		}
		n++;
	}
	if(isEmpty(sudoku))
	{
		return 0;
	}
	else
	{
		return 1;
	}	


}
