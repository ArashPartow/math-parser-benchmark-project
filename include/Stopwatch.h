#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <limits>
#include <ctime>
#include <chrono>

class Stopwatch
{
public:

   Stopwatch()
   : in_use_(false)
   {}

   inline void Start()
   {
      in_use_ = true;
      start_time_ = std::chrono::steady_clock::now();
   }

   inline double Stop()
   {
      stop_time_ = std::chrono::steady_clock::now();
      in_use_ = false;
      return time();
   }

   inline bool in_use() const
   {
      return in_use_;
   }

private:

   inline double time() const
   {
      const auto duration = stop_time_ - start_time_;
      return std::chrono::duration<double,std::nano>(duration).count();
   }

   typedef std::chrono::time_point<std::chrono::steady_clock> time_point_t;

   time_point_t start_time_;
   time_point_t stop_time_;
   bool in_use_;
};

#endif
