/*
*  Course:      CSC 111
*  Author:      Michael Reiter and B. Bird
*  UVicId:      V00831568
*  Assignment:  A7P2
*  Date:        13/11/14
*  Description: Generate HTML5 and SVG code to display an animated wire frame model.
*               The wire frame model is specified in an input text file identified by WIREFRAME_INPUT_FILENAME.
*               The HTML5/SVG code is output into a text file identified by HTML5_SVG_OUTPUT_FILENAME.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//The name of the input file
#define WIREFRAME_INPUT_FILENAME ("A7_2014_P12_teapot.txt")
// The name of the output file
#define HTML5_SVG_OUTPUT_FILENAME ("A7_2014_P2_teapot.html")
/* Number of frames in the animation - Do not change */
#define ANIMATION_FRAMES 180
/* Animation duration in seconds - Do not change */
#define ANIMATION_DURATION 5


/* ========================================================================= */
/*                              Type Definitions                             */
/*          Do not alter the provided definitions (they will be used         */
/*            for marking). You may add new definitions as needed.           */
/* ========================================================================= */

/* A line segment in 2d space */
typedef struct{
	float x1, y1;
	float x2, y2;
} LineSegment2d;

/* A line segment in 3d space */
typedef struct{
	float x1, y1, z1;
	float x2, y2, z2;
} LineSegment3d;


//Define the maximum size of matrix row or column
#define MATRIX_MAX (4)
//Define a Matrix type
typedef float Matrix[MATRIX_MAX][MATRIX_MAX];


/* Size of the HTML5 canvas - Do not change */
#define CANVAS_SIZE_X 800
#define CANVAS_SIZE_Y 800



/* ========================================================================= */
/*                       Library Function Declarations                       */
/*            These functions are defined at the end of the file.            */
/*      (Do not modify these declarations or the corresponding functions)    */
/* ========================================================================= */


/* writePrologue
   This function writes the initial part of the HTML file (which sets up the
   graphics interface). This must be called before any graphical data is written
   to the file.
*/
void writePrologue(FILE *f);

/* writeEpilogue
   This function writes the final part of the HTML file. This must be called
   after all data has been written, but before the file is closed.
   (The caller is responsible for closing the file afterwards).
*/
void writeEpilogue(FILE *f);

/* read_3d_segment
   Attempts to read six floating point values in the form
		x1 y1 z1 x2 y2 z2
   from the file pointer inputFile.
   If all six values are read successfully, the line segment is stored
   in the provided LineSegment3d struct and the function returns true.
   If all six values could not be read for any reason, the function returns
   false
*/
bool read_3d_segment(FILE* inputFile, LineSegment3d *segment);

/* write_animated_2d_segment
   If the provided file pointer outputFile is valid, writes an animated SVG
   line segment to outputFile with the colour provided and coordinates taken
   from the provided array of LineSegment2d structs.

   If the provided file pointer outputFile is not valid, the function will print an error
   message and terminate the program with EXIT_FAILURE.
*/

void write_animated_2d_segment(FILE* outputFile, LineSegment2d segments[ANIMATION_FRAMES], char colour[]);

/* matMul
   Compute the product C = A*B using matrix multiplication.

   ARows and ACols contain the number of rows and columns of the matrix A.
   BCols contains the number of columns in B (the number of rows in B is the same
   as the number of columns in A).
*/
void matMul(Matrix A, Matrix B, int ARows, int ACols, int BCols, Matrix C);


/* matInitIdentity
   Set the matrix A to an identity matrix of size (rows x cols).
   An identity matrix contains 1 in every diagonal entry (e.g. A[0][0], A[1][1], etc.)
   and 0 everywhere else.
*/
void matInitIdentity(Matrix A, int rows, int cols);

/* projectionMatrix
   Sets the provided matrix outMatrix to a 2 x 4 projection matrix.
*/
void projectionMatrix(Matrix outMatrix);

/* translationMatrix
   Sets the provided matrix outMatrix to a 4 x 4 translation matrix
   with translation (xt, yt, zt).
*/
void translationMatrix(Matrix outMatrix, float xt, float yt, float zt);

/* scaleMatrix
   Sets the provided matrix outMatrix to a 4 x 4 scaling matrix
   with scale factors (xs, ys, zs).
*/
void scaleMatrix(Matrix outMatrix, float xs, float ys, float zs);

