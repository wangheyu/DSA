#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cstdlib>

void _err_exp();


int main(int argc, char* argv[])
{
	char c;
	std::stack<char> op;
	std::queue<char> exp;
	bool point = false;

	while (true)
	{
		c = std::getchar();
		if (c == '\n')
			break;
		if (c == '\t' || c == ' ')
			continue;
		if (c > '0' && c <'9')
			exp.push(c);
		else if (c == '.')
			if (point == false)
			{
				exp.push(c);
				point = true;
			}
			else
				_err_exp();
		else if (c == ')')
		{
			if (op.empty())
				_err_exp();
			while (!op.empty() && op.top() != '(')
			{
				exp.push(op.top());
				op.pop();
			}
			/// 删除 ( .
			op.pop(); 
		}
		else if (c == '+' || c == '-')
		{
			if (!op.empty())
			{
				while (!op.empty() && op.top() != '(')
				{
					exp.push(op.top());
					op.pop();
				}
			}
			op.push(c);
			point = false;
		}
		else if (c == '*' || c == '/')
		{
			if (!op.empty())
			{
				while (!op.empty() && (op.top() == '*' || op.top() == '/'))
				{
					exp.push(op.top());
					op.pop();
				}
			}
			op.push(c);
			point = false;
		}
		else if (c == '(')
			op.push(c);
		else
			_err_exp();
	}
	if (!op.empty())
	{
		while (!op.empty())
		{
			exp.push(op.top());
			op.pop();
		}
	}

	while (!exp.empty())
	{
		std::cout << ' ' << exp.front();
		exp.pop();
	}
	std::cout << std::endl;
	return 0;
};

void _err_exp()
{
	std::cerr << "Illegal expression." << std::endl;
	exit(-1);
};