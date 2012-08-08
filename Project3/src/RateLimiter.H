#ifndef _RATELIMITER_H_
#define _RATELIMITER_H_

/*
 * Team: Exception
 * Date: Spring 2012
 * Description: RateLimiter class
 * 
 * what does this do?
 */

#include <string>
#include <ctime>
#include <boost/thread/mutex.hpp>

void test_ratelimiter();

class RateLimiter
{
private:
  timespec free_at;
  timespec cooldown;
  boost::mutex time_mutex;

public:
  RateLimiter() {}
  RateLimiter(int per_second_limit);
  void operator()(); // This function can only be called per_second_limit times per second.
};

#endif /* _RATELIMITER_H_ */
