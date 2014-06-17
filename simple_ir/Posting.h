#ifndef POSTING_H
#define POSTING_H
class Posting
{
private:
    char name[20];
    double fq;//频率
public:
    Posting(char*);
    Posting* next;
    double freq();//得到频率
    char* name();
};
#endif
