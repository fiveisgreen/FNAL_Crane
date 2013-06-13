#include <iostream>

#include "TCut.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"

#include "TMVAGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TPluginManager.h"

void doTMVA(){

	TMVA::Factory *factory = new TMVA::Factory( "TMVAnalysis", outputFile,
                                               Form("!V:!Silent:%sColor", gROOT->IsBatch()?"!":"") );

	//2. Link in varrialbes: 
	//    factory->AddVariable( "var1-var2", 'F' );
	factory->AddVariable( "var3",      'I' );
	factory->AddVariable( "var4",      'I' );
	//3. 
	factory->AddSignalTree    ( signal,     1.0     );
	factory->AddBackgroundTree( background, 1.0 );


	//4. 
	// Apply additional cuts on the signal and background samples (can be different)
	TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
	TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

	// tell the factory to use all remaining events in the trees after training for testing:
	factory->PrepareTrainingAndTestTree( mycuts, mycutb,
			"SplitMode=Random:NormMode=NumEvents:!V" );


	//5. Book it!
	if (Use_Cuts)     //*** YG recommended
		factory->BookMethod( TMVA::Types::kCuts, "Cuts",
				"!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

	if (Use_CutsD)     //*** YG recommended
		factory->BookMethod( TMVA::Types::kCuts, "CutsD",
				"!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

	if (Use_CutsPCA)
		factory->BookMethod( TMVA::Types::kCuts, "CutsPCA",
				"!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );


	if (Use_CutsGA)
		factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
				"H:!V:FitMethod=GA:EffSel:Steps=30:Cycles=3:PopSize=100:SC_steps=10:SC_rate=5:SC_factor=0.95:VarProp=FSmart" );

	if (Use_CutsSA)
		factory->BookMethod( TMVA::Types::kCuts, "CutsSA",
				"H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemperature=IncreasingAdaptive:InitialTemperature=1e+6:MinTemperature=1e-6:Eps=1e-10:UseDefaultScale" );






	// Train MVAs using the set of training events
	factory->TrainAllMethods();

	// ---- Evaluate all MVAs using the set of test events
	factory->TestAllMethods();

	// ----- Evaluate and compare performance of all configured MVAs
	factory->EvaluateAllMethods();

	// --------------------------------------------------------------

	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAnalysis is done!" << std::endl;

	delete factory;//memory management 
	if (!gROOT->IsBatch()) TMVAGui( outfileName );

}//end doTMVA
