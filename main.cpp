#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;
struct Users
{
	string login;
	string password;
	int role;
	int access;
};
struct Flight
{
	int flight_number; // номер рейса
	string type_of_plane; // Тип самолета
	string destrination; // пункт назначения
	int destrination_date_day; // дата вылета дни
	int destrination_date_month; // дата вылета месяцы
	int вeparture_time_hour; // время вылета часы
	int вeparture_time_minute; // время вылета минуты
	int flight_time; // время полета
	int aircraft_capacity; // вместимость самолета
	int tickets_of_business_class; // Билеты бизнес класса
	int price_of_business_class; // Цена бизнес класса
	int tickets_of_economy_class; // Билеты эконом
	int price_of_economy_class; // Цена эконом класса
};
struct Date
{
	int day;
	int month;
	int year;
	string fix_day;
};
struct Time
{
	int hour;
	int minute;
	int second;
};

Date getCurrentDate();
Time getCurrentTime();
void showDate(Date date);
void showTime(Time time);

void readFileOfFlight(Flight* arr_of_flight, int number_of_flight);
void ShowArrOfFlight(Flight* arr_of_flight, int number_of_flight);
void createFlight(Flight* arr_of_flight, int number_of_flight);
void adminMenu(int selection_menu_of_administrator, int menu_of_editing, int menu_of_accounts, Flight* arr_of_flight, int number_of_flight);
void LoginAccount(Users* arr_of_users, string input_login, string input_password);
void InputLogin(int number_of_users, Users* arr_of_users, string input_login);
int LoginUniquenessCheck(Users* arr_of_users, int number_of_users, string input_login);
void PasswordSecure(Users* arr_of_users, unsigned char p);
void WriteEndFileUsers(Users* arr_of_users, int number_of_users, Flight* arr_of_flight, int number_of_flight);
void UserRegistration(int number_of_users, Users* arr_of_users, string input_login, Flight* arr_of_flight, int number_of_flight);
void Menu(int number_of_users, Users* arr_of_users, Flight* arr_of_flight, int number_of_flight);

int selection_menu_of_administrator;
int menu_of_editing;
int menu_of_accounts;
unsigned char p;
string input_password;
string input_login;

const string FILE_OF_FLIGHT = "flight.txt";
const string FILE_OF_USERS = "users.txt"; //Путь к файлу
const int RESERVE_SIZE = 100; //Максимальное количество элементов массива

void adminMenu(int selection_menu_of_administrator, int menu_of_editing, int menu_of_accounts, Flight* arr_of_flight, int number_of_flight) {
	cout << "1. Редактирование рейсов" << endl;
	cout << "2. Редактирование учетных записей" << endl;
	cout << "3. Просмотр рейсов" << endl;
	cout << "4. Просмотр учетных записей" << endl;
	cout << "<---------------------------->" << endl;
	cout << "Выбор: ";
	cin >> selection_menu_of_administrator;
	switch (selection_menu_of_administrator)
	{
	case 1:
		cout << "1. Cоздать рейс" << endl;
		cout << "2. Редактировать рейс" << endl;
		cout << "<---------------------------->" << endl;
		cout << "Выбор: ";
		cin >> menu_of_editing;
		switch (menu_of_editing)
		{
		case 1:
			createFlight(arr_of_flight, number_of_flight);
			//Функция создания рейсов
		case 2:
			//Функция редактирования рейсов
		default:
			break;
		}
		break;
	case 2:
		cout << "1. Добавление учетных записей пользователей" << endl;
		cout << "2. Блокировка учетных записей пользователей" << endl;
		cout << "3. Подтверждение новых учетных записей пользователей" << endl;
		cout << "0. Вернуться назад" << endl;
		cout << "Выбор: " << endl;
		cin >> menu_of_accounts;
		switch (menu_of_accounts)
		{
		case 0: //Функция запуска меню администратора
		case 1: //Функция редактирования 
		case 2: //Функция блокировки (удвления)
		case 3: //Функция подтверждения записей


		default:
			cout << "Введите цифру от 0 до 3";
			// рекурсия
			break;
		}
		break;
	case 3:
		ShowArrOfFlight(arr_of_flight, number_of_flight);
	case 4:

	default:
		break;
	}

}

