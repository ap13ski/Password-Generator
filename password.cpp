#include "password.h"

namespace NS_PASSWORD
{
//=============================================================================
std::string PasswordGenerator::GetSequence(bool isLower, bool isUpper, bool isDigits, bool isSpecial)
{
	int total_lower = 2;
	int total_upper = 2;
	int total_digits = 3;
	int total_special = 1;
	
	std::string strLowerTotal;
	std::string strUpperTotal;
	std::string strDigitsTotal;
	std::string strSpecialTotal;

	int i;
	for (i = 0; i < total_lower; ++i) strLowerTotal += strLower;
	for (i = 0; i < total_upper; ++i) strUpperTotal += strUpper;
	for (i = 0; i < total_digits; ++i) strDigitsTotal += strDigits;
	for (i = 0; i < total_special; ++i) strSpecialTotal += strSpecial;

	std::string strSequence;
	if (isLower == true) strSequence += strLowerTotal;
	if (isUpper == true) strSequence += strUpperTotal;
	if (isDigits == true) strSequence += strDigitsTotal;
	if (isSpecial == true) strSequence += strSpecialTotal;

	return strSequence;
}

//=============================================================================
std::string PasswordGenerator::GenerateNewPassword(int number, bool isLower, bool isUpper, bool isDigits, bool isSpecial)
{	
	std::string strPassword;
	if (isLower == false && isUpper == false && isDigits == false && isSpecial == false)
	{
		return strPassword;
	}

	std::string strSequence = GetSequence(isLower, isUpper, isDigits, isSpecial);			
	for (int i = 0; i < number; ++i)
	{
		strPassword += strSequence[rand() % strSequence.size()];
	}	
	
	return strPassword;		
}	

//=============================================================================
std::string PasswordGenerator::GenerateNewPassword()
{	
	return GenerateNewPassword(number, isLower, isUpper, isDigits, isSpecial);		
}	

//=============================================================================
PasswordGenerator::PasswordGenerator(int number, bool isLower, bool isUpper, bool isDigits, bool isSpecial):
	number(number),	isLower(isLower), isUpper(isUpper),	isDigits(isDigits),	isSpecial(isSpecial),
	strLower("abcdefghijklmnopqrstuvwxyz"),
    strUpper("ABCDEFGHIJKLMNOPQRSTUVWXYZ"),
    strDigits("0123456789"),
    strSpecial("!@#$%^&*()_+-=[]{}|\\:;\"'<>,.?/")
{
	srand(time(NULL));
}

//=============================================================================

}