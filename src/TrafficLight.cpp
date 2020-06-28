#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 

    // perform queue modification and remove last element from queue
    std::unique_lock<std::mutex> Lock(_mutex);
    _cond.wait(Lock,[this] {return !_messages.empty();});
    
    T input_message = std::move(_messages.back());
    _messages.pop_back();
    return input_message;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> Lock(_mutex);
    _messages.push_back(std::move(msg));
    //std::cout << "sent" << std::endl;
    _cond.notify_one();
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.

    while (true)
        {
            //sleep at every iteration for CPU efficiency  
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if(_queue.receive() == TrafficLightPhase::green){
                return;
            }
        }

}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases,this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 

    std::random_device random_dev; 
    std::mt19937 rng(random_dev()); // Random number generator
    std::uniform_int_distribution<std::mt19937::result_type> distribution(4000, 6000); 
    auto cycle_duration = distribution(rng); // duration of a single simulation cycle in ms
    std::chrono::time_point<std::chrono::system_clock> last_update;

    
    // init stop watch
    last_update = std::chrono::system_clock::now();
    while (true) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // compute time difference to stop watch
        long last_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update).count();
        if (last_time >= cycle_duration) 
        {
            // using ternary operator
            _currentPhase = _currentPhase == TrafficLightPhase::red ? TrafficLightPhase::green : TrafficLightPhase::red;

            // Sends message to message queue
            _queue.send(std::move(_currentPhase));
           // std::cout<<"Sent!"<<std::endl;
            last_update = std::chrono::system_clock::now();
            cycle_duration = distribution(rng); 
        }
    }

}