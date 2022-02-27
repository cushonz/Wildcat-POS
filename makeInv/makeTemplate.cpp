#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void pushPrice(vector<double>& price)
{
	double dollars;
	cout << "Price:";
	cin >> dollars;			// Push prices into vector
	price.push_back(dollars); 
}

bool pushSKU(vector <string>& SKU)
{
	string SKUL;
	cout << "SKU:";
	cin >> SKUL;			// Push prices into vector
	if (SKUL.compare("Q") == 0 || SKUL.compare("q") == 0)
		return false;
	else
		SKU.push_back(SKUL); 
	return true;
}

void filePop(vector <double> prices, vector<string>& SKUs, string filename, int numb)
{
	ofstream file(filename);
	if (numb > -1)
	{
	file << SKUs[numb]<<endl;
	file << prices[numb]<<endl;
	filePop(prices,SKUs,"inventory.txt", numb-1);
	}
	file.close();
}

int main()
{
	vector<double> price;
	vector<string> SKU;
	int totalItems = -1;
	while (pushSKU(SKU))
	{
		pushPrice(price);
		totalItems++;
	}
	
	ofstream file("inventory.txt",ios_base::app);
	
	for ( int i = 0; i < price.size(); i++)
	{
		file << SKU[i]<<endl;
		file << price[i]<<endl;
	}
	
	file.close();
	
	cout << "Please verify that file was succesfully created in target location." << endl;
}
