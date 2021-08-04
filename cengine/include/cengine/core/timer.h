#ifndef _CE_UTIL_TIMER_H_
#define _CE_UTIL_TIMER_H_

typedef double ce_Timer;

double          ce_timeNow(void);

ce_Timer        ce_timerStart(void);
double          ce_timerStop(ce_Timer* timer);
double          ce_timerSplit(ce_Timer* timer);
double          ce_timerRead(const ce_Timer timer);

/* buf should be at least 16 characters long */
void            ce_timeStamp(char* buf);

#endif /* _CE_UTIL_TIMER_H_ */

