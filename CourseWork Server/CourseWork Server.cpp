#include "ServerClasses.h"

long getFileSize(fstream* base) {
	long fileSizeBytes;
	base->seekg(0, ios::end);
	fileSizeBytes = base->tellg();
	base->seekg(0, ios::beg);
	return fileSizeBytes;
}

int num = 0, number = 0;
void newHandler() {
	cout << "Вызвана функция newHandler: ";
	throw bad_alloc();
}
int hennery::addTarget(SOCKET& s) {
	char buf[255];
	study_name = receive(s);
	scale = atoi(receive(s).c_str());
	numTargets = atoi(receive(s).c_str());
	set_new_handler(newHandler);
	try {
		obj_study = new study[numTargets];
		for (int i = 0; i < numTargets; i++)
		{
			obj_study[i].addInfo(s);
		}
	}
	catch (bad_alloc & e) {
		cout << e.what() << endl;
		return 1;
	}
	return 0;

}
int hennery::writeTarget() {
	char str[1024];
	int i = 0, lastKey;
	map<int, hennery> note;
	map<int, hennery>::iterator it = note.begin();
	file1.open("Study.txt", ios::in | ios::out | ios::app | ios::binary);
	file1.seekg(0, ios::beg);
	while (true) {
		file1.getline(str, 2048, '\n');
		if (file1.fail()) break;
		i++;
	}
	number = i;
	file1.close();
	file1.open("Study.txt", ios::in | ios::out | ios::binary);
	if (!file1.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return 0;
	}
	else {
		file1.seekg(0, ios::end);
		note.insert(pair<int, hennery>(number + 1, *this));

		for (it = note.begin(); it != note.end(); ++it) {
			file1 << it->first << ' ';
			file1 << it->second;
		}
	}
	file1.close();
	return 0;

}
int hennery::readTarget(SOCKET& s, multimap<int, hennery>& note) {
	int i = 0, key;
	char str[1024], buf[255];
	hennery* data;
	file1.open("Study.txt", ios::in | ios::out | ios::app | ios::binary);
	if (!file1.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
	}
	else {
		file1.seekg(0, ios::beg);
		while (1) {
			file1.getline(str, 1024, '\n');
			if (file1.fail()) break;
			i++;

		}
		number = i;
		itoa(number, buf, 10);
		send(s, buf, sizeof(buf), 0);
		if (number == 0) {
			return number;
		}
		else {
			data = new  hennery[number];
			file1.close();
			file1.open("Study.txt", ios::in | ios::out | ios::binary);
			file1.seekg(0, ios::beg);
			for (int i = 0; i < number; i++) {

				file1.getline(buf, 255, ' ');
				key = atoi(buf);
				itoa(key, buf, 10);
				send(s, buf, sizeof(buf), 0);
				file1 >> data[i];
				data[i].send_target(s);
				note.insert(pair<int, hennery>(key, data[i]));

			}
		}
	}

	file1.close();
	return number;

}
int hennery::readTarget(multimap<int, hennery>& note) {
	int i = 0, key;
	char str[1024], buf[255];
	hennery* data;
	file1.open("Study.txt", ios::in | ios::out | ios::app | ios::binary);
	if (!file1.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
	}
	else {
		file1.seekg(0, ios::beg);
		while (1) {
			file1.getline(str, 1024, '\n');
			if (file1.fail()) break;
			i++;

		}
		number = i;
		if (number == 0) {

			return number;
		}
		else {
			data = new  hennery[number];
			file1.close();
			file1.open("Study.txt", ios::in | ios::out | ios::binary);
			file1.seekg(0, ios::beg);
			for (int i = 0; i < number; i++) {

				file1.getline(buf, 255, ' ');
				key = atoi(buf);

				file1 >> data[i];

				note.insert(pair<int, hennery>(key, data[i]));

			}
		}
	}

	file1.close();
	return number;

}
int hennery::send_target(SOCKET& s) {
	char buf[255];
	strcpy(buf, study_name.c_str());
	send(s, buf, sizeof(buf), 0);

	itoa(numTargets, buf, 10);
	send(s, buf, sizeof(buf), 0);

	itoa(scale, buf, 10);
	send(s, buf, sizeof(buf), 0);

	for (int j = 0; j < numTargets; j++) {
		obj_study[j].sendInfo(s);
	}
	return 0;
}
int hennery::edit_target(SOCKET& s) {
	multimap<int, hennery> note;
	int number = 0, key = 0;
	char buf[255];
	number = readTarget(s, note);
	key = atoi(receive(s).c_str());
	multimap<int, hennery>::iterator pos;
	pos = note.find(key);
	if (pos != note.end()) {
		pos->second.menu_edit_target(s, pos->second.getNumtargets());
	}
	file1.open("Study.txt", ios::trunc | ios::in | ios::out | ios::binary);
	if (!file1.is_open()) {
		cout << "Ошибка отрытия файла!" << endl;
		return 1;
	}
	else {
		file1.seekg(0, ios::end);
		for (pos = note.begin(); pos != note.end(); ++pos) {
			file1 << pos->first << ' ';
			file1 << pos->second;
		}
	}
	file1.close();
	return 0;
}
int hennery::menu_edit_target(SOCKET& s, int size) {
	int k, x;
	float y;
	char buf[255];
	k = atoi(receive(s).c_str());
	int cod = -1;
	while (true) {
		strcpy(buf, receive(s).c_str());
		if (strcmp(buf, "edit_amount") == 0) {

			x = atoi(receive(s).c_str());
			obj_study[k - 1].getAmount(x);
		}
		else if (strcmp(buf, "edit_price") == 0) {
			y = atof(receive(s).c_str());
			this->obj_study[k - 1].getPrice(y);
		}
		else if (strcmp(buf, "end") == 0) { break; }
	}
	return 0;

}
ostream& operator<<(ostream& stream, hennery& obj) {
	stream << obj.study_name << "*" << obj.numTargets << "*" << obj.scale << "*";
	for (int i = 0; i < obj.numTargets; i++) {
		stream << obj.obj_study[i];
	}
	stream << '\n';
	return stream;
}
istream& operator>>(istream& stream, hennery& obj) {
	char str[255];
	char buf[1024];
	stream.getline(str, 255, '*');
	obj.study_name = str;
	str[0] = '\0';
	stream.getline(str, 255, '*');
	obj.numTargets = atoi(str);
	str[0] = '\0';
	stream.getline(str, 255, '*');
	obj.scale = atoi(str);
	obj.obj_study = new study[obj.numTargets];
	for (int i = 0; i < obj.numTargets; i++) {
		stream >> obj.obj_study[i];
	}
	stream.getline(buf, 1024, '\n');
	return stream;
}

