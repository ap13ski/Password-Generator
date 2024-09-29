#pragma once

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
		bool isLower;
		bool isUpper;
		bool isDigits;
		bool isSpecial;

		std::string strLower;
		std::string strUpper;
		std::string strDigits;
		std::string strSpecial;
		
		std::string GetSequence(bool isLower, bool isUpper, bool isDigits, bool isSpecial);	
		
	public:

		std::string GenerateNewPassword(int number, bool isLower, bool isUpper, bool isDigits, bool isSpecial);	
		std::string GenerateNewPassword();	
		PasswordGenerator(int number, bool isLower, bool isUpper, bool isDigits, bool isSpecial);
	};

//=============================================================================
}