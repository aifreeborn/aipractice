/*
 * =============================================================================
 *
 *       Filename:  aiqueue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年11月28日 10时35分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#ifndef AI_QUEUE_H_
#define AI_QUEUE_H_

class Ai_Customer {
    private:
        long arrive;
        int process_time;

    public:
        Ai_Customer() { arrive = process_time = 0; }
        void set(long when);
        long when() const { return arrive; }
        int ptime() const { return process_time; }
};

typedef Ai_Customer Item;

class Ai_queue {
    private:
       struct Node {
           Item item;
           struct Node *next;
       };
       enum { Q_SIZE = 10 };

       Node *front;
       Node *rear;
       int items;          // current number of items in queue
       const int qsize;    // maximum number of items in queue

       Ai_queue(const Ai_queue &q) : qsize(0) {}
       Ai_queue & operator=(const Ai_queue &q) { return *this; }
    public:
        Ai_queue(int qs = Q_SIZE);
        ~Ai_queue();

        bool isempty() const;
        bool isfull() const;
        int queue_count() const;
        bool enqueue(const Item &item);
        bool dequeue(Item &item);
};

#endif /* AI_QUEUE_H_ */
