#include <string>
#include <iostream>
#include "Counter.h"

using namespace std;
using namespace zyd2001::word_freq_count;

int main()
{
	Counter counter;
	counter.setFile("input.txt");
	resultType result = counter.count();
	for (auto iter = result.cbegin(); iter != result.cend(); ++iter)
	{
		cout << iter->first << "\t";
		cout << iter->second << endl;
	}
}