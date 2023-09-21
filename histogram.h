//histogramV4.h
// to define the histograms used in the analysis
//
//-----------------------------------------------
// structure of the file
TH1F *nBCperEntry_H = new TH1F("nBCperEntry_H",";Number of BC per tree entry;Entries",100,-0.5,99.5);
TH1F *nBCperEntryWithPMT_H = new TH1F("nBCperEntryWithPMT_H",";Number of BC per tree entry;Entries",100,-0.5,99.5);
TH1F *nPMTperBC_H = new TH1F("nPMTperBC_H",";Number of PMTs per BC;Entries",17,-0.5,16.5);
TH1F *pmtOccupancy_H = new TH1F("pmtOccupancy_H",";PMT ID;Entries",16,-0.5,15.5);
TH1F *nPMTAperBC_H = new TH1F("nPMTAperBC_H",";Number of PMTs in A-side per BC;Entries",9,-0.5,8.5);
TH1F *nPMTCperBC_H = new TH1F("nPMTCperBC_H",";Number of PMTs in C-side per BC;Entries",9,-0.5,8.5);

//-----------------------------------------------
TGraphErrors *grVertex=new TGraphErrors();
TGraphErrors *grVertexRefBC=new TGraphErrors();

TGraphErrors *grOrA=new TGraphErrors();
TGraphErrors *grOrARefBC=new TGraphErrors();

TGraphErrors *grOrC=new TGraphErrors();
TGraphErrors *grOrCRefBC=new TGraphErrors();

TH1F *bcFDDAnd = new TH1F("bcFDDAnd",";BC ID [FDD AND] ;Entries",3564,-0.5,3563.5);
TH1F *bcFDDAndRefBC = new TH1F("bcFDDAndRefBC",";BC ID [FDD AND Ref BC] ;Entries",3564,-0.5,3563.5);
TH1F *bcFDDAndNotRefBC = new TH1F("bcFDDAndNotRefBC",";BC ID [FDD AND and not in Ref BC] ;Entries",3564,-0.5,3563.5);


TH1F *bcVertexRefBC = new TH1F("bcVertexRefBC",";BC ID [vertex Ref BC] ;Entries",3564,-0.5,3563.5);
TH1F *bcVertexNotRefBC = new TH1F("bcVertexNotRefBC",";BC ID [vertex and not in Ref BC] ;Entries",3564,-0.5,3563.5);

TH1F *bcMultiplicityTrigger1 = new TH1F("bcMultiplicityTrigger1",";BC ID [Mult trig 1] ;Entries",3564,-0.5,3563.5);
TH1F *bcMultiplicityTrigger2 = new TH1F("bcMultiplicityTrigger2",";BC ID [Mult trig 2] ;Entries",3564,-0.5,3563.5);
TH1F *bcMultiplicityTrigger3 = new TH1F("bcMultiplicityTrigger3",";BC ID [Mult trig 3] ;Entries",3564,-0.5,3563.5);

TH1F *bcMultiplicityTriggerNotRefBC1 = new TH1F("bcMultiplicityTriggerNotRefBC1",";BC ID [Mult trig 1 not Ref BC] ;Entries",3564,-0.5,3563.5);
TH1F *bcMultiplicityTriggerNotRefBC2 = new TH1F("bcMultiplicityTriggerNotRefBC2",";BC ID [Mult trig 1 not Ref BC] ;Entries",3564,-0.5,3563.5);
TH1F *bcMultiplicityTriggerNotRefBC3 = new TH1F("bcMultiplicityTriggerNotRefBC3",";BC ID [Mult trig 1 not Ref BC] ;Entries",3564,-0.5,3563.5);

