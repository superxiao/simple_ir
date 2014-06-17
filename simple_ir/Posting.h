#ifndef POSTING_H
#define POSTING_H

#include <string>
using namespace std;

class Posting
{
private:
    int fq;//频率
    string docId;

public:
    Posting(string docId, int fq);
    Posting* next;
    string getDocId();
    int freq();//得到频率
};
#endif
