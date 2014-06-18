#include "IndexConstructor.h"
#include <boost/filesystem.hpp>
#include "TokenReader.h"
#include <sstream>
#include <memory>
#include <unordered_map>
#include <algorithm>

using namespace std;
using namespace boost::filesystem;

static int getFileId(string fileName)
{
    // Assume files are named as numbers
    string idStr = boost::filesystem::path(fileName).stem().string();
    int id;
    stringstream(idStr) >> id;
    return id;
}

static bool compareIntFileNames(string file1, string file2)
{
    return getFileId(file1) < getFileId(file2);
}

IndexConstructor::IndexConstructor()
{
}

void IndexConstructor::getFilesPathsInFolder(string folder, int fileLimit)
{
    // Currently we only deal with the Reuter files 
    if ( !exists( folder ) ) 
    {
        cout << "folder " << folder << "doesn't exit!" << endl;
        return;
    }
    directory_iterator end_itr; 
    int i = 0;
    if(fileLimit == 0)
        fileLimit = INT32_MAX;
    for ( directory_iterator itr( folder );
        itr != end_itr && i != fileLimit;
        ++itr, ++i )
    {
        if ( is_regular_file(itr->status()) )
        {
            files.push_back(itr->path().string());
        }
    }
    sort(files.begin(), files.end(), compareIntFileNames);
    cout << "Done getting all file names. " << files.size() << " files in total." << endl;
    
}

shared_ptr<Dic> IndexConstructor::constructIndex(string folder, int fileLimit)
{
    getFilesPathsInFolder(folder, fileLimit);
    unordered_map<string ,List> hash;
    for(auto file = files.begin(); file != files.end(); file++)
    {
        int fileId = getFileId(*file);
        cout << "Processing file " << fileId << endl;
        vector<string> tokens = TokenReader::readAndLowerTokensFromFile(*file);
        for(auto token = tokens.begin(); token != tokens.end(); token++)
        {
            auto list = hash.find(*token); 
            if(list == hash.end())
            {
                List newList(*token);
                hash.emplace(*token, newList);
                list = hash.find(*token);
            }
            list->second.addPosting(fileId);
        }
    }
    cout << "Sorting terms" << endl;
    shared_ptr<Dic> dic(new Dic());
    for(auto itr = hash.begin(); itr != hash.end(); itr++)
    {
        dic->addList(itr->first, itr->second);
    }
    dic->sortLists();
    return dic;
}

IndexConstructor::~IndexConstructor()
{
}
