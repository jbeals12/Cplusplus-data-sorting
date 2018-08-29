/*
Aaron Shaneen
CS 2420 SUM' 15
Assignment 1
*/

//Copyright 2015, Bradley Peterson, Weber State University, All rights reserved.

#include <iostream>
#include <string>
#include <sstream>
//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#endif

using namespace std;


//**********************************
//Write your code below here
//**********************************

// CustomStack Class
template <typename T>
class CustomStack
{
private:
	T * stackArrPtr;
	unsigned int currentSize;
	unsigned int capacity;
public:
	CustomStack(const unsigned int arrSize);
	~CustomStack();
	unsigned int size();
	void push(const T& pushThis);
	T pop();
};

// CustomStack Constructor
template <typename T>
CustomStack<T>::CustomStack(const unsigned int arrSize)
{
	stackArrPtr = new T[arrSize];
	currentSize = 0;
	capacity = arrSize;
}

// CustomStack Destructor
template <typename T>
CustomStack<T>::~CustomStack()
{
	delete[] stackArrPtr;
	stackArrPtr = NULL;
	currentSize = 0;
	capacity = 0;
}

// CustomStack size method 
template <typename T>
unsigned int CustomStack<T>::size()
{
	return currentSize;
}

// CustomStack push method
template <typename T>
void CustomStack<T>::push(const T& pushThis)
{
	if (currentSize == capacity)
	{
		throw 1;
	}

	stackArrPtr[currentSize++] = pushThis;
}

// CustomStack pop method
template <typename T>
T CustomStack<T>::pop()
{
	if (currentSize == 0)
	{
		throw 1;
	}

	return stackArrPtr[--currentSize];
}

// CustomQueue Class
template <typename T>
class CustomQueue
{
private:
	T * queArrPtr;
	unsigned int currentSize;
	unsigned int capacity;
	unsigned int front;
	unsigned int back;
public:
	CustomQueue(const unsigned int arrSize);
	~CustomQueue();
	unsigned int size();
	T pop_front();
	void push_back(const T& pushThis);
};

// CustomQueue Constructor
template <typename T>
CustomQueue<T>::CustomQueue(const unsigned int arrSize)
{
	queArrPtr = new T[arrSize];
	currentSize = 0;
	capacity = arrSize;
	front = 0;
	back = 0;
}

// CustomQueue Destructor
template <typename T>
CustomQueue<T>::~CustomQueue()
{
	delete[] queArrPtr;
	queArrPtr = NULL;
	currentSize = 0;
	capacity = 0;
	front = 0;
	back = 0;
}

// CustomQueue size method 
template <typename T>
unsigned int CustomQueue<T>::size()
{
	return currentSize;
}

// CustomQueue push_back method
template <typename T>
void CustomQueue<T>::push_back(const T& pushThis)
{
	if (currentSize == capacity)
	{
		throw 1;
	}

	else if (back == capacity)
	{
		back = 0;
	}

	queArrPtr[back++] = pushThis;
	currentSize++;
}

// CustomQueue pop_front method
template <typename T>
T CustomQueue<T>::pop_front()
{
	if (currentSize == 0)
	{
		throw 1;
	}

	else if (front == capacity)
	{
		front = 0;
	}

	currentSize--;
	return queArrPtr[front++];
}

//**********************************
//Write your code above here
//**********************************

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
		return false;
	}
}


//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		if (whatItShouldBe == "") {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
		}
		else {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
		}
		return false;
	}
}

//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << ".  ";
		cout << "You are manually managing " << whatItIs << " bytes in memory, but it should be " << whatItShouldBe << " bytes." << endl;
		return false;
	}
}



