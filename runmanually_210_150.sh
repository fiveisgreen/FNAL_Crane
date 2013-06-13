#!/bin/csh -f

set label = mst_210_mu_150
set floc = dcache:/pnfs/cms/WAX/resilient/lpcpjm/PrivateMC/FastSim/533p3_full/naturalHiggsinoNLSP_try4/SusyNtuple/cms533v1_v1/tree_naturalHiggsinoNLSPout_mst_210_M3_5050_mu_150.root
set rroot = raw_plots_MC_st210_ho150.root 
set rlog = raw_plots_MC_st210_ho150.log 
set proot = plotsWithBackground_MC_st210_ho150.root 
set plog = plotsWithBackground_MC_st210_ho150.log


root -l -b -q ana_MC_BTagEff_arg.C\(\"$label\",\"$floc\"\)

echo "do JEC+1"
echo "Apriori, it settings are: "
grep JEC params_arg.h
grep BtagEff params_arg.h
rm foo
sed -i 's/int bumpJEC = 0/int bumpJEC = 1/' params_arg.h #jec +1
root -l -b -q ana_Main_MC_arg.C\(\"$label\",\"$floc\"\)
root -l -b -q postanaana_MC_arg.C+\(\"$label\"\)
echo $rroot >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $rroot $new_plotsroot_mc
echo $rlog >>foo; sed -i 's/.log/JECUp.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $rlog $new_logplotsroot_mc
echo $proot >>foo; sed -i 's/.root/JECUp.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $proot $new_plotsAndBackground_mc
echo $plog >>foo; sed -i 's/.log/JECUp.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $plog $new_logplotsAndBackground_mc

echo "do JEC-1"
sed -i 's/int bumpJEC = 1/int bumpJEC = -1/' params_arg.h #jec -1
echo "Running with settings settings: "
grep JEC params_arg.h
grep BtagEff params_arg.h
root -l -b -q ana_Main_MC_arg.C\(\"$label\",\"$floc\"\)
#root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"$label\"\)
echo $rroot >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $rroot $new_plotsroot_mc
echo $rlog >>foo; sed -i 's/.log/JECDown.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $rlog $new_logplotsroot_mc
echo $proot >>foo; sed -i 's/.root/JECDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $proot $new_plotsAndBackground_mc
echo $plog >>foo; sed -i 's/.log/JECDown.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $plog $new_logplotsAndBackground_mc

echo "do BtagEff+1"
sed -i 's/int bumpJEC = -1/int bumpJEC = 0/' params_arg.h
sed -i 's/int bumpBtagEff = 0/int bumpBtagEff = 1/' params_arg.h #btag +1
echo "Running with settings settings: "
grep JEC params_arg.h
grep BtagEff params_arg.h
#root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_Main_MC_arg.C\(\"$label\",\"$floc\"\)
root -l -b -q postanaana_MC_arg.C+\(\"$label\"\)
echo $rroot >>foo; sed -i 's/.root/BtagEffUp.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $rroot $new_plotsroot_mc
echo $rlog >>foo; sed -i 's/.log/BtagEffUp.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $rlog $new_logplotsroot_mc
echo $proot >>foo; sed -i 's/.root/BtagEffUp.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $proot $new_plotsAndBackground_mc
echo $plog >>foo; sed -i 's/.log/BtagEffUp.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $plog $new_logplotsAndBackground_mc

echo "do BtagEff-1"
sed -i 's/int bumpBtagEff = 1/int bumpBtagEff = -1/' params_arg.h #btag -1
echo "Running with settings settings: "
grep JEC params_arg.h
grep BtagEff params_arg.h
root -l -b -q ana_Main_MC_arg.C\(\"$label\",\"$floc\"\)
#root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"$label\"\)
echo $rroot >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsroot_mc = `cat foo`; rm foo
mv $rroot $new_plotsroot_mc
echo $rlog >>foo; sed -i 's/.log/BtagEffDown.log/' foo; set new_logplotsroot_mc = `cat foo`; rm foo
mv $rlog $new_logplotsroot_mc
echo $proot >>foo; sed -i 's/.root/BtagEffDown.root/' foo; set new_plotsAndBackground_mc = `cat foo`; rm foo
mv $proot $new_plotsAndBackground_mc
echo $plog >>foo; sed -i 's/.log/BtagEffDown.log/' foo; set new_logplotsAndBackground_mc = `cat foo`; rm foo
mv $plog $new_logplotsAndBackground_mc

echo "do main"
sed -i 's/int bumpBtagEff = -1/int bumpBtagEff = 0/' params_arg.h #do normal
echo "Running with settings settings: "
grep JEC params_arg.h
grep BtagEff params_arg.h
root -l -b -q ana_Main_MC_arg.C\(\"$label\",\"$floc\"\)
#root -l -b -q ana_Main_MC_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q postanaana_MC_arg.C+\(\"$label\"\)
