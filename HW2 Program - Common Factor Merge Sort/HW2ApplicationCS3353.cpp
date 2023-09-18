// HW2ApplicationCS3353.cpp Brendan Bovenschen CWID: A20323473

#include <iostream>
#include <list>
using namespace std;

//Function to multiply a list by a constant integer i
list<int> ListMultipy(list<int> li, int i) {
	//Pre: list li, integer i

	//iterate through each element, multiply by i
	for (list<int>::iterator it = li.begin(); it != li.end(); ++it) {
		*it = *it * i;
	}
	return li;
	//Post: li = li * i
}

//Merge two sorted lists with no duplicate elements
list<int> Merge(list<int> listA, list<int> listB) {
	//Pre: empty list lI, sorted lists listA and listB

	list <int> lI;
	list<int>::iterator iA = listA.begin();
	list<int>::iterator iB = listB.begin();

	while(iA != listA.end() || iB != listB.end()) {

		if (iA == listA.end() || (iB != listB.end() && *iB < *iA) ) {
			lI.push_back(*iB);
			++iB;
		}

		else if (iB == listB.end() || * iB > *iA) {
			lI.push_back(*iA);
			++iA;
		}
		else {
			lI.push_back(*iB);
			++iA;
			++iB;
		}
	}
	return lI;
	//Post: list lI is merger of listA and listB with no duplicaes from least to greatest
}


int main()
{
start:

	list<int> lFinal;
	list<int> lTemp = {2,3,5};
	list<int> l2, l3, l5;
	int n;

	//User prompt
	cout << "Please enter the length \'n\' list you wish to produce (-1 to exit program): ";
	cin >> n;

	if (n < 0) return 0;

	lFinal = Merge(lFinal, lTemp);

	//Calculate the amount of iterations for the main loop (see more in documentation)
	int itr = 0;
	for (int i = 3; i <= n; ++itr) {
		i = i + (2 * (itr + 1) + 1);
	}

	//Pre: lFinal, l2, l3, l5 are empty, lTemp = {2,3,5}, number of iterations h
	for (int i = 0; i < itr; ++i) {
		
		l2 = ListMultipy(lTemp, 2);

		 l3 = ListMultipy(lTemp, 3);

		 l5 = ListMultipy(lTemp, 5);
		 
		lTemp.clear();

		lTemp = Merge(l2, l3);
		lTemp = Merge(lTemp, l5);

		//lFinal = MergeFinal(lFinal, lTemp, n);
		lFinal = Merge(lFinal, lTemp);
	}

	//Cut the final list to the correct size
	lFinal.resize(n);

	//Post: l2 = lTemp * 2, l3 = lTemp * 3, l5 = lTemp * 5, lFinal = l2 merge l3 merge l5

	//Iterate through and print each element of the final list
	for (list<int>::iterator iT = lFinal.begin(); iT != lFinal.end(); ++iT) {
		cout << *iT << " ";
	}

	cout << "\n";

	goto start;
}
