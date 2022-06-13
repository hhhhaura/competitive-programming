g++ $1 -o ac
g++ $2 -o wa
g++ $3 -o gen
for i in $(seq 1 10000);
do	
	./gen > input 
	./wa < input > out1
	./ac < input > out2
	diff out1 out2 || break
done
