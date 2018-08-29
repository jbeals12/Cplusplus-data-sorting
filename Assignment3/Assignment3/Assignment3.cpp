/*
Aaron Shaneen
CS 2130 SUM' 15
Assignment #3
*/

//Copyright 2015, Bradley Peterson, Weber State University, All rights reserved.

#include <iostream>

//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <cstdio>
#endif

#include <sstream>

using namespace std;

#include <map>

//************************************************************************
//A class I designed to help keep track of how much memory you allocate
//Do not modify, this is not part of your assignment, it just helps test it.
//For this to work, a class needs to inherit off of this one. 
//Then this does the rest of the work, since it 
//overloads new, new[], delete, and delete[].
//************************************************************************
class manageMemory {
public:

	static std::size_t getTotalSize() {
		std::size_t total = 0;
		std::map<void *, std::size_t>::iterator iter;
		for (iter = mapOfAllocations.begin(); iter != mapOfAllocations.end(); ++iter) {
			total += iter->second;
		}
		return total;
	}

	//I overloaded the new and delete keywords so I could manually track allocated memory.
	void* operator new(std::size_t x){
		void *ptr = ::operator new(x);
		mapOfAllocations[ptr] = x;
		return ptr;
	}
	void* operator new[](std::size_t x) {
		void *ptr = ::operator new[](x);
		mapOfAllocations[ptr] = x;
		return ptr;
	}
	void operator delete(void* x) {
		mapOfAllocations.erase(x);
		::operator delete(x);
	}
	void operator delete[](void* x) {
		mapOfAllocations.erase(x);
		::operator delete[](x);
	}
private:
	static std::map<void *, std::size_t> mapOfAllocations;
};
std::map<void *, std::size_t> manageMemory::mapOfAllocations;

//******************
//The node class
//******************
template <typename T>
class nodeType : public manageMemory {
public:
	T info;
	nodeType *link;
};

//******************
//The linked list base class
//This contains within it a class declaration for an iterator
//******************
template <typename T>
class singlyLinkedList : public manageMemory  {
public:

	//public members of the singlyLinkedList class
	singlyLinkedList();
	~singlyLinkedList();
	string getStringFromList();

	void insertFirst(const T&);
	void insertLast(const T&);
	void insertValueAt(const unsigned int index, const T& value);    //For your assignment
	T getValueAt(const unsigned int index);                          //For your assignment
	T& operator[](const unsigned int index);                         //For your assignment
	void deleteValueAt(const unsigned int index);                    //For your assignment
	void deleteAllOfOccurrence(const T& value);                      //For your assignment

protected:
	nodeType<T> *first;
	nodeType<T> *last;
	int count;
};

template <typename T>
singlyLinkedList<T>::singlyLinkedList() {
	first = NULL;
	last = NULL;
	count = 0;
}

template <typename T>
singlyLinkedList<T>::~singlyLinkedList() {
	nodeType<T> *temp;
	while (first != NULL) {
		temp = first;
		first = first->link;
		delete temp;
	}
	last = NULL;
	count = 0;
}

template <typename T>
void singlyLinkedList<T>::insertFirst(const T& value) {
	nodeType<T> *temp = new nodeType<T>();
	temp->info = value;
	temp->link = NULL;

	//empty list scenario
	if (first == NULL) {
		last = temp;
	}
	else {
		temp->link = first;
	}

	first = temp;
	count++;
}

template <typename T>
void singlyLinkedList<T>::insertLast(const T& value) {
	nodeType<T> *temp = new nodeType<T>;
	temp->info = value;
	temp->link = NULL;

	if (first == NULL) {
		first = temp;
	}
	else {
		//put it on
		last->link = temp;
	}
	last = temp;
	count++;
}

//TODO: Complete this method
template <typename T>
void singlyLinkedList<T>::insertValueAt(const unsigned int index, const T& value)
{
	nodeType<T> * currNode = first;
	nodeType<T> * prevNode = first;
	int travCount = 0;

	// if index is out of bounds
	// (including the last node)
	if (index > count)
	{
		cout << "The index you entered is out of bounds." << endl;
	}

	// if to insert in the first index
	// or if inserting in an empty list
	else if (index == 0)
	{
		insertFirst(value);
		return;
	}

	// if to insert in the last index
	else if (index == count)
	{
		insertLast(value);
		return;
	}

	// or else traverse to specified index
	else
	{
		// traverses currNode to target node
		while (travCount != index)
		{
			currNode = currNode->link;
			travCount++;
		}

		// reset travCount for prevNode use
		travCount = 0;

		// traverses prevNode to the node prior to the target node
		while (travCount != (index - 1))
		{
			prevNode = prevNode->link;
			travCount++;
		}

		nodeType<T> * temp = new nodeType<T>;
		temp->info = value;
		prevNode->link = temp;
		temp->link = currNode;
		count++;
	}
}

