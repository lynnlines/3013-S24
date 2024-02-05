#ifndef NODE_H
#define NODE_H

class Node
{
public:
    int value;
    Node *next;
    Node(int _value) : value(_value), next(nullptr) {}
};
#endif