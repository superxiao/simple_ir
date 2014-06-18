#pragma once
#include <string>
#include <vector>
#include "Dic.h"
#include <memory>
using namespace std;

class IndexConstructor
{
private:
    vector<string> files;
    void getFilesPathsInFolder(string folder, int fileLimit);
public:
    IndexConstructor();
    shared_ptr<Dic> constructIndex(string folder, int fileLimit);
    ~IndexConstructor(void);
};

