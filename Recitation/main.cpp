#include <iostream>

using namespace std;

void arrayDynamicAllocation(int array[], int size, int number){
    int *oldArray = array;
    int size_new = size;
    for (int i = 0; i < size_new; i++)
    {
        cout << oldArray[i] << "\n" << endl;
    }
    for (int i = 0; i < number; i++)
    {
        int *newArray = new int [size_new * 2];
        for (int j = 0; j < size_new * 2; j++)
        {
            if (j < size_new) {
                newArray[j] = oldArray[j];
            }
            else {
                newArray[j] = oldArray[j - size_new] * 2;
            }
        }
        size_new *= 2;
        delete[] oldArray;
        oldArray = newArray;
    }
    for (int i = 0; i < size_new; i++)
    {
        cout << oldArray[i] << endl;
    }
}

int main()
{
    int arr[] = {0,1};
    arrayDynamicAllocation(arr, 2, 3);
}
