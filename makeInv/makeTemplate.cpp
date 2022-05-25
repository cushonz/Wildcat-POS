#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
	Author: Zachary Cushon
	
	makeTemplate is a simple way of registering prices and their respective SKU numbers in 
	a controller and guided fashion to ensure that users could reliably create new inventory data
	prior to my graduation as long as good instructions are written.

*/

// Add price to price vector to be unload later

void pushPrice(vector<double>& price)
{
	double dollars;
	cout << "Price:";
	cin >> dollars;			// Push prices into vector
	price.push_back(dollars); 
}

// Add SKU to vector to be unloaded later

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

 // Populate the file with SKUs followed by their prices

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
	// Initialize two empty vectors
	vector<double> price;
	vector<string> SKU;

	int totalItems = -1;
	while (pushSKU(SKU)) // Loop until user inputs escape char, in this case 'Q'
	{
		pushPrice(price);
		totalItems++;
	}
	
	ofstream file("inventory.txt",ios_base::app); // Create output file
	
	// Loop through the price array and unload both price and SKU since they
	for ( int i = 0; i < price.size(); i++)
	{
		file << SKU[i]<<endl;
		file << price[i]<<endl;
	}
	
	file.close();
	
	cout << "Please verify that file was succesfully created in target location." << endl;
}