//TODO: Complete this method
template <typename T>
T singlyLinkedList<T>::getValueAt(const unsigned int index)
{
	nodeType<T> * temp = first;
	int travCount = 0;

	// if list is empty
	if (first == NULL)
	{
		throw 1;
	}

	// if index is out of bounds
	else if (index > (count - 1))
	{
		throw 1;
	}

	// or else retrieve info from target node
	else
	{
		while (travCount != index)
		{
			temp = temp->link;
			travCount++;
		}
	}

	return temp->info;
}

//TODO: Complete this method
template <typename T>
T& singlyLinkedList<T>::operator[](const unsigned int index)
{
	nodeType<T> * temp = first;
	int travCount = 0;

	// if list is empty
	if (first == NULL)
	{
		throw 1;
	}

	// if index is out of bounds
	else if (index > (count - 1))
	{
		throw 1;
	}

	// or else retrieve info from target node
	else
	{
		while (travCount != index)
		{
			temp = temp->link;
			travCount++;
		}
	}

	return temp->info;
}

//TODO: Complete this method
template <typename T>
void singlyLinkedList<T>::deleteValueAt(const unsigned int index)
{
	nodeType<T> * currNode = first;
	nodeType<T> * prevNode = first;
	nodeType<T> * temp;
	int travCount = 0;

	// if list is empty
	if (first == NULL)
	{
		cout << "The list is empty." << endl;
	}

	// if index is out of bounds
	// (including the last node)
	else if (index > count)
	{
		cout << "The index you entered is out of bounds." << endl;
	}

	// if deleting on a single node list
	else if (count == 1)
	{
		temp = first;
		first = NULL;
		last = NULL;
		delete temp;
		count--;
	}

	// if deleting first node
	else if (index == 0)
	{
		temp = first;
		first = first->link;
		delete temp;
		count--;
	}

	// if deleting last node
	else if (index == count)
	{
		// traverses currNode to target node
		while (travCount != index)
		{
			currNode = currNode->link;
			travCount++;
		}

		// reset travCount for prevNode use
		travCount = 0;

		// traverses prevNode to the node prior to the target node
		while (travCount != (index - 1))
		{
			prevNode = prevNode->link;
			travCount++;
		}

		last = prevNode;
		last->link = NULL;
		delete currNode;
		count--;
	}

	// or else traverse to the specified index to delete
	else
	{
		// traverses currNode to target node
		while (travCount != index)
		{
			currNode = currNode->link;
			travCount++;
		}

		// reset travCount for prevNode use
		travCount = 0;

		// traverses prevNode to the node prior to the target node
		while (travCount != (index - 1))
		{
			prevNode = prevNode->link;
			travCount++;
		}

		temp = currNode;
		currNode = currNode->link;
		prevNode->link = currNode;
		delete temp;
		count--;
	}
}

//TODO: Complete this method
template <typename T>
void singlyLinkedList<T>::deleteAllOfOccurrence(const T& value)
{
	nodeType<T> * currNode;
	nodeType<T> * prevNode;
	nodeType<T> * temp;

	// if list is empty
	if (first == NULL)
	{
		cout << "The list is empty." << endl;
	}

	// if searching on a single node list
	else if (count == 1)
	{
		currNode = first;

		if (currNode->info == value)
		{
			first = NULL;
			last = NULL;
			delete currNode;
			count--;
		}
	}

	else
	{
		currNode = first;
		prevNode = currNode;

		// loop til the end has been reached
		while (currNode != last)
		{
			// if currNode matches
			if (currNode->info == value)
			{
				// if currNode is first
				if (currNode == first)
				{
					temp = currNode;
					currNode = currNode->link;
					first = currNode;
					delete temp;
					count--;
				}

				// if not first then we're in the middle
				else
				{
					temp = currNode;
					currNode = currNode->link;
					prevNode->link = currNode;
					delete temp;
					count--;
				}
			}

			// if currNode doesn't match then traverse
			else
			{
				prevNode = currNode;
				currNode = currNode->link;
			}
		}

		// if end has been reached and it matches
		if (currNode == last && currNode->info == value)
		{
			last = prevNode;
			prevNode->link = NULL;
			delete currNode;
			count--;
		}
	}
}

//This method helps return a string representation of all nodes in the linked list, do not modify.
template <typename T>
string singlyLinkedList<T>::getStringFromList() {
	stringstream ss;
	if (first == NULL) {
		ss << "The list is empty.";
	}
	else {

		nodeType<T> *currentNode = first;
		ss << currentNode->info;
		currentNode = currentNode->link;

		while (currentNode != NULL) {
			ss << " " << currentNode->info;
			currentNode = currentNode->link;
		};
	}
	return ss.str();
}

