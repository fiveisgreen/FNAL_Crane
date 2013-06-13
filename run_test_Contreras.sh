#!/bin/bash 
 
 # This file sets up the bash shell for condor 
 # If you have additional custom enhancements to your shell 
 # environment, you may need to add them here 
 #export  DISPLAY=localhost:11.0 
 export CUR_DIR=$PWD 
 
 export SCRAM_ARCH='slc5_amd64_gcc462' 
 export VO_CMS_SW_DIR='/cms/base/cmssoft' 
 export COIN_FULL_INDIRECT_RENDERING=1 
 source $VO_CMS_SW_DIR/cmsset_default.sh 
 
 # Change to your CMSSW software version 
 export MYREL='CMSSW_5_3_6' 
 export MYPROJECT='CMSSW_Releases' 
 export MYBASE="${MYPROJECT}/${MYREL}" 
 
 # Shown for c shell # Also change 'username' to your username 
 cd /cms/chrisjcc/2013Bprime/${MYBASE}/src 
 eval `scramv1 runtime -sh` 
 date 
 
 # Switch to your working directory below cd  $CUR_DIR 

 #---------------------------------------------------------------

 # Below run your actual commands... typically a cmsRun call

 cd ${CUR_DIR}

 root -l -n -b crossSectionVsMass.C\(\"${1}\"\)
