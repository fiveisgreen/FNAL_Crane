#!/bin/csh -f
echo "Make BtagEff"
set point_for_b=`echo ${1} | sed 's/wwaa/bbaa/;s/ttaa/bbaa/;s/zzaa/bbaa/'`
set file_for_b=`echo ${2} | sed 's/wwaa/bbaa/;s/ttaa/bbaa/;s/zzaa/bbaa/;s/_5_hh/_15_hh/;s/_10_hh/_15_hh/;s/_13_hh/_15_hh/'`
echo $point_for_b
echo $file_for_b

#root -l -b -q ana_MC_BTagEff_arg.C\(\"${1}\",\"${2}\"\)
root -l -b -q ana_MC_BTagEff_arg.C\(\"$point_for_b\",\"$file_for_b\"\)
