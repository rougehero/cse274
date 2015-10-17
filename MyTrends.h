#include "Trends.h"
#include <iostream>
#include <fstream>

using namespace std;


class Entry {
public:
	Entry() {
		key = -1;
		value = "";
		count = 0;
	}

	Entry(int k, string v) {
		key = k;
		value = v;
	}
	int count;
	int key;
	string value;
};


class MyTrends : public Trends { 
/* member variables and methods declared here */ 
public:
	MyTrends();
	MyTrends(int iM, int iA, int iB);
	~MyTrends();
	void increaseCount(string s, int amount);
	int getCount(string s);
	string getNthPopular(int n);
	int numEntries();



private:
	/** Calculates the hash function for input k as a*k+b
	  */
	int hash(int k);
	int* popularCount;
	Entry* table;
	int count;
	int m, a, b, h, counter;
	// add other data members if needed
};
