/*
 * =============================================================================
 *
 *       Filename:  aiqueue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年11月28日 10时35分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <iostream>
#include "aiqueue.h"

void Ai_Customer::set(long when)
{
    process_time = std::rand() % 3 + 1;
    arrive = when;
}

Ai_queue::Ai_queue(int qs)
        : front(nullptr),
        rear(nullptr),
        items(0),
        qsize(qs)
{
    /* Empty */
}

bool Ai_queue::isempty() const
{
    return items == 0;
}

bool Ai_queue::isfull() const
{
    return items == qsize;
}

int Ai_queue::queue_count() const
{
    return items;
}

bool Ai_queue::enqueue(const Item &item)
{
    if (isfull())
        return false;

    Node *add = new Node;

    add->item = item;
    add->next = nullptr;
    items++;
    if (front == nullptr)
        front = add;
    else
        rear->next = add;
    rear = add;
    return true;
}

bool Ai_queue::dequeue(Item &item)
{
    if (isempty())
        return false;

    item = front->item;
    items--;
    Node *temp = front;
    front = front->next;
    delete temp;
    if (items == 0)
        rear = nullptr;
    return true;
}

Ai_queue::~Ai_queue()
{
    Node *temp;

    while (front != nullptr) {
        temp = front;
        front = front->next;
        delete temp;
    }
}
