#!/bin/bash
root -l -b -q MakeHist_TnP_IterL3OI_TK_OverL1.C &> log_MakeHist_TnP_IterL3OI_TK_OverL1.log
root -l -b -q MakeHist_TnP_IterL3IO_L2Seeded_TK_OverL1.C &> log_MakeHist_TnP_IterL3IO_L2Seeded_TK_OverL1.log
root -l -b -q MakeHist_TnP_IterL3_FromL2_TK_OverL1.C &> log_MakeHist_TnP_IterL3_FromL2_TK_OverL1.log
root -l -b -q MakeHist_TnP_IterL3IO_FromL1_OverL1.C &> log_MakeHist_TnP_IterL3IO_FromL1_OverL1.log
root -l -b -q MakeHist_TnP_L3_OverL1.C &> log_MakeHist_TnP_L3_OverL1.log
root -l -b -q MakeHist_TnP_IsoMu27_OverL1.C &> log_MakeHist_TnP_IsoMu27_OverL1.log

root -l -b -q NoL3MuonPt/MakeHist_TnP_IterL3OI_TK_OverL1.C &> NoL3MuonPt/log_MakeHist_TnP_IterL3OI_TK_OverL1.log
root -l -b -q NoL3MuonPt/MakeHist_TnP_IterL3IO_L2Seeded_TK_OverL1.C &> NoL3MuonPt/log_MakeHist_TnP_IterL3IO_L2Seeded_TK_OverL1.log
root -l -b -q NoL3MuonPt/MakeHist_TnP_IterL3_FromL2_TK_OverL1.C &> NoL3MuonPt/log_MakeHist_TnP_IterL3_FromL2_TK_OverL1.log
root -l -b -q NoL3MuonPt/MakeHist_TnP_IterL3IO_FromL1_OverL1.C &> NoL3MuonPt/log_MakeHist_TnP_IterL3IO_FromL1_OverL1.log
root -l -b -q NoL3MuonPt/MakeHist_TnP_L3_OverL1.C &> NoL3MuonPt/log_MakeHist_TnP_L3_OverL1.log
root -l -b -q NoL3MuonPt/MakeHist_TnP_IsoMu27_OverL1.C &> NoL3MuonPt/log_MakeHist_TnP_IsoMu27_OverL1.log
