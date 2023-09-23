#define CHRONO_IN 0

#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>

#if CHRONO_IN
#include <chrono>
#endif

// Start code here

const int maxLength = 1e4 + 1;

std::string text;
int indexText = 0;
std::vector <char> punctuation ({'!', '.', '?'});

inline bool isPunctuation(const char& ch)  {
    for(const auto& x : punctuation)
        if(x == ch)
            return true;
    return false;
}

inline void changeSentence()  {
    bool foundFirstLetter = false;
    while(indexText < text.size() && !isPunctuation(text[indexText]))  {
        if(isalpha(text[indexText]))  {
            if(foundFirstLetter)
                text[indexText] += 'a' - 'A';
            foundFirstLetter = true;
        }
        indexText++;
    }
    while(indexText < text.size() && !isalpha(text[indexText]))
        indexText++;
}


// End code here

#define EASY_IO 0

int main()  {
    #if CHRONO_IN
    auto started_time = std::chrono::high_resolution_clock::now();
    #endif
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif

    // Start code here

    char ch = fgetc(stdin);
    while(ch != EOF)  {
        text.push_back(ch);
        ch = fgetc(stdin);
    }

    while(indexText != text.size())  {
        changeSentence();
    }

    std::cout << text << "\n";

    // End code here

    #if CHRONO_IN
    auto finished_time = std::chrono::high_resolution_clock::now();
    std::cerr << "Time elapsed (s):\n";
    std::cerr << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finished_time - started_time).count() / 1000.0 << "\n";
    #endif
    return 0;
}