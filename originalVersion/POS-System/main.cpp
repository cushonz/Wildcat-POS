#include "./lib/transaction.cpp"
#include <iostream>
#include <vector>
using namespace std;


/* A method responsible for retriving the price of a given SKU 
  perfect for customers who would like to know the price of an item

	'Price Inquiry'
*/
double priceLookup(string SKU){
	ifstream file("./data/inventory.txt");
	string line;
	while (!file.eof()){
		getline(file,line);
		if (line.compare(SKU) == 0){
			getline(file,line);
			double price = stod(line);
			file.close();
			return price;
		}
	}
	file.close();
	return 0;
}

int main(){
	// Assign each customer a transaction ID
	// to be used when the EOD report is generated
	int transID = 0;
	double totalSum = 0;
	int items;
	double price;
	string SKU;
	
	while (true) {
		// Create a transaction object
		Transaction trans(transID);
		// Running total for transaction
		vector<double> total;
		
		items = 0;
		while (true){
			cout << "SKU:";
			cin >> SKU;
			if (SKU.compare("q") == 0 || SKU.compare("Q") == 0) {
				totalSum = totalSum + trans.termTrans(items,transID);
				cout<<"--------------------------"<<endl;
				cout<<endl;
				break;
			}
			else if (SKU.compare("u") == 0 || SKU.compare("U") == 0) { // Remove the previous item
				cout << "removing SKU: " << trans.last()<<endl;
				trans.removeLast();
				items-=1;
			}
			else if (SKU.compare("e") == 0 || SKU.compare("E") == 0) {// Run end of day
				ofstream skus("./data/sales.txt",ios_base::app);
				cout << endl << "Running end of day..." << endl;
				skus<<"End of day: $" << setprecision(3) <<totalSum<<endl;
			} else{				
				price = priceLookup(SKU);
				if (price > 0){	//if SKU is not in system, you arent stuck AND nothing goes out free
					cout << "$"<<price<<endl;
					trans.addToSKU(SKU);
					trans.addToPrice(price);
					price*=1.083;
					total.push_back(price);
					items++;
				}else{
					string dec;
					cout << "SKU not found. would you like to add it?(Y/N)"<<endl;  // Considering restricting with pin
					cin >> dec;
					if (dec.compare("y") == 0 || dec.compare("Y") == 0){
						cout << "item price: ";
						cin >> price;
						ofstream inventory("./data/inventory.txt",ios_base::app);
						inventory << SKU << endl;
						inventory << price << endl;
					}
				}
			}
		}
		transID++;
	}
	
	return 0;
}
