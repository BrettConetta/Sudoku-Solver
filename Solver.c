#include <stdlib.h>
#include <stdio.h>
int checkHoriz(int ** mat, int i, int num);
int checkVert(int ** mat, int j, int num);
int checkSubGrid(int ** mat, int i, int j, int num);

int len = 9;//Global Var. Dims of sudoku grid

int checkSubGrid(int ** mat, int m, int n, int num)
{
	int count = 0;
	int i, j;
	
	for(i = m/3*3; i < m/3*3 + 3; i++)
	{
		for(j = n/3*3; j < n/3*3 + 3; j++)
		{
			if(mat[i][j] == num)
			{
				count++;
			}
		}
	}
	
	if(count > 1)
	{
		return -1;
	}
	else if(count == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int checkVert(int ** mat, int j, int num)
{
	int count = 0;
	int i;
	
	for(i = 0; i < len; i++)
	{
		if(mat[i][j] == num)
		{
			count++;
		}
	}
	
	if(count > 1)
	{
		return -1;
	} 
	else if(count == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int checkHoriz(int ** mat, int i, int num)
{
	int count = 0;
	int j;
	for(j = 0; j < len; j++)
	{
		if(mat[i][j] == num)
		{
			count++;
		}
	}
	
	if(count > 1)
	{
		return -1;
	} 
	else if(count == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main(int argc, char ** argv)
{
	int ** mat;
	int i, j, m, n, num, holder;
	int temp = 0;
	int count = 0;
	int zeroCounter = 0;
	
	
	mat = (int**)malloc(sizeof(int*) * len);
	for(i = 0; i < len; i++)
	{
		mat[i] = (int*)malloc(sizeof(int) * len);
	}
	
	if(argc<2)
 	{
    		printf("Not enough arguments\n");
  		return 0;
  	}
	FILE *fp;

  	fp = fopen(argv[1], "r");

	if(fp == NULL) 
		return 0;
	
	for(i = 0; i < len; i++)//these two loops fill  mat with the values given in the file
	{
		for(j = 0; j < len; j++)
		{
			fscanf(fp, "%d ", &temp);
			mat[i][j] = temp;
			temp = 0;
		}
		
	}
	
	for(i = 0; i < len; i++)
	{
		for(j = 0; j < len; j++)
		{
			if(mat[i][j] != 0)
			{
				num = mat[i][j];
				if(checkHoriz(mat, i, num) == 0)
				{
					if(checkVert(mat, j, num) == 0)
					{
						if(checkSubGrid(mat, i, j, num) == 0)
						{
							
						}
						else
						{
							printf("no-solution\n");
							return 0;
						}
					}
					else
					{
						printf("no-solution\n");
						return 0;
					}
				}
				else
				{
					printf("no-solution\n");
					return 0;
				}
			}
		}
	}
	
	
	
	for(m = 0; m < len; m++)//these two loops count all the 0's in the sudoku grid.
	{
		for(n = 0; n < len; n++)//used so the loop knows when to stop.
		{
			if(mat[m][n] == 0)
			{
				zeroCounter++;
			}
		}
	}
	
	
	while(zeroCounter != 0)
	{
		for(i = 0; i < len; i++)
		{
			for(j = 0; j < len; j++)
			{
				if(mat[i][j] == 0)
				{
					for(num = 1; num <= len; num++)
					{
						if(checkHoriz(mat, i, num) == 1)
						{
							if(checkVert(mat, j, num) == 1)
							{
								if(checkSubGrid(mat, i, j, num) == 1)
								{
									holder = num;
									count++;
								}
							}
						}
					}
				}
				if(count == 1)
				{
					mat[i][j] = holder;
				}
				count = 0;
			}
		}
		
		zeroCounter = 0;
		for(m = 0; m < len; m++)
		{
			for(n = 0; n < len; n++)
			{
				if(mat[m][n] == 0)
				{
					zeroCounter++;
				}
			}
		}
	}
	
	for(i = 0; i < len; i++)//these two loops print  mat with the values given in the file
	{
		for(j = 0; j < len; j++)
		{
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}
	return 0;
}
