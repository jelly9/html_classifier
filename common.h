
#include <iostream>
#include <string>
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

//#include "lib/include/cppjieba/Jieba.hpp"

#ifndef COMMON_H
#define COMMON_H

#define MAX_PATH_LENGTH 256

typedef std::string                 TString;
typedef std::vector<TString>        TStringArray;

typedef std::vector<double>         TVector;
typedef std::vector<TVector>        TVectorArray;

typedef std::map<TString, double>   TMap;
typedef std::vector<TMap>           TMapArray;

void init_feature(TStringArray feature, int argc, char *argv[]);
void get_word_count_map(const char *file_name, TMap &m);
void get_feature_vector_core(TStringArray &feature, TMap &m, TVector &v);

#endif
