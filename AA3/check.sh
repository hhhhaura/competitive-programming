g++ $1 -o wa
g++ $2 -o ac
g++ $3 -o gen
for i in $(seq 1 100000);
do	
	echo $i
	./gen > input
	./ac < input > out_ac
	./wa < input > out_wa
	diff out_ac out_wa || break
done

