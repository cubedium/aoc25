#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

int main(int argc, char* argv[])
{
	if (argc <= 1) 
	{
		printf("Not enough arguments (current amount is %d)\n", argc);
		return 0;
	}

	FILE* file;
	if ((file = fopen(argv[1], "r")) == NULL)
	{
		return 0;
	}

	int landedZeroCount = 0;
	int passedZeroCount = 0;
	int totalZeroCount  = 0;

	int pointed   = 50; // the current digit that the pointer is pointed at in the dial, can be 0-99
	int offset    =  0; // amount of spaces the dial is being rotated
	int direction =  0; // direction of which the dial is being rotated, -1 is left and 1 is right

	int passedZero    = 0; // for when it does a double add zero
	int startedAtZero = 0; // for when it counts going backwards from 0 as passing zero

	int c;
	while ((c = fgetc(file)) != EOF)
	{
		switch (c)
		{
			case 'L': direction = -1; break; // going
			case 'R': direction =  1; break; // going right, 
			default: // either a \n or a number, if it isnt any of those it will not be used
				if (isdigit(c)) // a number, update the offset
				{
					offset = offset * 10 + c-'0';
				}
				else if (c == '\n') // a \n, figure out the new pointed number and fix the pointed number if it does not fit on the dial
				{
					// update new pointed number
					pointed += offset * direction;

					if (DEBUG)
						printf("%c%d: \n", (direction<0 ? 'L' : 'R' ), offset);

					while (pointed<0||pointed>99)
					{
						if (DEBUG)
							printf("  passed zero at %d ", (pointed-(offset*direction)));

						if (pointed<0)
							pointed += 100;

						if (pointed>99)
							pointed -= 100;

						if (DEBUG)
							printf("and landed at %d\n", pointed);

						if (!startedAtZero)
						{
							passedZeroCount += 1;
							totalZeroCount  += 1;
							passedZero = 1;
						}
						else
						{
								if (DEBUG)
									printf("  startedAtZero, so not counting\n");
								startedAtZero = 0;
						}
					}

					if (pointed == 0)
					{
						if (DEBUG)
							printf("  landed on zero%s\n", (passedZero ? " but since zero has been passed, it will not be counted to total" : ""));
						
						if (!passedZero)
							totalZeroCount += 1;
						
						landedZeroCount += 1;
						startedAtZero = 1;
					}

					offset 		 = 0;
					direction  = 0;
					passedZero = 0;
				}
				break;
		}
	}
	fclose(file);

	printf("zero count:\n  landed: %d\n  passed: %d\n  total: %d\n", landedZeroCount, passedZeroCount, totalZeroCount);
}
