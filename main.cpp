#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

struct slist
{
	string head;
	vector<string> var;
};

struct storage
{
	string name;
	int num;
};

vector<storage> vi;
vector<slist> vlem;

void fprocess(ifstream&);
//void outfile(ofstream&);
//string lower(string);
string process(string);
void readLem(ifstream&);

class findstr
{
public:
	findstr(string st) :str(st) {}
	bool operator()(storage s) { return (s.name) == str; }
private:
	string str;
};

int main(int argc, char* argv[])
{
	ifstream fin, fsave, flemm("2+2+3lem.txt");
	ofstream fout;
	string temp, filename;
	if (argc == 2)
		filename = argv[1];
	else
		filename = "input.txt";
	vector<storage>::iterator result;
	readLem(flemm);
	fin.open(filename.c_str());
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
		if (str.substr(i, 2) == "\'s" || str.substr(i, 2) == "\'d" || str.substr(i, 2) == "\'m")
		{
			str.erase(i, 2);
			i--;
			continue;
		}
		if (str.substr(i, 3) == "n\'t" || str.substr(i, 3) == "\'ve" || str.substr(i, 3) == "\'ll")
		{
			str.erase(i, 3);
			i--;
			continue;
		}
		if (!isalpha(str[i]) && str[i] != '-')
		{
			str.erase(i, 1);
			i--;
			continue;
		}
		str[i] = tolower(str[i]);
	}
	return str;
}

void readLem(ifstream &fin)
{
	string strtemp;
	fin >> strtemp;
	while (fin.peek() != EOF)
	{
		slist temp;
		temp.head = strtemp;
		fin >> strtemp;
		if (strtemp[0] == '#')
		{
			string sub;
			sub = strtemp.substr(1, strtemp.size());
			int index = sub.find('#', 0);
			while (index != sub.npos)
			{
				temp.var.push_back(sub.substr(0, index));
				sub = sub.substr(index + 1, sub.size());
				index = sub.find('#', 0);
			}
			temp.var.push_back(sub);
			vlem.push_back(temp);
			fin >> strtemp;
		}
		else
		{
			vlem.push_back(temp);
			continue;
		}
	}
}