#ifndef WORD_FREQ_COUNT_H
#define WORD_FREQ_COUNT_H
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

namespace zyd2001::word_freq_count
{
    typedef std::map<std::string, int> resultType;
    class Counter
    {
    public:
        Counter();
        Counter(const std::string &filename);
        Counter(std::shared_ptr<std::ifstream> file);
        bool setFile(std::shared_ptr<std::ifstream> file);
        bool setFile(const std::string &);
		resultType result;
		resultType &count(bool clear = false, std::function<void(std::string, std::out_of_range)> handle  = \
    [](std::string word, std::out_of_range e){std::cerr << "A word didn't find in table: " << word << std::endl;});
    private:
        void init();
		std::string &clearFile();
        std::string &trim(std::string &str);
        std::string filename;
		std::string fileContent;
        std::shared_ptr<std::ifstream> file;
        std::unordered_map<std::string, std::string> data_table;
    };
}

#endif