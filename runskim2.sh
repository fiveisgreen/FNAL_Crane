#!/bin/csh -f
echo "1"
echo $1
source /uscmst1/prod/sw/cms/cshrc prod
echo "B"
setenv SCRAM_ARCH slc5_amd64_gcc462
date
scram project CMSSW CMSSW_5_3_3
echo "C"
cd CMSSW_5_3_3
cd src
cmsenv
echo "D"
eval `scramv1 runtime -csh`
tar -xzvf ../../tar_for_condor.tar
cp ../../*.h SusyNtuplizer/macro
cd SusyNtuplizer/macro
echo "Make BtagEff"
root -l -b -q ana_firstskim_multisave_arg.C\(6,${1},1\)
echo "show me the skim file:"
ls -ltr Super*.root
cp *.root ../../../../
pwd
cd ../../../../
pwd
