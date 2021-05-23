#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "RUS");

	/* Инициализыция */
	double x, y, z, c;
	printf("Введите угол X: >> ");
	scanf("%lf", &x);
	printf("Введите угол Y: >> ");
	scanf("%lf", &y);
	printf("Введите угол Z: >> ");
	scanf("%lf", &z);

	// Перевод в радианы
	x = x * M_PI / 180;
	y = y * M_PI / 180;
	z = z * M_PI / 180;

	// Вычисления
	c = (tan(x) * tan(x) + cos(y)) / sqrt(8 * pow(z, 5));
	/*c = tan(x);
	c *= c;
	c += cos(y);
	c /= sqrt(8 * pow(z, 5));
	*/
	/*
	* Вывод
	*/
	printf("Результат математического выражения:\n>> %f", c);
}
