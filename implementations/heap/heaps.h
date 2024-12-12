#include <vector>
#include <iostream>
#include <cassert>

template <class type = int>
struct defaultCmp{
    bool operator()(const type& a, const type& b){
        return a > b;
    }
};

template <class type, class comparator = defaultCmp <type>>
class myHeap{
    private:
    std::vector <type> heap;
    comparator cmp;

    void upHeap(int node);

    void downHeap(int node);

    public:
    // Constructor
    myHeap(){heap.push_back(type());};
    // Destructor
    ~myHeap(){};
    // Insert
    void insert(type val);
    // Get top
    type top();
    // Pop
    type pop();
};

template <class type, class comparator>
void myHeap<type, comparator>::upHeap(int node){
    if(node == 1){
        return;
    }
    int parent = node >> 1;
    if(!cmp(heap[parent], heap[node])){
        std::swap(heap[parent], heap[node]);
        upHeap(parent);
        return;
    }
    return;
}

template <class type, class comparator>
void myHeap<type, comparator>::downHeap(int node){
    if(node + 1 == heap.size()){
        heap.pop_back();
        return;
    }
    int childL, childR;
    childL = node << 1;
    childR = childL + 1;
    if(childL >= heap.size() && childR >= heap.size()){
        std::swap(heap[node], heap.back());
        heap.pop_back();

        upHeap(node);
        return;
    }
    if(childR >= heap.size()){
        std::swap(heap[childL], heap[node]);
        downHeap(childL);
        return;
    }
    if(cmp(heap[childL], heap[childR])){
        std::swap(heap[childL], heap[node]);
        downHeap(childL);
    }else{
        std::swap(heap[childR], heap[node]);
        downHeap(childR);
    }
}

template <class type, class comparator>
void myHeap<type, comparator>::insert(type val){
    heap.push_back(val);
    upHeap(heap.size() - 1);
}

template <class type, class comparator>
type myHeap<type, comparator>::top(){
    assert(heap.size() > 1);
    return heap[1];
}

template <class type, class comparator>
type myHeap<type, comparator>::pop(){
    assert(heap.size() > 1);
    type val = heap[1];
    downHeap(1);
    return val;
}
