/*
Aaron Shaneen
CS 2420
Assignment 8
*/

#include <iostream>
#include <string>
//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using namespace std;

void pressAnyKeyToContinue() {
	printf("Press any key to continue\n");

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

// This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs)
{
	if (whatItShouldBe == whatItIs)
	{
		cout << "Passed " << testName << endl;
		return true;
	}

	else
	{
		cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
		return false;
	}
}

template <typename T>
class node
{
public:

	T info;
	node<T>* llink;
	node<T>* rlink;
};

template <typename T>
class binaryTree
{
public:

	binaryTree();
	void insert(const T& insertItem);
	void postOrder() const;
	int nodeCount() const;
	int leavesCount() const;
	int singleChildCount() const;
	int levelCount(int targetLevel);

private:

	node<T> *root;
	void postOrder(node<T> *p) const;
	int nodeCount(node<T> *p) const;
	int leavesCount(node<T> *p) const;
	int singleChildCount(node<T> *p) const;
	int levelCount(node<T> *p, int currlevel, int targetLevel);
};

template <typename T>
binaryTree<T>::binaryTree()
{
	root = NULL;
}

template <typename T>
void binaryTree<T>::insert(const T& insertItem)
{
	node<T> *newNode = new node<T>();
	newNode->info = insertItem;
	newNode->llink = NULL;
	newNode->rlink = NULL;

	if (root == NULL)
	{
		root = newNode;
		return;
	}

	node<T> *current = root;
	node<T> *trailCurrent = NULL;

	while (current != NULL)
	{
		trailCurrent = current;

		if (current->info > insertItem)
		{
			current = current->llink;
		}

		else
		{
			current = current->rlink;
		}
	}

	// trailCurrent points to the last node in the
	// branch where we can stick a new node onto
	if (trailCurrent->info > insertItem)
	{
		//stick it on the left
		trailCurrent->llink = newNode;
	}

	else
	{
		trailCurrent->rlink = newNode;
	}
}

// postOrder()
template <typename T>
void binaryTree<T>::postOrder() const
{
	// This just gets it started
	postOrder(root);
}

template <typename T>
void binaryTree<T>::postOrder(node<T> *p) const
{
	if (p != NULL)
	{
		postOrder(p->llink);
		postOrder(p->rlink);
		cout << p->info << " ";
	}
}

// nodeCount()
template <typename T>
int binaryTree<T>::nodeCount() const
{
	int count = 0;

	count += nodeCount(root);

	return count;
}

template <typename T>
int binaryTree<T>::nodeCount(node<T> * ptr) const
{
	int count = 0;

	if (ptr != NULL)
	{
		count = nodeCount(ptr->llink);
		count += nodeCount(ptr->rlink);
		return 1 + count;
	}

	return 0;
}

// leavesCount()
template <typename T>
int binaryTree<T>::leavesCount() const
{
	int count = 0;

	count += leavesCount(root);

	return count;
}

template <typename T>
int binaryTree<T>::leavesCount(node<T> * ptr) const
{
	int count = 0;

	if (ptr != NULL)
	{
		count = leavesCount(ptr->llink);
		count += leavesCount(ptr->rlink);

		if (ptr->llink == NULL && ptr->rlink == NULL)
		{
			count += 1;
		}

		return count;
	}

	return 0;
}

// singleChildCount()
template <typename T>
int binaryTree<T>::singleChildCount() const
{
	int count = 0;

	count += singleChildCount(root);

	return count;
}

template <typename T>
int binaryTree<T>::singleChildCount(node<T> * ptr) const
{
	int count = 0;

	if (ptr != NULL)
	{
		count = singleChildCount(ptr->llink);
		count += singleChildCount(ptr->rlink);

		if (ptr->llink != NULL && ptr->rlink == NULL)
		{
			count += 1;
		}

		if (ptr->llink == NULL && ptr->rlink != NULL)
		{
			count += 1;
		}

		return count;
	}

	return 0;
}

// levelCount()
template <typename T>
int binaryTree<T>::levelCount(int targetLevel)
{
	int count = 0;

	count += levelCount(root, 1, targetLevel);

	return count;
}

template <typename T>
int binaryTree<T>::levelCount(node<T> * ptr, int currLevel, int targetLevel)
{
	int count = 0;

	if (ptr != NULL)
	{
		if (currLevel <= targetLevel)
		{
			count = levelCount(ptr->llink, currLevel + 1, targetLevel);
			count += levelCount(ptr->rlink, currLevel + 1, targetLevel);
			count + 1;

			if (currLevel == targetLevel)
			{
				count += 1;
			}

			return count;
		}
	}

	return 0;
}

int main()
{
	binaryTree<int> myTree;

	myTree.insert(37);
	myTree.insert(32);
	myTree.insert(73);
	myTree.insert(95);
	myTree.insert(42);
	myTree.insert(12);
	myTree.insert(00);
	myTree.insert(49);
	myTree.insert(98);
	myTree.insert(7);
	myTree.insert(27);
	myTree.insert(17);
	myTree.insert(47);
	myTree.insert(87);
	myTree.insert(77);
	myTree.insert(97);
	myTree.insert(67);
	myTree.insert(85);
	myTree.insert(15);
	myTree.insert(5);
	myTree.insert(35);
	myTree.insert(55);
	myTree.insert(65);
	myTree.insert(75);
	myTree.insert(25);
	myTree.insert(45);
	myTree.insert(3);
	myTree.insert(93);
	myTree.insert(83);
	myTree.insert(53);
	myTree.insert(63);
	myTree.insert(23);
	myTree.insert(13);
	myTree.insert(43);
	myTree.insert(33);

	myTree.postOrder();

	//******************************************************************************
	// NOTE: Global variables are not allowed to solve these problems.
	// Class data members which store accumulated counts are also not allowed.  
	// Storing your counts in parameters that pass by reference is also not allowed.
	// Your counting needs to be done through accumulating recursive return values.
	//******************************************************************************

	checkTest("Test #1, number of nodes", 35, myTree.nodeCount());
	checkTest("Test #2, number of leaves, (i.e. nodes with no children)", 11, myTree.leavesCount());
	checkTest("Test #3, number of nodes with one child", 14, myTree.singleChildCount());
	checkTest("Test #4, number of nodes on level 1 (the root level)", 1, myTree.levelCount(1));
	checkTest("Test #5, number of nodes on level 2", 2, myTree.levelCount(2));
	checkTest("Test #6, number of nodes on level 3", 4, myTree.levelCount(3));
	checkTest("Test #7, number of nodes on level 4", 6, myTree.levelCount(4));
	checkTest("Test #8, number of nodes on level 5", 7, myTree.levelCount(5));
	checkTest("Test #9, number of nodes on level 6", 7, myTree.levelCount(6));
	checkTest("Test #10, number of nodes on level 7", 7, myTree.levelCount(7));
	checkTest("Test #11, number of nodes on level 8", 1, myTree.levelCount(8));
	checkTest("Test #12, number of nodes on level 9", 0, myTree.levelCount(9));

	pressAnyKeyToContinue();
	return 0;
}