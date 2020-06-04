#include "ClientClasses.h"

char volk[255];
template<class T>
class entrance
{
	T pass[255];
	T login[255];

public:

	friend class userData;
	static char* crypt(T pass[255]);
	static int openuser();
	static int deleteuser()
	{
		FILE* fp;
		entrance* mas, temp;
		char check;
		int k = 0, zapis = 0;

		fopen_s(&fp, "loginuser.txt", "r");
		if (fp != NULL)
		{
			if (fscanf_s(fp, "%c", &check, 1) != EOF)
			{
				fseek(fp, -1, SEEK_CUR);
				while (!feof(fp))
				{
					fscanf_s(fp, "%s", temp.login, sizeof(temp.login));
					fscanf_s(fp, "%s\n", temp.pass, sizeof(temp.pass));
					++k;
				}
				rewind(fp);
				mas = new entrance[k];
				for (int i = 0; i < k; i++)
				{
					fscanf_s(fp, "%s", mas[i].login, sizeof(mas[i].login));
					fscanf_s(fp, "%s\n", mas[i].pass, sizeof(mas[i].pass));
				}
				fclose(fp);
				cin.ignore(10, '\n');

				while (true) {
					cin.unsetf(ios::skipws);
					cout << "Введите номер записи для удаления: " << endl;
					cin >> zapis;
					if (cin.good()) {
						cin.ignore(10, '\n');
						break;
					}
					cin.clear();
					cin.ignore(10, '\n');
					cout << "Неправильный ввод данных!(Введены символы)\n";
				};
				if (zapis < 1 || zapis > k)
				{
					return 1;
				}
				fopen_s(&fp, "loginuser.txt", "w");
				for (int i = 0; i < k; i++)
				{
					if (i + 1 == zapis) continue;
					fprintf(fp, "%s %s\n", mas[i].login, mas[i].pass);
				}
				rewind(fp);
				delete[] mas;
				fclose(fp);
				system("pause");
				return 0;
			}
			else
			{
				system("pause");
				fclose(fp);
				return 1;
			}
		}
		else { cout << "error of opening!" << endl; }
	}
	static int adduser()
	{
		FILE* fp;
		entrance temp;
		int k = 0, i = 0, j = 0, size = 0;
		cout << "Введите логин:\n";
		scanf_s("%s", temp.login, 255);
		_getch();
		printf_s("Введите пароль:\n");
		while (1)
		{
			temp.pass[i] = _getch();
			if (temp.pass[i] == '\r') break;
			if (temp.pass[i] == '\b')
			{
				printf("%s", "\b \b");
				--i;
			}
			else
			{
				printf("%c", '*');
				++i;
			}
		}
		temp.pass[i] = '\0';
		printf("\n");
		if (i - 1 < 1)
		{
			_getch();
			return 1;
		}
		strcpy_s(temp.pass, crypt(temp.pass));
		fopen_s(&fp, "loginuser.txt", "a");
		fprintf(fp, "%s %s\n", temp.login, temp.pass);
		fclose(fp);

		_getch();
		return 0;
	}
	static int loginadmin()
	{
		errno_t err;
		FILE* fr;
		entrance temp;
		char log[255], pass[255];
		int k = 0, i = 0;

		printf("Введите логин:\n");
		scanf_s("%s", log, 255);
		getchar();
		printf_s("Введите пароль от двух символов:\n");
		while (1)
		{
			pass[i] = _getch();
			if (pass[i] == '\r') break;
			if (pass[i] == '\b')
			{
				printf("%s", "\b \b");
				--i;
			}
			else
			{
				printf("%c", '*');
				++i;
			}
		}
		pass[i] = '\0';
		printf("\n");
		if (i - 1 < 1)
		{
			return 1;
		}

		strcpy_s(pass, crypt(pass));
		err = fopen_s(&fr, "loginadmin.txt", "r");
		if (fr != NULL)
		{
			while (!feof(fr))
			{
				fscanf_s(fr, "%s\n", temp.login, sizeof(temp.login));
				fscanf_s(fr, "%s\n", temp.pass, sizeof(temp.pass));
				if (strcmp(log, temp.login) == 0 && strcmp(pass, temp.pass) == 0)
				{
					fclose(fr);
					return 0;
				}
			}
			fclose(fr);
			return 1;

		}

	}
	int loginuser()
	{
		errno_t err;
		FILE* fp;
		entrance temp;
		char log[255], pass[255];
		int k = 0, i = 0;

		printf("Введите логин:\n");
		scanf_s("%s", log, 255);

		printf_s("Введите пароль от двух символов:\n");
		while (1)
		{
			pass[i] = _getch();
			if (pass[i] == '\r') break;
			if (pass[i] == '\b')
			{
				printf("%s", "\b \b");
				--i;
			}
			else
			{
				printf("%c", '*');
				++i;
			}
		}
		pass[i] = '\0';
		printf("\n");
		if (i - 1 < 1)
		{
			return 1;
		}
		strcpy_s(pass, crypt(pass));
		err = fopen_s(&fp, "loginuser.txt", "r");
		while (!feof(fp))
		{
			fscanf_s(fp, "%s\n", temp.login, sizeof(temp.login));
			fscanf_s(fp, "%s\n", temp.pass, sizeof(temp.pass));
			if (strcmp(log, temp.login) == 0 && strcmp(pass, temp.pass) == 0)
			{
				fclose(fp);
				strcpy(volk, log);
				//cout << "LOJFJKVF" << volk << endl;
				return 0;
			}
		}

		fclose(fp);
		return 1;
	}
	static int addadmin()
	{
		FILE* fp;
		entrance temp;
		int k = 0, i = 0, j = 0, size = 0;
		cout << "Введите логин:\n";
		scanf_s("%s", temp.login, 255);
		_getch();
		printf_s("Введите пароль:\n");
		while (1)
		{
			temp.pass[i] = _getch();
			if (temp.pass[i] == '\r') break;
			if (temp.pass[i] == '\b')
			{
				printf("%s", "\b \b");
				--i;
			}
			else
			{
				printf("%c", '*');
				++i;
			}
		}
		temp.pass[i] = '\0';
		printf("\n");
		if (i - 1 < 1)
		{
			_getch();
			return 1;
		}
		strcpy_s(temp.pass, crypt(temp.pass));
		fopen_s(&fp, "loginadmin.txt", "a");
		fprintf(fp, "%s %s\n", temp.login, temp.pass);
		fclose(fp);

		_getch();
		return 0;
	}
	int registerUser() {
		FILE* fp;
		entrance temp;
		int k = 0, i = 0, j = 0, size = 0;
		cout << "Для регистрации ввдите следующие данные:\n" << endl;
		cout << "Введите логин:\n";
		scanf_s("%s", temp.login, 255);
		_getch();
		printf_s("Введите пароль:\n");
		while (1)
		{
			temp.pass[i] = _getch();
			if (temp.pass[i] == '\r') break;
			if (temp.pass[i] == '\b')
			{
				printf("%s", "\b \b");
				--i;
			}
			else
			{
				printf("%c", '*');
				++i;
			}
		}
		temp.pass[i] = '\0';
		printf("\n");
		if (i - 1 < 1)
		{
			_getch();
			return 1;
		}
		strcpy_s(temp.pass, crypt(temp.pass));
		fopen_s(&fp, "loginuser.txt", "a");
		fprintf(fp, "%s %s\n", temp.login, temp.pass);
		fclose(fp);

		_getch();
		return 0;
	}
};
template<class T>
char* entrance<T>::crypt(T pass[255]) {
	char temp;

	if (strlen(pass) % 2 == 0)
	{
		for (int i = 0; i < strlen(pass); i = i + 2)
		{
			temp = pass[i];
			pass[i] = pass[i + 1] + 2;
			pass[i + 1] = temp + 2;
		}
	}
	else
	{
		for (int i = 0; i < strlen(pass); i = i + 2)
		{
			if (i + 1 == strlen(pass)) break;
			temp = pass[i];
			pass[i] = pass[i + 1] + 2;
			pass[i + 1] = temp + 2;
		}
	}
	return pass;
}
template<class T>
int entrance<T>::openuser() {
	FILE* fp;
	entrance temp, * mas;
	char check;
	int k = 0;

	fopen_s(&fp, "loginuser.txt", "r");
	if (fp != NULL)
	{
		if (fscanf_s(fp, "%c", &check, 1) != EOF)
		{
			fseek(fp, -1, SEEK_CUR);
			while (!feof(fp))
			{
				fscanf_s(fp, "%s", temp.login, sizeof(temp.login));
				fscanf_s(fp, "%s\n", temp.pass, sizeof(temp.pass));
				++k;
			}
			rewind(fp);
			mas = new entrance[k];
			for (int i = 0; i < k; i++)
			{
				fscanf_s(fp, "%s", mas[i].login, sizeof(mas[i].login));
				fscanf_s(fp, "%s\n", mas[i].pass, sizeof(mas[i].pass));
			}
			rewind(fp);
			fclose(fp);
			printf("Пользователи:\n");
			printf("----------------------------------------\n");
			printf("| ID   |           Логин пользователя  |\n");
			printf("----------------------------------------\n");
			for (int i = 0; i < k; i++)
			{
				printf("|%6d|%31s|\n", i + 1, mas[i].login);
				printf("---------------------------------------\n");
			}
			system("pause");
			return 0;
		}
		else
		{
			fclose(fp);
			system("pause");
			return 1;
		}
	}
	else { cout << "error of opening!" << endl; }

}

