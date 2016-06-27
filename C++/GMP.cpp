#include <iostream>
#include <gmpxx.h>
int main ()
{
	mpz_class a = 0;
	mpz_class b = 0;
	std::cin >> a >> b;
	std::cout << a * b << "\n";
	return 0;
}
