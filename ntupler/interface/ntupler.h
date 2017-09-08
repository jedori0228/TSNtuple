#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

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
	int LumiBlackNum;
	unsigned long long EventNum;










}