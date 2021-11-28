#include <iostream>
#include <cstdlib>
#include <ctime>
#include "aiqueue.h"

const int MIN_PER_HR = 60;

bool new_customer(double x);

int main()
{
    // random initializing of rand()
    std::srand(std::time(0));

    std::cout << "Case Study: Bank of Heather Automatic Teller\n";
    std::cout << "Enter maximum size of queue: ";
    int qs;
    std::cin >> qs;
    Ai_queue line(qs);

    std::cout << "Enter the number of simulation hours: ";
    int hours;
    std::cin >> hours;
    long cycle_limit = MIN_PER_HR * hours;

    std::cout << "Enter the average number of customers per hour: ";
    double per_hour;
    std::cin >> per_hour;
    double min_per_cust;
    min_per_cust = MIN_PER_HR / per_hour;

    Item temp;
    long turnaways = 0;
    long customers = 0;
    long served = 0;
    long sum_line = 0;
    int wait_time = 0;
    long line_wait = 0;

    for (int cycle = 0; cycle < cycle_limit; cycle++) {
        if (new_customer(min_per_cust)) {
            if (line.isfull()) {
                turnaways++;
            } else {
                customers++;
                temp.set(cycle);
                line.enqueue(temp);
            }
        }

        if (wait_time <= 0 && !line.isempty()) {
            line.dequeue(temp);
            wait_time = temp.ptime();
            line_wait += cycle - temp.when();
            served++;
        }

        if (wait_time > 0)
            wait_time--;
        sum_line += line.queue_count();
    }

    if (customers > 0) {
        std::cout << "customers accepted: " << customers << std::endl;
        std::cout << "  customers served: " << served << std::endl;
        std::cout << "         turnaways: " << turnaways << std::endl;
        std::cout << "average queue size: ";
        std::cout.precision(2);
        std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
        std::cout << (double) sum_line / cycle_limit << std::endl;
        std::cout << " average wait time: "
            << (double) line_wait / served << " minutes\n";
    } else {
        std::cout << "No customers!\n";
    }
    std::cout << "done!\n";
    return 0; 
}

bool new_customer(double x)
{
    return ((std::rand() * x / RAND_MAX) < 1);
}
