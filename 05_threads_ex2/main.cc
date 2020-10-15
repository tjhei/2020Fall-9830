// template for multithreaded vector addition

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <thread>

/**
 * A simple class representing a vector in the vector space R^n.
 */
class Vector
{
public:
  /**
   * Constructor, initialize to given size with random entries
   */
  explicit Vector(int size = 0)
  {
    values.resize(size);
    for (int i = 0; i < size; ++i)
      values[i] = rand();
  }

  /**
   * Constructor, copy @p other.
   */
  Vector(const Vector &other)
  {
    std::cout << "You are making a copy "
              << &other << " -> " << this
              << std::endl;
    values = other.values;
  }

  /**
   * Print the entries of the vector to the screen.
   */
  void print()
  {
    for (unsigned int i=0; i<values.size(); ++i)
      std::cout << values[i] << "\t";
    std::cout << std::endl;
  }

  /**
   * Return the l2/euclidian norm
   */
  double norm()
  {
    double tmp = 0.0;
    for (unsigned int i=0; i<values.size(); ++i)
      tmp += values[i]*values[i];
    return sqrtf(tmp);

  }

  /**
   * We store the elements of our vector here.
   */
  std::vector<double> values;
};


/**
 * Do part of a vector addition
 */
void add(Vector &out,
         const Vector &in1,
         const Vector &in2,
         unsigned int start,
         unsigned int end)
{
  for (unsigned int i=start; i<end; ++i)
    out.values[i] = in1.values[i] + in2.values[i];
}

int main()
{
  unsigned int size = 10000000; // = 80 MB
  const int n_runs = 100;
  Vector x(size);
  Vector y(size);

  std::cout << "Running " << n_runs << " additions... " << std::endl;

  bool run_serial = true;


  // serial version
  if (run_serial)
    {
      // repeatedly compute x = x+y
      for (int runs=0; runs<n_runs; ++runs)
        add(x, x, y, 0, size);

      std::cout << "Norm: " << x.norm() << std::endl;
    }

  // parallel version
  if (!run_serial)
    {
      const int num_threads = std::thread::hardware_concurrency();
      std::thread t[256]; // Likely big enough and fixed in size
      for (int runs=0; runs<n_runs; ++runs)
        {
          for (int i = 0; i < num_threads; ++i)
            {
              //unsigned int start = // TODO
              //unsigned int end =  // TODO
              //      t[i] = std::thread(add, ??);
            }

          for (int i = 0; i < num_threads; ++i)
            t[i].join();
        }
      std::cout << "Norm: " << x.norm() << std::endl;
    }

}
