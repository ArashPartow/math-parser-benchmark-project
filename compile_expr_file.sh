#!/bin/bash

rm -rf bench_expr_complete.txt
rm -rf buf.out
rm -rf buf.out2
rm -rf buf.duplicates
rm -rf buf.uniques

# make sure all files end with a newline. If they don't concatenating them
# will produce invalid expressions
echo "sanitizing file terminations"
sed -i -e '$a\' bench_expr_all.txt
sed -i -e '$a\' bench_expr_extensive.txt
sed -i -e '$a\' bench_expr_precedence.txt
sed -i -e '$a\' bench_expr_random_with_functions.txt
sed -i -e '$a\' bench_expr_random_without_functions.txt
sed -i -e '$a\' bench_expr.txt

echo "compiling files"
cat bench_expr_all.txt\
    bench_expr_extensive.txt\
    bench_expr_precedence.txt\
    bench_expr_random_with_functions.txt\
    bench_expr_random_without_functions.txt\
    bench_expr.txt | tr -d '\r' > buf.out

echo "trimming lines"
cat buf.out | sed '/^$/d;s/[[:blank:]]//g' > buf.out2

#echo "removing comment lines"
cat buf.out2 | sed -e '/^[[:space:]]*#/d' | sort -n > buf.out

echo "removing duplicate lines"
cat buf.out | uniq -d > buf.duplicates
cat buf.out | uniq -u > buf.unique
cat buf.duplicates buf.unique > buf.out

echo "sorting by line length"
awk '{ print length($0) " " $0; }' buf.out | sort -n | cut -d ' ' -f2- > buf.out2

echo "cloeaning up"
mv buf.out2 bench_expr_complete.txt
rm -rf buf.out
rm -rf buf.out2
rm -rf buf.duplicates
rm -rf buf.uniques

echo "done"
