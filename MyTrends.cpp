#include <iostream>
#include <algorithm>
#include <fstream>
#include "MyTrends.h"

using namespace std;


	MyTrends::MyTrends(){
		a=6;
		b=4;
		m=6703;
		table = new Entry[m];

	}

	MyTrends::MyTrends(int iM, int iA, int iB){

		a=iA;
		b=iB;
		m=iM;
		table = new Entry[m];

	}

	MyTrends::~MyTrends(){

		delete[] table;
	}
	
	
	void MyTrends::increaseCount(string s, int amount){
		
		int sum = 0;
		for (int i = 0; i < s.size(); i++) {
			sum+=s[i];
		}
		int key = hash(sum);
		if(table[key%m].value==s){
			table[key%m].count += amount;
		}
		else{
		
			while(table[key%m].value != s){
				key+=1;
				if(table[key%m].key==-1){
					table[key%m].value = s;
					table[key%m].count = amount;
					table[key%m].key = key%m;
					counter++;
					break;
				}

			}
		}
	}

	int MyTrends::getCount(string s){

		int sum = 0;
		for (unsigned int i = 0; i < s.size(); i++) {
			sum+=s[i];
		}
		int key = hash(sum);
		return table[key].count;
		 

	}

	string MyTrends::getNthPopular(int n){

		popularCount[m];
		for(int i = 0; i < m; i++){
			popularCount[i] = table[i].count;
		}
		sort(popularCount, popularCount+m);
		int knowing = popularCount[n];

		string word = "";
		int j = 0;
		while(true){
			
			if(table[j].count = knowing){
				word = table[j].value;
				break;
			}

			if(j > m){
				word = "ERROR";
				break;
			}
		}

		return word;
	}

	int MyTrends::numEntries(){
		
		
		//int counter = 0;
		//for(int j = 0; j < m; j++){
		//	if(table[j].count > 0){

		//		counter++;
		//	}
		//}
		
		return counter;

	}

	int MyTrends::hash(int k){

		h = (a*k)+b;
		return h;
	}
