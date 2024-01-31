/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:35:45 by ckarl             #+#    #+#             */
/*   Updated: 2024/01/31 22:11:53 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void)
{
	std::cout << "ScalarConverter class default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(std::string name)
{
	(void) name;
	std::cout << "ScalarConverter class string constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &c)
{
	std::cout << "ScalarConverter class copy constructor called" << std::endl;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &c)
{
	std::cout << "ScalarConverter class copy assignment operator called" << std::endl;
	return *this;
}

ScalarConverter::~ScalarConverter()
{
	std::cout << "ScalarConverter destructor called" << std::endl;
}

//helper functions
void	displayChar(int c)
{
	if (!isascii(c))
		std::cout << "char: Impossible" << std::endl;
	else if (c < 33 || c > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: " << static_cast<char>(c) << std::endl;
}

void	displayInt(double i)
{
	if (i > INT_MAX || i < INT_MIN)
		std::cout << "int: Impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(i) << std::endl;
}

int	getPrecision(std::string &str)
{
	size_t decPoint = str.find('.');
	if (decPoint != std::string::npos) {
		return str.size() - decPoint - 1;
	}
	return 0;
}

bool	testSpecialCases(std::string str)
{
	std::string	exc[6] = {"+inf", "-inf", "nan", "+inff", "-inff", "nanf"};
	for (int i = 0; i < 6; i++)
	{
		if (exc[i].compare(str) == 0) {
			if (i == 0 || i == 3)
				std::cout << "char: impossible\nint: impossible\nfloat: -inff\ndouble: -inf" << std::endl;
			else if (i == 1 || i == 4)
				std::cout << "char: impossible\nint: impossible\nfloat: +inff\ndouble: +inf" << std::endl;
			else if (i == 2 || i == 5)
				std::cout << "char: impossible\nint: impossible\nfloat: nanff\ndouble: nan" << std::endl;
			return true;
		}
	}
	return false;
}

//exception
const char	*ScalarConverter::InvalidInput::what(void) const throw()
{
	return "Invalid input";
}

const char	*ScalarConverter::OutOfRange::what(void) const throw()
{
	return "This value is out of range for the detected type";
}

//type specific converter functions
void	convertFromChar(char c)
{
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	displayChar((int)c);
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void	convertFromInt(std::string str)
{
	int32_t i;
	std::stringstream ss(str);
	ss >> i;

	if (ss.fail() == true)
		throw ScalarConverter::OutOfRange();
	std::cout << "int: " << i << std::endl;
	displayChar(i);
	std::cout << "float: " << i << ".0f" << std::endl;
	std::cout << "double: " << i << ".0" <<std::endl;
}

void	convertFromFloat(std::string str)
{
	str.pop_back();
	float i;
	std::stringstream ss(str);
	ss >> i;

	if (ss.fail() == true)
		throw ScalarConverter::OutOfRange();
	displayInt(static_cast<double>(i));
	displayChar((int)i);
	std::cout << std::fixed << std::setprecision(getPrecision(str)) << "float: " << i << "f" << std::endl;
	std::cout << std::fixed << std::setprecision(getPrecision(str)) << "double: " << static_cast<double>(i) <<std::endl;
}

void	convertFromDouble(std::string str)
{
	std::stringstream ss(str);
	double i;
	ss >> i;

	if (ss.fail() == true)
		throw ScalarConverter::OutOfRange();
	displayInt(i);
	displayChar((int)i);
	std::cout << std::fixed << std::setprecision(getPrecision(str)) << "float: " << static_cast<float>(i) << "f" << std::endl;
	std::cout << std::fixed << std::setprecision(getPrecision(str)) << "double: " << i <<std::endl;
}

//converter function
void	ScalarConverter::convertType(std::string str)
{
	if (str.length() <= 0)
		throw InvalidInput();
	char	*s = const_cast <char *>(str.c_str());
	int	onlyDigits = 0, sign = 0, point = 0, floatF = 0;

	if (!testSpecialCases(str)) {
		for (int i = 0; i < str.length(); i++)
		{
			if (!isdigit(s[i]) && str.length() > 1) {
				if (s[i] == '-' || s[i] == '+')
				{
					if (sign > 0)
						throw InvalidInput();
					sign++;
				}
				else if (s[i] == '.')
				{
					if (point > 0)
						throw InvalidInput();
					point++;
				}
				else if (s[i] == 'f')
				{
					if (floatF > 0)
						throw InvalidInput();
					floatF++;
				}
				else
					throw InvalidInput();
			}
		}
		if (str.length() == 1 && !isdigit(s[0]))
			convertFromChar(s[0]);
		else if (point && floatF)
			convertFromFloat(str);
		else if (point && !floatF)
			convertFromDouble(str);
		else
			convertFromInt(str);
	}
}

//control overflows (max and min) for int, float and double before conversion (limits header)