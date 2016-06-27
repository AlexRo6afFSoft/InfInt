echo "1" > inFile$1; 
for i in `seq 1 $2`; 
do 
	echo -n "0" >> inFile$1; 
done; 
echo " 1" >> inFile$1; 
for i in `seq 1 $2`; 
do 
	echo -n "0" >> inFile$1; 
done
