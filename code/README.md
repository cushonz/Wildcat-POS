Program instructions
-------------------------
This program works by scanning SKUs and searching for them in a designated price index file labeled "inventory.txt" , if this file does not exist with this exact naming the program will make its own and populate it as SKUs and prices are added.

Upon succesfully looking up a price the SKU will be added to the customers transaction and the found price will be added, items can be scanned until the customer no longer has more items at which point Q/q can be inputed for SKU to end the transaction

Once the transaction ends the SKUs, prices,subtotal,total, and transaction id will be saved to sales.txt

if the program fails to find the specified SKU the option to add it to inventory.txt will be presented, I believe this will help in the event that a slight variation in SKU won't cause a complete meltdown or hold up.

In it's current form this program is imperfect although is certainly better than nothing. I plan to continue working on the code and expanding upon it as needed to make things convenient for supervisors who will be handling both the software and the data collected from it.




Current additional options include 
-----------------------------------
Q - end transaction/total out
U - Undo one item previous(this will work to "remove the last x items")
E - End of Day(final transactoin must be closed) this will write the total sales including tax to the end of the sales file to allow for an easy summary of the sales for the day

NOTE:
This program is unfinished and has not been tested with all possible cases, please notify me of any glitches or issues that might be found and I will fix them promptly :)
