cp foo foo2
sed -i 's|Super|./savefile.py Super|' foo
sed -i 's|Super|rm Super|' foo2
sc foo
