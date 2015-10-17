#include <iostream>
#include <fstream>
#include <Windows.h>
#include "BMPCanvas.h"
#include "Fractal.h"
#include <math.h>
#include <complex>
#include <string>

using namespace std;

BMPCanvas::BMPCanvas(string iFileName, int iWidth, int iHeight){
	width = iWidth;
	height = iHeight;
	fileName = iFileName;
	image = new Color [width*height];
}

BMPCanvas::BMPCanvas(string iFileName){
	fileName = iFileName;
	image = new Color [width*height];
}

BMPCanvas::BMPCanvas(){
	ofstream outFile(".bmp", ios::out | ios::binary);
	writeHeader(outFile, 0, 0);
	image = new Color [width*height];
}

BMPCanvas::~BMPCanvas(){
	delete []image
	//image = NULL;
};

void BMPCanvas::read(){
	delete []image;
	image = new Color [getWidth()*getHeight()];

};

void BMPCanvas::writeBMP(){
	fileName = fileName + ".bmp";
	ofstream outFile(fileName, ios::out | ios::binary);
	writeHeader(outFile, getHeight(), getWidth());
	for (int row=0; row < getHeight(); row++){ // row == 0 is the bottom row
		for (int col=0; col < getWidth(); col++){ // col == 0 is the leftmost column
			Color tmp = getPixel(row,col);
			outFile.write((char*)&tmp.blue, 1);
			outFile.write((char*)&tmp.green, 1);
			outFile.write((char*)&tmp.red, 1);
		}
	}
};

void BMPCanvas::setDims(int iWidth, int iHeight){
width = iWidth;
height = iHeight;
};

int BMPCanvas::getWidth(){
return width;
};

int BMPCanvas::getHeight(){
return height;
};

void BMPCanvas::setPixel(int x, int y, Color c){
	if(x > width || x < 0 || y > height || y < 0){
	cout << "Error: out of bounds";
}
else{
	image[y*width+x]=c;
}
};

Color BMPCanvas::getPixel(int x, int y){
if(x > width || x < 0 || y > height || y < 0){
	cout << "Error: out of bounds";
	return Color(0,0,0);
}
else{
	return image[y*width+x];
}
};

void BMPCanvas::blank(bool white){
	
	string extendedFileName = fileName + ".bmp";
	ofstream outFile(extendedFileName, ios::out | ios::binary);

	

	unsigned char blue, green, red;

	if(white==true){
		red == 255, green = 255, blue = 255;
	}
	else{
		red == 0, green = 0, blue = 0;
	}

	for (int row=0; row < width; row++){ 
		for (int col=0; col < height; col++){ 
			outFile.write((char*)&blue, 1);
			outFile.write((char*)&green, 1);
			outFile.write((char*)&red, 1);
		}
	}
	writeHeader(outFile, width, height);
};

string BMPCanvas::getFileName(){
return fileName;
};

void BMPCanvas::setFileName(string iFileName){
	fileName = iFileName;
};


