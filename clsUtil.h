#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsDate.h";
using namespace std;

class clsUtil
{
public:
	static void Srand() {
		srand((unsigned)time(NULL));
	}
	static int RandomNumber(int from, int to) {
		int result = rand() % (to - from + 1) + from;
		return result;
	}
	static enum enCharType { SamallLetter = 1, CapitalLetter = 2, Digit = 3, MixChars = 4 };
	static char GetRandomCharactor(enCharType CharType) {
		switch (CharType) {
		case enCharType::SamallLetter:
			return char(RandomNumber(97, 122));
		case enCharType::CapitalLetter:
			return char(RandomNumber(65, 90));
		case enCharType::MixChars:
			return char(RandomNumber(48, 122));
		case enCharType::Digit:
			return char(RandomNumber(48, 57));
		}
	}
	static string GenerateWord(enCharType CharType, short Length) {
		string World;
		for (int i = 1; i <= Length; i++) {
			World += GetRandomCharactor(CharType);
		}
		return World;
	}
	static string GenerateKey(enCharType CharType) {
		string Key = "";
		Key = GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4);
		return Key;
	}
	static void GenerateKeys(short NumberOfKeys, enCharType CharType) {
		for (int i = 1; i <= NumberOfKeys; i++)
			cout << "Key [" << i << "] : " << GenerateKey(CharType) << endl;
	}
	static void Swap(int& A, int& B) {
		int Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(double& A, double& B) {
		double Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(string& A, string& B) {
		string Temp;
		Temp = A;
		A = B;
		B = Temp;
	}
	static void Swap(clsDate& Date, clsDate& Date2) {
		clsDate temp;
		temp = Date;
		Date = Date2;
		Date2 = temp;
	}
	static void PrintArray(int arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
	static void PrintArray(double arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
	static void PrintArray(string arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
	static void ShuffleArray(int arr[100], int arrlength) {
		for (int i = 0; i < arrlength; i++) {
			Swap(arr[RandomNumber(1, arrlength) - 1], arr[RandomNumber(1, arrlength) - 1]);
		}
	}
	static void ShuffleArray(string arr[100], int arrlength) {
		for (int i = 0; i < arrlength; i++) {
			Swap(arr[RandomNumber(1, arrlength) - 1], arr[RandomNumber(1, arrlength) - 1]);
		}
	}
	static void FillArrayWithRandomNumbers(int arr[100], int arrlength, int from, int to) {
		for (int i = 0; i < arrlength; i++)
			arr[i] = RandomNumber(from, to);
	}
	static void FillArrayWithRandomWords(string  arr[100], int arrlength, int from, int to) {
		for (int i = 0; i < arrlength; i++)
			arr[i] = RandomNumber(from, to);
	}
	static void FillArrayWithRandomKeys(string  arr[100], int arrlength, enCharType CharType) {
		for (int i = 0; i < arrlength; i++)
			arr[i] = GenerateKey(CharType);
	}
	static string Tabs(int Number) {
		string x = "";
		for (int i = 0; i < Number; i++)
			x += "\t";
		return x;
	}
	static string EncryptText(string Text, short EncryptionKey) {
		for (int i = 0; i <= Text.length(); i++) {
			Text[i] = char((int)Text[i] + EncryptionKey);
		}
		return Text;
	}
	static string DecrypText(string Text, short EncryptionKey) {
		for (int i = 0; i <= Text.length(); i++) {
			Text[i] = char((int)Text[i] - EncryptionKey);
		}
		return Text;
	}

};