//-----------------------------------------------
// bunch crossings
TH1F *allBC_H = new TH1F("allBC_H",";BC ID;Entries",3564,-0.5,3563.5);
TH1F *noPMTBC_H = new TH1F("noPMTBC_H",";BC ID;Entries",3564,-0.5,3563.5);
TH1F *cOnlyBC_H = new TH1F("cOnlyBC_H",";BC ID for signals in C-side only;Entries",3564,-0.5,3563.5);
TH1F *aOnlyBC_H = new TH1F("aOnlyBC_H",";BC ID for signals in A-side only;Entries",3564,-0.5,3563.5);
TH1F *acBC_H = new TH1F("acBC_H",";BC ID for signals in A- and C-sides;Entries",3564,-0.5,3563.5);
TH1F *bcAll = new TH1F("bcAll",";BC ID [ALL] for signals ;Entries",3564,-0.5,3563.5);
TH1F *bcOr = new TH1F("bcOr",";BC ID [OR] for signals ;Entries",3564,-0.5,3563.5);
TH1F *bcAnd = new TH1F("bcAnd",";BC ID [AND] for signals ;Entries",3564,-0.5,3563.5);
TH2F *adcChargeVsChanneId = new TH2F("adcChargeVsChanneId","adcCharge Vs ChanneId;charge in ADC ; Ch ID",4196,-100.5,4095.5,16,0,16);
TH2F *adcChargeVsChanneIdRefBCs = new TH2F("adcChargeVsChanneIdRefBCs","adcCharge Vs ChanneId [only for ref BCs];charge in ADC ; Ch ID",4196,-100.5,4095.5,16,0,16);
TH2F *timeVsChanneId = new TH2F("timeVsChanneId","time Vs ChanneId;time (TDC) ; Ch ID",2001,-1000.5,1000.5,16,0,16);
TH2F *timeVsChanneIdNoRefBC = new TH2F("timeVsChanneIdNoRefBC","time (no BC) Vs ChanneId;time (TDC) ; Ch ID",2001,-1000.5,1000.5,16,0,16);
TH2F *timeVsChanneIdRefBCs = new TH2F("timeVsChanneIdRefBCs","time Vs ChanneId [only for ref BCs];time (TDC) ; Ch ID",2001,-1000.5,1000.5,16,0,16);
TH2F *BCVsAdcCharge = new TH2F("BCVsAdcCharge","BC Vs ADC charge; BC; charge in ADC",3564,-0.5,3563.5,4196,-100.5,4095.5);
TH2F *BCVsTime = new TH2F("BCVsTime","aBC Vs ADC charge ; Ch ID",3564,-0.5,3563.5,2001,-1000.5,1000.5);
TH1F *avgTimeAFromDigit = new TH1F("avgTimeAFromDigit",";Avg time A (ns); ",2001,-20.5,20.5);
TH1F *avgTimeCFromDigit = new TH1F("avgTimeCFromDigit",";Avg time C (ns); ",2001,-20.5,20.5);
TH1F *avgTimeAFromDigitRefBC = new TH1F("avgTimeAFromDigitRefBC",";Avg time A (ns); ",2001,-20.5,20.5);
TH1F *avgTimeCFromDigitRefBC = new TH1F("avgTimeCFromDigitRefBC",";Avg time C (ns); ",2001,-20.5,20.5);
TH1F *vertex = new TH1F("zvertex","; z vertex (in cm);",201,-100.5,100.5);
TH1F *vertexRefBC = new TH1F("vertexRefBC","; z vertex (in cm);",201,-100.5,100.5);

TH2F *avgTimeDiffVsSumFromDigit = new TH2F("avgTimeDiffVsSumFromDigit","avgTimeDiffVsSumFromDigit; (tA - tC)/2 ; (tA + tC)/2",550,-50.5,50.5,550,-50.5,50.5);
TH2F *normalAvgTimeDiffVsSumFromDigit = new TH2F("normalAvgTimeDiffVsSumFromDigit","normalAvgTimeDiffVsSumFromDigit; (tA - tC)/2 ; (tA + tC)/2",550,-50.5,50.5,550,-50.5,50.5);
TH2F *adcSatutatedChargeVsChanneId = new TH2F("adcSatutatedChargeVsChanneId","adcCharge for (Satuaration BC +5 BC ) Vs ChanneId;charge in ADC ; Ch ID",4196,-100.5,4095.5,16,0,16);
TH2F *adcSatutatedTimeVsChanneId = new TH2F("adcSatutatedTimeVsChanneId","Time for (Satuaration BC +5 BC ) Vs ChanneId; time (ns); Ch ID",2001,-1000.5,1000.5,16,0,16);
TH2F *adcSatutatedDeltaBCVsChanneId = new TH2F("adcSatutatedDeltaBCVsChanneId","(Delta BC) Vs ChanneId; #Delta{BC} ; Ch ID",41,-20.5,20.5,16,0,16);
TH2F *ChannelChargeNoBC_H = new TH2F("ChannelChargeNoBC_H","adcCharge (no BC) Vs ChanneId;charge in ADC ; Ch ID",4196,-100.5,4095.5,16,0,16);

//TH1F *pmtBC_H[16];
TH1F *pmtBC_H[16];
TH1F *aQuadBC_H[4];
TH1F *cQuadBC_H[4];

