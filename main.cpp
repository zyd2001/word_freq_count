#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

struct storage
{
	string name;
	int num;
};

vector<storage> vi;

void fprocess(ifstream&);
//void outfile(ofstream&);
//string lower(string);
string process(string);

class findstr
{
public:
	findstr(string st) :str(st) {}
	bool operator()(storage s) { return (s.name) == str; }
private:
	string str;
};

int main()
{
	ifstream fin("input.txt"), fsave;
	ofstream fout;
	string temp;
	vector<storage>::iterator result;
	fsave.open("save.txt");
	if (fsave.is_open())
	{
		fprocess(fsave);
	}
	while (fin >> temp)
	{
		temp = process(temp);
		if (temp.size() == 0)
			continue;
		result = find_if(vi.begin(), vi.end(), findstr(temp));
		if (result == vi.end())
		{
			storage s = { temp, 1 };
			vi.push_back(s);
		}
		else
		{
			result->num++;
		}
	}
	fout.open("save.txt");
	for (int i = 0; i < vi.size(); i++)
	{
		fout << vi[i].name << "\t" << vi[i].num << endl;
	}
	return 0;
}

void fprocess(ifstream & fin)
{
	int tnum;
	string tstr;
	while (fin.peek() != EOF)
	{
		fin >> tstr;
		fin >> tnum;
		storage s = { tstr, tnum };
		vi.push_back(s);
	}
}

string process(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (!isalpha(str[i])) 
		{
			str.erase(i, 1);
			i--;
		}
		str[i] = tolower(str[i]);
	}
	return str;
}