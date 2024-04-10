#include"ImpTimer.h"
#include"CommonFunction.h"

ImpTimer::ImpTimer() {
	start_tick = 0;
	pause_tick = 0;
	is_paused = false;
	is_started = false;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::Start()
{
	is_started = true;
	is_paused = false;
	start_tick = SDL_GetTicks();// lấy tgian đã trôi qua

}

void ImpTimer::stop() {
	is_paused = false;
	is_started = false;
}

void ImpTimer::pause()
{
	if (is_started == true && is_paused == false) {
		is_paused = true;
		pause_tick = SDL_GetTicks() - start_tick;//lấy tgian hiên tại trừ đi tgian pause

	}
}

void ImpTimer::unpause()
{
	if (is_paused == true)
	{
		is_paused = false;
		start_tick = SDL_GetTicks() - pause_tick;
		pause_tick = 0;
	}
}

int ImpTimer::get_ticks() {//lấy tgian đã trôi qua
	if (is_started == true) {//trong th đang chạy
		if (is_paused == true) {
			return pause_tick;
		}
		else {
			return SDL_GetTicks() - start_tick;
		}
	}
	return 0;
}

bool ImpTimer::is_start() {
	return is_started;
}

bool ImpTimer::is_pause()
{
	return is_paused;
}

