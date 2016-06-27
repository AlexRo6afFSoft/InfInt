struct infint
{
	static std::string __infint_clean (std::string str, bool p)
	{
		std::reverse (std::begin (str), std::end (str));
		while (str.size () >= 1 and str [str.size () - 1] == '0')
			str.erase (str.size () - 1, 1);
		std::reverse (std::begin (str), std::end (str));
		if (str == "") return "0";
		if (!p) str = "-" + str;
		return std::move (str);
	}
	typedef uint64_t digit_t;
	static const digit_t base_base = 8;//10 ^ **9**
	static const digit_t base = 1000000000;//**10^9**
	std::vector <digit_t> digits;
	bool positive;

	infint (uintinf a)
	{
		digits = a.digits;
		positive = true;
	}

	uinfint abs () const
	{
		uinfint ans;
		ans.digits = digits;
		return std::move (ans);
	}

	infint clear () const
	{
		infint a = *this;
		while (a.digits.size () > 1 and a.digits.back () == 0)
			a.digits.pop_back ();
		return std::move (a);
	}

	std::string to_string () const
	{
		infint a = clear ();
		std::stringstream ss;
		if (a.digits.size () == 0)
			return "0";
		for (int i = a.digits.size () - 1 ; i >= 0 ; i --)
			ss << std::setw (base_base) << std::setfill ('0') << a.digits [i];
		return __infint_clean (ss.str (), positive);
	}

	bool operator < (const infint& a) const
	{
		if (positive == 1 and a.positive == 0)
			return false;
		if (positive == 0 and a.positive == 1)
			return true;
		if (positive == 0 and a.positive == 0)
			return a.abs () < this->abs ();
		infint b = clear (), c = a.clear ();
		std::string B = b.to_string (), C = c.to_string ();
		if (B.size () < C.size ())
			return true;
		else if (B.size () > C.size ())
			return false;
		else
			return B < C;
	}

	bool operator > (const infint& a) const
	{
		if (positive == 1 and a.positive == 0)
			return !false;
		if (positive == 0 and a.positive == 1)
			return !true;
		if (positive == 0 and a.positive == 0)
			return a.abs () > this->abs ();
		infint b = clear (), c = a.clear ();
		std::string B = b.to_string (), C = c.to_string ();
		if (B.size () > C.size ())
			return true;
		else if (B.size () < C.size ())
			return false;
		else
			return B > C;
	}

	static infint change_positive (infint a, bool p)
	{
		a.positive = p;
		return std::move (a);
	}

	static infint change_positive (uinfint b, bool p)
	{
		infint a (b);
		a.positive = p;
		return std::move (a);
	}
};

infint operator + (const infint& a, const infint& b)
{
	uinfint a1 = a.abs ();
	uinfint b1 = b.abs ();
	if (a.positive == b.positive)
		return std::move (infint::change_positive (a1 + b1, a.positive));
	else
	{
	}
}