void Menu(int number_of_users, Users* arr_of_users, Flight* arr_of_flight, int number_of_flight) {
	int selection_menu;
	cout << "<----------- Главное меню ----------->" << endl;
	cout << "1. Вход" << endl;
	cout << "2. Регистрация" << endl;
	cout << "3. Admin (test)" << endl;
	cout << "<---------------------------->" << endl;
	cout << "Выбор: ";
	cin >> selection_menu;
	switch (selection_menu)
	{
	case 1:
		LoginAccount(arr_of_users, input_login, input_password);
		break;
	case 2:                            
		UserRegistration(number_of_users, arr_of_users, input_login, arr_of_flight, number_of_flight);
		break;
	case 3:
		adminMenu(selection_menu_of_administrator, menu_of_editing, menu_of_accounts, arr_of_flight, number_of_flight);
		break;

	default:
		cout << "" << endl;
		cout << "Неверный ввод!" << endl;
		cout << "Введите цифру от 1 до 3" << endl;
		Menu(number_of_users, arr_of_users, arr_of_flight, number_of_flight);
		break;
	}
}

void ShowArrOfFlight(Flight* arr_of_flight, int number_of_flight) {
	readFileOfFlight(arr_of_flight, number_of_flight);
	cout << "<----Расписание рейсов---->" << endl;
	cout << endl;
	cout << "| Номер рейса | Тип самолета | Пункт назначения | Дата вылета |  Время вылета | Время полета | Общее количество билетов |  Бизнес класс | Цена | Эконом класс | Цена |\n";
	for (int i = 0; i < RESERVE_SIZE; i++)
	{
		cout << "| " << arr_of_flight[i].flight_number << " | " << arr_of_flight[i].type_of_plane << " | ";
		/*	arr_of_flight[i].destrination << "\t|\t" << arr_of_flight[i].destrination_date_day << "." <<
			arr_of_flight[i].destrination_date_month << "\t|\t" << arr_of_flight[i].вeparture_time_hour << ":" <<
			arr_of_flight[i].flight_time << "\t|\t" << arr_of_flight[i].aircraft_capacity << "\t|\t" <<
			arr_of_flight[i].tickets_of_business_class << "\t|\t" << arr_of_flight[i].price_of_business_class << "\t|\t" <<
			arr_of_flight[i].tickets_of_economy_class << "\t|\t" << arr_of_flight[i].price_of_economy_class << "\t|\n";
		*/
		break;
	}

}

void readFileOfFlight(Flight* arr_of_flight, int number_of_flight) {
	ifstream fin(FILE_OF_FLIGHT, ios::in); // Открыли файл для чтения
	if (!fin.is_open()) cout << "Указанный файл не существует!" << endl;
	else
	{
		int i = 0;
		while (!fin.eof())
		{
			if (i < RESERVE_SIZE)
			{
				fin >> arr_of_flight[i].flight_number
					>> arr_of_flight[i].type_of_plane
					>> arr_of_flight[i].destrination
					>> arr_of_flight[i].destrination_date_day
					>> arr_of_flight[i].destrination_date_month
					>> arr_of_flight[i].вeparture_time_hour
					>> arr_of_flight[i].flight_time
					>> arr_of_flight[i].aircraft_capacity
					>> arr_of_flight[i].tickets_of_business_class
					>> arr_of_flight[i].price_of_business_class
					>> arr_of_flight[i].tickets_of_economy_class
					>> arr_of_flight[i].price_of_economy_class;

				i++;
			}
			else
			{
				cout << "Недостаточно памяти для чтения всех данных!" << endl;
				break;
			}
		}
		number_of_flight = i;
	}
	fin.close(); //Закрыли файл

}

