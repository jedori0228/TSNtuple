#include <Rate/TriggerRateTool.h>

void MuonTriggerRate_afterFix( TString Trigger )
{
	TString DataBasePath = gSystem->Getenv("KP_DATA_PATH");
	vector< TString > vec_Data = 
	{
		DataBasePath+"/92X/HLTReRunNtuple_v20170923_withFix_HLTPhysics1_Run2017Cv3/*.root",
		DataBasePath+"/92X/HLTReRunNtuple_v20170923_withFix_HLTPhysics2_Run2017Cv3/*.root",
		DataBasePath+"/92X/HLTReRunNtuple_v20170923_withFix_HLTPhysics3_Run2017Cv3/*.root",
		DataBasePath+"/92X/HLTReRunNtuple_v20170923_withFix_HLTPhysics4_Run2017Cv3/*.root",
		DataBasePath+"/92X/HLTReRunNtuple_v20170923_withFix_HLTPhysics5_Run2017Cv3/*.root",
		DataBasePath+"/92X/HLTReRunNtuple_v20170923_withFix_HLTPhysics6_Run2017Cv3/*.root",
		DataBasePath+"/92X/HLTReRunNtuple_v20170923_withFix_HLTPhysics7_Run2017Cv3/*.root",
		DataBasePath+"/92X/HLTReRunNtuple_v20170923_withFix_HLTPhysics8_Run2017Cv3/*.root"
	};

	vector< Int_t > vec_RunNum = 
	{
		301567, 301627, 301664, 301665, 301694, 
		301912, 301913, 301914, 301941, 301959
	};

	TFile *f_output = TFile::Open("ROOTFile_MuonTriggerRate_"+Trigger+".root", "RECREATE");

	TriggerRateTool* tool = new TriggerRateTool();
	tool->Set_DataList( vec_Data );
	tool->Set_RunNumList( vec_RunNum );
	tool->Set_Trigger( Trigger );
	tool->Set_Output( f_output );
	tool->Analyze();
}
