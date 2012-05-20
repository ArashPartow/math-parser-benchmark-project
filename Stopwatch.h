#ifndef STOPWATCH_H
#define STOPWATCH_H

#if defined(__WIN32__) || defined(WIN32)
  #include <Windows.h>
#else
  #include <sys/time.h>
#endif


//-------------------------------------------------------------------------------------------------
class Stopwatch
{
public:

  void Start();
  double Stop();

private:
#if defined(__WIN32__) || defined(WIN32)
  DWORD m_tvs;
  DWORD m_tve;
#else
  struct timeval m_tvs;
  struct timeval m_tve;
#endif
};

#endif
