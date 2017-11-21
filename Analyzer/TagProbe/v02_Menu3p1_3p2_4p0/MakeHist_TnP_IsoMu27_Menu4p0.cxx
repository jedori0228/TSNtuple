#include <TagProbe/MakeHist_TnP_IsoMu27.h>

void MakeHist_TnP_IsoMu27_Menu4p0()
{
	HistProducer* producer = new HistProducer();
	producer->SetOutputFileName( "ROOTFile_MakeHist_TnP_IsoMu27_Menu4p0.root" );

	TString DataPath = gSystem->Getenv("KP_DATA_PATH");
	producer->AddDataPath(DataPath+"/92X/TSntuple_v20171109_Menu4p0_EphemeralHLTPhysics1_Run2017Dv1/ntuple_*.root");
	producer->AddDataPath(DataPath+"/92X/TSntuple_v20171109_Menu4p0_EphemeralHLTPhysics2_Run2017Dv1/ntuple_*.root");
	producer->AddDataPath(DataPath+"/92X/TSntuple_v20171109_Menu4p0_EphemeralHLTPhysics3_Run2017Dv1/ntuple_*.root");
	producer->AddDataPath(DataPath+"/92X/TSntuple_v20171109_Menu4p0_EphemeralHLTPhysics4_Run2017Dv1/ntuple_*.root");
	producer->AddDataPath(DataPath+"/92X/TSntuple_v20171109_Menu4p0_EphemeralHLTPhysics5_Run2017Dv1/ntuple_*.root");
	producer->AddDataPath(DataPath+"/92X/TSntuple_v20171109_Menu4p0_EphemeralHLTPhysics6_Run2017Dv1/ntuple_*.root");
	producer->AddDataPath(DataPath+"/92X/TSntuple_v20171109_Menu4p0_EphemeralHLTPhysics7_Run2017Dv1/ntuple_*.root");
	producer->AddDataPath(DataPath+"/92X/TSntuple_v20171109_Menu4p0_EphemeralHLTPhysics8_Run2017Dv1/ntuple_*.root");
	producer->Produce();
	// producer->AddDataPath("");
	// producer->AddDataPath("");
}