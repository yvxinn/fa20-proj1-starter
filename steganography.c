/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *truecolor=(Color*) malloc(sizeof(Color));
	if(image->image[row][col].B%2==0){
		truecolor->R=0;
		truecolor->G=0;
		truecolor->B=0;
	}else{
		truecolor->R=255;
		truecolor->G=255;
		truecolor->B=255;
	}
	return truecolor;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image *trueimage=(Image*)malloc(sizeof(Image));
	trueimage->cols=image->cols;
	trueimage->rows=image->rows;
	trueimage->image=(Color**)malloc(sizeof(Color*)*trueimage->rows);
	for(int i=0;i<image->rows;i++){
		trueimage->image[i]=(Color*)malloc(sizeof(Color)*trueimage->cols);
	}
	for(int i=0;i<trueimage->rows;i++){
		for(int j=0;j<trueimage->cols;j++){
			Color* truecolor=evaluateOnePixel(image,i,j);
			trueimage->image[i][j]=*truecolor;
			free(truecolor);
		}
	}
	return trueimage;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	Image* origin=readData(argv[1]);
	Image* newimage=steganography(origin);
	writeData(newimage);
	freeImage(origin);
	freeImage(newimage);
	return 0;
}
