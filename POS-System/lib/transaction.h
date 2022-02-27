#ifndef __Transaction__H__
#define __Transactoin__H__
#include <string>
#include <vector>
using namespace std;
class Transaction
{
public:
	Transaction(int TID);
	
	void addToSKU(string SKU); // Adds SKU's to transaction; items being scanned
	
	void addToPrice(double price); //After price look up add to this value
	
	double priceAdj(double price,string SKU); 	// This method will be overloaded one taking a percent value one taking a dollar amount
	
	double priceLookUp(string SKU);
	
	void removeLast(); // Pulls previous entry from vector(both price and SKU)
	
	//void removeFromOrder(string SKU);
	
	void removeSpecific(string SKU); // Deduct both price and SKU
	
	double totalOrder(); //helper function for termTrans()
	
	double termTrans(int size,int tid);	//Once the last item is scanned this will run
	
	void filePush(double money);
	
	string last();
	
	private:
	int id; 			// ID number so each purchase can be tracked
	vector<double> prices; //Vector that all prices will be stored in
	vector<string> items;
	double tax = 1.083;
	double subtotal;
};
#endif