//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
		return false;
	}
}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
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
		cout << "***Failed test " << testName << " *** " << endl << "  You lost track of " << whatItIs << " bytes in memory!" << endl;
		return false;
	}
}
//This helps with testing, do not modify.

void testInsertValueAt() {
	singlyLinkedList<int> *s = new singlyLinkedList<int>;
	for (int i = 10; i < 20; i++)  {
		s->insertLast(i);
	}

	//Test just to make sure the data went in the list. 
	checkTest("testInsertValueAt #1", "10 11 12 13 14 15 16 17 18 19", s->getStringFromList());

	s->insertValueAt(3, 33);

	checkTest("testInsertValueAt #2", "10 11 12 33 13 14 15 16 17 18 19", s->getStringFromList());

	s->insertValueAt(0, 9);

	checkTest("testInsertValueAt #3", "9 10 11 12 33 13 14 15 16 17 18 19", s->getStringFromList());

	s->insertValueAt(12, 20);

	checkTest("testInsertValueAt #4", "9 10 11 12 33 13 14 15 16 17 18 19 20", s->getStringFromList());

	delete s;

}

//This helps with testing, do not modify.
void testGetValueAt() {
	singlyLinkedList<int> *d = new singlyLinkedList<int>;
	for (int i = 10; i < 20; i++)  {
		d->insertLast(i);
	}

	//Test just to make sure the data went in the list. 
	checkTest("testGetValueAt #1", "10 11 12 13 14 15 16 17 18 19", d->getStringFromList());

	//Test retrieving items. 
	int item = d->getValueAt(0);
	checkTest("testGetValueAt #2", 10, item);

	item = d->getValueAt(5);
	checkTest("testGetValueAt #3", 15, item);

	item = d->getValueAt(9);
	checkTest("testGetValueAt #4", 19, item);

	//Make sure the list was undisturbed during this time
	checkTest("testGetValueAt #5", "10 11 12 13 14 15 16 17 18 19", d->getStringFromList());

	//Try to access out of bounds.  
	string caughtError = "";
	try {
		int item = d->getValueAt(-1);
	}
	catch (int error) {
		caughtError = "caught";
	}
	checkTest("testGetValueAt #6", "caught", caughtError);

	try {
		int item = d->getValueAt(100);
	}
	catch (int error) {
		caughtError = "caught";
	}
	checkTest("testGetValueAt #7", "caught", caughtError);

	delete d;
}

//This helps with testing, do not modify.
void testOperatorSquareBrackets() {
	singlyLinkedList<int> d;
	for (int i = 10; i < 20; i++)  {
		d.insertLast(i);
	}

	//Test just to make sure the data went in the list. 
	checkTest("testOperatorSquareBrackets #1", "10 11 12 13 14 15 16 17 18 19", d.getStringFromList());

	//Test retrieving items. 
	int item = d[0];
	checkTest("testOperatorSquareBrackets #2", 10, item);

	item = d[5];
	checkTest("testOperatorSquareBrackets #3", 15, item);

	item = d[9];
	checkTest("testOperatorSquareBrackets #4", 19, item);

	//Make sure the list was undisturbed during this time
	checkTest("testOperatorSquareBrackets #5", "10 11 12 13 14 15 16 17 18 19", d.getStringFromList());

	//now test the return by reference
	d[1] = 1000;
	checkTest("testOperatorSquareBrackets #6", "10 1000 12 13 14 15 16 17 18 19", d.getStringFromList());

	//Try to access out of bounds.  
	string caughtError = "";
	try {
		int item = d[-1];
	}
	catch (int error) {
		caughtError = "caught";
	}
	checkTest("testOperatorSquareBrackets #7", "caught", caughtError);

	try {
		int item = d[100];
	}
	catch (int error) {
		caughtError = "caught";
	}
	checkTest("testOperatorSquareBrackets #8", "caught", caughtError);

}

