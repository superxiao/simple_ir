#ifndef TERM_H
#define TERM_H
class Term
{
private:
    char name[20];
    Term* next;
    double fq;//频率
public:
    double freq();//得到频率
    char* name();
};
#endif
