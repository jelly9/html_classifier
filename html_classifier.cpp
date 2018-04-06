/*
 * 作者：肖国栋
 * 创建时间：2018-4-4
 *
 * */


#include "html_classifier.hpp"

void html_classifier::scan_files(const char *dir_name)
{
    assert(dir_name != NULL);

    char path[512] = {0};
    struct dirent *filename;//readdir 的返回类型

    DIR *dir;

    dir = opendir(dir_name);
    if(dir == NULL){
        cout << "open dir error!" << endl;;
        exit(1);
    }

    size_t i = 0;
    while((filename = readdir(dir)) != NULL){
        i++;
    }
    _word_map.resize(i);
    closedir(dir);

    dir = opendir(dir_name);
    i = 0;
    while((filename = readdir(dir)) != NULL){
        //目录结构下面会有两个.和..的目录？ 跳过着两个目录
        if(!strcmp(filename->d_name,".")||!strcmp(filename->d_name,".."))
            continue;

        //拼接文件的全路径
        sprintf(path,"%s/%s",dir_name,filename->d_name);
//        cout << i << " " << path << endl;

        get_word_map(path, i);
        //_file_name.push_back(path);
        i++;
    }

    closedir(dir);
}

void html_classifier::get_word_map(const char *file_name, size_t i)
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
}

void html_classifier::get_feature(GumboNode *node, int which)
{

    GumboVector *children;
    unsigned int i;

    // 如果当前节点不是一个元素的话直接返回 
    if(node->type != GUMBO_NODE_ELEMENT) return;
    // 获取该节点的所有子元素节点 
    children=&node->v.element.children;

    // 检查当前节点的标签是否为XXX
    if(node->v.element.tag == GUMBO_TAG_H1){
//        if(((GumboNode *)children->data[0])->v.text.text)
//            cout << ((GumboNode *)children->data[0])->v.text.text << endl;
        _word_map[which]["h1"]++;
    }

    if(node->v.element.tag == GUMBO_TAG_BR){
        //cout << ((GumboNode *)children->data[0])->v.text.text << endl;
        _word_map[which]["br"]++;
    }

    // 递归该节点下的所有子节点 
    for(i=0;i < children->length;++i)
        get_feature((GumboNode*)children->data[i], which);

}

void html_classifier::get_feature_vector()
{
    size_t x = _word_map.size(); 
    size_t y = _word_map[0].size(); 
    _feature_vector.resize(x);
    for(size_t i= 0; i < x; ++i){
        _feature_vector[i].resize(y);
    }

    for(size_t i = 0; i < _word_map.size(); ++i){
        size_t j = 0;
        map<string, double>::iterator it = _word_map[i].begin();
        while(it != _word_map[i].end()){
            _feature_vector[i][j] = it->second;
            ++it;
            ++j;
        }
    }
}

void html_classifier::get_avg_vector()
{
    size_t x = _feature_vector.size();
    size_t y = _feature_vector[0].size();
    size_t i = 0;
    size_t j = 0;
    double sum[2] = {0};
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