//-----------------------------------------------
// charge and time per PMT
TH1F *adcPMT_H[16];
TH2F * pmtChargeCorrelationFrontAndBackLayer[16];
TH2F * pmtTimeCorrelationFrontAndBackLayer[16];
TH2F *adcPMTWithBC_H[16];
TH1F *adcPMTcoincidence_H[16];
TH1F *adcPMTcoincCharge_H[16];
TH1F *adcPMTWithoutBC_H[16];
TH1F *timePMT_H[16];
TH2F *timePMTWithBC_H[16];
TH1F *timePMTcoincidence_H[16];
TH1F *bcPMTcoincidence_H[16];
TH2F *timePMTcoincidenceWithBC_H[16];
TH2F *timeChargePMT_H[16];
TH2F *timeChrgNoBC_PMT_H[16];
int sNCHANNELS_PM=19;

//-----------------------------------------------
// Flags
TH1F *flagsPMT_H[16];
TString feeNames[4] = {"isGateAndTVDC","isGate","isInTVDC","Qcut"};

//---------------------------------------------------
//Global variables
std::vector<int> refBCsVec;

std::map<int, string> mMapChTrgNames;// map to store FEE bits(8)
TH2F* mHistChDataBits;
//-----------------------------------------------
void initHistograms()
{
  mMapChTrgNames.insert({ o2::fdd::ChannelData::EEventDataBit::kNumberADC, "NumberADC" });
  mMapChTrgNames.insert({ o2::fdd::ChannelData::EEventDataBit::kIsDoubleEvent, "IsDoubleEvent" });
  mMapChTrgNames.insert({ o2::fdd::ChannelData::EEventDataBit::kIsTimeInfoNOTvalid, "IsTimeInfoNOTvalid" });
  mMapChTrgNames.insert({ o2::fdd::ChannelData::EEventDataBit::kIsCFDinADCgate, "IsCFDinADCgate" });
  mMapChTrgNames.insert({ o2::fdd::ChannelData::EEventDataBit::kIsTimeInfoLate, "IsTimeInfoLate" });
  mMapChTrgNames.insert({ o2::fdd::ChannelData::EEventDataBit::kIsAmpHigh, "IsAmpHigh" });
  mMapChTrgNames.insert({ o2::fdd::ChannelData::EEventDataBit::kIsEventInTVDC, "IsEventInTVDC" });
  mMapChTrgNames.insert({ o2::fdd::ChannelData::EEventDataBit::kIsTimeInfoLost, "IsTimeInfoLost" });

 mHistChDataBits = new TH2F("ChannelDataBits", "ChannelData bits per ChannelID;Channel;Bit", sNCHANNELS_PM, 0, sNCHANNELS_PM, mMapChTrgNames.size(), 0, mMapChTrgNames.size());

  for (const auto& entry : mMapChTrgNames) {
    mHistChDataBits->GetYaxis()->SetBinLabel(entry.first + 1, entry.second.c_str());
  }
  // define histograms stored in arrays
  int BackOrFrontPmts[] = {4,5,6,7,0,1,2,3,12,13,14,15,8,9,10,11};
  for(int i=0;i<16;i++) {

    pmtChargeCorrelationFrontAndBackLayer[i] = new TH2F(Form("pmtChargeCorrelationFrontAndBackLayer%d_H",i),Form(";PMT %d;PMT %d",i, BackOrFrontPmts[i]),4196,-100.5,4095.5,4196,-100.5,4095.5);
    pmtTimeCorrelationFrontAndBackLayer[i] = new TH2F(Form("pmtTimeCorrelationFrontAndBackLayer%d_H",i),Form(";PMT %d;PMT %d",i, BackOrFrontPmts[i]),/*4196,-100.5,4095.5*/800,-30,30,800,-30,30);
    pmtBC_H[i]=new TH1F(Form("pmtBC_%d_H",i),Form(";BC ID for PMT %d;Entries",i),3564,-0.5,3563.5);
    adcPMT_H[i]=new TH1F(Form("adcPMT_%d_H",i),Form(";ADC counts for PMT %d;Entries",i),4110,-13.5,4096.5);
    adcPMTWithBC_H[i]=new TH2F(Form("adcPMTWithBC_%d_H",i),Form(";BC ID;ADC counts for PMT %d",i),3564,-0.5,3563.5, 4110,-13.5,4096.5);

    adcPMTcoincidence_H[i]=new TH1F(Form("adcPMTcoincidence_%d_H",i),
				    Form(";ADC counts for PMT %d in coincidence with 2nd layer;Entries",i),4230,-133.5,4096.5);

    adcPMTcoincCharge_H[i]=new TH1F(Form("adcPMTcoincCharge_%d_H",i),
				    Form(";ADC counts for PMT %d in Charge coinc. with 2nd layer;Entries",i),4230,-133.5,4096.5);

    adcPMTWithoutBC_H[i]=new TH1F(Form("adcPMTWithoutBC_%d_H",i),
				    Form(";ADC counts for PMT %d ;Entries",i),4230,-133.5,4096.5);

    timePMT_H[i]=new TH1F(Form("timePMT_%d_H",i),Form(";time for PMT %d (ns); Entires",i),800,-10,30);
    timePMTWithBC_H[i]=new TH2F(Form("timePMTWithBC_%d_H",i),Form(";BC ID; time for PMT %d (ns)",i),3564,-0.5,3563.5,800,-30,30);
    timePMTcoincidence_H[i]=new TH1F(Form("timePMTcoincidence_%d_H",i),
				     Form(";time for PMT %d in coincidence with 2nd layer (ns); Entires",i),800,-10,30);
    bcPMTcoincidence_H[i]=new TH1F(Form("bcPMTcoincidence_%d_H",i),
             Form(";BC PMT %d in coincidence with 2nd layer (ns); Entires",i),3564,-0.5,3563.5);
    timePMTcoincidenceWithBC_H[i]=new TH2F(Form("timePMTcoincidenceWithBC_%d_H",i),
             Form("; BC ID;time for PMT %d in coincidence with 2nd layer (ns)",i),
             3564,-0.5,3563.5,800,-10,30);

    timeChargePMT_H[i]=new TH2F(Form("timeChrgCorrelation_PMT_%d_H",i),
    Form("time and charge correlation for PMT %d;ADC counts;time (ns)",i),
    4196, -100.5,4095.5,2001,-20.5,20.5);
    // TH2F *timeChargePMT_H[16];

    timeChrgNoBC_PMT_H[i]=new TH2F(Form("timeChrgNoBC_PMT_%d_H",i),
    Form("time and charge correlation for PMT %d (Not in colliding BC);ADC counts;time (ns)",i),
    4196, -100.5,4095.5,2001,-20.5,20.5);

    flagsPMT_H[i]=new TH1F(Form("flagsPMT_%d_H",i),";; Entires",4,0.5,4.5);
    flagsPMT_H[i]->GetXaxis()->SetBinLabel(1, "in time, in gate");
    flagsPMT_H[i]->GetXaxis()->SetBinLabel(2, "not in time, in gate");
    flagsPMT_H[i]->GetXaxis()->SetBinLabel(3, "in time, not in gate");
    flagsPMT_H[i]->GetXaxis()->SetBinLabel(4, "not in time, not in gate");
  }
  for(int i=0;i<4;i++) {
    aQuadBC_H[i]=new TH1F(Form("aQuadBC_%d_H",i),Form(";BC ID for quadrant %d in A-side; Entries",i),3564,-0.5,3563.5);
    cQuadBC_H[i]=new TH1F(Form("cQuadBC_%d_H",i),Form("cQuadBC_%d_H;BC ID for quadrant %d in A-side; Entries",i,i),3564,-0.5,3563.5);
  }
}

