#include <stdio.h>
#include <stdlib.h>
#include "TString.h"
#include <iostream>
void MoveFileToDcache(char* filename, char* thisDir, char* dCacheDir, bool deleteOrigionalFile = false);
void foo2(){
	char* file = "SuperSkim53X_data12A_1.root";
	//system( "rm SuperSkim53X_data12A_2.root");
	/*char* command = Form("srmcp \"file://///////uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/%s\" \"srm://cmssrm.fnal.gov:8443/resilient/abarker/SusyLooseSkim_53X_2012/%s\"",file,file);
	cout<<command<<endl;
	system( command);
	system( Form("rm %s",file));*/
	int ret =  system("ls");
	//int ret =  system("asdfasdfzsf");
	cout<<"I'm still here "<<ret<<endl;
        char* thisDir = "/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/"; //must end in slash and be a full path.
        char* dCacheDir = "abarker/SusyLooseSkim_53X_2012/"; //must end in slash and should start with abarker
	//MoveFileToDcache(Form("%s%i.root",filename_prefix,label), thisDir, dCacheDir, true);
}

void MoveFileToDcache(char* filename, char* thisDir, char* dCacheDir, bool deleteOrigionalFile){
        //This requires: #include <stdio.h> and #include <stdlib.h>
/*      example: 
        filename = "SuperSkim53X_data12A_1.root";
        thisDir = "/uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/" //must end in slash and be a full path.
        dCacheDir = "abarker/SusyLooseSkim_53X_2012/" //must end in slash and should start with abarker
        if deleteOrigionalFile, the file at filename is deleted after copying
*/        char* command = Form("srmcp \"file:////////%s%s\" \"srm://cmssrm.fnal.gov:8443/resilient/%s%s\"",thisDir,filename,dCacheDir,filename);
        //char* command = Form("srmcp \"file://///////uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/%s\" \"srm://cmssrm.fnal.gov:8443/resilient/abarker/SusyLooseSkim_53X_2012/%s\"",filename,filename);
        cout<<"Running dCache Copy Command:"<<endl;
        cout<<command<<endl;
        //should come out like:         //srmcp "file://///////uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis/SusyNtuplizer/macro/SuperSkim53X_data12A_1.root" "srm://cmssrm.fnal.gov:8443/resilient/abarker/SusyLooseSkim_53X_2012/SuperSkim53X_data12A_1.root"%
        system( command);
        if(deleteOrigionalFile){ 
                cout<<endl<<"*** Deleting "<<filename<<" ***"<<endl<<endl;
                 system( Form("rm %s",filename));
        } 
}//MoveFileToDcache
