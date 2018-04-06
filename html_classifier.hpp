
#ifndef _HTML_CLASSIFIER_
#define _HTML_CLASSIFIER_

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <assert.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <gumbo.h>

//#include "lib/include/cppjieba/Jieba.hpp"

using namespace std;

#define _DEBUG_ 1

class html_classifier{

public:
    void scan_files(const char *dir_name);//遍历文件夹
    void get_word_map(const char *file_name, size_t i);//构建特征 词-频 映射
    void get_feature(GumboNode *node, int which_title);//获取特征词
    void get_feature_vector();//创建特征向量
    void get_avg_vector();
    void display()
    {
#if _DEBUG_
//        double sum[2] = {0};
//        for(unsigned long i = 0; i < _word_map.size(); ++i){
//            cout << " " << "h1 " << _word_map[i]["h1"] << " br " << _word_map[i]["br"] << endl;
//            sum[0] += _word_map[i]["h1"];
//            sum[1] += _word_map[i]["br"];
//        }
//        cout << "sum " << sum[0] << " "<< sum[1] <<  endl;

//        size_t x = _feature_vector.size();
//        size_t y = _feature_vector[0].size();
//        size_t i = 0;
//        size_t j = 0;
//        for(i = 0; i < x; ++i){
//            for(j = 0; j < y; ++j){
//                cout << _feature_vector[i][j] << " ";
//            }
//            cout << endl;
//        }
//        cout << x << " " << y << endl;

        cout << _avg_vector.size() << endl;;
        for(size_t i = 0; i < _avg_vector.size(); ++i){
            cout << _avg_vector[i] << " | ";
        }
        cout << endl;


        //        sum[0] = 0;
        //        sum[1] = 0;
        //        size_t x = _feature_vector.size();
        //        size_t y = _feature_vector[0].size();
        //        cout << x << " " << y << endl;
//        for(size_t i = 0; i < x; ++i){
//            for(size_t j = 0; j < y; ++j){
//                cout << _feature_vector[i][j] << ",";
//                sum[j] += _feature_vector[i][j];
//            }
//            cout << endl;
//        }
//
#endif
    }


private:
    vector<map<string, double> > _word_map;//统计的词-频映射
    vector<vector<double> > _feature_vector;//由词频建立的特征向量
    vector<double>  _avg_vector;//平均特征向量
};


#endif