////////////////////////////////////////////////
//---------calculate avg time-------------------
////////////////////////////////////////////////
float DUMMY_TIME = -50000;
float timePerTDC = 0.013;
enum timeSide{
  timeA,
  timeC
};

bool isAside(int chID){
if (chID > 7)  return 1;
else return 0;
}
bool isCside(int chID){
if (chID < 8)  return 1;
else return 0;
}

std::array<float,2>  avgTime(gsl::span<const o2::fdd::ChannelData> chDataArr) {

Float_t timeFDA = 0, timeFDC = 0;
Float_t weightFDA = 0.0, weightFDC = 0.0;
int inTimeA =0, inTimeC =0;


for (auto chData:chDataArr) {
  Float_t timeErr = 1;
  Float_t adc = chData.mChargeADC;
  Float_t time = chData.mTime*timePerTDC; //TDC to ns
  Float_t pmt = (int)chData.mPMNumber;

auto fee = std::bitset<8>(chData.mFEEBits);
bool inTime = fee[o2::fdd::ChannelData::EEventDataBit::kIsEventInTVDC];

if(adc > 5) timeErr = 1./adc;
if(isAside(pmt)) {
inTimeA +=inTime;
timeFDA += time/(timeErr*timeErr);
weightFDA += 1./(timeErr*timeErr);
}//a side pmts

//--calcualte avg time and weight factor
if(isCside(pmt)) {
inTimeC +=inTime;
timeFDC += time/(timeErr*timeErr);
weightFDC += 1./(timeErr*timeErr);
}//c side pmts
}
std::array<float, 2> mCollisionTime = {DUMMY_TIME, DUMMY_TIME};
if (inTimeA > 0) mCollisionTime[timeSide::timeA] = (weightFDA > 1) ? (timeFDA / weightFDA ) : DUMMY_TIME;
if (inTimeC > 0) mCollisionTime[timeSide::timeC] = (weightFDC > 1) ? (timeFDC / weightFDC ) : DUMMY_TIME;
//std::cout<<"Avg time A"<<mCollisionTime[timeSide::timeA]<<"  Avg time C "<<mCollisionTime[timeSide::timeC]<<std::endl;
return mCollisionTime;
}

