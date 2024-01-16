/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"
int alive[9]={0,0,1,1,0,0,0,0,0};
int dead[9]={0,0,0,1,0,0,0,0,0};

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE

	int liveR,liveG,liveB;
	liveR=liveB=liveG=0;
	int R,G,B;
	R=G=B=0;
	if(image->image[row][col].R!=0){R=1;}
	if(image->image[row][col].G!=0){G=1;}
	if(image->image[row][col].B!=0){B=1;}
    int offsets[][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };
	for(int i=0;i<8;i++){
		int newRow = row + offsets[i][0];
        int newCol = col + offsets[i][1];
		if(newRow>image->rows-1){newRow=0;}
		if(newRow<0){newRow=image->rows-1;}
		if(newCol>image->cols-1){newCol=0;}
		if(newCol<0){newCol=image->cols-1;}
		if(image->image[newRow][newCol].R!=0){liveR++;}
		if(image->image[newRow][newCol].G!=0){liveG++;}
		if(image->image[newRow][newCol].B!=0){liveB++;}
	}
	Color* newcolor=(Color*)malloc(sizeof(Color));
	newcolor->R=newcolor->G=newcolor->B=0;
	if(((R==1)&&(alive[liveR]==1))||((R==0)&&dead[liveR]==1)){
		newcolor->R=255;
	}
	if(((G==1)&&(alive[liveG]==1))||((G==0)&&dead[liveG]==1)){
		newcolor->G=255;
	}
	if(((B==1)&&(alive[liveB]==1))||((B==0)&&dead[liveB]==1)){
		newcolor->B=255;
	}
	return newcolor;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *newimage=(Image*)malloc(sizeof(Image));
	newimage->cols=image->cols;
	newimage->rows=image->rows;
	newimage->image=(Color**)malloc(sizeof(Color*)*newimage->rows);
	for(int i=0;i<image->rows;i++){
		newimage->image[i]=(Color*)malloc(sizeof(Color)*newimage->cols);
	}
	for(int i=0;i<newimage->rows;i++){
		for(int j=0;j<newimage->cols;j++){
			Color* newcolor=evaluateOneCell(image,i,j,rule);
			newimage->image[i][j]=*newcolor;
			free(newcolor);
		}
	}
	return newimage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	uint32_t rule=0;
	if(argc!=3){
		printf("usage: ./gameOfLife filename rule\n");
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
	}else{
		rule=strtol(argv[2],NULL,16);
	}
	int bit=0;
	for(int i=0;i<=17;i++){
		bit=(rule>>i)&1;
		if(i<=8){
			dead[i]=bit;
		}else{
			alive[i-9]=bit;
		}
	}
	Image* origin=readData(argv[1]);
	Image* newimage=life(origin,rule);
	writeData(newimage);
	freeImage(origin);
	freeImage(newimage);
	return 0;

	//YOUR CODE HERE
}
