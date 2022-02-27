#include "transaction.cpp"
#include <iostream>
#include <vector>
using namespace std;

double priceLookup(string SKU)
{
	ifstream file("./data/inventory.txt");
	string line;
	while (!file.eof())
	{
		getline(file,line);
		if (line.compare(SKU) == 0)
		{
			getline(file,line);
			double price = stod(line);
			file.close();
			return price;
		}
	}
	file.close();
	return 0;
}

int main()
{
	int transID = 0;
	double totalSum = 0;
	int items;
	double price;
	string SKU;
	
	while (true) 
	{
		Transaction trans(transID);
		vector<double> total;
		
		items = 0;
		while (true)
		{
			cout << "SKU:";
			cin >> SKU;
			if (SKU.compare("q") == 0 || SKU.compare("Q") == 0) // "Is that everything"
			{
				totalSum = totalSum + trans.termTrans(items,transID);
				break;
			}
			else if (SKU.compare("u") == 0 || SKU.compare("U") == 0) // "Can you take that last one off?"
			{
				cout << "removing SKU: " << trans.last()<<endl;
				trans.removeLast();
				items-=1;
			}
			else if (SKU.compare("e") == 0 || SKU.compare("E") == 0) // "End of day?"
			{
				ofstream skus("sales.txt",ios_base::app);
				cout << endl << "Running end of day..." << endl;
				skus<<"End of day: $" << setprecision(3) <<totalSum;
			}
			else
			{
				
				
				price = priceLookup(SKU);
				if (price > 0)		//if SKU is not in system, you arent stuck.
				{
					cout << "$"<<price<<endl;
					trans.addToSKU(SKU);
					trans.addToPrice(price);
					price*=1.083;
					total.push_back(price);
					items++;
				}
				else
				{
					string dec;
					cout << "SKU not found. would you like to add it?(Y/N)"<<endl;  //managers only?
					cin >> dec;
					if (dec.compare("y") == 0 || dec.compare("Y") == 0)
					{
						cout << "item price: ";
						cin >> price;
						ofstream inventory("inventory.txt",ios_base::app);
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
