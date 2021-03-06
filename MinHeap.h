#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

// Max-heap implementation
class MinHeap {           // Number of things now in heap
public:
  bool GT (tuple<int,int,int> t1, tuple<int,int,int> t2) { return get<2>(t1) > get<2>(t2); }
  bool GTE (tuple<int,int,int> t1, tuple<int,int,int> t2) { return get<2>(t1) >= get<2>(t2); }
  bool LT (tuple<int,int,int> t1, tuple<int,int,int> t2) { return get<2>(t1) < get<2>(t2); }
  bool LTE (tuple<int,int,int> t1, tuple<int,int,int> t2) { return get<2>(t1) <= get<2>(t2); }

  
  MinHeap(int s)
  { n = 0; size = s; Heap.resize(s); }

  // Constructor supporting preloading of heap contents
  MinHeap(vector<tuple<int,int,int>> h, int num, int max)
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
  void insert(tuple<int,int,int> t) {
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
      if ((j<(n-1)) && (  LTE(Heap[j], Heap[j+1]))) {
        j++; // j is now index of child with greater value
      }
      if (  LTE(Heap[pos], Heap[j])) { return; }
      swap(Heap[pos], Heap[j]);
      pos = j;  // Move down
    }
  }

  // Remove and return maximum value
tuple<int,int,int> removemin() {
    if (n == 0) { return make_tuple(-1, -1, -1); }  // Removing from empty heap
    swap(Heap[0], Heap[--n]); // Swap maximum with last value
    siftdown(0);   // Put new heap root val in correct place
    return Heap[n];
  }

  // Remove and return element at specified position
 tuple<int,int,int> remove(int pos) {
    if ((pos < 0) || (pos >= n)) { return make_tuple(-1, -1, -1); } // Illegal heap position
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
    get<2>(Heap[pos]) = newVal;
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

  tuple<int,int,int> getElement(int pos)
  {
    return Heap[pos];
  }

  tuple<int,int,int> getMin () { return Heap[0]; }
  bool empty () { return Heap.empty(); }
  int get_cur_size () { return n; }
  int get_max_size () { return size; }
  vector<tuple<int,int,int>> getHeap () { return Heap; }

  private:
   vector<tuple<int,int,int>> Heap; // Pointer to the heap array
   int size;          // Maximum size of the heap
   int n;  
};