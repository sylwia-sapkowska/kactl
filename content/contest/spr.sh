for ((i=0;;i++)); do
	./gen > t.in
	./main < t.in > m.out || { printf "\nRE\n"; break; }
	./brute < t.in > b.out
	diff -wq m.out b.out || { printf "\nfatalnie ...\n"; break; }
	printf "OK %d\r" "$i"
done