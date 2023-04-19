#!/bin/bash
cd samples3;
for i in {10..30}
do
	temp=$((i*1000));
	../random_input_generator $temp;
done

for i in {10..30}
do
	temp=$((i*1000));
	file_name="input_$temp.txt";
	../selecting $file_name 'n';
done