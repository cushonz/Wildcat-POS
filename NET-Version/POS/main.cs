using System;
using Transaction;

// Rewriting wildcat POS in C# to be compiled using the .NET framework.
namespace wildcatPOS
{
    class Program
    {

        public static decimal priceLookup(string SKU)
        {
            decimal price;
            using (StreamReader file = new StreamReader("./data/inventory.txt"))
            {
                string line;
                while ((line = file.ReadLine()) != null)
                {
                    if (line.Equals(SKU))
                    {
                        line = file.ReadLine();
                        if (decimal.TryParse(line, out price))
                        {
                            return price;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                }
            }
            return 0;
        }

        static void Main(string[] args)
        {
            // Basic needed variables
            int transID = 0;
            decimal totalSum = 0;
            int items = 0;
            decimal price;
            string SKU;


            // main loop
            while (true)
            {
                transactionData trans = new transactionData(transID);
                List<decimal> total = new List<decimal>();

                while (true)
                {
                    Console.WriteLine("SKU: ");
                    // Scan SKU 
                    SKU = Console.ReadLine();
                    // perform case insensitive comparison
                    switch (SKU.ToUpper())
                    {
                        case "Q":
                            totalSum = totalSum + trans.TermTrans(items, transID);
                            Console.WriteLine("------------------------------");
                            break;
                        case "U":
                            Console.WriteLine("removing SKU: " + trans.Last());
                            trans.RemoveLast();
                            items -= 1;
                            break;
                        case "E":
                            using (StreamWriter skus = new StreamWriter(@"./data/sales.txt", true))
                            {
                                // Write to the file here
                                skus.WriteLine("End of day: $" + totalSum);
                            }
                            break;

                        default:
                            decimal currPrice = priceLookup(SKU);
                            if (currPrice > 0)
                            {
                                Console.WriteLine("$" + currPrice);
                                trans.AddToSKU(SKU);
                                trans.AddToPrice(currPrice);
                                currPrice *= 1.083m;
                                total.Add(currPrice);
                                items++;
                            }
                            else
                            {
                                Console.WriteLine("SKU not found. Would you like to add it? (Y/N)");
                                string dec = Console.ReadLine();
                                if (dec.ToLower() == "y")
                                {
                                    Console.WriteLine("Item price: ");
                                    price = decimal.Parse(Console.ReadLine());
                                    using (StreamWriter inventory = new StreamWriter(@"./data/inventory.txt", true))
                                    {
                                        inventory.WriteLine(SKU);
                                        inventory.WriteLine(price);
                                    }
                                }
                            }
                            break;


                    }

                }
            }

        }
    }
}
