
#include <iostream>
#include <fstream>
#include "transaction.h"
#include <vector>
#include <iomanip>
using namespace std;

// Constructor
Transaction :: Transaction(int TID){
	id = TID;
	subtotal = 0;
}


void Transaction :: addToSKU(string SKU){
	items.push_back(SKU); // Directly access items vector
}


/* This method is responsible for items that may be on sale or 
	in the event the customer has a coupon
 */

double Transaction :: priceAdj(double value,string SKU){
		ifstream dict("dictionary.txt"); 
		string price;
		double numb;
		
		for (string line; getline(dict,line);)
			if (line.compare(SKU) == 0)
				getline(dict,price);
		if (value < 1){
			numb = stod(price);
			numb = numb - (numb*value);
			return (numb);
		}
		
 		
 	
		numb = stod(price);
		numb -= value; // if value is greater than one do price mark down
		return numb;
}

// This will append the end of day report to the end of the sales history
void Transaction :: filePush(double money){
	ofstream sales("./data/sales.txt",ios_base::app);
	sales << "END OF DAY - Total Sales: $" << money <<endl;
}

// For indecisive customers
void Transaction :: removeLast(){
	items.pop_back();
}

// Provides the last item
string Transaction :: last(){
	return items.back();
}

// Retrive the price of an item by SKU # for price Inquiry
double Transaction :: priceLookUp(string SKU) // Might be useful to cast to double
{
	for (int i = 0; i < items.size(); i++)
		if (items[i].compare(SKU) == 0)
			return prices[i];
		
	ifstream dict("dictionary.txt");
	for (string line; getline(dict,line); ){
		if (line.compare(SKU) == 0)
			getline(dict,line);
			getline(dict,line);
			return stod(line);	//Return line following SKU which should be the price
	}
	return 0;
	
}

// Add to running total
void Transaction :: addToPrice(double price){
	prices.push_back(price);	// Directly access price vector
}

// Total out transaction and save important data to file
double Transaction :: termTrans(int size,int transID){
	cout << "Transaction #" << transID <<endl;
	ofstream skus("./data/sales.txt",ios_base::app);
	double subt = totalOrder();
	for (int i = 0; i < size; i++)
		skus << items[i]<<"      $"<<prices[i]<<endl;				// unload SKU's in transaction file
		skus << "$" << subt << " x 1.083"<<endl;			// append sub total after list of SKU's
	    cout << "Subtotal: $" << setprecision(3) << subt <<endl;
		subt *= tax;							// write total prior to tax calculation
		skus <<"$"<< setprecision(3) <<subt << endl;
		skus << "Transaction ID: "<< transID<<endl;			// write newly updated total after subtotal
		skus <<"Total:"<< "$" << setprecision(3) <<subt<<endl;
		return subt;
}

// Total up price vector
double Transaction :: totalOrder(){
	for (int i = 0; i < prices.size(); i++)
		subtotal+= prices[i];
	return subtotal;
}

