ls SuperSkim53X_data12*.root > fff
sed -i 's|SuperSkim53X_data12|./savefile.py SuperSkim53X_data12|g' fff
sc fff
