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
#include "TString.h"

// O2 headers
#include "DataFormatsFDD/Digit.h"
#include "DataFormatsFDD/ChannelData.h"
#include "DataFormatsFIT/Triggers.h"
#include "CommonConstants/PhysicsConstants.h"


// my headers
#include "histogram.h"

const float tdc2n = 0.013;
////////////////////////////////////////////////////////
//   F U N C T I O N S
////////////////////////////////////////////////////////

//-----------------------------------------------
// fill histograms for coincidence of info on layers in same quadrant
void fillCoincidence(int iQuad, int iPMT, uint16_t bc, float adc, float time)
{
 if (iPMT == 0 || iPMT == 2 || iPMT == 4 || iPMT == 6 ) aQuadBC_H[iQuad]->Fill(bc);
 if (iPMT == 8 || iPMT == 9 || iPMT == 10 || iPMT == 11 ) cQuadBC_H[iQuad]->Fill(bc);
 adcPMTcoincidence_H[iPMT]->Fill(adc);
 timePMTcoincidence_H[iPMT]->Fill(time);
 bcPMTcoincidence_H[iPMT]->Fill(bc);
 timePMTcoincidenceWithBC_H[iPMT]->Fill(bc,time);
}

//-----------------------------------------------
// fill histograms for coincidence of info on layers in same quadrant
void fillCoincCharge(int iPMT, float adc, float time)
{
  adcPMTcoincCharge_H[iPMT]->Fill(adc);

}