//This helps with testing, do not modify.
void testCustomStack() {
	
	string result;
	string caughtError;
	CustomStack<int> *stack = new CustomStack<int>(5);

	stack->push(1);
	int data = stack->pop();
	checkTest("testCustomStack #1", 1, data);

	stack->push(1);
	stack->push(2);
	stack->push(3);
	stack->push(4);
	stack->push(5);
	checkTest("testCustomStack #2", 5, stack->pop());
	checkTest("testCustomStack #3", 4, stack->pop());
	checkTest("testCustomStack #4", 3, stack->pop());
	checkTest("testCustomStack #5", 2, stack->pop());
	checkTest("testCustomStack #6", 1, stack->pop());

	//now cover error handling
	try {
		result = stack->pop();
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testCustomStack #7", "caught", caughtError);

	//check currentSize
	checkTest("testCustomStack #8", 0, stack->size());
	stack->push(12);
	stack->push(32);
	checkTest("testCustomStack #9", 2, stack->size());

	//now test filling it up
	stack->push(14);
	stack->push(53);
	stack->push(47);
	checkTest("testCustomStack #10", 5, stack->size());

	//now cover error handling
	caughtError = "";
	try {
		stack->push(8);
	}
	catch (int e) {
		caughtError = "caught";
	}
	checkTest("testCustomStack #11", "caught", caughtError);

	delete stack;

	//test some strings
	CustomStack<string> *sstack = new CustomStack<string>(10);

	sstack->push("apple");
	sstack->push("banana");
	sstack->push("cherry");

	checkTest("testCustomStack #12", 3, sstack->size());

	//remove banana from the stack.
	string temp = sstack->pop();
	sstack->pop();
	sstack->push(temp);

	//see if it worked 
	checkTest("testCustomStack #13", "cherry", sstack->pop());
	checkTest("testCustomStack #14", "apple", sstack->pop());

	delete sstack;
	
}



//This helps with testing, do not modify.
void testCustomQueue() {
	
	string result;
	string caughtError;
	CustomQueue<string> *pQueue = new CustomQueue<string>(5);

	//Tests push_back
	pQueue->push_back("penny");
	pQueue->push_back("nickel");
	pQueue->push_back("dime");
	pQueue->push_back("quarter");

	checkTest("testCustomQueue #1", 4, pQueue->size());

	checkTest("testCustomQueue #2", "penny", pQueue->pop_front());
	checkTest("testCustomQueue #3", 3, pQueue->size());

	checkTest("testCustomQueue #4", "nickel", pQueue->pop_front());
	checkTest("testCustomQueue #5", "dime", pQueue->pop_front());
	checkTest("testCustomQueue #6", "quarter", pQueue->pop_front());
	checkTest("testCustomQueue #7", 0, pQueue->size());

	caughtError = "not caught";
	try {
	result = pQueue->pop_front();
	} catch (int e) {
	caughtError = "caught";
	}
	checkTest("testCustomQueue #8", "caught", caughtError);
	checkTest("testCustomQueue #9", 0, pQueue->size());

	//Try it again.  This should make it wrap around, and fill up.
	pQueue->push_back("penny");
	pQueue->push_back("nickel");
	pQueue->push_back("dime");
	pQueue->push_back("quarter");

	checkTest("testCustomQueue #10", "penny", pQueue->pop_front());
	pQueue->push_back("half dollar");
	pQueue->push_back("silver dollar");

	//It should be full, no more room to add more.
	caughtError = "not caught";
	try {
	pQueue->push_back("million dollar bill");
	} catch (int e) {
	caughtError = "caught";
	}
	checkTest("testCustomQueue #11", "caught", caughtError);

	checkTest("testCustomQueue #12", "nickel", pQueue->pop_front());
	checkTest("testCustomQueue #13", "dime", pQueue->pop_front());
	checkTest("testCustomQueue #14", "quarter", pQueue->pop_front());
	checkTest("testCustomQueue #15", "half dollar", pQueue->pop_front());
	checkTest("testCustomQueue #16", "silver dollar", pQueue->pop_front());
	caughtError = "not caught";
	try {
	result = pQueue->pop_front();
	} catch (int e) {
	caughtError = "caught";
	}
	checkTest("testCustomQueue #17", "caught", caughtError);

	//Test adding and removing back and forth
	pQueue->push_back("penny");
	checkTest("testCustomQueue #18", "penny", pQueue->pop_front());
	pQueue->push_back("nickel");
	checkTest("testCustomQueue #19", "nickel", pQueue->pop_front());
	pQueue->push_back("dime");
	checkTest("testCustomQueue #20", "dime", pQueue->pop_front());
	pQueue->push_back("quarter");
	checkTest("testCustomQueue #21", "quarter", pQueue->pop_front());
	pQueue->push_back("half dollar");
	checkTest("testCustomQueue #22", "half dollar", pQueue->pop_front());
	pQueue->push_back("silver dollar");
	checkTest("testCustomQueue #23", 1, pQueue->size());

	checkTest("testCustomQueue #24", "silver dollar", pQueue->pop_front());
	caughtError = "not caught";
	try {
	result = pQueue->pop_front();
	} catch (int e) {
	caughtError = "caught";
	}
	checkTest("testCustomQueue #25", "caught", caughtError);

	delete pQueue;
	
}

void pressAnyKeyToContinue() {
	cout << "Press any key to continue...";

	//Linux and Mac users with g++ don't need this
	//But everyone else will see this message.
#ifndef __GNUC__
	_getch();

#else
	int c;
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));
#endif
	cout << endl;
}


int main() {

	testCustomStack();
	pressAnyKeyToContinue();
	//testCustomQueue();
	//pressAnyKeyToContinue();

	return 0;
}