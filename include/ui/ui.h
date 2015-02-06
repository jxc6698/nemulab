#ifndef __UI_H__
#define __UI_H__

enum { END, STOP, RUNNING, INT };
extern int nemu_state;
enum { NOBREAK, BREAK, BREAK1 };
extern int stop_state;

#endif