//This helps with testing, do not modify.
void testDeleteValueAt() {
	singlyLinkedList<int> *d = new singlyLinkedList<int>;
	for (int i = 10; i < 17; i++)  {
		d->insertLast(i);
	}

	//Test just to make sure the data went in the list. 
	checkTest("testDeleteValueAt #1", "10 11 12 13 14 15 16", d->getStringFromList());

	//Test deleting front items. 
	d->deleteValueAt(0);
	checkTest("testDeleteValueAt #2", "11 12 13 14 15 16", d->getStringFromList());

	d->deleteValueAt(0);
	checkTest("testDeleteValueAt #3", "12 13 14 15 16", d->getStringFromList());

	//Test deleting back itmes
	d->deleteValueAt(4);
	checkTest("testDeleteValueAt #4", "12 13 14 15", d->getStringFromList());

	d->deleteValueAt(3);
	checkTest("testDeleteValueAt #5", "12 13 14", d->getStringFromList());

	//Test deleting a Kth element that doesn't exist.
	d->deleteValueAt(500);
	checkTest("testDeleteValueAt #6", "12 13 14", d->getStringFromList());

	//Test deleting middle item
	d->deleteValueAt(1);
	checkTest("testDeleteValueAt #7", "12 14", d->getStringFromList());

	//Test deleting item on the back
	d->deleteValueAt(1);
	checkTest("testDeleteValueAt #8", "12", d->getStringFromList());

	//Test deleting item on the front
	d->deleteValueAt(0);
	checkTest("testDeleteValueAt #9", "The list is empty.", d->getStringFromList());

	//Test attempting to delete from an empty list
	d->deleteValueAt(0);
	checkTest("testDeleteValueAt #10", "The list is empty.", d->getStringFromList());

	delete d;
}

//This helps with testing, do not modify.
void testDeleteAllOfOccurrence() {

	singlyLinkedList<int> *d = new singlyLinkedList<int>;

	d->insertLast(4);
	d->insertLast(2);
	d->insertLast(6);
	d->insertLast(5);
	d->insertLast(6);
	d->insertLast(9);

	//Do a delete, test it.
	d->deleteAllOfOccurrence(6);
	checkTest("testDeleteAllOfOccurrence #1", "4 2 5 9", d->getStringFromList());

	delete d;
	d = new singlyLinkedList<int>;
	d->insertLast(4);
	d->insertLast(2);
	d->insertLast(3);
	d->insertLast(4);
	d->insertLast(4);
	d->insertLast(4);
	d->insertLast(9);
	d->deleteAllOfOccurrence(4);
	checkTest("testDeleteAllOfOccurrence #2", "2 3 9", d->getStringFromList());

	delete d;
	d = new singlyLinkedList<int>;
	d->insertLast(3);
	d->insertLast(3);
	d->insertLast(3);
	d->insertLast(8);
	d->insertLast(2);
	d->insertLast(3);
	d->insertLast(3);
	d->insertLast(3);
	d->deleteAllOfOccurrence(3);
	checkTest("testDeleteAllOfOccurrence #3", "8 2", d->getStringFromList());

	delete d;
	d = new singlyLinkedList<int>;
	d->insertLast(9);
	d->insertLast(9);
	d->insertLast(4);
	d->insertLast(2);
	d->insertLast(9);
	d->insertLast(9);
	d->insertLast(5);
	d->insertLast(1);
	d->insertLast(9);
	d->insertLast(2);
	d->insertLast(9);
	d->insertLast(9);

	//Do a delete, test it.
	d->deleteAllOfOccurrence(9);
	checkTest("testDeleteAllOfOccurrence #4", "4 2 5 1 2", d->getStringFromList());

	//Test deleting something that doesn't exist
	d->deleteAllOfOccurrence(7);
	checkTest("testDeleteAllOfOccurrence #5", "4 2 5 1 2", d->getStringFromList());

	//A few more tests
	d->deleteAllOfOccurrence(2);
	checkTest("testDeleteAllOfOccurrence #6", "4 5 1", d->getStringFromList());

	d->deleteAllOfOccurrence(4);
	checkTest("testDeleteAllOfOccurrence #7", "5 1", d->getStringFromList());

	d->deleteAllOfOccurrence(5);
	checkTest("testDeleteAllOfOccurrence #8", "1", d->getStringFromList());

	d->deleteAllOfOccurrence(1);
	checkTest("testDeleteAllOfOccurrence #9", "The list is empty.", d->getStringFromList());

	//retest deleting something that doesn't exist.
	d->deleteAllOfOccurrence(7);
	checkTest("testDeleteAllOfOccurrence #10", "The list is empty.", d->getStringFromList());

	delete d;

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

}

int main() {

	// Each of these checks how many bytes you have used.
	checkTestMemory("Memory Leak/Allocation Test #1", 0, manageMemory::getTotalSize());

	testInsertValueAt();

	checkTestMemory("Memory Leak/Allocation Test #2", 0, manageMemory::getTotalSize());

	testGetValueAt();

	checkTestMemory("Memory Leak/Allocation Test #3", 0, manageMemory::getTotalSize());

	testOperatorSquareBrackets();

	checkTestMemory("Memory Leak/Allocation Test #4", 0, manageMemory::getTotalSize());

	testDeleteValueAt();

	checkTestMemory("Memory Leak/Allocation Test #5", 0, manageMemory::getTotalSize());

	testDeleteAllOfOccurrence();

	checkTestMemory("Memory Leak/Allocation Test #6", 0, manageMemory::getTotalSize());

	pressAnyKeyToContinue();

	return 0;
}