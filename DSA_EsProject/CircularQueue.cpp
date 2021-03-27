#include <iostream>
using namespace std;

int const MAX = 157;

template <typename T>
class CircularQueue
{
public:
    int front;
    int rear;
    int length = 0;
    T circularQueue[MAX];

    CircularQueue() {
        front = 0;
        rear = -1;
    }

    bool IsEmpty()
    {
        //CHECK WHETHER THE QUEUE IS UNDERFLOW/EMPTY OR NOT
        return length == 0;
    }
    bool IsFull()
    {
        //CHECK WHETHER THE QUEUE IS OVERFLOW/FULL OR NOT
        return length == MAX;
    }

    void Enqueue(T x)
    {
        //WRITE CODE FOR ADDING AN ELEMENT INTO THE QUEUE
        //BEFORE THAT CHECK WHETHER THE QUEUE IS OVERFLOW/FULL OR NOT
        if (IsFull()) {
            cout << "Queue OVERFLOW" << endl;
        }
        else {

            if (rear == MAX - 1)
                rear = -1;

            circularQueue[++rear] = x;
            length++;
        }
    }
    T Dequeue()
    {
        //WRITE CODE FOR REMOVING AN ELEMENT FROM THE QUEUE
        //BEFORE THAT CHECK WHETHER THE QUEUE IS UNDERFLOW/EMPTY OR NOT
        if (IsEmpty()) {
            cout << "QUEUE UNDERFLOW" << endl;
            return NULL;
        }
        else {

            T temp = circularQueue[front++];

            if (front == MAX)
                front = 0;

            length--;
            return temp;
        }
    }
    void FirstElement()
    {
        if (!IsEmpty())
        {
            //DISPLAY FIRST ELEMENT OF THE QUEUE
            //T temp = circularQueue[front];
            cout << "front: " << circularQueue[front] << endl;
            //return temp;
        }
    }

    void PrintQueue() {

        //CODE FOR PRINTING THE ELEMENTS OF THE QUEUE
        //BEFORE THAT CHECK WHETHER THE QUEUE IS UNDERFLOW/EMPTY OR NOT
        if (!IsEmpty()) {
            cout << "QUEUE: ";
            for (int l = 0;l < length; l++) {

                cout << circularQueue[front] << " ";
                Enqueue(Dequeue());
            }
            cout << endl;
        }
    }
    void Clear() {

        //CODE FOR CLEARING THE ELEMENTS OF THE QUEUE
        //BEFORE THAT CHECK WHETHER THE QUEUE IS UNDERFLOW/EMPTY OR NOT
        if (!IsEmpty())
        {
            front = 0;
            rear = -1;
            length = 0;
            cout << "Queue is cleared." << endl;
        }
    }
};