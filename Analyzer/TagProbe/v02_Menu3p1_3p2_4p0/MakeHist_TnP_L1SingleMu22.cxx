#include <TagProbe/MakeHist_TnP_L1SingleMu22.h>

void Setup( HistProducer* producer, TString dataType );

void MakeHist_TnP_L1SingleMu22(TString dataType)
{
	HistProducer* producer = new HistProducer();
	Setup( producer, dataType );

	producer->Produce();
}

void Setup( HistProducer* producer, TString dataType )
{
	TString dataPath = gSystem->Getenv("KP_DATA_PATH");

	if( dataType == "Menu3p1" )
	{
		producer->SetOutputFileName("ROOTFile_MakeHist_TnP_L1SingleMu22_Menu3p1.root" );

		producer->AddDataPath( dataPath+"/92X/TSntuple_v20171128_SingleMuon_Run2017Dv1_302635_to_302635_GoldenJSON_Menu3p1/ntuple_*.root");
		producer->AddDataPath( dataPath+"/92X/TSntuple_v20171129_SingleMuon_Run2017Dv1_302525_to_302634_GoldenJSON_Menu3p1/ntuple_*.root");
	}
	else if( dataType == "Menu3p2" )
	{
		producer->SetOutputFileName("ROOTFile_MakeHist_TnP_L1SingleMu22_Menu3p2.root" );

		producer->AddDataPath( dataPath+"/92X/TSntuple_v20171128_SingleMuon_Run2017Dv1_302635_to_302635_GoldenJSON_Menu3p2/ntuple_*.root");
		producer->AddDataPath( dataPath+"/92X/TSntuple_v20171129_SingleMuon_Run2017Dv1_302525_to_302634_GoldenJSON_Menu3p2/ntuple_*.root");
	}
	else if( dataType == "Menu4p0" )
	{
		producer->SetOutputFileName("ROOTFile_MakeHist_TnP_L1SingleMu22_Menu4p0.root" );

		producer->AddDataPath( dataPath+"/92X/TSntuple_v20171128_SingleMuon_Run2017Dv1_302635_to_302635_GoldenJSON_Menu4p0/ntuple_*.root");
		producer->AddDataPath( dataPath+"/92X/TSntuple_v20171129_SingleMuon_Run2017Dv1_302525_to_302634_GoldenJSON_Menu4p0/ntuple_*.root");
	}
}