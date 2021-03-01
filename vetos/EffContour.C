// i/O
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
 
// ROOT
#include "TAttMarker.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TList.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveStats.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TText.h"
 
void EffContour(){

   // Some style definitions
   gStyle->SetPaperSize(26,20);
   gStyle->SetOptStat(1);
   gStyle->SetTitleXOffset(1.15);
   gStyle->SetTitleYOffset(1.15);
   gStyle->SetTitleBorderSize(1);
   gStyle->SetLegendBorderSize(1);
    //gStyle->SetPadBottomMargin(0.32);
   gStyle->SetPadBottomMargin(0.14);
   gStyle->SetPadLeftMargin(0.10);
   //gStyle->SetPadTopMargin(0.32);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadRightMargin(0.05);
   gStyle->SetCanvasColor(0);
   gStyle->SetPadColor(0);
   gStyle->SetPalette(1,0);
   //gStyle->SetOptTitle(kFALSE);
   gStyle->SetLabelSize(0.045,"XYZ");
   gStyle->SetTitleSize(0.05,"XYZ");
   gStyle->SetHistLineWidth(2);

   // Veto_4_OR Runs: 530, 529, 528
   double q0v41[] = {0.989055,0.986865,0.989792};
   double q0v42[] = {0.966436,0.959517,0.967969};
   double q0v43[] = {0.915359,0.898082,0.912003};
   double q1v41[] = {0.988325,0.986155,0.989088};
   double q1v42[] = {0.965706,0.958807,0.967265};
   double q1v43[] = {0.91463,0.897372,0.911299};
   double q2v41[] = {0.987961,0.9858,0.989088};
   double q2v42[] = {0.965341,0.958452,0.967265};
   double q2v43[] = {0.91463,0.897017,0.911299};
   double q3v41[] = {0.987961,0.985091,0.988736};
   double q3v42[] = {0.965341,0.957741,0.966913};
   double q3v43[] = {0.91463,0.896662,0.910947};
   double q4v41[] = {0.980664,0.977628,0.979225};
   double q4v42[] = {0.958045,0.950266,0.957394};
   double q4v43[] = {0.907333,0.889165,0.902113};
   double q5v41[] = {0.896275,0.885258,0.901374};
   double q5v42[] = {0.876187,0.858209,0.883057};
   double q5v43[] = {0.829803,0.804193,0.831279};
   double q6v41[] = {0.678127,0.675906,0.679352};
   double q6v42[] = {0.663497,0.656594,0.667724};
   double q6v43[] = {0.632041,0.61749,0.630374};
 
   double v4ey1[] = {((TMath::MaxElement(3,q0v41))-(TMath::MinElement(3,q0v41)))/2, ((TMath::MaxElement(3,q1v41))-(TMath::MinElement(3,q1v41)))/2, ((TMath::MaxElement(3,q2v41))-(TMath::MinElement(3,q2v41)))/2, ((TMath::MaxElement(3,q3v41))-(TMath::MinElement(3,q3v41)))/2, ((TMath::MaxElement(3,q4v41))-(TMath::MinElement(3,q4v41)))/2, ((TMath::MaxElement(3,q5v41))-(TMath::MinElement(3,q5v41)))/2, ((TMath::MaxElement(3,q6v41))-(TMath::MinElement(3,q6v41)))/2}; 
   double v4ey2[] = {((TMath::MaxElement(3,q0v42))-(TMath::MinElement(3,q0v42)))/2, ((TMath::MaxElement(3,q1v42))-(TMath::MinElement(3,q1v42)))/2, ((TMath::MaxElement(3,q2v42))-(TMath::MinElement(3,q2v42)))/2, ((TMath::MaxElement(3,q3v42))-(TMath::MinElement(3,q3v42)))/2, ((TMath::MaxElement(3,q4v42))-(TMath::MinElement(3,q4v42)))/2, ((TMath::MaxElement(3,q5v42))-(TMath::MinElement(3,q5v42)))/2, ((TMath::MaxElement(3,q6v42))-(TMath::MinElement(3,q6v42)))/2};
   double v4ey3[] = {((TMath::MaxElement(3,q0v43))-(TMath::MinElement(3,q0v43)))/2, ((TMath::MaxElement(3,q1v43))-(TMath::MinElement(3,q1v43)))/2, ((TMath::MaxElement(3,q2v43))-(TMath::MinElement(3,q2v43)))/2, ((TMath::MaxElement(3,q3v43))-(TMath::MinElement(3,q3v43)))/2, ((TMath::MaxElement(3,q4v43))-(TMath::MinElement(3,q4v43)))/2, ((TMath::MaxElement(3,q5v43))-(TMath::MinElement(3,q5v43)))/2, ((TMath::MaxElement(3,q6v43))-(TMath::MinElement(3,q6v43)))/2};
 
   double v4y1[] = {TMath::MinElement(3,q0v41) + v4ey1[0], TMath::MinElement(3,q1v41) + v4ey1[1], TMath::MinElement(3,q2v41) + v4ey1[2], TMath::MinElement(3,q3v41) + v4ey1[3], TMath::MinElement(3,q4v41) + v4ey1[4], TMath::MinElement(3,q5v41) + v4ey1[5], TMath::MinElement(3,q6v41) + v4ey1[6]};
   double v4y2[] = {TMath::MinElement(3,q0v42) + v4ey2[0], TMath::MinElement(3,q1v42) + v4ey2[1], TMath::MinElement(3,q2v42) + v4ey2[2], TMath::MinElement(3,q3v42) + v4ey2[3], TMath::MinElement(3,q4v42) + v4ey1[4], TMath::MinElement(3,q5v42) + v4ey2[5], TMath::MinElement(3,q6v42) + v4ey2[6]};
   double v4y3[] = {TMath::MinElement(3,q0v43) + v4ey3[0], TMath::MinElement(3,q1v43) + v4ey3[1], TMath::MinElement(3,q2v43) + v4ey3[2], TMath::MinElement(3,q3v43) + v4ey3[3], TMath::MinElement(3,q4v43) + v4ey3[4], TMath::MinElement(3,q5v43) + v4ey3[5], TMath::MinElement(3,q6v43) + v4ey3[6]};  
 
   double x[] = {0.0, 250.0, 500.0, 750.0, 1000.0, 1250.0, 1500.0};
   double y[] = {0.987763, 0.9870535, 0.9868755, 0.986343, 0.9783565, 0.888993, 0.673808};
   double ex[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
   double ey[] = {0.001291, 0.0012935, 0.0014715, 0.001651, 0.0014965, 0.008253, 0.002039};

/*
   auto c42 = new TCanvas("c42","c42",800,600);
   gPad->SetGrid(1,1);
   double x[] = {0.0, 250.0, 500.0, 750.0, 1000.0, 1250.0, 1500.0};
   double y[] = {0.987763, 0.9870535, 0.9868755, 0.986343, 0.9783565, 0.888993, 0.673808};
   double ex[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
   double ey[] = {0.001291, 0.0012935, 0.0014715, 0.001651, 0.0014965, 0.008253, 0.002039};
   auto ge = new TGraphErrors(7, x, y, ex, ey);
   ge->SetFillColor(4);
   ge->SetFillStyle(3010);
   ge->Draw("a3");
   ge->GetYaxis()->SetRangeUser(0.8,1.01);
   ge->GetXaxis()->SetTitle("E_{Veto} [adc]");
*/

   auto cv4 = new TCanvas("cv4","vv4",800,600);
   gPad->SetGrid(1,1);
   auto gv41 = new TGraphErrors(7, x, v4y1, ex, v4ey1);
   gv41->SetTitle("");
   gv41->GetXaxis()->SetTitle("E_{Veto_4} [adc]");
   gv41->GetXaxis()->SetRangeUser(0.0,1500.0);
   gv41->GetYaxis()->SetRangeUser(0.6,1.01);
   gv41->SetFillColor(kViolet-5);
   gv41->SetFillStyle(3001);
   gv41->Draw("a3");
   auto gv42 = new TGraphErrors(7, x, v4y2, ex, v4ey2);
   gv42->SetFillColor(kTeal-5);
   gv42->SetFillStyle(3001);
   gv42->Draw("3");
   auto gv43 = new TGraphErrors(7, x, v4y3, ex, v4ey3);
   gv43->SetFillColor(kOrange-3);
   gv43->SetFillStyle(3001);
   gv43->Draw("3"); 
   auto legendv4 = new TLegend(0.13, 0.17, 0.42, 0.3);
   legendv4->AddEntry(gv41,"t_{V4} #in [-250, 65] ns","f");
   legendv4->AddEntry(gv42,"t_{V4} #in [-200, 35] ns","f");
   legendv4->AddEntry(gv43,"t_{V4} #in [-150, 35] ns","f");
   legendv4->Draw();
   legendv4->SaveAs("Eff_V4_OR_Contour.pdf");


}
 
int main() {
   EffContour();
   return 0;
}
