namespace Transaction
{
    class transactionData
    {
        // General transaction data
        private int id;
        private decimal subtotal;
        private List<string> items = new List<string>();
        private List<decimal> prices = new List<decimal>();
        private decimal tax = 1.083M;

        // --------------------------------

        public transactionData(int TID)
        {
            id = TID;
            subtotal = 0;
        }

        public void AddToSKU(string SKU)
        {
            items.Add(SKU);
        }

        public decimal PriceAdj(decimal value, string SKU)
        {
            string price = string.Empty;
            decimal numb;

            using (var dict = new StreamReader("dictionary.txt"))
            {
                string line;
                while ((line = dict.ReadLine()) != null)
                {
                    if (line == SKU)
                    {
                        price = dict.ReadLine();
                        break;
                    }
                }
            }

            if (value < 1)
            {
                numb = Convert.ToDecimal(price);
                numb = numb - (numb * value);
                return numb;
            }

            numb = Convert.ToDecimal(price);
            numb -= value;
            return numb;
        }

        public void FilePush(decimal money)
        {
            using (var sales = new StreamWriter("./data/sales.txt", true))
            {
                sales.WriteLine("END OF DAY - Total Sales: $" + money);
            }
        }

        public void RemoveLast()
        {
            items.RemoveAt(items.Count - 1);
        }

        public string Last()
        {
            return items[items.Count - 1];
        }

        public decimal PriceLookUp(string SKU)
        {
            for (int i = 0; i < items.Count; i++)
            {
                if (items[i] == SKU)
                {
                    return prices[i];
                }
            }

            using (var dict = new StreamReader("dictionary.txt"))
            {
                string line;
                while ((line = dict.ReadLine()) != null)
                {
                    if (line == SKU)
                    {
                        dict.ReadLine();
                        return Convert.ToDecimal(dict.ReadLine());
                    }
                }
            }

            return 0;
        }

        public void AddToPrice(decimal price)
        {
            prices.Add(price);
        }

        public decimal TermTrans(int size, int transID)
        {
            Console.WriteLine("Transaction #" + transID);
            using (StreamWriter skus = new StreamWriter("./data/sales.txt", true))
            {
                decimal subt = TotalOrder();
                for (int i = 0; i < size; i++)
                    skus.WriteLine(items[i] + "      $" + prices[i].ToString("F2"));
                skus.WriteLine("$" + subt.ToString("F2") + " x 1.083");
                Console.WriteLine("Subtotal: $" + subt.ToString("F2"));
                subt *= tax;
                skus.WriteLine("$" + subt.ToString("F2"));
                skus.WriteLine("Transaction ID: " + transID);
                skus.WriteLine("Total: $" + subt.ToString("F2"));
                return subt;
            }
        }

        private decimal TotalOrder()
        {
            decimal subtotal = 0;
            foreach (decimal price in prices)
            {
                subtotal += price;
            }
            return subtotal;
        }

    }
}