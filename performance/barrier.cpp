//including libraries
#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <mutex>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <thread>
#include <ctime>
#include <condition_variable>

//initailising mutex variables
std::mutex mtx;

std::condition_variable cv;

int limit,nthread,sum;
int flag=0;

void compute_sum(int my_rank, int n)
{
	int my_first_i,my_last_i,my_sum,i;
	my_first_i = n * my_rank;
	my_last_i = my_first_i + n;
	for (i = my_first_i+1; i <= my_last_i; i++)
	{
		my_sum +=i;
	}
	mtx.lock();
	flag++;
	mtx.unlock();
	while(flag<nthread);
	sum += my_sum;
}

int main()
{
	int i,n;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::cout<<"Enter limit of sum\n";
	std::cin>>limit;
	std::cout<<"Enter no. threads required\n";
	std::cin>>nthread;
	n =  limit/nthread;
	std::thread sum_thread[nthread];
	start = std::chrono::steady_clock::now();
	for(i=0; i<nthread; i++)
	{
		sum_thread[i] = std::thread(compute_sum,i,n);
	}
	for(i=0; i<nthread; i++)
	{
		sum_thread[i].join();
	}
	std::cout<<"Sum = "<<sum<<"\n";
	end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout<<"Time Taken = "<<elapsed_seconds.count()<<"\n";
	return 0;
}
