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
#include "BMPCanvas.h"
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

Complex Point2Complex(int i, int j, double reMin, double reMax, int width, double imMin, double imMax, int height){

	 double a = reMin + i*(reMax-reMin)/(width - 1.0);
	 double b = imMin + j*(imMax-imMin)/(height - 1.0);

	 Complex c(a, b);
	 return c;
}

int FractalDivergeCount(Complex c, Complex k, int numIterations){
	Complex z(c);

	for(int i = 0; i < numIterations; i++){
	if(abs(z) > 2){
	return i;
	}
	z = z*z + k;
	}

	return numIterations;
}

void Sierpinski(string fileName, int width, int n){

	seedRNG();
	BMPCanvas sierpinski(fileName,width,width);
	sierpinski.blank(false);

	Complex p1 (0,0);
	Complex p2 (width-1,0);
	Complex p3 (width/2, sqrt(3)*(width/2));

	Complex midpoint;
	Complex temp (randomNumber(0,width),randomNumber(0,sqrt(3)*(width/2))); //random point
	Color white (255,255,255);
	sierpinski.setPixel(p1.real(), p1.imag(),white);
	sierpinski.setPixel(p2.real(), p2.imag(),white);
	sierpinski.setPixel(p3.real(), p3.imag(),white);

	
	int f;
	for(int i = 0; i < n; i++){
		f = randomNumber(1,4);
		if(f == 1){
			midpoint = Complex(((p1.real() + temp.real())/ 2), ((p1.imag() + temp.imag())/ 2));
			sierpinski.setPixel(midpoint.real(), midpoint.imag(),white);
			temp = midpoint;

		}
		else if(f == 2){ 
			midpoint = Complex(((p2.real() + temp.real())/ 2), ((p2.imag() + temp.imag())/ 2));
			sierpinski.setPixel(midpoint.real(), midpoint.imag(),white);
			temp = midpoint;

		}
		else if(f == 3){ 
			midpoint = Complex(((p3.real() + temp.real())/ 2), ((p3.imag() + temp.imag())/ 2));
			sierpinski.setPixel(midpoint.real(), midpoint.imag(),white);
			temp = midpoint;

		}
	}

	sierpinski.writeBMP();

}

void Julia (string fileName, Complex k){

	Complex c;
	int f;
	Color black(0,0,0);
	Color white(255,255,255);
	BMPCanvas julia(fileName, 1000, 1000);

	for (int i = 0;i< julia.getWidth(); i++){
		for(int j = 0;j<julia.getHeight(); j++){
			c = Point2Complex(i,j,-1.5,1.6, 1000, -1.5, 1.6, 1000);
			f = FractalDivergeCount(c, k, 100);
			Color col;
			if (f<50){
				col = Color(0, 9, 5*f);
			}
			else {
				col = Color(f-50, 10*(f-50), 255);
			}
			julia.setPixel(i, j, col);
		}
	}

	julia.writeBMP();

}

void Mandelbrot(string fileName){

	Complex c;
	int f;
	Color black(0,0,0);
	Color white(255,255,255);
	BMPCanvas mandelbrot(fileName, 1000, 1000);

	for (int i = 0;i< mandelbrot.getWidth(); i++){
		for(int j = 0;j<mandelbrot.getHeight(); j++){
			c = Point2Complex(i,j,-2.0, 1.0, 1000, -1.5, 1.5, 1000);
			f = FractalDivergeCount(c, c, 100);
			Color col;
			if (f<50){
				col = Color(160, 26, 4*f);
			}
			else {
				col = Color(f-40, 8*(f-30), 245);
			}
			mandelbrot.setPixel(i, j, col);
		}
	}

	mandelbrot.writeBMP();

}
