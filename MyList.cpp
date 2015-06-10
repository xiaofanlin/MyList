#include<iostream>
using namespace std;

template <class T>
class MyList{
    //declare friend function
    template<class C,class D>
    friend MyList<C> operator + (const MyList<C> &l1, const MyList<D> &l2);

    template<class C>
    friend MyList<C> operator + (const MyList<C> &l1, const MyList<C> &l2);

    template<class C>
    friend MyList<C> operator + (const MyList<C> &l1, const C &item);

    template<class C>
    friend ostream & operator<<(ostream &os, const MyList<C> &obj);

private:
	T *a;
	int size;
	int rear;//the number of array elements
	void double_space()//expand space if not large enough
	{
	    size *= 2;
	    T *tmp;
	    tmp = new T [size];
	    for (int i = 0; i < rear; ++i) tmp[i] = a[i];
	    delete []a;
	    a = tmp;
	}

    //quick sort functions of up
	int divide_up(T a[], int low, int high)
	{
	    T k = a[low];

	    do{while (low < high && a[high] >= k) --high;
	    if(low < high) {a[low] = a[high]; ++low;}
	    while (low < high && a[low] <= k) ++low;
	    if (low < high) {a [high] = a[low]; --high;}
	    } while (low !=high);
	    a[low] = k;
	    return low;
	}
	void quicksort_up(T a [], int low, int high)
	{
	    int mid;
	    if (low >= high) return ;
	    mid = divide_up(a, low, high);
	    quicksort_up(a, low, mid - 1);
	    quicksort_up(a, mid + 1, high);
	}

    //quick sort functions of down
	int divide_down(T a[], int low, int high)
	{
	    T k = a[low];

	    do{while (low < high && a[high] <= k) --high;
	    if(low < high) {a[low] = a[high]; ++low;}
	    while (low < high && a[low] >= k) ++low;
	    if (low < high) {a [high] = a[low]; --high;}
	    } while (low !=high);
	    a[low] = k;
	    return low;
	}

	void quicksort_down(T a [], int low, int high)
	{
	    int mid;
	    if (low >= high) return ;
	    mid = divide_down(a, low, high);
	    quicksort_down(a, low, mid - 1);
	    quicksort_down(a, mid + 1, high);
	}

public:

	MyList()
	{
		size = 100;
		a = new T [size];
		rear = 0;
	}

	MyList(int num, const T &item)//initialize with num item
	{
	    size = max(num,100);
		a = new T [size];
		rear=0;
	    for (int i = 0;i < num; ++i)
        {
            a[i] = item;
        }
        rear = num;
	}

	MyList(const MyList &l)//copy function
	{
	    delete []a;
	    size = l.size;
	    rear = l.rear;
	    a = new T [l.size];
	    for (int i = 0; i < l.rear; ++i)
        {
            a[i] = l.a[i];
        }
	}

	MyList(T* arr, int len)//initialize with an c++ array
	{
	    size = max(len, 100);
	    rear = 0;
	    a = new T [size];
	    for (int i = 0; i < len; ++i)
        {
            a[i] = arr[i];
            ++rear;
        }
	}

	void push(const T &item)//push the item into MyList
	{
	    try{
            if (rear >= size) throw size;
            a[rear] = item; ++rear;
            }
        catch (int) {double_space(); a[rear] = item; ++rear;}
	}

    T pop()//pop the last element
    {
        try{
        if (rear == 0) throw rear;
        T tmp = a[rear-1];
        --rear;
        return tmp;
        }
        catch (int) {cerr << "Empty array" << endl;}
    }

    void insert(int index, const T &item)//insert item in index
    {
        try{
        if (rear >= size) throw size;//space is not enough
        for (int i = rear; i > index; --i) a[i] = a[i-1];
        a[index] = item;
        ++rear;
        }
        catch (int) {
            double_space();
            for (int i = rear; i > index; --i) a[i] = a[i-1];
            a[index] = item;
            ++rear;
            }
    }

    void clean()//clean up array
    {
        rear = 0;
        T *tmp;
        tmp = new T[size];
        delete []a;
        a = tmp;
    }

    int get_size()
    {
        return rear;
    }

    void erase(int start, int end)
    {
        try{
            if (start < 0) start += rear;//transform into positive number
            if (end < 0) end += rear;

            if (start > end) throw false;//throw exception
            if (end > rear) throw end;
            T *tmp;
            tmp=new T [size];
            for (int i = 0; i < start; ++i)
            {
                tmp[i] = a[i];
            }
            for (int i = end+1; i < rear; ++i)
            {
                tmp[start+i-end-1] = a[i];
            }
            rear -= end-start+1;
            delete [] a;
            a = tmp;
        }
        catch (bool) {cerr << "wrong input" << endl;}
        catch (int) {cerr << "end beyond scope" << end;}

    }