void createFlight(Flight* arr_of_flight, int number_of_flight) {
	//ввод данных
	cout << "Номер рейса: ";
	cin >> arr_of_flight[number_of_flight - 1].flight_number;
	cout << "Тип самолета: ";
	cin >> arr_of_flight[number_of_flight - 1].type_of_plane;
	cout << "Пункт назначения: ";
	cin >> arr_of_flight[number_of_flight - 1].destrination;
	cout << "День вылета: ";
	cin >> arr_of_flight[number_of_flight - 1].destrination_date_day;
	cout << "Месяц вылета: ";
	cin >> arr_of_flight[number_of_flight - 1].destrination_date_month;
	cout << "Время полета:  ";
	cin >> arr_of_flight[number_of_flight - 1].flight_time;         //Функция работы со временем и вычислением
	cout << "Количество мест: ";
	cin >> arr_of_flight[number_of_flight - 1].aircraft_capacity;
	cout << "Количество билетов бизнес класса: ";
	cin >> arr_of_flight[number_of_flight - 1].tickets_of_business_class;
	cout << "Стоимость билета бизнес класса: ";
	cin >> arr_of_flight[number_of_flight - 1].price_of_business_class;
	cout << "Количество билетов эконом класса: ";
	cin >> arr_of_flight[number_of_flight - 1].tickets_of_economy_class;
	cout << "Стоимость билета эконом класса: ";
	cin >> arr_of_flight[number_of_flight - 1].price_of_economy_class;


	ofstream fout(FILE_OF_FLIGHT, ios::app);
	if (fout.is_open()) {                            // все поменять
		for (int i = 0; i < RESERVE_SIZE; i++)
		{
			fout << arr_of_flight[i].flight_number << " "
				<< arr_of_flight[i].type_of_plane << " "
				<< arr_of_flight[i].destrination << " "
				<< arr_of_flight[i].destrination_date_day << " "
				<< arr_of_flight[i].destrination_date_month << " "
				<< arr_of_flight[i].flight_time << " "
				<< arr_of_flight[i].aircraft_capacity << " "
				<< arr_of_flight[i].tickets_of_business_class << " "
				<< arr_of_flight[i].price_of_business_class << " "
				<< arr_of_flight[i].tickets_of_economy_class << " "
				<< arr_of_flight[i].price_of_economy_class << endl;
			fout << endl;
			break;
		}

		fout.close();
		cout << "Рейс добавлен" << endl;

	}
	else {
		cout << "<-----Не удалось открыть файл------>" << endl;
		// возврат в меню

	}
}

void WriteEndFileUsers(Users* arr_of_users, int number_of_users, Flight* arr_of_flight, int number_of_flight) {
	ofstream fout(FILE_OF_USERS, ios::app); // Открыли файл для записи
	if (fout.is_open()) {
		for (int i = 0; i < number_of_users; i++)
		{
			fout << arr_of_users[i].login << " "
				<< arr_of_users[i].password << endl;
			if (i < number_of_users - 1)
			{
				fout << endl;
			}
		}
		fout.close();
		cout << "Пользователь добавлен" << endl;
	}
	else
	{
		cout << "<-----Не удалось открыть файл------>" << endl;
		Menu(number_of_users, arr_of_users, arr_of_flight, number_of_flight);
	}
}

void UserRegistration(int number_of_users, Users* arr_of_users, string input_login, Flight* arr_of_flight, int number_of_flight) {

	if (number_of_users + 1 <= RESERVE_SIZE) {
		number_of_users++;
		InputLogin(number_of_users, arr_of_users, input_login);
		PasswordSecure(arr_of_users, p);
		WriteEndFileUsers(arr_of_users, number_of_users, arr_of_flight, number_of_flight);
	}
	else
	{
		cout << "Недостаточно памяти для добавления нового пользователя" << endl;
	}
}

void InputLogin(int number_of_users, Users* arr_of_users, string input_login) { // ПОМЕНЯТЬ

	cout << "<-------Регистрация нового пользователя------>" << endl;
	cout << "Логин: ";
	cin >> input_login;
	LoginUniquenessCheck(arr_of_users, number_of_users, input_login); //проверка уникальность логина
}

