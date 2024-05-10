#define NOMINMAX
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <limits>
#include <algorithm>

using namespace std;

string fileName() 
{
	static bool firstCall = true;
	if(!firstCall)
	{
		cin.ignore();
	}
	firstCall = false;

	cout << "Please enter a filename: \n";
	string file;
	getline(cin, file);

	file += ".txt";

	return file;
}

string readOrWrite()
{
	cout << "Would you like to read or write? \n";
	string readWrite;
	cin >> readWrite;
	transform(readWrite.begin(), readWrite.end(), readWrite.begin(), ::tolower);

	return readWrite;
}

bool fileExists(const string& filename)
{
	ifstream file(filename.c_str());
	return file.good();
}

int main()
{
	bool editing = true;
	while(editing == true){
	string filename{ fileName() };

	if (!fileExists(filename))
	{
		string CreateNewFile;
		cout << "Warning! No file exists with the name \"" << filename << "\"! Would you like to create a new file with that name?\n";
		cin >> CreateNewFile;
		transform(CreateNewFile.begin(), CreateNewFile.end(), CreateNewFile.begin(), ::tolower);
		cin.ignore();

		do {
			if (CreateNewFile != "yes" && CreateNewFile != "no")
			{
				string check;
				cout << "That is not a valid response. Please enter \"yes\" or \"no\". \n";
				cin >> CreateNewFile;
				transform(CreateNewFile.begin(), CreateNewFile.end(), CreateNewFile.begin(), ::tolower);
				cin.ignore();
			}

		} while (CreateNewFile != "yes" && CreateNewFile != "no");

		if (CreateNewFile == "yes") 
		{
			ofstream myFile(filename);
			myFile.open(filename);
		}
		else if(CreateNewFile == "no")
		{
			cout << "Opening a default file\n";
			filename = "Default.txt";
			ofstream myFile(filename);
			myFile.open(filename);
		}
	}
	string readWrite{ readOrWrite() };

	do {
		if (readWrite != "write" && readWrite != "read")
		{
			string check;
			cout << "That is not a valid response. Please enter \"read\" or \"write\". \n";
			cin >> readWrite;
		}

	} while (readWrite != "write" && readWrite != "read");

	system("cls");

	if (readWrite == "write")
	{
		bool writing{ true };
		string continueWriting;
		string readCheck;

		do {
			string myText;
			ofstream myFile;
			myFile.open(filename, ios::app);

			cout << "Please enter your text: \n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, myText);
			myFile << myText << '\n';

			system("cls");

			cout << "Text added. Would you like to add more? ";
			cin >> continueWriting;
			cin.ignore();
			transform(continueWriting.begin(), continueWriting.end(), continueWriting.begin(), ::tolower);
			do
			{
				if (continueWriting != "yes" && continueWriting != "no") {
					cout << "That response is not valid. Please enter \"yes\" or \"no\" \n";
					cin >> continueWriting;
					cin.ignore();
					transform(continueWriting.begin(), continueWriting.end(), continueWriting.begin(), ::tolower);
				}
			} while (continueWriting != "yes" && continueWriting != "no");
			
			if (continueWriting == "yes")
			{
				writing = true;
			}
			else if (continueWriting == "no")
			{
				writing = false;
				myFile.close();

				cout << "File closed. Would you like to read the file? \n";
				cin >> readCheck;
				transform(readCheck.begin(), readCheck.end(), readCheck.begin(), ::tolower);
				do
				{
					if (readCheck != "yes" && readCheck != "no"){
					cout << "That response is not valid. Please enter \"yes\" or \"no\" \n";
					cin >> readCheck;
					transform(readCheck.begin(), readCheck.end(), readCheck.begin(), ::tolower);
					}
				} while (readCheck != "yes" && readCheck != "no");
				if (readCheck == "yes")
				{
					readWrite = "read";
					system("cls");
				}
				else if (readCheck == "no")
				{
				}
			}
		} while (writing == true);
	}

	if (readWrite == "read")
	{
		if (fileExists(filename))
		{
			string text;
			ifstream MyFile(filename, ios::app);
			while (getline(MyFile, text)) {
				cout << text << '\n';
			}
			cout << '\n';
			Sleep(2500);
		}
		else
		{
			cout << filename <<" does not exist. Create it yourself, or alternatively use the \"write\" function. \n";
			Sleep(5000);
		}
	}
	string repeat{};
	cout << "Would you like to use another file? \n";
	cin >> repeat;
	transform(repeat.begin(), repeat.end(), repeat.begin(), ::tolower);
	do {
		if (repeat != "yes" && repeat != "no")
		{
			cout << "That is not a valid response. Please enter \"yes\" or \"no\". \n";
			cin >> repeat;
			transform(repeat.begin(), repeat.end(), repeat.begin(), ::tolower);
			cin.ignore();
		}

	} while (repeat != "yes" && repeat != "no");

		if (repeat == "yes")
		{
			editing = true;
		}
		else if (repeat == "no")
		{
			editing = false;
		}

	}
	system("pause");

	return 0;
}