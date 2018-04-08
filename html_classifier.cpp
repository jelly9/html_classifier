/*
 * 作者：肖国栋
 * 创建时间：2018-4-4
 *
 * */


#include "common.h"
#include "html_classifier.h"
#include <math.h>

void html_classifier::parser_html(const char *dir_name)
{
    assert(dir_name != NULL);

    char path[MAX_PATH_LENGTH] = {0};
    struct dirent *file_info;//readdir 的返回类型
    DIR *dir;

#ifdef STDOUT
    std::cout << dir_name << std::endl;
#endif
    dir = opendir(dir_name);
    assert(dir != NULL);

    while((file_info = readdir(dir)) != NULL){
        //目录结构下面会有两个.和..的目录？ 跳过着两个目录
        if(!strcmp(file_info->d_name,".")||!strcmp(file_info->d_name,".."))
            continue;

        sprintf(path,"%s/%s", dir_name, file_info->d_name);

        TMap temp;
        get_word_count_map(path, temp);
        _word_count_map.push_back(temp);
    }

    closedir(dir);
}

void html_classifier::get_feature_vector(TStringArray &feature)
{
    for(size_t i = 0; i < _word_count_map.size(); ++i){
        TVector temp;
        get_feature_vector_core(feature, _word_count_map[i], temp);
//        std::cout << temp.size() << std::endl;
        _feature_vector.push_back(temp);
    }
}

void html_classifier::get_avg_vector()
{
    size_t x = _feature_vector.size();
    size_t y = _feature_vector[0].size();
    size_t i = 0;
    size_t j = 0;
    TVector sum;
    sum.resize(y);
    for(i = 0; i < x; ++i){
        for(j = 0; j < y; ++j){
            sum[j] += _feature_vector[i][j];
        }
    }
    _avg_vector.resize(j);
    i = 0;
    for(; i < y; ++i){
        _avg_vector[i] = sum[i]/(double)x;
    }
}

void html_classifier::display()
{
#if 0
    for(size_t i = 0; i < _word_count_map.size(); ++i){
        std::cout << i << ":";
        TMap::iterator it = _word_count_map[i].begin();
        while(it != _word_count_map[i].end()){
            std::cout << it->first << "<=>" << it->second << " ";
            it++;
        }
        std::cout << std::endl;
    }
#else
    size_t x = _feature_vector.size();
    size_t y = _feature_vector[0].size();
    for(size_t i = 0; i < x; ++i){
        std::cout << i << ": ";
        for(size_t j = 0; j < y; ++j){
            std::cout << _feature_vector[i][j] << ",";
        }
        std::cout << std::endl;
    }
#endif
}


