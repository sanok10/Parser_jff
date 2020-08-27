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
	string out0= "";
	string out1= "";
	string outA= "";
};

void consoleOut(int, vershina[]);//функция консольного вывода, принимает длинну списка и список (работает корректно по числу выводов)
vershina FirstHalfparsing(string, int, vershina[]);//функция парсинга первой половины файла
int typecheck(string);//проверка типа поступившей строчки
int obrStr1(string);//для строк вида <from>0</from>&#13;
int obrStr2(string);//для строк вида <to>1</to>&#13;
char obrStr3(string);//для строк вида <read>1</read>&#13;
vershina obrStr4(vershina[], char, string, int, int);//<transout>b</transout>&#13;
string namefinder(string);

int main()
{
	/*char numm, nenum, onemore, onemoredi;
	numm = '1';
	nenum = 'q';
	onemore = 'we';
	onemoredi = '3';
	bool a = true;
	cout << a;
	std::cout << isdigit(numm) <<'\n';
	std::cout << isdigit(nenum) << '\n';
	std::cout << isdigit(onemore) << '\n';
	std::cout << isdigit(onemoredi) << '\n';
	*/
	int findIndex = 0;
	int idcoonected, type, to, transout;
	int findi; // id названное (не внутри массива, а внутри файла)
	char read[1];
	char pri;
	string filename, stroka, name;
	filename = "W:\\ff.txt";//стандартный путь к файлу
	int listLong = 0; // длинна списка вершин
	vershina list[100];
	char id[2];
	//std::std::cout << "пропишите путь к файлу\n";
	//cin >> filename;
	setlocale(LC_ALL, "Russian");
	ifstream file_in;
	file_in.open("W:\\ff.txt");
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
		getline(file_in, stroka);
		type = typecheck(stroka);
		if (type == 1) //строка from
		{
			findi = obrStr1(stroka);// неправильно узнаем откуда 
			//std::cout << findi << " findi\n";
			getline(file_in, stroka);//к следующей строке
			to = obrStr2(stroka);//узнаем куда
			getline(file_in, stroka);//к следующей строке
			pri = obrStr3(stroka);//узнаем  при
			getline(file_in, stroka);
			for (int i = 0; i < listLong; i++)
			{
				if (list[i].id == findi)
				{
					findIndex = i; // findIndex - реальный индекс записи в массиве
					//(где-то тут ошибка, не тот индекс)?
				}
			}
			//pri = read[0];
			*list = obrStr4(list, pri, stroka, findIndex, to); // функция вроде работает сразу с list 
		}
		/*else if (type == 2)//строка to
		{
			to = obrStr2(stroka);
			std::cout << to <<" to\n";
		}
		else if (type == 3)//строка read
		{
			read[1] = obrStr3(stroka, read[1]);
			std::cout << read[1] <<" read\n";
		}*/
		//то что ниже возможно более не нужно
		/*else if (type == 4)//строка transout
		{
			for (int i = 0; i < listLong; i++)
			{
				if (list[i].id == findi)
				{
					findIndex = i;
				}
			}
			*list = obrStr4(list, pri, stroka, findIndex, to); // функция вроде работает сразу с list 
		}*/
		else if (type == 0)//заполнение задачами
		{
			if (listLong > 0)
			{
				list[listLong ] = *list;
			}
			*list = FirstHalfparsing(stroka, listLong, list);//записывает все найденное в указатель
			listLong++;
		}
	}
	std::cout << '\n';
	for (int i = 0; i < listLong; i++)
	{
		std::cout << list[i].id << " id\n";
		std::cout << list[i].name << " name\n";
		std::cout << list[i].connect0 << " con0\n";
		std::cout << list[i].connect1 << " con1\n";
		std::cout << list[i].connectA << " conA\n";
		std::cout << list[i].out0 << " Out0\n";
		std::cout << list[i].out1 << " out1\n";
		std::cout << list[i].outA << " outA\n";
	}
	consoleOut (listLong, list);

	std::cout << listLong;
	int aaaa;
	std::cout << "Конец программы \n" << endl;
	std::cin >> aaaa;//стоппер консоли
	//system("pause");
	return 0;
}

