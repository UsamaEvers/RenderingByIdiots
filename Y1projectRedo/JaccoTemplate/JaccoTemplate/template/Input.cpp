#include "Input.h"
namespace Input
{
	namespace Internal
	{
		bool KeyInputs[300];
	}
	bool GetKey(int a_key)
	{
		return Internal::KeyInputs[a_key];
	}
	void SetKey(int a_key, bool a_val)
	{
		Internal::KeyInputs[a_key] = a_val;
	}
	

}