#include <TagProbe/MakeHist_TnP_IsoMu27.h>

void MakeHist_TnP_IsoMu27_noFix()
{
	TString DataPath = gSystem->Getenv("KP_DATA_PATH");
	vector<TString> vec_DataPath = 
	{
		DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics1_Run2017Fv1/ntuple_*.root",
		DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics2_Run2017Fv1/ntuple_*.root",
		DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics3_Run2017Fv1/ntuple_*.root",
		DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics4_Run2017Fv1/ntuple_*.root",
		DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics5_Run2017Fv1/ntuple_*.root",
		DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics6_Run2017Fv1/ntuple_*.root",
		DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics7_Run2017Fv1/ntuple_*.root",
		DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics8_Run2017Fv1/ntuple_*.root",
	};

	Int_t nDataPath = vec_DataPath.size();
	for(Int_t i=0; i<nDataPath; i++)
	{
		HistProducer* producer = new HistProducer();
		producer->AddDataPath(vec_DataPath[i]);
		producer->SetOutputFileName( TString::Format("ROOTFile_MakeHist_TnP_IsoMu27_withoutFix_v%02d.root", i) );
		producer->Produce();

		delete producer;
	}

	// producer->AddDataPath(DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics1_Run2017Fv1/ntuple_*.root");
	// producer->AddDataPath(DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics2_Run2017Fv1/ntuple_*.root");
	// producer->AddDataPath(DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics3_Run2017Fv1/ntuple_*.root");
	// producer->AddDataPath(DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics4_Run2017Fv1/ntuple_*.root");
	// producer->AddDataPath(DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics5_Run2017Fv1/ntuple_*.root");
	// producer->AddDataPath(DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics6_Run2017Fv1/ntuple_*.root");
	// producer->AddDataPath(DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics7_Run2017Fv1/ntuple_*.root");
	// producer->AddDataPath(DataPath+"/92X/TSntuple_v20171106_withoutFix_v2_EphemeralHLTPhysics8_Run2017Fv1/ntuple_*.root");
	// producer->Produce();
	// producer->AddDataPath("");
	// producer->AddDataPath("");
}