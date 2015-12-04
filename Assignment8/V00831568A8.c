/*
*  Course:      CSC 111
*  Author:      Michael Reiter, B. Bird and A. Bergen
*  UVicId:      V00831568
*  Assignment:  A8
*  Date:        27/11/14
*  Description: 13 exercises to do various tasks. Used to practice programming.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define PASCAL_MAX 100
#define MATRIX_MAX 100
#define DIFF_EPSILON (1e-14)
#define MAX_LINE 4096
#define NOT_FOUND (-1)


/* ========================================================================= */
/*                              Type Definitions                             */
/*          Do not alter the provided definitions (they will be used         */
/*            for marking). You may add new definitions as needed.           */
/* ========================================================================= */


typedef int Matrix[MATRIX_MAX][MATRIX_MAX];

/* Point -- A struct to represent a point (x,y) in the plane */
typedef struct {
	float x, y;
} Point;

/* PointListNode -- A node of a singly-linked list of points */
typedef struct PointListNode{
	Point *p;
	struct PointListNode *next;
} PointListNode;

/* ========================================================================= */
/*                                 Functions                                 */
/*        Do not change the name, return type or parameter types of          */
/*            the functions below or they will not be marked.                */
/*                  You may add new functions as needed.                     */
/* ========================================================================= */

/* ==================================================
   Task 1 - Text Parsing Exercise (easy)
   Roman Numeral to Integer converter
   Parameters:
     s - A null-terminated string containing Roman Numerals.
         No subtractive notation is used, so '9' is represented as 'VIIII'.
         The only characters in s will be 'M','D','C','L','X','V' and 'I'
   Return Value:
     The positive integer value corresponding to the roman numeral
	 representation. Note that if the input string is empty (i.e. ""), the
	 return value should be zero.
   ==================================================
*/

int romanToInt(char *s){
	int n = 0;
	int length = strlen(s);
	int k;
	for (k = 0; k < length; k++){
		switch (s[k]){
			case 'I':
				n += 1;
				break;
			case 'V':
				n += 5;
				break;
			case 'X':
				n += 10;
				break;
			case 'L':
				n += 50;
				break;
			case 'C':
				n += 100;
				break;
			case 'D':
				n += 500;
				break;
			case 'M':
				n += 1000;
				break;
		}
	}
	return n;
} /* romanToInt */

/* ==================================================
   Task 2 - String Manipulation Exercise (easy)
   Invert the capitalization of a string
   Parameters:
    s - A null-terminated character string.
   Return Value:
    None.
   Result:
    The function should convert every lowercase character in the string s to
	uppercase, and every uppercase character to lowercase (and store the
	modified character back into s). Characters which are not uppercase
	or lowercase letters must be left as-is. For example, if the input string
	is "Csc111", this function would convert it to "cSC111". The standard
	library functions 'islower', 'isupper', 'tolower' and 'toupper' may be
	helpful for this.
   ==================================================
*/

void invertCase(char *s){
	int k;
	int stringLength = strlen(s);
	for (k = 0; k < stringLength; k++){
		if (isupper(s[k])){
			s[k] = tolower(s[k]);
		} else if (islower(s[k])){
			s[k] = toupper(s[k]);
		}
	}
} /* invertCase */

/* ==================================================
   Task 3 - Fibonacci excercise (easy)
   Find the largest Fibonacci number below a given limit.
   The Fibonacci sequence is 1, 1, 2, 3, 5, 8, 13, ...
   The first two values are 1, and each subsequent value is the sum of the
   previous two values. This function should return the largest element in the
   sequence smaller than a provided limit.

   For example, maxFibonacci(10) would return 8.

   Parameters:
    upper_limit - The upper limit
   Return Value:
    The largest Fibonacci number less than or equal to upper_limit.
   ==================================================
*/

int maxFibbonacci(int max) {
	int first = 1;
	int second = 1;
	int next = 0;
	while ((first + second) <= max){
		next = first + second;
		first = second;
		second = next;
	}
	return next;
} /* maxFibonacci */

