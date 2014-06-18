#include <memory>
#include "Dic.h"

using namespace std;

#pragma once
class IndexPersister
{
private:
public:
    IndexPersister();
    void saveIndexToFile(shared_ptr<Dic> index, string termFile, string postingsFile);
    shared_ptr<Dic> readIndexFromFile(string termFile, string postingsFile);
    ~IndexPersister(void);
};

