#!/bin/csh -f

set label = st_400_mu_300_bbaa
set floc = /eos/uscms/store/user/lpcpjm/PrivateMC/FastSim/533p3_full/ewkinoLHEs/StopHiggs/bbaa/SusyNtuple/cms533v1_v1/tree_StopHiggs_stop400_chargino300_15_hh_bbaa.root 

root -l -b -q ana_MC_BTagEff_arg.C\(\"$label\",\"$floc\"\)
root -l -b -q ana_Main_MC_arg.C\(\"$label\",\"$floc\"\)
root -l -b -q postanaana_MC_arg.C+\(\"$label\"\)
