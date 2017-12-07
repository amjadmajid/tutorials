#include "virtual_chain.h"

task* addTasks( funcPt task0, funcPt task1, funcPt task2)
{
	static task tasks_chain[3];

	tasks_chain[0].func =  task0;
	tasks_chain[1].func = task1;
	tasks_chain[2].func = task2;

	tasks_chain[0].next = &tasks_chain[1];
	tasks_chain[1].next = &tasks_chain[2];
	tasks_chain[2].next = &tasks_chain[0];

	 if(*(unsigned int *) 0x1904 != 0xAD )
	 {
	 	*(unsigned long *) 0x1900  = (unsigned long) tasks_chain;
	 	*(unsigned int *) 0x1904 = 0xAD;
	 }
	return tasks_chain;
}


void scheduler(task * current ){
	current = (task*) *(unsigned long *) 0x1900 ;
	while(current)
	{
		(current->func)();
		current = current->next;
		*(unsigned long *) 0x1900 = (unsigned long ) current;
	}
}
