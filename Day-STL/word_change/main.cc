// 使用unordered_map/map实现单词转换程序。给定一个string，将它转换为另一个string。
// 程序的输入是两个文件，第一个文件保存的是一些规则，用来转换第二个文件中的文本。
// 每条规则由两部分组成：一个可能出现在输入文件中的单词和一个用来替换它的短语。
// 表达的含义是，每当第一个单词出现在输入中时，我们就将它替换为对应的短语，第二个输入文件包含要转换的文本。
// （C++ primer 11.3.6）

// 提示：
// 规则文件：map.txt文件，其实就是第一个单词，被后面的一串所替换。
// 待转换文本：file.txt文件，该文件中的单词如果出现在map.txt文件的第一个单词的话，就用map.txt的后面一串替代。
// 结果：最后结果其实就是，将file.txt文件中的并且出现在map.txt中第一个单词转换为map.txt后面的一串。
// 例如：where r u的输出结果就是where are you. r替换为are，u替换为you

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::unordered_map;

class Cstring
{
public:
    void rule(ifstream &);
    void change(ifstream &);

private:
    unordered_map<string, string> _rule;
};

void Cstring::rule(ifstream &ifs)
{
    string line;
    while (std::getline(ifs, line))
    {
        // 迭代器方式分割key，value
        string key;
        string value;
        auto it = line.begin();
        while ((*it) != ' ')
        {
            ++it;
        }
        key.insert(key.begin(), line.begin(), it);
        value.insert(value.begin(), it + 1, line.end());
        // cout << "key " << key << endl;
        // cout << "value " << value << endl;

        _rule.insert({key, value});
    }

    //another way
    // string key;
    // string value;
    // while (ifs >> key && std::getline(ifs, value))
    // {
    //     if (value.size() > 1)
    //     {
    //         // 去除空格
    //         _rule[key] = value.substr(1);
    //     }
    // }
}

void Cstring::change(ifstream &ifs)
{
    string line;
    while (std::getline(ifs, line))
    {
        istringstream iss(line);
        string word;
        while (iss >> word)
        {
            auto ret = _rule.find(word);
            if (ret != _rule.end())
            {
                cout << ret->second << " ";
            }
            else
            {
                cout << word << " ";
            }
        }
        cout << endl;
    }
}

void test0()
{
    Cstring cs;
    ifstream ifs1("map.txt");
    cs.rule(ifs1);
    ifstream ifs2("file.txt");
    cs.change(ifs2);
}

int main()
{
    test0();
    return 0;
}
