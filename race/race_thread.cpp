//including libraries
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdlib.h>

//initailising length of the race
int race_length=100;

//initail positions of hare and turtle
int hare_position=0,turtle_position=0;

//initailising mutex variables
std::mutex hare_mtx;
std::mutex turtle_mtx;

//hare thread
void hare()
{
    //initailising clock for thread syncronisation
    using clock = std::chrono::steady_clock;
    
    //race will continue untill someone wins
    while(hare_position<=race_length && turtle_position<=race_length)
    {
        //time step of 1 milliseconds
        clock::time_point next_time_point = clock::now() + std::chrono::milliseconds(1);
        
        //mutual exclusion for hare_position
        hare_mtx.lock();
        hare_position = hare_position + 5;
        hare_mtx.unlock();
        
        //waiting for next time step
        std::this_thread::sleep_until(next_time_point);
        
        //if hare is ahead of turtle and has reached the half-way of race track, then it sleep for random amount of time
        if(hare_position>=race_length/2 && hare_position>turtle_position)
        {
            hare_mtx.lock();
            std::cout<<"Hare Sleeps\n\n";
            hare_mtx.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1 * (rand() % 75 + 1)));
            hare_mtx.lock();
            std::cout<<"Hare Wake ups\n\n";
            hare_mtx.unlock();
        }
    }

}

//turtle thread
void turtle()
{
    //initailising clock for thread syncronisation
    using clock = std::chrono::steady_clock;
    
    //race will continue untill someone wins
    while(hare_position<=race_length && turtle_position<=race_length)
    {
        //time step of 1 milliseconds
        clock::time_point next_time_point = clock::now() + std::chrono::milliseconds(1);
        
        //mutual exclusion for turtle_position
        turtle_mtx.lock();
        turtle_position = turtle_position + 1;
        turtle_mtx.unlock();
        
        //waiting for next time step
        std::this_thread::sleep_until(next_time_point);
    }
}

//reporter thread
void reporter()
{
    //initailising clock for thread syncronisation
    using clock = std::chrono::steady_clock;
    
    //race will continue untill someone wins
    while(hare_position<=race_length && turtle_position<=race_length)
    {
        //time step of 1 milliseconds
        clock::time_point next_time_point = clock::now() + std::chrono::milliseconds(1);
        
        //mutual exclusion for hare_position
        hare_mtx.lock();
        std::cout<<"Hare Position = "<<hare_position<<"\n";       //reporting Position of hare
        hare_mtx.unlock();
        
        //mutual exclusion for turtle_position
        turtle_mtx.lock();
        std::cout<<"Turtle Position = "<<turtle_position<<"\n\n";        //reporting Position of turtle
        turtle_mtx.unlock();
        
        //waiting for next time step
        std::this_thread::sleep_until(next_time_point);
    }
}

//god thread
void god()
{
    //variables
    int initial,choice,repos=0,repos_prob;
    
    //initailising clock for thread syncronisation
    using clock = std::chrono::steady_clock;
    
    //loop will continue untill someone wins or reposition has not taken place
    while(hare_position<=race_length && turtle_position<=race_length && repos==0)
    {
        //time step of 1 milliseconds
        clock::time_point next_time_point = clock::now() + std::chrono::milliseconds(1);
        
        //reposition probability
        repos_prob=rand() % 10;
        
        //if repos_prob is 5, then reposition will take place
        if(repos_prob==5)
        {
            
            
            //mutex locks
            hare_mtx.lock();
            turtle_mtx.lock();
        
            std::cout<<"God intervenes in the Race\n\n";
            
            //message asking choice to reposition
            //if choice is 1, then hare will be repositioned
            //if choice is 2, then turtle will be repositioned
            //if choice is 3, then both hare and turtle will be repositioned
            std::cout<<"Enter:\n 1 to reposition hare\n 2 to reposition turtle\n 3 to reposition both hare and turtle\n";
            std::cin>>choice;
        
            if(choice==1 || choice==3)                      //if choice is 1 or 3, then hare is repositioned
            {
                //position of hare before reposition by the god
                initial = hare_position;
                
                //position where hare will be repositioned
                std::cout<<"Enter the position to where you want to reposition hare\n";
                std::cin>>hare_position;
                std::cout<<"God moves Hare from position "<<initial<<" to position "<<hare_position<<"\n\n";
                
                //repos is initailized to 1 so that reposition will not happen again
                repos=1;
            }
            if(choice==2 || choice==3)                  //if choice is 2 or 3, then turtle is repositioned
            {
                //position of turtle before reposition by the god
                initial = turtle_position;
                
                //position where turtle will be repositioned   
                std::cout<<"Enter the position to where you want to reposition turtle\n";
                std::cin>>turtle_position;
                std::cout<<"God moves Turtle from position "<<initial<<" to position "<<turtle_position<<"\n\n";
                
                //repos is initailized to 1 so that reposition will not happen again
                repos=1;
            }

            std::cout<<"God's works Ends\n\n";
            
            //mutex unlocks
            hare_mtx.unlock();
            turtle_mtx.unlock();
        
        }
            
        //waiting for next time step
        std::this_thread::sleep_until(next_time_point);
    }

}

int main()
{
    //Race Begins
    std::cout<<"Race Begins\n\n";
    
    //creating threads
    std::thread hare_thread(hare);
    std::thread turtle_thread(turtle);
    std::thread reporter_thread(reporter);
    std::thread god_thread(god);

    //destroying threads
    hare_thread.join();
    turtle_thread.join();
    reporter_thread.join();
    god_thread.join();

    //declaring the winner
    hare_mtx.lock();
    turtle_mtx.lock();
    if(hare_position>=race_length && turtle_position<race_length)
        std::cout<<"Hare Wins\n\n";
    else if(turtle_position>=race_length && hare_position<race_length)
        std::cout<<"Turtle Wins\n\n";
    else if(hare_position>=race_length && turtle_position>=race_length)
        std::cout<<"Race Tied\n\n";
    hare_mtx.unlock();
    turtle_mtx.unlock();
    
    //Race Ends 
    std::cout<<"Race Ends\n";

    //telling the compiler that everything went well
    return 0;
}