int hennery_production::addMark(SOCKET& s) {
	char buf[255], log[255];
	int x, key, scal, counter = 0;
	hennery_production data;
	multimap<int, hennery> mp;
	number = readTarget(s, mp);
	if (number == 0) {}
	else {
		multimap<int, hennery_production> experts;
		readMarks(experts);
		multimap<int, hennery>::iterator pos;
		strcpy(data.login, receive(s).c_str());
		strcpy(log, data.login);
		key = atoi(receive(s).c_str());
		multimap<int, hennery_production>::iterator ptr;
		for (ptr = experts.begin(); ptr != experts.end(); ptr++) {
			if (ptr->first == key && strcmp(ptr->second.login, log) == 0) {

				counter++;
			}
		}
		itoa(counter, buf, 10);
		send(s, buf, sizeof(buf), 0);

		if (counter == 0) {
			pos = mp.find(key);

			num = pos->second.getNumtargets();
			pos->second.send_target(s);

			data.size = num;
			for (int i = 0; i < num; i++) {
				x = atoi(receive(s).c_str());
				data.marks.push_back(x);
			}
			experts.clear();

			file2.open("Marks.txt", ios::in | ios::out | ios::app | ios::binary);
			if (!file2.is_open()) {
				cout << "Ошибка открытия файла!" << endl;
				return 1;
			}
			else {
				file2.seekg(0, ios::end);
				experts.insert(pair<int, hennery_production>(key, data));
				multimap<int, hennery_production>::iterator it = experts.begin();
				file2 << it->first << ".";
				file2 << it->second;
			}
			file2.close();
		}
	}
	return 0;



}
int hennery_production::writeMarks(multimap<int, hennery_production>& expert) {
	multimap<int, hennery_production>::iterator it;
	file2.open("Marks.txt", ios::trunc | ios::in | ios::out | ios::binary);
	if (!file2.is_open()) {
		cout << "Ошибка отрытия файла!" << endl;
		return 1;
	}
	else {
		file2.seekg(0, ios::end);
		for (it = expert.begin(); it != expert.end(); ++it) {
			file2 << it->first << '.';
			file2 << it->second;
		}
	}
	file2.close();
	return 0;

}
int hennery_production::readMarks(multimap<int, hennery_production>& note) {
	hennery_production* data;
	char str[1024], buf[255];
	int i = 0, number = 0, key;
	multimap<int, hennery_production>::iterator it;
	file2.open("Marks.txt", ios::in | ios::out | ios::app || ios::binary);
	if (!file2.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return -1;
	}
	else {
		file2.seekg(0, ios::beg);
		while (1) {

			file2.getline(str, 1024, '\n');
			if (file2.fail()) break;
			i++;

		}
		number = i;
		if (number == 0) {
			return number;
		}
		else {
			data = new hennery_production[number];
			file2.close();
			file2.open("Marks.txt", ios::in | ios::out | ios::binary);
			file2.seekg(0, ios::beg);

			for (int j = 0; j < number; j++) {
				file2.getline(buf, 255, '.');
				key = atoi(buf);
				file2 >> data[j];
				note.insert(pair<int, hennery_production>(key, data[j]));
			}
		}

	}
	file2.close();
	return number;

}
ostream& operator<<(ostream& stream, hennery_production& obj) {
	stream << obj.size << '.';
	for (int i = 0; i < obj.size; i++) {
		stream << obj.marks[i] << '.';
	}
	stream << obj.login << '.';
	stream << '\n';
	return stream;


}
istream& operator>>(istream& stream, hennery_production& obj) {
	char str[255], stroka[1024];
	stream.getline(str, 255, '.');
	obj.size = atoi(str);
	for (int i = 0; i < obj.size; i++) {

		stream.getline(str, 255, '.');
		obj.marks.push_back(atoi(str));

	}
	file2.getline(obj.login, 255, '.');
	file2.getline(stroka, 1024, '\n');
	return stream;

}

