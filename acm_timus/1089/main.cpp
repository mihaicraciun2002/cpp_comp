#define CHRONO_IN 0
#if CHRONO_IN
#include <chrono>
#endif
// INCLUDES
//######################################//
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>

//######################################//
// START CODE HERE
//######################################//

std::vector <std::string> dictionary;
std::vector <std::string> buffers;
std::vector <std::string> correctedText;
char Ch;
bool endDictionary = false;

inline void readChar()  {
    Ch = fgetc(stdin);
    if(Ch == '#')
        endDictionary = true;
}

inline bool readString(std::string& x)  {
    std::string buffer;
    if(endDictionary)  {
        buffer.push_back(Ch);
    }
    readChar();

    if(endDictionary && !isalpha(Ch) && Ch != EOF)  {
        buffer.push_back(Ch);
    }
    while(Ch != EOF && !isalpha(Ch))  {
        readChar();
        if(endDictionary && !isalpha(Ch) && Ch != EOF)  {
            buffer.push_back(Ch);
        }
    }
    if(Ch == EOF)  {
        if(endDictionary)  {
            buffers.push_back(buffer);
        }
        return false;
    }
    x.clear();
    if(endDictionary)
        buffers.push_back(buffer);
    while(Ch != EOF && isalpha(Ch))  {
        x.push_back(Ch);
        readChar();
    }
    return true;
}

inline bool myStrCmp(const std::string& x, const std::string& y)  {
    if(x.size() != y.size())
        return false;
    int nrErrors = 0;
    for(int i = 0;i < x.size();i++)  {
        if(x[i] != y[i])  {
            nrErrors++;
        }
        if(nrErrors > 1)
            return false;
    }
    if(nrErrors == 1)
        return true;
    return false;
}

//######################################//
// END CODE HERE
//######################################//
#define EASY_IO 0

int main()  {
    #if CHRONO_IN
    auto started_time = std::chrono::high_resolution_clock::now();
    #endif
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif
//######################################//
// START CODE HERE
//######################################//

    std::string helper;
    readString(helper);

    while(!endDictionary)  {
        dictionary.push_back(helper);
        readString(helper);
    }

    int errorCounter = 0;

    do  {
        for(const auto& dictionaryWord : dictionary)  {
            if(myStrCmp(dictionaryWord, helper))  {
                helper = dictionaryWord;
                errorCounter++;
                break;
            }
        }
        correctedText.push_back(helper);
    }while(readString(helper));

    for(int i = 2;i < buffers[0].size();i++)
        std::cout << buffers[0][i];
    for(int i = 0;i < correctedText.size();i++)  {
        std::cout << correctedText[i] << buffers[i + 1];
    }

    std::cout << errorCounter << "\n";

//######################################//
// END CODE HERE
//######################################//
    #if CHRONO_IN
    auto finished_time = std::chrono::high_resolution_clock::now();
    std::cerr << "Time elapsed (s):\n";
    std::cerr << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finished_time - started_time).count() / 1000.0 << "\n";
    #endif
    return 0;
}
