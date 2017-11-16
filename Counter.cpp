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
}

bool Counter::setFile(const std::string &name)
{
    filename = name;
    file = make_shared<ifstream>(name);
}

void Counter::init()
{
    data_table.clear();
    pair<string, string> save;
    fstream data("2+2+3lem.dat");
    string buf, temp;
    while (getline(data, buf))
    {
        buf.erase(buf.end() - 1);
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

resultType Counter::count(std::function<void(string, out_of_range)> handle)
{
    string word;
    result.clear();
    while ((*file) >> word)
    {
        trim(word);
        try 
        {
            if (word.empty())
                continue;
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

string &Counter::trim(string &str)
{
    if (str == "I")
        return str;
    for (auto iter = str.begin(); iter != str.end();)
    {
        if (isalpha(static_cast<unsigned char>(*iter)) || *iter == '-')
        {
            *iter = tolower(*iter);
            ++iter;
        }
        else if ((*iter) == '\'')
        {
            if ((*(iter-1)) == 'n')
            {
                str.erase(iter - 1, str.end());
                return str;
            }
            str.erase(iter, str.end());
            return str;
        }
        else
        {
            str.erase(iter);
        }
    }
    return str;
}