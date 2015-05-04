//----STANDARD----
#include "iostream"
#include "string"

//----LOCAL----
#include "out.h"

using namespace std;

namespace Starclock
{
	namespace Common
	{
		void Out::put(string message, OutputType type)
		{
			if ((debug && type == OutputType::DEBUG) || type != OutputType::DEBUG)
			{
				string output_tag;

				switch(type)
				{
					case (OutputType::INFO) :
						output_tag = "OUTPUT";
						break;
					case (OutputType::DEBUG) :
						output_tag = "DEBUG";
						break;
					case (OutputType::ERROR) :
						output_tag = "ERROR";
						break;
				}

				cout << "[" << output_tag << "]: " << message << endl;
			}
		}

		bool Out::test(bool test, string label, bool critical, bool silent)
		{
			if (test)
			{
				if (!silent)
					Out::put(label + ": success", OutputType::DEBUG);
			}
			else
			{
				Out::put(label + ": failure", OutputType::ERROR);

				if (critical)
				{
					Out::put("Critical error, program closing.", OutputType::ERROR);
					exit(EXIT_FAILURE);
				}
			}

			return test;
		}
	}
}