int expert_method::show_table(SOCKET& s) {
	char buf[255];

	int key, counter = 0;
	multimap<int, hennery> mp;
	multimap<int, hennery_production> expert;
	number = data->readTarget(s, mp);

	if (number == 0) {}
	else {
		number = adept->readMarks(expert);

		itoa(number, buf, 10);
		send(s, buf, sizeof(buf), 0);
		if (number == 0) {

		}
		else {
			key = atoi(receive(s).c_str());
			multimap<int, hennery>::iterator pos;
			pos = mp.find(key);
			multimap<int, hennery_production>::iterator it;

			for (it = expert.begin(); it != expert.end(); it++) {
				if (it->first == key) {
					counter++;
				}
			}
			itoa(counter, buf, 10);
			send(s, buf, sizeof(buf), 0);

			if (counter == 0) {

			}
			else {
				num = pos->second.getNumtargets();
				pos->second.send_target(s);

				for (int i = 0; i < num; i++) {

					for (it = expert.begin(); it != expert.end(); it++) {
						if (it->first == key) {
							itoa(it->second.getMarks()[i], buf, 10);
							send(s, buf, sizeof(buf), 0);

						}

					}

				}
			}
		}
	}
	return 0;



}
void expert_method::delete_target(SOCKET& s) {
	fstream file;
	multimap<int, hennery> zapic;
	multimap<int, int> task;
	number = data->readTarget(s, zapic);

	multimap<int, hennery>::iterator mapPtr;
	char buf[255];
	int key, cod;
	if (number == 0) {

	}
	else {
		key = atoi(receive(s).c_str());
		cod = key;
		map<int, hennery>::iterator pos = zapic.begin();
		readOrder(s, task);
		multimap<int, int>::iterator cur;
		//cur = task.find(key);
		int delElem = task.erase(key);

		pos = zapic.find(key);
		pos = zapic.erase(pos); // C++11
		multimap<int, hennery>::iterator it;
		search_marks(s, key);

		for (pos; pos != zapic.end(); ++pos) {
			const_cast<int&>(pos->first) = key;
			key++;
		}
		if (delElem != 0) {
			for (cur; cur != task.end(); ++cur) {
				const_cast<int&>(cur->first) = cod;
				cod++;
			}
		}
		file1.open("Study.txt", ios::trunc | ios::in | ios::out | ios::binary);
		if (!file1.is_open()) { cout << "Ошибка открытия файла!" << endl; return; }
		else {
			file1.seekg(0, ios::beg);
			for (it = zapic.begin(); it != zapic.end(); ++it) {
				file1 << it->first << ' ';
				file1 << it->second;
			}
		}
		file1.close();

		file.open("Order.txt", ios::trunc | ios::in | ios::out | ios::binary);
		if (!file.is_open()) { cout << "Ошибка открытия файла!" << endl; return; }
		else {
			file.seekg(0, ios::beg);
			for (cur = task.begin(); cur != task.end(); ++cur) {
				file << cur->first << ' ';
				file << cur->second;
			}
		}
		file.close();
	}
	data->readTarget(s, zapic);
}
int expert_method::search_marks(SOCKET& s, int key) {
	multimap<int, hennery_production> expert;
	number = adept->readMarks(expert);
	if (number == 0) {}
	else {
		multimap<int, hennery_production>::iterator it;
		multimap<int, hennery_production>::iterator pos;
		int delElem = expert.erase(key);
		if (delElem != 0) {
			for (pos = expert.begin(); pos != expert.end(); pos++) {
				if (pos->first > key) {
					int tmp = pos->first;
					tmp -= 1;
					const_cast<int&>(pos->first) = tmp;
				}
			}
			file2.open("Marks.txt", ios::trunc | ios::in | ios::out | ios::binary);
			if (!file2.is_open()) { cout << "Ошибка открытия файла!" << endl; return 0; }
			else {
				file2.seekg(0, ios::beg);
				for (it = expert.begin(); it != expert.end(); ++it) {
					file2 << it->first << '.';
					file2 << it->second;
				}
			}
			file2.close();
		}
	}
	return 0;
}
int expert_method::show_user_marks(SOCKET& s, multimap<int, hennery>& mp, multimap<int, hennery_production>& expert) {
	char buf[255], str[40];
	int key, counter = 0;
	char log[255];
	container<int> vect;
	number = data->readTarget(s, mp);
	if (number == 0) {
		return 0;
	}
	else {
		number = adept->readMarks(expert);
		itoa(number, buf, 10);
		send(s, buf, sizeof(buf), 0);
		if (number == 0) {
			return 0;
		}
		else {
			key = atoi(receive(s).c_str());
			strcpy(log, receive(s).c_str());
			multimap<int, hennery>::iterator pos;
			pos = mp.find(key);
			multimap<int, hennery_production>::iterator it;
			for (it = expert.begin(); it != expert.end(); it++) {
				if (it->first == key && strcmp(it->second.getLogin(), log) == 0) {
					counter++;
				}
			}

			itoa(counter, buf, 10);
			send(s, buf, sizeof(buf), 0);
			if (counter == 0) {
				return 0;
			}
			else {
				pos->second.send_target(s);
				for (it = expert.begin(); it != expert.end(); it++) {

					if (it->first == key && strcmp(it->second.getLogin(), log) == 0) {
						vect = it->second.getMarks();
						container<int>::Iterator iter(vect.begin());
						int i = 0;
						for (iter; iter != vect.end(); iter++) {
							itoa(vect[i], buf, 10);
							send(s, buf, sizeof(buf), 0);
							i++;
						}
					}
				}
				return key;
			}
		}
	}




}
int expert_method::show_user_marks(SOCKET& s) {
	char buf[255], str[40];
	int key, counter = 0;
	char log[255];
	container<int> vect;
	multimap<int, hennery> mp;
	multimap<int, hennery_production> expert;
	number = data->readTarget(s, mp);
	if (number == 0) {
		return 0;
	}
	else {
		number = adept->readMarks(expert);
		itoa(number, buf, 10);
		send(s, buf, sizeof(buf), 0);
		if (number == 0) {
			return 0;
		}
		else {
			key = atoi(receive(s).c_str());
			strcpy(log, receive(s).c_str());
			multimap<int, hennery>::iterator pos;
			pos = mp.find(key);
			multimap<int, hennery_production>::iterator it;
			for (it = expert.begin(); it != expert.end(); it++) {
				if (it->first == key && strcmp(it->second.getLogin(), log) == 0) {
					counter++;
				}
			}

			itoa(counter, buf, 10);
			send(s, buf, sizeof(buf), 0);
			if (counter == 0) {
				return 0;
			}
			else {
				pos->second.send_target(s);
				for (it = expert.begin(); it != expert.end(); it++) {

					if (it->first == key && strcmp(it->second.getLogin(), log) == 0) {
						vect = it->second.getMarks();
						container<int>::Iterator iter(vect.begin());
						int i = 0;
						for (iter; iter != vect.end(); iter++) {
							itoa(vect[i], buf, 10);
							send(s, buf, sizeof(buf), 0);
							i++;
						}
					}
				}
				return key;
			}
		}
	}
}

