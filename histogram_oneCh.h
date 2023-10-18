//histogram.h
// to define the histograms used in the analysis
//
//-----------------------------------------------
// structure of the file
TH1F *nBCperEntry_H = new TH1F("nBCperEntry_H",";Number of BC per tree entry;Entries",100,-0.5,99.5);


//-----------------------------------------------
// charge and time per PMT
TH1F *adcPMT_H[16];
int sNCHANNELS_PM=19;

//-----------------------------------------------
// BC vs charge 2-Dimension histograms
TH2F *BCVsChAonlyBC[16];
TH2F *BCVsChConlyBC[16];
TH2F *ChargeVsTime[16];
// BC distribution of signals outside a time window
TH2F *BCvsCharge_CollidingBC[16];
// BC vs Charge distribution of selected BC 
TH2F *nextBCvsCharge[16];

//-----------------------------------------------
// Flags
TH1F *flagsPMT_H[16];
TString feeNames[4] = {"isGateAndTVDC","isGate","isInTVDC","CollidingBC"};

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

    adcPMT_H[i]=new TH1F(Form("adcPMT_%d_H",i),Form(";ADC counts for PMT %d;Entries",i),4110,-13.5,4096.5);  
    BCVsChAonlyBC[i]= new TH2F(Form("BCVsChAonlyBC%d_H",i),"Colliding BC Vs Charge FDD-A; BC;charge",3565,-0.5,3564.5, 4200,-5.5,4094.5);
    BCVsChConlyBC[i]= new TH2F(Form("BCVsChConlyBC%d_H",i),"Colliding BC Vs Charge; BC;charge",3565,-0.5,3564.5, 4200,-5.5,4094.5);
    ChargeVsTime[i] = new TH2F(Form("ChargeVsTime%d_H",i),"Colliding BC, Charge Vs time ;charge (ADC counts);time (ns)",4100,-10.5,4189.5, 600,-30.,30.);
// BC distribution of signals outside a time window
    BCvsCharge_CollidingBC[i]= new TH2F(Form("BCvsCharge_CollidingBC_%d_H",i),"BC Vs Charge of colliding bunches; BC;charge",3565,-0.5,3564.5, 4200,-5.5,4094.5);
    nextBCvsCharge[i]= new TH2F(Form("nextBCvsCharge_%d_H",i), Form("charges of selected BC;BC;charge"),3565,-0.5,3564.5, 4200,-5.5,4094.5);

  }

}


void saveHistograms(TString useBit,int runNumber, double ChargeCoincThreshold = 0)
{
  TFile *fHist = 0;
  fHist = new TFile(Form("chrg_%s_%i.root",useBit.Data(),runNumber),"recreate");
  fHist->cd();
  
  nBCperEntry_H->Write();

  for(int i=0;i<16;i++) {
    adcPMT_H[i]->Write();
    BCVsChAonlyBC[i]->Write();
    BCVsChConlyBC[i]->Write();
    ChargeVsTime[i]->Write();
    BCvsCharge_CollidingBC[i]->Write();
    nextBCvsCharge[i]->Write();
  }
  
  // close the file
  fHist->Close();
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
  ptrGRPLHCIFData->print();
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
  Aside=AsideBunchOnly;
  Cside=CsideBunchOnly;

  /*
    for (int i = 0; i < (int)CollidingBunch.size(); i++) {
    if (CollidingBunch.test(i)) bcColliding->Fill(i);
    if (AsideBunchOnly.test(i)) bcAonly->Fill(i);
    if (CsideBunchOnly.test(i)) bcConly->Fill(i);
  }
  */

}
