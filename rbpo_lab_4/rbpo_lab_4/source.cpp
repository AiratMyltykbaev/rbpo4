#include <iostream>
#include <initializer_list>
#include <iterator>


class StackBasedOnArray
{
public:
    using Iterator = int*;
    StackBasedOnArray();

    explicit StackBasedOnArray(unsigned size);

    StackBasedOnArray(const StackBasedOnArray& other);

    StackBasedOnArray(StackBasedOnArray&& other);

    StackBasedOnArray(std::initializer_list<int> list);

    ~StackBasedOnArray();

    StackBasedOnArray::Iterator begin();
    const StackBasedOnArray::Iterator begin() const;
    StackBasedOnArray::Iterator end();
    const StackBasedOnArray::Iterator end() const;

    const int& operator[](int index) const;
    int& operator[](int index);

    StackBasedOnArray& operator=(const StackBasedOnArray& other);

    StackBasedOnArray& operator=(StackBasedOnArray&& other);

    StackBasedOnArray& operator=(std::initializer_list<int> ilist);

    int GetSize() const;
    bool Push(const int& element);
    bool Pop(int& element);
    bool Peek(int& element);


private:
    int* arr;
    int count;
};


StackBasedOnArray::StackBasedOnArray() : arr(nullptr), count(0) {}


StackBasedOnArray::StackBasedOnArray(unsigned size) : count(size)
{
    arr = new int[size];
}


StackBasedOnArray::~StackBasedOnArray()
{
    if (count > 0)
        delete[] arr;
}


StackBasedOnArray::StackBasedOnArray(const StackBasedOnArray& other)
{
    arr = new int[other.count];
    count = other.count;
    for (int i = 0; i < count; ++i)
    {
        arr[i] = other.arr[i];
    }
}


StackBasedOnArray::StackBasedOnArray(StackBasedOnArray&& other)
{
    arr = other.arr;
    count = other.count;
    other.arr = nullptr;
}


StackBasedOnArray::StackBasedOnArray(std::initializer_list<int> ilist) : arr(new int[ilist.size()]), count(ilist.size())
{
    int i = 0;
    for (const auto& element : ilist)
    {
        arr[i++] = element;
    }
}


int StackBasedOnArray::GetSize() const
{
    return count;
}


typename StackBasedOnArray::Iterator StackBasedOnArray::begin()
{
    return Iterator(arr);
}

const typename StackBasedOnArray::Iterator StackBasedOnArray::begin() const
{
    return Iterator(arr);
}


typename StackBasedOnArray::Iterator StackBasedOnArray::end()
{
    return Iterator(arr + count);
}


const typename StackBasedOnArray::Iterator StackBasedOnArray::end() const
{
    return Iterator(arr + count);
}

const int& StackBasedOnArray::operator[](int index) const
{
    return arr[index];
}

int& StackBasedOnArray::operator[](int index)
{
    return arr[index];
}


StackBasedOnArray& StackBasedOnArray::operator=(const StackBasedOnArray& other)
{
    if (this != &other)
    {
        delete[] arr;
        arr = new int[other.count];
        count = other.count;
        for (int i = 0; i < count; ++i)
        {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}


StackBasedOnArray& StackBasedOnArray::operator=(StackBasedOnArray&& other)
{
    if (this != &other)
    {
        delete[] arr;
        arr = other.arr;
        count = other.count;
        other.arr = nullptr;
    }
    return *this;
}


StackBasedOnArray& StackBasedOnArray::operator=(std::initializer_list<int> ilist)
{
    delete[] arr;
    arr = new int[ilist.size()];
    count = ilist.size();
    int i = 0;
    for (const auto& element : ilist)
    {
        arr[i++] = element;
    }
    return *this;
}


bool StackBasedOnArray::Push(const int& element)
{

    try
    {
        int* arr2 = new int[count + 1];

        for (int i = 0; i < count; i++)
            arr2[i + 1] = arr[i];

        arr2[0] = element;

        delete[] arr;
        arr = arr2;

        return true;
    }

    catch (...)
    {
        return false;
    }
}


bool StackBasedOnArray::Pop(int& element)
{
    if (count <= 0)
        return false;

    try
    {
        int* arr2 = new int[count - 1];

        element = arr[0];

        count--;

        for (int i = 0; i < count; i++)
            arr2[i] = arr[i + 1];

        delete[] arr;

        arr = arr2;

        return true;
    }
    catch (...)
    {
        return false;
    }

}


bool StackBasedOnArray::Peek(int& element)
{
    if (count > 0)
    {
        element = arr[0];
        return true;
    }

    return false;
}

int main()
{
    StackBasedOnArray stack1;
    StackBasedOnArray stack2(10);
    StackBasedOnArray stack3 = { 1,2,3,4,5,6,7,8,9 };
    stack1 = { 10, 20, 30 };

    stack1.Push(69);

    std::cout << "Elements of stack1: ";
    for (int* i1 = stack1.begin(); i1 != stack1.end(); ++i1)
        std::cout << *i1 << " ";
    std::cout << std::endl;

    int poppedElement;
    if (stack1.Pop(poppedElement))
        std::cout << "Popped element: " << poppedElement << std::endl;
    else
        std::cout << "stack is empty, cannot pop." << std::endl;

    int peekedElement;
    if (stack1.Peek(peekedElement))
        std::cout << "Peeked element: " << peekedElement << std::endl;
    else
        std::cout << "stack is empty, cannot peek." << std::endl;

    std::cout << "Size of stack1: " << stack1.GetSize() << std::endl;
    std::cout << "Size of stack2: " << stack2.GetSize() << std::endl;
    std::cout << "Size of stack3: " << stack3.GetSize() << std::endl;

    std::cout << "Elements of stack1: ";
    for (int* i1 = stack1.begin(); i1 != stack1.end(); ++i1)
        std::cout << *i1 << " ";
    std::cout << std::endl;

    std::cout << "Elements of stack3: ";
    for (int* i3 = stack3.begin(); i3 != stack3.end(); ++i3)
        std::cout << *i3 << " ";
    std::cout << std::endl;

    return 0;
}