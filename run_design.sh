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
cd SusyNtuplizer/macro
echo "Make BtagEff"
root -l -b -q ana_MC_BTagEff_arg.C\(\"${1}\",\"${2}\"\)

echo "do JEC+1"
sed -i 's/int bumpJEC = 0/int bumpJEC = 1/' params_arg.h #jec +1
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.txt/JECUp.txt/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.txt/JECUp.txt/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc
tar -cvf ${1}.tar new_plotsroot_mc new_logplotsroot_mc new_plotsAndBackground_mc new_logplotsAndBackground_mc

echo "do JEC-1"
sed -i 's/int bumpJEC = 1/int bumpJEC = -1/' params_arg.h #jec -1
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.txt/JECDown.txt/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.txt/JECDown.txt/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc
tar -uvf ${1}.tar new_plotsroot_mc new_logplotsroot_mc new_plotsAndBackground_mc new_logplotsAndBackground_mc

echo "do BtagEff+1"
sed -i 's/int bumpJEC = -1/int bumpJEC = 0/' params_arg.h
sed -i 's/int bumpBtagEff = 0/int bumpBtagEff = 1/' params_arg.h #btag +1
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/BtagEffUp.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.txt/BtagEffUp.txt/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/BtagEffUp.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.txt/BtagEffUp.txt/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc
tar -uvf ${1}.tar new_plotsroot_mc new_logplotsroot_mc new_plotsAndBackground_mc new_logplotsAndBackground_mc

echo "do BtagEff-1"
sed -i 's/int bumpBtagEff = 1/int bumpBtagEff = -1/' params_arg.h #btag -1
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.txt/BtagEffDown.txt/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.txt/BtagEffDown.txt/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc
tar -uvf ${1}.tar new_plotsroot_mc new_logplotsroot_mc new_plotsAndBackground_mc new_logplotsAndBackground_mc

echo "do main"
sed -i 's/int bumpBtagEff = -1/int bumpBtagEff = 0/' params_arg.h #do normal
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
tar -uvf ${1}.tar ${3} ${4} ${5} ${6}

mv ${1}.tar ../../../../

