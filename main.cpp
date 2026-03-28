#include <iostream>
#include <chrono>

using namespace std;
struct Interface
{
    virtual void add_Index(int element, int index) = 0;
    virtual void add_End(int element) = 0;
    virtual void add_Start(int element) = 0;
    virtual void remove_Index(int index) = 0;
    virtual void remove_End() = 0;
    virtual void remove_Start() = 0;
    virtual int find(int element) = 0;
    virtual ~Interface() {}
};
struct DynamicArray : public Interface

{
    int *array;
    int capacity; //maximum number of elements 
    int length; //nearest unused index
    
    ~DynamicArray(){delete[] array;}
    DynamicArray(){array=new int[5],capacity=5,length=0;}
    DynamicArray(int cap){array=new int[cap],capacity=cap,length=0;}
    void add_Index(int element, int index) override
    {
        if(0<=index && index<=length)
        {
            if(length==capacity) //copy to doubled
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
        else
        {
            cout<<"out of bounds!"<<endl;
        }
        
        

    }
    void add_End(int element) override
    {
    add_Index(element,length);
    }

    void add_Start(int element) override
    {
        add_Index(element,0);
    }

    void remove_Index(int index) override
    {
        if(0<=index && index<length)
        {
            length--;
            for(int i=index;i<length;i++)
            {
                array[i]=array[i+1];
            }  
        }
        else 
        {
            cout<<"out of bounds!"<<endl;
        }
    }

    void remove_End() override
    {

        if(length!=0)length--;
        else cout<<"out of bounds!"<<endl;
    }

    void remove_Start() override
    {
        remove_Index(0);
    }
    int find(int element) override
    {
        for(int i=0;i<length;i++)
        {
            if(array[i]==element) return i;
        }
         return -1; 
    }
};

struct Node
{
    int item;
    Node* next;
    Node(int a){item=a;next=nullptr;}
};
struct LinkedList : public Interface
{
    Node* head;
    int length;
    LinkedList(){head=nullptr;length=0;}
    ~LinkedList()
    {
        Node* current = head;
        while(current!=nullptr)
        {
            Node* next=current->next;
            delete current;
            current=next;
        }
    }
    void add_Index(int element, int index) override
    {
        
        if(0<=index && index<=length)
        {
            if (index==0)
            {
                Node* newNode=new Node(element);
                newNode->next=head;
                newNode->item=element;
                head=newNode;
                length++;  
            }
            else
            {
                Node* newNode=new Node(element);
                Node* current=head;
                for(int i=0;i<index-1;i++)
                {
                    current=current->next;
                }
                newNode->next=current->next;
                current->next=newNode;
                length++;   
            }
 
        }
        else
        {
            cout<<"out of bounds!"<<endl;
        }
    }
    void add_End(int element) override 
    { 
        add_Index(element,length); 
    }
    void add_Start(int element) override 
    { 
        add_Index(element,0); 
    }
    void remove_Index(int index) override
    {
        if(0<=index && index<length)
        {
            if(index==0)
            {
                Node* temp=head->next;
                delete head;
                head=temp;
                length--;
            }
            else
            {
                Node* temp=nullptr;
                Node* current=head;
                for(int i=0;i<index-1;i++)
                {
                    current=current->next;
                }
                temp=current->next;
                current->next=temp->next;   
                delete temp;
                length--;
            }

        }
        else
        {
            cout<<"out of bounds!"<<endl;
        }
    }
    void remove_Start() override
    {
        remove_Index(0);
    }
    void remove_End() override
    {
        if(length!=0) remove_Index(length-1);
        else cout<<"out of bounds!"<<endl;
    }
    int find(int element) override
    {
        Node* current=head;
        for(int i=0;i<length;i++)
        {
            if(current->item==element) return i;
            current=current->next;
        }
        return -1;
    }
};
// ===== BENCHMARK HELPERS =====
using ms = chrono::duration<double, milli>;

double measure(auto func)
{
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<ms>(end - start).count();
}

void printRow(const string& op, double da, double ll)
{
    cout << "| " << left;
    cout.width(16); cout << op;
    cout << "| ";
    cout.width(14); cout << da;
    cout << "| ";
    cout.width(14); cout << ll;
    cout << "|" << endl;
}

void printSeparator()
{
    cout << "+-----------------+--------------+--------------+" << endl;
}
void runBenchmark(const string& label, int N)
{
    cout << "\n========================================" << endl;
    cout << "  " << label << " (N = " << N << ")" << endl;
    cout << "========================================" << endl;
    printSeparator();
    cout << "| Operacja        | DynamicArray | LinkedList   |" << endl;
    printSeparator();

    // --- add_End ---
    {
        DynamicArray da(N);
        LinkedList   ll;
        double t_da = measure([&](){ for(int i=0;i<N;i++) da.add_End(i); });
        double t_ll = measure([&](){ for(int i=0;i<N;i++) ll.add_End(i); });
        printRow("add_End", t_da, t_ll);
    }

    // --- add_Start ---
    {
        DynamicArray da(N);
        LinkedList   ll;
        double t_da = measure([&](){ for(int i=0;i<N;i++) da.add_Start(i); });
        double t_ll = measure([&](){ for(int i=0;i<N;i++) ll.add_Start(i); });
        printRow("add_Start", t_da, t_ll);
    }

    // --- add_Index (middle) ---
    {
        DynamicArray da(N);
        LinkedList   ll;
        double t_da = measure([&](){ for(int i=0;i<N;i++) da.add_Index(i, da.length/2); });
        double t_ll = measure([&](){ for(int i=0;i<N;i++) ll.add_Index(i, ll.length/2); });
        printRow("add_Index(mid)", t_da, t_ll);
    }

    // fill for remove/find tests
    DynamicArray da_full(N);
    LinkedList   ll_full;
    for(int i=0;i<N;i++){ da_full.add_End(i); ll_full.add_End(i); }

    // --- find (worst case: last element) ---
    {
        double t_da = measure([&](){ for(int i=0;i<1000;i++) da_full.find(N-1); });
        double t_ll = measure([&](){ for(int i=0;i<1000;i++) ll_full.find(N-1); });
        printRow("find (worst)", t_da, t_ll);
    }

    // --- remove_End ---
    {
        DynamicArray da(N); LinkedList ll;
        for(int i=0;i<N;i++){ da.add_End(i); ll.add_End(i); }
        double t_da = measure([&](){ for(int i=0;i<N;i++) da.remove_End(); });
        double t_ll = measure([&](){ for(int i=0;i<N;i++) ll.remove_End(); });
        printRow("remove_End", t_da, t_ll);
    }

    // --- remove_Start ---
    {
        DynamicArray da(N); LinkedList ll;
        for(int i=0;i<N;i++){ da.add_End(i); ll.add_End(i); }
        double t_da = measure([&](){ for(int i=0;i<N;i++) da.remove_Start(); });
        double t_ll = measure([&](){ for(int i=0;i<N;i++) ll.remove_Start(); });
        printRow("remove_Start", t_da, t_ll);
    }

    // --- remove_Index (middle) ---
    {
        DynamicArray da(N); LinkedList ll;
        for(int i=0;i<N;i++){ da.add_End(i); ll.add_End(i); }
        double t_da = measure([&](){ while(da.length>0) da.remove_Index(da.length/2); });
        double t_ll = measure([&](){ while(ll.length>0) ll.remove_Index(ll.length/2); });
        printRow("remove_Index(mid)", t_da, t_ll);
    }

    printSeparator();
    cout << "  Czas w milisekundach [ms]" << endl;
}

int main()
{
    runBenchmark("MALE",   10000);
    runBenchmark("SREDNIE",100000);
   // runBenchmark("DUZE",   1000000);
    return 0;
}