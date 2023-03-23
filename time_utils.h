#ifndef TIME_UTILS_H_
#define TIME_UTILS_H_

#include <ctime>

typedef long timestamp_t;

static inline
timestamp_t timestamp(void)
{
	struct timespec timespec;

	clock_gettime(0, &timespec);
	return ((long) timespec.tv_sec) * 1000 +
	       (timespec.tv_nsec / 1000000);
}

#endif /* TIME_UTILS_H_ */
