#ifndef PASSWORD_H
#define PASSWORD_H
//#############################################################################


#include <ctime>
#include <cmath>
#include <string>

namespace NS_PASSWORD
{
//=============================================================================
	class PasswordGenerator
	{
	private:
		
		int number;
		bool is_lower;
		bool is_upper;
		bool is_digits;
		bool is_special;

		std::string str_lower;
		std::string str_upper;
		std::string str_digits;
		std::string str_special;

		std::string GetSequence(bool is_lower, bool is_upper, bool is_digits, bool is_special);
		
	public:

		std::string GenerateNewPassword(int number, bool is_lower, bool is_upper, bool is_digits, bool is_special);
		std::string GenerateNewPassword();
		PasswordGenerator(int number, bool is_lower, bool is_upper, bool is_digits, bool is_special);
	};

//=============================================================================
}


//#############################################################################
#endif