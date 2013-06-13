rr ana_Main_MC_arg.C\(\"mst_350_mu_200\",\"/eos/uscms/store/user/abarker/MC/st_350_ho_200/MC_AB_2500k_mst_350_mu_200.root\"\)
rr postanaana_MC_arg.C+\(\"mst_350_mu_200\"\)

#set thisdir=Normal
#set thisdir=JECup #did it
#set thisdir=JECdown
set thisdir=BTagEffdown
#set thisdir=BTagEffup

cp raw_plots_MC_st350_ho200.log $thisdir
cp raw_plots_MC_st350_ho200.root $thisdir
cp plotsWithBackground_MC_st350_ho200.log $thisdir
cp plotsWithBackground_MC_st350_ho200.root $thisdir

