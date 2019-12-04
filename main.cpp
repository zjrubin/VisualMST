#include "MST.h"
#include <iostream>
#include <fstream>

using std::cout; using std::endl;

using namespace std;

int main()
{
	cout << "Hello world" << endl;

	ifstream infile{ "./sample1/points_in.txt" };
	MST{ infile };

	return 0;
}