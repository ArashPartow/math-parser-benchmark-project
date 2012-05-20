#include "Stopwatch.h"

#include <cstdio>
#include <ctime>


//-------------------------------------------------------------------------------------------------
void Stopwatch::Start()
{
#if defined(__WIN32__) || defined(WIN32)
  m_tvs = GetTickCount();
#else
  if (gettimeofday(&m_tvs,0)) 
    fprintf(stderr,"cant get time!\n");
#endif
}

//-------------------------------------------------------------------------------------------------
double Stopwatch::Stop()
{
#if defined(__WIN32__) || defined(WIN32)
  m_tve = GetTickCount();

  return m_tve - m_tvs;
#else
  if (gettimeofday(&m_tve, 0)) 
    fprintf(stderr,"cant get time!\n");

  return m_tve.tv_sec - m_tvs.tv_sec+(double)(m_tve.tv_usec - m_tvs.tv_usec)/1000000.0;
#endif
}
