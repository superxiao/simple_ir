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
    int getFileId(string fileName);
public:
    IndexConstructor(string folderName, int fileLimit);
    shared_ptr<Dic> constructIndex();
    ~IndexConstructor(void);
};