std::array<float,2>  avgTimeWithoutTrigger(gsl::span<const o2::fdd::ChannelData> chDataArr) {

Float_t timeFDA = 0, timeFDC = 0;
Float_t weightFDA = 0.0, weightFDC = 0.0;
int inTimeA =0, inTimeC =0;


for (auto chData:chDataArr) {
  Float_t timeErr = 1;
  Float_t adc = chData.mChargeADC;
  Float_t time = chData.mTime*timePerTDC; //TDC to ns
  Float_t pmt = (int)chData.mPMNumber;

auto fee = std::bitset<8>(chData.mFEEBits);
bool inTime = fee[o2::fdd::ChannelData::EEventDataBit::kIsEventInTVDC];

if(adc > 5) timeErr = 1./adc;
if(isAside(pmt)) {
inTimeA +=inTime;
timeFDA += time/(timeErr*timeErr);
weightFDA += 1./(timeErr*timeErr);
}//a side pmts

//--calcualte avg time and weight factor
if(isCside(pmt)) {
inTimeC +=inTime;
timeFDC += time/(timeErr*timeErr);
weightFDC += 1./(timeErr*timeErr);
}//c side pmts
}
std::array<float, 2> mCollisionTime = {DUMMY_TIME, DUMMY_TIME};
mCollisionTime[timeSide::timeA] = (weightFDA > 1) ? (timeFDA / weightFDA ) : DUMMY_TIME;
mCollisionTime[timeSide::timeC] = (weightFDC > 1) ? (timeFDC / weightFDC ) : DUMMY_TIME;
//std::cout<<"Avg time A"<<mCollisionTime[timeSide::timeA]<<"  Avg time C "<<mCollisionTime[timeSide::timeC]<<std::endl;
return mCollisionTime;
}

std::array<float,2>  normalAvgTimeWithoutTrigger(gsl::span<const o2::fdd::ChannelData> chDataArr) {

Float_t timeFDA = 0, timeFDC = 0;
Float_t weightFDA = 0.0, weightFDC = 0.0;
int nPMTA =0, nPMTC =0;
for (auto chData:chDataArr) {
  Float_t time = chData.mTime*timePerTDC; //TDC to ns
  Float_t pmt = (int)chData.mPMNumber;
if(isAside(pmt)) {
nPMTA ++;
timeFDA += time;
}//a side pmts
//--calcualte avg time and weight factor
if(isCside(pmt)) {
nPMTC ++;
timeFDC += time;
}//c side pmts
}
std::array<float, 2> mCollisionTime = {DUMMY_TIME, DUMMY_TIME};
mCollisionTime[timeSide::timeA] = (nPMTA > 0) ? (timeFDA / nPMTA ) : DUMMY_TIME;
mCollisionTime[timeSide::timeC] = (nPMTC > 0) ? (timeFDC / nPMTC ) : DUMMY_TIME;
//std::cout<<"Avg time A"<<mCollisionTime[timeSide::timeA]<<"  Avg time C "<<mCollisionTime[timeSide::timeC]<<std::endl;
return mCollisionTime;
}

enum chargeType{
sumChA,
sumChC,
sumChBoth
};

std::array<float,3 > getSumCharge(gsl::span<const o2::fdd::ChannelData> chDataArr){

Float_t sumChFDA = 0, sumChFDC = 0, sumChFDD = 0 ;
for (auto chData:chDataArr) {

auto fee = std::bitset<8>(chData.mFEEBits);
bool inGate = fee[o2::fdd::ChannelData::EEventDataBit::kIsCFDinADCgate];
if (!inGate) continue;
Float_t Ch = chData.mChargeADC; //TDC to ns
Float_t pmt = (int)chData.mPMNumber;
if(isAside(pmt)) {
  sumChFDA+=Ch;
}// a side

if(isCside(pmt)) {
  sumChFDC+=Ch;
}//c side

}
sumChFDD = sumChFDA=sumChFDC;
std::array<float,3 > ch{sumChFDA, sumChFDC, sumChFDD};
return ch;
}

//-----headers to get BC filling scheme------
#include "CCDB/CcdbApi.h"
#include "CommonDataFormat/BunchFilling.h"
#include "CCDB/BasicCCDBManager.h"
#include "DataFormatsParameters/GRPObject.h"
#include "DataFormatsParameters/GRPLHCIFData.h"

