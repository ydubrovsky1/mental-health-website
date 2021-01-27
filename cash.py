from cs50 import get_float

# get change total from user
change = get_float("Change owed: ")
while change < 0: 
    change = get_float("Change owed: ")

# determine number of quarters
quarters = 0
while (change - .25) >= 0.00:
    quarters += 1
    change -= .25
    
# determine dimes
dimes = 0
while (change -.10) >= 0.00:
    dimes += 1
    change -= .10

# determine nickels
nickels = 0
while (round(change, 2) -.05) >= 0.00:
    nickels += 1
    change -= .05

# determine pennies
pennies = 0
while (round(change, 2) - .01) >= 0.00:
    pennies += 1
    change -= .01
    
# print total coins
total = quarters + dimes + nickels + pennies
print(total)