/* ==================================================
   Task 4 - 1-dimensional Array Exercise (easy)
   Linear Search
   Parameters:
     A - An array of integers
     n - The length of A
     k - An integer to search for in A
   Return Value:
     If k is an element of A, the return value should be an integer i such that
	 A[i] == k. If k is not an element of A, the return value should be the
	 constant NOT_FOUND (which is defined at the top of this file to be -1).
   ==================================================
*/

int linearSearch(int A[], int n, int k){
	int i;
	for (i = 0; i < n; i++){
		if (A[i] == k){
			return i;
		}
	}
	return NOT_FOUND;
} /* linearSearch */

/* ==================================================
   Task 5 - 2-dimensional Array Exercise I (intermediate)
   Pascal's Triangle
   Parameters:
     A - A 2d array of integers
     n - The number of rows to compute
   Return Value:
     None
   Result:
     When the function completes, the first n rows of A must contain the
     first n rows of Pascal's triangle.
     The first 5 rows of Pascal's triangle are
     1
     1 1
     1 2 1
     1 3 3 1
     1 4 6 4 1

     In general, row k has k + 1 entries, and the first and last entry of each
	 row is 1. Every other entry is the sum of the element above, and the
	 element above and to the left.
	 As the above example shows, row 0 should be "1", row 1 is "1 1", row 2 is
	 "1 2 1", etc.

     No more than n rows should be computed. The input array will be guaranteed
     to be large enough to hold all of the values.
   ==================================================
*/

int factorial(int n){
	if (n == 1 || n == 0){
		return 1;
	} else {
		return factorial(n-1)*n;
	}
}

void pascalsTriangle(int A[PASCAL_MAX][PASCAL_MAX], int n){
	int j, k;
	for (j = 0; j < n; j++){
		for (k = 0; k <= j; k++){
			A[j][k] = factorial(j)/(factorial(k)*factorial(j-k));
		}
	}
} /* pascalsTriangle */

/* ==================================================
   Task 6 - 2-dimensional Array Exercise II (hard)
   Shift a matrix one column to the left.
   Parameters:
    M - A Matrix
    rows - The number of rows in M
    cols - The number of columns in M
   Return Value:
     None
   Result:
     When the function completes, the columns of M will have been shifted
     by one column to the left. For example, if M is a 4 x 3 matrix with
     initial value
        0  1  2  3
       10 11 12 13
       14 15 16 17
     then the value of M after the function completes should be
        1  2  3  0
       11 12 13 10
       15 16 17 14

   ==================================================
*/

void shiftColumnsLeft(Matrix M, int rows, int cols) {
	int j, k, temp;
	for (j = 0; j < rows; j++){
		temp = M[j][0];
		for (k = 0; k < cols; k++){
			M[j][k-1] = M[j][k];
		}
		M[j][cols-1] = temp;
	}
} /* shiftColumnsLeft */

/* ==================================================
   Task 7 - String Exercise I (easy)
   Compute the length of the provided string.

   Parameters:
    inputString - A string
   Return Value:
    The length of inputString. In this context, the length of a string is the
	number of characters before the null terminator. For example, the length
	of the string "CSC111" is 6.

    The strlen() function (and its derivatives) may not be used in this
	function.
   ==================================================
*/

int stringLength(char inputString[]) {
	int k;
	for (k = 0; inputString[k] != '\0'; k++){}
	return k;
}

/* ==================================================
   Task 8 - String Exercise II (easy)
   Copy a suffix of inputString to outputString.

   Parameters:
    inputString - The input string
    outputString - An array to store the output string
    start_position - The first index of the inputString to copy
   Return Value:
    None
   Result:
    Every character of inputString from the index start_position to the end
    of the string is copied to the string outputString.

	For example, if inputString is "Hello World" and start_position is 4,
	outputString will be set to the string "o World".
   ==================================================
*/

