
#ifndef SCRIPTPROCESS_H
#define SCRIPTPROCESS_H

#include "../container/LinkedList.h"
#include "CheckedIntValue.h"

#define SCRIPTPROCESS_MIN_ID 1000
#define SCRIPTPROCESS_MAX_ID 1000000000

#ifndef FINAL_RELEASE_BUILD
// defining this gives you checks for use of uninitialized script variables
#define DEBUG_CHECK_FOR_UNINITIALIZED_SCRIPT_VALUE_USE
#endif

#ifdef DEBUG_CHECK_FOR_UNINITIALIZED_SCRIPT_VALUE_USE
typedef CheckedIntValue ScriptLastValueType;
#else
typedef intptr_t ScriptLastValueType;
#endif


// HACK: ...
namespace game
{
  class GameScripting;
  class GameScriptData;
}

namespace util
{
	class Script;

	class ScriptProcess
	{
	private:
		int ip;
		ScriptLastValueType lastValue;
		LinkedList<ScriptLastValueType> *userStack;  // used to store user push- and popValues
		ScriptLastValueType secondaryValue;

		LinkedList<intptr_t> *ipStack;	// used to store ip, ifDepth and thenBranch
		int userStackSize;
		Script *script;
		bool finished;
		int misbehaveCounter;

		intptr_t ifDepth;
		bool thenBranch;
		game::GameScriptData *data;

		int *callParamStack;
		int callParamStackUsed;
		int callParamStackAlloced;

		int *localVarStack;
		int localVarStackUsed;
		int localVarStackAlloced;

		int *scopeStack;
		int scopeStackUsed;
		int scopeStackAlloced;

		int pid;

	public:

		ScriptProcess();
		~ScriptProcess();

		inline bool isFinished() { return finished; }

		inline Script *getScript() { return script; }

		inline void setData(game::GameScriptData *data) { this->data = data; }

		inline game::GameScriptData *getData() { return data; }

		inline int getLastValue() { return lastValue; }

		inline int getSecondaryValue() { return secondaryValue; }

		inline void setLastValue(int lastValue) { this->lastValue = lastValue; }

		inline void setSecondaryValue(int secondaryValue) { this->secondaryValue = secondaryValue; }

		inline int getId() { return pid; }

		bool isUserStackEmpty();

		void error(const char *message);
		void warning(const char *message);
		void debug(const char *message);

		void copyFrom(ScriptProcess *otherScriptProcess);

		bool isCallParamStackEmpty();
		void pushCallParamStack(int value);
		int popCallParamStack();

		bool isLocalVarStackEmpty();
		void pushLocalVarStack(int value);
		int popLocalVarStack();
		int getLocalVarStackSize();
		int getLocalVarStackEntryValue(int index);
		void setLocalVarStackEntryValue(int index, int value);

		void enterLocalScope();
		void leaveLocalScope();

		friend class Script;

		// HACK: ...
		friend class game::GameScripting;
	};

}

#endif
