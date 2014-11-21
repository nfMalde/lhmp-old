#include "CTimerPool.h"
#include "../shared/limits.h"
CTimerPool::CTimerPool()
{
	for (int i = 0; i < MAX_TIMERS; i++)
	{
		pool[i] = NULL;
	}
}
CTimerPool::~CTimerPool()
{
	delete pool[MAX_TIMERS];
}

void CTimerPool::Tick()
{
	for (int i = 0; i < MAX_TIMERS; i++)
	{
		if (pool[i] != NULL)
		{
			if (pool[i]->Tick() == false)
			{
				delete pool[i];
				pool[i] = NULL;
			}
		}
	}
}

int	CTimerPool::New(SQVM* script, char* function, int interval, int repeat)
{
	for (int i = 0; i < MAX_TIMERS; i++)
	{
		if (pool[i] == NULL)
		{
			pool[i] = new CTimer(script,function,interval,repeat);
			return i;
		}
	}
	return -1;
}
void	CTimerPool::Delete(int ID)
{
	delete pool[ID];
}