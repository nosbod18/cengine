#ifndef CORE_TIMER_H
#define CORE_TIMER_H

typedef double timer_t;

double          time_now(void);

timer_t         timer_start(void);
double          timer_stop(timer_t* timer);
double          timer_split(timer_t* timer);
double          timer_read(const timer_t timer);

/* buf should be at least 16 characters long */
void            time_stamp(char* buf);

#endif /* CORE_TIMER_H */

