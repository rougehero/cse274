#include "encrypt.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/**
 * Add your own code to the main function below, as specified there.
 */

void test1() {
	RSAint i = chars2RSAint("ABC.", strlen("ABC.")+1);
    cout << "i: (should print 776159809) " << i << endl;
   
    char * s = (char*)malloc(strlen("ABC.")*sizeof(char) + sizeof(char));
    RSAint2chars(i, s, strlen("ABC.")+1);
    cout << "Should print ABC.: " << s << endl;
}

void test2() {
	RSAint i = chars2RSAint("ABCD.", strlen("ABCD.")+1);
    cout << "i: (should print 198713754177) " << i << endl;
   
    char * s = (char*)malloc(strlen("ABCD.")*sizeof(char) + sizeof(char));
    RSAint2chars(i, s, strlen("ABCD.")+1);
    cout << "Should print ABCD.: " << s << endl;
}

void test3() {
	int i = 0;
	int*newSize = (int*)malloc(sizeof(int));

	FILE * f;
	f = fopen("Keys.txt", "r");
	RSAint crackedN;
	fscanf(f, "%lld", &crackedN);
	RSAint crackedE;
	fscanf(f, "%lld", &crackedE);
	fclose(f);

	RSAint crackedO = RSACracker(crackedE, crackedN);

	int count = 0;
	RSAint code;
	RSAint*codeArray = (RSAint*)malloc(3000 * sizeof(RSAint));

	FILE* encryptedF;
	encryptedF = fopen("encrypted.txt", "r");
	
	while(fscanf(encryptedF, "%lld", &code) != EOF){
		*(codeArray + count) = code;
		count++;
	}

	fclose(encryptedF);

	char* decryptedMessege = (RSAdecrypt(codeArray, count, newSize, crackedE, crackedN));

	cout << "Decrypting messege" << endl << endl;
	for(int i = 0; i < *newSize; i++){
		cout<<*(decryptedMessege + i);

	}
	cout << endl;
	free(newSize);
	free(codeArray);

}

int main() {
	// for testing and grading - do not change!
	test1();
	test2();

	/**
	 * Write your code below this comment.
	 *	- Read the public key components n and e from the file keys.txt. (n is listed first.)
	 *	- Read the contents of the file encrypted.txt, containing a sequence of RSAints 
	 *		separated by spaces (which was produced by applying the encryption algorithm to a file) 
	 *		using the public key (e,n) you just read in. 
	 *	- Crack the encryption and print out the original message.
	 */

	//test3();
	return 0;
}
