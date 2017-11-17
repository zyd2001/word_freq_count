#include <string>
#include <iostream>
#include "Counter.h"

using namespace std;
using namespace zyd2001::word_freq_count;

int main(int argc, char **argv)
{
	Counter counter;
	string input, output;
	char choice;
	cout << "Initialized!" << endl;
	cout << "Enter in the output file name(don't include suffix): ";
	cin >> output;
	ofstream out(output + ".csv");
	while (true)
	{
		cout << "Enter in the input file name: ";
		cin >> input;
		counter.setFile(input);
		resultType result = counter.count(true);
		cout << "More input files? (Y/N): ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			continue;
		for (auto iter = result.cbegin(); iter != result.cend(); ++iter)
		{
			out << iter->first << ",";
			out << iter->second << endl;
		}
		break;
	}
}