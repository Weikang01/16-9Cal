#if defined(_WIN32)
#include <Windows.h>
#elif defined(_WIN64)
#include <Windows.h>
#endif
#include <iostream>
#include <string>

#pragma execution_character_set( "utf-8" )

int main()
{
#if defined(_WIN32)
	SetConsoleOutputCP(65001); // use utf-8
#elif defined(_WIN64)
	SetConsoleOutputCP(65001); // use utf-8
#endif

	std::cout << "The current calculator only support integer arithmetic operations\n\n";

	std::cout << "Ո������һ�����}��" << std::endl;
	std::string eqn = "30/6";
	std::cout << "\n���ߣ����@��ޝu�Σ��@�}�ܺ��Σ�...��" << std::endl;

	return 0;
}