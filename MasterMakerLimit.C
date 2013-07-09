#include "MCpoint.h"
#include <fstream>
#include <iostream>

//rr MasterMaker.C+
using namespace std;

void MasterMakerLimit(){
	std::vector<MCpoint*> points = setupMCpoints();
	ofstream jdlfile,makeTarFile;
	jdlfile.open("Limits.jdl");
	string executable = "runlims.sh";
	string thisdir = "/uscmst1b_scratch/lpc1/3DayLifetime/abarker/CMSSW_5_3_3/src/SusyNtuplizer/macro/";
	makeTarFile.open("makeLimitTars.sh");

		//prelim statements going into the jdl file
		//this will be submitted with one condor_submit StopGrid.jdl
	jdlfile<<"universe = vanilla"<<endl;
	jdlfile<<"Executable = "<<thisdir<<executable<<endl;
	jdlfile<<"should_transfer_files = YES"<<endl;
	jdlfile<<"when_to_transfer_output = ON_EXIT"<<endl;
	jdlfile<<"# This sets up where your log files go"<<endl;
	jdlfile<<"# Also make sure that the directoy where your log files will go exists"<<endl;

		//alternatively,  you may be able to use a comma separated list of the return files.
		//you now need your tar file to include plotsWithBackground_dataGLL12.root; i.e. datapoint->plotsAndBackground_mc
		//and we're going to assume it's in the macro's dir along with everything else.
	jdlfile<<"Outputdir = "<<thisdir<<"gridout"<<endl;
	jdlfile<<endl;

	int i=0;
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
	//for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end() && i<2;it++){
		if((*it)->type < 10) continue;
		jdlfile<<"MClable = "<<(*it)->pointName<<endl;//$1
		jdlfile<<"transfer_input_files="<<thisdir<<(*it)->pointName<<"_Limit.tar,"<<thisdir<<"plotsWithBackground_dataGLL12.root"<<endl;
		jdlfile<<"Output = $(Outputdir)/condor_$(MClable)_$(Cluster).stdout"<<endl; //cluster tells which submission you're on
		jdlfile<<"Error  = $(Outputdir)/condor_$(MClable)_$(Cluster).stderr"<<endl;
		jdlfile<<"Log    = $(Outputdir)/condor_$(MClable)_$(Cluster).stdlog"<<endl;
		jdlfile<<"Arguments = $(MClable)"<<endl;//args to be passed to the run script
		jdlfile<<"transfer_output_files = LimitResultBundle_$(MClable).txt, LimitResultBundle_$(MClable)_reduced.txt" << endl;
		jdlfile<<"Queue 1"<<endl; //queue one run file, then repete
		jdlfile<<endl;

		i++;
	}//end for
	i=0;
	for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
	//for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end() && i<2;it++){
		if((*it)->type != 10 && (*it)->type != 20) continue;
		makeTarFile << "tar -cvf "<<(*it)->pointName<<"_Limit.tar LimitCard_"<<(*it)->pointName<<"*.txt LimitPackage_"<<(*it)->pointName<<"*.root simplifyLimitBundle.py doLimits_"<<(*it)->pointName<<".sh"<<endl;
		i++;
	}//end for

	jdlfile.close();
	makeTarFile.close();
}//end main

