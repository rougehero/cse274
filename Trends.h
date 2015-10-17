/*****
 * Author   : brinkmwj
 * Date     : 2009-10-04
 * Sources  : All code is original
 * Purpose  : This class is designed to be an "Interface." Your trends data structure should be
 *            a sub-class of this class, but you should not implement this class. Instead, you should
 *            create a MyTrends class, in the files MyTrends.h and MyTrends.cpp
 *            Declare your class (in your MyTrends.h) like this:
 *  class MyTrends : public Trends {
 *    // declaration of member variables and methods here
 *  };
 *            In your class you should declare all of your methods to be virtual: This is how
 *            polymorphism is accomplished in C++. Do NOT copy the part that says "= 0" that I use
 *            below. That part means that the function, though declared, will not have any implementation.
 * Note     : DO NOT CHANGE THIS FILE!!! 
 */

#pragma once
#include <string>
using namespace std;

/*
 * This is an "abstract class" ... it contains a list of the public methods of the class, but
 *  they are all "pure virtual," which means they are not implemented anywhere in the code.
 *
 * An abstract class is used like an interface in Java: The only purpose of this class is to be the base
 *  class for your own data structure. You should make a .h and .cpp for you data structure: create files
 *  MyTrends.h and MyTrends.cpp, and called your class "MyTrends"
 */
class Trends {
public:
	/*
	 * If the string "s" has not been added to the data structure yet, add it, and set its count to "amount"
	 * If the string "s" already has an entry in your data structure, just increase the count by "amount"
	 *
	 * Usually, "amount" will be equal to 1. See Controller.cpp for an example of how increaseCount is used.
	 */
	virtual void increaseCount(string s, int amount) = 0;
	
	/*
	 * Return the count for the given string.
	 */
	virtual int getCount(string s) = 0;
	
	/*
	 * Return the nth most popular item, based on its count (0 = most popular, 1 = 2nd most popular).
	 * If there is a tie, return the string that comes first according to the the < operator for strings 
	 * (that is, comes first alphabetically).
	 */
	virtual string getNthPopular(int n) = 0;

	/*
	 * Return the total number of UNIQUE strings in the list. This will NOT be equal to the number of
	 * times increaseCount has been called, because sometimes you will add the same string to the
	 * data structure more than once. This function is useful when looping through the results
	 * using getNthPopular. If you do getNthPopular(numEntries()-1), it should get the least popular item.
	 */
	virtual int numEntries() = 0;
};
