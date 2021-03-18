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
   double q0v41[] = {0.331754,0.337036,0.323916};
   //double q0v42[] = {0.317532,0.387346,0.338015};
   double q0v42[] = {0.317532,0.35592,0.338015};
   double q0v43[] = {0.352233,0.359955,0.346516};
   double q1v41[] = {0.243629,0.244511,0.238774};
   double q1v42[] = {0.233966,0.261981,0.236757};
   double q1v43[] = {0.256259,0.259441,0.252532};
   double q2v41[] = {0.18229,0.182673,0.180244};
   double q2v42[] = {0.172942,0.193418,0.171725};
   double q2v43[] = {0.192306,0.194038,0.191325};
   double q3v41[] = {0.149509,0.148533,0.148378};
   double q3v42[] = {0.141284,0.140306,0.139458};
   double q3v43[] = {0.156295,0.157316,0.156408};
   double q4v41[] = {0.129266,0.129631,0.126642};
   double q4v42[] = {0.122206,0.122613,0.119926};
   double q4v43[] = {0.135162,0.136296,0.133401};
   double q5v41[] = {0.115101,0.115267,0.113555};
   double q5v42[] = {0.108304,0.108396,0.106986};
   double q5v43[] = {0.119717,0.121157,0.118839};
   double q6v41[] = {0.102275,0.104417,0.103269};
   double q6v42[] = {0.0967976,0.097614,0.0959555};
   double q6v43[] = {0.106557,0.108861,0.107892};
   double q7v41[] = {0.0935252,0.0953291,0.0932376};
   double q7v42[] = {0.0882419,0.0892996,0.0859842};
   double q7v43[] = {0.09792,0.0993593,0.0974033};
   double q8v41[] = {0.0866194,0.0870104,0.0855484};
   double q8v42[] = {0.0804514,0.0812756,0.0798999};
   double q8v43[] = {0.090686,0.0910923,0.0893075};
   double q9v41[] = {0.0800937,0.0816885,0.0801507};
   double q9v42[] = {0.0737554,0.0742159,0.0746017};
   double q9v43[] = {0.0839375,0.085512,0.0827393};
   double q10v41[] = {0.0737353,0.0759016,0.0732763};
   double q10v42[] = {0.0652587,0.0680124,0.0671059};
   double q10v43[] = {0.0775237,0.0798801,0.0766293};
   double q11v41[] = {0.0667076,0.0693397,0.067624};
   double q11v42[] = {0.0585573,0.0606751,0.0595414};
   double q11v43[] = {0.0704964,0.0727498,0.0706721};
   double q12v41[] = {0.0605165,0.0639661,0.0618252};
   double q12v42[] = {0.052464,0.0540457,0.05311};
   double q12v43[] = {0.0640825,0.0671696,0.0647215};
   double q13v41[] = {0.0553294,0.0560608,0.0563251};
   double q13v42[] = {0.0467624,0.0475254,0.0471934};
   double q13v43[] = {0.0588399,0.0596776,0.0589164};
   double q14v41[] = {0.0499191,0.0512039,0.0512834};
   double q14v42[] = {0.0404537,0.0415739,0.0417199};
   double q14v43[] = {0.0529838,0.0542007,0.0537224};
   double q15v41[] = {0.044732,0.045572,0.0463458};
   double q15v42[] = {0.0361513,0.0367072,0.0367174};
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
