#!/bin/csh -f
echo "1"
echo $1
echo "2"
echo $2
echo "3"
echo $3
echo "4"
echo $4
echo "5"
echo $5
echo "6"
echo $6
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
root -l -b -q ana_MC_BTagEff_arg.C\(\"${1}\",\"${2}\"\)
cat tmpfirealarm.txt | grep FIRE >> firealarm${1}.txt
root -l -b -q ana_MC_BTagEff_arg.C\(\"${1}\",\"${2}\"\)
cat tmpfirealarm.txt | grep FIRE >> firealarm.txt

echo "show me the Btag file:"
ls -ltr *.root
echo "do JEC+1"
sed -i 's/int bumpJEC = 0/int bumpJEC = 1/' params_arg.h #jec +1
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
cat tmpfirealarm.txt | grep FIRE >> firealarm.txt
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
cat tmpfirealarm.txt | grep FIRE >> firealarm.txt
echo "\nAttempt to run postanaana\n" > /dev/stderr
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
cat tmpfirealarm.txt | grep FIRE >> firealarm.txt
echo "\nout of postanaana\n" > /dev/stderr
echo "have I made the plotsWith file?"
ls -ltr *.root
echo $3 >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.log/JECUp.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo "should have moved raw"
ls -ltr *.root
echo $5 >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.log/JECUp.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc
echo "should have moved plotsWith"
ls -ltr *.root
echo "tar first set"
echo "tar -cvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc"
tar -cvf ${1}.tar $new_plotsroot_mc $new_logplotsroot_mc $new_plotsAndBackground_mc $new_logplotsAndBackground_mc
echo "done tar"
ls -ltr *.root
ls -ltr *.log

echo "FIRE ALARM STATUS"
cat firealarm.txt
