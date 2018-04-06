

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
    html_classifier h;
    cout << "scan..." << endl;
    h.scan_files("./novel/novel_yes_html");
    
    cout << "feature..." << endl;
    h.get_feature_vector();
    
    cout << "avg..." << endl;
    h.get_avg_vector();
    
    cout << "display..." << endl;
    h.display();




    return 0;

}