//проверка типа поступившей строчки
int typecheck(string stroka)
{
	int type=-1;
	for (int i = 0; i < stroka.size(); i++)
	{
		if (stroka[i] == 'f' && stroka[i + 1] == 'r') //если нашли 'from'
		{
			type = 1;
		}
		if (stroka[i]=='t' && stroka [i+1] == 'o' && stroka[i+2] == '<')//ecли нашли to
		{
			type = 2;
		}
		if (stroka[i] == 'r' && stroka[i+1] == 'e')//если нашли read
		{
			type = 3;
		}
		if (stroka[i] == 't' && stroka[i+1] == 'r' && stroka[i+2] == 'a' && stroka[i+3] == 'n' && stroka[i+4] == 's' && stroka[i+5] == 'o' && stroka[i+6] == 'u' && stroka[i+7] == 't')
		{
			type = 4;
		}
		if (stroka[i] == 'i' && stroka[i + 1] == 'd')//если нашли id
		{
			type = 0;
		}
	}
	return type;
}

/*while (stroka[iName] != '"')
			{
				list[listLong - 1].name += stroka[iName];
				iName++;
			}*/

//функция заполнения структуры с вершинами
vershina FirstHalfparsing(string stroka, int listLong, static vershina list[])
{
	char id[2];
	for (unsigned int i = 0; i < stroka.size(); i++)
	{
		if (isdigit(stroka[i]) != 0 && isdigit(stroka[i + 1]) == 0)  // если нашли однозначный id
		{
				listLong += 1;
				id[1] = stroka[i];
				id[0] = NULL;

				list->id = id[1] - 48; // atoi(id); // тут цепляет id! 
					//std::cout << list[listLong - 1].id+15 << "\n";
				list->name = namefinder(stroka);//теперь тут нормально
				/*int iName = i + 13; //вспомогательный счетчик для поиска имени
				while (stroka[iName] != '"')
				{
					list[listLong - 1].name += stroka[iName];
					iName++;
				}
				//std::cout << list[listLong - 1].name << "\n";*/
				//обнуляем переменные
					//iName = 0;
				id[1] = NULL;
			id[0] = NULL;
			i = stroka.size(); //заканчиваем вычисления в этой строке и обнуляем переменные
		}
		else if (isdigit(stroka[i]) != 0 && isdigit(stroka[i + 1]) != 0) // если нашли 2 значный айди
		{
			listLong += 1;
			id[1] = stroka[i + 1];
			id[0] = stroka[i];
			list->id = atoi(id);//присвоение id
			list->name = namefinder(stroka);
		}
	}
	 return *list;
}

//функция поиска имени (возможно не нужна)
string namefinder(string stroka)
{
	string name;
	for (int i = 0; i < stroka.size(); i++)
	{
		if (stroka[i] == 'n' && stroka[i+1] == 'a' && stroka[i+2] == 'm' && stroka[i+3] == 'e')
		{
			while (stroka[i+6] != '"')
			{
				name += stroka[i+6];
				i++;
			}
		}
		
	}
	return name;
}

// строка вида <from>0</from>&#13;
int obrStr1(string stroka )
{
	char id[2];
	int findi = -1; //найденное в файле id
	for (int i = 0; i <= stroka.size(); i++)
	{
		if (stroka[i] == 'f' && stroka[i + 1] == 'r') //если нашли 'from'
		{
			
			if (stroka[i + 6] == '<') // для односимвольных id
			{
				id[0] = stroka[i + 5]; 
				//id[1] = NULL;
				findi = atoi (id);
				i = stroka.size();
			}
			else // для двусимвольных
			{
				id[0] = stroka[i + 5];
				id[1] = stroka[i + 6];
				findi = atoi(id);
				cout << findi << " findi в функции\n";
				i = stroka.size();
			}
			

		}
		
	}
	
	return findi;
}

