//Program to open graph from root file
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TString.h"

// LUT
const char *lut[16] = {
                        "FDDC_0_0", "FDDC_0_1", "FDDC_0_2", "FDDC_0_3",
                        "FDDC_1_0", "FDDC_1_1", "FDDC_1_2", "FDDC_1_3",
                        "FDDA_2_0", "FDDA_2_1", "FDDA_2_2", "FDDA_2_3",
                        "FDDA_3_0", "FDDA_3_1", "FDDA_3_2", "FDDA_3_3"
                      };

void timeBC_perChannel_v0(const char * file="chrg_CollidingBC_543641", const char* folder="."){
    
  int rangeMinY = -5;
  int rangeMaxY = 5;
 
  TFile * rootFile = TFile::Open(TString::Format("%s/%s.root",folder,file));
  //rootFile->ls();
  //rootFile->GetListOfKeys()->Print();
  gStyle->SetOptStat(0);
  bool setLog = true;

  const int nChannels = 16;
  TH2F *htBC_A[nChannels];
  TH2F *htBC_C[nChannels];
  TH2F *htBC[nChannels];
  TH2F *htChargeVsTime[nChannels];

  for (int i = 0; i < nChannels; i++) {
    htBC_A[i] = (TH2F*)gDirectory -> Get(TString::Format("BCVsChAonlyBC%d_H",i));
    htBC_C[i] = (TH2F*)gDirectory -> Get(TString::Format("BCVsChConlyBC%d_H",i));
    htBC[i] = (TH2F*)gDirectory -> Get(TString::Format("BCvsCharge_CollidingBC_%d_H",i));
    htChargeVsTime[i] = (TH2F*)gDirectory -> Get(TString::Format("ChargeVsTime%d_H",i));

  }

 // Text Prints for the canvas
  TText *t = new TText();
  //t->SetTextAlign(22);
  t->SetNDC();
  t->SetTextColor(kRed+2);
  t->SetTextFont(43);
  t->SetTextSize(20);



  TCanvas* cCT_Aonly = new TCanvas("cCT_Aonly", "BC-A, FDD-C time", 1600,1000);
  cCT_Aonly->Divide(2,4);
  TCanvas* cAT_Aonly = new TCanvas("cAT_Aonly", "BC-A, FDD-A time", 1600,1000);
  cAT_Aonly->Divide(2,4);

  for (int i = 0; i < 16; i++) {

    if (i<8) {
      cCT_Aonly->cd(i+1);
       if (setLog) {
          cCT_Aonly->cd(i+1)->SetLogz();
          cCT_Aonly->cd(i+1)->SetLogy();
        }
    }
    else{
        cAT_Aonly->cd(i-7);
          if (setLog){
            cAT_Aonly->cd(i-7)->SetLogz();
            cAT_Aonly->cd(i-7)->SetLogy();
          }
    }

    //htBC_A[i]->GetYaxis() -> SetRangeUser(rangeMinY,rangeMaxY);
    htBC_A[i]->Draw("COLZ");
    int entriesH = htBC_A[i]->GetEntries();
    t->DrawText(.57,.8, Form("%s",lut[i]));
    t->DrawText(.20,.8, Form("Entries=%i",entriesH));
    //hT[i]->SetLineColor(i+1);
  }

 TCanvas* cCT_Conly = new TCanvas("cCT_Conly", "BC C-side ONLY, FDD-C time", 1600,1000);
  cCT_Conly->Divide(2,4);
  TCanvas* cAT_Conly = new TCanvas("cAT_Conly", "BC C-side ONLY, FDD-A time", 1600,1000);
  cAT_Conly->Divide(2,4);

  for (int i = 0; i < 16; i++) {

    if (i<8) {
      cCT_Conly->cd(i+1);
       if (setLog){ 
        cCT_Conly->cd(i+1)->SetLogz();
        cCT_Conly->cd(i+1)->SetLogy();     
       }
    }
    else{
        cAT_Conly->cd(i-7);
          if (setLog){
            cAT_Conly->cd(i-7)->SetLogz();
            cAT_Conly->cd(i-7)->SetLogy();
          } 
    }

    //htBC_A[i]->GetYaxis() -> SetRangeUser(rangeMinY,rangeMaxY);
    htBC_C[i]->Draw("COLZ");
    int entriesH = htBC_C[i]->GetEntries();
    t->DrawText(.57,.8, Form("%s",lut[i]));
    t->DrawText(.20,.8, Form("Entries=%i",entriesH));
    //hT[i]->SetLineColor(i+1);
  }


 TCanvas* cCT_Colliding = new TCanvas("cCT_Colliding", "Colliding BC, FDD-C time", 1600,1000);
  cCT_Colliding->Divide(2,4);
  TCanvas* cAT_Colliding = new TCanvas("cAT_Colliding", "Colliding BC, FDD-A time", 1600,1000);
  cAT_Colliding->Divide(2,4);

  for (int i = 0; i < 16; i++) {

    if (i<8) {
      cCT_Colliding->cd(i+1);
       if (setLog){ 
        cCT_Colliding->cd(i+1)->SetLogz();
        cCT_Colliding->cd(i+1)->SetLogy();     
       }
    }
    else{
        cAT_Colliding->cd(i-7);
          if (setLog){
            cAT_Colliding->cd(i-7)->SetLogz();
            cAT_Colliding->cd(i-7)->SetLogy();
          } 
    }

    //htBC_A[i]->GetYaxis() -> SetRangeUser(rangeMinY,rangeMaxY);
    htBC[i]->Draw("COLZ");
    int entriesH = htBC[i]->GetEntries();
    t->DrawText(.57,.8, Form("%s",lut[i]));
    t->DrawText(.20,.8, Form("Entries=%i",entriesH));
    //hT[i]->SetLineColor(i+1);
  }
 


  TCanvas* cCT_TimeCharge = new TCanvas("cCT_TimeCharge", "FDD-C time vs charge", 1600,1000);
  cCT_TimeCharge->Divide(2,4);
  TCanvas* cAT_TimeCharge = new TCanvas("cAT_TimeCharge", "FDD-A time vs charge", 1600,1000);
  cAT_TimeCharge->Divide(2,4);

 for (int i = 0; i < 16; i++) {

    if (i<8) {
      cCT_TimeCharge->cd(i+1);
       if (setLog) {
        cCT_TimeCharge->cd(i+1)->SetLogz();
        //cCT_TimeCharge->cd(i+1)->SetLogx();
       }
    }
    else{
        cAT_TimeCharge->cd(i-7);
          if (setLog) {
            cAT_TimeCharge->cd(i-7)->SetLogz();
           // cAT_TimeCharge->cd(i-7)->SetLogx();
          }
    }

    htChargeVsTime[i]->GetYaxis() -> SetRangeUser(rangeMinY,rangeMaxY);
    htChargeVsTime[i]->Draw("COLZ");
    int entriesH = htChargeVsTime[i]->GetEntries();
    t->DrawText(.57,.8, Form("%s",lut[i]));
    t->DrawText(.20,.8, Form("Entries=%i",entriesH));
    //hT[i]->SetLineColor(i+1);
  }

  // cAQ-> SaveAs(Form("%s/FDDA_Charge.pdf",folder));

}