void copySuffix(char inputString[], char outputString[], int start_position){
	int k;
	for (k = 0; inputString[k] != '\0'; k++){
		outputString[k] = inputString[k + start_position];
	}
}

/* ==================================================
   Task 9 - String Exercise III (intermediate)
   "Mirror" a string by concatenating it with a reversed copy of itself.
   For example, the string "Hello" would become "HelloolleH" and the string
   "Assignment 8" would become "Assignment 88 tnemngissA"

   Parameters:
    str - The string to mirror
   Return Value:
    None
   Result:
    A reversed copy of the string str will be appended to the end of str.
    You may assume that there is enough space available in str to permit this.
   ==================================================
*/

void mirrorString(char string[]) {
	int k;
	char newString[MAX_LINE];
	int stringLength = strlen(string);
	int i = 0;
	for (k = stringLength - 1 ; k >= 0; k--){
		newString[i] = string[k];
		i++;
	}
	strcat(string, newString);
}

/* ==================================================
   Task 10 - String Exercise IV (hard)
   Decrypt a coded message.

   A 'Caesar cipher' is a simple (and very easy to break) encryption method
   where each letter is shifted by one (so 'a' becomes 'b', 'b' becomes 'c'
   and so on, with 'z' becoming 'a'). This function will take a coded
   message and decrypt it to reveal the original message. Every character
   in the message will be a lowercase letter.

   For example, the string 'fohjoffsjoh' would be decrypted to 'engineering'.

   Hint: A char variable c which contains a lowercase letter can be converted
   into a number between 0 and 25 with the expression (c - 'a') and a number
   j between 0 and 25 can be converted to a lowercase letter with the
   expression (j + 'a').

   Parameters:
    codedMessage - A string containing the encrypted message.
    decodedMessage - An array to store the decoded message
   Return Value:
    None
   Result:
    The array decodedMessage will be set to a string containing the decoded
    message.
   ==================================================
*/

void decrypt(char codedMessage[], char decodedMessage[]) {
	int k;
	char letter;
	int messageLength = strlen(codedMessage);
	for (k = 0; k < messageLength; k++){
		letter = codedMessage[k];
		if (letter == 'a'){
			letter = 'z' + 1;
		}
		decodedMessage[k] = ((letter - 'a' - 1) + 'a');
	}
}

/* ==================================================
   Task 11 - Struct Exercise (very easy)
   Distance between points in the plane.
   Parameters:
    p1, p2 - Pointers to Point structs (see definition above)
   Return Value:
    The distance between the points described by p1 and p2.
    Note that the distance between points (x1,y1) and (x2,y2) is the
    length of the vector (x1-x2,y1-y2)
   ==================================================
*/

float distBetweenPoints(Point *p1, Point *p2){
	float dist = 0.0;
	int x = (p1->x) - (p2->x);
	int y = (p1->y) - (p2->y);
	dist = sqrt(((x*x) + (y*y)));
	return dist;
} /* distBetweenPoints */

/* ==================================================
   Task 12 - Linked List Exercise I (intermediate)
   Count nearby points.
   Parameters:
    pointList - Pointer to the head of a singly-linked list of points (see
                definition above).
    centrePoint - Pointer to a point struct.
    radius - A positive real value.
   Return Value:
    The number of points in pList whose distance from centrePoint is less than
	or equal to the radius provided.
    To obtain the distance, the distBetweenPoints function from Task 11 can be
	used. The end of the linked list is indicated by the 'next' pointer being
	NULL.
   ==================================================
*/

int countNearbyPoints(PointListNode *pointList, Point* centrePoint, float radius){
	int count = 0;
	while (pointList != NULL){
		if (distBetweenPoints(pointList->p, centrePoint) <= radius){
			count++;
		}
		pointList = pointList->next;
	}
	return count;
} /* countNearbyPoints */

