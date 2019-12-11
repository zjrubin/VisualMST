#include "getopt.h"
#include "Held_Karp_TSP.h"
#include "Kruskals_MST.h"
#include "Prims_MST.h"
#include "Utility.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using std::cout; using std::endl;
using std::exception;
using std::ifstream; using std::ofstream;
using std::string;
using std::unique_ptr; using std::make_unique;

void run(const string& infile_name, const string& outfile_name, const string& algorithm);
unique_ptr<Graph> create_Graph(ifstream& infile, const string& algorithm);

int main(int argc, char* argv[])
{
	try
	{
		int option_index = 0;
		int option = 0;

		// use getopt to find command line options
		struct option longOpts[] = {
			{"infile", required_argument, nullptr, 'i'},
			{"outfile", required_argument, nullptr, 'o'},
			{ "mode", required_argument, nullptr, 'm' },
			{ "help", no_argument, nullptr, 'h' },
			{ nullptr, 0, nullptr, '\0' }
		};

		string algorithm, infile, outfile;
		bool i_seen = false, o_seen = false, m_seen = false;
		while ((option = getopt_long(argc, argv, "i:o:m:h", longOpts, &option_index)) != -1)
		{
			switch (option)
			{
			case 'i':
				i_seen = true;
				infile = optarg;
				break;
			case 'o':
				o_seen = true;
				outfile = optarg;
				break;
			case 'm':
				m_seen = true;
				algorithm = optarg;
				break;
			case 'h':
			default:
				throw Error{ "Usage: " + string{argv[0]} + " -m <prims|kruskals> -i <infile> -o <outfile>" };
				break;
			}
		}

		if (!i_seen || !o_seen || !m_seen) // Make sure all required options have been seen
			throw Error{ "Usage: " + string{argv[0]} + " -m <prims|kruskals> -i <infile> -o <outfile>" };

		run(infile, outfile, algorithm);
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

void run(const string& infile_name, const string& outfile_name, const string& algorithm)
{
	ifstream infile{ infile_name };
	if (!infile.is_open())
		throw Error{ "Could not open infile!" };

	unique_ptr<Graph> mst_ptr = create_Graph(infile, algorithm);

	ofstream outfile{ outfile_name };
	if (!outfile.is_open())
		throw Error{ "Could not open oufile!" };

	mst_ptr->save(outfile);
}

unique_ptr<Graph> create_Graph(ifstream& infile, const string& algorithm)
{
	if (algorithm == "prims")
		return make_unique<Prims_MST>(infile);
	else if (algorithm == "kruskals")
		return make_unique<Kruskals_MST>(infile);
	else if (algorithm == "held-karp")
		return make_unique<Held_Karp_TSP>(infile);
	else
		throw Error{ "Invalid algorithm choice!\nValid options are: prims|kruskals" };
}
