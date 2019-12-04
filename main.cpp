#include "MST.h"
#include <fstream>

using std::ifstream; using std::ofstream;

int main()
{
	ifstream infile{ "./sample1/sample1_in.txt" };
	MST m{ infile };

	ofstream outfile{ "./sample1/sample1_out.txt" };
	m.save(outfile);

	return 0;
}
