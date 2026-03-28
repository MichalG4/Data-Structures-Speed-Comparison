#include <iostream>

using namespace std;
struct DynamicArray
{
    int *array;
    int capacity; //maximum number of elements 
    int length; //nearest unused index
    
    ~DynamicArray(){delete[] array;}
    DynamicArray(){array=new int[5],capacity=5,length=0;}
    DynamicArray(int cap){array=new int[cap],capacity=cap,length=0;}
    void add_ToIndex(int element, int index)
    {
        if(length==capacity) //copy to doubled with offset of 1
        {
            int *newArr=new int[capacity*2];
            for(int i=0;i<index;i++)//everything before index is transfered without offset
            {
                newArr[i]=array[i];
            }
            for(int i=length;i>index;i--)//everything past index is moved with offset of 1
            {
                newArr[i]=array[i-1];
            }
            newArr[index]=element;// insert element into choosen index, capacity doubled
            delete[] array;
            array=newArr;
            capacity*=2;
            length++;
        }
        else
        {
            for(int i=length;i>index;i--) //move every element past index one step forward
            {
                array[i]=array[i-1];
            }
            array[index]=element; //insert element into chosen index
            length++;
        }
        

    }
    void add_End(int element)
    {
    add_ToIndex(element,length);
    }
    void add_Start(int element)
    {
        add_ToIndex(element,0);
    }

};

int main()
{   
      DynamicArray arr(3);  // capacity = 3

    arr.add_End(10);
    arr.add_End(20);
    arr.add_End(30);
    for(int i = 0; i < arr.length; i++)
    {
        cout << i <<" "<< arr.array[i] << endl;
    }
    cout<<endl;
    // tu capacity = 3, length = 3, powinno się podwoić
    arr.add_End(40);  // ← realokacja!
    arr.add_End(50);

    // wyświetl wszystkie elementy
    for(int i = 0; i < arr.length; i++)
    {
        cout << i <<" "<< arr.array[i] << endl;
    }

    cout << "capacity: " << arr.capacity << endl;
    cout << "length: " << arr.length << endl;
    arr.add_ToIndex(60,3);
    for(int i = 0; i < arr.length; i++)
    {
        cout << i <<" "<< arr.array[i] << endl;
    }

    cout << "capacity: " << arr.capacity << endl;
    cout << "length: " << arr.length << endl;
    return 0;
}