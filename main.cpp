#include <string>
#include <iostream>
#include "Counter.h"

using namespace std;
using namespace zyd2001::word_freq_count;

void outputFile(ofstream &os, resultType &result)
{
	for (auto iter = result.cbegin(); iter != result.cend(); ++iter)
	{
		os << iter->first << ",";
		os << iter->second << endl;
	}
}

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
		if (!counter.setFile(input))
		{
			cout << "Cannot open the input file, try again? (Y/N): ";
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
				continue;
			else
			{
				outputFile(out, counter.result);
				break;
			}
				
		}
		counter.count(true);
		cout << "More input files? (Y/N): ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			continue;
		else
		{
			outputFile(out, counter.result);
			break;
		}
	}
}