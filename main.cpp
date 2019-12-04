#include "MST.h"
#include "Utility.h"
#include <exception>
#include <fstream>
#include <iostream>

using std::cout; using std::endl;
using std::exception;
using std::ifstream; using std::ofstream;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "usage: mst <infile> <outfile>" << endl;
		return 1;
	}

	try
	{
		ifstream infile{ argv[1] };
		if (!infile.is_open())
			throw Error{ "Could not open infile!" };

		ofstream outfile{ argv[2] };
		if (!outfile.is_open())
			throw Error{ "Could not open oufile!" };

		MST m{ infile };
		m.save(outfile);
	}
	catch (Error & e)
	{
		cout << e.what() << endl;
		return 1;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cout << "Unhandled exception caught!" << endl;
		return 1;
	}

	return 0;
}
