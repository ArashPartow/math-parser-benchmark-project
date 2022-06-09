#!/bin/sh
exec="Release/ParserBenchmark.exe"
$exec 250000 bench_expr.txt
$exec 250000 bench_expr_all.txt
$exec 250000 bench_expr_random_with_functions.txt
$exec 250000 bench_expr_random_without_functions.txt
$exec 250000 bench_expr_extensive.txt
$exec 250000 bench_expr_precedence.txt
$exec 250000 bench_expr_weird.txt
$exec 10000  bench_expr_complete.txt
