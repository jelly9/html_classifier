/*
 * 作者：肖国栋
 * 创建时间：2018-4-4
 *
 * */


#include "html_classifier.hpp"
#include "common.hpp"

void html_classifier::parser_html(const char *dir_name)
{
    assert(dir_name != NULL);

    char path[MAX_PATH_LENGTH] = {0};
    struct dirent *file_info;//readdir 的返回类型
    DIR *dir;

    dir = opendir(dir_name);
    assert(dir == NULL);

    while((file_info = readdir(dir)) != NULL){
        //目录结构下面会有两个.和..的目录？ 跳过着两个目录
        if(!strcmp(file_info->d_name,".")||!strcmp(file_info->d_name,".."))
            continue;

        sprintf(path,"%s", file_info->d_name);

        TMap temp;
        get_word_count_map(path, temp);
        _word_count_map.push_back(temp);
    }

    closedir(dir);
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

#if 0
bool html_classifier::is_novel(const char *file_name)
{
    struct stat buf;
    GumboOutput *output;
    FILE *fp;
    char *data;

    // 读取HTML文本文件 
    if(!(fp=fopen(file_name,"rb"))) 
        assert(false);

    stat(file_name,&buf);
    data=(char*)malloc(sizeof(char)*(buf.st_size+1));
    fread(data,sizeof(char),buf.st_size,fp);
    fclose(fp);
    data[buf.st_size]=0;

//    cout << data << endl;

    // 解析HTML文本文件,生成gumbo数据结构 
    output=gumbo_parse(data);
    // 获取TITLE 
    //        cout << i << ":";
    get_feature(output->root, i);
    free(data);
    // 销毁，释放内存
    gumbo_destroy_output(&kGumboDefaultOptions,output);

    return true;
}
#endif
