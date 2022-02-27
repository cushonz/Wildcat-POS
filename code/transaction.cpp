
#include <iostream>
#include <fstream>
#include "transaction.h"
#include <vector>
#include <iomanip>
using namespace std;

Transaction :: Transaction(int TID)
{
	id = TID;
	subtotal = 0;
}

void Transaction :: addToSKU(string SKU)
{
	items.push_back(SKU); // Directly access items vector
}

double Transaction :: priceAdj(double value,string SKU)
{
		ifstream dict("dictionary.txt"); 
		string price;
		double numb;
		
		for (string line; getline(dict,line);)
			if (line.compare(SKU) == 0)
				getline(dict,price);
				
		if (value < 1)
		{
			numb = stod(price);
			numb = numb - (numb*value);
			return (numb);
		}
		
 		
 	
		numb = stod(price);
		numb -= value; // if value is greater than one do price mark down
		return numb;
}

void Transaction :: filePush(double money)
{
	ofstream sales("sales.txt",ios_base::app);
	sales << "Total Sales: $" << money <<endl;
}

void Transaction :: removeLast()
{
	items.pop_back();
}

string Transaction :: last()
{
	return items.back();
}

double Transaction :: priceLookUp(string SKU) // Might be useful to cast to double
{
	for (int i = 0; i < items.size(); i++)
		if (items[i].compare(SKU) == 0)
			return prices[i];
		
	ifstream dict("dictionary.txt");
	for (string line; getline(dict,line); )
	{
		if (line.compare(SKU) == 0)
			getline(dict,line);
			getline(dict,line);
			return stod(line);	//Return line following SKU which should be the price
	}
	return 0;
	
}


void Transaction :: addToPrice(double price)
{
	prices.push_back(price);	// Directly access price vector
}

void Transaction :: termTrans(int size,int transID)
{
	cout << "Transaction #" << transID <<endl;
	ofstream skus("sales.txt",ios_base::app);
	double subt = totalOrder();
	for (int i = 0; i < size; i++)
		skus << items[i]<<"      $"<<prices[i]<<endl;				// unload SKU's in transaction file
		skus << "$" << subt << " x 1.083"<<endl;			// append sub total after list of SKU's
	    cout << "Subtotal: $" << setprecision(3) << subt <<endl;
		subt *= tax;							// write total prior to tax calculation
		skus <<"$"<< setprecision(3) <<subt << endl;
		skus << "Transaction ID: "<< transID<<endl;			// write newly updated total after subtotal
		cout <<"Total:"<< "$" << setprecision(3) <<subt<<endl;
}

double Transaction :: totalOrder()
{
	for (int i = 0; i < prices.size(); i++)
		subtotal+= prices[i];
	return subtotal;
}

