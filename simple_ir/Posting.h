#ifndef POSTING_H
#define POSTING_H

#include <string>
#include <memory>

using namespace std;

class Posting
{
private:
    int fq;//频率
    int docId;

public:
    Posting(int docId, int fq);
    shared_ptr<Posting> next;
    int getDocId();
    int freq();//得到频率
};
#endif
