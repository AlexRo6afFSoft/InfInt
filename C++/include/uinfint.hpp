#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

size_t max (size_t a, size_t b)
{
	return (a < b)?b:a;
}

size_t min (size_t a, size_t b)
{
	return (a > b)?b:a;
}

struct uinfint
{
	static std::string __uinfint_clean (std::string str)
	{
		std::reverse (std::begin (str), std::end (str));
		while (str.size () >= 1 and str [str.size () - 1] == '0')
			str.erase (str.size () - 1, 1);
		std::reverse (std::begin (str), std::end (str));
		if (str == "") return "0";
		return std::move (str);
	}
	typedef int64_t digit_t;
	static const digit_t base_base = 9;//10 ^ **9**
	static const digit_t base = 1000000000;//**10^9**
	std::vector <digit_t> digits;
	
	uinfint ()
	{
		digits.push_back (0);
	}

	uinfint (int8_t a)
	{
		digits.push_back (a);
	}

	uinfint (int16_t a)
	{
		digits.push_back (a);
	}

	uinfint (int32_t a)
	{
		digits.push_back (a);
	}

	uinfint (int64_t a)
	{
		digits.push_back (a % base);
		digits.push_back (a / base);
	}

	uinfint (std::string a)
	{
		std::size_t br = base_base - (a.size () % base_base);
		a = std::string (br, '0') + a;
		for (std::size_t i = 0 ; i < a.size () ; i += base_base)
		{
			std::string curr = a.substr (i, base_base);
			digits.push_back (atoi (curr.c_str ()));
		}
		reverse (digits.begin (), digits.end ());
	}
	
	template<typename T>
	uinfint (T it1, T it2)
	{
		for (T it = it1 ; it != it2 ; it ++)
			digits.push_back (*it);
	}

	uinfint clear () const
	{
		uinfint a = *this;
		while (a.digits.size () > 1 and a.digits.back () == 0)
			a.digits.pop_back ();
		return std::move (a);
	}

	std::string to_string () const
	{
		uinfint a = clear ();
		std::stringstream ss;
		if (a.digits.size () == 0)
			return "0";
		for (int i = a.digits.size () - 1 ; i >= 0 ; i --)
			ss << std::setw (base_base) << std::setfill ('0') << a.digits [i];
		return __uinfint_clean (ss.str ());
	}

	bool operator == (const uinfint& a) const
	{
		uinfint b = clear (), c = a.clear ();
		std::string B = b.to_string (), C = c.to_string ();
		if (B.size () != C.size ())
			return false;
		else
			return B == C;
	}

	bool operator < (const uinfint& a) const
	{
		uinfint b = clear (), c = a.clear ();
		std::string B = b.to_string (), C = c.to_string ();
		if (B.size () < C.size ())
			return true;
		else if (B.size () > C.size ())
			return false;
		else
			return B < C;
	}

	bool operator > (const uinfint& a) const
	{
		uinfint b = clear (), c = a.clear ();
		std::string B = b.to_string (), C = c.to_string ();
		if (B.size () > C.size ())
			return true;
		else if (B.size () < C.size ())
			return false;
		else
			return B > C;
	}
	
	bool operator <= (const uinfint& a) const
	{
		uinfint b = clear (), c = a.clear ();
		std::string B = b.to_string (), C = c.to_string ();
		if (B.size () < C.size ())
			return true;
		else if (B.size () > C.size ())
			return false;
		else
			return B <= C;
	}

	bool operator >= (const uinfint& a) const
	{
		uinfint b = clear (), c = a.clear ();
		std::string B = b.to_string (), C = c.to_string ();
		if (B.size () > C.size ())
			return true;
		else if (B.size () < C.size ())
			return false;
		else
			return B >= C;
	}
};

std::istream& operator >> (std::istream& out, uinfint& a)
{
	std::string asdf;
	out >> asdf;
	a = uinfint (asdf);
	return out;
}

std::ostream& operator << (std::ostream& out, const uinfint& a)
{
	out << a.to_string ();
	return out;
}

uinfint operator + (uinfint a, uinfint b)
{
	std::size_t MAX = max (a.digits.size (), b.digits.size ());
	a.digits.resize (MAX, 0);
	b.digits.resize (MAX, 0);
	uinfint c;
	c.digits = std::vector <uinfint::digit_t> (MAX + 1, 0);
	uinfint::digit_t pr = 0;
	
	for (std::size_t i = 0 ; i < MAX ; i ++)
	{
		uinfint::digit_t curr = pr + a.digits [i] + b.digits [i];
		pr = curr / uinfint::base;
		c.digits [i] = curr % uinfint::base;
	}
	c.digits [MAX] = pr;
	return std::move (c);
}

uinfint operator - (uinfint a, uinfint b)
{
	std::size_t MAX = max (a.digits.size (), b.digits.size ());
	a.digits.resize (MAX, 0);
	b.digits.resize (MAX, 0);
	uinfint c;
	c.digits = std::vector <uinfint::digit_t> (MAX + 1, 0);
	uinfint::digit_t pr = 0;
	
	for (std::size_t i = 0 ; i < MAX ; i ++)
	{
		uinfint::digit_t curr = -pr + a.digits [i] - b.digits [i];
		pr = (curr < 0);
		c.digits [i] = curr + pr * uinfint::base;
	}
	c.digits [MAX] = pr;
	return std::move (c);
}

