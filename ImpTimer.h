#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer
{
public: 
	ImpTimer();
	~ImpTimer();

	void Start();//dem tgian
	void stop();// dung lai
	void pause();
	void unpause();

	int get_ticks();

	bool is_start();
	bool is_pause();

private:
	int start_tick;
	int pause_tick;

	bool is_paused;
	bool is_started;
};
#endif