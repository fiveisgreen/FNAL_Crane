#!/bin/csh -f
#the task here is to take in a width, set it,
#then run 1. the data;
#2. a MC point
#3 set a limit.
#Assume we are given explicitely the window width to set as $1


echo "1"
source /uscmst1/prod/sw/cms/cshrc prod
echo "2"
setenv SCRAM_ARCH slc5_amd64_gcc462
date
scram project CMSSW CMSSW_5_3_3
echo "3"
cd CMSSW_5_3_3
cd src
cmsenv
echo "4"
eval `scramv1 runtime -csh`
tar -xzvf ../../tar_for_condor.tar
cp ../../*.h SusyNtuplizer/macro
cd SusyNtuplizer/macro
echo "Set the window"
sed -i 's/mHwidth = 11.f/mHwidth = ${1}/g' params_arg.h
echo "Make data"
root -l -b -q ana_Main_data.C
root -l -b -q postanaana.C+

echo "Make MC"
root -l -b -q ana_MC_BTagEff_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_MC_BTagEff_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
tar -uvf ${1}.tar ${3} ${4} ${5} ${6}

cp ${1}.tar ../../../../
pwd
cd ../../../../
pwd
echo "setup the limit setter"
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
cp ${1}.tar CMSSW_6_1_1/src/
cp CMSSW_5_3_3/src/SusyNtuplizer/macro/*.C CMSSW_6_1_1/src/
cp CMSSW_5_3_3/src/SusyNtuplizer/macro/*.h CMSSW_6_1_1/src/
cp CMSSW_5_3_3/src/SusyNtuplizer/macro/*.py CMSSW_6_1_1/src/
cp plotsWithBackground_dataGLL12.root CMSSW_6_1_1/src/
cd CMSSW_6_1_1/src/
echo "untar in the results from 5_3_3 analysis"
tar -xvf ${1}.tar
echo "Setup Limits!"
root -l -b -q SetupLimit.C+\(\"${1}\"\)
echo "Run All Cards"
date
source doLimits_${1}.sh
date
./simplifyLimitBundle.py LimitResultBundle_${1}.txt
echo "Load Up result"
tar -uvf ${1}.tar LimitResultBundle_${1}.txt LimitResultBundle_${1}_reduced.txt
cp ${1}.tar ../../
cd ../../
pwd
