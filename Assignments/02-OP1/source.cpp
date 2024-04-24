/*****************************************************************************
*
*  Author:           Caitlin Allison
*  Email:            cnallison1211@my.msutexas.edu
*  Label:            Vector Class
*  Title:            Vector Class
*  Course:           3013-201
*  Semester:         Spring 2024
*
*  Description:
*        This program will take in a vector from an array, an input
*   file, or another vector and create a new vector from it. Its structure
*   uses a linked list of integers to expand and downsize like a vector.
*   It has the properties of pop, push, and print along with a few others
*   so to achieve it acting like a vector.
*  Usage:
*        To use the input file option of the vector, please include a
*   a file named "input.dat". All the output from this program will be sent
*   to a file named "test.out".
*  Files:   source.cpp: main code
            Vector.h: header file for Vector class
            Node.h: header file for Node class
*****************************************************************************/

#include "Vector.h"
#include <fstream>
#include <iostream>

void heading(ofstream &outfile);

int main()
{
    ofstream outfile;
    outfile.open("test.out");

    heading(outfile);

    int x = 0;

    Vector v1;
    v1.pushFront(18);
    v1.pushFront(20);
    v1.pushFront(25);
    v1.pushRear(18);
    v1.pushRear(20);
    v1.pushRear(25);
    v1.print(outfile);

    int A[] = {11, 25, 33, 47, 51};
    Vector v2(A, 5);
    v2.print(outfile);

    v2.pushFront(9);
    v2.pushRear(63);
    v2.print(outfile);

    v1.pushRear(v2);
    v1.print(outfile);

    x = v1.popFront();
    x = v1.popFront();
    x = v1.popFront();
    v1.print(outfile);
    outfile << x << endl;

    x = v1.popRear();
    x = v1.popRear();
    x = v1.popRear();
    v1.print(outfile);
    outfile << x << endl;

    v2.print(outfile);
    x = v2.popAt(3);
    v2.print(outfile);
    outfile << x << endl;

    x = v2.find(51);
    outfile << x << endl;

    x = v2.find(99);
    outfile << x << endl;

    Vector v3(v1);
    v3.print(outfile);

    v3.pushFront(v2);
    v3.print(outfile);

    Vector v4("input.dat");
    v4.pushRear(v3);
    v4.print(outfile);
}

void heading(ofstream &outfile)
{
    outfile << "Caitlin Allison\n"
            << "Feb. 5 2024\n"
            << "Spring 2024\n\n";
}
