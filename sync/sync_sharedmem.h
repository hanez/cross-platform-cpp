// Cross-platform, named (cross-process), shared memory with two auto events.
// (C) 2016 CubicleSoft.  All Rights Reserved.

#ifndef CUBICLESOFT_SYNC_SHAREDMEM
#define CUBICLESOFT_SYNC_SHAREDMEM

#include "sync_util.h"

namespace CubicleSoft
{
	namespace Sync
	{
		class SharedMem
		{
		public:
			SharedMem();
			~SharedMem();

			// For platform consistency, Name + Size is a unique key.  size_t is, of course, limited to 4GB RAM on most platforms.
			// On some platforms (e.g. Windows), the objects may vanish if all handles are freed.
			bool Create(const char *Name, size_t Size);

			inline bool First()  { return MxFirst; }

			// When First() is true, call Ready() after initializing the memory.
			// The shared memory is locked until this function is called.
			void Ready();

			inline size_t GetSize()  { return MxSize; }
			inline char *RawData()  { return MxMem; }

		private:
			// Deny copy constructor and assignment operator.  Use a (smart) pointer instead.
			SharedMem(const SharedMem &);
			SharedMem &operator=(const SharedMem &);

			bool MxFirst;
			size_t MxSize;
			char *MxMem;

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
			HANDLE MxWinMutex;
#else
			char *MxMemInternal;
#endif
		};
	}
}

#endif