#include <stdio.h>

void sortIterative(int *data, int size);
void swap(int *a, int *b);
void sortOuter(int *data, int size, int i);
void sortInner(int *data, int *fixed, int i, int size);
void print(int *data, int size);
//TODO compare function to determine asc/desc order

int main()
{
	int data[] = {10, 9, 8, 7, 4, 5, 6, 3, 2, 1};
	int i, j;
	int size = 10;

	print(data, size);
	//sortIterative(data, size);
	//combined(data, size);

	sortOuter(data, size, 0);
	
	// print the array
	print(data, size);
	
	//exit
	return 0;
}

// outer cycle is recursi
void sortOuter(int *data, int size, int i)
{
	if(i < size - 1)
	{
		sortInner(data, &data[i], i, size);
		sortOuter(data, size, i + 1);
	}
}

// inner cycle is recursive
void sortInner(int *data, int *fixed, int i, int size)
{
	if( *fixed > data[i])
	{
		swap(fixed, &data[i]);
	}
	i += 1;
	if(i < size)
	{
		sortInner(data, fixed, i, size);
	}
}

/**
 *	sort done combined with recursion
 *	outer cycle done iteratively,
 *	inner cycle done recursively
 */
void combined(int *data, int size)
{
	int i;
	for(i = 0; i < size-1; i++)
	{
		sortInner(data, &data[i], i, size);
	}
}

// sort done iterratively
void sortIterative(int *data, int size)
{
	int i, j;
	for(i = 0; i < (size - 1); i++)
	{
		for(j = i + 1; j < size; j++)
		{
			if(data[j] < data[i])
			{
				swap(&data[i], &data[j]);
			}
		}
	}
}
// print the array
void print(int *data, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		printf("%2d ", data[i]);
	}
	printf("\n");
}

// simple swap function
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
