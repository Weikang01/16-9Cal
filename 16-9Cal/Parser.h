#pragma once
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

namespace Parser
{
	/* type defs */

	// RPN list
	typedef std::vector<std::string> RPN;

	// callback to unary function (1 argument)
	typedef double(*UnaryFuncEval)(double x);

	// callback to binary function (2 arguments)
	typedef double(*BinaryFuncEval)(double x, double y);

	// types
	enum class TokenTypes
	{
		OPERATOR,
		CONSTANT,
		FUNCTION,
		LPAREN,
		RPAREN,
		ELSE
	};

	/* Utility function callback */
	// convert a variable/constant into const char*
#define toString(x) #x

	// determine if vector contains values
	template<typename T>
	bool contains(std::vector<T> v, T x);

	// obtain key list
	template<typename T>
	std::vector<std::string> keys(std::map<std::string, T> m);

	// obtain combined key list
	template<typename T>
	std::vector<std::string> keys(std::map<std::string, T> m1, std::map<std::string, T> m2);

	// determine if character is number
	bool isNumber(char c);

	// determine if entire string is number
	bool isNumber(const char* c, bool acceptDecimal = true);

	// determine if string only contains numerical characters
	bool containsNumber(const char* str);

	// get numerical value of string
	int getNumericalVal(const char* c);

	// determine if string matches a function
	bool isFunction(std::string str);

	// get function precedence
	short getPrecedence(std::string str);

	// find element from list in the equation starting at index i
	std::string findElement(int i, const char* eqn, std::vector<std::string> list);

	std::string findElement(int i, const char* eqn, std::vector<char> list);

	/* Function class definition */
	class Func
	{
	public:
		UnaryFuncEval u_eval;  // unary function evaluation callback
		BinaryFuncEval b_eval;  // binary function evaluation callback

		TokenTypes type;  // type of function (ie function or operator)
		short prec;  // precedence
		bool unary;  // is a unary function

		// default constructor
		Func()
			:u_eval(nullptr), b_eval(nullptr), type(TokenTypes::ELSE), prec(0), unary(true)
		{}

		// constructor for unary functions
		Func(UnaryFuncEval eval, TokenTypes type = TokenTypes::FUNCTION, short prec = 0)
			:Func(type, prec, true)
		{
			u_eval = eval;
		}

		// constructor for binary functions
		Func(BinaryFuncEval eval, TokenTypes type = TokenTypes::FUNCTION, short prec = 0)
			:Func(type, prec, false)
		{
			b_eval = eval;
		}

		double eval(double x, double y = 0)
		{
			return this->unary ? u_eval(x) : b_eval(x, y);
		}
	private:
		Func(TokenTypes type, short prec, bool unary)
			: type(type), prec(prec), unary(unary), u_eval(nullptr), b_eval(nullptr)
		{}
	};

	// custom operation functions
	double °¢‹ß_add(double x, double y)
	{
		// pretty
		std::string x_str = toString(x);
		std::string y_str = toString(y);
		std::string b_str = "¡ª¡ª¡ª";
		std::string o_str = toString(x + y);

		/*
			123
			+ 3
			¡ª¡ª¡ª
			126

			 12
			+ 3
			¡ª¡ª¡ª
			 15
		*/
		y_str.insert(0, "+");
		if (o_str.length() < 3)
		{
			while (x_str.length() < 3) x_str.insert(0, " ");
			while (y_str.length() < 3) y_str.insert(1, " ");
			while (o_str.length() < 3) o_str.insert(0, " ");
		}
		else
		{
			while (x_str.length() < o_str.length()) x_str.insert(0, " ");
			while (y_str.length() < o_str.length()) y_str.insert(1, " ");
			while (b_str.length() < o_str.length()) b_str.insert(0, "¡ª");
		}
		printf("%s\n%s\n%s\n%s\n", x_str.c_str(), y_str.c_str(), b_str.c_str(), o_str.c_str());

		return x + y;
	}

