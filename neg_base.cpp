#include <stdio.h>
#include <math.h>
#include <stdlib.h>



#include "neg_base.h"



int main(int argc, char * argv[])
{
printf("Parameters: w1, w2, T, lambda, sigma, mu, iteration limit\n");
printf("Simulation starts\n");


//bemeneti érték vizsgálat és kiíratás
//char * vege;
if (argc > 1) {w1 = atof(argv[1]);}
if (argc > 2) {w2 = atof(argv[2]);}
if (argc > 3) {T = atof(argv[3]);}
if (argc > 4) {lambda = atof(argv[4]);}
if (argc > 5) {sigma = atof(argv[5]);}
if (argc > 6) {mu = atof(argv[6]);}
if (argc > 7) {iteration_limit = atoi(argv[7]);}


//solve_equation(true);

solve_equation_system();

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
	return pow(income_region1(wage1) * pow(price_index_region1(wage1,wage2), sigma - 1) + income_region2(wage2) * pow(price_index_region2(wage1,wage2) / T, sigma -1),(1 /  sigma)) - wage1;
};

double new_wage_region2(double wage1, double wage2)
{ 
	return pow(income_region1(wage1) * pow(price_index_region1(wage1,wage2) / T, sigma - 1) + income_region2(wage2) * pow(price_index_region2(wage1,wage2) , sigma -1),(1 /  sigma)) - wage2;
};

//Modified form to derivations

double mnew_wage_region1(double wage1, double wage2)
{
	return new_wage_region1(wage1,wage2) + wage1;
};

double mnew_wage_region2(double wage1, double wage2)
{ 
	return new_wage_region2(wage1,wage2) - wage2;
};

//Modified form to derivations

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

return (1/sigma) * pow(mnew_wage_region1(wage1,wage2),1 - sigma)*
(
mu * lambda * pow(price_index_region1(wage1,wage2),sigma-1)-
income_region1(wage1) * pow(price_index_region1(wage1,wage2),2*sigma-2) * lambda * (1-sigma) * pow(wage1, -sigma) - 
pow(T, 2- 2*sigma)*income_region2(wage2) * pow(price_index_region2(wage1,wage2),2*sigma-2) * lambda * (1- sigma) * pow(wage1,-sigma) 
) - 1 ;

};

double d2new_wage_region1(double wage1, double wage2)
{

return (1/sigma) * pow(mnew_wage_region1(wage1,wage2),1 - sigma)*
(
-income_region1(wage1) * pow(price_index_region1(wage1,wage2),2*sigma-2) * (1 - lambda) * (1-sigma) * pow(wage2, -sigma) * pow(T,1-sigma)+ 
mu * (1 - lambda) * pow(price_index_region2(wage1,wage2),sigma-1) * pow(T, 1 - sigma)-
income_region2(wage2) * pow(price_index_region2(wage1,wage2),2*sigma-2) * (1 - lambda) * (1- sigma) * pow(wage2,-sigma) * pow(T, 1 - sigma) 
);

};

double d1new_wage_region2(double wage1, double wage2)
{ 

return (1/sigma) * pow(mnew_wage_region2(wage1,wage2),1 - sigma)*
(
mu *  lambda * pow(price_index_region1(wage1,wage2),sigma-1) * pow(T, 1 - sigma)-
income_region1(wage1) * pow(price_index_region1(wage1,wage2),2*sigma-2) *  lambda * (1- sigma) * pow(wage1,-sigma) * pow(T, 1 - sigma)-
income_region2(wage2) * pow(price_index_region2(wage1,wage2),2*sigma-2) *  lambda * (1-sigma) * pow(wage1, -sigma) * pow(T,1-sigma)
);

};

double d2new_wage_region2(double wage1, double wage2)
{ 

return (1/sigma) * pow(mnew_wage_region2(wage1,wage2),1 - sigma)*
(
-pow(T, 2- 2*sigma)*income_region1(wage1) * pow(price_index_region1(wage1,wage2),2*sigma-2) * (1 - lambda) * (1- sigma) * pow(wage2,-sigma)+
mu * (1- lambda) * pow(price_index_region2(wage1,wage2),sigma-1)-
income_region2(wage2) * pow(price_index_region2(wage1,wage2),2*sigma-2) * (1 - lambda) * (1-sigma) * pow(wage2, -sigma) 
) - 1 ;

};

