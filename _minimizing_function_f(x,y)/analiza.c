//dodanie mozliwosci step'a pokolenia
#include <stdio.h>
#include <math.h>
#include "funkcje_linux.h"

int main()
{
    int n = 16;
    float step = 0.05;


//double a = GA_Get_Min_x(n);
//double b  = GA_Get_Min_y(n);
//double c = GA_Get_Max_x(n);
//double d = GA_Get_Max_y(n);

//printf("%f %f %f, %f \n", a,b,c,d);

/*
FILE* plik;
	plik=fopen("plot.txt","a");

	for(double i=GA_Get_Min_x(n);i<GA_Get_Max_x(n);i+=step)
	{
		for(double j=GA_Get_Min_y(n);j<GA_Get_Max_y(n);j+=step)
		{
		    fprintf(plik, "%f %f %f\n",i,j,GA_TestFunction(n,i,j));
			//printf("%f %f %f\n",i,j,GA_TestFunction(n,i,j));
		};
		//printf("\n");
	};
	fclose(plik);
	*/
	FILE* plik;
	plik=fopen("plot.txt","a");

	for(double i=-2;i<2;i+=step)
	{
		for(double j=-2;j<2;j+=step)
		{
		    fprintf(plik, "%f %f %f\n",i,j,GA_TestFunction(n,i,j));
			//printf("%f %f %f\n",i,j,GA_TestFunction(n,i,j));
		};
		//printf("\n");
	};
	fclose(plik);

	return 0;
};
