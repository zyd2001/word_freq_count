#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

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

class findstorage
{
public:
	findstorage(string st) :str(st) {}
	bool operator()(storage s) { return (s.name) == str; }
private:
	string str;
};

class findstr
{
public:
	findstr(string st) : str(st) {}
	bool operator()(string s) { return s == str; }
private:
	string str;
};

class findlem
{
public:
	findlem(string st) : str(st) {}
	bool operator()(slist s) 
	{
		if (s.head == str)
			return true;
		else
		{
			vector<string>::iterator result = find_if(s.var.begin(), s.var.end(), findstr(str));
			if (result == s.var.end())
				return false;
			else
				return true;
		}
	}
private:
	string str;
};

int main()
{
	ifstream fin, fsave, flemm("2+2+3lem.txt");
	ofstream fout;
	string temp, filename;
	int count = 0;
	vector<storage>::iterator result;
	cout << "Program is initializing."<< endl;
	readLem(flemm);
	fsave.open("save.txt");
	if (fsave.is_open())
	{
		fprocess(fsave);
	}
	cout << "Initialization successful! Please enter the file name(q to quit): " ;
	cin >> filename;
	while (filename != "q")
	{
		fin.open(filename.c_str());
		while (fin >> temp)
		{
			count++;
			if (count % 100 == 0)
				cout << "processed " << count << "words" << endl;
			temp = process(temp);
			if (temp.size() == 0)
				continue;
			result = find_if(vi.begin(), vi.end(), findstorage(temp));
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
		int i;
		for (i = 0; i < vi.size() - 1; i++)
		{
			fout << vi[i].name << "\t" << vi[i].num << endl;
		}
		fout << vi[i].name << "\t" << vi[i].num;
		fout.close();
		fin.close();
		cout << "The output is saved in save.txt! Please enter next file name(q to quit): ";
		cin >> filename;
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
	vector<slist>::iterator result = find_if(vlem.begin(), vlem.end(), findlem(str));
	if (result == vlem.end())
		return str;
	else
	{
		str = result->head;
		return str;
	}
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