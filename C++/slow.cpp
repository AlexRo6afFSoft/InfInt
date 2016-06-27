#include <iostream>
#include <big_integer.hpp>

using namespace std;

int main ()
{
	big_int a (10);
	big_int b (5);
	cin >> a >> b;
	if (a.positive == b.positive)
	{
		cout << (big_int::slow_mul (a, b));
	}
	else
	{
		cout << (big_int::change_positive (big_int::slow_mul (a, b), 0));
	}
}
