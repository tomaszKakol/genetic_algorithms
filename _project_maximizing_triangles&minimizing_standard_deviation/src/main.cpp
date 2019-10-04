#include "ga/ga.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>

void init(GAGenome&);
float Surface_area(float a,float b,float c);
float Standard_deviation(std::vector<float> surfaces, float mean);
float my_log(float base, float x);
float objective(GAGenome&);
int load_data();
int save_data(const GAGenome&);
//int create_data();
std::vector<float> rods;

int main()
{
    int   popsize = 250;
    int   ngen    = 250;
    float pmut    = 0.01;
    float pcross  = 0.9;

    /*
    if (!create_data()){
        std::cout << "Prenty.txt file not found!" << std::endl;
        return 0;
    }
    */
    if (!load_data()){
        std::cout << "Prenty.txt file not found!" << std::endl;
        return 0;
    }

    std::cout << "In progress ..." << std::endl;
    GA1DArrayGenome<int> genome(rods.size(), objective);
    genome.initializer(init);
    genome.mutator(GA1DArrayGenome<int>::SwapMutator);
    genome.crossover(GA1DArrayGenome<int>::PartialMatchCrossover);
    //pop.crossover(GA1DArrayGenome<int>::OrderCrossover);
    //pop.crossover(GA1DArrayGenome<int>::CycleCrossover);
    GASimpleGA ga(genome);

    ga.selector(GARankSelector());
    //ga.selector(GATournamentSelector());
    //ga.selector(GARouletteWheelSelector());
    ga.populationSize(popsize);
    ga.nGenerations(ngen);
    ga.pMutation(pmut);
    ga.pCrossover(pcross);
    ga.evolve();
    //ga.evolve(rand());

    //std::cout << "Best(ouput.txt file vector from 0, not from 1!):\n" << ga.statistics().bestIndividual() << "\n";
    //std::cout << "The best GA found:\n" << ga.statistics();
    std::cout << "\nThe end! Results in ouput.txt file...\nThanks!\n";

    if (!save_data(ga.statistics().bestIndividual())){
        std::cout << "Ouput.txt file not found!" << std::endl;
        return 0;
    }

    return 0;
}

float objective(GAGenome& gen){
    GA1DArrayGenome<int>& genome = (GA1DArrayGenome<int>&) gen;
    int sum_triangle = 0;
    float sum_S = 0;
    float mean_S = 0;
    float std_dev = 0;
    float score = 0;
    std::vector<float> surfaces;

    int i;
    for (i = 0; i < genome.size(); i=i+3){
        float a, b, c, S;
        a = rods[genome[i]];
        b = rods[genome[i+1]];
        c = rods[genome[i+2]];

        S = Surface_area(a,b,c);
        if(S>=0){
            surfaces.push_back(S);
            sum_S += S;
            sum_triangle++;
        }
    }
    if (sum_triangle== 0){
        return 0;
    }

    mean_S  = sum_S/surfaces.size();
    std_dev = Standard_deviation(surfaces, mean_S);

    //optimization
    //non-linearity regarding the amount of data
    int max_triangles = genome.size()/3;
    //float max_surface =  Surface_area(50,50,50);//(int)1082

    score += max_triangles + (my_log(3.0, (float)sum_triangle)*sum_triangle);//max_triangles
    if(std_dev > mean_S*sum_triangle/max_triangles){
        score +=  max_triangles + (sum_triangle / my_log(3.0, (std_dev + 1.0)));
    }
    //printf("\ntriangle_amount : %d \n", sum_triangle);
    //printf("std_dev  : %f \n", std_dev);
    return score;
}

float my_log(float base, float x) {
    return log(x) / log(base);
}

float Surface_area(float a,float b,float c){
	if (a < 0 || b < 0 || c <0 || a+b <= c || a+c <=b || b+c <=a) {
        //printf("Not a valid trianglen\n");
        return -1;
    }
    float p = (a+b+c)/2.0;
    return sqrt(p*(p-a)*(p-b)*(p-c));//75*25*25*25
};

float Standard_deviation(std::vector<float> surfaces, float mean){
  float std_dev = 0;
  for (int i = 0; i < (int)surfaces.size(); i++){
        std_dev += pow((surfaces[i] - mean), 2);
    }
    return sqrt(std_dev/surfaces.size());
}

void init(GAGenome& gen){
    GA1DArrayGenome<int>& genome = (GA1DArrayGenome<int>&) gen;
    int i;
    for(i = 0; i < genome.size(); i++){
            genome[i] = i;
    }
    for(i = 0; i < genome.size() / 2; i++){
            genome.swap(rand() % genome.size(), rand() % genome.size());
    }
}

int load_data(){
    float length;
    int count = 0;

    std::fstream file("../exe/prety.txt", std::ios_base::in);
    if (!file){
        return 0;
    }

    while (file >> length){
        if (count % 2 == 1){
            rods.push_back(length);
        }
        ++count;
    }

    //printf("\ndata: %d \n", (int)rods.size());
     if((int)rods.size() % 3 != 0){
         std::cout << "Invalid number of rods";
         getchar();
         return -1;
    }

    file.close();
    return 1;
}

int save_data(const GAGenome& gen){
    GA1DArrayGenome<int>& genome=(GA1DArrayGenome<int>&)gen;
    std::fstream file;

    file.open("../exe/output.txt", std::fstream::out | std::fstream::trunc);
    if (!file){
        return 0;
    }

    for (int i = 0; i < genome.size(); i++){
        file << genome[i] + 1 << " \r\n";
    }

    file.close();
    return 1;
}

/*
int create_data()
{
    int myRange = std::rand()%1000+3;

    if(myRange % 3 == 1){
        myRange += 2;
           printf("\nrange: %d \n", myRange );
    }
    else if(myRange % 3 == 2){
        myRange += 1;
        printf("\nrange: %d \n", myRange );
    }
    else{
        printf("\nrange: %d \n", myRange );
    }

    std::fstream file;

    file.open("../exe/prety.txt", std::fstream::out | std::fstream::trunc);
    if (!file){
        return 0;
    }

    for (int i = 0; i < myRange ; i++){
            int xRan = rand()%50+1;
            file << i+1<<" " << xRan << " \r\n";
    }

    file.close();
    return 1;
}
*/
