# word_freq_count

# class `Counter`
In namespace `zyd2001::word_freq_count`.

Count the frequency of words appear in the document (can distinguish different type of word such as be(are, is, was, were, am, etc..)).

A simple wrapper is in `main.cpp`. It will output a `.csv` file.

## constructors: 

All constructors will read the data file `2+2+3lem.dat` which provide the table to look up for the "lemma" [2+2+3lem.dat](http://wordlist.aspell.net/12dicts-readme/#Lemmatized)

* `Counter()`
* `Counter(std::shared_ptr<std::ifstream> file)` This constructor will initialize the counter with a shared_ptr of an ifstream
* `Counter(const std::string &filename)` this constructor will initialize the counter with input file defined by filename

## public variables:
* `resultType result` is a `std::map<std::string, int>` that contains the result in the form of "word, frequency"

## public functions: 
* `bool setFile(std::shared_ptr<std::ifstream> file)` Set the input file. Similar with the second constructor but will check whether the ifstream is available.
* `bool setFile(const std::string &filename)` Set the input file. Similar with the third constructor but will check whether the program can open the file defined by filename.
* `resultType &count(bool clear = false, ...)` count the frequency. Return the reference of public variable result. If the parameter `clear` is true, the counter will clear the result before counting. By default it will persist the result. The second argument is a `std::function`(see that in `Counter.h`) that can handle the error when the word can't be found in the word list.