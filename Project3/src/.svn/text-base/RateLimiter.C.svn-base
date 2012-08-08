#include "RateLimiter.H"
#include <ctime>
#include <iostream>
#include <assert.h>

using std::cerr;
using std::endl;

const long NS_IN_S(1000000000);
const timespec ONE_S = {1, 0};

/** Difference between a and b in terms of magnitude and sign.
 * magnitude = abs(a - b), sign = a == b ? 0 : a-b/abs(a-b)
 */
void diff(const timespec& a, const timespec& b, timespec &magnitude, int &sign)
{
  // This is ugly because timespec can have unsigned components and needs to
  // carry across fields.
  if (a.tv_sec == b.tv_sec) {
    magnitude.tv_sec = 0;
    if (a.tv_nsec == b.tv_nsec) {
      magnitude.tv_nsec = 0;
      sign = 0;
    } else if (a.tv_nsec > b.tv_nsec) {
      magnitude.tv_nsec = a.tv_nsec - b.tv_nsec;
      sign = -1;
    } else {
      magnitude.tv_nsec = b.tv_nsec - a.tv_nsec;
      sign = 1;
    }
  } else if (a.tv_sec > b.tv_sec) {
    sign = -1;
    magnitude.tv_sec = a.tv_sec - b.tv_sec;
    if (a.tv_nsec >= b.tv_nsec) {
      magnitude.tv_nsec = a.tv_nsec - b.tv_nsec;
    } else {
      magnitude.tv_nsec = NS_IN_S - (b.tv_nsec - a.tv_nsec);
      magnitude.tv_sec--;
    }
  } else {
    sign = 1;
    magnitude.tv_sec = b.tv_sec - a.tv_sec;
    if (b.tv_nsec >= a.tv_nsec) {
      magnitude.tv_nsec = b.tv_nsec - a.tv_nsec;
    } else {
      magnitude.tv_nsec = NS_IN_S - (a.tv_nsec - b.tv_nsec);
      magnitude.tv_sec--;
    }
  }
}

/** timespec add. a+b
 */
timespec add(const timespec& a, const timespec& b)
{
  timespec result;
  result.tv_nsec = a.tv_nsec + b.tv_nsec;
  result.tv_sec = a.tv_sec + b.tv_sec + result.tv_nsec / NS_IN_S;
  result.tv_nsec %= NS_IN_S;
  return result;
}

/** timespec less than or equal to. a<=b
 */
bool leq(const timespec& a, const timespec& b)
{
  return a.tv_sec < b.tv_sec || (a.tv_sec == b.tv_sec && a.tv_nsec <= b.tv_nsec);
}

void test_diff(timespec &a, timespec &b, time_t sec, long nsec, int sign)
{
  int s;
  timespec r;
  diff(a, b, r, s);
  //cerr << "Expected r:" << sign << " * " << sec << ":" << nsec << endl;
  //cerr << "Actual   r:" << s << " * " << r.tv_sec << ":" << r.tv_nsec << endl;
  assert(r.tv_sec == sec && r.tv_nsec == nsec && s == sign);
}

void test_ratelimiter()
{
  timespec a,b,c,d,e,r;
  a.tv_sec = 1;
  a.tv_nsec = 100;
  b.tv_sec = 1;
  b.tv_nsec = 50;
  c.tv_sec = 2;
  c.tv_nsec = 50;
  d.tv_sec = 2;
  d.tv_nsec = 100;
  e.tv_sec = 1;
  e.tv_nsec = NS_IN_S - 1;

  r = add(a, c);
  //cerr << "r:" << r.tv_sec << ":" << r.tv_nsec << endl;
  assert(r.tv_sec == 3 && r.tv_nsec == 150);

  r = add(a, e);
  //cerr << "r:" << r.tv_sec << ":" << r.tv_nsec << endl;
  assert(r.tv_sec == 3 && r.tv_nsec == 99);

  test_diff(a, b, 0, 50, -1);
  test_diff(b, a, 0, 50, 1);
  test_diff(a, c, 0, NS_IN_S - 50, 1);
  test_diff(c, a, 0, NS_IN_S - 50, -1);
  test_diff(a, d, 1, 0, 1);
  test_diff(d, a, 1, 0, -1);

  RateLimiter limit(2);
  
  const char* count[10] = {"1 ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10"};
  timespec start, end, time;
  int sign;
  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < 10; i++) {
    limit();
    cerr << count[i];
    // usleep(NS_IN_S / 1000 / 2);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  diff(start, end, time, sign);
  //cerr << time.tv_sec << ":" << time.tv_nsec << endl;

  // At two per second (assuming one second of "banked" requests), ten requests
  // should take just over four seconds.
  assert(time.tv_sec >= 4 && time.tv_sec <= 5);
  cerr << " Passed!" << endl;
}

RateLimiter::RateLimiter(int per_second_limit)
{
  cooldown.tv_sec = 0;
  cooldown.tv_nsec = NS_IN_S / per_second_limit;
  free_at.tv_sec = 0;
  free_at.tv_nsec = 0;
}

void RateLimiter::operator()()
{
  timespec time_left; // How long until we can execute
  bool sleep; // Do we have to sleep?
  {
    // cerr << "Locking" << endl;
    // Lock the time calculation part
    boost::mutex::scoped_lock lock(time_mutex);

    timespec current_time;
    // cerr << "Getting time" << endl;
    // Get the time from the clock that measures actual time, not process time
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    //    cerr << "Time:" << current_time.tv_sec << ":" << current_time.tv_nsec << endl;

    int sign;
    // time_left is the difference between now and when we can execute. If we
    // could have executed in the past or can right now, sign will be <= 0,
    diff(current_time, free_at, time_left, sign);
    sleep = sign > 0;

    // cerr << "Time_Left:" << sign << " * " << time_left.tv_sec << ":" << time_left.tv_nsec << endl;
    
    // We shouldn't allow "banking" request during times of inactivity,
    // so adjust free_at if it has been more than a second since the last call.
    if(!sleep && leq(ONE_S, time_left)) {
      diff(ONE_S, add(cooldown, current_time), free_at, sign);
    }

    // Add the cooldown
    free_at = add(cooldown, free_at);

    // cerr << "Unlocking" << endl;
    // Unlocked by scope
  }

  // Sleep outside of the lock so other threads can queue up.
  if (sleep) {
    // cerr << "Sleepies" << endl;
    nanosleep(&time_left, 0);
    // cerr << "Done sleepies" << endl;
  }
}
