// This example demonstrates using a mutex to avoid a race condition when
// adding values to a vector.

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex data_mutex;
std::vector<int> data;

void call_from_thread(int tid)
{
  for (unsigned int i=0; i<5; ++i)
    {
      int value = tid; // imagine some computation here

      std::lock_guard<std::mutex> lock(data_mutex);
      data.push_back(value);
    }
}

int main()
{
  const int num_threads = 10;
  std::cout << "Starting " << num_threads << " threads ..." << std::endl;

  std::thread t[num_threads];

  for (int i = 0; i < num_threads; ++i)
    {
      t[i] = std::thread(call_from_thread, i);
    }

  std::cout << "Done launching threads ...\n" << std::endl;

  for (int i = 0; i < num_threads; ++i)
    {
      t[i].join();
    }

  std::cout << "All threads are done." << std::endl;
  for (const auto i : data)
    std::cout << i << " ";
  std::cout << std::endl;
}