void PasswordSecure(Users* arr_of_users, unsigned char p) {
	cout << "Пароль: ";
	do
	{
		p = _getch();
		if (p == 13) break;
		if (p == '\b' && !arr_of_users->password.empty())
		{
			cout << '\b';
			cout << ' ';
			cout << '\b';
			arr_of_users->password.pop_back();
			continue;
		}
		if (isalnum((unsigned char)p))
		{
			cout << '*';
			arr_of_users->password.push_back(p);
		}
	} while (true);
	cout << "" << endl;
}

int LoginUniquenessCheck(Users* arr_of_users, int number_of_users, string input_login) { /// input login изменить, функция не работает

	ifstream fin(FILE_OF_USERS, ios::in); // Открыли файл для чтения
	if (fin.is_open()) {


		for (int i = 0; i < RESERVE_SIZE; i++) {

			fin >> arr_of_users[i].login;


			if (input_login == arr_of_users[i].login) {

				cout << "<-----Логин уже занят другим пользователем------>" << endl;
				cout << "придумайте другой логин" << endl;
				return 0;
				fin.close();
				LoginUniquenessCheck(arr_of_users, number_of_users, input_login);

			}
		}
	}
	else
	{
		cout << "Не удалось открыть файл" << endl;

	}
	arr_of_users[number_of_users - 1].login = input_login;
}

void LoginAccount(Users* arr_of_users, string input_login, string input_password) {

	cout << "<-------Вход в аккаунт пользователя------>" << endl;
	cout << "Логин: ";
	cin >> input_login;
	ifstream fin(FILE_OF_USERS, ios::in); // Открыли файл для чтения
	if (fin.is_open()) {


		for (int i = 1; i < RESERVE_SIZE; i++) {

			fin >> arr_of_users[i].login;


			if (input_login == arr_of_users[i].login) {
				cout << "Пароль: ";
				cin >> input_password;
				for (int i = 1; i < RESERVE_SIZE; i++) {

					fin >> arr_of_users[i].password;
					if (input_password == arr_of_users[i].password) {
						cout << "Вход выполнен" << endl;
						break;
					}
					else
					{
						cout << "Неправельно введён пароль!" << endl;
						cout << "Повторите попытку ввода!" << endl;
						cout << endl;
						LoginAccount(arr_of_users, input_login, input_password);		/// STOP

					}
				}
			}
		}
	}
	else
	{
		cout << "Не удалось открыть файл с учетными запясями" << endl;

	}
	cout << "Пользователя с таким логином не существует" << endl;
}

Date getCurrentDate()
{
	using namespace std;
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);
	Date currentDate;
	currentDate.day = localtime.tm_mday;
	currentDate.month = 1 + localtime.tm_mon; // tm_mon: months in range [0-11]
	currentDate.year = 1900 + localtime.tm_year; // tm_year: years since 1900
	return currentDate;
}
Time getCurrentTime()
{
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);
	Time currentTime;
	currentTime.hour = localtime.tm_hour;
	currentTime.minute = localtime.tm_min;
	currentTime.second = localtime.tm_sec;

	return currentTime;
}
void showDate(Date date)
{
	string fix_day;
	string fix_month;
	if (date.day < 10) {
		fix_day = "0"+to_string(date.day);
	}
	else {
		fix_day = to_string(date.day);
	}
	 if  (date.month < 10) {
		fix_month = "0" + to_string(date.month);
	}
	else {
		 fix_month = to_string(date.month);
	}
	cout << "Дата           Время" << endl;
	cout << fix_day << "." << fix_month << "." << date.year << "      ";
}
void showTime(Time time)
{

	cout << time.hour << ":" << time.minute << ":" << time.second << endl;
	cout << endl;
}

int main() {
	setlocale(0, "");
	Users arr_of_users[RESERVE_SIZE];
	Flight arr_of_flight[100];
	int number_of_users = 1;
	int number_of_flight = 1;
	showDate(getCurrentDate());
	showTime(getCurrentTime());
	Menu(number_of_users, arr_of_users, arr_of_flight, number_of_flight);
	return 0;
}
