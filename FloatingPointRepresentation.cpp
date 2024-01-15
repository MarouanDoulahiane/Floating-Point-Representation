#include <iostream>

using namespace std;

bool    isValidNumber(string nb)
{
	size_t  i = 0;

	if (nb[i] == '+' || nb[i] == '-') 
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
	cerr << "Error: Good Input" << endl;
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
	for (int i = 0; i < nb.size(); i++)
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
		handleFloat()

}