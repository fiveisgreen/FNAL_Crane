#!/bin/csh -f
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
echo "Make BtagEff"
set point_for_b=`echo ${1} | sed 's/wwaa/bbaa/g;s/ttaa/bbaa/g;s/zzaa/bbaa/g'`
set file_for_b=`echo ${2} | sed 's/wwaa/bbaa/g;s/ttaa/bbaa/g;s/zzaa/bbaa/g;s/_5_hh/_15_hh/;s/_10_hh/_15_hh/;s/_13_hh/_15_hh/'`
echo $point_for_b
echo $file_for_b

#root -l -b -q ana_MC_BTagEff_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_MC_BTagEff_arg.C\(\"$point_for_b\",\"$file_for_b\"\)
root -l -b -q ana_MC_BTagEff_arg.C\(\"$point_for_b\",\"$file_for_b\"\)

echo "do JEC+1"
sed -i 's/int bumpJEC = 0/int bumpJEC = 1/' params_arg.h #jec +1
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.log/JECUp.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.log/JECUp.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc
tar -cvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc

ls *.root
ls *.tar

echo "do JEC-1"
sed -i 's/int bumpJEC = 1/int bumpJEC = -1/' params_arg.h #jec -1
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.log/JECDown.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.log/JECDown.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc
tar -uvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc

echo "do BtagEff+1"
sed -i 's/int bumpJEC = -1/int bumpJEC = 0/' params_arg.h
sed -i 's/int bumpBtagEff = 0/int bumpBtagEff = 1/' params_arg.h #btag +1
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/BtagEffUp.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.log/BtagEffUp.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/BtagEffUp.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.log/BtagEffUp.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc
tar -uvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc

echo "do BtagEff-1"
sed -i 's/int bumpBtagEff = 1/int bumpBtagEff = -1/' params_arg.h #btag -1
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.log/BtagEffDown.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.log/BtagEffDown.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc
tar -uvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc

echo "do main"
sed -i 's/int bumpBtagEff = -1/int bumpBtagEff = 0/' params_arg.h #do normal
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
#echo "Setup Limits!"
#ls *.root
#root -l -b -q SetupLimit.C+\(\"${1}\"\)
#echo "Run All Cards"
#date
#cat doLimits_${1}.sh | grep -v ! > doLimits_${1}_mod.sh
#source doLimits_${1}_mod.sh
#date
#./simplifyLimitBundle.py LimitResultBundle_${1}.txt
echo "Load Up result"
#tar -cvf Cards_${1}.tar LimitCard*.txt
#tar -uvf ${1}.tar LimitResultBundle_${1}.txt LimitResultBundle_${1}_reduced.txt Cards_${1}.tar
cp ${1}.tar ../../
cd ../../
pwd
