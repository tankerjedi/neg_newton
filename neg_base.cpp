#include <stdio.h>
#include <math.h>
#include <stdlib.h>



#include "neg_base.h"



int main(int argc, char * argv[])
{
printf("Parameters: w1, w2, slambda (iteration parameters), T, lambda,sigma (modells parameters)\n");
printf("Simulation starts\n");

//printf("Wage in region1 is: %4.2f\n",wage_region1( income_region1(1), income_region2(1), price_index_region1(1,1), price_index_region2(1,1)));

//printf("Price in region1 is by (1,1): %4.2f\n", price_index_region1(1,1));

//printf("Value of goal function: %4.10f\n",goal_function(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

//printf("Value of dL/dw1: %4.2f\n", dwage_region1(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

//printf("Value of dL/dw2: %4.2f\n", dwage_region2(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

//printf("Value of dL/dG1: %4.2f\n", dprice_index_region1(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));

//printf("Value of dL/dG2: %4.2f\n", dprice_index_region2(1.1,1.1,price_index_region1(1.1,1.1),price_index_region2(1.1,1.1)));


//bemeneti érték vizsgálat és kiíratás
//char * vege;
if (argc > 1) {w1 = atof(argv[1]);}
if (argc > 2) {w2 = atof(argv[2]);}
if (argc > 3) {steplambda1 = atof(argv[3]);}
if (argc > 4) {T = atof(argv[4]);}
if (argc > 5) {lambda = atof(argv[5]);}
if (argc > 6) {sigma = atof(argv[6]);}
//printf("__________________________Lambda paraméter: %f\n", s3lambda);


solve();

return 0;
}

//Equations


//Base modell - original equations

double income_region1(double wage1)
{
return mu * lambda * wage1 + (1 - mu) / 2;
};

double income_region2(double wage2)
{
return mu * (1 - lambda) * wage2 + (1 - mu) / 2;
};

double price_index_region1(double wage1, double wage2)
{
return pow(lambda * pow(wage1, 1 - sigma) + (1 - lambda) * pow(wage2 * T, 1 - sigma),(1 / (1 - sigma)));
};

double price_index_region2(double wage1, double wage2)
{
return pow(lambda * pow(wage1 * T, 1 - sigma) + (1 - lambda) * pow(wage2, 1 - sigma),(1 / (1 - sigma)));
};

double wage_region1(double income1, double income2, double price_index1, double price_index2)
{
return pow(income1 * pow(price_index1, sigma - 1) + income2 * pow(price_index2 / T, sigma -1),(1 /  sigma));
};

double wage_region2(double income1, double income2, double price_index1, double price_index2)
{ 
return pow(income1 * pow(price_index1 / T, sigma - 1) + income2 * pow(price_index2 , sigma -1),(1 /  sigma));
};

double real_wage_region1(double wage1, double price_index1)
{
return wage1 * pow(price_index1, -mu);
};

double real_wage_region2(double wage2, double price_index2)
{
return wage2 * pow(price_index2, -mu);
};

//simplified equations


double new_wage_region1(double wage1, double wage2)
{
return pow(income_region1(wage1) * pow(price_index_region1(wage1,wage2), sigma - 1) + income_region2(wage2) * pow(price_index_region2(wage1,wage2) / T, sigma -1),(1 /  sigma));
};

double new_wage_region2(double wage1, double wage2)
{ 
return pow(income_region1(wage1) * pow(price_index_region1(wage1,wage2) / T, sigma - 1) + income_region2(wage2) * pow(price_index_region2(wage1,wage2) , sigma -1),(1 /  sigma));
};

//Dinamics

double average_real_wage(double real_wage1, double real_wage2)
{
return 0;
};

double new_lamda(double average_real_wage0, double real_wage1) //The value of the population share in the next
{
return 0;

};

//Derivatives


double d1new_wage_region1(double wage1, double wage2)
{
return pow(income_region1(wage1) * pow(price_index_region1(wage1,wage2), sigma - 1) + income_region2(wage2) * pow(price_index_region2(wage1,wage2) / T, sigma -1),(1 /  sigma));
};

double d2new_wage_region1(double wage1, double wage2)
{
return pow(income_region1(wage1) * pow(price_index_region1(wage1,wage2), sigma - 1) + income_region2(wage2) * pow(price_index_region2(wage1,wage2) / T, sigma -1),(1 /  sigma));
};

double d1new_wage_region2(double wage1, double wage2)
{ 
return pow(income_region1(wage1) * pow(price_index_region1(wage1,wage2) / T, sigma - 1) + income_region2(wage2) * pow(price_index_region2(wage1,wage2) , sigma -1),(1 /  sigma));
};

