
#include "common.hpp"

void init_feature(int argc, char *argv[])
{
    g_feature_word.resize(argc);

    for(int i = 0; i < argc; ++i){
        g_feature_word[i] = TString(argv[i]);
    }
}

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
    if(!(fp=fopen(file_name,"rb"))) 
        assert(false);

    stat(file_name,&buf);
    //data=(char*)malloc(sizeof(char)*(buf.st_size+1));
    data = new char[buf.st_size + 1];
    fread(data,sizeof(char),buf.st_size,fp);
    fclose(fp);
    data[buf.st_size]=0;

//    cout << data << endl;

    // 解析HTML文本文件,生成gumbo数据结构 
    output=gumbo_parse(data);
    // 获取TITLE 
    //        cout << i << ":";
    get_word_count_map_core(output->root, m);

    // 销毁，释放内存
    delete[] data;;
    gumbo_destroy_output(&kGumboDefaultOptions,output);
}

//根据m中词-次数 映射 算出向量，保存到v中
void get_feature_vector_core(TMap &m, TVector &v)
{
    v.resize(g_feature_word.size());

    for(size_t i = 0; i < g_feature_word.size(); ++i){
        if(find(m.begin(), m.end(), g_feature_word[i])->second){
            v[i] = m[g_feature_word[i]];
        }else{
            v[i] = 0;
        }
    }
}


