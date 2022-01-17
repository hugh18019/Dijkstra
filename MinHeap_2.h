#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

// Max-heap implementation
class MinHeap2 {           // Number of things now in heap
public:
  bool GT (tuple<int,int> t1, tuple<int,int> t2) { return get<1>(t1) > get<1>(t2); }
  bool GTE (tuple<int,int> t1, tuple<int,int> t2) { return get<1>(t1) >= get<1>(t2); }
  bool LT (tuple<int,int> t1, tuple<int,int> t2) { return get<1>(t1) < get<1>(t2); }
  bool LTE (tuple<int,int> t1, tuple<int,int> t2) { return get<1>(t1) <= get<1>(t2); }

  
  MinHeap2(int s)
  { n = 0; size = s; Heap.resize(s); }

  // Constructor supporting preloading of heap contents
  MinHeap2(vector<tuple<int,int>> h, int num, int max)
  { Heap = h;  n = num;  size = max; buildheap(); }
  // { Heap = h;  n = num;  size = max;  buildheap(); }

  // Return current size of the heap
  int heapsize() { return n; }

  // Return true if pos a leaf position, false otherwise
  bool isLeaf(int pos)
  { return (pos >= n/2) && (pos < n); }

  // Return position for left child of pos
  int leftchild(int pos) {
    if (pos >= n/2) { return -1; }
    return 2*pos + 1;
  }

  // Return position for right child of pos
  int rightchild(int pos) {
    if (pos >= (n-1)/2) { return -1; }
    return 2*pos + 2;
  }

  // Return position for parent
  int parent(int pos) {
    if (pos <= 0) { return -1; }
    return (pos-1)/2;
  }

  // Insert val into heap
  void insert(tuple<int,int> t) {
    if (n >= size) {
      return;
    }
    int curr = n++;
    Heap[curr] = t;  // Start at end of heap
    // Now sift up until curr's parent's key > curr's key
    while ((curr != 0) && (   LT( Heap[curr], Heap[parent(curr)] ) )) {
      swap(Heap[curr], Heap[parent(curr)]);
      curr = parent(curr);
    }
  }

  // Heapify contents of Heap
  void buildheap()
  {
    for (int i=n/2-1; i>=0; i--) 
    { 
      siftdown(i); 
    } 
  }

  // Put element in its correct place
  void siftdown(int pos) {
    if ((pos < 0) || (pos >= n)) { return; } // Illegal position
    while (!isLeaf(pos)) {
      int j = leftchild(pos);
      if ((j<(n-1)) && (  LTE(Heap[j + 1], Heap[j]))) {
        j++; // j is now index of child with smaller value
      }
      if (  LTE(Heap[pos], Heap[j])) { return; }
      swap(Heap[pos], Heap[j]);
      pos = j;  // Move down
    }
  }

  // Remove and return maximum value
tuple<int,int> removemin() {
    if (n == 0) { return make_tuple(-1, -1); }  // Removing from empty heap
    swap(Heap[0], Heap[--n]); // Swap maximum with last value
    siftdown(0);   // Put new heap root val in correct place
    return Heap[n];
  }

  // Remove and return element at specified position
 tuple<int,int> remove(int pos) {
    if ((pos < 0) || (pos >= n)) { return make_tuple(-1, -1); } // Illegal heap position
    if (pos == (n-1)) { n--; } // Last element, no work to be done
    else {
      swap(Heap[pos], Heap[--n]); // Swap with last value
      update(pos);
    }
    return Heap[n];
  }

  // Modify the value at the given position
  void modify(int pos, int newVal) {
    if ((pos < 0) || (pos >= n)) { return; } // Illegal heap position
    get<1>(Heap[pos]) = newVal;
    update(pos);
  }

  // The value at pos has been changed, restore the heap property
  void update(int pos) {
    // If it is a big value, push it up
    while ((pos > 0) && ( LT(Heap[pos], (Heap[parent(pos)])) > 0)) {
      swap(Heap[pos], Heap[parent(pos)]);
      pos = parent(pos);
    }
    siftdown(pos); // If it is little, push down
  }

  tuple<int,int> getElement(int pos)
  {
    return Heap[pos];
  }

  tuple<int,int> getMin () { return Heap[0]; }
  bool empty () { return Heap.empty(); }
  int get_cur_size () { return n; }
  int get_max_size () { return size; }
  vector<tuple<int,int>> getHeap () { return Heap; }

  private:
   vector<tuple<int,int>> Heap; // Pointer to the heap array
   int size;          // Maximum size of the heap
   int n;  
};