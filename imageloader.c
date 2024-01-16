/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

// Opens a .ppm P3 image file, and constructs an Image object.
// You may find the function fscanf useful.
// Make sure that you close the file with fclose before returning.
Image *readData(char *filename)
{
	// YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	Image *image = (Image *)malloc(sizeof(Image));
	char buf[3];
	fscanf(fp, "%s", buf);
	int maxcolor;
	if (strcmp(buf, "P3") == 0)
	{
		fscanf(fp, "%u %u %u", &image->cols, &image->rows, &maxcolor);
		Color **colors = (Color **)malloc(sizeof(Color *) * image->rows);
		for (int i = 0; i < image->rows; i++)
		{
			colors[i] = (Color *)malloc(sizeof(Color) * image->cols);
		}
		for (int i = 0; i < image->rows; i++)
		{
			for (int j = 0; j < image->cols; j++)
			{
				fscanf(fp, "%hhu %hhu %hhu", &colors[i][j].R, &colors[i][j].G, &colors[i][j].B);
			}
		}
		image->image = colors;
	}
	fclose(fp);
	return image;
}

// Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	// YOUR CODE HERE
	int max=255;
	printf("%s\n", "P3");
	printf("%u %u\n%d\n", image->cols, image->rows,max);
	for (int i = 0; i < image->rows; i++)
	{
		for (int j = 0; j < image->cols; j++)
		{
			printf("%3u %3u %3u", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
			if (j != image->cols - 1)
			{
				printf("   ");
			}
		}
		printf("\n");
	}
}

// Frees an image
void freeImage(Image *image)
{
	// YOUR CODE HERE
	for (int i = 0; i < image->rows; i++)
	{
		free(image->image[i]);
		if (image->image[i] != NULL)
		{
			image->image[i] = NULL;
		}
	}
	free(image->image);
	if(!image->image){image->image=NULL;}
	free(image);
	image=NULL;
}