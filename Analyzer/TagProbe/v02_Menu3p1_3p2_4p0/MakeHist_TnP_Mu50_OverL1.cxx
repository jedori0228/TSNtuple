#include <TagProbe/MakeHist_TnP_Mu50_OverL1.h>

void MakeHist_TnP_Mu50_OverL1(TString dataPath, TString outputFileName )
{
	HistProducer* producer = new HistProducer();
	producer->SetOutputFileName( outputFileName );
	producer->AddDataPath(dataPath);
	producer->Produce();
}