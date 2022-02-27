# Wildcat-POS

![alt_text](https://github.com/cushonz/Wildcat-POS/blob/main/pics/Wildcat%20spirit%20mark%20facing%20right2-cropped.png)


A simple point of sale system made to be used by [The Central Washington University Wildcat Shop](https://wildcatshop.net/) in place of the traditional POS in the event of an outage during offsite events.

# Point of Sale Menu


Current Controls Include:

	Q - End transaction/Total out
	U - Undo last item(this can be used in succesion)
	E - End of day (this will write the total sales including tax to the end of the sales file to allow for an easy summary of the sales for the day)
	

In future versions a menu can be added although I felt this is simple enough at the moment.

# Missing SKU?

In the event of a missing SKU the cashier will be given the opportunity to add the item to the database, the danger in this is that all future sales of this SKU will be based off of this price, meaning its important that it is put in carefully and correctly. 

Here is an example of what happens upon scanning an unknown  SKU:

	![alt_text](https://github.com/cushonz/Wildcat-POS/blob/main/pics/cashier-view.png)
	
Notice after dding the SKU to the database the customer still had to be rung up for the SKU.

	



