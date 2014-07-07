#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <limits>
#include <ctime>

#ifdef WIN32
#   ifndef NOMINMAX
#      define NOMINMAX
#   endif
#   ifndef WIN32_LEAN_AND_MEAN
#      define WIN32_LEAN_AND_MEAN
#   endif
#   include <windows.h>
#else
#   include <sys/time.h>
#   include <sys/types.h>
#endif

class Stopwatch
{
public:

#ifdef WIN32
   Stopwatch()
   : in_use_(false)
   {
      QueryPerformanceFrequency(&clock_frequency_);
   }

   inline void Start()
   {
      in_use_ = true;
      QueryPerformanceCounter(&start_time_);
   }

   inline double Stop()
   {
      QueryPerformanceCounter(&stop_time_);
      in_use_ = false;
      return (time() * 1000.0);
   }

   inline double time() const
   {
      return (1.0 * (stop_time_.QuadPart - start_time_.QuadPart)) / (1.0 * clock_frequency_.QuadPart);
   }

#else

   Stopwatch()
   : in_use_(false)
   {
      start_time_.tv_sec  = 0;
      start_time_.tv_usec = 0;
      stop_time_.tv_sec   = 0;
      stop_time_.tv_usec  = 0;
   }

   inline void Start()
   {
      in_use_ = true;
      gettimeofday(&start_time_,0);
   }

   inline double Stop()
   {
      gettimeofday(&stop_time_, 0);
      in_use_ = false;
      return (time() * 1000.0);
   }

   inline unsigned long long int usec_time() const
   {
      if (!in_use_)
      {
         if (stop_time_.tv_sec >= start_time_.tv_sec)
         {
            return 1000000 * (stop_time_.tv_sec  - start_time_.tv_sec ) +
               (stop_time_.tv_usec - start_time_.tv_usec);
         }
         else
            return std::numeric_limits<unsigned long long int>::max();
      }
      else
         return std::numeric_limits<unsigned long long int>::max();
   }

   inline double time() const
   {
      return usec_time() * 0.000001;
   }

#endif

   inline bool in_use() const
   {
      return in_use_;
   }

private:

   bool in_use_;

#ifdef WIN32
   LARGE_INTEGER start_time_;
   LARGE_INTEGER stop_time_;
   LARGE_INTEGER clock_frequency_;
#else
   struct timeval start_time_;
   struct timeval stop_time_;
#endif
};

#endif
