/*****
 * Author   : brinkmwj
 * Date     : 2009-07-23
 * Modified : inclezd (2/28/2015)
 * Sources  : All code is original
 * Purpose  : The IntList class implements a linked list of integers, as described by our textbook.
 *            This file also declares IntListNode, which is a class that represents a single node of
 *            an IntList, and a stand-alone function called splice that will be useful in Phase02.
 * Note     : If you are looking at this file, you are cheating!
 *****/
#include "IntList.h"
#include <iostream>

using namespace std;

IntListNode::IntListNode(){
	data = -1;
	next = this;
	prev = this;
}

IntList::IntList(){
	sentinel = new IntListNode();
}

IntList::~IntList(){
	clear();
	delete sentinel;
}

void IntList::pop_back(){
	if(isEmpty()) return;

	IntListNode* n = sentinel->prev;
	sentinel->prev = sentinel->prev->prev;
	sentinel->prev->next = sentinel;
	delete n;
}

bool IntList::isEmpty(){
	return (sentinel->next == sentinel);
}

void IntList::clear(){
	while(!isEmpty()){
		pop_back();
	}
}

void IntList::push_back(int c){
	IntListNode* n = new IntListNode();
	n->data = c;

	n->next = sentinel;
	n->prev = sentinel->prev;
	sentinel->prev->next = n;
	sentinel->prev = n;
}

void splice(IntListNode* sourceStart, IntListNode* sourceEnd, IntListNode* target){
	IntListNode* oldTargetNext = target->next;
	IntListNode* sourceStartPrev = sourceStart->prev;
	IntListNode* sourceEndNext = sourceEnd->next;

	//Splice into target
	sourceEnd->next = target->next;
	sourceStart->prev = target;
	target->next = sourceStart;
	oldTargetNext->prev = sourceEnd;

	//Splice out of old list
	sourceStartPrev->next = sourceEndNext;
	sourceEndNext->prev = sourceStartPrev;

}

IntListNode* IntList::head(){
	if(!isEmpty()){
		return sentinel->next;
	} else {
		return NULL;
	}
}

IntListNode* IntList::tail(){
	if(!isEmpty()){
		return sentinel->prev;
	} else {
		return NULL;
	}
}

IntListNode* IntList::getSentinel(){
	return sentinel;
}

void IntList::printList() {
	IntListNode* cur = sentinel->next;
	while (cur != sentinel) {
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}
