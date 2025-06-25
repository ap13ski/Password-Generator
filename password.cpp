#include "password.h"


namespace NS_PASSWORD
{
//=============================================================================
std::string PasswordGenerator::GetSequence(bool is_lower, bool is_upper, bool is_digits, bool is_special)
{
	int total_lower = 2;
	int total_upper = 2;
	int total_digits = 3;
	int total_special = 1;

	std::string str_lower_total;
	std::string str_upper_total;
	std::string str_digits_total;
	std::string str_special_total;

	int i;
	for (i = 0; i < total_lower; ++i) str_lower_total += str_lower;
	for (i = 0; i < total_upper; ++i) str_upper_total += str_upper;
	for (i = 0; i < total_digits; ++i) str_digits_total += str_digits;
	for (i = 0; i < total_special; ++i) str_special_total += str_special;

	std::string str_sequence;
	if (is_lower == true) str_sequence += str_lower_total;
	if (is_upper == true) str_sequence += str_upper_total;
	if (is_digits == true) str_sequence += str_digits_total;
	if (is_special == true) str_sequence += str_special_total;

	return str_sequence;
}

//=============================================================================
std::string PasswordGenerator::GenerateNewPassword(int number, bool is_lower, bool is_upper, bool is_digits, bool is_special)
{
	std::string str_password;
	if (is_lower == false && is_upper == false && is_digits == false && is_special == false)
	{
		return str_password;
	}

	std::string str_sequence = GetSequence(is_lower, is_upper, is_digits, is_special);
	for (int i = 0; i < number; ++i)
	{
		str_password += str_sequence[rand() % str_sequence.size()];
	}
	
	return str_password;
}

//=============================================================================
std::string PasswordGenerator::GenerateNewPassword()
{
	return GenerateNewPassword(number, is_lower, is_upper, is_digits, is_special);
}	

//=============================================================================
PasswordGenerator::PasswordGenerator(int number, bool is_lower, bool is_upper, bool is_digits, bool is_special):
	number(number), is_lower(is_lower), is_upper(is_upper), is_digits(is_digits), is_special(is_special),
	str_lower("abcdefghijklmnopqrstuvwxyz"),
	str_upper("ABCDEFGHIJKLMNOPQRSTUVWXYZ"),
	str_digits("0123456789"),
	str_special("!@#$%^&*()_+-=[]{}|\\:;\"'<>,.?/")
{
	srand(time(NULL));
}

//=============================================================================
}