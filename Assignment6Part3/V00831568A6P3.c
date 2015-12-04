/*
*  Course:      CSC 111
*  Author:      Michael Reiter
*  UVicId:      V00831568
*  Assignment:  A6P3
*  Date:        22/10/14
*  Description: Generate HTML5 and SVG code to display a wire frame model.
*               The wire frame model is specified in an input text file identified by WIREFRAME_INPUT_FILENAME.
*               The HTML5/SVG code is output into a text file identified by HTML5_SVG_OUTPUT_FILENAME.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//The name of the input file
#define WIREFRAME_INPUT_FILENAME ("A6_2014_teapot.txt")
// The name of the output file
#define HTML5_SVG_OUTPUT_FILENAME ("A6_2014_teapot.html")


/* ========================================================================= */
/*                              Type Definitions                             */
/*          Do not alter the provided definitions (they will be used         */
/*            for marking). You may add new definitions as needed.           */
/* ========================================================================= */

#define MATRIX_MAX 100

/* A point (x,y) in 2d space */
typedef float Point2d[2];

/* A point (x,y,z) in 3d space */
typedef float Point3d[3];


#define CANVAS_SIZE_X 500
#define CANVAS_SIZE_Y 500

/* ========================================================================= */
/*                       Library Function  Declarations                      */
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


/* ========================================================================= */
/*                               Main Program                                */
/*        Using the types and functions declared above, as well as the       */
/*              Standard Library, implement the functions below.             */
/*       There are a total of 4 functions to implement (including main).     */
/* ========================================================================= */



/* read_3d_segment
   Attempts to read six floating point values in the form
		x1 y1 z1 x2 y2 z2
   from the file pointer inputFile.
   If all six values are read successfully, the point (x1, y1, z1) is stored
   in the vector endpoint1, the point (x2, y2, z2) is stored in the vector
   endpoint2 and the function returns true.
   If all six values could not be read for any reason, the function returns
   false
*/
bool read_3d_segment(FILE* inputFile, Point3d endpoint1, Point3d endpoint2){
	float x1, y1, z1, x2, y2, z2;
	if (fscanf(inputFile, "%f %f %f %f %f %f", &x1, &y1, &z1, &x2, &y2, &z2) != EOF){
		endpoint1[0] = x1;
		endpoint1[1] = y1;
		endpoint1[2] = z1;
		endpoint2[0] = x2;
		endpoint2[1] = y2;
		endpoint2[2] = z2;
		return true;
	} else {
		return false;
	}
} /* read_3d_segment */


/* write_2d_segment
   If the provided file pointer outputFile is valid, writes an SVG line segment
   to the output file with one endpoint at Point1 = (x1, y1), the other endpoint
   at Point2 = (x2, y2) and the colour provided.
   An example of an SVG line segment from (0,0) to (6,10) with colour "red" is
	<line x1="0" y1="0" x2="6" y2="10" style="stroke: red;" />

   If the provided file pointer outputFile is not valid, the function will print an error
   message and terminate the program with EXIT_FAILURE.
*/

void write_2d_segment(FILE* outputFile, Point2d point1, Point2d point2, char colour[]){
	if (outputFile != NULL){
		fprintf(outputFile, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke: %s;\" />\n", point1[0], point1[1], point2[0], point2[1], colour);
	} else {
		printf("Error: outputFile is invalid.");
		exit(EXIT_FAILURE);
	}
} /* write_2d_segment */


/* convert_point_3d_to_2d
   Converts the provided 3d point inputPoint to a 2d point and stores the result
   in the outputPoint array.

   For assignment 6, the conversion should take a 3d point of the form (x, y, z)
   and produce a 2d point (500*x + 250, 500*z + 250). The y coordinate of the 3d
   point should be discarded.
*/
void convert_point_3d_to_2d(Point3d inputPoint, Point2d outputPoint){
	outputPoint[0] = (500*inputPoint[0] + 250);
	outputPoint[1] = (500*inputPoint[2] + 250);

} /* convert_point_3d_to_2d */

/* main

   This function is already complete.
   Do not modify the contents of main() in your submission, or you may lose marks.

   The main program does the following:
	- Open the input file WIREFRAME_INPUT_FILENAME (defined at the top of this file),
	  which contains the data for a wireframe model.

	- Open the output file HTML5_SVG_OUTPUT_FILENAME (also defined at the top of this
	  file), which will contain the output HTML code.

	- Call the writePrologue function to write the HTML prologue to the output file.

	- For each 3d line segment in the input file:
		- Convert the 3d line segment to a 2d line segment
		- Write the 2d line segment to the output file

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

	//Create 2 3d points
	Point3d point1_3d, point2_3d;
	//Create 2 2d points
	Point2d point1_2d, point2_2d;
	while(read_3d_segment(inputFile,point1_3d, point2_3d)){
		//Convert each 3d point to a 2d point
		convert_point_3d_to_2d(point1_3d, point1_2d);
		convert_point_3d_to_2d(point2_3d, point2_2d);
		//Write the 2d line segment to the output file
		write_2d_segment(outputFile, point1_2d, point2_2d, "blue");
	}
	
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
	fputs("<title>CSC 111 Fall 2014 -  Assignment 6 Part 3</title>\n",f);
	fputs("</head>\n",f);
	fputs("<body>\n",f);
	fprintf(f,"<svg width=\"%dpx\" height=\"%dpx\">\n",CANVAS_SIZE_X,CANVAS_SIZE_Y);
	fputs("<g transform=\"translate(0 500)\">\n",f);
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
