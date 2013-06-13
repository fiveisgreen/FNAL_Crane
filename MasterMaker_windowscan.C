#include "MCpoint.h"
#include <fstream>
#include <iostream>

//rr MasterMaker.C+
using namespace std;

void MasterMaker_windowscan(){
	std::vector<MCpoint*> points = setupMCpoints();
	ofstream jdlfile,runfile;
	jdlfile.open("WindowScan.jdl");
	string executable = "runWindowscan.sh";
	string thisdir = "/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/";
	runfile.open(executable.data());
	MCpoint * datapoint = setupMCpoint("Data", "");//this is efficient.

		//prelim statements going into the jdl file
		//this will be submitted with one condor_submit StopGrid.jdl
	jdlfile<<"universe = vanilla"<<endl;
	jdlfile<<"Executable = "<<thisdir<<executable<<endl;
	jdlfile<<"should_transfer_files = YES"<<endl;
	jdlfile<<"when_to_transfer_output = ON_EXIT"<<endl;
	jdlfile<<"# This sets up where your log files go"<<endl;
	jdlfile<<"# Also make sure that the directoy where your log files will go exists"<<endl;
	jdlfile<<"transfer_input_files=/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/tar_for_condor.tar,";//no endl
//	jdlfile<<"/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/"<<datapoint->plotsAndBackground_mc<<",";//no endl
	jdlfile<<"/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/params_arg.h,";//no endl
	jdlfile<<"/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/MCpoint.h"<<endl;

		//alternatively,  you may be able to use a comma separated list of the return files.
		//you now need your tar file to include plotsWithBackground_dataGLL12.root; i.e. datapoint->plotsAndBackground_mc
		//and we're going to assume it's in the macro's dir along with everything else.
	jdlfile<<"Outputdir = "<<thisdir<<"gridout"<<endl;
	jdlfile<<endl;

	//for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end();it++){
	for(float width = 11.0f; width >= 1.999; width -= 0.2){
	//for(std::vector<MCpoint*>::iterator it = points.begin();it != points.end() && i<2;it++){
		jdlfile<<"MClable = "<<(*it)->pointName<<endl;//$1
		jdlfile<<"MCfilepath = "<<(*it)->filepath<<endl;//$2
		jdlfile<<"plotsroot_mc = "<<(*it)->plotsroot_mc<<endl;//$3
		jdlfile<<"logplotsroot_mc = "<<(*it)->logplotsroot_mc<<endl;//$4
		jdlfile<<"plotsAndBackground_mc = "<<(*it)->plotsAndBackground_mc<<endl;//$5
		jdlfile<<"logplotsAndBackground_mc = "<<(*it)->logplotsAndBackground_mc<<endl;//$6
		jdlfile<<"Output = $(Outputdir)/condor_$(MClable)_$(Cluster).stdout"<<endl; //cluster tells which submission you're on
		jdlfile<<"Error  = $(Outputdir)/condor_$(MClable)_$(Cluster).stderr"<<endl;
		jdlfile<<"Log    = $(Outputdir)/condor_$(MClable)_$(Cluster).stdlog"<<endl;
		jdlfile<<"Arguments = $(MClable) $(MCfilepath) $(plotsroot_mc) $(logplotsroot_mc) $(plotsAndBackground_mc) $(logplotsAndBackground_mc)"<<endl;//args to be passed to the run script
		jdlfile<<"transfer_output_files =$(MClable).tar"<<endl;
		jdlfile<<"Queue 1"<<endl; //queue one run file, then repete
		jdlfile<<endl;
	}//end for
	jdlfile.close();


		//setup the file first.

	runfile<<"#!/bin/csh -f"<<endl;
	runfile<<"echo \"1\""<<endl;
	runfile<<"source /uscmst1/prod/sw/cms/cshrc prod"<<endl;
	runfile<<"echo \"2\""<<endl;
	runfile<<"setenv SCRAM_ARCH slc5_amd64_gcc462"<<endl;
	runfile<<"date"<<endl;
	runfile<<"scram project CMSSW CMSSW_5_3_3"<<endl;
	runfile<<"echo \"3\""<<endl;
	runfile<<"cd CMSSW_5_3_3"<<endl;
	runfile<<"cd src"<<endl;
	runfile<<"cmsenv"<<endl;
	runfile<<"echo \"4\""<<endl;
	//runfile<<"root -l -b -q ana_MC_BTagEff_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	//runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	//runfile<<"root -l -b -q postanaana_MC_arg.C+\\(\\\"${1}\\\"\\)"<<endl;
	runfile<<"eval `scramv1 runtime -csh`"<<endl;
	//you're in src/ call tar from two dir below. Creates SusyNtuplizer/macro/ here
	runfile<<"tar -xzvf ../../tar_for_condor.tar"<<endl;
	runfile<<"cp ../../*.h SusyNtuplizer/macro"<<endl; //if you supply extra .h files like MCpoint.h or params, this will overwrite those in tar.
	runfile<<"cd SusyNtuplizer/macro"<<endl;
	runfile<<"echo \"Make BtagEff\""<<endl;
	runfile<<"root -l -b -q ana_MC_BTagEff_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q ana_MC_BTagEff_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<""<<endl;
	runfile<<"echo \"do JEC+1\""<<endl;
	runfile<<"sed -i 's/int bumpJEC = 0/int bumpJEC = 1/' params_arg.h #jec +1"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q postanaana_MC_arg.C+\\(\\\"${1}\\\"\\)"<<endl;
	runfile<<"echo $3 >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $3 $new_plotsroot_mc"<<endl;
	runfile<<"echo $4 >>foo; sed -i 's/.log/JECUp.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $4 $new_logplotsroot_mc"<<endl;
	runfile<<"echo $5 >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $5 $new_plotsAndBackground_mc"<<endl;
	runfile<<"echo $6 >>foo; sed -i 's/.log/JECUp.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $6 $new_logplotsAndBackground_mc"<<endl;
	runfile<<"tar -cvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc"<<endl;
	runfile<<""<<endl;
	runfile<<"echo \"do JEC-1\""<<endl;
	runfile<<"sed -i 's/int bumpJEC = 1/int bumpJEC = -1/' params_arg.h #jec -1"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q postanaana_MC_arg.C+\\(\\\"${1}\\\"\\)"<<endl;
	runfile<<"echo $3 >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $3 $new_plotsroot_mc"<<endl;
	runfile<<"echo $4 >>foo; sed -i 's/.log/JECDown.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $4 $new_logplotsroot_mc"<<endl;
	runfile<<"echo $5 >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $5 $new_plotsAndBackground_mc"<<endl;
	runfile<<"echo $6 >>foo; sed -i 's/.log/JECDown.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $6 $new_logplotsAndBackground_mc"<<endl;
	runfile<<"tar -uvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc"<<endl;
	runfile<<""<<endl;
	runfile<<"echo \"do BtagEff+1\""<<endl;
	runfile<<"sed -i 's/int bumpJEC = -1/int bumpJEC = 0/' params_arg.h"<<endl;
	runfile<<"sed -i 's/int bumpBtagEff = 0/int bumpBtagEff = 1/' params_arg.h #btag +1"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q postanaana_MC_arg.C+\\(\\\"${1}\\\"\\)"<<endl;
	runfile<<"echo $3 >>foo; sed -i 's/.root/BtagEffUp.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $3 $new_plotsroot_mc"<<endl;
	runfile<<"echo $4 >>foo; sed -i 's/.log/BtagEffUp.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $4 $new_logplotsroot_mc"<<endl;
	runfile<<"echo $5 >>foo; sed -i 's/.root/BtagEffUp.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $5 $new_plotsAndBackground_mc"<<endl;
	runfile<<"echo $6 >>foo; sed -i 's/.log/BtagEffUp.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $6 $new_logplotsAndBackground_mc"<<endl;
	runfile<<"tar -uvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc"<<endl;
	runfile<<""<<endl;
	runfile<<"echo \"do BtagEff-1\""<<endl;
	runfile<<"sed -i 's/int bumpBtagEff = 1/int bumpBtagEff = -1/' params_arg.h #btag -1"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q postanaana_MC_arg.C+\\(\\\"${1}\\\"\\)"<<endl;
	runfile<<"echo $3 >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $3 $new_plotsroot_mc"<<endl;
	runfile<<"echo $4 >>foo; sed -i 's/.log/BtagEffDown.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $4 $new_logplotsroot_mc"<<endl;
	runfile<<"echo $5 >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $5 $new_plotsAndBackground_mc"<<endl;
	runfile<<"echo $6 >>foo; sed -i 's/.log/BtagEffDown.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo"<<endl;
	runfile<<"mv $6 $new_logplotsAndBackground_mc"<<endl;
	runfile<<"tar -uvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc"<<endl;
	runfile<<""<<endl;
	runfile<<"echo \"do main\""<<endl;
	runfile<<"sed -i 's/int bumpBtagEff = -1/int bumpBtagEff = 0/' params_arg.h #do normal"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q ana_Main_MC_arg.C\\(\\\"${1}\\\",\\\"${2}\\\"\\)"<<endl;
	runfile<<"root -l -b -q postanaana_MC_arg.C+\\(\\\"${1}\\\"\\)"<<endl;
	runfile<<"tar -uvf ${1}.tar ${3} ${4} ${5} ${6}"<<endl;
	runfile<<""<<endl;
	runfile<<"cp ${1}.tar ../../../../"<<endl;
		//stuff for limit setting
	runfile<<"pwd"<<endl;
	runfile<<"cd ../../../../"<<endl;
	runfile<<"pwd"<<endl;
	runfile<<"echo \"setup the limit setter\""<<endl;
	runfile<<"setenv SCRAM_ARCH slc5_amd64_gcc472"<<endl;
	//runfile<<"cmsrel CMSSW_6_1_1"<<endl;
	runfile<<"scram project CMSSW CMSSW_6_1_1"<<endl;
	runfile<<"sleep 2"<<endl;
	runfile<<"cd CMSSW_6_1_1/src"<<endl;
	runfile<<"cmsenv"<<endl;
	runfile<<"cmscvsroot CMSSW"<<endl;
	runfile<<"addpkg HiggsAnalysis/CombinedLimit V03-01-08"<<endl;
	runfile<<"scramv1 b"<<endl;
	runfile<<"rehash"<<endl;
	runfile<<"echo \"done setting up the limit setter\""<<endl;
	runfile<<"pwd"<<endl;
	runfile<<"cd ../../"<<endl;
	runfile<<"pwd"<<endl;
	runfile<<"cp ${1}.tar CMSSW_6_1_1/src/"<<endl;
	runfile<<"cp CMSSW_5_3_3/src/SusyNtuplizer/macro/*.C CMSSW_6_1_1/src/"<<endl;
	runfile<<"cp CMSSW_5_3_3/src/SusyNtuplizer/macro/*.h CMSSW_6_1_1/src/"<<endl;
	runfile<<"cp CMSSW_5_3_3/src/SusyNtuplizer/macro/*.py CMSSW_6_1_1/src/"<<endl;
	runfile<<"cp "<<datapoint->plotsAndBackground_mc<<" CMSSW_6_1_1/src/"<<endl;//
	//assume that the data file is NOT part of the tarbal, but is provided separately as an additional input file
	//you should do the same with params_args.h and MCpoint.h 
	//runfile<<"cp CMSSW_5_3_3/src/SusyNtuplizer/macro/"<<datapoint->plotsAndBackground_mc<<" CMSSW_6_1_1/src/"<<endl;
	runfile<<"cd CMSSW_6_1_1/src/"<<endl;
	runfile<<"echo \"untar in the results from 5_3_3 analysis\""<<endl;
	runfile<<"tar -xvf ${1}.tar"<<endl;
	runfile<<"echo \"Setup Limits!\""<<endl;
	runfile<<"root -l -b -q SetupLimit.C+\\(\\\"${1}\\\"\\)"<<endl;
	runfile<<"echo \"Run All Cards\""<<endl;
	runfile<<"date"<<endl;
	runfile<<"source doLimits_${1}.sh"<<endl;
	runfile<<"date"<<endl;
	runfile<<"./simplifyLimitBundle.py LimitResultBundle_${1}.txt"<<endl; //make simplified result file
	runfile<<"echo \"Load Up result\""<<endl;
	runfile<<"tar -uvf ${1}.tar LimitResultBundle_${1}.txt LimitResultBundle_${1}_reduced.txt"<<endl;
	runfile<<"cp ${1}.tar ../../"<<endl;
	runfile<<"cd ../../"<<endl;
	runfile<<"pwd"<<endl;

	runfile.close();

}//end main

