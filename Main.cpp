#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include<map>
#include<regex>
#define EOL '\n'
using namespace std;

bool checking_file_name(string& stroka)
{
	regex regular("([\\w]+[.][t][x][t])");
	if (regex_match(stroka.c_str(), regular)) return true;
	else return false;
}

string entering_file_name()
{
	bool flag = true;
	while (flag)
	{
		string name;
		cout << "Введите имя файла в котором будет производиться поиск элементов: " << endl;
		cin >> name;
		if (checking_file_name(name)) {
			flag = false;
			return name;
		}
		else {
			flag = true;
			cout << "Некорректное имя файла!" << endl;
		}
	}
}

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

bool continue_check()
{
	bool flag = true;
	char symbol;
	cout << endl << "Do you want to continue?" << endl;
	cout << "If you want - press 1" << endl;
	cout << "If you want to quit - press 0" << endl;
	while (!(cin >> symbol) || flag)
	{
		cin.clear();
		if ((symbol == '0') && (cin.peek() == EOL)) {
			flag = false;
			return false;
		}
		else if ((symbol == '1') && (cin.peek() == EOL)) {
			flag = false;
			return true;
		}
		else {
			flag = true;
		}
		while (cin.get() != EOL);
		cout << "Нажмите 0 или 1: " << endl;
	}
}

//map<int, string> glavi()
//{
//	
//}

string input(ifstream& in)
{
	string inp;
	char symbol;
	while (!in.eof())
	{
		in >> symbol;
		if (in.peek() == ' ') { inp.push_back(symbol); inp.push_back(' '); }
		else if (in.peek() == EOL) { inp.push_back(symbol); inp.push_back('\n'); }
		else inp.push_back(symbol);
	}
	return inp;
}

string slovo()
{
	string inp;
	cout << "Введите искомое слово" << endl;
	cin >> inp;
	return inp;
}

int poisk(string& text, string& iskomoe_slovo, int& pos)
{
	return text.find(iskomoe_slovo, pos);
}

vector<int> positions(string& text, string& word)
{
	vector<int> pos;
	int num = 0;
	bool flag = true;
	while (flag)
	{
		num = poisk(text, word, num);
		if (num != string::npos) {
			pos.push_back(num); num++;
		}
		else flag = false;
	}
	return pos;
}

int searching_check()
{
	int a;
	bool flag = true;
	cout << "Предыдущее вхождение -> 1" << endl <<
		"Выход из поиска -> 2" << endl <<
		"Следующее вхождение -> 3" << endl;
	while (!(cin >> a) || flag ) {
		cin.clear();
		if ((a == 1) && (cin.peek() == EOL)) {
			flag = false;
			return 1;
		}
		else if ((a == 2) && (cin.peek() == EOL)) {
			flag = false;
			return 2;
		}
		else if ((a == 3) && (cin.peek() == EOL)){
			flag = false;
			return 3;
		}
		else {
			flag = true;
		}
		while (cin.get() != EOL);
		cout << "Нажмите нужную клавишу: " << endl;
	}
}

void searching_way(string& text, vector<int>& lefts, vector<int>& rights, int& pos_in_vector)
{
	cout << endl << endl;
	int activity_choosing = searching_check();
	if ((activity_choosing == 1) && (pos_in_vector > 0)) {
		system("cls");
		pos_in_vector--;
		for (int i = 0; i < text.size(); i++)
		{
			int element_code = static_cast<int>(text[i]);
			if (((i >= lefts[pos_in_vector]) && (i < rights[pos_in_vector])) && (((element_code >= 65) || (element_code <= 90)) || ((element_code >= 97) || (element_code <= 122)))) {
				SetColor(Black, Yellow);
				cout << text[i];
				SetColor(White, Black);
			}
			else cout << text[i];
		}
		cout << endl << endl;
		searching_way(text, lefts, rights, pos_in_vector);
	}
	if (activity_choosing == 2) return;
	if ((activity_choosing == 3) && (pos_in_vector < lefts.size() - 1)) {
		system("cls");
		pos_in_vector++;
		for (int i = 0; i < text.size(); i++)
		{
			int element_code = static_cast<int>(text[i]);
			if (((i >= lefts[pos_in_vector]) && (i <= rights[pos_in_vector])) && (((element_code >= 65) || (element_code <= 90)) || ((element_code >= 97) && (element_code <= 122)))) 
			{
				SetColor(Black, Yellow);
				cout << text[i];
				SetColor(White, Black);
			}
			else cout << text[i];
		}
		cout << endl << endl;
		searching_way(text, lefts, rights, pos_in_vector);
	}
}

void output(string& text, vector<int>& positions)
{
	vector<int> lefts, rights;
	bool flag = true;
	int left, right;
	for (int j = 0; j < positions.size(); j++)
	{
		left = right = positions[j];
		while (flag) {
			if ((text[left] != ' ') && (text[left] != '\n') && (left != 0)) left--;
			else flag = false;
		}
		lefts.push_back(left);
		flag = true;
		while (flag) {
			if ((text[right] != ' ') && (text[right] != '\n') && (right != text.size())) right++;
			else flag = false;
		}
		rights.push_back(right);
	}
	int n = 0;
	for (int i = 0; i < text.size(); i++)
	{
		int element_code = static_cast<int>(text[i]);
		if (((i >= lefts[n]) && (i < rights[n])) && (((element_code >= 65) || (element_code <= 90)) || ((element_code >= 97) || (element_code <= 122)))) {
			SetColor(Black, Yellow);
			cout << text[i];
			SetColor(White, Black);
		}
		else cout << text[i];
	}
	searching_way(text, lefts, rights, n);
}

int main()
{
	bool iteration = true;
	while (iteration)
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		static string name = entering_file_name();
		ifstream in(name);
		if (in.is_open()) {
			string text = input(in);
			string key = slovo();
			vector<int> position = positions(text, key);
			if (position.size() > 0)
			{
				for (int i = 0; i < position.size(); i++)
					cout << position[i] << ' ';
				cout << endl;
				output(text, position);
			}
			else cout << "Not found" << endl << endl;
			iteration = continue_check();
		}
		else {
			cout << "Файла с таким именем не существует!" << endl;
			iteration = continue_check();
		}
	}
}	
