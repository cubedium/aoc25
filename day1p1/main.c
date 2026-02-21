#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if (argc <= 1) 
	{
		printf("Not enough arguments (current amount is %d)\n", argc);
		return 0;
	}
	
	int currentPoint = 50;
	int currentDirection = 0; // -1 = left, 1 = right, 0 = none
	int currentOffset = 0;
	int zeroCount = 0;
	int c;

	FILE* file;
	if ((file = fopen(argv[1], "r")) == NULL)
	{
		return 0;
	}

	while ((c = fgetc(file)) != EOF)
	{
		if (currentDirection != 0)
		{
			if (isdigit(c))
			{
				currentOffset = currentOffset * 10 + c-'0';
				printf("%c: %d\n", c, currentOffset);
			}
			else if (c == '\n')
			{
				currentPoint += currentOffset * currentDirection;
				currentDirection = 0;
				currentOffset = 0;

				while (currentPoint<0||currentPoint>99)
				{
					if (currentPoint<0)
					{
						printf("<before: %d\n", currentPoint);
						currentPoint += 100;
						printf("<after: %d\n", currentPoint);
					}
					else if (currentPoint>99)
					{
						printf(">before: %d\n", currentPoint);
						currentPoint -= 100;
						printf(">after: %d\n", currentPoint);
					}
				}
				if (currentPoint == 0)
				{
					printf("zero\n");
					zeroCount += 1;
				}
			}
		}
		else
		{
			switch (c)
			{
				case 'L': currentDirection = -1; break; 
				case 'R': currentDirection =  1; break;
				default : break;
			}
		}
	}
	fclose(file);

	printf("zero count: %d\n", zeroCount);
}
