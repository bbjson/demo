// sdlthread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "SDL.h"

SDL_cond* cond = SDL_CreateCond();
SDL_mutex* mutex = SDL_CreateMutex();

int index = 0;
static int MyThread(void *data) {
	while (1) {
		SDL_LockMutex(mutex);
		index++;
		std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << index << "\n";
		if (index % 2 == 0) {
			SDL_CondSignal(cond);
			SDL_UnlockMutex(mutex);

			SDL_CondWait(cond, mutex);
		}
	}

	return 0;
}

static int YouThread(void* data) {
	while (1) {
		SDL_LockMutex(mutex);
		index++;
		std::cout << "***********************************************" << index << "\n";
		if (index % 2 != 0) {
			SDL_CondSignal(cond);
			SDL_UnlockMutex(mutex);
			SDL_CondWait(cond, mutex);
		}
	}
	return 0;
}

#undef main;
int main()
{

	SDL_Thread *threaMy = SDL_CreateThread(MyThread,"MyThread", NULL);
	SDL_Thread *threadYou = SDL_CreateThread(YouThread, "YouThread", NULL);

	SDL_WaitThread(threaMy, 0);
	SDL_WaitThread(threadYou, 0);


	return 0;

}




