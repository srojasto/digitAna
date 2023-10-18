//author: akhuntia@cern.ch
// analysis of FDD digits
//

////////////////////////////////////////////////////////
//   H E A D E R S
////////////////////////////////////////////////////////

// C++ headers
#include <iostream>
#include <fstream>
using namespace std;

#include <bitset>

#include <vector>
using std::vector;

// Root headers
#include "TFile.h"
#include "TGraphErrors.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"

// O2 headers
#include "DataFormatsFDD/Digit.h"
#include "DataFormatsFDD/ChannelData.h"
#include "DataFormatsFIT/Triggers.h"
#include "CommonConstants/PhysicsConstants.h"


// my headers
#include "anaDigits_nonIntBC.h"

const float tdc2n = 0.013;


//-----------------------------------------------
// main analysis: get BC maps, time and adc for each PMT
void anaDigits_nonIntBC(int useFeeBits= 3, unsigned int runNumber = 543641, double adcCoincThreshold= 15, bool processNTrees=1, int iFile=0 )
{
  
  cout << "Proccessing the run number " << runNumber << endl;
  cout << "Charge threshold " << adcCoincThreshold << endl;  

  //------get BC filling pattern------
  BCPattern Aside{};
  BCPattern Cside{};
  BCPattern CollidingBunch{};
  int64_t timeStamp = 1657040724000;
  getBcFillingPattern(runNumber, Aside, Cside, CollidingBunch);
  
  // printing flag
  bool doPrint = false;
  //number of BCs to be processed
  //int nBCProceess = 100;
  int nTrees  = 1000000000;

  if(useFeeBits > 3) useFeeBits =3;
  // init histogram arrays
  initHistograms();


  // open file and set the branches
  TFile* digitFile = 0;
  if (iFile == 0) digitFile = TFile::Open(Form("~/cernbox/fdd/runsFDD/runs2023/%i/o2_fdddigits.root",runNumber));
  else if (iFile == 1) digitFile = TFile::Open("o2_fdddigits.root");
  else return;

  printf("\n\r File to open: ~/cernbox/fdd/runsFDD/runs2023/%i/o2_fdddigits.root\n\r",runNumber);

  TTree* digitTree = (TTree*)digitFile->Get("o2sim");
  std::vector<o2::fdd::Digit> digitsBC, *digitsBCPtr = &digitsBC;
  std::vector<o2::fdd::ChannelData> digitsCh, *digitsChPtr = &digitsCh;
  digitTree->SetBranchAddress("FDDDigitCh", &digitsChPtr);
  digitTree->SetBranchAddress("FDDDigit", &digitsBCPtr);

  // loop over entries to get the orbits
  int nTree = digitTree->GetEntries();
  if (doPrint) cout << " There are " << nTree << " entries in tree \n";
  cout << " There are " << nTree << " entries in tree \n";

  for (int iTree = 0; iTree<nTree; iTree++) {
    if (processNTrees && nTrees < iTree) {
        //cout << "iTree = " << iTree << endl;
        saveHistograms(feeNames[useFeeBits],runNumber, adcCoincThreshold);
      return;
    }
     //cout << " Processing Tree  " << iTree<<std::endl;
                                     // get entry
    digitTree->GetEntry(iTree);
    // get BCs in this entry
    int nBC = digitsBC.size();
    if (doPrint) cout << " There are " << nBC << " BC in this entry \n";

    // loop over BC in this entry
    int bcWithPMT = 0;
    nBCperEntry_H->Fill(nBC);

    for(int iBC=0;iBC<nBC;iBC++) {
      // if (iBC%2 == 0) cout<<"Tree "<<iTree<<": BC " << iBC << ": "<<nBC<<std::endl;
      //if(processnBC && iBC > nBCProceess) return;
      // get digits in this BC
      auto& currentDigit = digitsBC[iBC];
      // get BC info
      uint32_t orbit = currentDigit.getOrbit();
      uint16_t bc = currentDigit.getBC();

      // get PMT info
      auto activePMT = currentDigit.getBunchChannelData(digitsCh);    
      int nPMT = activePMT.size();

      // loop over PMTs
      float adc[16] = {0};
      float time[16] = {0};
      int hasData[16] = {0};
      int iChannel = -1;

      
      for(int iPMT = 0; iPMT<nPMT;iPMT++) {
        // get the PMT flags
        iChannel = activePMT[iPMT].mPMNumber;
        hasData[iChannel] = 1;  
        // fill charge and time arrays
        adc[iChannel] = float(activePMT[iPMT].mChargeADC);
        time[iChannel] = float(activePMT[iPMT].mTime)*tdc2n;

        // fill only non interacting bunches A
        if (Aside.test((int)bc)) {
          BCVsChAonlyBC[iChannel]->Fill(bc,adc[iChannel]);
        }

        // BC distribution per channel of signals outside of a timewindow
        //if ( (time[iChannel]<-1 || time[iChannel]>1) && (adc[iChannel] < 1500) && (adc[iChannel] > 15) ){
        if(!CollidingBunch.test((int)bc)){
          BCvsCharge_notCollidingBC[iChannel]->Fill(bc,adc[iChannel]);
        }
        
      }

      // fill time and adc
      for(int i=0;i<16;i++) {
        if (hasData[i] == 0) continue;
        adcPMT_H[i]->Fill(adc[i]);

        //if ( (time[i]<-1 || time[i]>1) && (adc[i] < 1500) && (adc[i] > 15) )
        if(!CollidingBunch.test((int)bc))
        {
          ChargeVsTime[i] -> Fill(adc[i],time[i]);
        }
      }


    }

    //cout << "Event " << iTree+1 << "\r";
  }
  cout << "\n\n";

  // save histograms
 
   saveHistograms(feeNames[useFeeBits],runNumber, adcCoincThreshold);

}