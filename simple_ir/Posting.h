#ifndef POSTING_H
#define POSTING_H
#include <string>
#include <string>
#include <memory>

using namespace std;

class Posting
{
private:
    int fq;//频率
    int docId;
    string other;

public:
    Posting(int docId, int fq);
    Posting(string docId, int fq);
    shared_ptr<Posting> next;
    int getDocId();
    string getOther();
    int freq();//得到频率
};
#endif
