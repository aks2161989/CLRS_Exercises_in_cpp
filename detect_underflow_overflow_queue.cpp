// 10.1-4: Rewrite ENQUEUE and DEQUEUE to detect underflow and overflow of a queue
#include <iostream>

using namespace std;

int startPos = 0;
int tailPos = 0;
int headPos = 0;
int overflowCount = 0;
int underflowCount = 0;

void enqueue(int *arr, int arrLen)
{

    char userChoice = 'y';
    while(userChoice == 'y' || userChoice == 'Y')
    {
        int userNum = 0;
        cout << "Enter a number to enqueue: ";
        cin >> userNum;

        if(arr[tailPos] == 0 && (tailPos + 1) != headPos && tailPos != (arrLen - 1))
            arr[tailPos] = userNum;
        else if(tailPos == (arrLen - 1) && arr[0] == 0)
            arr[tailPos] = userNum;
        else
        {
            overflowCount++;
            cout << "Overflow detected at index " << tailPos
            << ". Total overflows detected till now: " << overflowCount << "\n";
            arr[tailPos] = userNum;
        }

        if( tailPos >= startPos && (tailPos + 1) < arrLen)
            tailPos++;
        else if (tailPos < startPos)
            tailPos++;
        else
            tailPos = 0;


        cout << "Enqueue more elements? 'y' for yes: ";
        cin >> userChoice;
    }
}

void dequeue(int *arr, int arrLen)
{
    cout << "Dequeieng an element...\n";

    char userChoice = 'y';
    while(userChoice == 'y' || userChoice == 'Y')
    {
        if(arr[headPos] != 0)
            arr[headPos] = 0;
        else
        {
            underflowCount++;
            cout << "Underflow detected at index " << headPos
            << ". Total underflows detected till now: " << underflowCount << "\n";
            arr[headPos] = 0;
        }

        if( headPos >= startPos && (headPos + 1) < arrLen)
            headPos++;
        else if (headPos < startPos)
            headPos++;
        else
            headPos = 0;


        cout << "Dequeue more elements? 'y' for yes: ";
        cin >> userChoice;
    }
}

void printQueue(int* arr, int arrLen)
{
    for(int index = 0; index < arrLen; ++index)
        cout << arr[index] << ' ';
    cout << '\n';

    arr = nullptr;
}
int main()
{
    int arrLen;
    cout << "How long should the array be? ";
    cin >> arrLen;
    int* arr = new int[arrLen] {0};
    printQueue(arr, arrLen);

    cout << "Where to start the queue? ";
    cin >> startPos;
    headPos = tailPos = startPos;

    enqueue(arr, arrLen);
    printQueue(arr, arrLen);

    dequeue(arr, arrLen);
    printQueue(arr, arrLen);

    return 0;
}
