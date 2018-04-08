
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <gumbo.h>
#include <algorithm>

#include "common.h"


#ifndef HTML_CLASSIFIER
#define HTML_CLASSIFIER


class html_classifier{

public:
    void parser_html(const char *dir_name);//解析html
    void get_feature_vector(TStringArray &feature);
    void get_avg_vector();
    void display();

protected:
    TMapArray           _word_count_map;//统计的词-频映射
    TVectorArray        _feature_vector;//由词频建立的特征向量
public:
    TVector             _avg_vector;//平均特征向量
};

#endif