/* rotationMatrixX
   Sets the provided matrix outMatrix to a 4 x 4 rotation matrix
   which rotates by the provided angle around the X axis.

   Note that angle must be specified in radians.
*/
void rotationMatrixX(Matrix outMatrix, float angle);

/* rotationMatrixY
   Sets the provided matrix outMatrix to a 4 x 4 rotation matrix
   which rotates by the provided angle around the Y axis.

   Note that angle must be specified in radians.
*/
void rotationMatrixY(Matrix outMatrix, float angle);

/* rotationMatrixZ
   Sets the provided matrix outMatrix to a 4 x 4 rotation matrix
   which rotates by the provided angle around the Z axis.

   Note that angle must be specified in radians.
*/
void rotationMatrixZ(Matrix outMatrix, float angle);

/* ========================================================================= */
/*                               Main Program                                */
/*        Using the types and functions declared above, as well as the       */
/*              Standard Library, implement the functions below.             */
/*       There are a total of 4 functions to implement (including main).     */
/* ========================================================================= */



/* convert_line_segment_3d_to_2d
   Converts the provided 3d line segment inputSegment to a 2d line segment
   and stores the result in outputSegment.

   The TransformMatrix is a 2 x 4 matrix describing the conversion transformation.

   In A7, the conversion is performed by creating a 4 x 2 matrix A of the form
        x1 x2
        y1 y2
        z1 z2
         1  1
   and taking the product B = TransformMatrix*A. B will be a 2 x 2 matrix of the form
        X1 X2
        Y1 Y2
   containing the coordinates of the 2d line segment's endpoints. The elements of B
   should be stored in the respective elements of the outputSegment struct.
*/
void convert_line_segment_3d_to_2d(LineSegment3d inputSegment, LineSegment2d *outputSegment, Matrix TransformMatrix){

	Matrix A, B;

	A[0][0] = inputSegment.x1;
	A[0][1] = inputSegment.x2;
	A[1][0] = inputSegment.y1;
	A[1][1] = inputSegment.y2;
	A[2][0] = inputSegment.z1;
	A[2][1] = inputSegment.z2;
	A[3][0] = 1;
	A[3][1] = 1;

	matMul(TransformMatrix, A, 2, 4, 2, B);

	outputSegment->x1 = B[0][0];
	outputSegment->x2 = B[0][1];
	outputSegment->y1 = B[1][0];
	outputSegment->y2 = B[1][1];

} /* convert_line_segment_3d_to_2d */


/* process_wireframe_model
   Given a pointer (inputFile) to an open file containing 3d line segments,
   read each line segment, rotate it to create an animation, convert
   each rotated point to a 2d point, then write the animated segment to the output
   file referenced by the pointer outputFile.

   Before reading any line segments, the function should construct a transform
   matrix M1, which is defined by the product
        M1 = P * T * S * R_X
   where
        - P is a projection matrix (use the projectionMatrix function)
        - T is a translation matrix with translation (400, 400, 400)
        - S is a scale matrix with scale factors (700, 700, 700)
        - R_X is a rotation by 20 degrees about the X axis

   The matrix P is 2 x 4. All other matrices are 4 x 4. Note that unlike in part 1,
   there is no matrix R_Z at this step.

   For each 3d line segment read, the array animated_segments should be filled
   in with ANIMATION_FRAMES entries, each of which is a 2d line segment. The
   segment animated_segments[j] will be frame j of the animation.

   To construct each segment in the array, loop through all values of j from 0
   to ANIMATION_FRAMES-1. For each value of j, construct a matrix M2, given
   by the product
        M2 = M1*R_Z
   where R_Z is a rotation by
        j*(360.0/ANIMATION_FRAMES)
   degrees around the Z axis (note that you will have to convert this angle
   to radians before calling the rotationMatrixZ function). Note that M1
   is a 2 x 4 matrix (so M2 will also be 2 x 4). After the matrix M2 is
   constructed, the convert_line_segment_3d_to_2d function should be called
   with the original 3d segment as input and animated_segments[j] as output.

   Some of the code has been provided, including the basic structure of loops
   necessary.

*/
void process_wireframe_model(FILE* inputFile, FILE* outputFile){

	LineSegment3d segment3d;
	LineSegment2d animated_segments[ANIMATION_FRAMES];
	Matrix M1, M2, P, T, S, R_X, PT, PTS, R_Z;
	int j;

	projectionMatrix(P);
	translationMatrix(T, 400, 400, 400);
	scaleMatrix(S, 700, 700, 700);
	rotationMatrixX(R_X, 20*M_PI/180);

	matMul(P, T, 2, 4, 4, PT);
	matMul(PT, S, 2, 4, 4, PTS);
	matMul(PTS, R_X, 2, 4, 4, M1);

	while (read_3d_segment(inputFile,&segment3d)){

		for (j = 0; j < ANIMATION_FRAMES; j++){
			//Construct frame j of the animation.

			/* Construct M2 here */
			rotationMatrixZ(R_Z, j*(360.0/ANIMATION_FRAMES)*M_PI/180);
			matMul(M1, R_Z, 2, 4, 4, M2);

			/* Call convert_line_segment_3d_to_2d with segment3d,
			   animated_segments[j] and M2 as arguments */
			convert_line_segment_3d_to_2d(segment3d, &animated_segments[j], M2);
		}

		write_animated_2d_segment(outputFile,animated_segments,"magenta");
	}

} /* process_wireframe_model */


