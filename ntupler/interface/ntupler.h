#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateIsolation.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Scalers/interface/LumiScalers.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTEventAnalyzerAOD.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "TTree.h"

using namespace std;
using namespace reco;
using namespace edm;

class ntupler : public edm::EDAnalyzer
{
public:
	ntupler(const edm::ParameterSet &iConfig);
	virtual ~ntupler() {};

	virtual void analyze(const edm::Event &iEvent, const edm::EventSetup &iSetup);
	virtual void beginJob();
	virtual void endJob();
	virtual void beginRun(const edm::Run &iRun, const edm::EventSetup &iSetup);
	virtual void endRun(const edm::Run &iRun, const edm::EventSetup &iSetup);

private:
	void Init();
	void Make_Branch();
	void Fill_HLT(const edm::Event &iEvent);
	void Fill_Muon(const edm::Event &iEvent);
	void Fill_HLTMuon(const edm::Event &iEvent);
	void Fill_L1Muon(const edm::Event &iEvent);
	void Fill_GenParticle(const edm::Event &iEvent);

	edm::EDGetTokenT< std::vector<reco::Muon> >					Token_OfflineMuon;
	edm::EDGetTokenT< reco::VertexCollection >					Token_OfflineVertex;
	edm::EDGetTokenT<edm::TriggerResults>						Token_TriggerResults;
	edm::EDGetTokenT<trigger::TriggerEvent>						Token_TriggerEvent;

	edm::EDGetTokenT<reco::RecoChargedCandidateCollection> 		Token_L3Muon;
	edm::EDGetTokenT<reco::RecoChargedCandidateCollection>		Token_L2Muon;
	edm::EDGetTokenT<l1t::MuonBxCollection> 					Token_L1Muon;

	edm::EDGetTokenT<reco::RecoChargedCandidateCollection> 		Token_TkMuon;

	edm::EDGetTokenT<reco::IsoDepositMap> 						Token_ChargedIsoDep;
	edm::EDGetTokenT<reco::RecoChargedCandidateIsolationMap> 	Token_NeutralIsoDep;
	edm::EDGetTokenT<reco::RecoChargedCandidateIsolationMap> 	Token_PhotonIsoDep;

	edm::EDGetTokenT<double> 									Token_Rho;
	edm::EDGetTokenT<double> 									Token_OfflineRho;

	edm::EDGetTokenT<double> 									Token_RhoECAL;
	edm::EDGetTokenT<double> 									Token_RhoHCAL;

	edm::EDGetTokenT<edm::ValueMap<float>> 						Token_OfflineECALPFIso03;
	edm::EDGetTokenT<edm::ValueMap<float>> 						Token_OfflineHCALPFIso03;
	edm::EDGetTokenT<edm::ValueMap<float>> 						Token_OfflineECALPFIso04;
	edm::EDGetTokenT<edm::ValueMap<float>> 						Token_OfflineHCALPFIso04;

	edm::EDGetTokenT<LumiScalersCollection> 					Token_LumiScaler;
	edm::EDGetTokenT< std::vector<PileupSummaryInfo> > 			Token_PUSummaryInfo;
	edm::EDGetTokenT< GenEventInfoProduct >						Token_GenEventInfo;
	edm::EDGetTokenT<reco::GenParticleCollection> 				Token_GenParticle;

	TTree *ntuple;
	static const int ArrSize = 2000;

	int RunNum;
	int LumiBlockNum;
	unsigned long long EventNum;

	int nVertices;
	double Rho_Offline;
	double BX_ID;
	double InstLumi;
	int TruePU;
	double GenEventWeight;

	int nGenParticle;
	int GenParticle_ID[ArrSize];
	int GenParticle_Status[ArrSize];
	int GenParticle_Mother[ArrSize];

	double GenParticle_Pt[ArrSize];
	double GenParticle_Eta[ArrSize];
	double GenParticle_Phi[ArrSize];
	double GenParticle_Px[ArrSize];
	double GenParticle_Py[ArrSize];
	double GenParticle_Pz[ArrSize];
	double GenParticle_E[ArrSize];
	double GenParticle_Charge[ArrSize];