double d2new_wage_region2(double wage1, double wage2)
{ 
return pow(income_region1(wage1) * pow(price_index_region1(wage1,wage2) / T, sigma - 1) + income_region2(wage2) * pow(price_index_region2(wage1,wage2) , sigma -1),(1 /  sigma));
};

//solver

double solve()
{
//változók kezdeti értékei
int i;
double cpi1 = price_index_region1(w1,w2);
double cpi2 = price_index_region2(w1,w2);
double dw1, dw2, dcpi1, dcpi2;

//fejléc
printf("Iteráció \t w1 \t dw1 \t w2 \t dw2 \t g1 \t dg1 \t  g2 \t  dg2 \t jöv1 \t jöv2 \t célérték\n");


//fájl megnyitás

FILE * pFile;
pFile = fopen ( "neg.txt" , "w" );
fprintf(pFile,"Iteráció \t w1 \t dw1 \t w2 \t dw2 \t g1 \t dg1 \t  g2 \t  dg2 \t jöv1 \t jöv2 \t célérték\n");

//Kezdeti értékek


//printf("%3d \t %f \t %f \t %f \t %f \t %f \t  %f \t %f \t %f \t %f \t %f \t %f\n",0,w1,dwage_region1(w1,w2,cpi1,cpi2),w2,dwage_region2(w1,w2,cpi1,cpi2),cpi1,dprice_index_region1(w1,w2,cpi1,cpi2),cpi2,dprice_index_region2(w1,w2,cpi1,cpi2),income_region1(w1),income_region2(w2),goal_function(w1,w2,cpi1,cpi2));

//fprintf(pFile,"%3d \t %f \t %f \t %f \t %f \t %f \t  %f \t %f \t %f \t %f \t %f \t %f\n",0,w1,dwage_region1(w1,w2,cpi1,cpi2),w2,dwage_region2(w1,w2,cpi1,cpi2),cpi1,dprice_index_region1(w1,w2,cpi1,cpi2),cpi2,dprice_index_region2(w1,w2,cpi1,cpi2),income_region1(w1),income_region2(w2),goal_function(w1,w2,cpi1,cpi2));

//szovegesfajl << "Iteráció \t w1 \t dw1 \t w2 \t dw2 \t g1 \t dg1 \t  g2 \t  dg2 \t jöv1 \t jöv2 \t célérték\n";

for(i = 1; i <= iteration_limit; i++)
{
//derivált értékek
//dw1 = dwage_region1(w1,w2,cpi1,cpi2);
//dw2 = dwage_region2(w1,w2,cpi1,cpi2);
//dcpi1 = dprice_index_region1(w1,w2,cpi1,cpi2);
//dcpi2 = dprice_index_region2(w1,w2,cpi1,cpi2);

//pontok kiszámítása
//w1 = w1 + steplambda1 * dw1;
//w2 = w2 + steplambda1 * dw2;
//cpi1 = cpi1 + steplambda2 * dcpi1;
//cpi2 = cpi2 + steplambda2 * dcpi2;

//célfüggvény érékének kiíratása
//printf("A célfüggvény értéke %2.50f \n",goal_function(w1,w2,cpi1,cpi2));

//printf("%3d \t %f \t %f \t %f \t %f \t %f \t  %f \t %f \t %f \t %f \t %f \t %f\n",i,w1,dwage_region1(w1,w2,cpi1,cpi2),w2,dwage_region2(w1,w2,cpi1,cpi2),cpi1,dprice_index_region1(w1,w2,cpi1,cpi2),cpi2,dprice_index_region2(w1,w2,cpi1,cpi2),income_region1(w1),income_region2(w2),goal_function(w1,w2,cpi1,cpi2));

//fprintf(pFile,"%3d \t %f \t %f \t %f \t %f \t %f \t  %f \t %f \t %f \t %f \t %f \t %f\n",i,w1,dwage_region1(w1,w2,cpi1,cpi2),w2,dwage_region2(w1,w2,cpi1,cpi2),cpi1,dprice_index_region1(w1,w2,cpi1,cpi2),cpi2,dprice_index_region2(w1,w2,cpi1,cpi2),income_region1(w1),income_region2(w2),goal_function(w1,w2,cpi1,cpi2));
//szovegesfajl << i << "\t" << w1 << "\t" <<  dwage_region1(w1,w2,cpi1,cpi2) << "\t" << w2 << "\t" << dwage_region2(w1,w2,cpi1,cpi2) << "\t"<< cpi1 << "\t" << dprice_index_region1(w1,w2,cpi1,cpi2) << "\t" << cpi2 << "\t" << dprice_index_region2(w1,w2,cpi1,cpi2) << "\t" << income_region1(w1) << "\t" << income_region2(w2) << "\t" << goal_function(w1,w2,cpi1,cpi2) << "\n";
}

//Fájl bezárása
fclose (pFile);

}
