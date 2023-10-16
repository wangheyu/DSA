#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cstdlib>

// 错误处理函数
void _err_exp();


int main(int argc, char* argv[])
{
	char c;   // 读入缓冲区
	std::stack<char> op;    // 操作符栈
	std::queue<char> exp;   // 后缀表达式队列
	bool point = false;     // 小数点使用标志

	while (true)
	{
		c = std::getchar();
		// 输入以回车结束
		if (c == '\n')
			break;
		// 制表符和空格跳过
		if (c == '\t' || c == ' ')
			continue;
		// 数字直接输出
		if (c > '0' && c <'9')
			exp.push(c);
		// 允许小数点
		else if (c == '.')
			// 只允许一个小数点
			if (point == false)
			{
				exp.push(c);
				point = true;
			}
			else
				_err_exp();
		// 这一段逻辑和括号匹配类似, 但只考虑小括号
		else if (c == ')')
		{
			if (op.empty())
				_err_exp();
			// 这里其实没有排除一对空括号的情形, 
			// 一对括号内的全部运算符都应该输出
			while (!op.empty() && op.top() != '(')
			{
				exp.push(op.top());
				op.pop();
			}
			/// 删除 ( 
			op.pop(); 
		}
		else if (c == '+' || c == '-')
		{
			// 加减运算优先级低, 所以清空全部运算符, 
			// 直到遇到左括号或者空栈.
			if (!op.empty())
			{
				while (!op.empty() && op.top() != '(')
				{
					exp.push(op.top());
					op.pop();
				}
			}
			// 插入当前的 +/- 运算符
			op.push(c);
			// 准备输入数字
			point = false;
		}
		else if (c == '*' || c == '/')
		{
			if (!op.empty())
			{
				// 只清空同级别运算符
				while (!op.empty() && 
				       (op.top() == '*' || op.top() == '/'))
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
	// 输入完毕, 但操作符栈中可能还有运算符,
	// 全部输出到后缀表达式队列中
	if (!op.empty())
	{
		while (!op.empty())
		{
			exp.push(op.top());
			op.pop();
		}
	}
	// 输出后缀表达式
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