/* ==================================================
   Task 13 - Linked List Exercise II (hard)
   Add a point to the end of a linked list of points.
   Parameters:
    pointList - Pointer to the head of a singly-linked list of points (see
                definition above). The list will contain at least one
				node.
    newPoint - Pointer to a Point struct to add to the end of the list.

   Result:
    A new PointListNode referring to newPoint will be placed at the end
    of the provided linked list. Note that the PointListNode must be allocated
    with malloc().
   ==================================================
*/

void addPointAtEnd(PointListNode *pointList, Point* newPoint){
	PointListNode *var = (PointListNode*)malloc(sizeof(PointListNode));
	while (pointList->next != NULL){
		pointList = pointList->next;
	}
	pointList->next = var;
	var->p = newPoint;
	var->next = NULL;
} /* addPointAtEnd */

/* ========================================================================= */
/*                              Testing Code                                 */
/*        None of the functions in this section will be marked, but          */
/*     they may be useful for testing (you may modify them if you wish)      */
/* ========================================================================= */

/* allocateNewPoint - Allocate memory for a new point, set it to the values provided and return a pointer */
Point *allocateNewPoint(float x,float y){
	Point *p = malloc(sizeof(*p));
	p->x = x;
	p->y = y;
	return p;
} /* allocateNewPoint */

/* addPointToList - Add a new node to the front of a singly linked list, referencing the given point */
PointListNode *addPointToList(PointListNode *list, Point* newPoint){
	PointListNode *newNode = malloc(sizeof(*newNode));
	newNode->next = list;
	newNode->p = newPoint;
	return newNode;
} /* addPointToList */

/* freePointList - Recursively delete a linked list of points */
void freePointList(PointListNode *list){
	if (!list)
		return;
	freePointList(list->next);
	free(list->p);
	free(list);
} /* freePointList */

/* printPointList - Recursively print a linked list of points in reverse order */
void printPointList(PointListNode* list){
	if (!list)
		return;
	printf("(%.2f,%.2f) ",list->p->x,list->p->y);
	printPointList(list->next);
} /* printPointList */

/* reversePointList - Reverse the order of a linked list of points and return the new head */
PointListNode* reversePointList(PointListNode *list){
	if (!list || !list->next)
		return list;
	PointListNode* newPrev = list->next;
	PointListNode* newHead = reversePointList(newPrev);
	newPrev->next = list;
	list->next = NULL;
	return newHead;
} /* reversePointList */

/* firstNonWhitespaceCharacter - Return a pointer to the first non-whitespace character in the string provided */
char *firstNonWhitespaceCharacter(char *s){
	if (!s || !*s)
		return s;
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	return s;
} /* firstNonWhitespaceCharacter */

/* removeTrailingSpaces - If the string s contains spaces at the end, get rid of them (e.g. "abcd   " would become "abcd" */
void removeTrailingSpaces(char *s){
	char* lastNonSpace = s;
	while (*s){
		if (*s != ' ' && *s != '\n' && *s != '\t')
			lastNonSpace = s;
		s++;
	}
	while (lastNonSpace != s)
		*++lastNonSpace = '\0';
}

/* readNInts - Read up to n integers from the input string provided and return the number read. */
int readNInts(char* input, int out[], int n){
	int i;
	long val;
	for (i = 0; i < n; i++){
		//Advance the input pointer until we find the beginning of an integer
		//(that is, a digit or a - sign)
		while (*input && !isdigit(*input) && *input != '-')
			input++;
		if (!*input)
			break;
		/* Use strtol to read a long integer in base 10 from the current position of input,
		   and then store the location of the first character after the number it read
		   back into the input pointer (so we can move on to the next value) */
		val = strtol(input,&input,10);
		//Since val is declared as long, we have to cast it back to int
		out[i] = (int)val;
	}
	return i;
} /* readNInts */

