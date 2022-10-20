/*
 ============================================================================
 Name        : pu_2010_1.cpp.cpp
 Author      : Tanyo Ivanov
 Version     :
 Copyright   : Tanyo Ivanov
 Description : Решнение на задача от предварителен кандидат-студентски
			   изпит по информатика в Пловдивски университет даван на
			   1 юни 2010 г.
 ============================================================================
 */
#include <iostream>
#include <cstring>

using namespace std;

// Константи за формата да датата
const short unsigned int YMD_FORMAT = 1; // yy.mm.dd
const short unsigned int DMY_FORMAT = 2; // dd.mm.yy

// Константи с кодове класа автомобил
const short unsigned int KLAS_SMAL = 1;
const short unsigned int KLAS_COMPACT = 2;
const short unsigned int KLAS_MIDDLE = 3;
const short unsigned int KLAS_WAN = 4;
const short unsigned int KLAS_JEEP = 5;
const short unsigned int CMP_BY_MARK = 1;
const short unsigned int CMP_BY_KLAS_AND_DATE = 2;
char *getKlasName(char *code, char *klasName);
char *getDateByCode(char *code, char *date, unsigned short int format);

struct Mobile
{
	char mark[41];
	char color[21];
	double price;
	char code[9];
};

void inputMobile(Mobile &mobile);
void displayMobile(Mobile mobile);
bool checkMobile(Mobile mobile);

struct MobilesList
{
	int count;
	Mobile mobiles[200];
};

void initMobilesList(MobilesList &list);
void addMobileToMobilesList(MobilesList &list, Mobile mobile);
void inputMobilesList(MobilesList &list);
void displayMobilesList(MobilesList const &list);
MobilesList getMobilesSublist(MobilesList const &list);
double getAverageMobilesPrice(MobilesList const &list, int klasType);
void sortMobilesList(MobilesList &list, int cmpFunc);
int cmp_by_mark(Mobile mobile1, Mobile mobile2);
int cmp_by_klas_and_date(Mobile mobile1, Mobile mobile2);

int main()
{
	MobilesList mobilesList, subMobilesList;
	double minAveragePrice;

	for (int i = 1; i <= 3; i++)
	{

		std::cout << "Firm " << i << ".\n"
				  << "-------------------\n\n";

		initMobilesList(mobilesList);

		std::cout << "[ Input mobiles ] \n\n";
		inputMobilesList(mobilesList);

		std::cout << "[ List of mobiles ] \n\n";
		sortMobilesList(mobilesList, CMP_BY_MARK);
		displayMobilesList(mobilesList);

		std::cout << "[ List BMW and Audi mobiles to return at  14.08.2008 ] \n\n";
		subMobilesList = getMobilesSublist(mobilesList);
		sortMobilesList(subMobilesList, CMP_BY_KLAS_AND_DATE);
		if (subMobilesList.count > 0)
		{
			displayMobilesList(subMobilesList);
		}
		else
		{
			std::cout << "Not found mobiles!\n";
		}

		double avgPrice;
		avgPrice = getAverageMobilesPrice(mobilesList, KLAS_JEEP);
		std::cout << "[ Average price of jeeps ]" << avgPrice << std::endl;

		if (1 == i)
		{
			minAveragePrice = avgPrice;
		}
		else if (avgPrice < minAveragePrice)
		{
			minAveragePrice = avgPrice;
		}

		std::cout << std::endl;
	}

	cout << "Min jeep average price: " << minAveragePrice << std::endl;

	return 0;
}

/* Намира класа автомобил по зададен код
   Връща указател към низа klasName
 */
char *getKlasName(char *code, char *klasName)
{
	unsigned short int klasCode;
	klasCode = code[1] - '0';

	switch (klasCode)
	{
	case KLAS_SMAL:
		strcpy(klasName, "malak");
		break;
	case KLAS_COMPACT:
		strcpy(klasName, "kompakten");
		break;
	case KLAS_MIDDLE:
		strcpy(klasName, "sreden");
		break;
	case KLAS_WAN:
		strcpy(klasName, "van");
		break;
	case KLAS_JEEP:
		strcpy(klasName, "jeep");
		break;
	}

	return klasName;
}

/* Намира годината на внос по зададен код
   Връща указател към низа year
 */
char *getDateByCode(char *code, char *date, unsigned short int format = DMY_FORMAT)
{
	unsigned short int positions[3] = {2, 4, 6};
	if (YMD_FORMAT == format)
	{
		positions[0] = 6;
		positions[1] = 4;
		positions[2] = 2;
	}

	char *p = (char *)date;
	unsigned short int pos;
	for (int i = 0; i < 3; i++)
	{
		pos = positions[i];
		*p++ = code[pos];
		*p++ = code[pos + 1];
		*p++ = '.';
	}
	*p = '\0';

	return date;
}

/* Въвежда автомобил */
void inputMobile(Mobile &mobile)
{
	std::cout << "Mark: ";
	std::cin.getline(mobile.mark, 41);

	std::cout << "Color: ";
	std::cin.getline(mobile.color, 21);

	std::cout << "Price: ";
	std::cin >> mobile.price;

	std::cout << "Code: ";
	std::cin >> mobile.code;
	cin.get();
}

