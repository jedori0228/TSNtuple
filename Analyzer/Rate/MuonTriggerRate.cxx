#define nDataset 7
#include <Rate/TriggerRateTool.h>


void MuonTriggerRate( TString Trigger )
{
	// TString DataBasePath = gSystem->Getenv("KP_DATA_PATH");
	vector< TString > vec_Data = 
	{
		"/Users/KyeongPil_Lee/ServiceWorks/HLTReRun/v20170912_RateStudy/Test_v04_HLTPhysicsN/ntuple*.root"
		// "/Users/KyeongPil_Lee/ServiceWorks/TriggerStudyNtuple/Analyzer/Rate/Local/ntuple_withBugFIx_v3_HLTPhysics2.root",
		// "/Users/KyeongPil_Lee/ServiceWorks/TriggerStudyNtuple/Analyzer/Rate/Local/ntuple_withBugFIx_v4_HLTPhysics2.root"
	};

	vector< Int_t > vec_RunNum = 
	{
		301567, 301627, 301664, 301665, 301694, 
		301912, 301913, 301914, 301941, 301959
	};

	// vector< TString > vec_Trigger =
	// {
	// 	"HLT_IsoMu27_v13",
	// 	"HLT_IsoMu24_v10",
	// 	"HLT_Mu50_v11",
	// 	"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v12",
	// 	"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v13",
	// 	"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v3",
	// 	"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v3"
	// };

	TFile *f_output = TFile::Open("ROOTFile_MuonTriggerRate_"+Trigger+".root", "RECREATE");

	TriggerRateTool* tool = new TriggerRateTool();
	tool->Set_DataList( vec_Data );
	tool->Set_RunNumList( vec_RunNum );
	tool->Set_Trigger( Trigger );
	tool->Set_Output( f_output );
	tool->Analyze();
}
