#include "heap.h"


Heap::~Heap()
{
    clear();
}
void Heap::bubbleUp(int index,vector<int>&priority,vector<int>&time,vector<int>&arrival, vector<string>&schedule)
{
    if(index==0)
    {
        return;
    }
    if(index != 0)
    {
        int parent = (index - 1)/2;
        if(heap[index] < heap[parent])
        {
            swap(index,parent,priority,time,arrival,schedule);
            bubbleUp(parent,priority,time,arrival,schedule);
        }
    }
}
void Heap::bubbleDown(int index)
{
    int max = index;
    int left = 2* index+1;
    int right = left +1;
    if(left > elements -1)
    {
        return;
     }
    if(right < elements - 1)
    {
        max =left;
    }
    else if(heap[left] < heap[right])
    {
        max =left;
    }
    else
    {
        max =right;
    }
    if(heap[index] < heap[max])
    {
        max =index;
    }
    if(max != index)
    {
        int m = heap[index];
        int j =heap[max];
        heap[index]=j;
        heap[max] =m;
        bubbleDown(max);
    }
}

void Heap::swap(int index1, int index2,vector<int>&priority,vector<int>&time,vector<int>&arrival, vector<string>&schedule)
{
    // swapping the heap stuff
    int m = heap[index1];
    int j =heap[index2];
    heap[index1]=j;
    heap[index2] =m;
    // swapping the priority vector
    int w=priority[index1];
    int q =priority[index2];
    priority[index1]=q;
    priority[index2]=w;
    // swapping the schedule vector
    string ww= schedule[index1];
    string he = schedule[index2];
    schedule[index1] = he;
    schedule[index2] = ww;

    // swapping the time vector
    int kk = time[index1];
    int jh = time[index2];
    time[index1]=jh;
    time[index2]= kk;

    //swapping the arrival vector
    j=arrival[index1];
    m =arrival[index2];
    arrival[index1]=m;
    arrival[index2]=j;
    return;
}
void Heap::reallocaste() //expanding the size of the tree
{
    int* old = heap;
    size *= 2;
    heap = new int[size];
    for(int i =0; i<elements; i++)
    {
        heap[i]= old[i];
    }
    delete[] old;
}
void Heap::add(int value,vector<int>&priority,vector<int>&time,vector<int>&arrival, vector<string>&tasks)
{
    heap[elements] = value;  //placing  a value at the end of the heap
    bubbleUp(elements,priority,time,arrival,tasks);
    elements++;
}
void Heap::display(int index,vector<int>&time,vector<int>&arrival, vector<string>&tasks)
{
    if(isEmpty()==false) // to ensure that there are values within the heap
    {
        for(int i = index;i< elements; i++)
        {
            cout<<tasks[i]<<" @ "<<heap[i]<<" for 0 out of "<<time[i]<<" arriving at "<<arrival[i]<<endl;
        }
        cout<<endl;
    }
}
int Heap::peek(int &index)
{
        if(index<elements) // an if else statement to see if the index has a value
        {
           return heap[index];
        }
    return false;
}
bool Heap::isEmpty()
{
    if(elements != 0)// check to see if the elements has any value within them
    {
        return false;
    }
    //else it will return
    return true;
}
bool Heap::remove(int &value)
{
    elements--;
    int jj =heap[value];
    heap[value]=heap[elements];
    bubbleDown(value);
        return true;

}
void Heap::buildHeap(int *pile , int elements)
{
    for(int k=(elements/2); k > 0; k--)// every time a new row is added half of the treeis added
    {
        bubbleDown(k);
    }
}

void Heap::clear()
{
    while(elements!=0){
    for(int i = 0; i < 1;i++)
    {
       remove(i);
    }
}
}
