
#include "common.h"
#include "html_classifier.h"
#include <math.h>

bool is_novel(TStringArray &feature, TVector &yes, TVector &no, const char *file_name)
{
    TMap word_count;
    get_word_count_map(file_name, word_count);

    TVector feature_vector;
    get_feature_vector_core(feature, word_count, feature_vector);

#if 1
    //向量夹角
    double angle1 = atan2(feature_vector[0], feature_vector[1]) - atan2(yes[0], yes[1]);
    double angle2 = atan2(feature_vector[0], feature_vector[1]) - atan2(no[0], no[1]);

    if(angle1 < 0){
        angle1 *= -1;
    }

    if(angle2 < 0){
        angle2 *= -1;
    }

    return angle1<angle2 ? true : false;
#else
    //欧氏距离
    double dist_yes = sqrt(POW(yes[0]-feature_vector[0]) + POW(yes[1]-feature_vector[1]));
    double dist_no = sqrt(POW(no[0]-feature_vector[0]) + POW(no[1]-feature_vector[1]));

//    std::cout << "dist_yes:" << dist_yes << "dist_no:" << dist_no << std::endl;

    return dist_yes<dist_no ? true : false;
#endif
}

void Test()
{
    TStringArray feature;
    feature.push_back("h1");
    feature.push_back("br");
//    feature.push_back("chapter");


    //构建是小说的平均向量
    const char *yes_dir = "./novel/novel_yes_html";;
    html_classifier h_yes;
    h_yes.parser_html(yes_dir);
    h_yes.get_feature_vector(feature);
    h_yes.get_avg_vector();
    std::cout << "===========================================" << std::endl;
    std::cout << "yes_feature: " << h_yes._avg_vector[0] << "," << h_yes._avg_vector[1] << std::endl;
    
    //构建不是小说的平均向量
    const char *no_dir = "./novel/novel_no_html";;
    html_classifier h_no;
    h_no.parser_html(no_dir);
    h_no.get_feature_vector(feature);
    h_no.get_avg_vector();
    std::cout << "===========================================" << std::endl;
    std::cout << "no_feature:  " << h_no._avg_vector[0] << "," << h_no._avg_vector[1] << std::endl;

    char path[MAX_PATH_LENGTH] = {0};
    struct dirent *file_info;//readdir 的返回类型
    DIR *dir;
    double sum = 0;
    double c = 0;

    //测试是小说
    dir = opendir(yes_dir);
    assert(dir != NULL);

    while((file_info = readdir(dir)) != NULL){
        if(!strcmp(file_info->d_name,".")||!strcmp(file_info->d_name,".."))
            continue;
        sprintf(path,"%s/%s", yes_dir, file_info->d_name);

        bool ret = is_novel(feature, h_yes._avg_vector, h_no._avg_vector, path);
        ++sum;

        if(ret == true){
//            std::cout << "yes" << std::endl;
            ++c;
        }else{
//            std::cout << "no" << std::endl;
        }
    }
    closedir(dir);
    double accu = c/sum;
    std::cout << "===========================================" << std::endl;
    std::cout << "Test yes:" << std::endl;
    std::cout << "sum:" << sum << " yes:" << c << " accu:" << accu << std::endl;

    //测试非小说
    sum = 0;
    c = 0;
    dir = opendir(no_dir);
    assert(dir != NULL);

    while((file_info = readdir(dir)) != NULL){
        //目录结构下面会有两个.和..的目录？ 跳过着两个目录
        if(!strcmp(file_info->d_name,".")||!strcmp(file_info->d_name,".."))
            continue;
        sprintf(path,"%s/%s", no_dir, file_info->d_name);

        bool ret = is_novel(feature, h_yes._avg_vector, h_no._avg_vector, "novel/novel_no_html/111.html");
        ++sum;

        if(ret == true){
//            std::cout << "yes" << std::endl;
        }else{
            ++c;
//            std::cout << "no" << std::endl;
        }
    }
    closedir(dir);
    accu = c/sum;
    std::cout << "===========================================" << std::endl;
    std::cout << "Test no:" << std::endl;
    std::cout << "sum:" << sum << " no:" << c << " accu:" << accu << std::endl;
    std::cout << "===========================================" << std::endl;
}

int main(int argc,char *argv[])
{
    (void)argc;
    (void)argv;

    Test();

    return 0;

}

