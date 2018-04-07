#pragma once

#ifndef _COMMON_
#define _COMMON_

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
#include <algorithm>

//#include "lib/include/cppjieba/Jieba.hpp"

#define MAX_PATH_LENGTH 256

typedef std::string                 TString;
typedef std::vector<TString>        TStringArray;

typedef std::vector<double>         TVector;
typedef std::vector<TVector>        TVectorArray;

typedef std::map<TString, double>   TMap;
typedef std::vector<TMap>           TMapArray;

TStringArray g_feature_word;

void init_feature(int argc, char *argv[]);
void get_word_count_map(const char *file_name, TMap &m);
void get_feature_vector_core(TMap &m, TVector &v);

#endif
