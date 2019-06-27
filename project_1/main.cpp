#include <iostream>
#include <cctype>
#include <codecvt>
#include <locale>
#include "modAlphaCipher.h"

using namespace std;
bool isValid(const string& s)
{
	locale loc("ru_RU.UTF-8");
	wstring_convert<codecvt_utf8 <wchar_t>, wchar_t> codec;
	wstring ws = codec.from_bytes(s);
	for(auto wc:ws)
		if (!isalpha(wc,loc) || !isupper(wc,loc))
			return false;
	return true;
}

int main(int argc, char **argv)
{
	string key;
	string text;
	unsigned op;
	cout << "Шифратор готов. Введите ключ: ";
	cin >> key;
	if (!isValid(key)) {
		cerr << "Ключ не принят" << endl;
		return 1;
	}
	cout << "Ключ принят" << endl;
	modAlphaCipher cipher(key);
	do {
		cout << "Шифратор готов. Введите операцию (0-выход, 1-Зашифровка, 2-Расшифровка): ";
		cin >> op;
		if (op > 2) {
			cout << "Недопустимая операция" << endl;
		} else if (op > 0) {
			cout << "Шифратор готов. Введите текст: ";
			cin >> text;
			if (isValid(text)) {
				if (op == 1) {
					cout << "Зашифрованный текст: " << cipher.encrypt(text) << endl;
				} else {
					cout << "Расшифрованный текст: " << cipher.decrypt(text) << endl;
				}
			} else {
				cout << "Операция не удалась: неверный формат текста" << endl;
			}
		}
	} while (op != 0);
	return 0;
}
