/**
 * Class Vector
 *
 * Description:
 *      Implements a linked list to replicate a vector. Is of type integer
 *
 * Public Methods:
 *          Vector()
 *          Vector(string)
 *          Vector(int arr[], int size)
 *
 *  void    pushFront(int)
 *  void    pushFront(Vector)
 *  void    pushRear(int)
 *  void    pushRear(Vector)
 *  void    pushAt(int, int)
 *  void    inOrderPush(int)
 *
 *  int     popRear()
 *  int     popFront()
 *  int     popAt(int)
 *
 *  int     find(int)
 *
 *  void    print()
 *
 * Usage:
 *      Vector v1("input.dat")      // reads values for vector from input.dat
 *
 *      v1.pushFront(5)             // pushs the 5 to the front of v1
 *
 */
#ifndef VECTOR_H
#define VECTOR_H
#include "Node.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Vector
{
private:
    Node *front; // keeps track of the front of the vector
    Node *rear;  // keeps track of the rear of the vector

public:
    Vector() // default constructor
    {
        front = rear = nullptr;
    }

    Vector(string file) // infile constructor
    {
        ifstream infile;
        infile.open(file); // opens files

        Node *newN;
        Node *travel;
        int value;

        infile >> value;        // reads in first line of file
        newN = new Node(value); // sets front of vector to value
        front = travel = newN;

        while (!infile.eof()) // reads until reaches the end of the file
        {
            infile >> value; // grabs file data for each line
            newN = new Node(value);

            travel->next = newN;   // adds to vector
            travel = travel->next; // moves to next vector spot
        }

        rear = travel; // initializes rear to the last file value
    }

    Vector(int arr[], int size) // parameterized constructor from array
    {
        Node *newN;   // pointers to make new spot in vector
        Node *travel; // and travel the vector

        // loops through the array
        for (int i = 0; i < size; i++)
        {
            newN = new Node(arr[i]);

            if (!i) // sets the first index to front & travel
            {
                front = travel = newN;
            }
            else
            {
                travel->next = newN;
                travel = travel->next;
            }
        }
        rear = travel; // sets the rear to the end of the array
    }

    void pushFront(int val) // pushes val to front of vector
    {
        Node *newN = new Node(val);

        if (front) // if front is initialized
        {
            newN->next = front;
            front = newN;
        }
        else // sets first object to front and rear
        {
            front = rear = newN;
        }
    }

    void pushFront(Vector vec) // pushes vec to front of this vector
    {
        Node *newN;
        Node *newHead = nullptr; // the new front
        Node *ogFront;           // the old front
        Node *travel;            // travels vec
        Node *frontVec;          // travels the front of this vec,
                                 // the newHead section of this vec
        ogFront = front;

        travel = vec.front;

        // start with initializing front to front of the new vec
        // keep on squeezing in the nodes until you reach the nullptr
        // up its next up to the og front
        while (travel)
        {
            newN = new Node(travel->value);

            if (!newHead) // if the newHead has not be initialized
            {
                frontVec = newHead = newN;
                travel = travel->next;
            }
            else
            {
                // travels vec
                travel = travel->next;

                frontVec->next = newN;

                // travels the front of this vec
                frontVec = frontVec->next;
            }
        }

        // attaches the front to the original vector
        frontVec->next = ogFront->next;
        front = newHead;
    }

    void pushRear(int val) // pushes val to rear of vector
    {
        Node *newN = new Node(val);

        if (rear) // if rear exist, adds to rear
        {
            rear->next = newN;
            rear = newN;
        }
        else // creates front and rear if there is none
        {
            front = rear = newN;
        }
    }

    void pushRear(Vector vec) // pushes vec to rear of this vector
    {
        Node *newN;
        Node *travel; // travels vec

        travel = vec.front;

        while (travel)
        {
            newN = new Node(travel->value);

            // adds to rear
            rear->next = newN;
            rear = newN;
            travel = travel->next;
        }
    }

    void pushAt(int index,
                int val) // pushes val to the vector[index]
    {
        int i = 0; // keeps track of index in vector
        Node *travel = front;
        Node *newN = new Node(val);

        while (!(i && index)) // while i !== index
        {
            travel = travel->next;
            i++;
        }

        newN->next = travel->next;
        travel->next = newN;
    }

    void inOrderPush(int val) // pushes val in order of the vector values
    {
        Node *newN = new Node(val);
        Node *travel;
        Node *prev;
        prev = travel = front;

        // descending order
        if (front->value > rear->value)
        {
            while (travel && front->value > travel->value)
            {
                prev = travel;
                travel = travel->next;
            }
        }
        // ascending order
        else
        {
            while (travel && front->value < travel->value)
            {
                prev = travel;
                travel = travel->next;
            }
        }

        newN->next = travel;
        prev->next = newN;
    }

    int popFront() // pops the front of the vector
    {
        int pop = front->value; // grabs value about to be popped
        Node *temp = front;
        front = front->next;

        delete temp; // deallocates memory
        return pop;
    }

    int popRear() // pops the rear of the vector
    {

        int pop = rear->value;
        Node *travel = front;
        Node *temp = rear;

        // travels vec to grab rear and rear - 1
        while (travel->next != rear)
        {
            travel = travel->next;
        }

        travel->next = nullptr;
        rear = travel;

        delete temp; // deallocates memory
        return pop;
    }

    int popAt(int index) // pops vector[index]
    {
        Node *prev;
        Node *current;
        int pop;
        int i = 0; // keeps track of index in vector

        current = prev = front;

        while (i < index)
        {
            prev = current;
            current = current->next;
            i++;
        }
        pop = current->value;
        prev->next = current->next;

        delete current; // deallocates memory

        return pop;
    }

    int find(int val) // finds value in vector,
                      // return -1 if not found
    {
        Node *travel = front;
        int i = 0; // keeps track of index

        while (travel)
        {
            if (val == travel->value)
            {
                return i;
            }
            travel = travel->next;
            i++;
        }
        return -1; // returns -1 if not found
    }

    void print(ofstream
                   &outfile) // prints to outfile
    {
        Node *travel = front;

        outfile << "[ ";

        while (travel)
        {
            outfile << travel->value;
            travel->next &&outfile << " , ";

            travel = travel->next;
        }
        outfile << " ]\n";
    }
};
#endif