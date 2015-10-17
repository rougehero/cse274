
#include "Deck.h"
#include "IntList.h"
#include <iostream>

Deck::Deck(){

	for(int i = 0; i < 52; i++){
		deckList.push_back(i);
	}
}

IntListNode* Deck::getListHead(){
	return deckList.head();
}

void Deck::shuffle(){
	IntList A;
	IntList B;
	cut(&A, &B);
	
	
	 int random = rand() % 1;

	 while(!A.isEmpty() || !B.isEmpty()){
			 IntListNode* t = deckList.tail();
			 if(t==NULL){
				 t = deckList.getSentinel();
			 }
			 if(!A.isEmpty()){
				 IntListNode* temp = A.head();

				 random = rand()%3;
				 if(random!=0){
					 for(int i = 1; i<random && temp->next!=A.getSentinel();i++){

						 temp=temp->next;
					 }
					 splice(A.head(),temp,t);
				 }
			 }
			 if(!B.isEmpty()){
				 IntListNode* temp = B.head();

				 random = rand()%3;
				 if(random!=0){
					 for(int i = 1; i<random && temp->next!=B.getSentinel();i++){

						 temp=temp->next;
					 }
					 splice(B.head(),temp,t);
				 }
			 }
	 }

}



void Deck::cut(IntList* A, IntList* B){

	IntListNode* half = deckList.head();

	for(int j = 0; j<26; j++){
		half = half->next;
	}

	splice(deckList.head(), half, A->getSentinel());
	splice(deckList.head(), deckList.tail(), B->getSentinel());
	
}