/* main

   This function is already complete.
   Do not modify the contents of main() in your submission, or you may lose marks.

   The main program does the following:
	- Open the input file WIREFRAME_INPUT_FILENAME (defined at the top of this file),
	  which contains the data for a wireframe model.

	- Open the output file HTML5_SVG_OUTPUT_FILENAME (also defined at the top of this
	  file), which will contain the output HTML code.

	- Call the writePrologue function to write the HTML prologue to the output file.

	- Call the process_wireframe_model function to process the line segments in the file.

	- Call the writeEpilogue function to write the HTML epilogue to the output file.

	- Close the input and output files.
*/
int main(){

	//Open the input file
	FILE* inputFile = fopen(WIREFRAME_INPUT_FILENAME,"r");
	if (inputFile == NULL){
		printf("ERROR: Unable to open input file \"%s\". Exiting...\n",WIREFRAME_INPUT_FILENAME);
		return EXIT_FAILURE;
	}

	//Open the output file
	FILE* outputFile = fopen(HTML5_SVG_OUTPUT_FILENAME,"w");
	if (outputFile == NULL){
		printf("ERROR: Unable to open output file \"%s\". Exiting...\n",HTML5_SVG_OUTPUT_FILENAME);
		return EXIT_FAILURE;
	}

	//Write the prologue to the output file
	writePrologue(outputFile);

	process_wireframe_model(inputFile,outputFile);

	//Write the epilogue to the output file
	writeEpilogue(outputFile);
	fclose(outputFile);
	fclose(inputFile);
	return EXIT_SUCCESS;
} /* main */


/* ========================================================================= */
/*                           Library Functions                               */
/*        These are declared above, and will be useful to generate           */
/*            the output file. Do not modify these functions.                */
/* ========================================================================= */


/* writePrologue
   This function writes the initial part of the HTML file (which sets up the
   graphics interface). This must be called before any graphical data is written
   to the file.
*/
void writePrologue(FILE *f){
	if (!f){
		printf("writePrologue error: output file == NULL\n");
		exit(1);
	}
	fputs("<!DOCTYPE html>\n",f);
	fputs("<html>\n",f);
	fputs("<head>\n",f);
	fputs("<title>CSC 111 Fall 2014 -  Assignment 7 Part 2</title>\n",f);
	fputs("</head>\n",f);
	fputs("<body>\n",f);
	fprintf(f,"<svg width=\"%dpx\" height=\"%dpx\">\n",CANVAS_SIZE_X,CANVAS_SIZE_Y);
	fprintf(f,"<g transform=\"translate(0 %d)\">\n",CANVAS_SIZE_Y);
	fputs("<g transform=\"scale(1 -1)\">\n",f);
} /* writePrologue */

/* writeEpilogue
   This function writes the final part of the HTML file. This must be called
   after all data has been written, but before the file is closed.
   (The caller is responsible for closing the file afterwards).
*/
void writeEpilogue(FILE *f){
	if (!f){
		printf("writeEpilogue error: output file == NULL\n");
		exit(1);
	}
	fputs("</g></g>\n",f);
	fputs("</svg>\n",f);
	fputs("</body>\n",f);
	fputs("</html>\n",f);
} /* writeEpilogue */

