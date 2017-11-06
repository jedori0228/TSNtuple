#define nDataset 8
// #define nDataset 7
#include <Rate/v01_Run305636/TriggerRateTool.h>

void MuonTriggerRate_withFix( TString Trigger )
{
	TString DataBasePath = gSystem->Getenv("KP_DATA_PATH");
	vector< TString > vec_Data = 
	{
		DataBasePath+"/92X/TSntuple_v20171031_withFix_EphemeralHLTPhysics1_Run2017Fv1/*.root",
		DataBasePath+"/92X/TSntuple_v20171031_withFix_EphemeralHLTPhysics2_Run2017Fv1/*.root",
		DataBasePath+"/92X/TSntuple_v20171031_withFix_EphemeralHLTPhysics3_Run2017Fv1/*.root",
		DataBasePath+"/92X/TSntuple_v20171031_withFix_EphemeralHLTPhysics4_Run2017Fv1/*.root",
		DataBasePath+"/92X/TSntuple_v20171031_withFix_EphemeralHLTPhysics5_Run2017Fv1/*.root",
		DataBasePath+"/92X/TSntuple_v20171031_withFix_EphemeralHLTPhysics6_Run2017Fv1/*.root",
		DataBasePath+"/92X/TSntuple_v20171031_withFix_EphemeralHLTPhysics7_Run2017Fv1/*.root",
		DataBasePath+"/92X/TSntuple_v20171031_withFix_EphemeralHLTPhysics8_Run2017Fv1/*.root"
	};

	vector< Int_t > vec_RunNum = 
	{
		305636
	};

	TFile *f_output = TFile::Open("ROOTFile_MuonTriggerRate_"+Trigger+".root", "RECREATE");

	TriggerRateTool* tool = new TriggerRateTool();
	tool->Set_DataList( vec_Data );
	tool->Set_RunNumList( vec_RunNum );
	tool->Set_Trigger( Trigger );
	tool->Set_Output( f_output );
	tool->Analyze();
}