int  expert_method::edit_user_marks(SOCKET& s) {
	hennery_production data;
	multimap<int, hennery> mp;
	multimap<int, hennery_production> expert;
	int key = show_user_marks(s, mp, expert);
	char log[255], buf[255];
	int scal;
	if (key == 0) {}
	else {
		strcpy(log, receive(s).c_str());
		multimap<int, hennery_production>::iterator it;
		multimap<int, hennery_production>::iterator pos;
		for (it = expert.begin(); it != expert.end(); it++) {

			if (it->first == key && strcmp(it->second.getLogin(), log) == 0) {
				pos = it;
				break;
			}

		}
		multimap<int, hennery>::iterator cur;
		cur = mp.find(key);
		num = pos->second.getMarks().size();
		expert.erase(pos);
		cur->second.send_target(s);
		strcpy(data.getLogin(), log);
		data.receive_marks(s, num);
		expert.insert(pair<int, hennery_production>(key, data));
		data.writeMarks(expert);
	}
	return 0;
}
int expert_method::delete_user_marks(SOCKET& s) {
	multimap<int, hennery_production> expert;
	multimap<int, hennery> mp;
	int key = show_user_marks(s, mp, expert);
	char log[255];
	if (key == 0) {
	}
	else {
		strcpy(log, receive(s).c_str());
		multimap<int, hennery_production>::iterator it;
		multimap<int, hennery_production>::iterator pos;
		for (pos = expert.begin(); pos != expert.end(); pos++) {
			if (pos->first == key && strcmp(log, pos->second.getLogin()) == 0) {
				expert.erase(pos);
				break;
			}
		}
		adept->writeMarks(expert);

	}
	return 0;


} //+
int expert_method::meth(SOCKET& s, multimap<int, int>& task) {
	char buf[255];
	multimap<int, hennery> adm;
	multimap<int, hennery_production> usr;

	int key = 0, counter = 0, answ;
	number = data->readTarget(s, adm);
	if (number == 0) {}
	else {
		answ = adept->readMarks(usr);
		itoa(answ, buf, 10);
		send(s, buf, sizeof(buf), 0);
		if (answ == 0) {
			return 0;
		}
		else {
			char buf[255];
			key = atoi(receive(s).c_str());
			multimap<int, hennery_production>::iterator ptr;
			multimap<int, hennery>::iterator it;
			multimap<int, hennery>::iterator pos;
			for (ptr = usr.begin(); ptr != usr.end(); ptr++) {
				if (ptr->first == key) {
					counter++;
				}
			}
			int exp = counter;
			itoa(counter, buf, 10);
			send(s, buf, sizeof(buf), 0);
			if (counter == 0)
			{
				return 0;
			}
			else {
				string* aim;

				vector<int> sum(exp);
				it = adm.find(key);
				int numAim = it->second.getNumtargets();
				it->second.send_target(s);
				vector<vector<int>> marks(exp, vector <int>(numAim));
				aim = new string[numAim];
				for (int i = 0; i < numAim; i++) {
					aim[i] = it->second.getObj()[i].getTarget();
				}
				ptr = usr.begin();
				int i = 0;
				for (ptr; ptr != usr.end(); ptr++) {
					if (ptr->first == key) {

						for (int j = 0; j < numAim; j++) {
							marks[i][j] = ptr->second.getMarks()[j];
							serv.sending(marks[i][j], s);
						}
						i++;
					}

				}
				for (int i = 0; i < exp; i++) {

					for (int j = 0; j < numAim; j++) {

						sum[i] += marks[i][j];
					}
				}
				vector<vector<float>> normMatrix(exp, vector <float>(numAim));

				for (int i = 0; i < exp; i++) {
					for (int j = 0; j < numAim; j++) {
						normMatrix[i][j] = float(marks[i][j]) / float(sum[i]);
						serv.sendFloat(normMatrix[i][j], s);
					}
				}

				vector<float> w(numAim);
				for (int i = 0; i < numAim; i++) {

					for (int j = 0; j < exp; j++) {
						w[i] = w[i] + normMatrix[j][i];
					}
					w[i] /= exp;
					serv.sendFloat(w[i], s);
				}
				int  index = 0;
				float temp = w[0];
				for (int i = 0; i < numAim; i++) {

					if (w[i] > temp)
					{
						temp = w[i];
						index = i;
					}
				}
				serv.sending(index, s);
				task.insert(pair<int, int>(key, index));
			}
		}
	}
	return key;
}
int expert_method::writeMeth(multimap<int, int>& task) {
	multimap<int, int>::iterator it;
	fstream file("Order.txt", ios::binary);

	file.open("Order.txt", ios::in | ios::out | ios::app | ios::binary);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return 0;
	}
	else {

		file.seekg(0, ios::end);
		for (it = task.begin(); it != task.end(); ++it) {
			file << it->first << ' ';
			file << it->second << '.';
			file << '\n';
		}


	}
	file.close();
	return 0;
}
int expert_method::readOrder(SOCKET& s, multimap<int, int>& task) {
	int i = 0, key, index;
	char str[1024], buf[255];
	fstream file;
	file.open("Order.txt", ios::in | ios::out | ios::app | ios::binary);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
	}
	else {
		file.seekg(0, ios::beg);
		while (1) {
			file.getline(str, 1024, '\n');
			if (file.fail()) break;
			i++;

		}
		number = i;
		if (number == 0) {
			return number;
		}
		else {
			file.close();
			file.open("Order.txt", ios::in | ios::out | ios::app | ios::binary);
			file.seekg(0, ios::beg);
			for (int i = 0; i < number; i++) {

				file.getline(buf, 255, ' ');
				key = atoi(buf);
				file.getline(buf, 255, '.');
				index = atoi(buf);
				file.getline(str, 1024, '\n');
				task.insert(pair<int, int>(key, index));
			}
		}
	}
	file.close();
	return number;

}
int expert_method::addOrder(SOCKET& s, multimap<int, int>& task) {
	multimap<int, int> fil;
	int key = meth(s, task);
	int counter = 0;
	if (key == 0) {}
	else {
		readOrder(s, fil);
		multimap<int, int>::iterator ptr;
		multimap<int, hennery> mp;
		data->readTarget(mp);
		multimap<int, hennery>::iterator it;
		it = mp.find(key);
		for (ptr = fil.begin(); ptr != fil.end(); ptr++) {
			if (ptr->first == key) {

				counter++;
			}
		}
		serv.sending(counter, s);
		if (counter == 0) {
			writeMeth(task);
			fil.clear();
			readOrder(s, fil);
			for (ptr = fil.begin(); ptr != fil.end(); ptr++) {
				if (ptr->first == key) {
					it->second.getObj()[ptr->second].sendInfo(s);
				}
			}
		}
	}
	return 0;
}
int expert_method::showOrders(SOCKET& s, multimap<int, int>& task) {

	multimap<int, hennery> mp;

	int number = data->readTarget(mp);
	int counter = 0;
	readOrder(s, task);
	multimap<int, hennery>::iterator it;
	multimap<int, int>::iterator cur;
	for (cur = task.begin(); cur != task.end(); ++cur) {
		counter++;
	}
	serv.sending(number, s);
	if (number == 0) {}
	else {

		serv.sending(counter, s);
		if (counter == 0) {}
		else {
			for (cur = task.begin(); cur != task.end(); ++cur) {

				it = mp.find(cur->first);
				serv.sending(cur->first, s);
				it->second.getObj()->sendInfo(s);
			}

		}
	}

	return 0;
}
int main()
{
	WSACleanup();
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SServer server;

	multimap<int, hennery> note;
	multimap<int, hennery_production> use;
	multimap<int, int> task;
	expert_method term;
	hennery_production user;
	hennery admin;

	server.startServer();
	SOCKET s2;

	SOCKADDR_IN addr_c;
	int addrlen = sizeof(addr_c);
	while (true) {
		if ((s2 = accept(server.s, (struct sockaddr*) & addr_c, &addrlen)) != 0) {
			printf("Адрес нового подключенного клиента %u.%u.%u.%u:%u\n",
				(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b1,
				(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b2,
				(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b3,
				(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b4,
				ntohs(addr_c.sin_port));
			char buf[255];
			int result = 0;
			do {
				result = recv(s2, buf, sizeof(buf), 0);
				if (result > 0) {
					if (strcmp(buf, "addTarget") == 0)
					{
						if (admin.addTarget(s2) == 0)
							admin.writeTarget();
						else cout << "Объект не добавлен!" << endl;
					}
					if (strcmp(buf, "delete_target") == 0)
					{
						term.delete_target(s2);
					}
					if (strcmp(buf, "show_targets") == 0)
					{
						admin.readTarget(s2, note);
						note.clear();
					}
					if (strcmp(buf, "show_marks") == 0)
					{
						term.show_table(s2);
					}
					if (strcmp(buf, "meth") == 0)
					{
						term.meth(s2, task);
						task.clear();
					}
					if (strcmp(buf, "createMarks") == 0)
					{
						user.addMark(s2);
					}
					if (strcmp(buf, "delete_user_marks") == 0)
					{
						term.delete_user_marks(s2);
					}
					if (strcmp(buf, "edit_user_marks") == 0)
					{
						term.edit_user_marks(s2);
					}
					if (strcmp(buf, "show_user_marks") == 0)
					{
						term.show_user_marks(s2);
					}
					if (strcmp(buf, "edit_target") == 0)
					{
						admin.edit_target(s2);
					}
					if (strcmp(buf, "addOrder") == 0)
					{
						term.addOrder(s2, task);
						task.clear();
					}
					if (strcmp(buf, "showOrders") == 0)
					{
						term.showOrders(s2, task);
						task.clear();
					}

				}
				else {
					cout << "Клиент отключился." << endl;
					closesocket(s2);
					main();
				}

			} while (result > 0);
		}
		closesocket(s2);
	}
	server.closeServer();
	system("pause");
	return 0;
}