#include<iostream>
#include<cstring>
#include<string>
#include"Posting.h"
using namespace std;
Posting::Posting(int docId, int fq)
{
    this->docId = docId;
    this->fq = fq;
    next=NULL;
}

Posting::Posting(string other, int fq)
{
    this->other = other;
    this->fq = fq;
    next=NULL;
}

int Posting::freq()
{
    return fq;
}

int Posting::getDocId()
{
    return docId;
}

string Posting::getOther()
{
    return other;
}