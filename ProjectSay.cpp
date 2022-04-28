// ProjectSay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <math.h> 
using namespace std;

int CountWords(string line, int sum, int word);
int CountSyllables(int word, string line);
int CountSentences(string line);
string RemovePunctuation(string line);

int main()
{
	string line;
	int word{ 0 };
	int sum{ 0 };
	int index{ 0 };
	string filename;
	ifstream Data;
	do {
		cout << "\nPlease enter name of file to read from " << endl;
		cin >> filename;
		Data.open(filename);
	} while (Data.fail());
	if (Data.is_open())
	{
		while (!Data.eof())
		{
			getline(Data, line);
		}
	}

	cout << "\nWord Count: " << CountWords(line, sum, word);
	cout << "\n\nSentence Count: " << CountSentences(line);
	cout << "\n\nSyllable Count: " << CountSyllables(word, line);

	index = floor(206.835 - 84.6 *
		((float)CountSyllables(word, line) /
		(float)CountWords(line, sum, word)) - 1.015 *
		((float)CountWords(line, sum, word) /
		(float)CountSentences(line)) + 0.5);
	cout << "\n\nReadability Index: " << index << endl;
	Data.close();

	return 0;
}

int CountWords(string line, int sum, int word)
{
	int numofChars = line.length();
	for (unsigned int n = 0; n < line.length(); n++)
	{
		if (line.at(n) == '.' || line.at(n) == ',' || line.at(n) == '?' ||
			line.at(n) == '!' || line.at(n) == ':' || line.at(n) == ';')
		{
			numofChars--;
		}
		if (line.at(n) == ' ')
		{
			word++;
		}
	}
	line = RemovePunctuation(line);

	if (line[line.length() - 1])
	{
		word++;
	}

	sum = numofChars + sum;
	return word;
}

int CountSentences(string line)
{
	int sentence{ 0 };
	for (unsigned int n = 0; n < line.length(); n++)
	{
		if (line.at(n) == '.' || line.at(n) == '?' || line.at(n) == '!' ||
			line.at(n) == ':' || line.at(n) == ';')
		{
			sentence++;
		}
	}
	return sentence;
}

string RemovePunctuation(string line)
{
	for (int i = 0, len = line.size(); i < len; i++)
	{
		if (ispunct(line[i]))
		{
			line.erase(i--, 1);
			len = line.size();
		}
	}
	//cout << "\n\nLine: " << line;
	return line;
}

int CountSyllables(int word, string line)
{
	const string vowels = "AEIOUY";
	vector<string>vect ={ "aa", "ee","oo","au","ea","ie",
						  "ai","oa","eo","oi","ou","ui" };
	int syllable{ 0 };
	string str = RemovePunctuation(line);
	istringstream linestream(str);
	string words;

	for (unsigned int n = 0; n < line.length(); n++)
	{
		if (vowels.npos != vowels.find(toupper(line.at(n))))
		{
			syllable++;
		}
		while (linestream >> words)
		{
			if (words.back() == 'e')
			{
				syllable--;
			}
		}
	}

	bool found = any_of(vect.begin(), vect.end(), [&line](const auto& s) 
		{return line.find(s) != string::npos; });
	if (found)
	{
		syllable--;
	}

	return syllable;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
