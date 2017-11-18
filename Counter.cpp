#include "Counter.h"
#include <cctype>

using namespace std;
using namespace zyd2001::word_freq_count;

Counter::Counter() {init();}

Counter::Counter(const string &name) : filename(name), file(make_shared<ifstream>(name)) {init();}

Counter::Counter(shared_ptr<std::ifstream> f) : file(f) {init();}

bool Counter::setFile(std::shared_ptr<std::ifstream> f)
{
    file = f;
	if (file->is_open())
		return true;
	else
		return false;
}

bool Counter::setFile(const std::string &name)
{
    filename = name;
    file = make_shared<ifstream>(name);
	if (file->is_open())
		return true;
	else
		return false;
}

void Counter::init()
{
    data_table.clear();
    pair<string, string> save;
    fstream data("2+2+3lem.dat");
	if (!data.is_open())
	{
		cerr << "Cannot open the data file \"2+2+3lem.dat\"." << endl;
		cerr << "Please make sure that \"2+2+3lem.dat\" is in the same folder with the program." << endl;
		exit(EXIT_FAILURE);
	}
    string buf, temp;
    while (getline(data, buf))
    {
        if (buf[0] == ' ')
        {
            istringstream is(buf);
            while (is >> temp)
            {
                save.first = temp;
                data_table.insert(save);
            }
        }
        else
        {
            save.first = buf;
            save.second = buf;
            data_table.insert(save);
        }
    }
}

resultType &Counter::count(bool clear, std::function<void(string, out_of_range)> handle)
{
    string word, temp;
    if (clear)
        result.clear();
	clearFile();
	istringstream is(fileContent);
    while (is >> word)
    {
        try 
        {
			if (word == "i")
				word = "I";
            word = data_table.at(word);
        }
        catch (out_of_range e) 
        {
            handle(word, e);
        }
        result[word]++;
    }
    return result;
}

string &Counter::clearFile()
{
	if (!file->is_open())
	{
		cerr << "Open input file failed" << endl;
		exit(EXIT_FAILURE);
	}
	stringstream buffer;
	buffer << file->rdbuf();
	fileContent = buffer.str();
	for (auto iter = fileContent.begin(); iter != fileContent.end();)
	{
		if (isalpha(static_cast<unsigned char>(*iter)) || *iter == '-')
		{
			*iter = tolower(*iter);
			++iter;
		}
		else if ((*iter) == '\'')
		{
			if (*(iter - 1) == 'n' && *(iter - 2) != 'a')
			{
				*(iter - 1) = ' ';
				*(iter + 1) = ' ';
				*iter = ' ';
				iter += 2;
			}
			else
			{
				*iter = ' ';
				*(iter + 1) = ' ';
				iter += 2;
			}
		}
		else
		{
			*iter = ' ';
			++iter;
		}
	}
	return fileContent;
}

//string &Counter::trim(string &str)
//{
//    for (auto iter = str.begin(); iter != str.end();)
//    {
//        if (isalpha(static_cast<unsigned char>(*iter)) || *iter == '-')
//        {
//            *iter = tolower(*iter);
//            ++iter;
//        }
//        else if ((*iter) == '\'')
//        {
//            if ((*(iter-1)) == 'n')
//            {
//                str.erase(iter - 1, str.end());
//                return str;
//            }
//            str.erase(iter, str.end());
//            return str;
//        }
//        else
//        {
//            str.erase(iter);
//        }
//    }
//    if (str == "i")
//        str[0] = 'I';
//    return str;
//}