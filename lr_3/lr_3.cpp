// ConsoleApplication5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

typedef struct koef_interpol_s
{
	double x;
	double y;
	double a;
	double b;
	double c;
	double d;
}koef_interpol;


double func(double x)
{
	return x * x;
}


double get_h(std::vector<koef_interpol> koef_vector, int i)
{
	if (i == 0)
		return 0;
	else
		return koef_vector[i].x - koef_vector[i - 1].x;
}

void find_koef_spline(std::vector<koef_interpol> &koef_vector)
{
	int kol_vo = koef_vector.size();
	std::vector<double> pr_koef_1;
	std::vector<double> pr_koef_2;
	pr_koef_1.resize(kol_vo + 1);
	pr_koef_2.resize(kol_vo + 1);

	pr_koef_1[0] = 0;
	pr_koef_2[0] = 0;

	for (int i = 1; i < kol_vo - 1; i++)
	{
		double A = get_h(koef_vector, i);
		double B = 2 * (get_h(koef_vector, i + 1) + get_h(koef_vector, i));
		double D = get_h(koef_vector, i + 1);
		double F = 6 * ((koef_vector[i + 1].y - koef_vector[i].y) / get_h(koef_vector, i + 1) - (koef_vector[i].y - koef_vector[i - 1].y) / get_h(koef_vector, i));
		pr_koef_1[i + 1] = -(D / (B + A * pr_koef_1[i]));
		pr_koef_2[i + 1] = ((F - A * pr_koef_2[i]) / (B + A * pr_koef_1[i]));
	}

	koef_interpol koef_int;
	koef_int.c = 0;
	koef_vector[0].c = 0;

	koef_vector.push_back(koef_int);

	/*for (int i = 0; i < kol_vo; i++)
	{
	printf("%lf   %lf\n", pr_koef_1[i], pr_koef_2[i]);
	}*/


	koef_vector[kol_vo - 1].c = pr_koef_2[kol_vo - 1];
	for (int i = kol_vo - 2; i > 0; i--)
	{
		//printf("!! %lf\n", pr_koef_2[i + 1]);
		koef_vector[i].c = koef_vector[i + 1].c * pr_koef_1[i + 1] + pr_koef_2[i + 1];
		//printf("!! %lf   %lf   %lf\n", koef_vector[i].c, pr_koef_1[i], pr_koef_2[i]);
	}
	koef_vector[0].a = 0;
	koef_vector[0].b = 0;
	koef_vector[0].d = 0;

	for (int i = 1; i < kol_vo; i++)
	{
		koef_vector[i].a = koef_vector[i].y;
		koef_vector[i].b = (koef_vector[i].y - koef_vector[i - 1].y) / get_h(koef_vector, i) + get_h(koef_vector, i) * (2 * koef_vector[i].c + koef_vector[i - 1].c) / 6;
		koef_vector[i].d = (koef_vector[i].c - koef_vector[i - 1].c) / get_h(koef_vector, i);
		//printf("!! %lf   %lf   %lf\n", koef_vector[i].c, pr_koef_1[i], pr_koef_2[i]);
	}
	pr_koef_1.clear();
	pr_koef_2.clear();
}

double find_znach(std::vector<koef_interpol> koef_vector, double find_x, int kol_vo)
{
	int ind;
	for (int i = 1; i < kol_vo; i++)
	{
		ind = i;
		if (find_x > koef_vector[i - 1].x && find_x <= koef_vector[i].x)
		{
			break;
		}
	}
	//printf("ind = %d\n", ind);
	//printf("## %lf  %lf  %lf  %lf \n", koef_vector[ind].a, koef_vector[ind].b, koef_vector[ind].c, koef_vector[ind].d);
	double res = koef_vector[ind].a + koef_vector[ind].b*(find_x - koef_vector[ind].x) + (koef_vector[ind].c / 2)* pow((find_x - koef_vector[ind].x), 2) + (koef_vector[ind].d / 6)* pow((find_x - koef_vector[ind].x), 3);

	return res;
}