// строка вида <to>1</to>&#13; работает некорректно
int obrStr2(string stroka)
{
	char id[2];
	int idconnected;
	//получаем id вершины, с которой соеденен, попутно проверяя сколько в нем цифр  
	for (unsigned int iii = 0; iii < stroka.size(); iii++)
	{
		if (isdigit(stroka[iii]) && !isdigit(stroka[iii + 1])) // для односимвольных
		{
			id[0] = stroka[iii];
			//id[0] = NULL;
			iii = stroka.size(); //завершаем вычисления для строки
			std::cout << "односимв айди \n";
			idconnected = atoi(id);
		}
		if (isdigit(stroka[iii]) && isdigit(stroka[iii + 1]))
		{
			id[0] = stroka[iii];
			id[1] = stroka[iii + 1];
			iii = stroka.size(); //завершаем вычисления для строки
			std::cout << "двухсимв айди \n";
			idconnected = atoi(id) ;//id вершины с которой соеденена та, что из списка
		}

	}
	
	return idconnected;
}

// строка вида <read>1</read>&#13; работает корректно
//TODO: Заменить конкретные символы на абстрактные для расширения функционала
char obrStr3(string stroka)
{
	char re;
	for (unsigned int iii = 0; iii < stroka.size(); iii++)
	{
		if (stroka[iii] == '0') 
		{
			re = '0';
		}
		if (stroka[iii] == '1')
		{
			re = '1';
		}
		if (stroka[iii] == 'a')
		{
			re = 'a';
		}
	}
	return re;
}

//обработчик строк вида <transout>b</transout>&#13; работает корректно
vershina obrStr4(vershina list[], char pri, string stroka, int elemNum, int to)
{
	for (int iii = 0; iii < stroka.size(); iii++) //тут работаем с выводимым значением, ищем слово transout
	{
		if (stroka[iii] == 't' && stroka[iii+6] == 'u')
		{
			if (pri == 'a')
			{ 
				list[elemNum].outA = stroka[iii + 9];
				list[elemNum].connectA = to; //задаем с какой вершиной соед. при А
				//std::cout << "pri a\n";
			}
			if (pri == '1')
			{
				list[elemNum].out1 = stroka[iii + 9];
				list[elemNum].connect1 = to; // с какой вершиной соед. при 1
				//std::cout << "pri 1\n";
			}
			if (pri == '0')
			{
				list[elemNum].out0 = stroka[iii + 9];
				list[elemNum].connect0 = to; // с какой соед. при 0
				//std::cout << "pri 0\n";
			}
			iii = stroka.size();
		}
	}
	return *list;
}


//функция консольного вывода, принимает длинну списка и список (недоделанная)
void consoleOut(int listLong, vershina list[100]) 
{
		std::cout << "Имя точки| " << "переход при 0|" << "переход при 1" << "| переход при а\n"; //далее функция вывода результатов с графлением
	for (int iii = 0; iii < listLong ; iii++)
	{
		std::cout << ". \n";

		if (list[iii].connect0 != -1)
		{
			std::cout << list[iii].name << "      | " << list[iii].connect0 << "/" << list[iii].out0 << "          |  " << "----------" << "  |  " << "----------\n";
		}
		if (list[iii].connect1 != -1)
		{
			std::cout << list[iii].name << "       | " << "---------- " << "  |  " << list[iii].connect1 << " " << list[iii].out0 << "           |  " << "----------\n";
		}
		if (list[iii].connectA != -1)
		{
			std::cout << list[iii].name << "       | " << "----------" << "  |  " << "-----------" << "  |  " << list[iii].connectA << " " << list[iii].out0 << "\n";
		}
		if (list[iii].connect0 == -1 && list[iii].connect1 == -1 && list[iii].connectA == -1)
		{
			std::cout << list[iii].name << "       | " << "---------- " << "  |  " << "-----------" << "  |  " << "----------\n";
		}
	}
}

// перенести прогу в винформс, добавить функцию вывода таблицы в файл, добавить функции упрощения таблицы
//TODO: Заменить конкретные символы на абстрактные для расширения функционала



