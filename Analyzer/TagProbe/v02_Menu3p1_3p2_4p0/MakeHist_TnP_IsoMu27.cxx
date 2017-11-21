#include <TagProbe/MakeHist_TnP_IsoMu27.h>

void MakeHist_TnP_IsoMu27(TString dataPath, TString outputFileName )
{
	HistProducer* producer = new HistProducer();
	producer->SetOutputFileName( outputFileName );
	producer->AddDataPath(dataPath);
	producer->Produce();
}