#syntax: convertlist filenames /eos/dir/dir/dir/
#takes a list of file names [filenames] and makes it into a list of executable commands. 
#chain->Add("/eos/dir/dir/dir/ReSkim53X_data_susyEvents_99_1_Frm_A.root");
sed 's|^|chain->Add("'$2'|' $1 > temp
sed -i 's|root|root");|' temp
echo "results are in the file temp"
echo "They look like this:"
head -1 temp
