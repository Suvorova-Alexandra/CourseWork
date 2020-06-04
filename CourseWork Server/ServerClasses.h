#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <iostream>
#include <WinSock2.h>
#include <string>
#include <sstream>
#include <exception>
#include <fstream>
#include <vector>
#include <conio.h> 
#include <map>
#include <limits>
#include <stdio.h>
#include <locale.h>
#include <iterator>
#include <iomanip>
#include <time.h>
#include <winsock.h>
#include <winsock.h>
using namespace std;
int main();
fstream file1, file2;
class ArrayException : public std::exception
{
private:
	string m_error;

public:
	ArrayException(string error) : m_error(error) {}
	const char* what() const noexcept { return m_error.c_str(); }
};
void term_func() {
	cout << "term_func() was called by terminate().\n";
	exit(-1);
}
class SServer
{
public:

	SServer() {};
	~SServer() {};

	void startServer() {
		if (WSAStartup(MAKEWORD(2, 2), &wData) != 0)
		{
			printf("WSA Startup succes\n");
			return;
		}
		s = socket(AF_INET, SOCK_STREAM, NULL);
		sockaddr_in local_addr;//
		local_addr.sin_family = AF_INET;//
		local_addr.sin_port = htons(1280);//
		local_addr.sin_addr.s_addr = 0;//

		if (s == SOCKET_ERROR) {
			printf("Socket not created\n");
			return;
		}

		if (bind(s, (struct sockaddr*) & local_addr, sizeof(local_addr)) != SOCKET_ERROR) {
			printf("Сокет успешно создан!\n");
		}

		if (listen(s, SOMAXCONN) != SOCKET_ERROR) {
			printf("Прием клиентов по порту %u\n", ntohs(local_addr.sin_port));
		}
	}
	void closeServer() {
		closesocket(s);
		WSACleanup();
		cout << "Server was stoped. You can close app" << endl;
	}
	void handle() {
		while (true)
		{
			SOCKET s2;
			SOCKADDR_IN addr_c;
			int addrlen = sizeof(addr_c);
			if ((s2 = accept(s, (struct sockaddr*) & addr_c, &addrlen)) != 0) {
				printf("sended Client connected from 0 %u.%u.%u.%u:%u\n",
					(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b1,
					(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b2,
					(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b3,
					(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b4,
					ntohs(addr_c.sin_port));
				char buf[100], buf1[100], s;


			}
			Sleep(50);
		}
	}
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
			return 0;
		}
		return x;
	}
	int answer(int& x, SOCKET& s) {
		char buf[255];
		try {
			if (recv(s, buf, sizeof(buf), 0)) {
				x = atoi(buf);
			}
			else throw length_error("Размер строки превышен!");
		}
		catch (length_error & e) {
			cout << e.what() << endl;

		}
		return x;
	}
	int answString(string& str, SOCKET& s) {
		char buf[255];
		try {
			if (recv(s, buf, sizeof(buf), 0)) {
				str = buf;
			}
			else throw length_error("Размер строки превышен!");
		}
		catch (length_error & e) {
			cout << e.what() << endl;
			return 0;
		}
		return 0;
	}
	int sendString(string& str, SOCKET& s) {
		char buf[255];
		try {
			if (sizeof(str) > 255)
				throw length_error("Размер строки превышен!");
			else {
				strcpy(buf, str.c_str());
				cout << buf << endl;
				send(s, buf, sizeof(buf), 0);
			}
		}
		catch (length_error & e) {
			cout << e.what() << endl;
			term_func();
		}
		return 0;
	}
	int sendFloat(float x, SOCKET& s) {
		char buf[255];
		int ret = snprintf(buf, sizeof(buf), "%f", x);
		send(s, buf, sizeof(buf), 0);
		return 0;
	}
	int answFloat(float& x, SOCKET& s) {
		char buf[255];
		if (recv(s, buf, sizeof(buf), 0)) {
			x = atof(buf);
		}
		return 0;
	}
	unsigned short port;
	SOCKET s;
	WSAData wData;
};
void getTime(tm& newtime)
{
	time_t now = time(0);
	localtime_s(&newtime, &now);
	newtime.tm_mon = 1 + newtime.tm_mon;
	newtime.tm_year = 1900 + newtime.tm_year;
}
string receive(SOCKET& s)
{
	char buf[255];
	int result = 0;
	result = (recv(s, buf, sizeof(buf), 0));
	if (result < 0)
	{
		cout << "Соединение с клиентом было остановлено." << endl;
		closesocket(s);
		main();
	}
	else
		buf[strlen(buf)] = '\0';
	return buf;
}
class study {
	string target;
	int amount;
	float price;
	tm time;
public:
	int addInfo(SOCKET& s) {
		char buf[255];
		target = receive(s);
		amount = atoi(receive(s).c_str());
		price = atof(receive(s).c_str());
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
	string getTarget() {
		return target;
	}
	int getAmount(int& x) {
		amount = x;
		return amount;
	}
	float getPrice(float& x) {
		price = x;
		return price;
	}
	int getKolvo() {
		return amount;
	}
	float getPr() {
		return price;
	}
	friend ostream& operator<<(ostream& stream, study& obj);
	friend istream& operator>>(istream& stream, study& obj);
};
ostream& operator<<(ostream& stream, study& obj) {
	getTime(obj.time);
	stream << obj.target << '*' << obj.amount << "*" << obj.price << "*" << obj.time.tm_year << "/" << obj.time.tm_mon << "/" << obj.time.tm_mday << ".";
	return stream;
}
istream& operator>>(istream& stream, study& obj) {
	char str[255];
	stream.getline(str, 255, '*');
	obj.target = str;
	stream.getline(str, 255, '*');
	obj.amount = atoi(str);
	stream >> obj.price;
	stream.getline(str, 255, '*');
	stream.getline(str, 255, '/');
	obj.time.tm_year = atoi(str);
	stream.getline(str, 255, '/');
	obj.time.tm_mon = atoi(str);
	stream.getline(str, 255, '.');
	obj.time.tm_mday = atoi(str);
	return stream;
}

template<typename T>
class container {
	T* marks;
	int kolvo;
public:
	class Iterator;
	container(int n = 0) :kolvo(n) {}

	T operator [](int index)
	{
		if (index < 0 || kolvo < index) throw "Нарушены пределы контейнера!";
		return this->marks[index];
	}
	int size()
	{
		return this->kolvo;
	}
	void push_back(T data)
	{
		try {
			T* _result = new T[this->kolvo++];
			if (this->kolvo > 0) {
				for (int index = 0; index < this->kolvo; index++)
				{
					if (index != this->kolvo - 1)
					{
						_result[index] = this->marks[index];
					}
					else
					{
						_result[index] = data;
						break;
					}
				}
				this->marks = _result;
			}
			else throw ArrayException("Размер контейнера - отрицательное число!");
		}
		catch (ArrayException & exception) {
			std::cerr << "Возникла ошибка в контейнере(" << exception.what() << ")\n";
			term_func();
		}
	}

	void clear() { delete[] marks; }
	Iterator begin() { return marks; }
	Iterator end() { return marks + kolvo; }
	friend ostream& operator<<(ostream& s, const container<T>& n)
	{
		s << container<T>::marks[n];
		return s;
	}
	class Iterator {
		T* obj;
	public:
		Iterator(T* first) :obj(first) {}
		T& operator+(int n) { return *(obj + n); }
		T& operator-(int n) { return *(obj - n); }
		T& operator++() { return *++obj; }
		T& operator--() { return *--obj; }
		T& operator++(int) { return *obj++; }
		T& operator--(int) { return *obj--; }
		bool operator!=(const Iterator& it) { return obj != it.obj; }
		bool operator==(const Iterator& it) { return obj == it.obj; }
		T& operator*() { return *obj; }
	};
};
class hennery
{
protected:
	int scale;
	int numTargets;
	study* obj_study = new study;
	string study_name;

public:
	int addTarget(SOCKET& s);
	int writeTarget();
	int readTarget(SOCKET& s, multimap<int, hennery>& note);
	int readTarget(multimap<int, hennery>& note);
	int getNumtargets() {
		return numTargets;
	}
	int getScale() {
		return scale;
	}
	study* getObj() {
		return obj_study;
	}
	int send_target(SOCKET& s);
	int edit_target(SOCKET& s);
	int menu_edit_target(SOCKET& s, int size);
	friend ostream& operator<<(ostream& stream, hennery& obj);
	friend istream& operator>>(istream& stream, hennery& obj);
};

class hennery_production :public hennery {
	int size;
	container<int> marks;
	char login[255];
public:
	int addMark(SOCKET& s);
	int writeMarks(multimap<int, hennery_production>& expert);
	int readMarks(multimap<int, hennery_production>& note);
	container<int>& getMarks() {
		return marks;
	}
	char* getLogin() {
		return login;
	}
	int receive_marks(SOCKET& s, int siz) {
		char buf[255];
		marks.clear();
		size = siz;
		for (int i = 0; i < siz; i++) {
			marks.push_back(atoi(receive(s).c_str()));
		}
		return 0;
	}
	int send_marks(SOCKET& s, vector<int> vect, int size) {
		char buf[255];
		for (int i = 0; i < size; i++) {
			vect.push_back(atoi(buf));
		}
		return 0;
	}
	friend ostream& operator<<(ostream& stream, hennery_production& obj);
	friend istream& operator>>(istream& stream, hennery_production& obj);
};

class expert_method {

	hennery* data = new hennery;
	hennery_production* adept = new hennery_production;
public:
	SServer serv;
	int show_table(SOCKET& s);
	void delete_target(SOCKET& s);
	int search_marks(SOCKET& s, int key);
	int show_user_marks(SOCKET& s, multimap<int, hennery>& mp, multimap<int, hennery_production>& expert);
	int show_user_marks(SOCKET& s);
	int  edit_user_marks(SOCKET& s);
	int delete_user_marks(SOCKET& s);
	int meth(SOCKET& s, multimap<int, int>& task);
	int addOrder(SOCKET& s, multimap<int, int>& task);
	int writeMeth(multimap<int, int>& task);
	int readOrder(SOCKET& s, multimap<int, int>& task);
	int showOrders(SOCKET& s, multimap<int, int>& task);
};
