#!/bin/csh -f
echo "setup the limit setter"
source /uscmst1/prod/sw/cms/cshrc prod
setenv SCRAM_ARCH slc5_amd64_gcc472
scram project CMSSW CMSSW_6_1_1
sleep 2
cd CMSSW_6_1_1/src
cmsenv
cmscvsroot CMSSW
addpkg HiggsAnalysis/CombinedLimit V03-01-08
scramv1 b
rehash
echo "done setting up the limit setter"
pwd
cd ../../
pwd
cp *.tar CMSSW_6_1_1/src/
cp plotsWithBackground_dataGLL12.root CMSSW_6_1_1/src/
cp CMSSW_5_3_3/src/SusyNtuplizer/macro/*.C CMSSW_6_1_1/src/
cp CMSSW_5_3_3/src/SusyNtuplizer/macro/*.h CMSSW_6_1_1/src/
cp CMSSW_5_3_3/src/SusyNtuplizer/macro/*.py CMSSW_6_1_1/src/
cp plotsWithBackground_dataGLL12.root CMSSW_6_1_1/src/
cd CMSSW_6_1_1/src/
echo "untar in the results from 5_3_3 analysis"
tar -xvf *.tar
echo "Run All Cards"
date
cat doLimits_${1}.sh | grep -v ! > doLimits_${1}_mod.sh
source doLimits_${1}_mod.sh
date
./simplifyLimitBundle.py LimitResultBundle_${1}.txt
echo "Load Up result"
cp LimitResultBundle_${1}.txt ../../
cp LimitResultBundle_${1}_reduced.txt ../../
cd ../../
pwd
