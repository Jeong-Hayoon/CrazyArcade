#pragma once
#include "CommonInclude.h"

namespace hy
{
	class SoundManager
	{
	public:
		static bool Initialize();
		static LPDIRECTSOUND8 GetDevice() { return mSoundDevice; }

	private:
		static LPDIRECTSOUND8 mSoundDevice;
	};
}