#define feyn_C 

#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>

#include "TAxis.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include <iostream>
#include <fstream>
#include "TLine.h"
#include "TEllipse.h"
	//user defiend
#include "utilities.h"
#include "cuts.h"
#include "params_arg.h"
#include "quicksave.C"
#include "CMSStyle.C"
using namespace std;

void feyn(){
  TCanvas *c1 = new TCanvas("c1", "A canvas", 10,10, 600, 300);
   c1->Range(0, 0, 160, 120);
   Int_t linsav = gStyle->GetLineWidth();
   gStyle->SetLineWidth(3);
   TLatex t;
   t.SetTextAlign(22);
   t.SetTextSize(0.1);
   TLine * l;


//two lines = 2 branches of diagram
float yLoLine = 30;
float yUpLine = yLoLine + 2*20;
float yu = yUpLine + 20;
float yl = yLoLine - 20;
float xoffset = 10;
float vqx = 10;//quark vertex vq
float vcx = vqx+10;//circle vertex = vc
float vcy = 0.5*(yUpLine+yLoLine);
float rcircle = 5;
float vsx = vcx + 20; //stop vertex vs
float vbx = vsx + xoffset;//b-vertex vb
float vchx = vsx + 20;
float vwx = vchx + 0.5*xoffset;
float vwuy = yUpLine + 10;
float vwly = yLoLine - 10;
float vnx = vchx + 20;
float vgx = vnx+xoffset;
float vhx = vnx + 20;
float vax = vhx + 15;
float vauy = yUpLine + 10;
float valy = yUpLine - 10;

//quark lines
float dy = 2;
l = new TLine(vqx,yUpLine,vcx,vcy); l->Draw();
l = new TLine(vqx,yUpLine+dy,vcx,vcy+dy); l->Draw();
l = new TLine(vqx,yUpLine-dy,vcx,vcy-dy); l->Draw();
l = new TLine(vqx,yLoLine,vcx,vcy); l->Draw();
l = new TLine(vqx,yLoLine+dy,vcx,vcy+dy); l->Draw();
l = new TLine(vqx,yLoLine-dy,vcx,vcy-dy); l->Draw();
//circle
TEllipse* circ = new TEllipse(vcx,vcy,rcircle,rcircle);
circ->SetFillStyle(3244);
circ->SetFillColor(10);
circ->Draw("Same");
//stop lines
l = new TLine(vcx,vcy,vsx,yUpLine); l->Draw();
l = new TLine(vcx,vcy,vsx,yLoLine); l->Draw();
//b line
l = new TLine(vbx,yu,vsx,yUpLine); l->Draw();
l = new TLine(vbx,yl,vsx,yLoLine); l->Draw();
//chargino lines
l = new TLine(vsx,yUpLine,vchx,yUpLine); l->Draw();
l = new TLine(vsx,yLoLine,vchx,yLoLine); l->Draw();
//W lines
   TCurlyLine *WU = new TCurlyLine(vax,vauy,vhx,yUpLine);
   WU->SetWavy();
   gammaU->Draw();
l = new TLine(vwx,vwuy,vchx,yUpLine); l->Draw();
l = new TLine(vwx,vwly,vchx,yLoLine); l->Draw();
//neutralino lines
l = new TLine(vchx,yUpLine,vnx,yUpLine); l->Draw();
l = new TLine(vchx,yLoLine,vnx,yLoLine); l->Draw();
//Goldstino line
l = new TLine(vgx,yu,vnx,yUpLine); l->Draw();
l = new TLine(vgx,yl,vnx,yLoLine); l->Draw();
//higgs lines
l = new TLine(vnx,yUpLine,vhx,yUpLine); l->Draw();
l = new TLine(vnx,yLoLine,vhx,yLoLine); l->Draw();
//photon lines
   TCurlyLine *gammaU = new TCurlyLine(vax,vauy,vhx,yUpLine);
   gammaU->SetWavy();
   gammaU->Draw();
   TCurlyLine *gammaL = new TCurlyLine(vax,valy,vhx,yUpLine);
   gammaL->SetWavy();
   gammaL->Draw();


/*   l = new TLine(10, 10, 30, 30); l->Draw();
   l = new TLine(10, 50, 30, 30); l->Draw();
   TCurlyArc *ginit = new TCurlyArc(30, 30, 12.5*sqrt(2), 135, 225);
   ginit->SetWavy();
   ginit->Draw();
   t.DrawLatex(7,6,"e^{-}");
   t.DrawLatex(7,55,"e^{+}");
   t.DrawLatex(7,30,"#gamma");

   TCurlyLine *gamma = new TCurlyLine(30, 30, 55, 30);
   gamma->SetWavy();
   gamma->Draw();
   t.DrawLatex(42.5,37.7,"#gamma");
*/


}
