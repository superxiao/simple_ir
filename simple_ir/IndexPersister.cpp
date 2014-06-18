#include "IndexPersister.h"
#include <fstream>
#include <iostream>

IndexPersister::IndexPersister()
{
}

void IndexPersister::saveIndexToFile(shared_ptr<Dic> index, string termFile, string postingsFile)
{
    ofstream termStream(termFile, std::ios::binary);
    ofstream postingsStream(postingsFile, std::ios::binary);
    for(Dic::list_iterator list = index->begin(); list != index->end(); list++)
    {
        string term = list->getTerm();
        if (term.length() > 255)
        {
            cout << "We don't index terms larger than 255 characters!" << endl;
            continue;
        }
        char charCount = term.length();
        termStream.write(reinterpret_cast<const char *>(&charCount), sizeof(charCount));
        termStream.flush();
        termStream << term;
        termStream.flush();
        int docNum = list->getLength();
        termStream.write(reinterpret_cast<const char *>(&docNum), sizeof(docNum));
        
        termStream.flush();
        auto posting = list->getPostings();
        while(posting != NULL)
        {
            int docId = posting->getDocId();
            postingsStream.write(reinterpret_cast<const char *>(&docId), sizeof(docId));
            posting = posting->next;
        }
    }
}

shared_ptr<Dic> IndexPersister::readIndexFromFile(string termFile, string postingsFile)
{
    ifstream termStream(termFile, ios::binary);
    ifstream postingsStream(postingsFile,ios::binary);
    shared_ptr<Dic> dic(new Dic());
    char charCount;
    while(termStream.read(&charCount, sizeof(charCount)))
    {
        string term;
        for(char i = 0; i < charCount; i++)
        {
            char c;
            termStream.read(&c, sizeof(c));
            term.push_back(c);
        }
        int docNum = 0;
        termStream.read(reinterpret_cast<char *>(&docNum), sizeof(docNum));
        shared_ptr<List> list(new List(term));
        
         
        for(int i = 0; i < docNum; i++)
        {
            int docId;
            postingsStream.read(reinterpret_cast<char *>(&docId), sizeof(docId));
            list->addPosting(docId);
        }
        dic->addList(term, *list);
    }
    dic->setSorted(true);
    return dic;
}

IndexPersister::~IndexPersister(void)
{
}