/* readNFloats - Read up to n floats from the input string provided and return the number read. */
int readNFloats(char* input, float out[], int n){
	int i;
	float val;
	for (i = 0; i < n; i++){
		//Advance the input pointer until we find the beginning of a number
		//(that is, a digit, a decimal point or a '-' sign)
		while (*input && !isdigit(*input) && *input != '-' && *input != '.')
			input++;
		if (!*input)
			break;
		/* Use strtof to read a floating-point value from the current position of input,
		   and then store the location of the first character after the number it read
		   back into the input pointer (so we can move on to the next value) */
		val = strtof(input,&input);
		out[i] = val;
	}
	return i;
} /* readNFloats */

/* readNDoubles - Read up to n doubles from the input string provided and return the number read. */
int readNDoubles(char* input, double out[], int n){
	int i;
	double val;
	for (i = 0; i < n; i++){
		//Advance the input pointer until we find the beginning of a number
		//(that is, a digit, a decimal point or a '-' sign)
		while (*input && !isdigit(*input) && *input != '-' && *input != '.')
			input++;
		if (!*input)
			break;
		/* Use strtod to read a floating-point value from the current position of input,
		   and then store the location of the first character after the number it read
		   back into the input pointer (so we can move on to the next value) */
		val = strtod(input,&input);
		out[i] = val;
	}
	return i;
} /* readNFloats */

/* testPrompt - Prompt for some input, and if no input is provided, return NULL. Otherwise, return a
   pointer to the first non-whitespace input character. If prompt is NULL, is is assumed
   that the caller will handle all prompts/feedback */
char* testPrompt(const char* prompt, char *outBuf, int bufLength){
	if (prompt){
		printf("%s",prompt);
		fflush(stdout);
	}
	if (fgets(outBuf,bufLength,stdin)){
		outBuf = firstNonWhitespaceCharacter(outBuf);
		if (*outBuf)
			return outBuf;
	}
	if (prompt)
		printf("\t No data provided - Skipping test.\n\n");
	return NULL;
} /* testPrompt */


/* startTest - Print a banner denoting the start of a test */
void startTest(char *testName){
	printf(" ****** Testing %s ******\n",testName);
}


/* testRoman - Test the romanToInt function (Task 1)*/
void testRoman(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	startTest("romanToInt");
	if(!(inputString = testPrompt("Enter a roman numeral: ",inputBuffer,sizeof(inputBuffer))))
		return;
	removeTrailingSpaces(inputString);
	printf("Integer representation of roman numeral \"%s\" is: %d\n\n",inputString,romanToInt(inputString));
	fflush(stdout);
} /* testRoman */

/* testInvertCase - Test the invertCase function (Task 2)*/
void testInvertCase(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	startTest("invertCase");
	if(!(inputString = testPrompt("Enter a string for invertCase: ",inputBuffer,sizeof(inputBuffer))))
		return;
	removeTrailingSpaces(inputString);
	printf("Original string : \"%s\"\n",inputString);
	invertCase(inputString);
	printf("After invertCase: \"%s\"\n\n",inputString);
	fflush(stdout);
} /* testInvertCase*/

/* testMaxFibonacci - Test the maxFibonacci function (Task 3)*/
void testMaxFibonacci(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	startTest("maxFibonacci");
	if(!(inputString = testPrompt("Enter an upper limit: ",inputBuffer,sizeof(inputBuffer))))
		return;
	int max_value;
	if (readNInts(inputString,&max_value,1) != 1){
		printf("\t No value provided - skipping test.\n\n");
		return;
	}
	fflush(stdout);
	printf("Largest Fibonacci number less than or equal to %d: %d\n\n",max_value, maxFibbonacci(max_value));
} /* testMaxFibonacci */


