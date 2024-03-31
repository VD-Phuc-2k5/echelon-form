#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float** initialize(int rows, int cols);
void freeMemory(float** matrix, int rows);
float random_number(int min, int max);
void createMatrix(float** matrix, int rows, int cols);
void printtMatrix(float** matrix, int rows, int cols);
//handle
void swap(float &a, float &b);
void swap_row(float** matrix, int row1, int row2, int cols);
void eliminate(float** matrix, int base, int row, int cols);
void convert_to_echelon_form(float** matrix, int rows, int cols);

void main()
{
	srand((int)time(0));
	int rows, cols;
    	printf("Rows, Cols: ");
   	 scanf_s("%d %d", &rows, &cols);
	float **matrix = initialize(rows, cols);
	createMatrix(matrix, rows, cols);
	printtMatrix(matrix, rows, cols);
	printf("\n");
	clock_t begin = clock();
	convert_to_echelon_form(matrix, rows, cols);
	clock_t end = clock();
	printtMatrix(matrix, rows, cols);
	freeMemory(matrix, rows);
	printf("Time run: %gs\n", (float)(end-begin)/CLOCKS_PER_SEC);
	system("pause>0");
}

float** initialize(int rows, int cols)
{
	float **matrix = new float *[rows];
	for (int i = 0; i < rows; ++i)
		matrix[i] = new float[cols]();
	return matrix;
}
void freeMemory(float** matrix, int rows)
{
	for (int i = 0; i < rows; ++i)
		delete[] matrix[i];
	delete matrix;
	matrix = NULL;
}
float random_number(int min, int max)
{
	return min + rand() % (max - min + 1);
}
void createMatrix(float** matrix, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			matrix[i][j] = random_number(-9, 9);
	}
}
void printtMatrix(float** matrix, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			printf("%6.2f\t", matrix[i][j]);
		printf("\n");
	}
}
void swap(float &a, float &b)
{
	float temp = a;
	a = b;
	b = temp;
}
void swap_row(float** matrix, int row1, int row2, int cols)
{
	for (int i = 0; i < cols; i++)
		swap(matrix[row1][i], matrix[row2][i]);
}
void eliminate(float** matrix, int base, int rows,  int cols)
{
	float c;
	for (int i = base + 1; i < rows;  i++)
	{
		c = matrix[i][base] / matrix[base][base];
		for (int j = 0; j < cols; ++j)
			matrix[i][j] -= c*matrix[base][j];
	}
}
void convert_to_echelon_form(float** matrix, int rows, int cols)
{
	for (int i = 0; i < rows - 1; i++)
	{
		int j = i;
		if (matrix[j][i] != 0)
			eliminate(matrix, i, rows, cols);
		else
		{
			while(matrix[j][i] == 0 && j < rows - 1)
				++j;
			if (j < rows - 1) 
			{
				swap_row(matrix, i, j, cols);
				eliminate(matrix, i, rows, cols);
			}
		}
	}
}


