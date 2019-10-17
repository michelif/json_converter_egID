#include "CommonTools/CandAlgos/interface/ModifyObjectValueBase.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoEgamma/EgammaTools/interface/json_wrapper.h"

class EGSFModifier : public ModifyObjectValueBase {
public:
  EGSFModifier(const edm::ParameterSet& conf);
  ~EGSFModifier() override{}
  
  void modifyObject(pat::Electron& ele) const final;
  void modifyObject(pat::Photon& pho) const final;
  

};

EGSFModifier::EGSFModifier(const edm::ParameterSet& conf):
  ModifyObjectValueBase(conf)
{
  //std::string sfName="filename";
  std::string sfName="run2_eleIDs.json";
  if(1){
  }else{
    throw cms::Exception("ConfigError") <<"Error constructing EGSFModifier, sf file name "<<sfName<<" not valid";
  } 

}


void EGSFModifier::modifyObject(pat::Electron& ele)const
{
  auto eta = ele.eta();
  auto pt  = ele.pt();
  std::string year = "2018";
  std::string ID = "mvaEleID-Fall17-noIso-V2-wp80";
  
  SF_Reader sf;
  sf.read_json("run2_eleIDs.json");
  cout << sf.error (year, ID, "pt:[20.0,35.0]", "eta:[1.444,1.566]") << endl;

  double value = sf.value (year, ID, "pt:[20.0,35.0]", "eta:[1.444,1.566]");
  double error = sf.error (year, ID, "pt:[20.0,35.0]", "eta:[1.444,1.566]");

  ele.addUserFloat(ID + "_value", value);
  ele.addUserFloat(ID + "_error", error);
  ele.addUserFloat("daje",1);
						
}

void EGSFModifier::modifyObject(pat::Photon& pho)const
{
  pho.addUserFloat("daje",1);
}

DEFINE_EDM_PLUGIN(ModifyObjectValueFactory,
		  EGSFModifier,
		  "EGSFModifier");
