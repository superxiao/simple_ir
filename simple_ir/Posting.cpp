#include<iostream>
#include<cstring>
#include<string>
#include"Posting.h"
using namespace std;
Posting::Posting(string docId, int fq)
{
    this->docId = docId;
    this->fq = fq;
    next=NULL;
}
int Posting::freq()
{
    return fq;
}

string Posting::getDocId()
{
    return docId;
}