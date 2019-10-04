#include <iostream>
#include <cmath>
#include <vector>
#include <getopt.h>
#include <ga/ga.h>
#include <ga/GASelector.h>
#include "funkcje_linux.h"
using namespace std;

int n = 16;
int ngen = 100;

float objective(GAGenome& gen);

int main(int argc, char* argv[])
{
	GABin2DecPhenotype map;
	map.add(20,GA_Get_Min_x(n),GA_Get_Max_x(n));
	map.add(20,GA_Get_Min_y(n),GA_Get_Max_y(n));

	GABin2DecGenome genome(map,objective);
	GASelectionScheme* sel=NULL;

	float pmut;
	float pcross;
	int popsize;
	const char * selections_temp;
	const char * crossmetod_temp;

	float mut[] = {0.01, 0.05, 0.1};
    float cros[] = {0.4, 0.5, 0.6, 0.7, 0.8, 0.3};
    int pop[] = {100};
    string selections[] = {"roulette", "tournament", "rank"};
    string crossmetod[] = {"onepoint", "twopoint", "evenodd", "uniform"};

    int sizeFolders = 3*6*1*3*4;

	for (int m_c = 0; m_c < 3; m_c++){
        pmut = mut[m_c];
        for (int c_c = 0; c_c < 6; c_c++){
        pcross = cros[c_c];
            for (int p_c = 0; p_c < 1; p_c++){
                popsize = pop[p_c];
                for (int s_c = 0; s_c < 3; s_c++){
                    selections_temp = selections[s_c].c_str();
                    if(selections_temp == selections[0]){
                         printf("roulette...\n");
                        //ga.selector(GARouletteWheelSelector());
                        sel=new GARouletteWheelSelector();
                    }
                    else if(selections_temp == selections[1])
                    {
                        printf("tournament...\n");
                        //ga.selector(GATournamentSelector());
                        sel=new GATournamentSelector();
                    }
                    else if(selections_temp == selections[2])
                    {
                        printf("rank...\n");
                        //ga.selector(GARankSelector());
                        sel=new GARankSelector();
                    }
                    else {
                        return -1;

                    };

                        for (int cm_c = 0; cm_c < 4; cm_c++){
                            crossmetod_temp = crossmetod[cm_c].c_str();

                        if(crossmetod_temp ==  crossmetod[0]){
                            printf("onepoint...\n");
                            genome.crossover(GA1DBinaryStringGenome::OnePointCrossover);
                        }
                        else if(crossmetod_temp ==  crossmetod[1]){
                            printf("twopoint...\n");
                            genome.crossover(GA1DBinaryStringGenome::TwoPointCrossover);
                        }
                        else if(crossmetod_temp ==  crossmetod[2]){
                            printf("evenodd...\n");
                            genome.crossover(GA1DBinaryStringGenome::EvenOddCrossover);
                        }
                        else if(crossmetod_temp ==  crossmetod[3]){
                            printf("uniform...\n");
                            genome.crossover(GA1DBinaryStringGenome::UniformCrossover);
                        }
                        else {
                                return -1;
                        };

                        GASimpleGA ga(genome);

                        if(sel){
                            //printf("sel...\n");
                            ga.selector(*sel);
                        }

                        ga.minimize();
                        ga.populationSize(popsize);
                        ga.nGenerations(ngen);
                        ga.pMutation(pmut);
                        ga.pCrossover(pcross);

                        GASigmaTruncationScaling scaling;
                        ga.scaling(scaling);

                        char path_1[sizeFolders];
                        sprintf(path_1,"concurrence_%1.2f_%1.2f_%d_%s_%s.dat",pmut,pcross,popsize,selections_temp,crossmetod_temp);
                        ga.scoreFilename(path_1);

                        ga.scoreFrequency(1);
                        ga.flushFrequency(50);
                        ga.selectScores(GAStatistics::AllScores);
                        //ga.evolve((unsigned)time(0));

                        vector<float> best,median,online,offlineMax,offlineMin;
                        int i;
                        for(i=0;i<ngen;i++){
                            ga.step();
                            best.push_back(objective(ga.population().individual(0)));
                            median.push_back(objective(ga.population().individual(ga.population().size()/2)));
                            online.push_back(ga.statistics().online());
                            offlineMax.push_back(ga.statistics().offlineMax());
                            offlineMin.push_back(ga.statistics().offlineMin());
                        };

                        FILE* plik;

                        for(i=0;i<ngen;i++)
                        {
                            char path_2[sizeFolders];
                            sprintf(path_2,"tmp_%1.2f_%1.2f_%d_%s_%s.raw",pmut,pcross,popsize,selections_temp,crossmetod_temp);
                            plik=fopen(path_2,"a");

                            fprintf(plik,"%f %f %f %f %f\n",best[i],median[i],offlineMax[i],offlineMin[i],online[i]);
                            fclose(plik);
                        };

                        char path_3[sizeFolders];
                        sprintf(path_3,"best_%1.2f_%1.2f_%d_%s_%s.raw",pmut,pcross,popsize,selections_temp,crossmetod_temp);
                        plik=fopen(path_3,"a");

                        GABin2DecGenome best_genome(map,objective);
                        best_genome=ga.statistics().bestIndividual();
                        fprintf(plik,"%f %f\n",best_genome.phenotype(0),best_genome.phenotype(1));
                        fclose(plik);

                        //cout<<"Najlepsze rozwiazanie: ("<<best_genome.phenotype(0)<<","<<best_genome.phenotype(1)<<")=>"<<objective(best_genome)<<endl;

                    }
                }
            }
        }
    }

	return 0;
};
float objective(GAGenome& gen)
{
	float x,y;
	GABin2DecGenome &genome=(GABin2DecGenome&)gen;
	x=genome.phenotype(0);
	y=genome.phenotype(1);
	return GA_TestFunction(n,x,y);
};
