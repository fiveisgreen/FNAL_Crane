#include "MCpoint.h"
#include <fstream>
#include <iostream>

//rr MasterMaker.C+
using namespace std;

void MasterMakerSkim(){
	ofstream jdlfile,runfile;
	printf("making dataskim.jdl\n");
	jdlfile.open("dataskim.jdl");
	string executable = "runskim.sh";
	string thisdir = "/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/";
 	string retdir="/uscmst1b_scratch/lpc1/3DayLifetime/abarker/";

	runfile.open(executable.data());
	//MCpoint * datapoint = setupMCpoint("Data", "");//this is efficient.

		//prelim statements going into the jdl file
		//this will be submitted with one condor_submit StopGrid.jdl
	jdlfile<<"universe = vanilla"<<endl;
	jdlfile<<"Executable = "<<thisdir<<executable<<endl;
	jdlfile<<"should_transfer_files = YES"<<endl;
	jdlfile<<"when_to_transfer_output = ON_EXIT"<<endl;
	jdlfile<<"# This sets up where your log files go"<<endl;
	jdlfile<<"# Also make sure that the directoy where your log files will go exists"<<endl;
	jdlfile<<"transfer_input_files=/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/tar_for_condor.tar,";//no endl
	jdlfile<<"/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/params_arg.h"<<endl;//no endl

		//alternatively,  you may be able to use a comma separated list of the return files.
		//you now need your tar file to include plotsWithBackground_dataGLL12.root; i.e. datapoint->plotsAndBackground_mc
		//and we're going to assume it's in the macro's dir along with everything else.
	jdlfile<<"Outputdir = "<<retdir<<"gridout"<<endl;
	jdlfile<<endl;

	//for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
	for(int j=0;j<100;j++){
	//for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end() && i<2;it++){
		jdlfile<<"Output = $(Outputdir)/condor_"<<j<<".stdout"<<endl; //cluster tells which submission you're on
		jdlfile<<"Error  = $(Outputdir)/condor_"<<j<<".stderr"<<endl;
		jdlfile<<"Log    = $(Outputdir)/condor_"<<j<<".stdlog"<<endl;
		jdlfile<<"Arguments = "<<j<<endl;//args to be passed to the run script
		jdlfile<<"transfer_output_files =SuperSkim53X_data_bf1_12Dr_"<<j<<".root"<<endl;
		jdlfile<<"Queue 1"<<endl; //queue one run file, then repete
		jdlfile<<endl;
	}//end for
	jdlfile.close();
}
