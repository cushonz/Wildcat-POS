# Wildcat-POS

![alt_text](https://github.com/cushonz/Wildcat-POS/blob/main/pics/Wildcat%20spirit%20mark%20facing%20right2-cropped.png)

A simple point of sale system made to be used by [The Central Washington University Wildcat Shop](https://wildcatshop.net/) in place of the traditional POS in the event of an outage during offsite events.

I hope to expand on this and eventually create a user interface.

This project is written in C++ in an effort to keep the program portable, meaning nothing needs to be installed for this program to be run(hopefully) although it is important that it is compiled for you operating system(likely windows).

# Point of Sale Menu

Current Controls Include:

    Q - End transaction/Total out
    U - Undo last item(this can be used in succesion)
    E - End of day (this will write the total sales including tax to the end of the sales file to allow for an easy summary of the sales for the day)

In future versions a menu can be added although I felt this is simple enough at the moment.

# New UI and backend framework

I've refactored the project using .NET and C# to be more compatible with windows machines, I also implemented a UI!

![alt_text](https://github.com/cushonz/Wildcat-POS/blob/main/pics/NewUI.png)