	double °¢‹ß_sub(double x, double y)
	{
		// pretty
		std::string x_str = toString(x);
		std::string y_str = toString(y);
		std::string b_str = "¡ª¡ª¡ª";

		bool hasSolution = true;
		int x_len = x_str.length();
		int y_len = y_str.length();

		if (x_len < y_len) hasSolution = false; else
		while (x_len && y_len)
		{
			if (x_str[--x_len] < y_str[--y_len])
			{
				hasSolution = false;
				break;
			}
		}

		/*
			123
			-23
			¡ª¡ª¡ª
			100

			123
			-43
			¡ª¡ª¡ª
			12
			-4
			¡ª¡ª¡ª
			°¢‹ß£º¡¸2u4²»‰ò£¬½è1¡¹
			12
			-4
			¡ª¡ª¡ª
			°¢‹ß£º¡¸2u4²»‰ò£¬½è1¡¹

			...
			...
			infinite loop
			exit(0);
		*/
		if (hasSolution)
		{
			std::string o_str = toString(x - y);

			y_str.insert(0, "-");
			if (x_str.length() < 3)
			{
				while (x_str.length() < 3) x_str.insert(0, " ");
				while (y_str.length() < 3) y_str.insert(1, " ");
				while (o_str.length() < 3) o_str.insert(0, " ");
			}
			else
			{
				while (y_str.length() < x_str.length()) y_str.insert(1, " ");
				while (b_str.length() < x_str.length()) b_str.insert(0, "¡ª");
				while (o_str.length() < x_str.length()) o_str.insert(0, " ");
			}
			printf("%s\n%s\n%s\n%s\n", x_str.c_str(), y_str.c_str(), b_str.c_str(), o_str.c_str());

			return x - y;
		}
		else
		{
			std::stringstream ss;
			x_len = x_str.length();
			y_len = y_str.length();

			if (x_str.length() < 3)
			{
				while (x_str.length() < 3) x_str.insert(0, " ");
				while (y_str.length() < 2) y_str.insert(0, " ");
			}
			else
			{
				while (y_str.length() < x_str.length()) y_str.insert(0, " ");
				while (b_str.length() < x_str.length()) b_str.insert(0, "¡ª");
			}

			while (x_str[--x_len] < y_str[--y_len])
			{
				ss << x_str.substr(0, x_len + 1) << "\n-" << y_str.substr(0, x_len + 1) << b_str << '\n';
			}
			ss << "°¢‹ß£º¡¸" << x_str[x_len] <<"u" << y_str[y_len] << "²»‰ò£¬½è1¡¹\n";

			for (int i = 0; i <= 3; i++)
			{
				ss << x_str.substr(0, x_len + 1) << "\n-" << y_str.substr(0, x_len + 1) << b_str << '\n';
				ss << "°¢‹ß£º¡¸" << x_str[x_len] << "u" << y_str[y_len] << "²»‰ò£¬½è1¡¹\n";
			}
			ss << "...\n...\ninfinite loop exception\n";
			std::cout << ss.str();
			exit(0);
		}
	}

	double °¢‹ß_mul(double x, double y)
	{
		// pretty
		std::string x_str = toString(x);
		std::string y_str = toString(y);
		std::string b_str = "¡ª¡ª¡ª";

		// calculate result
		double r = 0.;
		for (int i = x_str.length() - 1; i >= 0; i--)
		{
			int cur_num = (x_str[i] - int('0')) * y;
			if (i == x_str.length() - 1)  // if it is in 10^0 position
				r += cur_num;
			else
				r += cur_num * std::pow(10, x_str.length() - 1 - i);
		}

		std::string o_str = toString(r);

		/*
			 53
			x 3
			¡ª¡ª¡ª
			  9
			 15
			¡ª¡ª¡ª
			 24

			353
			x 3
			¡ª¡ª¡ª
			  9
			 15
			 9
			¡ª¡ª¡ª
			104
		*/

		y_str.insert(0, "x");
		int max_len = std::max(x_str.length(), y_str.length(), o_str.length());

		if (max_len < 3)
		{
			while (x_str.length() < 3) x_str.insert(0, " ");
			while (y_str.length() < 3) y_str.insert(1, " ");
			while (o_str.length() < 3) o_str.insert(0, " ");
		}
		else
		{
			while (x_str.length() < max_len) x_str.insert(0, " ");
			while (y_str.length() < max_len) y_str.insert(1, " ");
			while (b_str.length() < max_len) b_str.insert(0, "¡ª");
			while (o_str.length() < max_len) o_str.insert(0, " ");
		}
		printf("%s\n%s\n%s\n%s\n", x_str.c_str(), y_str.c_str(), b_str.c_str(), o_str.c_str());

		return r;
	}