/* testLinearSearch - Test the linearSearch function (Task 4)*/
void testLinearSearch(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	int n;
	int val;
	int numRead;
	int result;
	startTest("linearSearch");
	if(!(inputString = testPrompt("Choose an array size for linearSearch: ",inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNInts(inputString,&n,1) != 1){
		printf("\t No size provided - skipping test.\n\n");
		return;
	}
	//Now create an array big enough to store n ints
	//C99 allows this kind of declaration (which is referred to as a 'variable length array')
	int A[n];
	printf("Enter %d values for linearSearch: ",n);
	if(!(inputString = testPrompt("",inputBuffer,sizeof(inputBuffer))))
		return;
	if ((numRead = readNInts(inputString,A,n)) != n){
		printf("\t Only %d values were entered - skipping test.\n\n",numRead);
		return;
	}
	if(!(inputString = testPrompt("Enter a value to search for: ",inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNInts(inputString,&val,1) != 1){
		printf("\t No value provided - skipping test.\n\n");
		return;
	}
	result = linearSearch(A,n,val);
	if (result == NOT_FOUND)
		printf("linearSearch returns NOT_FOUND when searching for %d.\n\n",val);
	else
		printf("linearSearch returns %d when searching for %d.\n\n",result,val);
	fflush(stdout);
} /* testLinearSearch*/

/* testPascal - Test the pascalsTriangle function (Task 5)*/
void testPascal(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	int n;
	int i,j;
	int A[PASCAL_MAX][PASCAL_MAX];
	startTest("pascalsTriangle");
	if(!(inputString = testPrompt("Enter the number of rows of Pascal's triangle to generate: ",inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNInts(inputString,&n,1) != 1){
		printf("\t No value provided - skipping test.\n\n");
		return;
	}
	if (n >= PASCAL_MAX){
		printf("\t Number of rows is too large - skipping test.\n\n");
		return;
	}
	pascalsTriangle(A,n);
	printf("The first %d rows of Pascal's triangle are:\n",n);
	for(i = 0; i < n; i++){
		for (j = 0; j <= i; j++)
			printf("%2d ",A[i][j]);
		printf("\n");
	}
	printf("\n");
	fflush(stdout);
} /* testPascal*/


/* testShiftColumnsLeft - Test the testShiftColumnsLeft function (Task 6)*/
void testShiftColumnsLeft(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	int rows_cols[2];
	int A[MATRIX_MAX][MATRIX_MAX];
	int i,j;
	startTest("shiftColumnsLeft");
	if(!(inputString = testPrompt("Enter the number of rows and columns: ",inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNInts(inputString,rows_cols,2) != 2){
		printf("\t No value provided - skipping test.\n\n");
		return;
	}
	int rows = rows_cols[0];
	int cols = rows_cols[1];
	if (rows >= MATRIX_MAX || rows < 1 || cols >= MATRIX_MAX || cols < 1){
		printf("\t Invalid rows (%d) or columns (%d) - skipping test.\n\n",rows,cols);
		return;
	}

	printf("Enter the contents of the matrix (one row per line):\n");
	fflush(stdout);
	for(i = 0; i < rows; i++){
		if(!(inputString = testPrompt(NULL,inputBuffer,sizeof(inputBuffer))))
			return;
		if (readNInts(inputString,&A[i][0],cols) != cols){
			printf("\t Too few values provided - skipping test.\n\n");
			return;
		}
	}
	shiftColumnsLeft(A, rows,cols);
	printf("The shifted matrix is:\n");
	for(i = 0; i < rows; i++){
		for (j = 0; j < cols; j++)
			printf("%2d ",A[i][j]);
		printf("\n");
	}
	printf("\n");
	fflush(stdout);
} /* testShiftColumnsLeft */


/* testStringLength - Test the stringLength function (Task 7)*/
void testStringLength(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	startTest("stringLength");
	if(!(inputString = testPrompt("Enter a string: ",inputBuffer,sizeof(inputBuffer))))
		return;
	removeTrailingSpaces(inputString);
	printf("Length of string \"%s\" is: %d\n\n",inputString,stringLength(inputString));
	fflush(stdout);
} /* testStringLength */


/* testCopySuffix - Test the copySuffix function (Task 8)*/
void testCopySuffix(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	char string[MAX_LINE], suffix[MAX_LINE];
	int start_position;
	startTest("copySuffix");
	if(!(inputString = testPrompt("Enter a string: ",inputBuffer,sizeof(inputBuffer))))
		return;
	removeTrailingSpaces(inputString);
	strcpy(string,inputString);
	int len = strlen(string);
	printf("Enter a value between 0 and %d: ",len-1);
	fflush(stdout);
	if(!(inputString = testPrompt(NULL,inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNInts(inputString,&start_position,1) != 1){
		printf("\t No value provided - skipping test.\n\n");
		return;
	}
	if (start_position < 0 || start_position >= len){
		printf("\t Invalid value provided - skipping test.\n\n");
		return;
	}
	printf("Input string is \"%s\"\n",string);
	suffix[0] = '\0';
	copySuffix(string,suffix,start_position);
	suffix[MAX_LINE-1] = '\0';
	printf("Suffix starting at index %d is: \"%s\"\n\n",start_position,suffix);
	fflush(stdout);
} /* testCopySuffix */



/* testMirrorString - Test the mirrorString function (Task 9)*/
void testMirrorString(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	char string[MAX_LINE*2];
	startTest("mirrorString");
	if(!(inputString = testPrompt("Enter a string: ",inputBuffer,sizeof(inputBuffer))))
		return;
	removeTrailingSpaces(inputString);
	strcpy(string,inputString);
	printf("Original string: \"%s\"\n",string);
	mirrorString(string);
	string[2*MAX_LINE-1] = '\0';
	printf("After mirroring: \"%s\"\n\n",string);
	fflush(stdout);
} /* testMirrorString */



/* testDecrypt - Test the decrypt function (Task 10)*/
void testDecrypt(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	char decodedString[MAX_LINE];
	startTest("decrypt");
	if(!(inputString = testPrompt("Enter a coded message (lowercase letters only): ",inputBuffer,sizeof(inputBuffer))))
		return;
	removeTrailingSpaces(inputString);
	char *s = inputString;
	while(*s){
		if (!islower(*s)){
			printf("\t String does not contain only lowercase letters - skipping test.\n\n");
			return;
		}
		s++;
	}
	printf(" Coded message: \"%s\"\n",inputString);
	decodedString[0] = '\0';
	decrypt(inputString,decodedString);
	decodedString[MAX_LINE-1] = '\0';
	printf("After decoding: \"%s\"\n\n",decodedString);
	fflush(stdout);
} /* testDecrypt */

/* testDBP - Test the distBetweenPoints function (Task 11)*/
void testDBP(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	Point p1,p2;
	float xy[2];
	startTest("distBetweenPoints");
	if(!(inputString = testPrompt("Enter x & y for the first point: ",inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNFloats(inputString,xy,2) != 2){
		printf("\t Wrong number of values provided - skipping test.\n\n");
		return;
	}
	p1.x = xy[0];
	p1.y = xy[1];
	if(!(inputString = testPrompt("Enter x & y for the second point: ",inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNFloats(inputString,xy,2) != 2){
		printf("\t Wrong number of values provided - skipping test.\n\n");
		return;
	}
	p2.x = xy[0];
	p2.y = xy[1];
	printf("The distance between (%.2f,%.2f) and (%.2f,%.2f) is: %f\n\n",p1.x,p1.y,p2.x,p2.y,distBetweenPoints(&p1,&p2));
	fflush(stdout);
} /* testDBP*/

/* testCNP - Test the countNearbyPoints function (Task 12)*/
void testCNP(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	PointListNode *list = NULL;
	float xy[2];
	Point centre;
	float radius;
	int count;
	startTest("countNearbyPoints");
	if(!(inputString = testPrompt("Enter x & y for the centre point: ",inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNFloats(inputString,xy,2) != 2){
		printf("\t Wrong number of values provided - skipping test.\n\n");
		return;
	}
	centre.x = xy[0];
	centre.y = xy[1];
	if(!(inputString = testPrompt("Enter a radius: ",inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNFloats(inputString,&radius,1) != 1){
		printf("\t Wrong number of values provided - skipping test.\n\n");
		return;
	}

	//Now allow the user to enter as many points as they want
	printf("Creating point list - Enter as many points as you want, and leave a line blank when you are done.\n");
	count = 0;
	while (1){
		printf("Enter x & y for point %d: ",count+1);
		fflush(stdout);
		if(!(inputString = testPrompt(NULL,inputBuffer,sizeof(inputBuffer))))
			break;
		if (readNFloats(inputString,xy,2) != 2){
			printf("\t Wrong number of values provided - ending list.\n");
			break;
		}
		list = addPointToList(list,allocateNewPoint(xy[0],xy[1]));
		count++;
	}
	list = reversePointList(list);
	printf("The list of points is: ");
	printPointList(list);
	printf("\n");
	printf("The number of points within radius %.2f from (%.2f,%.2f) is: %d\n\n",radius,centre.x,centre.y,countNearbyPoints(list,&centre,radius));
	freePointList(list);
	fflush(stdout);
} /* testCNP*/


/* testAddPointAtEnd - Test the addPointAtEnd function (Task 13)*/
void testAddPointAtEnd(){
	char inputBuffer[MAX_LINE];
	inputBuffer[MAX_LINE-1] = '\0';
	char *inputString;
	PointListNode *list = NULL;
	Point* newPoint = NULL;
	float xy[2];
	int count;
	startTest("addPointAtEnd");
	
	//Now allow the user to enter as many points as they want
	printf("Creating point list - Enter as many points as you want, and leave a line blank when you are done.\n");
	count = 0;
	while (1){
		printf("Enter x & y for point %d: ",count+1);
		fflush(stdout);
		if(!(inputString = testPrompt(NULL,inputBuffer,sizeof(inputBuffer))))
			break;
		if (readNFloats(inputString,xy,2) != 2){
			printf("\t Wrong number of values provided - ending list.\n");
			break;
		}
		list = addPointToList(list,allocateNewPoint(xy[0],xy[1]));
		count++;
	}
	if (count == 0){
		printf("\t No data provided - Skipping test.\n\n");
		return;

	}
	list = reversePointList(list);
	printf("The list of points is: ");
	printPointList(list);
	printf("\n");
	printf("Enter x & y for a point to add at the end of the list: ");
	fflush(stdout);
	if(!(inputString = testPrompt("",inputBuffer,sizeof(inputBuffer))))
		return;
	if (readNFloats(inputString,xy,2) != 2){
		printf("\t Wrong number of values provided - skipping test.\n\n");
		return;
	}
	newPoint = allocateNewPoint(xy[0],xy[1]);
	printf("Adding the point (%.2f,%.2f) to the end of the list with addPointAtEnd\n",newPoint->x,newPoint->y);
	addPointAtEnd(list,newPoint);
	printf("The modified list of points is: ");
	printPointList(list);
	printf("\n");
	freePointList(list);
	fflush(stdout);
} /* testAddPointAtEnd*/



int main(){
	testRoman(); //Test Task 1 (Roman Numerals)
	testInvertCase(); //Test Task 2 (Invert Capitalization)
	testMaxFibonacci(); //Test Task 3 (Fibonacci Numbers)
	testLinearSearch(); //Test Task 4 (Linear Search)
	testPascal(); //Test Task 5 (Pascal's Triangle)
	testShiftColumnsLeft(); //Test Task 6 (Shift Columns Left)
	testStringLength(); //Test Task 7 (String Length)
	testCopySuffix(); //Test Task 8 (Copy Suffix)
	testMirrorString(); //Test Task 9 (Mirror String)
	testDecrypt(); //Test Task 10 (Decrypt)
	testDBP(); //Test Task 11 (Distance Between Points)
	testCNP(); // Test Task 12 (Count Nearby Points)
	testAddPointAtEnd(); // Test Task 13 (Add Point at End)


	printf(" ****** Testing Finished ******\n");
	return EXIT_SUCCESS;
} /* main */
