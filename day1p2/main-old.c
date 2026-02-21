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

				// lets say its at 50 and it turned left by 68 spaces, making it go to -18 but its supposed to go to 82 
				if (currentDirection == -1 && currentPoint < 0)
				{
					currentPoint += 100;
					zeroCount += 1;
					printf("Left zero from %d with offset %d, current count: %d\n", (currentPoint - (currentOffset*currentDirection)), currentOffset, zeroCount);
				}
				// lets say its at 95 and it turned right by 60 spaces, making it go to 155 but its suppsoed to go to 55
				if (currentDirection == 1 && currentPoint > 100)
				{
					currentPoint -= 100;
					zeroCount += 1;
					printf("Right zero from %d with offset %d, current count: %d\n", (currentPoint - (currentOffset*currentDirection)), currentOffset, zeroCount);
				}

				currentOffset = 0;
				currentDirection = 0;

				if (currentPoint == 0)
				{
					zeroCount += 1;
					printf("Landed on zero, current count: %d\n", zeroCount);
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