uinfint operator << (const uinfint& a, const std::size_t& b)
{
	uinfint c = a;
	reverse (c.digits.begin (), c.digits.end ());
	for (std::size_t i = 0 ; i < b ; i ++)
		c.digits.push_back (0);
	reverse (c.digits.begin (), c.digits.end ());

	return std::move (c);
}

uinfint operator >> (const uinfint& a, const std::size_t& b)
{
	uinfint c = a;
	reverse (c.digits.begin (), c.digits.end ());
	for (std::size_t i = 0 ; i < b ; i ++)
		c.digits.pop_back ();
	reverse (c.digits.begin (), c.digits.end ());

	return std::move (c);
}

uinfint standart_mul (const uinfint& a, const uinfint::digit_t& b, const std::size_t B)
{
	uinfint c;
	c.digits.resize (a.digits.size () + 1 + B, 0);
	for (std::size_t i = 0 ; i < a.digits.size () ; i ++)
	{
		uinfint::digit_t curr = (a.digits [i] * b);
		c.digits [i + 1 + B] += curr / uinfint::base;
		c.digits [i + B] += curr % uinfint::base;
	}
	return std::move (c);
}

namespace __uinfint_slow
{
	uinfint slow_mul (const uinfint& a, const uinfint& b)
	{
		uinfint c (0);
		for (int i = 0 ; i < b.digits.size () ; i ++)
		{
			uinfint curr = standart_mul (a, b.digits [i], i);
			c = c + curr;
		}
		return std::move (c);
	}
}

uinfint operator * (uinfint, uinfint);
uinfint karatsuba (uinfint num1, uinfint num2)
{
////std::cout << num1 << " " << num2 << std::endl;
////std::cout << num1.digits.size () << " " << num2.digits.size () << std::endl;
	if ((num1.digits.size () < 4) or (num2.digits.size () < 4))
		return (__uinfint_slow::slow_mul (num1, num2));

	if (num1.digits.size () != num2.digits.size ())
	{
		while (num1.digits.size () < num2.digits.size ())
			num1.digits.push_back (0);
		while (num1.digits.size () > num2.digits.size ())
			num2.digits.push_back (0);
	}
	std::size_t m = num1.digits.size () / 2;
	uinfint high1 (num1.digits.begin (), num1.digits.begin () + m);
	uinfint low1 (num1.digits.begin () + m, num1.digits.end ()); 
	uinfint high2 (num2.digits.begin (), num2.digits.begin () + m);
	uinfint low2 (num2.digits.begin () + m, num2.digits.end ()); 

	uinfint a = low1 * low2;
	uinfint c = high1 * high2;
	uinfint b = (low1 + high1) * (low2 + high2) - (a + c);
	            //(low1 * high2) + (low2 * high1);
	uinfint ans = (a << (2 * m)) + (b << m) + c;

	return std::move (ans);
}

uinfint operator * (uinfint a, uinfint b)
{
	return std::move (karatsuba(a, b));
}

uinfint operator *= (uinfint& a, uinfint b)
{
	return (a = a * b);
}

namespace __uinfint_slow
{
	uinfint slow_div (const uinfint& a, const uinfint& b)
	{
		uinfint ans = 0;
		uinfint c = 0;
		c.digits.clear ();
		for (int i = a.digits.size () - 1 ; i >= 0 ; i --)
		{
			c = (c << 1) + a.digits [i];
			if (c == b)
			{
				ans = (ans << 1) + 1;
			}

			if (c > b)
			{
				uinfint::digit_t down = 0, up = uinfint::base;
				while (up - down > 1)
				{
					uinfint::digit_t mid = (up + down) / 2;
					uinfint curr = b * mid;
					if (curr < c)
						down = mid;
					else if (curr > c)
						up = mid;
					else
					{
						ans = (ans << 1) + mid;
						c.digits.clear ();
					}
				}
				ans = (ans << 1) + down;
				c = c - b * down;
			}
		}
		return std::move (ans);
	}
}

uinfint operator / (const uinfint& a, const uinfint& b)
{
	return std::move (__uinfint_slow::slow_div (a, b));
}

uinfint operator /= (uinfint& a, const uinfint& b)
{
	return (a = a / b);
}

namespace __uinfint_slow
{
	uinfint slow_mod (const uinfint& a, const uinfint& b)
	{
		uinfint ans = 0;
		uinfint c = 0;
		c.digits.clear ();
		for (int i = a.digits.size () - 1 ; i >= 0 ; i --)
		{
			c = (c << 1) + a.digits [i];
			if (c == b)
			{
				ans = (ans << 1) + 1;
			}

			if (c > b)
			{
				uinfint::digit_t down = 0, up = uinfint::base;
				while (up - down > 1)
				{
					uinfint::digit_t mid = (up + down) / 2;
					uinfint curr = b * mid;
					if (curr < c)
						down = mid;
					else if (curr > c)
						up = mid;
					else
					{
						ans = (ans << 1) + mid;
						c.digits.clear ();
					}
				}
				ans = (ans << 1) + down;
				c = c - b * down;
			}
		}
		return std::move (c);
	}
}

uinfint operator % (const uinfint& a, const uinfint& b)
{
	return std::move (__uinfint_slow::slow_mod (a, b));
}

uinfint operator %= (uinfint& a, const uinfint& b)
{
	return (a = a % b);
}
