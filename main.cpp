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

struct sl
{
	string name;
	string head;

	bool operator!=(string s) const
	{
		return name != s;
	}
	bool operator==(string s) const
	{
		return name == s;
	}
	bool operator>(sl s) const
	{
		return this->name > s.name;
	}
	bool operator<(sl s) const
	{
		return this->name < s.name;
	}
	bool operator>(string s) const
	{
		return this->name > s;
	}
	bool operator<(string s) const
	{
		return this->name < s;
	}
};

vector<storage> vi;
vector<slist> vlem;
vector<sl> vl;

void fprocess(ifstream&);
//void outfile(ofstream&);
//string lower(string);
string process(string);
void readLem(ifstream&);
void sprocess();
string binarySearch(string);

bool comp(const sl &a, const sl &b)
{
	return a.name < b.name;
}

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
	string temp, filename, filename_save;
	//int count = 0;
	vector<storage>::iterator result;
	cout << "Enter the save file name: ";
	cin >> filename_save;
	cout << "Program is initializing." << endl;
	readLem(flemm);
	sprocess();
	vl.erase(vl.begin());
	vlem.clear();
	fsave.open(filename_save.c_str());
	if (fsave.is_open())
	{
		fprocess(fsave);
	}
	cout << "Initialization successful! Please enter the file name(q to quit): ";
	cin >> filename;
	while (filename != "q")
	{
		fin.open(filename.c_str());
		while (fin >> temp)
		{
			/*count++;
			if (count % 100 == 0)
				cout << "processed " << count << "words" << endl;*/
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
		fout.open(filename_save.c_str());
		int i;
		for (i = 0; i < vi.size() - 1; i++)
		{
			fout << vi[i].name << "\t" << vi[i].num << endl;
		}
		fout << vi[i].name << "\t" << vi[i].num;
		fout.close();
		fin.close();
		cout << "The output is saved in " << filename_save <<"! Please enter next file name(q to quit): ";
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
	if (str == "I")
		goto skip;
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
skip:
	/*vector<slist>::iterator result = find_if(vlem.begin(), vlem.end(), findlem(str));
	if (result == vlem.end())
		return str;
	else
	{
		str = result->head;
		return str;
	}*/
	str = binarySearch(str);
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

void sprocess()
{
	int size = vlem.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < vlem[i].var.size(); j++)
		{
			sl temp;
			temp.name = vlem[i].var[j];
			temp.head = vlem[i].head;
			vl.push_back(temp);
		}
		sl temp;
		temp.name = vlem[i].head;
		temp.head = vlem[i].head;
		vl.push_back(temp);
	}
	sort(vl.begin(), vl.end(), comp);
}

string binarySearch(string s)
{
	int size = vl.size();
	int front = 0;
	int back = size - 1;
	int mid = size / 2;
	while (vl[front] < vl[back] && vl[mid] != s)
	{
		if (vl[mid] > s)
			back = mid - 1;
		if (vl[mid] < s)
			front = mid + 1;
		if (back < 0)
			back = 0;
		if (front > vl.size())
			front = vl.size();
		mid = (front + back) / 2;
	}
	if (vl[mid] == s)
		return vl[mid].head;
	return s;
}