using BCPattern = std::bitset<o2::constants::lhc::LHCMaxBunches>;
void getBcFillingPattern(unsigned int runnum, BCPattern& Aside, BCPattern& Cside, BCPattern& CollidingBunch){
  // Get the latest bunch filling scheme from production CCDB
  //auto& ccdb = o2::ccdb::BasicCCDBManager::instance();
  o2::ccdb::CcdbApi ccdb;
  //ccdb.setURL("http://alice-ccdb.cern.ch");
  ccdb.init(o2::base::NameConf::getCCDBServer());
  const auto headers = ccdb.retrieveHeaders("RCT/Info/RunInformation", std::map<std::string, std::string>(),runnum);
  const std::string tsKey = "SOR";
  uint64_t ts{};
  const auto &itTimestamp = headers.find(tsKey);
  if(itTimestamp!=headers.end()) {
    ts = std::stoll(itTimestamp->second);
  }

  std::map<std::string, std::string> mapMetadata;
  std::map<std::string, std::string> mapHeader;

  const auto *ptrGRPLHCIFData = ccdb.retrieveFromTFileAny<o2::parameters::GRPLHCIFData>("GLO/Config/GRPLHCIF",mapMetadata,ts,&mapHeader);
  const auto &bunchFilling = ptrGRPLHCIFData->getBunchFilling();
  // ptrGRPLHCIFData->print();
  CollidingBunch = bunchFilling.getBCPattern();
  Aside = bunchFilling.getBeamPattern(0);
  Cside = bunchFilling.getBeamPattern(1);

  std::cout<<std::endl;
  //---a and c side bunches without colllisons
  BCPattern AsideBunchOnly = ~Cside & Aside;
  BCPattern CsideBunchOnly = ~Aside & Cside;
  cout <<"\n Only A side bunch: ";
  for (int i = 0; i < (int)CollidingBunch.size(); i++)
  if (AsideBunchOnly.test(i)) cout<<  i << " ";
  std::cout<<std::endl;
  cout <<"\n Only C side bunch: ";
  for (int i = 0; i < (int)CollidingBunch.size(); i++)
  if (CsideBunchOnly.test(i)) cout<<  i << " ";
  std::cout<<std::endl;
  //bf.print();
}

/*
void getBcFillingPattern(int64_t timeStamp, BCPattern& Aside, BCPattern& Cside, BCPattern& CollidingBunch){
  // Get the latest bunch filling scheme from production CCDB
  auto& ccdb = o2::ccdb::BasicCCDBManager::instance();
  ccdb.setURL("http://alice-ccdb.cern.ch");
  o2::parameters::GRPLHCIFData *lhcif = ccdb.getForTimeStamp<o2::parameters::GRPLHCIFData>("GLO/Config/GRPLHCIF",timeStamp);
  if(!lhcif) return;
  o2::BunchFilling bf = lhcif->getBunchFilling();
  Aside = bf.getBeamPattern(0);//get A side filling
  Cside = bf.getBeamPattern(1);//get C side filling
  CollidingBunch = bf.getPattern();//bc pattern for colliding bunches
  cout <<"A side ";
  for (int i = 0; i < (int)Aside.size(); i++)
  if (Aside.test(i)) cout<< i << " ";
  std::cout<<std::endl;
  cout <<"C side ";
  for (int i = 0; i < (int)Cside.size(); i++)
  if (Cside.test(i)) cout<<  i << " ";
  std::cout<<std::endl;
  cout <<"Colliding bunch: ";
  for (int i = 0; i < (int)CollidingBunch.size(); i++)
  if (CollidingBunch.test(i)) {
  refBCsVec.push_back(i);
  cout<<  i << " ";
}
  std::cout<<std::endl;
  //---a and c side bunches without colllisons
  BCPattern AsideBunchOnly = ~Cside & Aside;
  BCPattern CsideBunchOnly = ~Aside & Cside;
  cout <<"\n Only A side bunch: ";
  for (int i = 0; i < (int)CollidingBunch.size(); i++)
  if (AsideBunchOnly.test(i)) cout<<  i << " ";
  std::cout<<std::endl;
  cout <<"\n Only C side bunch: ";
  for (int i = 0; i < (int)CollidingBunch.size(); i++)
  if (CsideBunchOnly.test(i)) cout<<  i << " ";
  std::cout<<std::endl;
  //bf.print();
}*/




