#include <stdlib.h>
#include <stdio.h>

#ifndef V_CHAIN_H_
#define V_CHAIN_H_

typedef void (*funcPt)(void);

typedef struct task{
	struct task * next;
	funcPt func;
} task;

// functions prototyping 
task * addTasks( funcPt task0, funcPt task1, funcPt task2);
void scheduler(task *);
#endif