//-----------------------------------------------
// main analysis: get BC maps, time and adc for each PMT
void anaDigits(int useFeeBits= 3, unsigned int runNumber = 540645, bool processNTrees=1,bool processnBC=1,int iFile=0,  int adcSaturation = 1, const char * filePath = "~/cernbox/fdd/runsFDD/runs2023")
{
  const int n_PMTs = 16;   // # of channels
  double adcCoincThreshold= 10; // Coincidencia threshold carga
  cout << "Proccessing the run number " << runNumber << endl;
  //------get BC filling pattern------
  BCPattern Aside{};
  BCPattern Cside{};
  BCPattern CollidingBunch{};
  int64_t timeStamp = 1657040724000;
  // getBcFillingPattern(runNumber, Aside, Cside, CollidingBunch);
  // printing flag
  bool doPrint = 0;
  //number of BCs to be processed
  //int nBCProceess = 100;
  int nTrees  = 1000000000;

  if(useFeeBits > 3) useFeeBits =3;
  // init histogram arrays
  initHistograms();

  // open file and set the branches
  TFile* digitFile = 0;
  if (iFile == 0) digitFile = TFile::Open(Form("~/cernbox/fdd/runsFDD/runs2023/%i/o2_fdddigits.root", runNumber));
  else if (iFile == 1) digitFile = TFile::Open("o2_fdddigits.root");
  else return;

  printf("\n\r File to open:%s/%i/o2_fdddigits.root\n\r", filePath, runNumber);

  TTree* digitTree = (TTree*)digitFile->Get("o2sim");
  std::vector<o2::fdd::Digit> digitsBC, *digitsBCPtr = &digitsBC;
  std::vector<o2::fdd::ChannelData> digitsCh, *digitsChPtr = &digitsCh;
  digitTree->SetBranchAddress("FDDDigitCh", &digitsChPtr);
  digitTree->SetBranchAddress("FDDDigit", &digitsBCPtr);

  // loop over entries to get the orbits
  int nTree = digitTree->GetEntries();
  if (doPrint) cout << " There are " << nTree << " entries in tree \n";
  cout << " There are " << nTree << " entries in tree \n";

  int oldBCWithSaturation[n_PMTs] = {0};
  int currentBCWithSaturation[n_PMTs] = {0};

  o2::InteractionRecord oldIneractionRate[n_PMTs]= {};
  o2::InteractionRecord currentIneractionRate[n_PMTs] = {};

  int nPoints =0;

  for (int iTree = 0; iTree<nTree; iTree++) {
    if (processNTrees && nTrees < iTree) {
      saveHistograms(feeNames[useFeeBits],runNumber);
      return;
    }

   int Vertex = 0, OrA =0, OrC =0;
   int VertexRefbc = 0, OrARefbc =0, OrCRefbc =0;
    //cout << " Processing Tree  " << iTree<<std::endl;
                                     // get entry
    digitTree->GetEntry(iTree);
    // get BCs in this entry
    int nBC = digitsBC.size();
    nBCperEntry_H->Fill(nBC);
    //if (doPrint) cout << " There are " << nBC << " BC in this entry \n";
     ////cout << " There are " << nBC << " BC in this entry \n";

    // loop over BC in this entry
    int bcWithPMT = 0;
    //=================================
    //===== Time to calculate trigger rates ====
    //=================================
      double mTimeSum =0;
      double mTimeMinNS = -1;
      double mTimeMaxNS = 0.;

    if (digitsBC.size() > 0) {
      // Considering that Digit container is already sorted by IR
      const o2::InteractionRecord& firstIR = digitsBC[0].getIntRecord();
      const o2::InteractionRecord& lastIR = digitsBC[digitsBC.size() - 1].getIntRecord();
      double timeMinNS = firstIR.bc2ns();
      double timeMaxNS = lastIR.bc2ns();
      mTimeMinNS = std::min(mTimeMinNS, timeMinNS); // to be sure if somehow TFID is unordered
      mTimeMaxNS = std::max(mTimeMaxNS, timeMaxNS);
      mTimeSum += timeMaxNS - timeMinNS;
      mTimeSum *=1.e-6; //ns to ms
    }

    for(int iBC=0;iBC<nBC;iBC++) {
      // if (iBC%2 == 0) cout<<"Tree "<<iTree<<": BC " << iBC << ": "<<nBC<<std::endl;
      //if(processnBC && iBC > nBCProceess) return;
      // get digits in this BC
      auto& currentDigit = digitsBC[iBC];
      // get BC info
      uint32_t orbit = currentDigit.getOrbit();
      uint16_t bc = currentDigit.getBC();

      //-----------------------------ak----------------------
      bool orA = currentDigit.mTriggers.getOrA();
      bool orC = currentDigit.mTriggers.getOrC();
      bcAll->Fill(bc);
      if (orA) {
        OrA++;
        OrARefbc++;
      }

      if (orC) {
        OrC++;
        OrCRefbc++;
      }
      if(orA || orC ) bcOr->Fill(bc);


      if(orA && orC )  {
          bcFDDAnd->Fill(bc);
        if (CollidingBunch.test(bc)) {
          bcFDDAndRefBC->Fill(bc);
        }else
          bcFDDAndNotRefBC->Fill(bc);
      }
      if(currentDigit.mTriggers.getVertex()) {
        Vertex++;
        bcAnd->Fill(bc);
        if (CollidingBunch.test(bc)) {
          bcVertexRefBC->Fill(bc);
        VertexRefbc++;
      }
        else bcVertexNotRefBC->Fill(bc);
      }

      // get PMT info
      auto activePMT = currentDigit.getBunchChannelData(digitsCh);
      fillChannelDataCorrelation(bc, activePMT,-1);
      fillChannelTimeCorrelation(bc, activePMT);

      std::array<float,3> FDDCh = getSumCharge(activePMT);

      if (FDDCh[sumChBoth] > 2000) {
        bcMultiplicityTrigger1->Fill(bc);
        if (!CollidingBunch.test(bc)) bcMultiplicityTriggerNotRefBC1->Fill(bc);

      }
      if (FDDCh[sumChA] > 600 && FDDCh[sumChC] > 600) {
        bcMultiplicityTrigger2->Fill(bc);
        if (!CollidingBunch.test(bc)) bcMultiplicityTriggerNotRefBC2->Fill(bc);
      }
      if (FDDCh[sumChA] > 600 || FDDCh[sumChC] > 600) {
        bcMultiplicityTrigger3->Fill(bc);
        if (!CollidingBunch.test(bc)) bcMultiplicityTriggerNotRefBC3->Fill(bc);
      }
      /////////////////////////////////////////////////////////
      //----------Evaluate the avg time from A side ----------
      /////////////////////////////////////////////////////////
      std::array<float,2>  timeFDD = avgTime(activePMT);
      avgTimeAFromDigit->Fill(timeFDD[timeSide::timeA]);
      avgTimeCFromDigit->Fill(timeFDD[timeSide::timeC]);

      std::array<float,2>  timeFDDWOTrigger = avgTimeWithoutTrigger(activePMT);
      avgTimeDiffVsSumFromDigit->Fill((timeFDDWOTrigger[timeSide::timeC] - timeFDDWOTrigger[timeSide::timeA])/2.0, (timeFDDWOTrigger[timeSide::timeC] + timeFDDWOTrigger[timeSide::timeC])/2.0);

      std::array<float,2>  normalTimeFDDWOTrigger = normalAvgTimeWithoutTrigger(activePMT);
      normalAvgTimeDiffVsSumFromDigit->Fill((normalTimeFDDWOTrigger[timeSide::timeA] - normalTimeFDDWOTrigger[timeSide::timeC])/2.0, (normalTimeFDDWOTrigger[timeSide::timeA] + normalTimeFDDWOTrigger[timeSide::timeC])/2.0);
      //-------time for reference BC-----------
      //-------time for reference BC-----------
      if (CollidingBunch.test((int)bc)){

      avgTimeAFromDigitRefBC->Fill(timeFDD[timeSide::timeA]);
      avgTimeCFromDigitRefBC->Fill(timeFDD[timeSide::timeC]);
      }
      if (timeFDD[timeSide::timeA] != DUMMY_TIME && timeFDD[timeSide::timeC] != DUMMY_TIME ) {
      vertex->Fill((timeFDD[timeSide::timeC]-timeFDD[timeSide::timeA])/2. * o2::constants::physics::LightSpeedCm2NS);//z-vertex distribution in cm
      if (CollidingBunch.test((int)bc))
      vertexRefBC->Fill((timeFDD[timeSide::timeC]-timeFDD[timeSide::timeA])/2. * o2::constants::physics::LightSpeedCm2NS);//z-vertex distribution in cm
      }
      int nPMT = activePMT.size();
      // fill histos
      nPMTperBC_H->Fill(nPMT);
      allBC_H->Fill(bc);
      if (nPMT == 0) noPMTBC_H->Fill(bc);
      if (doPrint) cout << "   orbit " << orbit << " bc " << bc << " active PMTs " << nPMT << "\n";
      if (nPMT == 0) continue;
      bcWithPMT++;
      // loop over PMTs
      int cPMT = 0;
      int aPMT = 0;
      int coincidences[8]={0};
      float time[n_PMTs] = {0};
      float adc[n_PMTs] = {0};
      int hasData[n_PMTs] = {0};
      int iChannel = -1;

      for(int iPMT = 0; iPMT<nPMT;iPMT++) {
        // get the PMT flags
        iChannel = activePMT[iPMT].mPMNumber;
        // if(iChannel != 3) continue;

        ///Use FEE bits to have better amplitude and time
        auto fee = std::bitset<8>(activePMT[iPMT].mFEEBits);
        bool inGate = fee[o2::fdd::ChannelData::EEventDataBit::kIsCFDinADCgate];
        bool inTime = fee[o2::fdd::ChannelData::EEventDataBit::kIsEventInTVDC];

        for (const auto& entry : mMapChTrgNames) {
            if (activePMT[iPMT].mFEEBits & (1 << entry.first)) {
              mHistChDataBits->Fill(iChannel, entry.first);
            }
          }


          // fill in flags
          if (inGate && inTime) flagsPMT_H[iChannel]->Fill(1);
          if (!inGate && inTime) flagsPMT_H[iChannel]->Fill(3);
          if (inGate && !inTime) flagsPMT_H[iChannel]->Fill(2);
          if (!inGate && !inTime) flagsPMT_H[iChannel]->Fill(4);
          //ak
          //make selection
          switch(useFeeBits){
            case 0: if (!(inGate && inTime)) continue; //akhuntia
            break;
            case 1: if (!inGate) continue; //akhuntia
            break;
            case 2: if (!inTime) continue; //akhuntia
            break;
            }
          //if (!(inGate && inTime)) continue; //akhuntia
          // get time and charge

          time[iChannel] = float(activePMT[iPMT].mTime)*tdc2n;
          adc[iChannel] = float(activePMT[iPMT].mChargeADC);
          //if (adc[iChannel] != 0) adcChargeVsChanneId->Fill(adc[iChannel],activePMT[iPMT].mPMNumber);
          adcChargeVsChanneId->Fill(adc[iChannel],activePMT[iPMT].mPMNumber);
          timeVsChanneId->Fill(activePMT[iPMT].mTime,activePMT[iPMT].mPMNumber);
          //if (CollidingBunch.test((int)bc)) {
          if (CollidingBunch.test((int)bc)) {
            adcChargeVsChanneIdRefBCs->Fill(adc[iChannel],activePMT[iPMT].mPMNumber);
            timeVsChanneIdRefBCs->Fill(activePMT[iPMT].mTime,activePMT[iPMT].mPMNumber);

            //timeChargePMT_H[i]->Fill(adc[iChannel],time[iChannel]);  // Solangel, time and charge correlation
          }
          else{

              timeChrgNoBC_PMT_H[iChannel]->Fill(adc[iChannel],time[iChannel]); // Solangel, time and charge correlation
              adcPMTWithoutBC_H[iChannel]->Fill(adc[iChannel]);// charges outside the BC
              ChannelChargeNoBC_H->Fill(adc[iChannel],iChannel);
              timeVsChanneIdNoRefBC->Fill(time[iChannel],iChannel);
          }
          BCVsAdcCharge->Fill(bc,float(activePMT[iPMT].mChargeADC));// charge in ADC
          BCVsTime->Fill(bc,float(activePMT[iPMT].mTime));// time in channel

          hasData[iChannel] = 1;

          if (int(activePMT[iPMT].mChargeADC) >  adcSaturation) {
            //for the first time set the interaction record (old)
            if(oldIneractionRate[iChannel].bc==o2::InteractionRecord::DummyBC) {
              oldIneractionRate[iChannel] = currentDigit.mIntRecord;
              ////std::cout<<"[First time] chanel "<<iChannel<<" charge "<< int(activePMT[iPMT].mChargeADC)<< "   "<<oldIneractionRate[iChannel]<<endl;
            }
            if (currentDigit.mIntRecord != oldIneractionRate[iChannel] && currentDigit.mIntRecord.differenceInBC(oldIneractionRate[iChannel]) > 7)
            {
            //std::cout<<"chanel "<<iChannel<<" charge "<< int(activePMT[iPMT].mChargeADC)<< oldIneractionRate[iChannel]<<endl;
            ////std::cout<<"[other time] chanel "<<iChannel<<" charge "<< int(activePMT[iPMT].mChargeADC)<< "   "<<oldIneractionRate[iChannel]<<endl;
            oldIneractionRate[iChannel] = currentDigit.mIntRecord;
            }
        }

        //cout<<" cur BC "<<currentDigit.mIntRecord.bc<<" cur orbit"<< currentDigit.mIntRecord.orbit<<" Old bc: "<< oldIneractionRate[iChannel].bc
        //<<" Old orbit: "<< oldIneractionRate[iChannel].orbit<<endl;
        //cout<<" delta BC "<<currentDigit.mIntRecord.differenceInBC(oldIneractionRate[iChannel])<<endl;

        //Fill charge for the next 5 bcs for which we see the saturation
        if(oldIneractionRate[iChannel].bc != o2::InteractionRecord::DummyBC && currentDigit.mIntRecord!=oldIneractionRate[iChannel] && abs(currentDigit.mIntRecord.differenceInBC(oldIneractionRate[iChannel])) < 6)
        {
          ////// std::cout<<"[writing] chanel "<<iChannel<<" charge "<<int(activePMT[iPMT].mChargeADC)<<" Time "<<time[iChannel]<<" delta BC "<<currentDigit.mIntRecord.differenceInBC(oldIneractionRate[iChannel])<<" "<<currentDigit.mIntRecord<<endl;
          adcSatutatedChargeVsChanneId->Fill(int(activePMT[iPMT].mChargeADC),iChannel);
          adcSatutatedTimeVsChanneId->Fill(float(activePMT[iPMT].mTime*tdc2n),iChannel);
          adcSatutatedDeltaBCVsChanneId->Fill(currentDigit.mIntRecord.differenceInBC(oldIneractionRate[iChannel]),iChannel);
        }

        // store occupancy
        pmtOccupancy_H->Fill(iChannel);
        pmtBC_H[iChannel]->Fill(bc);
        // count instances in a and c side
              if(adc[iChannel] > 0)//ak
        (iChannel<8)? aPMT++ : cPMT++ ;
      }// fill occupancy

      nPMTAperBC_H->Fill(aPMT);
      nPMTCperBC_H->Fill(cPMT);


      //for(int i=0;i<n_PMTs;i++) {
      //  timeChrgNoBC_PMT_H[i]->Fill(adc[i],time[i]); // Solangel, time and charge correlation
      //}

      // fill time and adc
      for(int i=0;i<16;i++) {

        if (hasData[i] == 0) continue;
        adcPMT_H[i]->Fill(adc[i]);
        timePMT_H[i]->Fill(time[i]);
        adcPMTWithBC_H[i]->Fill(bc, adc[i]);
        timePMTWithBC_H[i]->Fill(bc, time[i]);

        timeChargePMT_H[i]->Fill(adc[i],time[i]); // Solangel, time and charge correlation

        // C-side coincidences
        if (i == 0 && !(adc[0]< 1.e-9) && hasData[4] == 1) fillCoincidence(3,i,bc,adc[i],time[i]);
        if (i == 1 && !(adc[1]< 1.e-9)&& hasData[5] == 1) fillCoincidence(3,i,bc,adc[i],time[i]);
        if (i == 2 && !(adc[2]< 1.e-9)&& hasData[6] == 1) fillCoincidence(2,i,bc,adc[i],time[i]);
        if (i == 3 && !(adc[3]< 1.e-9)&& hasData[7] == 1) fillCoincidence(2,i,bc,adc[i],time[i]);
        if (i == 4 && !(adc[4]< 1.e-9)&& hasData[0] == 1) fillCoincidence(0,i,bc,adc[i],time[i]);
        if (i == 5 && !(adc[5]< 1.e-9)&& hasData[1] == 1) fillCoincidence(0,i,bc,adc[i],time[i]);
        if (i == 6 && !(adc[6]< 1.e-9)&& hasData[2] == 1) fillCoincidence(1,i,bc,adc[i],time[i]);
        if (i == 7 && !(adc[7]< 1.e-9)&& hasData[3] == 1) fillCoincidence(1,i,bc,adc[i],time[i]);

        // A-side coincidences
        if (i == 8 && !(adc[8]< 1.e-9)&& hasData[12] == 1) fillCoincidence(0,i,bc,adc[i],time[i]);
        if (i == 9 && !(adc[9]< 1.e-9)&& hasData[13] == 1) fillCoincidence(1,i,bc,adc[i],time[i]);
        if (i == 10 && !(adc[10]< 1.e-9)&& hasData[14] == 1) fillCoincidence(2,i,bc,adc[i],time[i]);
        if (i == 11 && !(adc[11]< 1.e-9)&& hasData[15] == 1) fillCoincidence(3,i,bc,adc[i],time[i]);
        if (i == 12 && !(adc[12]< 1.e-9)&& hasData[8] == 1) fillCoincidence(0,i,bc,adc[i],time[i]);
        if (i == 13 && !(adc[13]< 1.e-9)&& hasData[9] == 1) fillCoincidence(1,i,bc,adc[i],time[i]);
        if (i == 14 && !(adc[14]< 1.e-9)&& hasData[10] == 1) fillCoincidence(2,i,bc,adc[i],time[i]);
        if (i == 15 && !(adc[15]< 1.e-9)&& hasData[11] == 1) fillCoincidence(3,i,bc,adc[i],time[i]);

        // C-side coincidences with charge
        // double adcCoincThreshold= 40; // Coincidencia threshold carga
        if (i == 0 && !(adc[0]< 1.e-9) && hasData[4] == 1 && (adc[4]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        // Fill chnnel1 charge distribution after selection in charge from channel 4
        if (i == 1 && !(adc[1]< 1.e-9) && hasData[5] == 1 && (adc[5]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 2 && !(adc[2]< 1.e-9) && hasData[6] == 1 && (adc[6]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 3 && !(adc[3]< 1.e-9) && hasData[7] == 1 && (adc[7]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 4 && !(adc[4]< 1.e-9) && hasData[0] == 1 && (adc[0]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 5 && !(adc[5]< 1.e-9) && hasData[1] == 1 && (adc[1]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 6 && !(adc[6]< 1.e-9) && hasData[2] == 1 && (adc[2]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 7 && !(adc[7]< 1.e-9) && hasData[3] == 1 && (adc[3]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);

        // A-side coincidences with charge
        if (i == 8 && !(adc[8]< 1.e-9) && hasData[12] == 1 && (adc[12]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 9 && !(adc[9]< 1.e-9) && hasData[13] == 1 && (adc[13]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 10 && !(adc[10]< 1.e-9) && hasData[14] == 1 && (adc[14]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 11 && !(adc[11]< 1.e-9) && hasData[15] == 1 && (adc[15]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 12 && !(adc[12]< 1.e-9) && hasData[8] == 1 && (adc[8]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 13 && !(adc[13]< 1.e-9) && hasData[9] == 1 && (adc[9]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 14 && !(adc[14]< 1.e-9) && hasData[10] == 1 && (adc[10]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);
        if (i == 15 && !(adc[15]< 1.e-9) && hasData[11] == 1 && (adc[11]> adcCoincThreshold)) fillCoincCharge(i,adc[i],time[i]);


      } // end loop over PMTs with data

      // fill BC histos per side
      if ((aPMT == 0) && (cPMT>0)) {
        cOnlyBC_H->Fill(bc);
      } else if ((aPMT>0) && (cPMT==0)) {
        aOnlyBC_H->Fill(bc);
      } else if ((aPMT>0) && (cPMT>0)) {
        acBC_H->Fill(bc);
      } else {
        if (doPrint) cout << " Warning: no PMT with a signal " << endl;
      }
      // fill BC histos per quadrant
      for(int i=0;i<4;i++) {
        if (coincidences[i]==2) aQuadBC_H[i]->Fill(bc);
        if (coincidences[i+4]==2) cQuadBC_H[i]->Fill(bc);
       }
    } // loop over BC


  grOrA->SetPoint(nPoints,nPoints,OrA/mTimeSum);
  grOrARefBC->SetPoint(nPoints,nPoints,OrARefbc/mTimeSum);

  grOrC->SetPoint(nPoints,nPoints,OrC/mTimeSum);
  grOrCRefBC->SetPoint(nPoints, nPoints, OrCRefbc/mTimeSum);

  grVertex->SetPoint(nPoints, nPoints, Vertex/mTimeSum);
  grVertexRefBC->SetPoint(nPoints, nPoints, VertexRefbc/mTimeSum);

  nPoints++;
  nBCperEntryWithPMT_H->Fill(bcWithPMT);
  if (iTree>20) doPrint = false;
  } // loop over tree entries
  grVertex->SetName("grVertex");
grVertexRefBC->SetName("grVertexRefBC");

grOrA->SetName("grOrA");
grOrARefBC->SetName("grOrARefBC");

grOrC->SetName("grOrC");
grOrCRefBC->SetName("grOrCRefBC");

  // normalise flag histograms
  for(int i=0;i<16;i++) {
    flagsPMT_H[i]->Scale(1./flagsPMT_H[i]->GetEntries());
  }
  // save histograms
  saveHistograms(feeNames[useFeeBits],runNumber);
}
