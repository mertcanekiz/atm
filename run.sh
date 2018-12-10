if [ ! -f "./bin/atm" ]
then
echo "Compiling..."
./compile.sh
fi
cd bin
touch users.csv
./atm
