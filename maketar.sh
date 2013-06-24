cd /uscms_data/d2/abarker/CMSSW_5_3_3/src/SusyAnalysis

tar -czvf tar_for_condor.tar SusyNtuplizer/ --exclude "*.root" --exclude "*.tar" --exclude "plots*" --exclude "st_250_ho_150" --exclude "ho_140" --exclude "ho_200" --exclude "st_250_ho_200" --exclude "NBTagEffup" --exclude "working*" --exclude "gridout" --exclude "*log*" --exclude "*eventlist*" --exclude "obsolete" --exclude "Limit*" --exclude ".git*"

cd -
