#include <TagProbe/MakeHist_TnP_Mu50.h>

void MakeHist_TnP_Mu50(TString dataPath, TString outputFileName )
{
	HistProducer* producer = new HistProducer();
	producer->SetOutputFileName( outputFileName );
	producer->AddDataPath(dataPath);
	producer->Produce();
}