    T get_item(int index)
    {
        return a[index];
    }

    MyList get_item(int start, int end)
    {
        try
        {
            if (start < 0) start += rear;
            if (end < 0) end += rear;
            if (start > end)
            {
                MyList <T> tmp;
                return tmp;
            }
            if (end > rear) throw end;
            MyList <T> tmp(a+start, end-start+1);//use initialize function
            return tmp;
        }
        catch (int) {cerr << "end beyond scope" << endl;}
    }

    int count(const T &item)
    {
        int cnt=0;
        for (int i = 0; i < rear; ++i) if (a[i] == item) ++cnt;
        return cnt;
    }

    void remove(const T &item)
    {
        try
        {
            bool flag = false;//to judge whether item exist or not
            if (rear == 0) throw false;
            int i = 0;
            for (;i < rear; ++i)
            {
                if (a[i] == item)
                {
                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                for (; i < (rear - 1); ++i)
                {
                    a[i] = a[i+1];
                }
                --rear;
            }
            else throw rear;
        }
        catch (int) {cerr << "No such item" << endl;}
        catch (bool) {cerr << "Empty array" << endl;}
    }

    MyList &operator = (const MyList &l)
    {
        if (this == &l) return *this;
        delete [] a;
        size = l.size;
        rear = l.rear;
        T *storage;//temp point
        storage = new T [size];
        for (int i = 0; i < l.rear; ++i) storage [i] = l.a [i];
        a = storage;
        return *this;
    }

    MyList &operator += (const T &item)
    {
        try
        {
            if (rear >= size) throw rear;
            a [rear] = item;
            ++rear;
            return *this;
        }
        catch (int)
        {
            double_space();
            a [rear] = item;
            ++rear;
            return *this;
        }
    }

    MyList &operator += (const MyList &l)
    {
        try
        {
            if ((rear + l.rear) > size) throw size;//beyond size,we need to double space
            for (int i = rear; i < (rear + l.rear); ++i) a [i] = l.a [i - rear];
            rear += l.rear;
            return *this;
        }
        catch (int)
        {
            size += l.size;
            T *storage;
            storage = new T [size];
            int i = 0;
            for (; i < rear; ++i) storage [i] = a [i];
            for (int j = 0; j < l.rear; ++j) storage [rear + j] = l.a [j];
            delete [] a;
            a = storage;
            rear += l.rear;
            return *this;
        }
    }

    T &operator [](int index)
    {
        try
        {
            if (index >=rear || index < 0) throw rear;
            return a [index];
        }
        catch (int) {cerr << "Beyond boundary" << endl;}

    }

    void sort(bool less=true)
    {
        try
        {
            if (rear == 0) throw rear;
            if (less) quicksort_up (a, 0, rear - 1);
            else quicksort_down (a, 0, rear - 1);
        }
        catch (int) {cerr << "Empty array" << endl;}
    }

    void reverse()
    {
        T *storage;
        storage = new T [size];
        for (int i = rear - 1; i >= 0; --i) storage [rear - i -1] = a [i];
        delete [] a;
        a = storage;
    }


	~MyList(){delete [] a;}
};

//set class C, class D so that we can get different type MyList
template<class C, class D>
MyList<C> operator + (const MyList<C> &l1, const MyList<D> &l2)
{
    cerr << "They are different type" << endl;
}

template<class C>
MyList<C> operator + (const MyList<C> &l1, const MyList<C> &l2)
{
    MyList<C> tmp;
    tmp.rear = l1.rear +l2.rear;
    tmp.size = tmp.rear;
    C *storage;
    storage = new C [tmp.size];
    for (int i = 0; i < l1.rear; ++i)
    {
        storage [i] = l1.a[i];
    }
    for (int i = 0; i < l2.rear; ++i)
    {
        storage [l1.rear + i] = l2.a[i];
    }
    tmp.a = storage;
    return tmp;
}

template<class C>
MyList<C> operator + (const MyList<C> &l1, const C &item)
{
    MyList<C> tmp;
    tmp.size = l1.size + 1;
    tmp.rear = l1.rear + 1;
    C *storage;
    storage = new C [tmp.size];
    for (int i = 0; i < l1.rear; ++i)
    {
        storage [i] = l1.a [i];
    }
    storage [tmp.rear - 1] = item;
    tmp.a = storage;
    return tmp;

}

template<class C>
ostream & operator<<(ostream &os, const MyList<C> &obj)
{
    try
        {
            if (obj.rear == 0) throw obj.rear;
            os << "[";
            for (int i = 0; i < (obj.rear - 1); ++i) os << obj.a [i] << "," << " ";
            os << obj.a [obj.rear - 1] << "]" ;//specially deal with the last one should
            return os;
        }
        catch (int) {cerr << "Empty array" << endl;}
}
