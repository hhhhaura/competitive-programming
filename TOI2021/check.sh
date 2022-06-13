g++ $1 -o ac
g++ $2 -o wa
g++ $3 -o gen
for i in $(seq 1 100000);
do 
	echo $i
	./gen > input
	./ac < input > out1
	./wa < input > out2
	diff out1 out2 || break
done