	int GenParticle_isPrompt[ArrSize];
	int GenParticle_isPromptFinalState[ArrSize];
	int GenParticle_isTauDecayProduct[ArrSize];
	int GenParticle_isPromptTauDecayProduct[ArrSize];
	int GenParticle_isDirectPromptTauDecayProductFinalState[ArrSize];
	int GenParticle_isHardProcess[ArrSize];
	int GenParticle_isLastCopy[ArrSize];
	int GenParticle_isLastCopyBeforeFSR[ArrSize];
	int GenParticle_isPromptDecayed[ArrSize];
	int GenParticle_isDecayedLeptonHadron[ArrSize];
	int GenParticle_fromHardProcessBeforeFSR[ArrSize];
	int GenParticle_fromHardProcessDecayed[ArrSize];
	int GenParticle_fromHardProcessFinalState[ArrSize];
	int GenParticle_isMostlyLikePythia6Status3[ArrSize];

	vector< std::string > vec_FiredTrigger;
	vector< std::string > vec_FilterName;
	vector< double > vec_HLTObj_Pt;
	vector< double > vec_HLTObj_Eta;
	vector< double > vec_HLTObj_Phi;

	double Rho;
	double RhoECAL;
	double RhoHCAL;

	int nMuon;

	double Muon_Pt[ArrSize];
	double Muon_Eta[ArrSize];
	double Muon_Phi[ArrSize];
	double Muon_Px[ArrSize];
	double Muon_Py[ArrSize];
	double Muon_Pz[ArrSize];
	double Muon_dB[ArrSize];
	double Muon_Charge[ArrSize];
	int Muon_IsGLB[ArrSize];
	int Muon_IsSTA[ArrSize];
	int Muon_IsTRK[ArrSize];
	int Muon_IsPF[ArrSize];
	int Muon_IsTight[ArrSize];
	int Muon_IsMedium[ArrSize];
	int Muon_IsLoose[ArrSize];

	double Muon_PFIso03_Charged[ArrSize];
	double Muon_PFIso03_Neutral[ArrSize];
	double Muon_PFIso03_Photon[ArrSize];
	double Muon_PFIso03_SumPU[ArrSize];

	double Muon_PFIso04_Charged[ArrSize];
	double Muon_PFIso04_Neutral[ArrSize];
	double Muon_PFIso04_Photon[ArrSize];
	double Muon_PFIso04_SumPU[ArrSize];

	double Muon_PFCluster03_ECAL[ArrSize];
	double Muon_PFCluster03_HCAL[ArrSize];

	double Muon_PFCluster04_ECAL[ArrSize];
	double Muon_PFCluster04_HCAL[ArrSize];

	double Muon_NormChi2_GlbTrk[ArrSize];
	int Muon_nTrackerHit_GlbTrk[ArrSize];
	int Muon_nTrackerLayer_GlbTrk[ArrSize];
	int Muon_nPixelHit_GlbTrk[ArrSize];
	int Muon_nMuonHit_GlbTrk[ArrSize];

	double Muon_NormChi2_InnerTrk[ArrSize];
	int Muon_nTrackerHit_InnerTrk[ArrSize];
	int Muon_nTrackerLayer_InnerTrk[ArrSize];
	int Muon_nPixelHit_InnerTrk[ArrSize];

	double Muon_dxyVTX_BestTrk[ArrSize];
	double Muon_dzVTX_BestTrk[ArrSize];

	int Muon_nMatchedStation[ArrSize];
	int Muon_nMatchedRPCLayer[ArrSize];
	int Muon_StationMask[ArrSize];

	int nL3Muon;
	double L3Muon_Pt[ArrSize];
	double L3Muon_Eta[ArrSize];
	double L3Muon_Phi[ArrSize];
	double L3Muon_Charge[ArrSize];
	double L3Muon_TrkPt[ArrSize];
	double L3Muon_TrkIso[ArrSize];
	double L3Muon_ECALIso[ArrSize];
	double L3Muon_HCALIso[ArrSize];

	int nL2Muon;
	double L2Muon_Pt[ArrSize];
	double L2Muon_Eta[ArrSize];
	double L2Muon_Phi[ArrSize];
	double L2Muon_Charge[ArrSize];
	double L2Muon_TrkPt[ArrSize];

	int nTkMuon;
	double TkMuon_Pt[ArrSize];
	double TkMuon_Eta[ArrSize];
	double TkMuon_Phi[ArrSize];
	double TkMuon_Charge[ArrSize];
	double TkMuon_TrkPt[ArrSize];

	int nL1Muon;
	double L1Muon_Pt[ArrSize];
	double L1Muon_Eta[ArrSize];
	double L1Muon_Phi[ArrSize];
	double L1Muon_Charge[ArrSize];
	double L1Muon_Quality[ArrSize];
};
