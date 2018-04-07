
#include "common.hpp"

#ifndef _HTML_CLASSIFIER_
#define _HTML_CLASSIFIER_

using std::cout;
using std::endl;


class html_classifier{

public:
    void parser_html(const char *dir_name);//解析html
    void get_feature_vector();
    void get_avg_vector();
    bool is_novel(const char *file_name);

    void display()
    {
        cout << _avg_vector.size() << endl;;
        for(size_t i = 0; i < _avg_vector.size(); ++i){
            cout << _avg_vector[i] << " | ";
        }
        cout << endl;
    }

protected:
    TMapArray           _word_count_map;//统计的词-频映射
    TVectorArray        _feature_vector;//由词频建立的特征向量
public:
    TVector             _avg_vector;//平均特征向量
};

#endif
