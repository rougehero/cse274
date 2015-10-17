#include "Fractal.h"
#include "BMPCanvas.h"
#include <fstream>



void makeYellowSquare(string fileName, int dim) {
	string extendedFileName = fileName + ".bmp";
	ofstream outFile(extendedFileName, ios::out | ios::binary);

	writeHeader(outFile, dim, dim);

	unsigned char blue = 0, green = 0, red = 255;

	for (int row=0; row < dim; row++){ // row == 0 is the bottom row
		for (int col=0; col < dim; col++){ // col == 0 is the leftmost column
			outFile.write((char*)&blue, 1);
			outFile.write((char*)&green, 1);
			outFile.write((char*)&red, 1);
		}
	}
}

int main(){
	//makeYellowSquare("Sqr", 200);

	MakeSquare256();
	MakeSphere256();
    return 0;
}


//i went to study hours and recieved help from: Craig, Mike, Richard, Nick, and Ray.
