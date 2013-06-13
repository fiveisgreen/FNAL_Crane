#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include "TH2D.h"
#include "TFile.h"

using namespace std;

int main (int argc, char* argv[]) {
	if (argc < 2) {
		cout << argv[0] << "" << endl;
		return 0;
	}

	string dataDir = "";
	string limitFile = "";
	string outFile = "";
	double m1step = 0;
	double m1min = 0;
	double m1max = 0;
	double m2step = 0;
	double m2min = 0;
	double m2max = 0;
        if (string(argv[1]) == "coNLSP") {
                limitFile = "limits/limits_coNLSP_v1.txt";
                outFile = "exclusions/exclusions_coNLSP_v1.root";
                m1step = 25;
                m1min = 550;
                m1max = 1400;
                m2step = 50;
                m2min = 2000;
                m2max = 2400;
        } else if (string(argv[1]) == "HeavyHiggs_OpenSearch") {
                limitFile = "limits/limits_HeavyHiggs_OpenSearch.txt";
                outFile = "exclusions/exclusions_HeavyHiggs_OpenSearch.root";
                m1step = 50;
                m1min = 300;
                m1max = 950;
                m2step = 50;
                m2min = 0;
                m2max = 0;
        } else if (string(argv[1]) == "HeavyHiggs_RPV2012") {
                limitFile = "limits/limits_HeavyHiggs_RPV2012.txt";
                outFile = "exclusions/exclusions_HeavyHiggs_RPV2012.root";
                m1step = 50;
                m1min = 300;
                m1max = 950;
                m2step = 50;
                m2min = 0;
                m2max = 0;
	} else if (string(argv[1]) == "AtoZhiggs_RPV2012") {
                limitFile = "limits/limits_AtoZhiggs_RPV2012.txt";
                outFile = "exclusions/exclusions_AtoZhiggs_RPV2012.root";
                m1step = 50;
                m1min = 300;
                m1max = 1000;
                m2step = 50;
                m2min = 0;
                m2max = 0;
	} else if (string(argv[1]) == "HeavyHiggs_RPV2012_19p4ifb") {
                limitFile = "limits/limits_HeavyHiggs_RPV2012_19p4ifb.txt";
                outFile = "exclusions/exclusions_HeavyHiggs_RPV2012_19p4ifb.root";
                m1step = 50;
                m1min = 300;
                m1max = 1000;
                m2step = 50;
                m2min = 0;
                m2max = 0;
	} else if (string(argv[1]) == "HeavyHiggs_RPV2012_19p4ifb_NoTau") {
                limitFile = "limits/limits_HeavyHiggs_RPV2012_19p4ifb_NoTau.txt";
                outFile = "exclusions/exclusions_HeavyHiggs_RPV2012_19p4ifb_NoTau.root";
                m1step = 50;
                m1min = 300;
                m1max = 1000;
                m2step = 50;
                m2min = 0;
                m2max = 0;
	}else if (string(argv[1]) == "T1tttt") {
		limitFile = "limits/limits_T1tttt_v1.txt";
		outFile = "exclusions/exclusions_T1tttt_v1.root";
		m1step = 25;
		m1min = 800;
		m1max = 1100;
		m2step = 25;
		m2min = 0;
		m2max = 750;
        } else if (string(argv[1]) == "StopLRPV_lambda122") {
		limitFile = "limits/limits_StopLRPV_lambda122.txt";
		outFile = "exclusions/exclusions_StopLRPV_lambda122.root";
		m1step = 50;
		m1min = 250;
		m1max = 1000;
		m2step = 25;
		m2min = 0;
		m2max = 0;
	} else if (string(argv[1]) == "StopLRPV_lambda123") {
		limitFile = "limits/limits_StopLRPV_lambda123.txt";
		outFile = "exclusions/exclusions_StopLRPV_lambda123.root";
		m1step = 50;
		m1min = 250;
		m1max = 1000;
		m2step = 25;
		m2min = 0;
		m2max = 0;
	} else if (string(argv[1]) == "StopLRPV_lambda233") {
		limitFile = "limits/limits_StopLRPV_lambda233.txt";
		outFile = "exclusions/exclusions_StopLRPV_lambda233.root";
		m1step = 50;
		m1min = 250;
		m1max = 1000;
		m2step = 25;
		m2min = 0;
		m2max = 0;
        } else if (string(argv[1]) == "LeptonicRPV_lambda233") {
                limitFile = "limits/limits_LeptonicRPV_lambda233.txt";
                outFile = "exclusions/exclusions_LeptonicRPV_lambda233.root";
                m1step = 100;
                m1min = 1000;
                m1max = 2200;
                m2step = 100;
                m2min = 800;
                m2max = 2400;
	} else if (string(argv[1]) == "mSUGRA_LRPV_lambda122") {
                limitFile = "limits/limits_mSUGRA_LRPV_lambda122_v2.txt";
                outFile = "exclusions/exclusions_mSUGRA_LRPV_lambda122_v2.root";
                m1step = 25;
                m1min = 100;
                m1max = 1300;
                m2step = 2;
                m2min = 2;
                m2max = 26;
	} else if (string(argv[1]) == "bprime") {
		limitFile = "/cms/thomassen/2012/EWKino/Statistics/bprime/limits.txt";
		outFile = "exclusions_bprime.root";
		m1step = 50;
		m1min = 500;
		m1max = 700;
		m2step = 0.1;
		m2min = 0;
		m2max = 1;
	} else if (string(argv[1]) == "StopHiggs") {
                limitFile = "limits/slide_combined_full_noreweight_chargino250.out";
                outFile = "exclusions/exclusions_slide_combined_full_noreweight_chargino250.root";
                m1step = 50;
                m1min = 200;
                m1max = 800;
                m2step = 0.1;
                m2min = 0;
                m2max = 1;
	} else {
		cout << "Unknown keyword " << argv[1] << endl; 
		return -1;
	}

	if(m1max < m1min || m2max < m2min) return -1;
	int m1bins = (int)((m1max - m1min) / m1step + 1);
	int m2bins = (int)((m2max - m2min) / m2step + 1);
	m1max = m1min + (m1bins - 1) * m1step;
	m2max = m2min + (m2bins - 1) * m2step;
	
	TH2D* hObs = new TH2D ("hObs", limitFile.c_str()
		, m1bins, m1min - m1step/2., m1max + m1step/2.
		, m2bins, m2min - m2step/2., m2max + m2step/2.);
	hObs->GetXaxis()->SetTitle("m_{1}");
	hObs->GetYaxis()->SetTitle("m_{2}");
	
	TH2D* hExp = new TH2D(*hObs);
	hExp->SetName("hExp");
	
	TH2D* hExp1p = new TH2D(*hObs);
	hExp1p->SetName("hExp1p");
	
	TH2D* hExp1m = new TH2D(*hObs);
	hExp1m->SetName("hExp1m");
	
	TH2D* hExp2p = new TH2D(*hObs);
	hExp2p->SetName("hExp2p");
	
	TH2D* hExp2m = new TH2D(*hObs);
	hExp2m->SetName("hExp2m");
	
	cout << "[PT] Reading limits from " << limitFile << " ..." << endl;
	ifstream in (limitFile.c_str());
	while(in) {
		string line;
		getline(in, line);
		if(!in) break;
		double m1;
		double m2;
		float limit[6];
		if(line[0] == '#') continue;
		sscanf (line.c_str(),"%lf:%lf cls: %f %f ( %f : %f ) ( %f : %f )", &m1, &m2, limit, limit+1, limit+2, limit+3, limit+4, limit+5);
		//cout << m1 << " " << m2  << " " << limit[0] << " " << limit[1] << " " << limit[2] << " " << limit[3] << " " << limit[4] << " " << limit[5] << endl;
		if(m1 < m1min || m2 < m2min || m1 > m1max || m2 > m2max) continue;

		if(!(m1 >= m1min && m1 <= m1max && (fmod(m1 - m1min, m1step) == 0 || fmod(m1 - m1min, m1step) - m1step < 1E-12)) || !(m2 >= m2min && m2 <= m2max && (fmod(m2 - m2min, m2step) == 0 || fmod(m2 - m2min, m2step) - m2step < 1E-12))) {
			cout << "[PT] Skipping point (" << m1 << "," << m2 << ") because it is not on the grid" << endl;
			continue;
		}
		if(hObs->GetBinContent(hObs->FindFixBin(m1, m2)) != 0 || hExp->GetBinContent(hExp->FindFixBin(m1, m2)) != 0) {
			cout << "[PT] ERROR: The point (" << m1 << "," << m2 << ") was already filled." << endl;
			return -1;
		}
		
		hObs->Fill(m1, m2, limit[0]);
		hExp->Fill(m1, m2, limit[1]);
		hExp1p->Fill(m1, m2, limit[2]);
		hExp1m->Fill(m1, m2, limit[3]);
		hExp2p->Fill(m1, m2, limit[4]);
		hExp2m->Fill(m1, m2, limit[5]);
	}

	TFile f(outFile.c_str(), "RECREATE");
	
	hObs->Write();
	hExp->Write();
	hExp1p->Write();
	hExp1m->Write();
	hExp2p->Write();
	hExp2m->Write();
	
	f.Close();

	cout << "Output file produced: " << outFile << endl;

	return 0;
}