//old main cykle
//
////getline(file_in, stroka);
//
//
//getline(file_in, stroka);
//for (unsigned int i = 0; i < stroka.size(); i++)
//{
//	//если мы в первой половине файла
//	if (stroka[i] == 'i' && stroka[i + 1] == 'd') // выцепляем id и имена вершин (работает корректно)
//	{
//		if (stroka[i + 5] != '0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9') // если нашли однозначный id
//		{
//			listLong += 1;
//			id[1] = stroka[i + 4];
//			id[0] = NULL;
//
//			list[listLong - 1].id = id[1] - 48; // atoi(id); // тут цепляет id!
//				//std::cout << list[listLong - 1].id+15 << "\n";
//			int iName = i + 13; //вспомогательный счетчик для поиска имени 
//			while (stroka[iName] != '"')
//			{
//				list[listLong - 1].name += stroka[iName];
//				iName++;
//			}
//			//std::cout << list[listLong - 1].name << "\n";
//		//обнуляем переменные
//			iName = 0;
//			id[1] = NULL;
//			id[0] = NULL;
//			i = stroka.size(); //заканчиваем вычисления в этой строке и обнуляем переменные
//		}
//		else //если мы нашли строку без текста id
//		{
//			if (stroka[i] != 'f' && stroka[i + 1] != 'r')//проверяем что не находимся во второй половине файла
//			{
//				int iName = i + 14; //вспомогательный счетчик для поиска имени 
//				id[0] = stroka[i + 4];
//				id[1] = stroka[i + 5];
//				//* 10 + atoi(stroka[i + 5]);
//				list[iName].id = atoi(id);
//				//list[listLong].id = stroka[i + 4];
//				while (stroka[iName] != '"') //красивое обращение с именами, по этому принципу сделать и остальные
//				{
//					list[iName].name += stroka[iName];
//					iName++;
//				}
//				iName = 0;
//				listLong += 1;
//				i = stroka.size(); //заканчиваем вычисления в этой строке
//			}
//
//		}
//
//	}//<--------------------------------до сюда правильно работает--------------------------------->
//
//	// работа со второй половиной файла
//	//считываем переходы 
//	if (stroka[i] == 'f' && stroka[i + 1] == 'r') //если нашли 'from'
//	{
//		int findi; //найденное в файле id
//		if (stroka[i + 6] = '<') // для односимвольных id
//		{
//			id[1] = stroka[i + 5]; //очень сомнительный способ работы, надо чето менять(?)
//			id[0] = NULL;
//		}
//		else // для двусимвольных
//		{
//			id[1] = stroka[i + 6];
//			id[0] = stroka[i + 5];
//		}
//		findi = atoi(id); //тоже потенциально не работает, хотя вряд ли
//			//std::cout << findi << "\n";
//		id[0] = NULL;
//		id[1] = NULL;
//
//		/*ниже возможно допущена логическая ошибка - нужно не перебирать список в поисках совпадений,
//		а идти по файлу в препрыжку обращаясь иногда к списку. номер в списке нельзя связывать с id,
//		иначе список рискует быть "дырявым"*/
//
//		for (int numInList = 0; numInList <= listLong - 1; numInList++) //перебираем наш список вершин и устанавливаем связи
//		{
//			if (list[numInList].id == findi)//когда дошли до нужного элемента в обработанном списке
//			{
//				//obrStr2(findi, str);
//				//std::cout << "here \n";
//				getline(file_in, stroka2); //строка формата <to>x</to>&#13;
//				//получаем id вершины, с которой соеденен, попутно проверяя сколько в нем цифр  
//				for (unsigned int iii = 0; iii < stroka2.size(); iii++)
//				{
//					if (isdigit(stroka2[iii]) && !isdigit(stroka2[iii + 1])) // для односимвольных
//					{
//						id[1] = stroka2[iii];
//						id[0] = NULL;
//						iii = stroka2.size(); //завершаем вычисления для строки
//						std::cout << "односимв айди \n";
//					}
//					if (isdigit(stroka2[iii]) && isdigit(stroka2[iii + 1]))
//					{
//						id[0] = stroka2[iii];
//						id[1] = stroka2[iii + 1];
//						iii = stroka2.size(); //завершаем вычисления для строки
//						std::cout << "двухсимв айди \n";
//					}
//
//				}
//				//std::cout << id[0] << id[1] << " \n";
//				idcoonected = id[0] * 10 + id[1] - 48;//id вершины с которой соеденена та, что из списка
//				std::cout << idcoonected << "\n";
//
//				id[0] = NULL;
//				id[1] = NULL;
//				// ищем при каком входе соеденины
//				getline(file_in, stroka);  //строка формата <read>x</read>&#13;
//				for (unsigned int iii = 0; iii < stroka.size(); iii++)
//				{
//					if (stroka[iii] == '0' || '1' || 'a') //TODO: Заменить конкретные символы на абстрактные для расширения функционала
//					{
//
//						if (stroka[iii] == '0' && stroka[iii + 1] == '<')
//						{
//							list[findi].connect0 = idcoonected;//вешаем id на коннект при нуле 
//							getline(file_in, stroka3);//получаем следующую строку 
//							//Думаю это можно вывести в функцию -------------->
//							iii = 0;
//							for (int iii = 0; iii < stroka3.size(); iii++) //тут работаем с выводимым значением, ищем слово transout
//							{
//								if (stroka3[iii] == 't' && stroka3[iii + 5] == 'o')
//								{
//									list->out0 = iii + 9;
//									//std::cout << "pri 0\n";
//								}
//							}//--------------------------------> //выдераем символ
//							//записываем вывод в соответствии со входом
//
//							//в дальнейшем - точно должно стать функцией, блябуду
//						}
//						if (stroka[iii] == '1' && stroka[iii + 1] == '<')
//						{
//							list[findi].connect1 = idcoonected;
//							getline(file_in, stroka3);//получаем следующую строку 
//							iii = 0;
//							for (int iii = 0; iii < stroka3.size(); iii++) //тут работаем с выводимым значением, ищем слово transout
//							{
//								if (stroka3[iii] == 't' && stroka3[iii + 5] == 'o')
//								{
//									list->out1 = iii + 9;
//									std::cout << "pri 1\n";
//								}
//							}
//						}
//						if (stroka[iii] == 'a' && stroka[iii + 1] == '<')
//						{
//							list[findi].connectA = idcoonected;
//							getline(file_in, stroka3);//получаем следующую строку 
//							iii = 0;
//							list[100] = obrStr4(list[100]);
//
//							/*for (int iii = 0; iii < stroka3.size(); iii++) //тут работаем с выводимым значением, ищем слово transout
//							{
//								if (stroka3[iii] == 't' && stroka3[iii + 5] == 'o')
//								{
//									list->outA = iii + 9;
//										std::cout << "pri a\n";
//								}
//							}*/
//						}
//					}
//
//					//list[sss].out
//					getline(file_in, stroka); // ищем при каком входе соеденины
//					iii++;
//				}
//
//				/*iii = 0;
//				getline(file_in, stroka3);
//				{
//						for (stroka[iii] == 't' && stroka[iii + 5] == 'o') //тут работаем с выводимым значением, ищем слово transout
//					{
//						if (list[findi]. == '0')
//						{
//							list[findi]. = ;
//						}
//						if (stroka[iii] == '1')
//						{
//							list[findi]. = ;
//						}
//						if (stroka[iii] == 'b')
//						{
//							list[findi]. = ;
//						}
//						iii = stroka.size(); //завершаем работу со строкой
//					}
//				}*/
//			}
//			numInList++; //переходим к следующему эл-ту списка
//		}
//
//	}
//
//}
//
///*for (int i = 0; i < stroka.size(); i++)
//{
//	if (stroka[i] == 'f' && stroka[i + 1] == 'r')
//
//
//}*/
//	}