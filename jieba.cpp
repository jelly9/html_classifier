
#include <iostream>
using namespace std;
#include "lib/include/cppjieba/Jieba.hpp"

const char* const DICT_PATH = "../dict/jieba.dict.utf8";
const char* const HMM_PATH = "../dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
const char* const IDF_PATH = "../dict/idf.utf8";
const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";

int main()
{

    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);
    vector<string> words;
    vector<cppjieba::Word> jiebawords;
    string s;
    vector<string> r;


    s = "我来到百度大厦";
    Cut(s, r, true);

    for(size_t i = 0; i < r.size(); ++i){
        cout << r[i].c_str() << ",";
    }
    cout << endl;

    return 0;
}
