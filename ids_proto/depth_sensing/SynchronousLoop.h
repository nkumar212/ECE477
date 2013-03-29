#ifndef SYNCHRONOUS_LOOP_H
#define SYNCHRONOUS_LOOP_H

class SynchronousLoop
{
	protected: //Static Properties
		static class SynchronousLoop* Singleton;
	protected: //Static Members
		static SynchronousLoop* getSingleton();
	protected: //Instance Properties
		long loop_period;
	public: void main();
	public: //Member Functions
		void setPeriod(long ms);
};

#endif
