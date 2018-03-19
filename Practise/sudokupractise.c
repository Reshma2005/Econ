solve(sudoku)
{
	int i,j;
	char flag = 0,flag1=0;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(a[i][j] == 0)
			{
				flag = 1;
				value = singlePossibility(sudoku,i,j);
				if(value != 0)
				{
					flag1 = 1;
					a[i][j] = value;
					return solve(sudoku);
				}
			}
		}
	}
	if(flag == 0)
	{
		return true;
	}
	if(flag == 1 && flag1 = 0)
	{
		return solve1(sudoku);
	}
	
}

int solve1(sudoku)
{
	int n = 2,i,j,value;
	while(n <= 9)
	{
		for(i=0;i<9;i++)
		{
	                for(j=0;j<9;j++)
			{
				if(a[i][j] == 0)
				{
					if(noOfpossibility == n)
					{
						for(value=1;value<=9;value++)
						{
							if(check(sudoku,i,j,value) == 1)
							{
								a[i][j] = 1;
								if(solve(sudoku) == 1)
								{
									return 1;
								}
								else
								{
									a[i][j] = 0;
								}

							}
						}
					}
				}
			}
		}
		n++;
	}
	return 0;
}

int singlePossibility(int sudoku[MAX][MAX},int row,int col)
{
	int i,count = 0,value;
	for(i = 1;i <= MAX;i++)
	{
		if(check(sudoku,row,col) == 1)
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
                if(check(sudoku,row,col) == 1)
                {
                        count++;
                }
        }
	return count;

}
