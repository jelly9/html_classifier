

#include "html_classifier.hpp"
/* 包含头文件 */
#include <gumbo.h>

int main(int argc,char *argv[])
{
    (void)argc;
    (void)argv;
//    if(argc != 2){
//        cout << "usage: " << argv[0] << "[dir]"<< endl;
//        return 1;
//    }
//    html_classifier h(argv[1]);
    html_classifier h_yes;
    h_yes.scan_files("./novel/novel_yes_html");
    h_yes.get_feature_vector();
    h_yes.get_avg_vector();
    h_yes.display();

    html_classifier h_no;
    h_no.scan_files("./novel/novel_no_html");
    h_no.get_feature_vector();
    h_no.get_avg_vector();
    h_no.display();
    
    return 0;

}

