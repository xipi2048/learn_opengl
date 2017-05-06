// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

namespace QuantumTrip {
	enum EndState
	{
		good = 0,
		bad = -1
	};

	class Game
	{
	public:
		Game();
		static EndState run();
	};
}

// TODO: reference additional headers your program requires here
