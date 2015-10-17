/*****
 * Author   : brinkmwj
 * Date     : 2009-07-23
 * Sources  : All code is original
 * Purpose  : I have implemented the chiSquared function for you, do not change it.
 * Note     : N/A
 *****/

#include "Experiment.h"
#include <fstream>
#include <iomanip>
#include "Deck.h"
#include <sstream>
#include <iostream>

#define MAXNUMSHUFFLES 15

using namespace std;

/*
 * DO NOT CHANGE THIS FUNCTION! Add all your code after this!
 */ 
double chiSquared(long* rowHead, int rowLength){
	long rowTotal = 0;
	double expected = 0.0;
	double chiSq = 0.0;
	for(int i=0;i<rowLength; i++){
		rowTotal += rowHead[i];
	}
	expected = ((double)rowTotal)/((double)rowLength);

	for(int i=0; i<rowLength; i++){
		chiSq = chiSq + (((rowHead[i] - expected)*(rowHead[i] - expected))/expected);
	}

	return chiSq;
}

/*
 * Add your doOneExperiment here
 */

double doOneExperiment(int numshuffles){
	
	long* countMatrix = new long[52*52];
	for(int i = 0; i < 52*52;i++){
		countMatrix[i] = 0.0;
	}

	for(int k = 0; k <NUMEXPERIMENTS;k++){
		Deck deckList;
		for(int i = 0; i < numshuffles;i++){
			deckList.shuffle();
			}
		IntListNode* temp = deckList.getListHead();
		for(int i =0;i<52;i++){
			countMatrix[temp->data*52+i] = countMatrix[temp->data*52+i]+1;
			temp = temp->next;
			}
	}

	stringstream oss;
	oss << "table" << numshuffles << ".txt";  
	ofstream myFile;
	myFile.open(oss.str());
	for(int k = 0; k < 52; k++){
		for(int f = 0; f < 52; f++){
			myFile<<countMatrix[k*52+f]<<", ";
		}
		myFile<<endl<<endl;
	}
	myFile.close();
	double k = chiSquared(countMatrix, 52);

	if(k<CRITICALVALUE)
		cout<<numshuffles<<" shuffles was fair, chi^2 = "<<k<<endl;
	else
		cout<<numshuffles<<" shuffles was biased, chi^2 = "<<k<<endl;
	
	return k;

}

/*
 * Add your doExperimentRun here
 */

void doExperimentRun(){
	for(int i = 0; i<MAXNUMSHUFFLES;i++){
		double j = doOneExperiment(i);
	if(j < CRITICALVALUE){
		break;
		}
	}
}