/* read_3d_segment
   Attempts to read six floating point values in the form
		x1 y1 z1 x2 y2 z2
   from the file pointer inputFile.
   If all six values are read successfully, the line segment is stored
   in the provided LineSegment3d struct and the function returns true.
   If all six values could not be read for any reason, the function returns
   false
*/
bool read_3d_segment(FILE* inputFile, LineSegment3d *segment){
	if (inputFile == NULL)
		return false;
	int numRead = fscanf(inputFile,"%f %f %f %f %f %f",
		&segment->x1, &segment->y1, &segment->z1, &segment->x2, &segment->y2, &segment->z2);
	if (numRead < 6)
		return false;
	else
		return true;
} /* read_3d_segment */

/* write_animated_2d_segment
   If the provided file pointer outputFile is valid, writes an animated SVG
   line segment to outputFile with the colour provided and coordinates taken
   from the provided array of LineSegment2d structs.

   If the provided file pointer outputFile is not valid, the function will print an error
   message and terminate the program with EXIT_FAILURE.
*/

void write_animated_2d_segment(FILE* outputFile, LineSegment2d segments[ANIMATION_FRAMES], char colour[]){
	int j;
	if (outputFile == NULL){
		printf("ERROR: Output file invalid.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(outputFile,"<line x1=\"0\" y1=\"0\" x2=\"0\", y2=\"0\" style=\"stroke: %s;\">\n",colour);

	fprintf(outputFile,"<animate attributeName=\"x1\" values=\"");
	for(j = 0; j < ANIMATION_FRAMES; j++)
		fprintf(outputFile,"%.1f;",segments[j].x1);
	fprintf(outputFile,"\" dur=\"%ds\" repeatCount=\"indefinite\" />\n",ANIMATION_DURATION);

	fprintf(outputFile,"<animate attributeName=\"y1\" values=\"");
	for(j = 0; j < ANIMATION_FRAMES; j++)
		fprintf(outputFile,"%.1f;",segments[j].y1);
	fprintf(outputFile,"\" dur=\"%ds\" repeatCount=\"indefinite\" />\n",ANIMATION_DURATION);

	fprintf(outputFile,"<animate attributeName=\"x2\" values=\"");
	for(j = 0; j < ANIMATION_FRAMES; j++)
		fprintf(outputFile,"%.1f;",segments[j].x2);
	fprintf(outputFile,"\" dur=\"%ds\" repeatCount=\"indefinite\" />\n",ANIMATION_DURATION);

	fprintf(outputFile,"<animate attributeName=\"y2\" values=\"");
	for(j = 0; j < ANIMATION_FRAMES; j++)
		fprintf(outputFile,"%.1f;",segments[j].y2);
	fprintf(outputFile,"\" dur=\"%ds\" repeatCount=\"indefinite\" />\n",ANIMATION_DURATION);

	fprintf(outputFile,"</line>\n");
} /* write_animated_2d_segment */


/* matMul
   Compute the product C = A*B using matrix multiplication.

   ARows and ACols contain the number of rows and columns of the matrix A.
   BCols contains the number of columns in B (the number of rows in B is the same
   as the number of columns in A).
*/
void matMul(Matrix A, Matrix B, int ARows, int ACols, int BCols, Matrix C){

	int i, j, k;

	for (i = 0; i < ARows; i++){
		for (j = 0; j < BCols; j++){
			C[i][j] = 0;
			for (k = 0; k < ACols; k++)
				C[i][j] += A[i][k]*B[k][j];
		}
	}

} /* matMul */


/* matInitIdentity
   Set the matrix A to an identity matrix of size (rows x cols).
   An identity matrix contains 1 in every diagonal entry (e.g. A[0][0], A[1][1], etc.)
   and 0 everywhere else.
*/
void matInitIdentity(Matrix A, int rows, int cols) {
	int k, j;
	for (j=0;  j<rows;  j++){
		for (k=0;  k<cols;  k++){
			if (j == k)
				A[j][k] = 1.0;
			else
				A[j][k] = 0.0;
		}
	}
} /* matInitIdentity */



/* projectionMatrix
   Sets the provided matrix outMatrix to a 2 x 4 projection matrix.
*/
void projectionMatrix(Matrix outMatrix){
	outMatrix[0][0] = 1; outMatrix[0][1] = 0; outMatrix[0][2] = 0; outMatrix[0][3] = 0;
	outMatrix[1][0] = 0; outMatrix[1][1] = 0; outMatrix[1][2] = 1; outMatrix[1][3] = 0;
} /* projectionMatrix */

/* translationMatrix
   Sets the provided matrix outMatrix to a 4 x 4 translation matrix
   with translation (xt, yt, zt).
*/
void translationMatrix(Matrix outMatrix, float xt, float yt, float zt){
	outMatrix[0][0] = 1; outMatrix[0][1] = 0; outMatrix[0][2] = 0; outMatrix[0][3] = xt;
	outMatrix[1][0] = 0; outMatrix[1][1] = 1; outMatrix[1][2] = 0; outMatrix[1][3] = yt;
	outMatrix[2][0] = 0; outMatrix[2][1] = 0; outMatrix[2][2] = 1; outMatrix[2][3] = zt;
	outMatrix[3][0] = 0; outMatrix[3][1] = 0; outMatrix[3][2] = 0; outMatrix[3][3] = 1;
} /* translationMatrix */

/* scaleMatrix
   Sets the provided matrix outMatrix to a 4 x 4 scaling matrix
   with scale factors (xs, ys, zs).
*/
void scaleMatrix(Matrix outMatrix, float xs, float ys, float zs){
	outMatrix[0][0] = xs; outMatrix[0][1] = 0;  outMatrix[0][2] = 0;  outMatrix[0][3] = 0;
	outMatrix[1][0] = 0;  outMatrix[1][1] = ys; outMatrix[1][2] = 0;  outMatrix[1][3] = 0;
	outMatrix[2][0] = 0;  outMatrix[2][1] = 0;  outMatrix[2][2] = zs; outMatrix[2][3] = 0;
	outMatrix[3][0] = 0;  outMatrix[3][1] = 0;  outMatrix[3][2] = 0;  outMatrix[3][3] = 1;
} /* scaleMatrix */

/* rotationMatrixX
   Sets the provided matrix outMatrix to a 4 x 4 rotation matrix
   which rotates by the provided angle around the X axis.

   Note that angle must be specified in radians.
*/
void rotationMatrixX(Matrix outMatrix, float angle){
	outMatrix[0][0] = 1; outMatrix[0][1] = 0;           outMatrix[0][2] = 0;           outMatrix[0][3] = 0;
	outMatrix[1][0] = 0; outMatrix[1][1] = cos(angle);  outMatrix[1][2] = -sin(angle); outMatrix[1][3] = 0;
	outMatrix[2][0] = 0; outMatrix[2][1] = sin(angle);  outMatrix[2][2] = cos(angle);  outMatrix[2][3] = 0;
	outMatrix[3][0] = 0; outMatrix[3][1] = 0;           outMatrix[3][2] = 0;           outMatrix[3][3] = 1;
} /* rotationMatrixX */

/* rotationMatrixY
   Sets the provided matrix outMatrix to a 4 x 4 rotation matrix
   which rotates by the provided angle around the Y axis.

   Note that angle must be specified in radians.
*/
void rotationMatrixY(Matrix outMatrix, float angle){
	outMatrix[0][0] = cos(angle);  outMatrix[0][1] = 0; outMatrix[0][2] = -sin(angle); outMatrix[0][3] = 0;
	outMatrix[1][0] = 0;           outMatrix[1][1] = 1; outMatrix[1][2] = 0;           outMatrix[1][3] = 0;
	outMatrix[2][0] = sin(angle);  outMatrix[2][1] = 0; outMatrix[2][2] = cos(angle);  outMatrix[2][3] = 0;
	outMatrix[3][0] = 0;           outMatrix[3][1] = 0; outMatrix[3][2] = 0;           outMatrix[3][3] = 1;
} /* rotationMatrixY */

/* rotationMatrixZ
   Sets the provided matrix outMatrix to a 4 x 4 rotation matrix
   which rotates by the provided angle around the Z axis.

   Note that angle must be specified in radians.
*/
void rotationMatrixZ(Matrix outMatrix, float angle){
	outMatrix[0][0] = cos(angle); outMatrix[0][1] = -sin(angle); outMatrix[0][2] = 0; outMatrix[0][3] = 0;
	outMatrix[1][0] = sin(angle); outMatrix[1][1] = cos(angle);  outMatrix[1][2] = 0; outMatrix[1][3] = 0;
	outMatrix[2][0] = 0;          outMatrix[2][1] = 0;           outMatrix[2][2] = 1; outMatrix[2][3] = 0;
	outMatrix[3][0] = 0;          outMatrix[3][1] = 0;           outMatrix[3][2] = 0; outMatrix[3][3] = 1;
} /* rotationMatrixZ */
