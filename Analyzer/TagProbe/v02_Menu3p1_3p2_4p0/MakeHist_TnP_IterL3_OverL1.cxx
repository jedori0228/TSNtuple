#include <TagProbe/MakeHist_TnP_IterL3_OverL1.h>

void MakeHist_TnP_IterL3_OverL1(TString dataPath, TString outputFileName )
{
	HistProducer* producer = new HistProducer();
  producer->iterl3obj = "IterL3OI_TK";
	producer->SetOutputFileName( outputFileName );
	producer->AddDataPath(dataPath);
	producer->Produce();
}