int check_div_zero(std::vector<koef_interpol> koef_vector, double x)
{
	double eps = 0.001;
	for (int i = 0; i < koef_vector.size(); i++)
	{
		if (fabs(koef_vector[i].x - x) < eps)
			return 0;
	}
	return 1;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	double x_find;
	koef_interpol koef_int;
	std::vector<koef_interpol> koef_vector;

	int kol_vo;

	int choose;


	while (1)
	{
		printf("1 - ввести значения вручную\n");
		printf("2 - использовать значения функции\n");
		while (1)
		{
			printf("Ваш выбор: ");
			if (!(std::cin >> choose))
			{
				printf("Некорректно введено значение\n");
				std::cin.clear();
				std::cin.ignore(15000, '\n');
				continue;
			}
			break;
		}
		if (choose == 1)
		{
			koef_vector.clear();
			while (1)
			{
				printf("Введите количество точек: ");
				if (!(std::cin >> kol_vo))
				{
					printf("Некорректно введено значение\n");
					std::cin.clear();
					std::cin.ignore(15000, '\n');
					continue;
				}
				if (kol_vo < 3)
				{
					printf("Необходимо минимум 3 точки\n");
					std::cin.clear();
					std::cin.ignore(15000, '\n');
					continue;
				}
				break;
			}
			printf("Вводите x и y через пробел\n");
			for (int i = 0; i < kol_vo; i++)
			{
				while (1)
				{
					printf("%d) ", i + 1);
					double x_read, y_read;
					if (!(std::cin >> x_read) || !(std::cin >> y_read))
					{
						printf("Некорректно введены значения\n");
						std::cin.clear();
						std::cin.ignore(15000, '\n');
						continue;
					}

					if (!check_div_zero(koef_vector, x_read))
					{
						printf("Такое значение x уже есть!\n");
						std::cin.clear();
						std::cin.ignore(15000, '\n');
						continue;
					}
					koef_int.x = x_read;
					koef_int.y = y_read;

					break;
				}
				koef_vector.push_back(koef_int);
			}

			find_koef_spline(koef_vector);
			/*for (int i = 0; i < kol_vo; i++)
			{
			printf("%lf  %lf  %lf  %lf \n", koef_vector[i].a, koef_vector[i].b, koef_vector[i].c, koef_vector[i].d);
			}*/
			while (1)
			{
				printf("Введите интересующий x: ");
				if (!(std::cin >> x_find))
				{
					printf("Некорректно введено значение\n");
					std::cin.clear();
					std::cin.ignore(15000, '\n');
					continue;
				}
				break;
			}

			double res = find_znach(koef_vector, x_find, kol_vo);
			printf("Полученный ответ = %lf\n", res);

		}
		else if (choose == 2)
		{
			koef_vector.clear();
			kol_vo = 20;
			double begin = -10;
			printf("x        y\n");
			for (int i = 0; i < kol_vo; i++)
			{
				koef_int.x = begin;
				koef_int.y = func(koef_int.x);
				printf("%7.3lf   %7.4lf\n", koef_int.x, koef_int.y);
				koef_vector.push_back(koef_int);
				begin++;
			}
			while (1)
			{
				printf("Введите интересующий x: ");
				if (!(std::cin >> x_find))
				{
					printf("Некорректно введено значение\n");
					std::cin.clear();
					std::cin.ignore(15000, '\n');
					continue;
				}
				break;
			}
			find_koef_spline(koef_vector);
			/*for (int i = 0; i < kol_vo; i++)
			{
			printf("%lf  %lf  %lf  %lf \n", koef_vector[i].a, koef_vector[i].b, koef_vector[i].c, koef_vector[i].d);
			}*/
			double res = find_znach(koef_vector, x_find, kol_vo);
			printf("Полученный ответ = %lf\nВерный ответ = %lf\n", res, func(x_find));
		}
	}
	system("pause");
	return 0;
}

