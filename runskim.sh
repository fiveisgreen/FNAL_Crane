#!/bin/csh -f
echo "1"
source /uscmst1/prod/sw/cms/cshrc prod
setenv SCRAM_ARCH slc5_amd64_gcc462
printenv
ls -alt
date
scram project CMSSW CMSSW_5_3_3
cd CMSSW_5_3_3
cd src
cmsenv
echo "3"
eval `scramv1 runtime -csh`
tar -xzvf ../../tar_for_condor.tar
cp ../../*.h SusyNtuplizer/macro
cd SusyNtuplizer/macro
echo "4"
#root -l -b -q ana_MC_BTagEff_arg.C\(\"$point_for_b\",\"$file_for_b\"\)
root -l -b -q ana_firstskim.C
echo "5"
cp ReSkim53X_data_*.root ../../../../
pwd
cd ../../../../
lt | tail -3
