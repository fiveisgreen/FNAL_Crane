sc lsDcache | grep Super > ddd 
sed -i 's|Suoer|chain->Add("dcache:/pnfs/cms/WAX/resilient/abarker/SusyLooseSkim_53X_2012Super|g' ddd
sed -i 's|root|root");|g' ddd
echo ":r ddd"
