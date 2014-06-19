#pragma once
#include <string>
#include <memory>
#include "Dic.h"
#include "List.h"
#include "Posting.h"
#include <unordered_map>
#include <set>

using namespace std;
class TwoGramIndexer
{
private:
    unordered_map<string, List> hash;
public:
    TwoGramIndexer(void);
    void addToken(string);
    shared_ptr<Dic> constructCurrentGrams();
    static void saveIndexToFile(shared_ptr<Dic> index, string termFile, string postingsFile);
    static shared_ptr<Dic> readIndexFromFile(string termFile, string postingsFile);
    static shared_ptr<set<string>> TwoGramIndexer::searchForTwoGram(shared_ptr<Dic> dic, string gram);
    static vector<string> searchForPrefix(shared_ptr<Dic> dic, string pre);
    static vector<string> searchForPostfix(shared_ptr<Dic> dic, string post);
    ~TwoGramIndexer(void);
};

