#ifndef STARCLOCK_COMMON_OUT_H
#define STARCLOCK_COMMON_OUT_H

//----STANDARD----
#include "string"

using namespace std;

namespace Starclock
{
	namespace Common
	{
		const bool debug = true;

		enum OutputType
		{
			INFO,
			DEBUG,
			ERROR
		};

		class Out
		{
			public: static void put(string message, OutputType type = OutputType::DEBUG);
			public: static bool test(bool test, string label = "NULL Test", bool critical = false, bool silent = false);
		};
	}
}

#endif // STARCLOCK_COMMON_OUT_H
