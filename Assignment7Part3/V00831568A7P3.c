/*
*  Course:      CSC 111
*  Author:      Michael Reiter and Hausi Muller
*  UVicId:      V00831568
*  Assignment:  A7P3
*  Date:        13/11/14
*  Description: Reading, writing, and encoding files
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define INPUTFILENAME    ("A7_2014_P3_Sherlock.txt")
#define OUTPUTFILENAME   ("A7_2014_P3_SherlockEncoded.txt")

void processFile(FILE* ifp, FILE* ofp) {
	printf("Begin process file\n");

	char temp;
	char str[100];
	int k = 0;
	while (fscanf(ifp, "%s", str) != EOF){
		if (strlen(str) >= 4){
			temp = str[1];
			str[1] = str[2];
			str[2] = temp;
		}
		k++;
		if (k % 10 == 0){
			fprintf(ofp, "\n");
		}
		fprintf(ofp, "%s ", str);
	}

	printf("End process file\n");
} /* ProcessFile */

int main(void) {
	printf("Welcome to Sherlock Holmes\n\n");
	unsigned int seed = (unsigned int)time(NULL);
	srand(seed);
	FILE *ifp;
	FILE *ofp;
	ifp = fopen(INPUTFILENAME, "r");
	if (ifp == NULL) {
		printf("Cannot open input file %s\n", INPUTFILENAME);
		exit(EXIT_FAILURE);
	} /*if*/
	ofp = fopen(OUTPUTFILENAME, "w");
	if (ofp == NULL) {
		printf("Cannot create output file %s\n", OUTPUTFILENAME);
		exit(EXIT_FAILURE);
	} /*if*/
	processFile(ifp, ofp);
	fclose(ofp);
	fclose(ifp);
	printf("\nWe encoded Sherlock Holmes\n");
	return EXIT_SUCCESS;
} /*main*/
