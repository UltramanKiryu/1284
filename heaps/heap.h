#ifndef HEAP_H
#define HEAP_H
#include"Process.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Heap
{
private:
    int *heap;
    int size;
    int elements;

    void bubbleUp(int idx,vector<int>&priority,vector<int>&time,vector<int>&arrival, vector<string>&schedule);
    void bubbleDown(int idx);
    void swap(int index1, int index2,vector<int>&priority,vector<int>&time,vector<int>&arrival, vector<string>&schedule);
    void reallocaste();

public:
    Heap(): heap(new int[20]), size(20),elements(0){}
    ~ Heap();

    void add(int value, vector<int>&priority,vector<int>&time,vector<int>&arrival, vector<string>&tasks);
    int peek(int &index);
    bool isEmpty();
    bool remove(int &value);
    void display(int index,vector<int>&time,vector<int>&arrival, vector<string>&schedule);
    void buildHeap(int *pile , int elements);
    void clear();

};

#endif // HEAP_H
