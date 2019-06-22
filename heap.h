
/******************************************************
  Heap.h -- Declarations for Basic Heap-of-Pair-of-Ints Class

  Stores pairs <element,priority> of ints.
  Supports O(log n) insertion, O(1) peeking at min priority and element
  with min priority, and O(log n) extraction of element with min priority.
*******************************************************/
using namespace std;

class Heap{

public:
   // Constructors and Destructor

   // New empty Heap with default capacity.
   Heap();

   // New empty Heap with capacity c.
   Heap(int c);

   // New Heap with size s, consisting of pairs <Pi,Ei> where,
   // for 0 <= i < s, Pi is Priorities[i] and Ei is value Elements[i].
   // Capacity is s + c, where c is the "spare capacity" argument.
   // Requires: Priorities and Elements are of size at least s.
   Heap( const int * Priorities, const int * Elements, int s, int c);

   // New Heap with combined contents the two Heap arguments.
   // Size of the new Heap is the sum of the sizes of argument Heaps.
   // Capacity of the new Heap is its size plus the "spare capacity" c.
   Heap( const Heap & Heap1, const Heap & Heap2, int c );

   // Destructor.
   ~Heap();

   // Accessors
   bool empty() const {return hSize == 0;}; // True iff Heap is empty.
   int size() const { return hSize ;} ; // Current size of Heap.
   int capacity() const { return hCapacity ;} ; // Current capacity.
   int peekMin() const { return A[0].element ;} // Peek at minimum priority element.
   int peekMinPriority() const { return A[0].priority ;} // Peek at minimum priority.

   // Modifiers
   void insert( int element, int priority ); // Insert the pair <element,priority>.
   int extractMin(); // Remove and return the highest (minimum) priority element.

private:
   class Pair{
      public:
        int element ;
        int priority ;
   };

   Pair* A ; // Array containing heap contents.
   int hCapacity ; // Max number of elements (= size of A).
   int hSize ; // Current number of elements.

   // Repairs ordering invariant after adding leaf at A[i].
   void trickleUp(int i);

   // Repairs ordering invariant for sub-tree rooted at index i,
   //   when A[i] may be have larger priority than one of its children,
   //   but the subtrees of its children are heaps.
   void trickleDown(int i);

   // Establishes ordering invariant for entire array contents.
   void heapify(); //(Same as "make_heap" in lectures.)

   // Useful for implementing trickle up and down
   void swap(int i,int j);
};

Heap::Heap(){
   hCapacity = 10 ;
   A = new Pair[hCapacity];
   hSize = 0 ;
}

Heap::Heap(int c){ // New empty Heap with capacity c.
   // Complete this.

   hCapacity = c;
   A = new Pair[hCapacity];
   hSize = 0;
}

// New Heap with capacity c+s, with s elements, consisting of pairs <Pi,Vi> where
//  Pi is Priorities[i], Ei is value Elements[i], for 0 <= i < s.
Heap::Heap( const int * Priorities, const int * Elements, int s, int c){
   // Complete this.

   hCapacity = c+s;
   A = new Pair[hCapacity];
   hSize = s;
   for(int i=0; i<s; i++)
   {
	   A[i].element = Elements[i];
	   A[i].priority = Priorities[i];
   }
   heapify();
}

// New Heap with combined contents and of the two given heaps.
Heap::Heap( const Heap & Heap1, const Heap & Heap2, int c ){
   hCapacity = Heap1.hSize + Heap2.hSize + c ;
   // Complete this.

   A = new Pair[hCapacity];
   hSize = Heap1.hSize + Heap2.hSize;
   for(int i=0; i<Heap1.hSize; i++)
   {
	   A[i] = Heap1.A[i];
   }

   int j=0;

   for(int i=Heap1.hSize; i<hSize; i++)
   {
	   A[i] = Heap2.A[j];
	   j++;
   }
    heapify();

}

// Destructor
Heap::~Heap(){
   delete[] A;
}

// Modifiers

void Heap::insert(int element, int priority){
   A[hSize].element = element;
   A[hSize].priority = priority;
   trickleUp(hSize);
   hSize ++;
}

// Repairs the heap ordering invariant after adding a new element.
// Initial call should be trickleUp(hSize-1).
void Heap::trickleUp(int i){
   // Complete this.

   while(i>0)
   {
	   if(A[i].priority < A[(i-1)/2].priority)
	   {
		   swap(i, (i-1)/2);
	   }
     else{
       break;
     }
	   i=(i-1)/2;
   }
}

void Heap::swap(int i, int j){
   Pair temp = A[i];
   A[i] = A[j];
   A[j] = temp ;
}

// Removes and returns the element with highest priority.
// (That is, the element associated with the minimum priority value.)
int Heap::extractMin(){
   // Complete this.

  int min = 0;
	if (hSize == 1)
	{
    min = A[0].element;
    hSize--;
		return min;

	}

   else if(hSize >1)
   {
	   swap(0, hSize-1);
     min = A[hSize - 1].element;
	   hSize--;
    trickleDown(0);
      return min;
   }
}

// Repairs the heap ordering invariant after replacing the root.
// (extractMin() calls trickleDown(0)).
// (trickleDown(i) performs the repair on the subtree rooted a A[i].)
// (heapify() calls trickleDown(i) for i from (hSize/2)-1 down to 0.)
void Heap::trickleDown(int i){
   // Complete this.

   if((2*(i+1)<=hSize) && (2*(i+1)+1 <= hSize)) // left right
   {
     if( (A[2*(i+1)-1].priority <= A[2*(i+1)].priority)  &&  (A[2*(i+1)-1].priority) < (A[i].priority) )
     {
       swap (2*(i+1)-1,i);
       i=2*(i+1)-1;
       trickleDown(i);
     }

     else if( (A[2*(i+1)].priority <= A[2*(i+1)-1].priority)  &&  (A[2*(i+1)].priority) < (A[i].priority) )
     {
       swap (2*(i+1),i);
       i=2*(i+1);
       trickleDown(i);
     }

   }


   else if((2*(i+1)<=hSize) && (2*(i+1)+1 > hSize))   //left
   {
     if(A[2*(i+1)-1].priority < A[i].priority)
     {
       swap (2*(i+1)-1,i);
       i=2*(i+1)-1;
       trickleDown(i);
     }
   }
}

// Turns A[0] .. A[size-1] into a heap.
void Heap::heapify(){
   for( int i = (hSize/2)-1; i>=0 ; i-- ) trickleDown(i);
}
