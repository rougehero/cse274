/*****
 * Author   : brinkmwj
 * Date     : 2009-07-23
 * Sources  : All code is original
 * Purpose  : This file implements a simple controller and main() function for
 *            the project.
 * Note     : If you are looking at this file, you are cheating!
 *****/
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Tester.h"
#include "Deck.h"
#include "Experiment.h"

using namespace std;

int main(){
	// Tester t;
	// t.doTests();

	srand((int)time(NULL));

	doExperimentRun();

	return 0;
}
