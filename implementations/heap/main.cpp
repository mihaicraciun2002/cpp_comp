#include <iostream>
#include <string>
#include "heaps.h"


int main(){
    myHeap <std::string> heap;

    heap.insert("A");
    heap.insert("Z");

    std::cerr << heap.pop() << " " << heap.pop();
    return 0;
}
