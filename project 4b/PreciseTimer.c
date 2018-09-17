/*
 * NAME: Jonathan Chang
 * EMAIL: j.a.chang820@gmail.com
 * ID: 104853981
 */ 

#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "PreciseTimer.h"


static void get_monotonic_time(struct timespec *tp) {
  if (clock_gettime(CLOCK_MONOTONIC, tp) == -1) {
    switch(errno) {
    case EFAULT:
      fprintf(stderr, 
	      "Clock points outside the accessible address space.\r\n");
      break;
    case EINVAL:
      fprintf(stderr, 
	      "Monotonic clock is not supported on this system.\r\n");
      break;
    case EPERM:
      fprintf(stderr,
	      "No permission to set the clock.\r\n");
      break;
    default:
      fprintf(stderr,
	      "Miscellaneous clock error.\r\n%s\r\n",
	      strerror(errno));
    }
    exit(2);
  }
}


static long long get_diff(struct timespec *start, struct timespec *end) {
  long long billion = 1E9;
  long long sec_diff = (long long) (end->tv_sec - start->tv_sec);
  long long nsec_diff = (long long) (end->tv_nsec - start->tv_nsec);
  return (sec_diff * billion) + nsec_diff;
}


void PreciseTimer_start(struct PreciseTimer *timer) {
  struct timespec *start = &(timer->start_time);
  get_monotonic_time(start);
}


void PreciseTimer_end(struct PreciseTimer *timer) {
  struct timespec *start = &(timer->start_time);
  struct timespec *end = &(timer->end_time);
  get_monotonic_time(end);
  timer->diff = get_diff(start, end);
}


void PreciseTimer_report(struct PreciseTimer *timer) {
  struct timespec *start = &(timer->start_time);
  struct timespec *end = &(timer->end_time);
  fprintf(stderr, "Start sec: %ld nsec: %ld\r\n", start->tv_sec, start->tv_nsec);
  fprintf(stderr, "End sec: %ld nsec: %ld\r\n", end->tv_sec, end->tv_nsec);
  fprintf(stderr, "Diff nsec: %lld\r\n", timer->diff);
}


float PreciseTimer_elapsedFloat(struct PreciseTimer *timer) {
  struct timespec now;
  get_monotonic_time(&now);
  long million = 1E6;
  int start_sec = timer->start_time.tv_sec;
  int start_msec = timer->start_time.tv_nsec / million;
  int now_sec = now.tv_sec;
  int now_msec = now.tv_nsec / million;
  int whole_seconds = now_sec - start_sec;
  float frac_seconds = ((float)(now_msec - start_msec)) / 1000;
  return (float)whole_seconds + frac_seconds;
}


void PreciseTimer_now(struct timespec *tp) {
  struct timespec now;
  get_monotonic_time(&now);
}
