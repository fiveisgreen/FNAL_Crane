cp st*.tar /eos/uscms/store/user/abarker/hggxout_18fb_NLO/
cp mu*.tar /eos/uscms/store/user/abarker/hggxout_18fb_NLO/
ls -1 mu_*.tar > tar1.txt
ls -1 mu_*.tar > tar2.txt
ls -1 st_*.tar > tar3.txt
ls -1 st_*.tar > tar4.txt
sed -i 's/mu_/tar -xvf mu_/g' tar1.txt
sed -i 's/mu_/rm mu_/g' tar2.txt
sed -i 's/st_/tar -xvf st_/g' tar3.txt
sed -i 's/st_/rm st_/g' tar4.txt
./Shuffel.py tar1.txt tar2.txt > untarAll.txt
./Shuffel.py tar3.txt tar4.txt > untarAll2.txt
rm tar1.txt
rm tar2.txt
rm tar3.txt
rm tar4.txt
sc untarAll2.txt
sc untarAll.txt
ls -1tr raw_plots_M*BtagEff* > killBtagEff.txt
ls -1tr raw_plots_MC*JEC* > killJEC.txt
sed -i 's/killBtagEff.txt//g' killBtagEff.txt
sed -i 's/killJEC.txt//g' killJEC.txt
sed -i 's/raw_/rm raw_/g' killBtagEff.txt
sed -i 's/raw_/rm raw_/g' killJEC.txt
sc killBtagEff.txt
sc killJEC.txt

ls -1tr plotsWithBackground_M*BtagEff* > killBtagEff.txt
ls -1tr plotsWithBackground_M*JEC* > killJEC.txt
sed -i 's/plotsWith/rm plotsWith/g' killBtagEff.txt
sed -i 's/plotsWith/rm plotsWith/g' killJEC.txt
sed -i 's/raw_/rm raw_/g' killBtagEff.txt
sed -i 's/raw_/rm raw_/g' killJEC.txt
sc killBtagEff.txt
sc killJEC.txt

tar -xvf Cards_st_200_mu_150_bbaa.tar LimitCard_st_200_mu_150_bbaa_2JbMLgbar2_MET.txt
tar -xvf Cards_st_225_mu_215_bbaa.tar LimitCard_st_225_mu_215_bbaa_2JbMLgbar2_MET.txt
tar -xvf Cards_st_250_mu_150_bbaa.tar LimitCard_st_250_mu_150_bbaa_2JbMLgbar2_MET.txt
tar -xvf Cards_st_200_mu_150_bbaa.tar LimitCard_st_200_mu_150_bbaa_bbin3_MET.txt
tar -xvf Cards_st_225_mu_215_bbaa.tar LimitCard_st_225_mu_215_bbaa_bbin3_MET.txt
tar -xvf Cards_st_250_mu_150_bbaa.tar LimitCard_st_250_mu_150_bbaa_bbin3_MET.txt
root -l -b -q format_plots_combined.C+
python makeTable.py