SClient::SClient()
{

}
SOCKET SClient::start() {
	if (WSAStartup(MAKEWORD(2, 2), &wData) != 0)
	{
		printf("WSA Startup succes\n");
		return 0;
	}

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(1280);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	this->s = socket(AF_INET, SOCK_STREAM, 0);

	connect(s, (sockaddr*)&dest_addr, sizeof(dest_addr));
	printf("Client created\n");
	return s;
}
SClient::~SClient()
{
}
void SClient::handle()
{
	char buf[100];
	while (true)
	{
		int k = recv(s, buf, sizeof(buf), 0);
		if (k > 0) {
			cout << buf;
		}
		Sleep(30);
	}
}

void hennery::addTarget(SOCKET& s) {
	char str[255];
	int scal;
	int kursor;
	cin.ignore();
	cout << "Введите название исследования:" << endl;
	getline(cin, study_name);
	client.sendString(study_name, s);
	while (true) {
		cin.unsetf(ios::skipws);
		cout << "Введите шкалу:" << endl;
		cin >> scale;
		if (scale < 1 || scale>100) {
			cout << " Не может быть отрицательное число!Максимально возможная шкала - 100." << endl;
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
	client.sending(scale, s);

	while (true) {
		cin.unsetf(ios::skipws);
		cout << "Введите количество целей:" << endl;
		cin >> numTargets;

		if (numTargets > 100 || numTargets < 1) {
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
	client.sending(numTargets, s);
	if (numTargets < 0) {}
	else {
		obj_study = new study[numTargets];
		for (int i = 0; i < numTargets; i++) {
			obj_study->addInfo(s);
		}
	}

}
int hennery::receive_target(SOCKET& s) {
	client.answString(study_name, s);

	client.answer(numTargets, s);
	client.answer(scale, s);
	obj_study = new study[numTargets];
	for (int k = 0; k < numTargets; k++) {
		obj_study[k].receiveInfo(s);
	}
	return 0;

}
int hennery::show_targets(SOCKET& s) {
	int number = 0, key;
	map<int, hennery> mp;
	hennery* data;
	char buf[255];
	client.answer(number, s);
	if (number == 0) {
		cout << "Файл с исследованиями пуст!" << endl;
		return number;
	}
	else {
		data = new hennery[number];
		buf[0] = '\0';
		for (int i = 0; i < number; i++) {
			client.answer(key, s);
			data[i].receive_target(s);

			mp.insert(pair<int, hennery>(key, data[i]));

		}
		map<int, hennery>::iterator it;
		cout << "+-------+------------------------------------------+------------------------------------------+-------------------+-----------------+-------------------+" << endl;
		cout << "| Ключ  |         Название исследования            |                 Цели                     |   Количество(штук)|   Цена(бел.р.)  | Итоговая cтоимость|" << endl;
		cout << "|-------|------------------------------------------|------------------------------------------|-------------------|-----------------|-------------------|" << endl;
		for (it = mp.begin(); it != mp.end(); ++it) {

			cout << "|" << setw(7) << it->first << "|";
			cout << setw(42) << it->second.study_name << "|";
			for (int i = 0; i < it->second.numTargets; i++) {
				cout << setw(42) << it->second.obj_study[i].getTarget() << "|" << setw(19) << it->second.obj_study[i].getAmount() << "|" << setw(17) << it->second.obj_study[i].getPrice() << '|'
					<< setw(19) << it->second.obj_study[i].getAmount() * it->second.obj_study[i].getPrice() << "|" << '\n';

				if (i != it->second.numTargets - 1) {
					cout << "|       |                                          |------------------------------------------|-------------------|-----------------|-------------------|" << endl;
					cout << "|       |" << setw(43) << '|';
				}

			}
			cout << "+-------+------------------------------------------+------------------------------------------+-------------------+-----------------+-------------------+" << endl;
		}
	}
	return number;

}
void hennery::delete_target(SOCKET& s) {
	int key, number = 0;
	//char buf[255];
	number = show_targets(s);
	if (number == 0) {
	}
	else {
		cout << " Введите key опроса, который вы хотите удалить: ";
		cin.ignore(10, '\n');
		while (true) {
			cin.unsetf(ios::skipws);
			cin >> key;
			if (key < 1 || key>number) {
				cout << " Ключ введен неверно!" << endl;
				cin.clear(ios::failbit);
			}
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			cin.clear();
			cin.ignore(10, '\n');
		}
		client.sending(key, s);

		show_targets(s);
	}
}
int hennery::edit_target(SOCKET& s) {
	int number = 0, key, k, x;
	float y;
	char buf[255];
	number = show_targets(s);
	while (true) {
		cout << "Введите ключ: ";
		cin.unsetf(ios::skipws);
		cin >> key;

		if (key < 1 || key>number) {
			cout << " Ключ введен неверно!" << endl;
			cin.clear(ios::failbit);
		}
		if (cin.good()) {
			cin.ignore(10, '\n');
			break;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}
	itoa(key, buf, 10);
	send(s, buf, sizeof(buf), 0);

	cout << "Выберите номер цели: " << endl;
	cin >> k;
	itoa(k, buf, 10);
	send(s, buf, sizeof(buf), 0);

	int cod = -1;
	while (1) {
		cout << "1.Изменить количество." << endl;
		cout << "2.Изменить цену." << endl;
		cout << "0.Выход." << endl;
		cin.ignore();
		cin >> cod;
		switch (cod) {
		case 1:
			cin.ignore();
			cout << "Введите количество: " << endl;
			strcpy(buf, "edit_amount");
			send(s, buf, sizeof(buf), 0);
			cin >> x;
			client.sending(x, s);
			break;
		case 2:
			cin.ignore();
			cout << "Введите цену: " << endl;
			strcpy(buf, "edit_price");
			send(s, buf, sizeof(buf), 0);
			cin >> y;
			client.sendFloat(y, s);
			break;
		case 0:
			strcpy(buf, "end");
			send(s, buf, sizeof(buf), 0);
			return 0;
		}
	}
	return 0;
}
void hennery::addMark(SOCKET& s) {
	vector<int> marks;
	hennery data;
	char str[255];
	int number = 0, x;
	int counter = 0, key, num = 0;
	number = show_targets(s);
	if (number == 0) {
	}
	else {
		send(s, volk, sizeof(volk), 0);

		cout << "Введите key:" << endl;
		cin.ignore(10, '\n');
		while (true) {
			cin.unsetf(ios::skipws);
			cin >> key;
			if (key < 1 || key>number) {
				cout << " Ключ введен неверно!" << endl;
				cin.clear(ios::failbit);
			}
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			cin.clear();
			cin.ignore(10, '\n');
		}
		client.sending(key, s);
		client.answer(counter, s);
		if (counter == 0) {
			data.receive_target(s);
			cout << "Максимальная оценка " << data.scale << ", минимальная - 1." << endl;

			str[0] = '\0';
			cout << "Введите оценки:" << endl;
			for (int i = 0; i < data.numTargets; i++) {
				cin.ignore(10, '\n');
				while (true) {
					cin.unsetf(ios::skipws);
					cout << i + 1 << ". " << data.obj_study[i].getTarget() << ": ";
					cin >> x;
					if (x < 1 || x>data.scale) {
						cout << " Оценка введена неверно!" << endl;
						cin.clear(ios::failbit);
					}
					if (cin.good()) {
						cin.ignore(10, '\n');
						break;
					}
					cin.clear();
					cin.ignore(10, '\n');
				}
				marks.push_back(x);
			}
			for (int i = 0; i < data.numTargets; i++) {

				itoa(marks[i], str, 10);
				send(s, str, sizeof(str), 0);
				str[0] = '\0';
			}
		}
		else cout << "Вы уже проставили этому исследованию оценки!" << endl;
	}
}
int hennery::show_my_marks(SOCKET& s) {
	int key, counter = 0, number = 1, x = 0, answ = 0;
	char buf[255], str[40];
	number = show_targets(s);
	if (number == 0) {
		return 0;
	}
	else {

		if (recv(s, buf, sizeof(buf), 0) != 0) {
			answ = atoi(buf);
		}
		if (answ == 0) {
			cout << "Файл с оценками пуст!" << endl;
			return 0;
		}
		else {
			cout << "Введите ключ: ";
			cin.ignore(10, '\n');
			while (true) {
				cin.unsetf(ios::skipws);
				cin >> key;

				if (key < 1 || key>number) {
					cout << " Ключ введен неверно!" << endl;
					cin.clear(ios::failbit);
				}
				if (cin.good()) {
					cin.ignore(10, '\n');
					break;
				}
				cin.clear();
				cin.ignore(10, '\n');
			}
			itoa(key, buf, 10);
			send(s, buf, sizeof(buf), 0);

			send(s, volk, sizeof(volk), 0);
			if (recv(s, buf, sizeof(buf), 0)) {
				counter = atoi(buf);
			}
			if (counter == 0) {
				cout << "Вы еще не поставили оценки этому исследованию!" << endl;
				return 0;
			}
			else {
				cout << "+----------------------------------------+----------------------+";
				cout << endl;
				cout << "|          Название цели                 |      Мои оценки      |";
				cout << endl;
				cout << "+----------------------------------------+----------------------+";
				cout << endl;
				receive_target(s);
				for (int i = 0; i < numTargets; i++) {

					cout << "|" << setw(40) << obj_study[i].getTarget() << "|";

					client.answer(x, s);
					marks.push_back(x);

					cout << setw(22) << marks[i] << "|";
					cout << '\n';
					cout << "+----------------------------------------+";
					cout << "----------------------+";
					cout << endl;

				}
				marks.clear();
				return key;
			}
		}
	}


}
int hennery::edit_user_marks(SOCKET& s) {
	cout << "Выберите ключ исследования, оценки которого хотите отредактировать." << endl;
	int key = show_my_marks(s);
	int x;
	char buf[255];
	if (key == 0) {
		return 0;
	}
	else {
		send(s, volk, sizeof(volk), 0);
		receive_target(s);
		cout << "Максимальная оценка " << scale << ", минимальная - 0." << endl;

		cout << "Введите оценки:" << endl;
		for (int i = 0; i < numTargets; i++) {
			cin.ignore();
			while (true) {
				cin.unsetf(ios::skipws);
				cout << i + 1 << ". " << obj_study[i].getTarget() << ": ";
				cin >> x;
				if (x < 0 || x>scale) {
					cout << " Оценка введена неверно!" << endl;
					cin.clear(ios::failbit);
				}
				if (cin.good()) {
					cin.ignore(10, '\n');
					break;
				}
				cin.clear();
				cin.ignore(10, '\n');
			}
			marks.push_back(x);
		}
		for (int i = 0; i < numTargets; i++) {

			itoa(marks[i], buf, 10);
			send(s, buf, sizeof(buf), 0);
		}
		return 0;
	}
}
int hennery::show_marks(SOCKET& s) {
	int key, counter = 0, number, answ = 0;
	char buf[255];
	number = show_targets(s);
	if (number == 0) {
		//return number;
	}
	else {

		client.answer(answ, s);
		if (answ == 0) {
			cout << "Файл с оценками пуст!" << endl;
		}
		else {

			cout << "Введите ключ: ";
			cin.ignore(10, '\n');
			while (true) {
				cin.unsetf(ios::skipws);
				cin >> key;
				if (key < 1 || key>number) {
					cout << " Ключ введен неверно!" << endl;
					cin.clear(ios::failbit);
				}
				if (cin.good()) {
					cin.ignore(10, '\n');
					break;
				}
				cin.clear();
				cin.ignore(10, '\n');
			}
			client.sending(key, s);
			client.answer(counter, s);
			if (counter == 0) {
				cout << "У этого исследования еще нет оценок экспертов!" << endl;
			}
			else {
				cout << "+----------------------------------------+";


				for (int j = 0; j < counter; j++) {
					cout << "----------------------+";
				}
				cout << endl;
				cout << "|          Название цели                 |";


				for (int j = 0; j < counter; j++) {
					cout << "      Эксперт №  " << j + 1 << "    |";
				}
				cout << endl;

				cout << "+----------------------------------------+";
				for (int j = 0; j < counter; j++) {
					cout << "----------------------+";
				}
				cout << endl;
				receive_target(s);
				for (int i = 0; i < numTargets; i++) {

					cout << "|" << setw(40) << obj_study[i].getTarget() << "|";

					for (int j = 0; j < counter; j++) {
						if (recv(s, buf, sizeof(buf), 0)) {

							marks.push_back(atoi(buf));
						}
						cout << setw(22) << marks[j] << "|";

					}

					marks.clear();
					cout << '\n';
					cout << "+----------------------------------------+";
					for (int j = 0; j < counter; j++) {
						cout << "----------------------+";
					}
					cout << endl;
				}
			}
		}
	}
	return 0;
}
void hennery::delete_user_marks(SOCKET& s) {
	cout << "Выберите ключ исследования, оценки которого хотите удалить." << endl;
	int key = show_my_marks(s);
	if (key == 0) {

	}
	else {
		send(s, volk, sizeof(volk), 0);

	}



}
int hennery::meth(SOCKET& s) {

	hennery data;

	int key, counter = 0, number = 0, answ, x, index = 0;
	number = show_targets(s);
	if (number == 0) {}
	else {
		client.answer(answ, s);
		if (answ == 0) {
			cout << "Файл с оценками экспертов пуст!" << endl;
			return 1;
		}
		else {
			cout << "Введите ключ: ";
			cin.ignore(10, '\n');
			while (true) {
				cin.unsetf(ios::skipws);
				cin >> key;
				if (key < 1 || key>number) {
					cout << " Ключ введен неверно!" << endl;
					cin.clear(ios::failbit);
				}
				if (cin.good()) {
					cin.ignore(10, '\n');
					break;
				}
				cin.clear();
				cin.ignore(10, '\n');
			}
			client.sending(key, s);
			client.answer(counter, s);
			if (counter == 0) {
				cout << "Список оценок этого исследования пуст." << endl;
				return 2;
			}
			else {
				int exp = counter;

				data.receive_target(s);
				vector<vector<int>> marks(exp, vector <int>(data.numTargets));

				for (int i = 0; i < exp; i++) {

					for (int j = 0; j < data.numTargets; j++) {
						client.answer(x, s);
						marks[i][j] = x;
					}
				}

				cout << "Матрица оценок экспертов:\n";
				for (int i = 0; i < exp; i++) {
					for (int j = 0; j < data.numTargets; j++)
					{

						cout << marks[i][j] << ' ';

					}
					putchar('\n');

				}
				float y;
				vector<vector<float>> normMatrix(exp, vector <float>(data.numTargets));
				for (int i = 0; i < exp; i++) {
					for (int j = 0; j < data.numTargets; j++)
					{
						client.answFloat(y, s);
						normMatrix[i][j] = y;

					}
				}
				cout << "Нормированная матрица:\n";
				for (int i = 0; i < exp; i++) {
					for (int j = 0; j < data.numTargets; j++)
					{


						cout << normMatrix[i][j] << ' ';

					}
					putchar('\n');

				}
				vector<float> w(data.numTargets);
				for (int i = 0; i < data.numTargets; i++) {

					client.answFloat(w[i], s);
					cout << "Цель №" << i + 1 << ". '" << data.obj_study[i].getTarget() << "' ";
					cout << w[i] << endl;
				}
				int temp = w[0];
				client.answer(index, s);
				cout << "Оптимальный вариант: цель номер " << index + 1 << " - " << data.obj_study[index].getTarget() << endl;
			}


		}
	}
	return 0;
}
int hennery::addOrder(SOCKET& s) {
	fstream file;
	int key, counter = 0, number, answ = 0, k;
	char buf[255];
	key = meth(s);
	if (key == 1 || key == 2) {
	}
	else {
		study obj;
		client.answer(counter, s);
		if (counter == 0) {
			obj.receiveInfo(s);

			cout << "По результатам оценок экспертов в данном исследовании был совершен заказ: " << obj.getTarget() << "; " << obj.getAmount() * obj.getPrice() << endl;


		}
		else cout << "Заказ от этого исследования уж был совершен!" << endl;

	}
	return 0;
}
int hennery::showOrders(SOCKET& s) {
	int number = 0;
	study* data;
	int counter = 0, key;
	client.answer(number, s);
	if (number == 0) {
		cout << "Файл с исследованиями пуст!" << endl;
	}
	else {
		client.answer(counter, s);
		if (counter == 0) {
			cout << "Файл с заказами пуст!" << endl;
		}
		else {
			data = new study[counter];
			cout << "+-------+----------------------------------------------------+--------------+--------------------+" << endl;
			cout << "| Ключ  |    Наименование заказанного продукта/услуги        |   Количество | Итоговая стоимость |" << endl;
			cout << "+-------+----------------------------------------------------+--------------+--------------------+" << endl;
			for (int i = 0; i < counter; i++) {
				client.answer(key, s);
				data[i].receiveInfo(s);
				cout << "|" << setw(7) << key << "|" << setw(52) << data[i].getTarget() <<
					"|" << setw(14) << data[i].getAmount() << "|" << setw(20) << data[i].getAmount() * data[i].getPrice() << "|" << endl;
				cout << "+-------+----------------------------------------------------+--------------+--------------------+" << endl;


			}

		}

	}
	return 0;

}
void menuUsers(SOCKET s) {
	int cod = -1;
	entrance<char> vhod;
	while (cod != 0) {
		cout << "1.Добавить пользователя." << endl;
		cout << "2.Удалить пользователя." << endl;
		cout << "3.Показать пользователей." << endl;
		cout << "0.Выход." << endl;

		while (true) {
			cin.unsetf(ios::skipws);
			cout << "Выберите цифру:" << endl;
			cin >> cod;
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Неправильный ввод данных!(Введены символы)\n";
		};
		switch (cod) {
		case 1:
			system("cls");
			if (entrance<char>::adduser() == 0)
			{
				cout << "Добавление успешно!\n";
			}
			else
			{
				cout << "Ошибка!\n";
			}
			system("pause");
			break;
		case 2:
			system("cls");
			entrance<char>::openuser();
			if (entrance<char>::deleteuser() == 0)
			{
				cout << "Удаление успешно!\n";
			}
			else
			{
				cout << "Ошибка!\n";
			}
			system("pause");
			break;
		case 3:
			if (entrance<char>::openuser() == 0)
			{
				cout << "Чтение успешно!\n";
			}
			else
			{
				cout << "Файл пуст!\n";
			}
			system("pause");
			break;
		case 0:
			return;
		default:
			cout << "Неправильный ввод!" << endl;
			break;
		}
		cin.ignore(10, '\n');
	}

}

int menuExpert(SOCKET& s) {
	int cod = -1;
	hennery user;
	char buf[255];
	while (1) {
		cout << "Меню пользователя:" << endl;
		cout << "1.Добавить оценки." << endl;
		cout << "2.Удалить оценки." << endl;
		cout << "3.Редактировать оценки." << endl;
		cout << "4.Просмотреть свои оценки." << endl;
		cout << "0.Выход." << endl;
		while (true) {
			cin.unsetf(ios::skipws);
			cout << "Выберите цифру:" << endl;
			cin >> cod;
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Неправильный ввод данных!(Введены символы)\n";
		};
		switch (cod) {
		case 1:
			system("cls");
			strcpy(buf, "createMarks");
			send(s, buf, sizeof(buf), 0);
			user.addMark(s);
			break;
		case 2:
			system("cls");
			strcpy(buf, "delete_user_marks");
			send(s, buf, sizeof(buf), 0);
			user.delete_user_marks(s);
			break;
		case 3:
			system("cls");
			strcpy(buf, "edit_user_marks");
			send(s, buf, sizeof(buf), 0);
			user.edit_user_marks(s);
			break;
		case 4:
			system("cls");
			strcpy(buf, "show_user_marks");
			send(s, buf, sizeof(buf), 0);
			user.show_my_marks(s);
			break;
		case 0:
			return 0;
		default:
			cout << "Неправильный ввод!" << endl;
			break;
		}
		cin.ignore(10, '\n');
	}
}
int menuAdmin(SOCKET& s) {
	int cod = -1;
	hennery admin;
	char buf[255];
	while (cod != 0) {
		cout << "Меню администратора:" << endl;
		cout << "1.Добавить исследование." << endl;
		cout << "2.Удалить исследование." << endl;
		cout << "3.Управление пользователями." << endl;
		cout << "4.Просмотр исследований." << endl;
		cout << "5.Просмотр оценок экспертов." << endl;
		cout << "6.Формирование отчета." << endl;
		cout << "7.Редактировать цель." << endl;
		cout << "8.Добавление заказа." << endl;
		cout << "9.Просмотр заказов" << endl;
		cout << "0.Выход." << endl;

		while (true) {
			cin.unsetf(ios::skipws);
			cout << "Выберите цифру:" << endl;
			cin >> cod;
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Неправильный ввод данных!(Введены символы)\n";
		};
		switch (cod) {
		case 1:
			system("cls");
			strcpy(buf, "addTarget");
			send(s, buf, sizeof(buf), 0);
			admin.addTarget(s);
			break;
		case 2:
			system("cls");
			strcpy(buf, "delete_target");
			send(s, buf, sizeof(buf), 0);
			admin.delete_target(s);
			break;
		case 3:
			system("cls");
			menuUsers(s);
			break;
		case 4:
			system("cls");
			strcpy(buf, "show_targets");
			send(s, buf, sizeof(buf), 0);
			admin.show_targets(s);
			break;
		case 5:
			system("cls");
			strcpy(buf, "show_marks");
			send(s, buf, sizeof(buf), 0);
			admin.show_marks(s);
			break;
		case 6:
			system("cls");
			strcpy(buf, "meth");
			send(s, buf, sizeof(buf), 0);
			admin.meth(s);
			break;
		case 7:
			system("cls");
			strcpy(buf, "edit_target");
			send(s, buf, sizeof(buf), 0);
			admin.edit_target(s);
			break;
		case 8:
			system("cls");
			strcpy(buf, "addOrder");
			send(s, buf, sizeof(buf), 0);
			admin.addOrder(s);
			break;
		case 9:
			system("cls");
			strcpy(buf, "showOrders");
			send(s, buf, sizeof(buf), 0);
			admin.showOrders(s);
			break;
		case 0:
			return 0;
		default:
			cout << "Неправильный ввод!" << endl;
			break;

		}
		cin.ignore(10, '\n');
	}
	return 0;

}

int mainMenu() {
	int cod = -1;
	entrance<char> vhod;

	while (cod != 0) {
		cout << "1.Вход под администратором." << endl;
		cout << "2.Вход под пользователем." << endl;
		cout << "3.Регистрация пользователя." << endl;
		cout << "0.Выход." << endl;
		while (true) {
			cin.unsetf(ios::skipws);
			cout << "Выберите цифру:" << endl;
			cin >> cod;
			if (cin.good()) {
				cin.ignore(10, '\n');
				break;
			}
			cin.clear();
			cin.ignore(10, '\n');
			cout << "Неправильный ввод данных!(Введены символы)\n";
		};
		switch (cod) {
		case 1: {
			if (vhod.loginadmin() == 0) {
				cout << "Вход успешно выполнен! \n";
				SClient client;
				SOCKET clin = client.start();
				system("cls");
				menuAdmin(clin);
				closesocket(clin);
			}
			else {
				cout << "Неверный логин или пароль!" << "\n";
				system("pause");
			}
		}
			  break;
		case 2:
			if (vhod.loginuser() == 0) {
				cout << "Вход успешно выполнен! \n";
				system("pause");
				SClient client;
				SOCKET clin = client.start();
				system("cls");
				menuExpert(clin);
				closesocket(clin);

			}
			else {
				cout << "Неверный логин или пароль! \n";
				system("pause");
			}
			break;
		case 3:
			vhod.registerUser();
			break;
		case 0:
			return 0;
		default:
			cout << "Неправильный ввод!" << endl;
			break;

		}
		cin.ignore(10, '\n');
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	mainMenu();
	WSACleanup();
	system("pause");
	return 0;
}