void textwrite(FILE * allomany,int line, bool text )
{

if (text == false ) return;

printf("%3d \t %.3f \t %.3f \t %.3f \t %.3f \t %.3f \t  %.3f \t %.3f \t %.3f \t %.3f \t %.3f \t %.3f \n",line,w1,d1new_wage_region1(w1,w2),d2new_wage_region1(w1,w2),w2,d1new_wage_region2(w1,w2),d2new_wage_region2(w1,w2),price_index_region1(w1,w2) ,price_index_region2(w1,w2), income_region1(w1),income_region2(w2), new_wage_region1(w1,w2) +  new_wage_region2(w1,w2));

fprintf(allomany,"%3d \t %e \t %e \t %e \t %e \t %e \t  %e \t %e \t %e \t %e \t %e \t %e \n",line,w1,d1new_wage_region1(w1,w2),d2new_wage_region1(w1,w2),w2,d1new_wage_region2(w1,w2),d2new_wage_region2(w1,w2),price_index_region1(w1,w2) ,price_index_region2(w1,w2), income_region1(w1),income_region2(w2), new_wage_region1(w1,w2) +  new_wage_region2(w1,w2));

};

//solver

double solve_equation(bool extrainfo)
{
//változók kezdeti értékei
int i;
double dw1, dw2, segedw1, segedw2;
double jacobi[2][2], determinans, jacobiinverz[2][2];

//fejléc
if (extrainfo)
{

	printf("Iteráció \t w1 \t d1w1 \t d2w1 \t w2 \t d1w2 \t d2w2 \t g1 \t  g2 \t jöv1 \t jöv2 \t célfv. \n");

};

//fájl megnyitás

FILE * pFile;
pFile = fopen ( "neg.txt" , "w" );
if (extrainfo)
{
	
	fprintf(pFile,"Iteráció \t w1 \t dw1 \t w2 \t dw2 \t g1 \t  g2 \t jöv1 \t jöv2 \t célfv. \n");

};
//Kezdeti értékek kiíratása a képernyőre és fájlba

textwrite(pFile,0,extrainfo);

//Iteráció
for(i = 1; i <= iteration_limit; i++)
{
//Jacobi mátrix kiszámítása
jacobi[0][0] = d1new_wage_region1(w1,w2);
jacobi[0][1] = d2new_wage_region1(w1,w2);
jacobi[1][0] = d1new_wage_region2(w1,w2);
jacobi[1][1] = d2new_wage_region2(w1,w2);


determinans = jacobi[0][0]*jacobi[1][1]-jacobi[0][1]*jacobi[1][0];

//Ha determináns nulla, akkor nem lépünk többet
if (determinans == 0) {
printf("Optimális megoldás------------------------------------------------------------\n");
break;
}

//Ha nem nulla, akkor folytatjuk az iterációt

jacobiinverz[0][0] = jacobi[1][1]/determinans;
jacobiinverz[0][1] = -jacobi[0][1]/determinans;
jacobiinverz[1][0] = -jacobi[1][0]/determinans;
jacobiinverz[1][1] = jacobi[0][0]/determinans;


//Új pontok keresése - Newton iteráció
segedw1 = w1 - ( jacobiinverz[0][0] * new_wage_region1(w1,w2) + jacobiinverz[0][1] * new_wage_region2(w1,w2) );
segedw2 = w2 - ( jacobiinverz[1][0] * new_wage_region1(w1,w2) + jacobiinverz[1][1] * new_wage_region2(w1,w2) );


//printf("EZZZZZ %f\n", jacobiinverz[1][1]);

w1 = segedw1;
w2 = segedw2;

//célfüggvény érékének kiíratása

textwrite(pFile,i,extrainfo);

}

//Fájl bezárása
fclose(pFile);

};

double solve_equation_system()
{
	int i;

//fejléc

	printf("Iteráció \t w1 \t w2 \t g1 \t  g2 \t jöv1 \t jöv2 \t célfv. \n");


//fájl megnyitás


	FILE * pFile;
	pFile = fopen ( "neg_lambda.txt" , "w" );
	fprintf(pFile,"Lambda \t w1 \t w2 \t g1 \t  g2 \t jöv1 \t jöv2 \t célfv. \n");


	for(i=0;i<101;i++)
	{
		lambda = i/100;
		solve_equation(false);

		printf("%3d \t %.3f \t %.3f \t %.3f \t %.3f \t %.3f \t  %.3f \t %.3f \n",i,w1,w2,price_index_region1(w1,w2) ,price_index_region2(w1,w2), income_region1(w1),income_region2(w2), new_wage_region1(w1,w2) +  new_wage_region2(w1,w2));


		fprintf(pFile,"%3d \t %e \t %e \t %e \t %e \t %e \t  %e \t %e \n",i ,w1,w2,price_index_region1(w1,w2) ,price_index_region2(w1,w2), income_region1(w1),income_region2(w2), new_wage_region1(w1,w2) +  new_wage_region2(w1,w2));

	}

	fclose(pFile);

};



