#include <iostream>

using namespace std;

bool    isValidNumber(string nb)
{
	size_t  i = 0;

	if ((nb[i] == '+' || nb[i] == '-' )&& nb.size() > 1)
		i++;
	while (isdigit(nb[i]))
		i++;
	if (nb[i] == '.')
		i++;
	while (isdigit(nb[i]))
		i++;
	if (i != nb.size())
		return (false);
	return (true);
}

string  getInputNumber(string msg)
{
	string  input;

	cout << msg;
	tryagain:
	if (getline(cin, input).eof())
	{
		cerr << "\nError: getline() failed!" << endl;
		exit(1);
	}
	if (input.empty())
	{
		cout << "Try To " << msg;
		goto tryagain;
	}
	if (!isValidNumber(input))
	{
		cerr << "Error: Bad Input" << endl;
		exit(1);
	}
	return input;
}

ssize_t getFloatingPointPos(string nb)
{
	size_t pos = nb.find('.');
	if (pos == string::npos)
		return (-1);
	return (pos);
}

bool    containZeros(string nb)
{
	for (size_t i = 0; i < nb.size(); i++)
		if (nb[i] != '0')
			return false;

	return true;
}

void    handleInt(string nb)
{
	int res;
	string bits;

	try {
		res = stoi(nb);
	}
	catch (...) {
		cerr << "stoi() failed!" << std::endl;
		exit(1);
	}

	int temp = res;
	if (!temp)
		bits += '0';
	while (temp)
	{
		bits += temp % 2? '1': '0';
		temp /= 2;
	}
	reverse(bits.begin(), bits.end());
	if (res < 0)
		bits = "-" + bits;
	cout << "This an int number it's represent in memory like this:" << endl;
	cout << res << " -> [" << bits << "]" << endl; 
}

string	getBits(string nb)
{
	int res;
	string bits;

	try {
		res = stoi(nb);
	}
	catch (...) {
		cerr << "stoi() failed!" << std::endl;
		exit(1);
	}
	int temp = res;
	while (temp)
	{
		bits += temp % 2? '1': '0';
		temp /= 2;
	}
	reverse(bits.begin(), bits.end());
	return bits;
}

string	getBits(int res)
{
	string bits;

	int temp = res;
	while (temp)
	{
		bits += temp % 2? '1': '0';
		temp /= 2;
	}
	reverse(bits.begin(), bits.end());
	return bits;
}

int	stringToInt(string nb)
{
	int res;

	try {
		res = stoi(nb);
	}
	catch (...) {
		cerr << "stoi() failed!" << std::endl;
		exit(1);
	}
	return (res);
}

void	handleFloat(string integerPart, string floatPart)
{
	string	results;

	string	intBits = getBits(integerPart);
	int		exponentBias = intBits.size() - 1 + 127;
	string	exponentBits = getBits(exponentBias);
	results += integerPart[0] == '-'? "1": "0";

	for (int i = 0; i < 8 - exponentBits.size(); i++)
		results += "0";
	results += exponentBits;
	int mantissaPos = 1;
	if (integerPart[0] == '+' || integerPart[0] == '-')
		mantissaPos++;
	cerr << "Test :" << intBits.substr(mantissaPos) << endl;
	results += intBits.substr(mantissaPos);
	int i = results.size();
	int	floatInt = stringToInt(floatPart);
	int	divider = 10 * floatPart.size();
	for (; i < 32; i++)
	{
		floatInt *= 2;
		results += floatInt / divider? "1": "0";

		floatInt = floatInt % divider;
	}
	cout << "This a float number it's represent in memory like this:" << endl;
	cout << "myFl(): " << " -> [" << results << "]" << endl; 
}

int main(void)
{
	string  input = getInputNumber("Enter The Number: ");
	ssize_t floatPos = getFloatingPointPos(input);

	string  integerPart;
	string  fractionalPart;

	if (floatPos != -1)
	{
		integerPart = input.substr(0, floatPos);
		fractionalPart = input.substr(floatPos + 1);
	}
	else
		integerPart = input;
	if (integerPart.empty())
		integerPart += '0';
	if (fractionalPart.empty())
		fractionalPart += '0';
	// cout << "integer Part = |" << integerPart << "|" << endl;
	// cout << "fractional Part = |" << fractionalPart << "|" << endl;
	if (containZeros(fractionalPart))
		handleInt(integerPart);
	else
	{
		handleFloat(integerPart, fractionalPart);

		float floatValue = stof(input);
		unsigned int bits = *reinterpret_cast<unsigned int*>(&floatValue);
		bitset<32> bitRepresentation(bits);
		cout << "stof():  -> [" << bitRepresentation << "]" << endl;

		
	}
	return (0);
}