//-----------------------------------------------
void fillChannelTimeCorrelation(Long64_t BC, gsl::span<const o2::fdd::ChannelData> chData)
{
  int nPMT = chData.size();
  bool hasData[16] = {0};
  float adcCharge[16] = {0};
  float adcTime[16] = {0};
  for(int iPMT = 0; iPMT<nPMT;iPMT++) {
    int  iChannel = chData[iPMT].mPMNumber;
         hasData[iChannel] = 1;
         adcTime[iChannel] = float(chData[iPMT].mTime)*timePerTDC; //TDC to ns
        // std::cout<<"adc ch "<<adcCharge[iChannel]<<std::endl;
  }

  for(int iPMT = 0; iPMT<nPMT;iPMT++) {
  // get the PMT flags
  int  iChannel = chData[iPMT].mPMNumber;
  //std::cout<<"Active channel "<<iChannel<<std::endl;
  if (iChannel== 0 && hasData[4])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel+4]);
  } // 0-4
  if (iChannel== 1 && hasData[5])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel+4]);// adcTime[iChannel
  } // 1-5
  if (iChannel== 2 && hasData[6])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel+4]);
  } // 2-6
  if (iChannel== 3 && hasData[7])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel+4]);
  } // 3-7
  if (iChannel== 4 && hasData[0])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel-4]);
  } // 4-0
  if (iChannel== 5 && hasData[1])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel-4]);
  } // 5-1
  if (iChannel== 6 && hasData[2])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel-4]);
  } // 6-2
  if (iChannel== 7 && hasData[3])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel-4]);
  } // 7-3
  if (iChannel== 8 && hasData[12])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel+4]);
  } // 8-12
  if (iChannel== 9 && hasData[13])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel+4]);
  } // 9-13
  if (iChannel== 10 && hasData[14])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel+4]);
  } // 10-14
  if (iChannel== 11 && hasData[15])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel+4]);
  } // 11-15
  if (iChannel== 12 && hasData[8])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel-4]);
} // 12-8
  if (iChannel== 13 && hasData[9])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel-4]);
  } // 13-9
  if (iChannel== 14 && hasData[10])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel-4]);
  } // 14-10
  if (iChannel== 15 && hasData[11])
  {
  pmtTimeCorrelationFrontAndBackLayer[iChannel]->Fill(adcTime[iChannel], adcTime[iChannel-4]);
  } // 15-11
}
}

