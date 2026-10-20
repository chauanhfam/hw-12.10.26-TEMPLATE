#include <iostream>
using namespace std;
template <typename T>
class Array
{
    int count;
    int capacity;
    T* data;
    int grow;

public:
    Array(int grow = 1)
    {
        count = 0;
        capacity = 0;
        data = nullptr;
        this->grow = grow > 0 ? grow : 1;
    }

    Array(const Array<T>& other)
    {
        count = other.count;
        capacity = other.capacity;
        grow = other.grow;

        if (capacity > 0)
        {
            data = new T[capacity];

            for (int i = 0; i < count; i++)
            {
                data[i] = other.data[i];
            }
        }
        else
        {
            data = nullptr;
        }
    }

    ~Array()
    {
        delete[] data;
    }

    int GetSize() const
    {
        return capacity;
    }

    void SetSize(int newSize, int newGrow = 1)
    {
        if (newSize < 0)
        {
            return;
        }

        if (newGrow > 0)
        {
            grow = newGrow;
        }

        if (newSize == 0)
        {
            delete[] data;
            data = nullptr;
            count = 0;
            capacity = 0;
            return;
        }

        T* newData = new T[newSize];

        int newCount = count;

        if (newCount > newSize)
        {
            newCount = newSize;
        }

        for (int i = 0; i < newCount; i++)
        {
            newData[i] = data[i];
        }

        delete[] data;

        data = newData;
        count = newCount;
        capacity = newSize;
    }

    int GetUpperBound() const
    {
        return count - 1;
    }

    bool IsEmpty() const
    {
        return count == 0;
    }

    void FreeExtra()
    {
        if (capacity == count)
            return;

        if (count == 0)
        {
            delete[] data;
            data = nullptr;
            capacity = 0;
            return;
        }

        T* newData = new T[count];

        for (int i = 0; i < count; i++)
            newData[i] = data[i];

        delete[] data;

        data = newData;
        capacity = count;
    }

    void RemoveAll()
    {
        delete[] data;
        data = nullptr;
        count = 0;
        capacity = 0;
    }

    T GetAt(int index) const
    {
        if (index < 0 || index >= count)
        {
            return T();
        }

        return data[index];
    }

    void SetAt(int index, T value)
    {
        if (index >= 0 && index < count)
        {
            data[index] = value;
        }
    }

    T& operator[](int index)
    {
        return data[index];
    }

    const T& operator[](int index) const
    {
        return data[index];
    }

    void Add(T value)
    {
        if (count == capacity)
        {
            SetSize(capacity + grow, grow);
        }

        data[count] = value;
        count++;
    }

    void Append(const Array<T>& other)
    {
        for (int i = 0; i < other.count; i++)
        {
            Add(other.data[i]);
        }
    }

    Array<T>& operator=(const Array<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }

        T* newData = nullptr;

        if (other.capacity > 0)
        {
            newData = new T[other.capacity];

            for (int i = 0; i < other.count; i++)
            {
                newData[i] = other.data[i];
            }
        }

        delete[] data;

        data = newData;
        count = other.count;
        capacity = other.capacity;
        grow = other.grow;

        return *this;
    }

    T* GetData() const
    {
        return data;
    }

    void InsertAt(int index, T value)
    {
        if (index < 0 || index > count)
        {
            return;
        }

        if (count == capacity)
        {
            SetSize(capacity + grow, grow);
        }

        for (int i = count; i > index; i--)
        {
            data[i] = data[i - 1];
        }

        data[index] = value;
        count++;
    }

    void InsertAt(int index, int number, T value)
    {
        if (index < 0 || index > count || number <= 0)
        {
            return;
        }

        for (int i = 0; i < number; i++)
        {
            InsertAt(index + i, value);
        }
    }
    void RemoveAt(int index, int number = 1)
    {
        if (index < 0 || index >= count || number <= 0)
        {
            return;
        }

        if (index + number > count)
        {
            number = count - index;
        }

        for (int i = index; i < count - number; i++)
        {
            data[i] = data[i + number];
        }

        count -= number;
    }
};
int main()
{
    Array<int> arr(5);

    cout << "Size: " << arr.GetSize() << endl;
    cout << "UpperBound: " << arr.GetUpperBound() << endl;
    cout << "IsEmpty: " << arr.IsEmpty() << endl;

    arr.SetSize(5, 5);

    arr.Add(10);
    arr.Add(20);
    arr.Add(30);
    arr.Add(40);

    cout << "\nSize: " << arr.GetSize() << endl;
    cout << "UpperBound: " << arr.GetUpperBound() << endl;

    cout << "Elements: ";
    for (int i = 0; i <= arr.GetUpperBound(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    arr.InsertAt(1, 15);

    cout << "After InsertAt: ";
    for (int i = 0; i <= arr.GetUpperBound(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    arr.RemoveAt(2);

    cout << "After RemoveAt: ";
    for (int i = 0; i <= arr.GetUpperBound(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    arr.FreeExtra();

    cout << "Size after FreeExtra: " << arr.GetSize() << endl;

    return 0;
}