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
 
void EffContour2(){

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

   // Veto_4_OR Runs: 549, 548, 547
   double q0v41[] = {0.252579,0.254263,0.246525};
   double q0v42[] = {0.339131,0.345284,0.331993};
   double q0v43[] = {0.352233,0.359955,0.346516};
   double q1v41[] = {0.189079,0.189987,0.18448};
   double q1v42[] = {0.248007,0.249935,0.243293};
   double q1v43[] = {0.256259,0.259441,0.252532};
   double q2v41[] = {0.145016,0.147256,0.144319};
   double q2v42[] = {0.187009,0.187581,0.185123};
   double q2v43[] = {0.192306,0.194038,0.191325};
   double q3v41[] = {0.120475,0.121687,0.119424};
   double q3v42[] = {0.152559,0.152149,0.151731};
   double q3v43[] = {0.156295,0.157316,0.156408};
   double q4v41[] = {0.105918,0.107379,0.102878};
   double q4v42[] = {0.132095,0.132059,0.129538};
   double q4v43[] = {0.135162,0.136296,0.133401};
   double q5v41[] = {0.0943722,0.0962691,0.0928953};
   double q5v42[] = {0.116929,0.117592,0.115739};
   double q5v43[] = {0.119717,0.121157,0.118839};
   double q6v41[] = {0.083998,0.0873295,0.0848485};
   double q6v42[] = {0.10416,0.105916,0.105301};
   double q6v43[] = {0.106557,0.108861,0.107892};
   double q7v41[] = {0.0773092,0.0799442,0.0766488};
   double q7v42[] = {0.095578,0.0966725,0.0953205};
   double q7v43[] = {0.09792,0.0993593,0.0974033};
   double q8v41[] = {0.0716836,0.0729678,0.0706392};
   double q8v42[] = {0.0884551,0.0887155,0.0876318};
   double q8v43[] = {0.090686,0.0910923,0.0893075};
   double q9v41[] = {0.0669977,0.0687303,0.0658518};
   double q9v42[] = {0.0819855,0.0832386,0.0810632};
   double q9v43[] = {0.0839375,0.085512,0.0827393};
   double q10v41[] = {0.061977,0.0641827,0.0610644};
   double q10v42[] = {0.0756832,0.0777617,0.0752075};
   double q10v43[] = {0.0775237,0.0798801,0.0766293};
   double q11v41[] = {0.056789,0.0587567,0.0565317};
   double q11v42[] = {0.068879,0.0708897,0.0695555};
   double q11v43[] = {0.0704964,0.0727498,0.0706721};
   double q12v41[] = {0.051601,0.0543124,0.0517496};
   double q12v42[] = {0.0626325,0.0656195,0.0637063};
   double q12v43[] = {0.0640825,0.0671696,0.0647215};
   double q13v41[] = {0.0475845,0.0480079,0.0473692};
   double q13v42[] = {0.0574456,0.0582309,0.0580027};
   double q13v43[] = {0.0588399,0.0596776,0.0589164};
   double q14v41[] = {0.0430659,0.0439254,0.0431926};
   double q14v42[] = {0.0517568,0.0530123,0.0529612};
   double q14v43[] = {0.0529838,0.0542007,0.0537224};
   double q15v41[] = {0.0386031,0.0392228,0.0395273};
   double q15v42[] = {0.0467373,0.0473804,0.0483805};
   double q15v43[] = {0.0477412,0.0482588,0.049091};
 
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
   //gv42->GetXaxis()->SetRangeUser(0.0,1500.0);
   //gv42->GetYaxis()->SetRangeUser(0.02,0.39);
   gv42->GetXaxis()->SetRangeUser(0.0,700.0);
   gv42->GetYaxis()->SetRangeUser(0.1,0.39);
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
   legendv4->AddEntry(gv43,"t_{V4} #in [-50, 450] ns","f");
   legendv4->AddEntry(gv42,"t_{V4} #in [-40, 160] ns","f");
   legendv4->AddEntry(gv41,"t_{V4} #in [-25, 25] ns","f");
   legendv4->Draw();
   cv4->SaveAs("Eff_V4_OR_Contour_Au_zoom.pdf");
   //cv4->SaveAs("Eff_V4_OR_Contour_Au.pdf");



}
 
int main() {
 
  EffContour2();
   return 0;
}
