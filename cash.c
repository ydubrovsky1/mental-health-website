#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main(void)
{
   float change;
   do {
       change = get_float("how much change?\n");
   }
   while (change < 0);
   int changetotal = round(change * 100);
    
    
    //obtained change now lets count up the dollars and coins
    
    int cents = changetotal;
    int dollars = 0;
    
    while (cents > 99)
    {cents = cents - 100;
    dollars = dollars + 1;
    }
    
    //took out and counted dollars, remaining amount is all coins
    
    int dnponly = cents;
    int quarters = 0;
    
    while (dnponly > 24)
   {dnponly = dnponly - 25;
   quarters = quarters + 1;}
   
   //took out and counted quarters; dimes, nickels and pennies remain
   
   int nponly = dnponly;
   int dimes = 0;
   
   while (nponly > 9)
   {nponly = nponly - 10;
   dimes = dimes + 1; }
   
   //took out and counted dimes; nickels and pennies remain
   
   int ponly = nponly;
   int nickels = 0;
   
   while (ponly > 4)
   {ponly = ponly - 5;
   nickels = nickels +1; }
   
   //took out and counted nickels. pennies remain
   
   int only = ponly;
   int pennies = 0;
   
   while (only > 0)
   { only = only - 1;
   pennies = pennies +1; }
   
   //took out and counted all coins. Time to add up the total number of coins
   
   int total = pennies + nickels + dimes + quarters;

printf("dollars: %i\n", dollars);    
printf("quarters: %i\n", quarters);
printf("dimes: %i\n", dimes);
printf("nickels: %i\n", nickels);
printf("pennies: %i\n", pennies);
printf("total coins: %i\n", total);
printf("%i\n", total);
}
    
    