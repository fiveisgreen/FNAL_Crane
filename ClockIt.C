#include <time.h>
//#include "TFractionFitter.h"
//#include "TAxis.h"
#include "TH1.h"
#include "TMath.h"
//#include <TH2.h>
//#include <TStyle.h>
//#include <TCanvas.h>
#include "TFile.h"
//#include "TTree.h"
//#include "TVirtualFitter.h"
//#include "TLegend.h"
#include <iostream>
//#include "TF1.h"
//#include "TLine.h"
//#include "CMSStyle.C"
//#include "utilities.h"
#include <string.h>
#include <map>
using namespace std;

void ClockIt(){
//This macro is meant solely as a performance testbed

long long niterations = 1000000LL;//a 



//clock how long the for loop takes
clock_t start1 = clock();
for(long long i=0;i<niterations;i++){
}
clock_t stop1 = clock();
double basetime = ((double) (stop1 - start1))/CLOCKS_PER_SEC;

///prep for test area

///end prep for test area
clock_t start = clock();
for(long long i=0;i<niterations;i++){
	///test area
	printf("Hello World %llu\n",i);
	///end test area
}
clock_t stop = clock();
printf("That took %.6f milliseconds\n",1000.0*((((double) (stop - start))/CLOCKS_PER_SEC)  - basetime) / ((double) niterations) );
printf("i.e. %.6f milliseconds for %llu iterations\n",1000.0*((((double) (stop - start))/CLOCKS_PER_SEC)  - basetime), niterations );
printf("including baseline %.6f milliseconds\n",1000.0*(((double) (stop - start))/CLOCKS_PER_SEC)) ;
}//end ClockIt
