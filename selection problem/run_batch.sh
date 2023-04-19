#!/bin/bash

echo "n,sort 1,sort 2,sort 3,,p&s 1,p&s 2,p&s 3,diff1,diff2,diff3" > "summary.csv"
for (( i=1000000; i<=3000000; i+=100000 ));
do
	echo -n $i >> "summary.csv";
	echo $i > "input_n";
    ./make_ex < "input_n";
	for j in {1..3};
	do
    	echo -n "," >> "summary.csv";
    	time (./selection_problem_sort<$i"_"$j".txt">"out_"$i"_"$j".ans")  > "tmp.log" 2>&1;
    	tmp_min=$(grep real "tmp.log" | tr -d 'real\t' | cut -d 'm' -f1);
    	tmp_sec=$(grep real "tmp.log" | tr -d 'real\t' | cut -d 'm' -f2 | tr -d 's\n');
    	tmp_time=$(echo "$tmp_min * 60 + $tmp_sec" | bc );
    	echo -n $tmp_time  >> "summary.csv";
	done
	echo -n "," >> "summary.csv";
	for j in {1..3};
	do
    	echo -n "," >> "summary.csv";
    	time (./selection_problem_p\&s<$i"_"$j".txt">"out_"$i"_"$j".out")  > "tmp.log" 2>&1;
    	tmp_min=$(grep real "tmp.log" | tr -d 'real\t' | cut -d 'm' -f1);
    	tmp_sec=$(grep real "tmp.log" | tr -d 'real\t' | cut -d 'm' -f2 | tr -d 's\n');
    	tmp_time=$(echo "$tmp_min * 60 + $tmp_sec" | bc );
    	echo -n $tmp_time  >> "summary.csv";
	done
	

	for j in {1..3};
	do
    	difference=$(diff "out_"$i"_"$j".ans" "out_"$i"_"$j".out" 2>&1);
    	if [ "$difference" = "" ];then
    		echo -n ",0" >> "summary.csv";
    	else
    		echo -n ",1" >> "summary.csv";
    	fi
    	rm $i"_"$j".txt" "out_"$i"_"$j".ans" "out_"$i"_"$j".out";
	done
	echo "" >> "summary.csv";
	rm tmp.log input_n;
done