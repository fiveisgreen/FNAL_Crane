#!/bin/csh -f
root -l -b -q ana_MC_BTagEff_arg.C\(\"${1}\",\"${2}\"\)

echo "do JEC+1"
echo "Apriori, it settings are: "
grep JEC params_arg.h
grep BtagEff params_arg.h
sed -i 's/int bumpJEC = 0/int bumpJEC = 1/' params_arg.h #jec +1
#root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
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

echo "do JEC-1"
sed -i 's/int bumpJEC = 1/int bumpJEC = -1/' params_arg.h #jec -1
echo "Running with settings settings: "
grep JEC params_arg.h
grep BtagEff params_arg.h
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
#root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.log/JECDown.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.log/JECDown.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc

echo "do BtagEff+1"
sed -i 's/int bumpJEC = -1/int bumpJEC = 0/' params_arg.h
sed -i 's/int bumpBtagEff = 0/int bumpBtagEff = 1/' params_arg.h #btag +1
echo "Running with settings settings: "
grep JEC params_arg.h
grep BtagEff params_arg.h
#root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
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

echo "do BtagEff-1"
sed -i 's/int bumpBtagEff = 1/int bumpBtagEff = -1/' params_arg.h #btag -1
echo "Running with settings settings: "
grep JEC params_arg.h
grep BtagEff params_arg.h
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
#root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
echo $3 >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $3 $new_plotsroot_mc
echo $4 >>foo; sed -i 's/.log/BtagEffDown.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $4 $new_logplotsroot_mc
echo $5 >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $5 $new_plotsAndBackground_mc
echo $6 >>foo; sed -i 's/.log/BtagEffDown.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $6 $new_logplotsAndBackground_mc

echo "do main"
sed -i 's/int bumpBtagEff = -1/int bumpBtagEff = 0/' params_arg.h #do normal
echo "Running with settings settings: "
grep JEC params_arg.h
grep BtagEff params_arg.h
root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
#root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"${1}\"\)
