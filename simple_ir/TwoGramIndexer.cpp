#include "TwoGramIndexer.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>

using namespace boost;
TwoGramIndexer::TwoGramIndexer(void)
{
}

static vector<string> getTwoGrams(string token)
{
    vector<string> grams;
    string gram = "$";
    for(auto itr = token.begin(); itr!= token.end(); itr++)
    {
        gram += *itr;
        grams.push_back(gram);
        gram = *itr;
    }
    gram += "$";
    grams.push_back(gram);
    return grams;
}

void TwoGramIndexer::addToken(string token)
{
    vector<string> grams = getTwoGrams(token);
    for(auto itr = grams.begin(); itr != grams.end(); itr++)
    {
        auto list = hash.find(*itr); 
        if(list == hash.end())
        {
            List newList(*itr);
            hash.emplace(*itr, newList);
            list = hash.find(*itr);
        }
        list->second.addOther(token);
    }
}

shared_ptr<Dic> TwoGramIndexer::constructCurrentGrams()
{
    shared_ptr<Dic> dic(new Dic());
    for(auto itr = hash.begin(); itr != hash.end(); itr++)
    {
        dic->addList(itr->first, itr->second);
    }
    dic->sortLists();
    return dic;
}

shared_ptr<set<string>> TwoGramIndexer::searchForTwoGram(shared_ptr<Dic> dic, string gram)
{
    auto list = dic->getListByTerm(gram);
    return list->getOthers();
}

vector<string> TwoGramIndexer::searchForPrefix(shared_ptr<Dic> dic, string pre)
{
    auto prefixTwoGrams = getTwoGrams(pre);
    prefixTwoGrams.pop_back();

    shared_ptr<vector<string>> result_set = NULL;

    for(auto itr = prefixTwoGrams.begin(); itr != prefixTwoGrams.end(); itr++)
    {
        auto terms = searchForTwoGram(dic, *itr);
        if(result_set == NULL)
        {
            result_set = shared_ptr<vector<string>>(new vector<string>(terms->begin(), terms->end()));
            continue;
        }
        vector<string> result(min(result_set->size(), terms->size()));
        auto end = set_intersection(result_set->begin(), result_set->end(), terms->begin(), terms->end(), result.begin());
        result_set = shared_ptr<vector<string>>(new vector<string>(result.begin(), end));
    }
    vector<string> true_results;
    for(auto itr = result_set->begin(); itr != result_set->end(); itr++)
    {
        if(starts_with(*itr, pre))
        {
            true_results.push_back(*itr);
        }
    }
    return true_results;
}

vector<string> TwoGramIndexer::searchForPostfix(shared_ptr<Dic> dic, string post)
{
    auto postfixTwoGrams = getTwoGrams(post);
    postfixTwoGrams.erase(postfixTwoGrams.begin());
    shared_ptr<vector<string>> result_set = NULL;
    for(auto itr = postfixTwoGrams.begin(); itr != postfixTwoGrams.end(); itr++)
    {
        auto terms = searchForTwoGram(dic, *itr);
        if(result_set == NULL)
        {
            result_set = shared_ptr<vector<string>>(new vector<string>(terms->begin(), terms->end()));
            continue;
        }
        vector<string> result(min(result_set->size(), terms->size()));
        auto end = set_intersection(result_set->begin(), result_set->end(), terms->begin(), terms->end(), result.begin());
        result_set = shared_ptr<vector<string>>(new vector<string>(result.begin(), end));
    }
    vector<string> true_results;
    for(auto itr = result_set->begin(); itr != result_set->end(); itr++)
    {
        if(ends_with(*itr, post))
        {
            true_results.push_back(*itr);
        }
    }
    return true_results;
}

void TwoGramIndexer::saveIndexToFile(shared_ptr<Dic> index, string termFile, string postingsFile)
{
    cout << "Saving 2-gram index to disk.." << endl;
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
        termStream << term;
        int num = list->getOthersLength();
        termStream.write(reinterpret_cast<const char *>(&num), sizeof(num));

        auto tokenSet = list->getOthers();
        for(auto itr = tokenSet->begin(); itr != tokenSet->end(); itr++)
        {
            string term = *itr;
            char charCount = term.length();
            termStream.write(reinterpret_cast<const char *>(&charCount), sizeof(charCount));
            postingsStream.write(term.c_str(), term.length());
        }
    }
}

shared_ptr<Dic> TwoGramIndexer::readIndexFromFile(string termFile, string postingsFile)
{
    ifstream termStream(termFile, ios::binary);
    ifstream postingsStream(postingsFile,ios::binary);
    shared_ptr<Dic> dic(new Dic());
    char charCount;
    while(termStream.read(&charCount, sizeof(charCount)))
    {
        char term_cstr[255];
        termStream.read(term_cstr, charCount);
        term_cstr[charCount] = 0;
        string term(term_cstr);
        int num = 0;
        termStream.read(reinterpret_cast<char *>(&num), sizeof(num));
        shared_ptr<List> list(new List(term));
        
        for(int i = 0; i < num; i++)
        {
            char charCount;
            termStream.read(&charCount, sizeof(charCount));
            char buffer[256] = {0};
            postingsStream.read(buffer, charCount);
            string term(buffer);
            list->addOther(term);
        }
        dic->addList(term, *list);
    }
    dic->setSorted(true);
    return dic;
}

TwoGramIndexer::~TwoGramIndexer(void)
{
}
