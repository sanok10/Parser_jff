// парсер для та.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
struct vershina
{
	int id;
	string name;
	int connectA=-1;
	int connect0=-1;
	int connect1=-1;
	int out0= NULL;
	int out1= NULL;
	int outA= NULL;
};


int main()
{
	int idcoonected;
	string filename, stroka, stroka2, stroka3, stroka4, name;
	int listLong = 0; // длинна списка вершин
	vershina list[100];
	char id[2];
	//std::cout << "пропишите путь к файлу\n";
	//cin >> filename;
	setlocale(LC_ALL, "Russian");
	ifstream file_in;
	file_in.open("w:\\ff.txt");
	if (!file_in)
	{
		std::cout << "Проблемы с открытием файла";
	}
	else
	{
		std::cout << "Файл открыт!\n";
	}

	
	while (!file_in.eof()) // основной цикл
	{
		//getline(file_in, stroka);
		
			
			getline(file_in, stroka);
			for (unsigned int i = 0; i < stroka.size(); i++)
			{
				if (stroka[i] == 'i' && stroka[i + 1] == 'd') // выцепляем id и имена вершин
				{
					if (stroka[i + 5] != '0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9') // если нашли однозначный id
					{
						listLong += 1;
						id[1] = stroka[i + 4];
						id[0] = NULL;

						list[listLong - 1].id = id[1] - 48; // atoi(id); // тут не правильно цепляет id!!!!!!!!!!!!!!!!!!!

						int iName = i + 13; //вспомогательный счетчик для поиска имени 
						while (stroka[iName] != '"')
						{
							list[listLong - 1].name += stroka[iName];
							iName++;
						}
						iName = 0;
						id[1] = NULL;
						id[0] = NULL;
						i = stroka.size(); //заканчиваем вычисления в этой строке и обнуляем переменные
					}
					else
					{
						if (stroka[i] != 'f' && stroka[i + 1] != 'r')
						{
							int iName = i + 14; //вспомогательный счетчик для поиска имени 
							id[0] = stroka[i + 4];
							id[1] = stroka[i + 5];
							//* 10 + atoi(stroka[i + 5]);
							list[iName].id = atoi(id);
							//list[listLong].id = stroka[i + 4];
							while (stroka[iName] != '"')
							{
								list[iName].name += stroka[iName];
								iName++;
							}
							iName = 0;
							listLong += 1;
							i = stroka.size(); //заканчиваем вычисления в этой строке
						}

					}

				}
				// работа со второй половиной файла

				if (stroka[i] == 'f' && stroka[i + 1] == 'r') //считываем переходы 
				{
					int findi; //найденное id
					if (stroka[i + 6] = '<') // для односимвольных id
					{
						id[1] = stroka[i + 5]; //очень сомнительный способ работы, надо чето менять
						id[0] = NULL;
					}
					else // для двусимвольных
					{
						id[1] = stroka[i + 6];
						id[0] = stroka[i + 5];
					}
					findi = atoi(id); //тоже потенциально не работает
					id[0] = NULL;
					id[1] = NULL;

					/*ниже возможно допущена логическая ошибка - нужно не перебирать список в поисках совпадений,
					а ебошить по файлу в препрыжку обращаясь иногда к списку. номер в списке нельзя связывать с id, 
					иначе список рискует быть "дырявым"*/

					for (int numInList = 0; numInList < listLong - 1; numInList++) //перебираем список вершин и устанавливаем связи
					{
						if (list[numInList].id == findi)//когда дошли до нужного элемента в списке
						{

							getline(file_in, stroka2);
							for (unsigned int iii = 0; iii < stroka2.size(); iii++)
							{
								if (isdigit(stroka2[iii]) && !isdigit(stroka2[iii + 1])) // для односимвольных
								{
									id[1] = stroka2[iii];
									id[0] = NULL;
									iii = stroka2.size(); //завершаем вычисления для строки

								}
								if (isdigit(stroka2[iii]) && isdigit(stroka2[iii + 1]))
								{
									id[0] = stroka2[iii];
									id[1] = stroka2[iii + 1];
									iii = stroka2.size(); //завершаем вычисления для строки
								}
								
							}
							idcoonected = atoi(id);//хуита, перенести в циклы
							id[0] = NULL;
							id[1] = NULL;
							getline(file_in, stroka); // ищем при каком входе соеденины 
							for (unsigned int iii = 0; iii < stroka.size(); iii++)
							{
								if (stroka[iii] == '0' || '1' || 'a') //TODO: Заменить конкретные символы на абстрактные для расширения функционала
								{

									if (stroka[iii] == '0' && stroka[iii + 1] == '<')
									{
										list[findi].connect0 = idcoonected;
										getline(file_in, stroka3);//получаем следующую строку 
										iii = 0;
										for (int iii = 0; iii < stroka3.size(); iii++) //тут работаем с выводимым значением, ищем слово transout
										{
											if (stroka3[iii] == 't' && stroka3[iii + 5] == 'o')
											{
												list->out0 = iii + 9;
											}
										}										   //выдераем символ
										//записываем вывод в соответствии со входом

										//в дальнейшем - точно должно стать функцией, блябуду
									}
									if (stroka[iii] == '1' && stroka[iii + 1] == '<')
									{
										list[findi].connect1 = idcoonected;
										getline(file_in, stroka3);//получаем следующую строку 
										iii = 0;
										for (int iii = 0; iii < stroka3.size(); iii++) //тут работаем с выводимым значением, ищем слово transout
										{
											if (stroka3[iii] == 't' && stroka3[iii + 5] == 'o')
											{
												list->out1 = iii + 9;
											}
										}
									}
									if (stroka[iii] == 'a' && stroka[iii + 1] == '<')
									{
										list[findi].connectA = idcoonected;
										getline(file_in, stroka3);//получаем следующую строку 
										iii = 0;
										for (int iii = 0; iii < stroka3.size(); iii++) //тут работаем с выводимым значением, ищем слово transout
										{
											if (stroka3[iii] == 't' && stroka3[iii + 5] == 'o')
											{
												list->outA = iii + 9;
											}
										}
									}
								}
								
								//list[sss].out
							}
							//iii = 0;
							//getline(file_in, stroka3);
							//{
							//		for (stroka[iii] == 't' && stroka[iii + 5] == 'o') //тут работаем с выводимым значением, ищем слово transout
							//	{
							//		if (list[findi]. == '0')
							//		{
							//			list[findi]. = ;
							//		}
							//		if (stroka[iii] == '1')
							//		{
							//			list[findi]. = ;
							//		}
							//		if (stroka[iii] == 'b')
							//		{
							//			list[findi]. = ;
							//		}
							//		iii = stroka.size(); //завершаем работу со строкой
							//	}
							//}
						}
					}

				}

			}

		/*for (int i = 0; i < stroka.size(); i++)
		{
			if (stroka[i] == 'f' && stroka[i + 1] == 'r')
			

		}*/
	}


	cout << "Имя точки| " << "переход при 0|" << "переход при 1" << "| переход при а\n"; //далее функция вывода результатов с графлением
	for (int iii = 0; iii < listLong-1; iii++)
	{
		
		if (list[iii].connect0 != -1)
		{
			cout << list[iii].name << "      | " << list[iii].connect0 << "/"<< list[iii].out0 << "          |  " << "----------" << "  |  " << "----------\n";
		}
		if (list[iii].connect1 != -1)
		{
			cout << list[iii].name << "       | " << "---------- " << "  |  " << list[iii].connect1 << "/" << list[iii].out0 << "             |  " << "----------\n";
		}
		if (list[iii].connectA != -1)
		{
			cout << list[iii].name << "       | " << "----------" << "  |  " << "-----------" << "  |  " << list[iii].connectA << "/" << list[iii].out0 << "\n";
		}
	}

	int aaaa;
	std::cout << "Конец программы \n" << endl;
	std::cin >> aaaa;//стоппер консоли
	//system("pause");
	return 0;
}


// перенести прогу в винформс, добавить функцию вывода таблицы в файл, добавить функции упрощения таблицы



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