	double °¢‹ß_div(double x, double y)
	{
		/*
		   41
		  ¡ª¡ª
		6|30
		  24
		  ¡ª¡ª
		   6
		   6
		  ¡ª¡ª
		   0

		    111.214
		   ¡ª¡ª¡ª
		16|322
		   16
		   ¡ª¡ª¡ª
		   16
		   16
		   ¡ª¡ª¡ª
		    020
			 16
			 ¡ª¡ª
			  40
			  32
			  ¡ª¡ª
			   80
			   64  // every time we got a number divisible by y, let (num - y) be the subtrahend, and let y be the difference
			   ¡ª¡ª
			   16
			   16
			   ¡ª¡ª
			    0


		    ¡ª¡ª¡ª¡ª
		2.5|12.5

		x:=10, y:=10

		     41
		   ¡ª¡ª¡ª
		25|125
		   100
		   ¡ª¡ª¡ª
		    25
			25
			¡ª¡ª
			 0

			  41
			¡ª¡ª¡ª¡ª
		2.5|12.5
		    10.0
			¡ª¡ª¡ª¡ª
			 2.5
			 2.5
			 ¡ª¡ª¡ª
			   0
		*/
		
		// pretty
		std::string x_str = std::to_string(x);
		std::string y_str = std::to_string(y);

		size_t decimal_pos = 0;
		if (x_str[0] == '.') x_str.insert(0, "0");
		if (y_str[0] == '.') y_str.insert(0, "0");
		if (x_str.find('.') != std::string::npos)
			decimal_pos = x_str.length() - x_str.find('.');
		if (y_str.find('.') != std::string::npos)
			decimal_pos =  std::max(decimal_pos, x_str.length() - y_str.find('.'));

		x *= std::pow(10., decimal_pos);
		y *= std::pow(10., decimal_pos);

		int v = std::stoi(x_str.substr(0, y_str.length()));
		if (v < y)
			if (y_str.length() <= x_str.length())
				v = std::stoi(x_str.substr(0, y_str.length() + 1));
			else
				v = std::stoi(x_str.substr(0, x_str.length()) + std::string(y_str.length() - x_str.length(), '0'));

		int remainder = 1;
		int cur_pos = std::to_string(v).length();

		while (remainder)
		{
			if (v % int(y))
			{
				remainder = v % int(y);
			}
			else if (v == int(y))
			{
				remainder = 0;
			}
			else
			{
				remainder = int(y);
			}
		}

		// TODO: GIVE UP

		return 0;
	}

	/* reference */
	// unary functions
	std::map<std::string, Func> unary_functions = {
		{"sqrt", Func()}
	};

	// binary functions
	std::map<std::string, Func> binary_functions = {
		{"+", Func(°¢‹ß_add, TokenTypes::OPERATOR, 2)},
		{"-", Func(°¢‹ß_sub, TokenTypes::OPERATOR, 2)},
		{"*", Func(°¢‹ß_mul, TokenTypes::OPERATOR, 3)},
		{"/", Func(°¢‹ß_div, TokenTypes::OPERATOR, 3)},
	};
}

