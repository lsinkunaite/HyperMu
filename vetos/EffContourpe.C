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
 
void EffContourpe(){

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
   double q0v41[] = {0.983527,0.982798,0.986399};
   double q0v42[] = {0.983527,0.982225,0.986399};
   double q0v43[] = {0.982916,0.982225,0.986399};
   double q1v41[] = {0.982916,0.981651,0.986399};
   double q1v42[] = {0.982916,0.981078,0.986399};
   double q1v43[] = {0.982306,0.981078,0.986399};
   double q2v41[] = {0.982306,0.981651,0.986399};
   double q2v42[] = {0.982306,0.981078,0.986399};
   double q2v43[] = {0.981696,0.981078,0.986399};
   double q3v41[] = {0.982306,0.981651,0.985807};
   double q3v42[] = {0.982306,0.981078,0.985807};
   double q3v43[] = {0.981696,0.981078,0.985807};
   double q4v41[] = {0.982306,0.981651,0.985807};
   double q4v42[] = {0.982306,0.981078,0.985807};
   double q4v43[] = {0.981696,0.981078,0.985807};
   double q5v41[] = {0.982306,0.981078,0.985807};
   double q5v42[] = {0.982306,0.980505,0.985807};
   double q5v43[] = {0.981696,0.980505,0.985807};
   double q6v41[] = {0.982306,0.980505,0.985807};
   double q6v42[] = {0.982306,0.979931,0.985807};
   double q6v43[] = {0.981696,0.979931,0.985807};
   double q7v41[] = {0.982306,0.980505,0.985216};
   double q7v42[] = {0.982306,0.979931,0.985216};
   double q7v43[] = {0.981696,0.979931,0.985216};
   double q8v41[] = {0.981696,0.980505,0.985216};
   double q8v42[] = {0.981696,0.979931,0.985216};
   double q8v43[] = {0.981086,0.979931,0.985216};
   double q9v41[] = {0.980476,0.979358,0.984033};
   double q9v42[] = {0.980476,0.978784,0.984033};
   double q9v43[] = {0.979866,0.978784,0.984033};
   double q10v41[] = {0.973764,0.970183,0.975148};
   double q10v42[] = {0.973764,0.96961,0.975148};
   double q10v43[] = {0.973154,0.96961,0.975148};
   double q11v41[] = {0.95424,0.950115,0.960947};
   double q11v42[] = {0.95424,0.949541,0.960947};
   double q11v43[] = {0.95363,0.949541,0.960947};
   double q12v41[] = {0.914478,0.904243,0.929544};
   double q12v42[] = {0.914478,0.90367,0.929544};
   double q12v43[] = {0.913867,0.90367,0.929544};
   double q13v41[] = {0.850336,0.839931,0.863233};
   double q13v42[] = {0.850336,0.839357,0.863233};
   double q13v43[] = {0.849725,0.839357,0.863233};
   double q14v41[] = {0.773227,0.765212,0.782712};
   double q14v42[] = {0.773227,0.764064,0.782712};
   double q14v43[] = {0.772616,0.764064,0.782712};
   double q15v41[] = {0.686659,0.683697,0.693902};
   double q15v42[] = {0.686659,0.682549,0.693902};
   double q15v43[] = {0.686047,0.682549,0.693902};
 
   double v4ey1[] = {((TMath::MaxElement(3,q0v41))-(TMath::MinElement(3,q0v41)))/2, ((TMath::MaxElement(3,q1v41))-(TMath::MinElement(3,q1v41)))/2, ((TMath::MaxElement(3,q2v41))-(TMath::MinElement(3,q2v41)))/2, ((TMath::MaxElement(3,q3v41))-(TMath::MinElement(3,q3v41)))/2, ((TMath::MaxElement(3,q4v41))-(TMath::MinElement(3,q4v41)))/2, ((TMath::MaxElement(3,q5v41))-(TMath::MinElement(3,q5v41)))/2, ((TMath::MaxElement(3,q6v41))-(TMath::MinElement(3,q6v41)))/2, ((TMath::MaxElement(3,q7v41))-(TMath::MinElement(3,q7v41)))/2, ((TMath::MaxElement(3,q8v41))-(TMath::MinElement(3,q8v41)))/2, ((TMath::MaxElement(3,q9v41))-(TMath::MinElement(3,q9v41)))/2, ((TMath::MaxElement(3,q10v41))-(TMath::MinElement(3,q10v41)))/2, ((TMath::MaxElement(3,q11v41))-(TMath::MinElement(3,q11v41)))/2, ((TMath::MaxElement(3,q12v41))-(TMath::MinElement(3,q12v41)))/2, ((TMath::MaxElement(3,q13v41))-(TMath::MinElement(3,q13v41)))/2, ((TMath::MaxElement(3,q14v41))-(TMath::MinElement(3,q14v41)))/2, ((TMath::MaxElement(3,q15v41))-(TMath::MinElement(3,q15v41)))/2}; 
   double v4ey2[] = {((TMath::MaxElement(3,q0v42))-(TMath::MinElement(3,q0v42)))/2, ((TMath::MaxElement(3,q1v42))-(TMath::MinElement(3,q1v42)))/2, ((TMath::MaxElement(3,q2v42))-(TMath::MinElement(3,q2v42)))/2, ((TMath::MaxElement(3,q3v42))-(TMath::MinElement(3,q3v42)))/2, ((TMath::MaxElement(3,q4v42))-(TMath::MinElement(3,q4v42)))/2, ((TMath::MaxElement(3,q5v42))-(TMath::MinElement(3,q5v42)))/2, ((TMath::MaxElement(3,q6v42))-(TMath::MinElement(3,q6v42)))/2, ((TMath::MaxElement(3,q7v42))-(TMath::MinElement(3,q7v42)))/2, ((TMath::MaxElement(3,q8v42))-(TMath::MinElement(3,q8v42)))/2, ((TMath::MaxElement(3,q9v42))-(TMath::MinElement(3,q9v42)))/2, ((TMath::MaxElement(3,q10v42))-(TMath::MinElement(3,q10v42)))/2, ((TMath::MaxElement(3,q11v42))-(TMath::MinElement(3,q11v42)))/2, ((TMath::MaxElement(3,q12v42))-(TMath::MinElement(3,q12v42)))/2, ((TMath::MaxElement(3,q13v42))-(TMath::MinElement(3,q13v42)))/2, ((TMath::MaxElement(3,q14v42))-(TMath::MinElement(3,q14v42)))/2, ((TMath::MaxElement(3,q15v42))-(TMath::MinElement(3,q15v42)))/2};
   double v4ey3[] = {((TMath::MaxElement(3,q0v43))-(TMath::MinElement(3,q0v43)))/2, ((TMath::MaxElement(3,q1v43))-(TMath::MinElement(3,q1v43)))/2, ((TMath::MaxElement(3,q2v43))-(TMath::MinElement(3,q2v43)))/2, ((TMath::MaxElement(3,q3v43))-(TMath::MinElement(3,q3v43)))/2, ((TMath::MaxElement(3,q4v43))-(TMath::MinElement(3,q4v43)))/2, ((TMath::MaxElement(3,q5v43))-(TMath::MinElement(3,q5v43)))/2, ((TMath::MaxElement(3,q6v43))-(TMath::MinElement(3,q6v43)))/2, ((TMath::MaxElement(3,q7v43))-(TMath::MinElement(3,q7v43)))/2, ((TMath::MaxElement(3,q8v43))-(TMath::MinElement(3,q8v43)))/2, ((TMath::MaxElement(3,q9v43))-(TMath::MinElement(3,q9v43)))/2, ((TMath::MaxElement(3,q10v43))-(TMath::MinElement(3,q10v43)))/2, ((TMath::MaxElement(3,q11v43))-(TMath::MinElement(3,q11v43)))/2, ((TMath::MaxElement(3,q12v43))-(TMath::MinElement(3,q12v43)))/2, ((TMath::MaxElement(3,q13v43))-(TMath::MinElement(3,q13v43)))/2, ((TMath::MaxElement(3,q14v43))-(TMath::MinElement(3,q14v43)))/2, ((TMath::MaxElement(3,q15v43))-(TMath::MinElement(3,q15v43)))/2};
 
   double v4y1[] = {TMath::MinElement(3,q0v41) + v4ey1[0], TMath::MinElement(3,q1v41) + v4ey1[1], TMath::MinElement(3,q2v41) + v4ey1[2], TMath::MinElement(3,q3v41) + v4ey1[3], TMath::MinElement(3,q4v41) + v4ey1[4], TMath::MinElement(3,q5v41) + v4ey1[5], TMath::MinElement(3,q6v41) + v4ey1[6], TMath::MinElement(3,q7v41) + v4ey1[7], TMath::MinElement(3,q8v41) + v4ey1[8], TMath::MinElement(3,q9v41) + v4ey1[9], TMath::MinElement(3,q10v41) + v4ey1[10], TMath::MinElement(3,q11v41) + v4ey1[11], TMath::MinElement(3,q12v41) + v4ey1[12], TMath::MinElement(3,q13v41) + v4ey1[13], TMath::MinElement(3,q14v41) + v4ey1[14], TMath::MinElement(3,q15v41) + v4ey1[15]};
   double v4y2[] = {TMath::MinElement(3,q0v42) + v4ey2[0], TMath::MinElement(3,q1v42) + v4ey2[1], TMath::MinElement(3,q2v42) + v4ey2[2], TMath::MinElement(3,q3v42) + v4ey2[3], TMath::MinElement(3,q4v42) + v4ey1[4], TMath::MinElement(3,q5v42) + v4ey2[5], TMath::MinElement(3,q6v42) + v4ey2[6], TMath::MinElement(3,q7v42) + v4ey2[7], TMath::MinElement(3,q8v42) + v4ey2[8], TMath::MinElement(3,q9v42) + v4ey2[9], TMath::MinElement(3,q10v42) + v4ey2[10], TMath::MinElement(3,q11v42) + v4ey2[11], TMath::MinElement(3,q12v42) + v4ey2[12], TMath::MinElement(3,q13v42) + v4ey2[13], TMath::MinElement(3,q14v42) + v4ey2[14], TMath::MinElement(3,q15v42) + v4ey2[15]};
   double v4y3[] = {TMath::MinElement(3,q0v43) + v4ey3[0], TMath::MinElement(3,q1v43) + v4ey3[1], TMath::MinElement(3,q2v43) + v4ey3[2], TMath::MinElement(3,q3v43) + v4ey3[3], TMath::MinElement(3,q4v43) + v4ey3[4], TMath::MinElement(3,q5v43) + v4ey3[5], TMath::MinElement(3,q6v43) + v4ey3[6], TMath::MinElement(3,q7v43) + v4ey3[7], TMath::MinElement(3,q8v43) + v4ey3[8], TMath::MinElement(3,q9v43) + v4ey3[9], TMath::MinElement(3,q10v43) + v4ey3[10], TMath::MinElement(3,q11v43) + v4ey3[11], TMath::MinElement(3,q12v43) + v4ey3[12], TMath::MinElement(3,q13v43) + v4ey3[13], TMath::MinElement(3,q14v43) + v4ey3[14], TMath::MinElement(3,q15v43) + v4ey3[15]};  



   double x[] = {0.0,100.0,200.0,300.0,400.0,500.0,600.0,700.0,800.0,900.0,1000.0,1100.0,1200.0,1300.0,1400.0,1500.0};
   double ex[] = {0.0};


   auto cv4 = new TCanvas("cv4","cv4",800,600);
   gPad->SetGrid(1,1);
   auto gv42 = new TGraphErrors(16, x, v4y2, ex, v4ey2);
   gv42->SetTitle("");
   gv42->GetXaxis()->SetTitle("E_{Veto_4} [adc]");
   gv42->GetXaxis()->SetRangeUser(0.0,1200.0);
   //gv42->GetYaxis()->SetRangeUser(0.02,0.39);
   //gv42->GetXaxis()->SetRangeUser(0.0,700.0);
   gv42->GetYaxis()->SetRangeUser(0.9,1.01);
   gv42->SetFillColor(kTeal-5);
   gv42->SetFillStyle(3001);
   gv42->Draw("a3");
   auto gv43 = new TGraphErrors(16, x, v4y3, ex, v4ey3);
   gv43->SetFillColor(kViolet-5);
   gv43->SetFillStyle(3001);
   gv43->Draw("3");
   auto gv41 = new TGraphErrors(16, x, v4y1, ex, v4ey1);
   gv41->SetFillColor(kOrange-3);
   gv41->SetFillStyle(3001);
   gv41->Draw("3"); 
   auto legendv4 = new TLegend(0.63,0.77,0.92,0.9);
   legendv4->AddEntry(gv43,"t_{V4} #in [-250, 65] ns","f");
   legendv4->AddEntry(gv42,"t_{V4} #in [-60, 35] ns","f");
   legendv4->AddEntry(gv41,"t_{V4} #in [-30, 30] ns","f");
   legendv4->Draw();
   //cv4->SaveAs("Eff_V4_OR_Contour_Au_zoom.pdf");
   //cv4->SaveAs("Eff_V4_OR_Contour_Au.pdf");



}
 
int main() {
   EffContourpe();
   return 0;
}
