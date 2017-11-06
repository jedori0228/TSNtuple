#!bin/bash

root -b -q 'DrawPlot_Comparison.cxx("HLT_IsoMu24_v10")'
root -b -q 'DrawPlot_Comparison.cxx("HLT_IsoMu27_v13")'
root -b -q 'DrawPlot_Comparison.cxx("HLT_Mu50_v11")'
root -b -q 'DrawPlot_Comparison.cxx("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v3")'
root -b -q 'DrawPlot_Comparison.cxx("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v3")'

echo "finished"