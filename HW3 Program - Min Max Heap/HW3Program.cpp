// Homework 3 Program Brendan Bovenschen March 30th 2023
//

#include <iostream>

using namespace std;

class MMHeap
{
    int len;
    int arr[128];

    //Heap position calculations
    int Parent(int i) { return (i - 1) / 2; }

    int Left(int i) { return 2 * i + 1; }

    int Right(int i) { return 2 * i + 2; }

    //Simple swap function
    void Swap(int a, int b) 
    { //Pre: position a,b on array 'arr'
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
      //Post: value of a and b have been switch
    }

    //Removes element from list, moves other elements down to fill
    void RemoveElement(int i) 
    { //Pre: position i in array 'arr' of length 'len'
        while (i < len)
        {
            arr[i] = arr[i + 1];
            i++;
        }
        len--;
        //Post: array length is subtracted by 1
    }

    //Returns the smallest element position of
    //the children and grandchildren of element position 'i'
    int SmallestCGC(int i) 
    { //Pre: position i in array arr of length len
        int m = i;

        for (int j = Left(i); j <= Right(i); j++) // Child comparisons
        {
            if (j >= len) return m; //terminate if out of array bounds
            if (arr[j] < arr[m]) m = j;
        }
        for (int j = Left(Left(i)); j <= Left(Left(i)) + 3; j++) // Grandchild comparison
        {
            if (j >= len) return m; //terminate if out of array bounds
            if (arr[j] < arr[m]) m = j;
        }

        return m;
        //Post: m is the minimum element in the children or grandchidren of i
    }

    //Returns the largest element position of
    //the children and grandchildren of element position 'i'
    int LargestCGC(int i) 
    { //Pre: position i in array arr of length len
        int m = i;

        for (int j = Left(i); j <= Right(i); j++) // Child comparisons
        {
            if (j >= len) return m; //terminate if out of array bounds
            if (arr[j] > arr[m]) m = j;
        }
        for (int j = Left(Left(i)); j <= Left(Left(i)) + 3; j++) // Grandchild comparison
        {
            if (j >= len) return m; //terminate if out of array bounds
            if (arr[j] > arr[m]) m = j;
        }

        return m;
        //Post: m is the maximum element in the children or grandchidren of i
    }

    //Upward heapification for minimum level
    void HeapifyUpMin(int i)
    {
        //Pre: position i in array 'arr'
        if (i < 3) return; //if no grandparents

        int g = Parent(Parent(i)); //grandparent

        if (arr[i] < arr[g]) //Swap element i with its grandparent if less
        {
            Swap(i, g);
            HeapifyUpMin(g);
        }
        //Post: i is integrated into arr
    }

    //Upward heapification for maximum level
    void HeapifyUpMax(int i)
    {
        //Pre: position i in array 'arr'
        if (i < 3) return; //if no grandparents

        int g = Parent(Parent(i)); //grandparent

        if (arr[i] > arr[g]) //Swap element i with its grandparent if greater
        {
            Swap(i, g);
            HeapifyUpMax(g);
        }
        //Post: i is integrated into arr
    }

    //Downward Heapify for element in a minimum level:
    //Swaps element i into list through the minimum value
    void HeapifyDownMin(int i)
    {
        //Pre: integer 'i' indicating position on array
        int m = SmallestCGC(i); //minimum in i's children and grandchildren

        if (m == i) return; //terminate if i has no lesser children

        if (m > Right(i))  //if m is a grandchild of i
        {
            Swap(m, i);

            //swap i and parent if i is greater than parent
            int p = Parent(m);
            if (arr[m] > arr[p]) Swap(m, p); 
                
            MMHeapifyDown(m); //Heapify for next min/max level
        }
        //m is a child of i, swap if less than
        else if (arr[m] < arr[i])
            Swap(m, i);
        //Post: element i has been integrated into the MMHeap
    }

    //Downward Heapify for element in a maximum level:
    //Swaps element i into list through the maximum value
    void HeapifyDownMax(int i) 
    {
        //Pre: integer 'i' indicating position on array
        int m = LargestCGC(i); //maximum in i's children and grandchildren

        if (m == i) return; //terminate if i has no greater children

        if (m > Right(i))  //if m is a grandchild of i
        {
            Swap(m, i);

            //swap i and parent if i is less than parent
            int p = Parent(m);
            if (arr[m] < arr[p]) Swap(m, p); 
                
            MMHeapifyDown(m); //Heapify for next min/max level
        }
        //m is a child of i, swap if greater than
        else if (arr[m] > arr[i])
            Swap(m, i);
        //Post: element i has been integrated into the MMHeap
    }

    //Determines if i is on a min or max level node
    bool isMinLvl(int i) 
    { //Pre: array position 'i', tree level 'lvl'
        int lvl = 0;
        i++; 

        while (i > 0) { //largest 2^i that is < i
            i = i / 2;  //binary increase in level size
            lvl++;
        }
        return lvl % 2 != 0; //checks is lvl is odd or even
        //Post: true if lvl is odd (min level), false if even (max)
    }

    //Heapify for min max heap structure
    //Heapify min for min levels, max for max levels
    void MMHeapifyDown(int i) 
    { //Pre: array position i
        if (isMinLvl(i)) 
            HeapifyDownMin(i);
        else
            HeapifyDownMax(i);
        //Post: i is integrated into the min max array
    }

    //Heapify down from the middle elemnt to the first
    void MMBuildHeap()
    { 
        //Pre: unsorted array 'arr' of length 'l'
        for (int i = (len / 2) - 1; i >= 0; i--)
            MMHeapifyDown(i);
        //Post: arr is sorted to min-max heap rules
    }

public:
    
