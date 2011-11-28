
//Parameters

int iteration_limit = 100; //Itertaion limit

double lambda = 0.5; //Region's population share in region1 parameter
double pgamma =1; //Speed of population moving 
double steplambda1 = -0.1; //derivate step 1
double steplambda2 = -0.4; //derivate step 2

double  mu = 0.5; //Cobb-Douglas utility function parameter
double sigma = 5; //CES utility function parameter

double T = 1; //Transportation cost

double w1 = 1.1; //bérváltozó kezdeti értéke
double w2 = 0.9;

//Equations


//Base modell - original equation system

double income_region1(double wage1);

double income_region2(double wage2);

double price_index_region1(double wage1, double wage2);

double price_index_region2(double wage1, double wage2);

double wage_region1(double income1, double income2, double price_index1, double price_index2);

double wage_region2(double income1, double income2, double price_index1, double price_index2);

double real_wage_region1(double wage1, double price_index1);

double real_wage_region2(double wage2, double price_index2);

//Simplified equation system: 2 equations and two variables 

double new_wage_region1(double wage1);

double new_wage_region2(double wage2);

//Dinamics

double average_real_wage(double real_wage1, double real_wage2);

double new_lamda(double average_real_wage0, double real_wage1); //The value of the population share in the next 

//Solver

double goal_function(double wage1, double wage2, double price_index1, double price_index2);

double dwage_region1(double wage1, double wage2, double price_index1, double price_index2);

double dwage_region2(double wage1, double wage2, double price_index1, double price_index2);

double dprice_index_region1(double wage1, double wage2, double price_index1, double price_index2);

double dprice_index_region2(double wage1, double wage2, double price_index1, double price_index2);

double solve();


//void solve(double lambda0, double pgamma, double mu, double sigma, double T, int iteration limit = 500);

