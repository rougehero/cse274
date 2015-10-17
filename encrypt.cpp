#include <iostream>
#include <fstream>
#include <bitset>
#include "rsa_functions.h"
#include <cassert>

using namespace std;


RSAint chars2RSAint(char* str, int c){

	//assert(str != NULL, 0 <= c <= sizeof(RSAint));
	RSAint temp = 0;
	for (int i = 0; i < c; i++){
		temp = (RSAint)str[i]<<8|temp;
	}
	return temp;

}

void RSAint2chars(RSAint enc, char* str, int c) {
    //assert(enc >= 0 && c >= 0);
    for (int i=0; i < c; i++) {
        *(str + i) = (char) enc % 256;
        enc = enc >> 8;
    }
}

void generateKey(RSAint p, RSAint q, RSAint* e, RSAint* d, RSAint* n){

	//assert(e != NULL, d != NULL, n != NULL, minPrimeLimit < p < maxPrimeLimit, minPrimeLimit < q < maxPrimeLimit, p != q);

	*n = q*p;
	RSAint toit;
	toit = (q-1)*(p-1);
	*e = randomPrime(1, toit);

	for(int j = 0; j < 10; j++){

		if(isCoPrime(*e, toit)){
			*d = multiplicative_inverse(*e, *n);
			//assert(*n = p*q, e*d % ((p-1)*(q-1)) = 1, e > 10,000);
			return;
		}
		*e = randomPrime(1, toit);
	}

}

RSAint* RSAencrypt(char* msg, int size, int* newSize, RSAint e, RSAint n){
	
	//assert(msg != NULL, newSize != NULL , size > 0);

	*newSize = size - 1 / 3 + 1;
	RSAint * rsaArray = (RSAint*)malloc(sizeof(RSAint)* *newSize);
	int arrayPosition = 0;

	int i = 0;
	for(i = 0; i < size; i++){
		char chr[] = {msg[i+1], msg[i+2]};
		RSAint theRSA = chars2RSAint(chr, *newSize);
		RSAint encryptedRSA = modular_power(theRSA, e, n);
		rsaArray[arrayPosition] = encryptedRSA;
		arrayPosition++;
	}

	if(size%3 == 1){

		char chr[] = {msg[i]};
		
		RSAint theRSA = chars2RSAint(chr, 1);
		RSAint encryptedRSA = modular_power(theRSA, e, n);
		rsaArray[arrayPosition] = encryptedRSA;

	}

	if(size%3 == 2){

		char chr[] = {msg[i], msg[i+1]};
		
		RSAint theRSA = chars2RSAint(chr, 2);
		RSAint encryptedRSA = modular_power(theRSA, e, n);
		rsaArray[arrayPosition] = encryptedRSA;

	}

	return rsaArray;

	free(rsaArray);

}

char* RSAdecrypt(RSAint* encoding, int size, int* newSize, RSAint d, RSAint n){

	//assert(encoding != NULL, newSize != NULL, size > 0);

	char* theChars = (char*)malloc(3 * sizeof(char));
	int arrayPosition = 0;
	int i = 0;
	char*c = (char*)malloc(3 * sizeof(char));

	for(i = 0; i< size; i++){
		RSAint decryptedChar = modular_power(*(encoding + i), d, n);
		RSAint2chars(decryptedChar, c, 3);

		int z = 0;
		for(z = 0; z < 3; z++){
			if( *(c+z) == 0){
				break;
			}
			*(theChars + arrayPosition) = *(c+z);
			arrayPosition++;
		}

	}

	*newSize = arrayPosition;
	return theChars;
	free(theChars);
	free(c);

}

RSAint RSACracker(RSAint e, RSAint n){

	RSAint d;
	RSAint p = 2;
	RSAint q;

	while(true){
		q= n/p;
		if(n ==p*q && isCoPrime(p, q)){
			d = multiplicative_inverse(e, (p-1) * (q-1));
			break;
		}
		p++;
	}
	cout << "RSACracker Found p: " <<p<<" q: "<<(n/p)<<" ";
	cout << "Crack is: " << d << endl;

	return d;
}


