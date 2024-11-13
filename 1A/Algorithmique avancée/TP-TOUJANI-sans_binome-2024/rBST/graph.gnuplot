set term png size 600, 400

set title 'Time to build in function of the size for uniform permutations'                       # plot title
set xlabel 'size'                              # x-axis label
set ylabel 'time'
set output "uniform-build.png"
plot "data.gnuplot" using 1:2 with linespoint title "BST-Uniform-Build","data.gnuplot" using 1:8 with linespoint title "RBST-Uniform-Build"

set title 'Height in function of the size for uniform permutations'                       # plot title
set xlabel 'size'                              # x-axis label
set ylabel 'Height'
set output "uniform-height.png"
plot "data.gnuplot" using 1:3 with linespoint title "BST-Uniform-height","data.gnuplot" using 1:9 with linespoint title "RBST-Uniform-height"

set title 'Time to perform 1000 searches in function of the size for uniform permutations'                       # plot title
set xlabel 'size'                              # x-axis label
set ylabel 'time'
set output "uniform-search.png"
plot "data.gnuplot" using 1:4 with linespoint title "BST-Uniform-search","data.gnuplot" using 1:10 with linespoint title "RBST-Uniform-search"


set title 'Time to build in function of the size for non-uniform permutations'                       # plot title
set xlabel 'size'                              # x-axis label
set ylabel 'time'
set output "non-uniform-build.png"
plot "data.gnuplot" using 1:5 with linespoint title "BST-Non-Uniform-Build","data.gnuplot" using 1:8 with linespoint title "RBST-Non-Uniform-Build"

set title 'Height in function of the size for non-uniform permutations'                       # plot title
set xlabel 'size'                              # x-axis label
set ylabel 'Height'
set output "non-uniform-height.png"
plot "data.gnuplot" using 1:6 with linespoint title "BST-Non-Uniform-height","data.gnuplot" using 1:9 with linespoint title "RBST-Non-Uniform-height"

set title 'Time to perform 1000 searches in function of the size for non uniform permutations'                       # plot title
set xlabel 'size'                              # x-axis label
set ylabel 'time'
set output "non-uniform-search.png"
plot "data.gnuplot" using 1:7 with linespoint title "BST-Non-Uniform-search","data.gnuplot" using 1:10 with linespoint title "RBST-Non-Uniform-search"



