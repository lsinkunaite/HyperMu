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


   // Veto_5_OR Runs: 530, 529, 528
   double q0v51[] = {0.990528,0.988652,0.991907};
   double q0v52[] = {0.972678,0.964184,0.974314};
   double q0v53[] = {0.932969,0.91773,0.927516};
   double q1v51[] = {0.990528,0.988652,0.991203};
   double q1v52[] = {0.972678,0.964184,0.97361};
   double q1v53[] = {0.932969,0.91773,0.926812};
   double q2v51[] = {0.990528,0.988652,0.991203};
   double q2v52[] = {0.972678,0.964184,0.97361};
   double q2v53[] = {0.932969,0.91773,0.926812};
   double q3v51[] = {0.990528,0.988298,0.991203};
   double q3v52[] = {0.972678,0.96383,0.97361};
   double q3v53[] = {0.932969,0.917376,0.926812};
   double q4v51[] = {0.99016,0.98617,0.990148};
   double q4v52[] = {0.972303,0.961702,0.972555};
   double q4v53[] = {0.93258,0.915603,0.925757};
   double q5v51[] = {0.956633,0.95282,0.947924};
   double q5v52[] = {0.939869,0.928698,0.931034};
   double q5v53[] = {0.901239,0.884001,0.885644};
   double q6v51[] = {0.818082,0.810859,0.802604};
   double q6v52[] = {0.804229,0.789922,0.788881};
   double q6v53[] = {0.772512,0.753016,0.752287};

   double v5ey1[] = {((TMath::MaxElement(3,q0v51))-(TMath::MinElement(3,q0v51)))/2, ((TMath::MaxElement(3,q1v51))-(TMath::MinElement(3,q1v51)))/2, ((TMath::MaxElement(3,q2v51))-(TMath::MinElement(3,q2v51)))/2, ((TMath::MaxElement(3,q3v51))-(TMath::MinElement(3,q3v51)))/2, ((TMath::MaxElement(3,q4v51))-(TMath::MinElement(3,q4v51)))/2, ((TMath::MaxElement(3,q5v51))-(TMath::MinElement(3,q5v51)))/2, ((TMath::MaxElement(3,q6v51))-(TMath::MinElement(3,q6v51)))/2};
   double v5ey2[] = {((TMath::MaxElement(3,q0v52))-(TMath::MinElement(3,q0v52)))/2, ((TMath::MaxElement(3,q1v52))-(TMath::MinElement(3,q1v52)))/2, ((TMath::MaxElement(3,q2v52))-(TMath::MinElement(3,q2v52)))/2, ((TMath::MaxElement(3,q3v52))-(TMath::MinElement(3,q3v52)))/2, ((TMath::MaxElement(3,q4v52))-(TMath::MinElement(3,q4v52)))/2, ((TMath::MaxElement(3,q5v52))-(TMath::MinElement(3,q5v52)))/2, ((TMath::MaxElement(3,q6v52))-(TMath::MinElement(3,q6v52)))/2};
   double v5ey3[] = {((TMath::MaxElement(3,q0v53))-(TMath::MinElement(3,q0v53)))/2, ((TMath::MaxElement(3,q1v53))-(TMath::MinElement(3,q1v53)))/2, ((TMath::MaxElement(3,q2v53))-(TMath::MinElement(3,q2v53)))/2, ((TMath::MaxElement(3,q3v53))-(TMath::MinElement(3,q3v53)))/2, ((TMath::MaxElement(3,q4v53))-(TMath::MinElement(3,q4v53)))/2, ((TMath::MaxElement(3,q5v53))-(TMath::MinElement(3,q5v53)))/2, ((TMath::MaxElement(3,q6v53))-(TMath::MinElement(3,q6v53)))/2};

   double v5y1[] = {TMath::MinElement(3,q0v51) + v5ey1[0], TMath::MinElement(3,q1v51) + v5ey1[1], TMath::MinElement(3,q2v51) + v5ey1[2], TMath::MinElement(3,q3v51) + v5ey1[3], TMath::MinElement(3,q4v51) + v5ey1[4], TMath::MinElement(3,q5v51) + v5ey1[5], TMath::MinElement(3,q6v51) + v5ey1[6]};
   double v5y2[] = {TMath::MinElement(3,q0v52) + v5ey2[0], TMath::MinElement(3,q1v52) + v5ey2[1], TMath::MinElement(3,q2v52) + v5ey2[2], TMath::MinElement(3,q3v52) + v5ey2[3], TMath::MinElement(3,q4v52) + v5ey1[4], TMath::MinElement(3,q5v52) + v5ey2[5], TMath::MinElement(3,q6v52) + v5ey2[6]};
   double v5y3[] = {TMath::MinElement(3,q0v53) + v5ey3[0], TMath::MinElement(3,q1v53) + v5ey3[1], TMath::MinElement(3,q2v53) + v5ey3[2], TMath::MinElement(3,q3v53) + v5ey3[3], TMath::MinElement(3,q4v53) + v5ey3[4], TMath::MinElement(3,q5v53) + v5ey3[5], TMath::MinElement(3,q6v53) + v5ey3[6]};


   // Veto_6_OR Runs: 530, 529, 528
   double q0v61[] = {0.975895,0.973423,0.976728};
   double q0v62[] = {0.964207,0.961375,0.966855};
   double q0v63[] = {0.929145,0.926648,0.931946};
   double q1v61[] = {0.973338,0.972006,0.974965};
   double q1v62[] = {0.961651,0.959957,0.965092};
   double q1v63[] = {0.926589,0.92523,0.930183};
   double q2v61[] = {0.971147,0.970234,0.974612};
   double q2v62[] = {0.959459,0.958186,0.964739};
   double q2v63[] = {0.924397,0.923459,0.929831};
   double q3v61[] = {0.968955,0.969525,0.973554};
   double q3v62[] = {0.957268,0.957477,0.963681};
   double q3v63[] = {0.922206,0.92275,0.928773};
   double q4v61[] = {0.966399,0.965273,0.970733};
   double q4v62[] = {0.954711,0.953225,0.96086};
   double q4v63[] = {0.919284,0.918143,0.925952};
   double q5v61[] = {0.887509,0.89011,0.890691};
   double q5v62[] = {0.875457,0.878057,0.881171};
   double q5v63[] = {0.841855,0.844381,0.844499};
   double q6v61[] = {0.642544,0.656859,0.672426};
   double q6v62[] = {0.631944,0.647643,0.664669};
   double q6v63[] = {0.606725,0.623183,0.638928};

   double v6ey1[] = {((TMath::MaxElement(3,q0v61))-(TMath::MinElement(3,q0v61)))/2, ((TMath::MaxElement(3,q1v61))-(TMath::MinElement(3,q1v61)))/2, ((TMath::MaxElement(3,q2v61))-(TMath::MinElement(3,q2v61)))/2, ((TMath::MaxElement(3,q3v61))-(TMath::MinElement(3,q3v61)))/2, ((TMath::MaxElement(3,q4v61))-(TMath::MinElement(3,q4v61)))/2, ((TMath::MaxElement(3,q5v61))-(TMath::MinElement(3,q5v61)))/2, ((TMath::MaxElement(3,q6v61))-(TMath::MinElement(3,q6v61)))/2};
   double v6ey2[] = {((TMath::MaxElement(3,q0v62))-(TMath::MinElement(3,q0v62)))/2, ((TMath::MaxElement(3,q1v62))-(TMath::MinElement(3,q1v62)))/2, ((TMath::MaxElement(3,q2v62))-(TMath::MinElement(3,q2v62)))/2, ((TMath::MaxElement(3,q3v62))-(TMath::MinElement(3,q3v62)))/2, ((TMath::MaxElement(3,q4v62))-(TMath::MinElement(3,q4v62)))/2, ((TMath::MaxElement(3,q5v62))-(TMath::MinElement(3,q5v62)))/2, ((TMath::MaxElement(3,q6v62))-(TMath::MinElement(3,q6v62)))/2};
   double v6ey3[] = {((TMath::MaxElement(3,q0v63))-(TMath::MinElement(3,q0v63)))/2, ((TMath::MaxElement(3,q1v63))-(TMath::MinElement(3,q1v63)))/2, ((TMath::MaxElement(3,q2v63))-(TMath::MinElement(3,q2v63)))/2, ((TMath::MaxElement(3,q3v63))-(TMath::MinElement(3,q3v63)))/2, ((TMath::MaxElement(3,q4v63))-(TMath::MinElement(3,q4v63)))/2, ((TMath::MaxElement(3,q5v63))-(TMath::MinElement(3,q5v63)))/2, ((TMath::MaxElement(3,q6v63))-(TMath::MinElement(3,q6v63)))/2};
 
   double v6y1[] = {TMath::MinElement(3,q0v61) + v6ey1[0], TMath::MinElement(3,q1v61) + v6ey1[1], TMath::MinElement(3,q2v61) + v6ey1[2], TMath::MinElement(3,q3v61) + v6ey1[3], TMath::MinElement(3,q4v61) + v6ey1[4], TMath::MinElement(3,q5v61) + v6ey1[5], TMath::MinElement(3,q6v61) + v6ey1[6]};
   double v6y2[] = {TMath::MinElement(3,q0v62) + v6ey2[0], TMath::MinElement(3,q1v62) + v6ey2[1], TMath::MinElement(3,q2v62) + v6ey2[2], TMath::MinElement(3,q3v62) + v6ey2[3], TMath::MinElement(3,q4v62) + v6ey1[4], TMath::MinElement(3,q5v62) + v6ey2[5], TMath::MinElement(3,q6v62) + v6ey2[6]};
   double v6y3[] = {TMath::MinElement(3,q0v63) + v6ey3[0], TMath::MinElement(3,q1v63) + v6ey3[1], TMath::MinElement(3,q2v63) + v6ey3[2], TMath::MinElement(3,q3v63) + v6ey3[3], TMath::MinElement(3,q4v63) + v6ey3[4], TMath::MinElement(3,q5v63) + v6ey3[5], TMath::MinElement(3,q6v63) + v6ey3[6]};


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
/*
   auto cv4 = new TCanvas("cv4","cv4",800,600);
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
   //auto legendv4 = new TLegend(0.13, 0.17, 0.42, 0.3);
   auto legendv4 = new TLegend(0.13,0.17,0.42,0.3);
   legendv4->AddEntry(gv41,"t_{V4} #in [-250, 65] ns","f");
   legendv4->AddEntry(gv42,"t_{V4} #in [-200, 35] ns","f");
   legendv4->AddEntry(gv43,"t_{V4} #in [-150, 35] ns","f");
   legendv4->Draw();
   //cv4->SaveAs("Eff_V4_OR_Contour_zoom.pdf");
   cv4->SaveAs("Eff_V4_OR_Contour.pdf");

   auto cv5 = new TCanvas("cv5","cv5",800,600);
   gPad->SetGrid(1,1);
   auto gv51 = new TGraphErrors(7, x, v5y1, ex, v5ey1);
   gv51->SetTitle("");
   gv51->GetXaxis()->SetTitle("E_{Veto_5} [adc]");
   gv51->GetXaxis()->SetRangeUser(0.0,1500.0);
   gv51->GetYaxis()->SetRangeUser(0.85,1.01);
   gv51->SetFillColor(kViolet-5);
   gv51->SetFillStyle(3001);
   gv51->Draw("a3");
   auto gv52 = new TGraphErrors(7, x, v5y2, ex, v5ey2);
   gv52->SetFillColor(kTeal-5);
   gv52->SetFillStyle(3001);
   gv52->Draw("3");
   auto gv53 = new TGraphErrors(7, x, v5y3, ex, v5ey3);
   gv53->SetFillColor(kOrange-3);
   gv53->SetFillStyle(3001);
   gv53->Draw("3");
   auto legendv5 = new TLegend(0.13,0.17,0.42,0.3);
   legendv5->AddEntry(gv51,"t_{V5} #in [-250, 65] ns","f");
   legendv5->AddEntry(gv52,"t_{V5} #in [-200, 35] ns","f");
   legendv5->AddEntry(gv53,"t_{V5} #in [-150, 35] ns","f");
   legendv5->Draw();
   cv5->SaveAs("Eff_V5_OR_Contour_zoom.pdf");
   //cv5->SaveAs("Eff_V5_OR_Contour.pdf");

   auto cv6 = new TCanvas("cv6","cv6",800,600);
   gPad->SetGrid(1,1);
   auto gv61 = new TGraphErrors(7, x, v6y1, ex, v6ey1);
   gv61->SetTitle("");
   gv61->GetXaxis()->SetTitle("E_{Veto_6} [adc]");
   gv61->GetXaxis()->SetRangeUser(0.0,1500.0);
   gv61->GetYaxis()->SetRangeUser(0.88,0.99);
   gv61->SetFillColor(kViolet-5);
   gv61->SetFillStyle(3001);
   gv61->Draw("a3");
   auto gv62 = new TGraphErrors(7, x, v6y2, ex, v6ey2);
   gv62->SetFillColor(kTeal-5);
   gv62->SetFillStyle(3001);
   gv62->Draw("3");
   auto gv63 = new TGraphErrors(7, x, v6y3, ex, v6ey3);
   gv63->SetFillColor(kOrange-3);
   gv63->SetFillStyle(3001);
   gv63->Draw("3");
   auto legendv6 = new TLegend(0.13,0.17,0.42,0.3);
   legendv6->AddEntry(gv61,"t_{V6} #in [-250, 65] ns","f");
   legendv6->AddEntry(gv62,"t_{V6} #in [-200, 35] ns","f");
   legendv6->AddEntry(gv63,"t_{V6} #in [-150, 35] ns","f");
   legendv6->Draw();
   cv6->SaveAs("Eff_V6_OR_Contour_zoom.pdf");
   //cv6->SaveAs("Eff_V6_OR_Contour.pdf");
*/
   auto cv456 = new TCanvas("cv456","cv456",800,600);
   gPad->SetGrid(1,1);
   auto gv51 = new TGraphErrors(7, x, v5y1, ex, v5ey1); 
   gv51->SetTitle("");
   gv51->GetXaxis()->SetTitle("E_{Veto} [adc]");
   gv51->GetXaxis()->SetRangeUser(0.0,1500.0);
   gv51->GetYaxis()->SetRangeUser(0.94,1.0);
   gv51->SetFillColor(kViolet-5);
   gv51->SetFillStyle(3001);
   gv51->Draw("a3");
   auto gv41 = new TGraphErrors(7, x, v4y1, ex, v4ey1);
   gv41->SetFillColor(kTeal-5);
   gv41->SetFillStyle(3001);
   gv41->Draw("3");
   auto gv61 = new TGraphErrors(7, x, v6y1, ex, v6ey1);
   gv61->SetFillColor(kOrange-3);
   gv61->SetFillStyle(3001);
   gv61->Draw("3");
   auto legendv456 = new TLegend(0.13,0.17,0.42,0.3);
   legendv456->AddEntry(gv51,"t_{V5} #in [-250, 65] ns","f");
   legendv456->AddEntry(gv41,"t_{V4} #in [-250, 65] ns","f");
   legendv456->AddEntry(gv61,"t_{V6} #in [-250, 65] ns","f");
   legendv456->Draw();
   cv456->SaveAs("Eff_V456_OR_Contour_zoom.pdf");
   //cv456->SaveAs("Eff_V456_OR_Contour.pdf");

}
 
int main() {
 
  EffContour();
   return 0;
}