    //MinMaxHeap class constructor
    //assign length and array 'arr'
    MMHeap(int* inArr, int inLen)
    { 
        len = inLen;

        for (int i = 0; i < len; i++) //copy each element to arr
            arr[i] = inArr[i];

        MMBuildHeap(); //sort array to min max heap
    }

    //traverse each element of heap and print
    void printHeap() {
        for (int i = 0; i < len; i++)
            cout << arr[i] << " ";

        cout << "\n";
    }

    //Heap min is always position 0
    int GetMin() 
    { 
        if (len == 0) return -1; //array is empty
        return arr[0]; 
    }

    //Heap max is greater of position 1 and 2
    int GetMax() 
    {
        if (len == 0) return -1; // array is empty

        if (arr[1] > arr[2]) return arr[1];
        return arr[2];
    }

    //Remove element 1 and heapify
    void ExtractMin() 
    {//Pre: min value at position '0'

        if (len == 0) return; //terminate if no elements

        RemoveElement(0);
        MMHeapifyDown(0);
        //Post: min value removed, hole heapified
    }

    //Remove max element and heapify
    void ExtractMax() 
    { //Pre: max value at position '1' or '2'

        if (len == 0) return; //terminate if no elements

        int i;

        if (arr[1] > arr[2]) i = 1; //comparisoin for max element
        else i = 2;

        RemoveElement(i);
        MMHeapifyDown(i);
        //Post: max value removed, hole heapified
    }

    //Inserts a number into a position in the array
    void Insert(int num)
    { //Pre: number value 'num', array 'arr'

        arr[len] = num; //place num at end of array
        len++;
        
        if (len == 1) return; //terminate if only 1 element

        int i = len - 1; //last position
        int p = Parent(i);

        //Min level
        if (isMinLvl(i)) 
        {
            if (arr[i] > arr[p]) //swap if breaking min max rule
            {                    //heapify up min max for correct level
                Swap(i, p);
                HeapifyUpMax(p);
            }
            else HeapifyUpMin(i);
            return;
        }

        //Max level
        if (arr[i] < arr[p]) //swap if breaking min max rule
        {                    //heapify up min max for correct level
            Swap(i, p);
            HeapifyUpMin(p);
        }
        else HeapifyUpMax(i);
        //Post: num is integrated into the arr
    }
};

//
//
//Everything past this line is user interface code
//
// 

//Handles the example seen in the documentation
void UIExample() 
{
    //Create array
    cout << "\nInput Array: ";
    int arr[] = { 4,1,3,2,16,9,10,14,8,7 }; 
    int len = 10;
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    MMHeap heap = MMHeap(arr, len);

    //Output each function

    //print heap
    cout << "\nMin-Max Heap: ";
    heap.printHeap(); ///Expected: 1 16 10 2 4 9 3 14 8 7

    //GetMin/ExtractMin
    cout << "Min value '" << heap.GetMin() << "' extracted, MMHeap: ";
    heap.ExtractMin();
    heap.printHeap(); //Expected: 2 10 16 4 9 3 14 8 7

    //GetMax/ExtractMax
    cout << "Max value '" << heap.GetMax() << "' extracted, MMHeap: ";
    heap.ExtractMax();
    heap.printHeap(); //Expected: 2 10 14 9 3 4 8 7

    //Insert
    cout << "Inserted element '5' into MMHeap: ";
    heap.Insert(5);
    heap.printHeap(); //Expected: 2 10 14 5 3 4 8 7 9
}

//User interface that handles input of array and all MMHeap function calls
void UIMMHeap()
{   //Set up heap from array
    int arr[128];

    cout << "\nPlease enter array seperated by spaces, -1 to complete array:\n";
    int input;
    cin >> input;
    int i = 0;

    while(input != -1) //copy values to array
    {
        arr[i] = input;
        cin >> input;
        i++;
    }

    MMHeap heap(arr, i); //heap constructor

    cout << "MMHeap: ";
    heap.printHeap();

    //MMHeap Menu
    while (true)
    {
        //User Prompt
        cout << "\nInput: 0 GetMin, 1 GetMax, 2 ExtractMin, 3 ExtractMax, 4 Insert, other for top menu: ";
        int input;
        cin >> input;

        //Menu Options Handler
        switch (input) 
        {
        case 0:
            cout << "Min: " << heap.GetMin() << "\n";
            break;
        case 1:
            cout << "Max: " << heap.GetMax() << "\n";
            break;
        case 2:
            cout << "Min Value '" << heap.GetMin() << "' Extracted\nMMHeap: ";
            heap.ExtractMin();
            heap.printHeap();
            break;
        case 3:
            cout << "Max Value '" << heap.GetMax() << "' Extracted\nMMHeap: ";
            heap.ExtractMax();
            heap.printHeap();
            break;
        case 4:
            int num;
            cout << "Element to be inserted: ";
            cin >> num;

            heap.Insert(num);

            cout << "Element '" << num << "' inserted\nMMHeap: ";

            heap.printHeap();
            break;
        default:
            return;
        }
    }
}

//Main Menu
int main()
{
    while (true) 
    {
        //User Prompt
        cout << "\nType 0 for example, 1 to create an MMHeap, other to quit: ";
        int input;
        cin >> input;

        //Menu Options Handler
        switch (input) 
        {
            case 0:
                UIExample();
                break;
            case 1:
                UIMMHeap();
                break;
            default:
                return 0;
        }
    }

}