/* Извежда автомобил на екрана */
void displayMobile(Mobile mobile)
{
	char buff[256];
	std::cout << mobile.mark << ", ";
	std::cout << getKlasName(mobile.code, buff) << ", ";
	std::cout << mobile.color << ", ";
	std::cout << mobile.price << ", ";
	std::cout << getDateByCode(mobile.code, buff) << std::endl;
}

/* Проверява дали дадения автомобил съдържа в името си BMW или AUDI и
   дали и НЕ е върнат на 14.08.2008 */
bool checkMobile(Mobile mobile)
{
	// Ако не съдържа нито Audi нито BMW  в името си се връща false
	if (NULL == strstr(mobile.mark, "Audi") && NULL == strstr(mobile.mark, "BMW"))
	{
		return false;
	}

	char date[20];
	getDateByCode(mobile.code, date, DMY_FORMAT);
	if (0 != strcmp(date, "14.08.2008"))
	{
		return false;
	}

	return true;
}

/* Инициализира списъкът с автомобили */
void initMobilesList(MobilesList &list)
{
	list.count = 0;
}

/* Добавя автомобил към списъка */
void addMobileToMobilesList(MobilesList &list, Mobile mobile)
{
	list.mobiles[list.count++] = mobile;
}

/* Въвежда списък с автомобили */
void inputMobilesList(MobilesList &mobiles)
{
	int cntMobiles;
	do
	{
		std::cout << "Input mobiles count: ";
		std::cin >> cntMobiles;

		if (cntMobiles > 0 && cntMobiles <= 200)
			break;

		std::cout << "Count must be in interval [1, 200]! " << std::endl;
	} while (true);
	std::cin.get();

	Mobile mobile;
	for (int i = 0; i < cntMobiles; i++)
	{
		std::cout << "Input mobile " << (i + 1) << ":\n\n";
		inputMobile(mobile);
		addMobileToMobilesList(mobiles, mobile);
		std::cout << std::endl;
	}
}

/* Извежда списъкът с автомобили на екрана */
void displayMobilesList(MobilesList const &list)
{
	for (int i = 0; i < list.count; i++)
	{
		displayMobile(list.mobiles[i]);
	}
	std::cout << std::endl;
}

/* Връща подсписък по зададените критерии от т. 3 */
MobilesList getMobilesSublist(MobilesList const &list)
{
	MobilesList foundMobiles;
	initMobilesList(foundMobiles);

	for (int i = 0; i < list.count; i++)
	{
		if (true == checkMobile(list.mobiles[i]))
		{
			addMobileToMobilesList(foundMobiles, list.mobiles[i]);
		}
	}

	return foundMobiles;
}

/* Връща средната наемна цена на всички автомобили от даден клас (джипове) */
double getAverageMobilesPrice(MobilesList const &list, int klasType = KLAS_JEEP)
{
	double totalPrice = 0.0;
	int klas, cnt = 0;
	for (int i = 0; i < list.count; i++)
	{
		klas = list.mobiles[i].code[1] - '0';
		if (klasType == klas)
		{
			totalPrice += list.mobiles[i].price;
			cnt++;
		}
	}

	if (0 == cnt)
		return 0.0;

	return totalPrice / cnt;
}

/* Сортира списъка, като указва коя функция за сравнение да се извика.
   (По принцип се реализира чрез указател към тип функция)
*/
void sortMobilesList(MobilesList &list, int cmpFunc = CMP_BY_MARK)
{
	Mobile tmpMobile;
	int pos, cmp;
	for (int i = 0; i < list.count - 1; i++)
	{
		pos = i;
		for (int j = i + 1; j < list.count; j++)
		{

			switch (cmpFunc)
			{
			case CMP_BY_MARK:
				cmp = cmp_by_mark(list.mobiles[j], list.mobiles[pos]);
				break;
			case CMP_BY_KLAS_AND_DATE:
				cmp = cmp_by_klas_and_date(list.mobiles[j], list.mobiles[pos]);
				break;
			default:
				cmp = 0;
			}

			if (cmp < 0)
			{
				pos = j;
			}
		}

		if (pos != i)
		{
			tmpMobile = list.mobiles[i];
			list.mobiles[i] = list.mobiles[pos];
			list.mobiles[pos] = tmpMobile;
		}
	}
}

/* Сравнява два автомобила по марка (лексикографски) */
int cmp_by_mark(Mobile mobile1, Mobile mobile2)
{
	return strcmp(mobile1.mark, mobile2.mark);
}

/* Сравнява два автомобила по клас и по дата  */
int cmp_by_klas_and_date(Mobile mobile1, Mobile mobile2)
{
	char date1[20], date2[20], tmp1[20], tmp2[20];
	getDateByCode(mobile1.code, tmp1, YMD_FORMAT); // Връща yy.mm.dd
	getDateByCode(mobile2.code, tmp2, YMD_FORMAT); // Връща yy.mm.dd

	// Преобразува от yy.mm.dd до yyyy.mm.dd
	if (tmp1[0] <= '1')
		strcpy(date1, "20");
	else
		strcpy(date1, "19");

	if (tmp2[0] <= '1')
		strcpy(date2, "20");
	else
		strcpy(date2, "19");

	strcat(date1, tmp1);
	strcat(date2, tmp2);

	if ('0' == date1[0])
	{
		if ('0' == date2[0])
			return strcmp(date1, date2);
		else
			return 1;
	}
	else
	{
		if ('0' == date2[0])
			return -1;
		else
			return strcmp(date1, date2);
	}
}
