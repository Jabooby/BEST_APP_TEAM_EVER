#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
	int i1, i2, i3, i4, i5;
	FILE *fp;
	
	if ( (fp = fopen("inputTEST.txt", "r")) == NULL)
	{
		fprintf(stderr, "Error opening file. \n");
		exit(1);
	}
	fscanf(fp, "%i %i %i %i %i", &i1, &i2, &i3, &i4, &i5);
	printf("The values are: %i, %i, %i, %i and %i. \n", i1, i2, i3, i4, i5);

	fclose(fp);
	return(0);
}
