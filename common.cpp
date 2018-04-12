
#include "common.h"

static void get_word_count_map_core(GumboNode *node, TMap &m)
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
        m["h1"]++;
    }

    if(node->v.element.tag == GUMBO_TAG_BR){
        //cout << ((GumboNode *)children->data[0])->v.text.text << endl;
        m["br"]++;
    }

//    if(node->v.element.tag == GUMBO_TAG_TITLE){
//        TString title = ((GumboNode *)children->data[0])->v.text.text;
//        if(title.find("上一章")<title.length() ||
//           title.find("下一章")<title.length()){
//            m["chapter"]++;
//        }
//    }

    // 递归该节点下的所有子节点 
    for(i=0;i < children->length;++i)
        get_word_count_map_core((GumboNode*)children->data[i], m);
}

//统计file_name中的词和出现次数，保存到m中
void get_word_count_map(const char *file_name, TMap &m)
{
    struct stat buf;
    GumboOutput *output;
    FILE *fp;
    char *data;

    // 读取HTML文本文件 
#ifdef STDOUT
    std::cout << file_name << std::endl;
#endif
    if((fp=fopen(file_name,"rb")) == NULL) 
        assert(false);

    stat(file_name,&buf);
    data = new char[buf.st_size + 1];
    fread(data,sizeof(char),buf.st_size,fp);
    fclose(fp);
    data[buf.st_size]=0;


    // 解析HTML文本文件,生成gumbo数据结构 
    output=gumbo_parse(data);
    // 获取TITLE 
    get_word_count_map_core(output->root, m);

    // 销毁，释放内存
    delete[] data;;
    gumbo_destroy_output(&kGumboDefaultOptions,output);
}

//根据m中词-次数 映射 算出向量，保存到v中
void get_feature_vector_core(TStringArray &feature, TMap &m, TVector &v)
{
    v.resize(feature.size());

#ifdef STDOUT
    std::cout << m.size() << std::endl;
#endif

    for(size_t i = 0; i < feature.size(); ++i){
        if(m.find(feature[i]) != m.end()){
            v[i] = m[feature[i]];
        }else{
            v[i] = 0;
        }
    }
}
