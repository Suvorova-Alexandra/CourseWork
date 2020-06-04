#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <iostream>
#include <WinSock2.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <conio.h> 
#include <map>
#include <limits>
#include <stdio.h>
#include <locale.h>
#include <iterator>
#include <iomanip>
#include <exception>
#include <iomanip>
#include <winsock.h>
#include <winsock.h>
using namespace std;
void term_func() {
	cout << "Вызвана собственная функция завершения.\n";
	exit(-1);
}
class SClient
{
public:
	SClient();
	~SClient();
	SOCKET start();
	void handle();
	int sending(int x, SOCKET& s) {
		char buf[255];
		try {
			if (sizeof(x) > 255)
				throw length_error("Размер строки превышен!");
			else {
				itoa(x, buf, 10);
				send(s, buf, sizeof(buf), 0);
			}
		}
		catch (length_error & e) {
			cout << e.what() << endl;
			term_func();
		}
		return x;
	}
	int answer(int& x, SOCKET s) {
		char buf[255];
		if (recv(s, buf, sizeof(buf), 0) != 0) {
			x = atoi(buf);
		}
		return x;
	}
	int answString(string& str, SOCKET s) {
		char buf[255];
		if (recv(s, buf, sizeof(buf), 0) != 0) {

			str = buf;
		}

		return 0;
	}
	int sendString(string& str, SOCKET& s) {
		char buf[255];
		try {
			if (str.size() > 255)
				throw length_error("Размер строки превышен!");
			else {
				strcpy(buf, str.c_str());
				send(s, buf, sizeof(buf), 0);
			}
		}
		catch (length_error & e) {
			cout << e.what() << endl;
			term_func();
		}
		return 0;
	}
	int sendFloat(float x, SOCKET s) {
		char buf[255];
		int ret = snprintf(buf, sizeof buf, "%f", x);
		send(s, buf, sizeof(buf), 0);
		return 0;
	}
	int answFloat(float& x, SOCKET s) {
		char buf[255];
		if (recv(s, buf, sizeof(buf), 0) != 0) {
			x = atof(buf);
		}
		return 0;
	}

	SOCKET s;
	sockaddr_in dest_addr;
	WSAData wData;
};

class study {
	string target;
	int amount;
	float price;
	tm time;
public:
	int addInfo(SOCKET& s) {
		char buf[255];
		cin.ignore();
		cout << "Введите цель: " << endl;
		getline(cin, target);
		strcpy(buf, target.c_str());
		send(s, buf, sizeof(buf), 0);
		while (true) {
			cin.unsetf(ios::skipws);
			cout << "Введите количество продукта: " << endl;
			cin >> amount;
			if (amount < 1) {
				cout << " Не может быть отрицательное число!" << endl;
				cin.clear(ios::failbit);
			}
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Неправильный ввод данных\n";

		}

		itoa(amount, buf, 10);
		send(s, buf, sizeof(buf), 0);
		while (true) {
			cin.unsetf(ios::skipws);
			cout << "Введите цену: " << endl;
			cin >> price;
			if (price < 0.0) {
				cout << " Не может быть отрицательное число!" << endl;
				cin.clear(ios::failbit);
			}
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}

			cin.clear();
			cin.ignore(10, '\n');
			cout << "Неправильный ввод данных\n";

		}
		snprintf(buf, sizeof(buf), "%f", price);
		send(s, buf, sizeof(buf), 0);
		return 0;
	}
	int sendInfo(SOCKET& s) {
		char buf[255];
		itoa(amount, buf, 10);
		send(s, buf, sizeof(buf), 0);

		snprintf(buf, sizeof buf, "%f", price);
		send(s, buf, sizeof(buf), 0);

		strcpy(buf, target.c_str());
		send(s, buf, sizeof(buf), 0);

		itoa(time.tm_year, buf, 10);
		send(s, buf, sizeof(buf), 0);

		itoa(time.tm_mon, buf, 10);
		send(s, buf, sizeof(buf), 0);

		itoa(time.tm_mday, buf, 10);
		send(s, buf, sizeof(buf), 0);
		return 0;
	}
	int receiveInfo(SOCKET& s) {
		char buf[255];
		if (recv(s, buf, sizeof(buf), 0) != 0) {
			amount = atoi(buf);
		}
		if (recv(s, buf, sizeof(buf), 0) != 0) {
			price = atof(buf);
		}
		if (recv(s, buf, sizeof(buf), 0) != 0) {
			target = buf;
		}
		if (recv(s, buf, sizeof(buf), 0) != 0) {
			time.tm_year = atoi(buf);
		}
		if (recv(s, buf, sizeof(buf), 0) != 0) {
			time.tm_mon = atoi(buf);
		};
		if (recv(s, buf, sizeof(buf), 0) != 0) {
			time.tm_mday = atoi(buf);
		}
		return 0;
	}
	string getTarget() {
		return target;
	}
	int getAmount() {
		return amount;
	}
	float getPrice() {
		return price;
	}
	int getYear() { return time.tm_year; }
	int getMonth() { return time.tm_mon; }
	int getDay() { return time.tm_mday; }
	friend ostream& operator<<(ostream& stream, study& obj);
	friend istream& operator>>(istream& stream, study& obj);
};
ostream& operator<<(ostream& stream, study& obj) {
	stream << obj.target << '.' << obj.amount << "." << obj.price << "." << obj.time.tm_year << "/" << obj.time.tm_mon << "/" << obj.time.tm_mday << "\n";
	return stream;
}
istream& operator>>(istream& stream, study& obj) {
	char str[255];
	stream.getline(str, 255, '.');
	obj.target = str;
	stream.getline(str, 255, '.');
	obj.amount = atoi(str);
	stream.getline(str, 255, '.');
	obj.price = atof(str);
	stream.getline(str, 255, '/');
	obj.time.tm_year = atoi(str);
	stream.getline(str, 255, '/');
	obj.time.tm_mon = atoi(str);
	stream.getline(str, 255, '\n');
	obj.time.tm_mday = atoi(str);
	return stream;
}
class hennery
{
	SClient client;
	int scale;
	int numTargets;
	string study_name;
	int size;
	study* obj_study;
	vector<int> marks;
public:
	void addTarget(SOCKET& s);
	int receive_target(SOCKET& s);
	int show_targets(SOCKET& s);
	void delete_target(SOCKET& s);
	int edit_target(SOCKET& s);
	void addMark(SOCKET& s);
	int show_my_marks(SOCKET& s);
	int edit_user_marks(SOCKET& s);
	int show_marks(SOCKET& s);
	void delete_user_marks(SOCKET& s);
	int meth(SOCKET& s);
	int addOrder(SOCKET& s);
	int showOrders(SOCKET& s);
};