void fillChannelDataCorrelation(Long64_t BC, gsl::span<const o2::fdd::ChannelData> chData, float adcThrd = 3800)
{

  int nPMT = chData.size();
  bool hasData[16] = {0};
  float adcCharge[16] = {0};
  float adcTime[16] = {0};
  for(int iPMT = 0; iPMT<nPMT;iPMT++) {
    int  iChannel = chData[iPMT].mPMNumber;
         hasData[iChannel] = 1;
         adcCharge[iChannel] = float(chData[iPMT].mChargeADC);
        // std::cout<<"adc ch "<<adcCharge[iChannel]<<std::endl;
  }

  for(int iPMT = 0; iPMT<nPMT;iPMT++) {
  // get the PMT flags
  int  iChannel = chData[iPMT].mPMNumber;
  //std::cout<<"Active channel "<<iChannel<<std::endl;
  if (iChannel== 0 && (adcCharge[iChannel] > adcThrd) && hasData[4])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel], adcCharge[iChannel+4]); // 0-4
  } // 0-4
  if (iChannel== 1 && (adcCharge[iChannel] > adcThrd) && hasData[5])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel+4]); // 1-5
  } // 1-5
  if (iChannel== 2 && (adcCharge[iChannel] > adcThrd) && hasData[6])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel+4] ); // 2-6
  } // 2-6
  if (iChannel== 3 && (adcCharge[iChannel] > adcThrd) && hasData[7])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel+4] ); // 3-7
  } // 3-7
  if (iChannel== 4 && (adcCharge[iChannel] > adcThrd) && hasData[0])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel-4]); // 4-0
  } // 4-0
  if (iChannel== 5 && (adcCharge[iChannel] > adcThrd) && hasData[1])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel-4]); // 5-1
  } // 5-1
  if (iChannel== 6 && (adcCharge[iChannel] > adcThrd) && hasData[2])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel-4]); // 6-2
  } // 6-2
  if (iChannel== 7 && (adcCharge[iChannel] > adcThrd) && hasData[3])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel-4]); // 7-3
  } // 7-3
  if (iChannel== 8 && (adcCharge[iChannel] > adcThrd) && hasData[12])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel+4] ); // 8-12
  } // 8-12
  if (iChannel== 9 && (adcCharge[iChannel] > adcThrd) && hasData[13])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel+4] ); // 9-13
  } // 9-13
  if (iChannel== 10 && (adcCharge[iChannel] > adcThrd) && hasData[14])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel+4] ); // 10-14
  } // 10-14
  if (iChannel== 11 && (adcCharge[iChannel] > adcThrd) && hasData[15])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel+4] ); // 11-15
  } // 11-15
  if (iChannel== 12 && (adcCharge[iChannel] > adcThrd) && hasData[8])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel-4]); // 12-8
  } // 12-8
  if (iChannel== 13 && (adcCharge[iChannel] > adcThrd) && hasData[9])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel-4]); // 13-9
  } // 13-9
  if (iChannel== 14 && (adcCharge[iChannel] > adcThrd) && hasData[10])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel-4]); // 14-10
  } // 14-10
  if (iChannel== 15 && (adcCharge[iChannel] > adcThrd) && hasData[11])
  {
  pmtChargeCorrelationFrontAndBackLayer[iChannel]->Fill(adcCharge[iChannel],adcCharge[iChannel-4]); // 15-11
  } // 15-11
}
 //std::cout<<"BC  "<<BC<<std::endl;
}
//-----------------------------------------------
void saveHistograms(TString useBit,int runNumber)
{
  TFile *fHist = 0;
  fHist = new TFile(Form("Analysis_%s_%i.root",useBit.Data(),runNumber),"recreate");
  fHist->cd();
  // structure of the file
  nBCperEntry_H->Write();
  nBCperEntryWithPMT_H->Write();
  nPMTperBC_H->Write();
  pmtOccupancy_H->Write();
  nPMTAperBC_H->Write();
  nPMTCperBC_H->Write();
  // bunch crossings
  allBC_H->Write();
  noPMTBC_H->Write();
  aOnlyBC_H->Write();
  cOnlyBC_H->Write();
  acBC_H->Write();
  bcAll->Write();
  bcOr->Write();
  bcAnd->Write();


  bcFDDAnd->Write();
  bcFDDAndRefBC->Write();
  bcFDDAndNotRefBC->Write();

  bcVertexRefBC->Write();
  bcVertexNotRefBC->Write();

  bcMultiplicityTrigger1->Write();
  bcMultiplicityTrigger2->Write();
  bcMultiplicityTrigger3->Write();

  bcMultiplicityTriggerNotRefBC1->Write();
  bcMultiplicityTriggerNotRefBC2->Write();
  bcMultiplicityTriggerNotRefBC3->Write();

  grOrA->Write();
  grOrARefBC->Write();

  grOrC->Write();
  grOrCRefBC->Write();

  grVertex->Write();
  grVertexRefBC->Write();

  adcChargeVsChanneId->Write();
  adcChargeVsChanneIdRefBCs->Write();
  timeVsChanneIdRefBCs->Write();
  timeVsChanneId->Write();
  BCVsAdcCharge->Write();
  BCVsTime->Write();
  avgTimeAFromDigit->Write();
  avgTimeCFromDigit->Write();
  avgTimeAFromDigitRefBC->Write();
  avgTimeCFromDigitRefBC->Write();
  vertex->Write();
  vertexRefBC->Write();
  avgTimeDiffVsSumFromDigit->Write();
  normalAvgTimeDiffVsSumFromDigit->Write();
  adcSatutatedChargeVsChanneId->Write();
  adcSatutatedTimeVsChanneId->Write();
  adcSatutatedDeltaBCVsChanneId->Write();
  mHistChDataBits->Write();
  ChannelChargeNoBC_H->Write();
  timeVsChanneIdNoRefBC->Write();

  for(int i=0;i<16;i++) {
    pmtBC_H[i]->Write();
    pmtChargeCorrelationFrontAndBackLayer[i]->Write();
    pmtTimeCorrelationFrontAndBackLayer[i]->Write();
    adcPMT_H[i]->Write();
    adcPMTWithBC_H[i]->Write();
    adcPMTcoincidence_H[i]->Write();
    adcPMTcoincCharge_H[i]->Write();
    timePMT_H[i]->Write();
    timePMTWithBC_H[i]->Write();
    timePMTcoincidence_H[i]->Write();
    bcPMTcoincidence_H[i]->Write();
    timePMTcoincidenceWithBC_H[i]->Write();
    flagsPMT_H[i]->Write();
    timeChargePMT_H[i]->Write();
    timeChrgNoBC_PMT_H[i]->Write();
    adcPMTWithoutBC_H[i]->Write();// charges outside the BC

  }
  for(int i=0;i<4;i++) {
    aQuadBC_H[i]->Write();
    cQuadBC_H[i]->Write();
  }
  // close the file
  fHist->Close();
}
