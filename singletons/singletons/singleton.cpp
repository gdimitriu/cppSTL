#include "singleton.h"
#include <cassert>
Singleton* Singleton::pInstance_ = 0;
bool Singleton::destroyed_ = false;
string Singleton::strSingleton="bla bla\n";


void Singleton::KillPhoenixSingleton()
{
	// Make all ashes again
	// - call the destructor by hand.
	// It will set pInstance_ to zero and destroyed_ to true
	pInstance_->~Singleton();
}

void Singleton::OnDeadReference()
{
	// Obtain the shell of the destroyed singleton
	Create();
	// Now pInstance_ points to the "ashes" of the singleton
	// - the raw memory that the singleton was seated in.
	// Create a new singleton at that address
	new(pInstance_) Singleton;
	// Queue this new object's destruction
	#ifdef ATEXIT_FIXED
		atexit(KillPhoenixSingleton);
	#endif
	// Reset destroyed_ because we're back in business
	destroyed_ = false;
}

namespace Private
{
	static void AtExitFn()
	{
		assert(elements > 0 && pTrackerArray != 0);
		// Pick the element at the top of the stack
		LifetimeTracker* pTop = pTrackerArray[elements - 1];
		// Remove that object off the stack
		// Don't check errors-realloc with less memory
		// can't fail
		pTrackerArray = static_cast<TrackerArray>(std::realloc(
		pTrackerArray, sizeof(T) * --elements));
		// Destroy the element
		delete pTop;
	}
}