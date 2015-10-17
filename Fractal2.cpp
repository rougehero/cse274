/*****
 * Author   : inclezd (modification of code from karroje and brinkmfwj) 
 * Date     : 2013-08-30
 * Purpose  : These functions are utility functions for generating bmp formatted fractals.
 * NOTES    : DO NOT MODIFY ANY OF THE CODE PROVIDED! Write your code below the line at the bottom of this file.
 *****/
#include <iostream>
#include <fstream>

//Windows.h is only needed for readHeader and writeHeader.
#include <Windows.h>
#include "Fractal.h"
#include <math.h>
#include <complex>

#pragma comment (lib, "winmm.lib")

using namespace std;

/**
 * Provided functions. DO NOT MODIFY!!!
 **/

// Random Number Generator seed: Seed the random number generator.  Seeds
// from clock if seed_value = 0.
void seedRNG(long seed_value) {
  if (seed_value > 0) 
	  srand(seed_value);
  else {
     double x = timeGetTime();  
     while (x == timeGetTime() );   // BETTER solution: get process ID
    srand(timeGetTime());
  }
}


// Return a random integer in the half-open interval [i,j).
// (Meaning: it returns a number ranging from i up to BUT NOT INCLUDING j.)
int randomNumber(int i, int j) {
	return (int)((j-i)*((1.0*rand()) / (RAND_MAX+1))) + i;
}

//Information on BMP format was provided by www.fileformat.info/format/bmp/egff.htm
void writeHeader(ostream& out, int width, int height){
  if (width % 4 != 0) {
    cerr << "ERROR: There is a windows-imposed requirement on BMP that the width be a multiple of 4.\n";
    cerr << "Your width does not meet this requirement, hence this will fail.  You can fix this\n";
    cerr << "by increasing the width to a multiple of 4." << endl;
    exit(1);
  }

	BITMAPFILEHEADER tWBFH;
	tWBFH.bfType = 0x4d42;
	tWBFH.bfSize = 14 + 40 + (width*height*3);
	tWBFH.bfReserved1 = 0;
	tWBFH.bfReserved2 = 0;
	tWBFH.bfOffBits = 14 + 40;

	BITMAPINFOHEADER tW2BH;
	memset(&tW2BH,0,40);
	tW2BH.biSize = 40;
	tW2BH.biWidth = width;
	tW2BH.biHeight = height;
	tW2BH.biPlanes = 1;
	tW2BH.biBitCount = 24;
	tW2BH.biCompression = 0;

	out.write((char*)(&tWBFH),14);
	out.write((char*)(&tW2BH),40);
}

//Information on BMP format was provided by www.fileformat.info/format/bmp/egff.htm
void readHeader(istream& in, int& width, int& height){
	BITMAPFILEHEADER tWBFH;
	BITMAPINFOHEADER tW2BH;
	in.read((char*)(&tWBFH),14);
	in.read((char*)(&tW2BH),40);

	width = tW2BH.biWidth;
	height = tW2BH.biHeight;
}

/*****************************************************************************************************/
/**
 * End of provided functions, your work goes below here. You may modify anything below this line, but
 * do NOT modify anything above this line.
 **/


void MakeSquare256(){
	int x = 256, y =256;

	BMPCanvas newSqaure("newSquare", x, y);
	
	Color black = Color(0, 0, 0);
	Color white = Color(255, 255, 255);

	for (int row=0; row < x; row++){ // row == 0 is the bottom row
		for (int col=0; col < y; col++){ // col == 0 is the leftmost column
			if(col >= 64 &&  col < 192 && row >= 64 && row < 192){
			newSqaure.setPixel(row, col, white);
			}
			else{
			newSqaure.setPixel(row, col, black);
			}
		}
	}
	newSqaure.writeBMP();
}

void MakeSphere256(){
	int x = 256, y = 256;

	BMPCanvas newSphere("newSphere", x, y);
	
	Color black = Color(0, 0, 0);
	Color white = Color(255, 255, 255);

	for (int row=0; row < x; row++){ // row == 0 is the bottom row
		for (int col=0; col < y; col++){ // col == 0 is the leftmost column
			
			int distanceSquared = (row-128)*(row-128) + (col-128)*(col-128);
			int color_value = 0;
			if (distanceSquared <= (90*90)){	        
			color_value = (255*((90*90)-distanceSquared))/(90*90);
			}
			Color C = Color(color_value, color_value, color_value);   // Keeping all values the same dictates a shade of grey
			newSphere.setPixel(row, col, C);
		}
	}
	newSphere.writeBMP();
}
