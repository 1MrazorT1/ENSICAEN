set term png size 600, 400

set output "bst-build.png"
set title 'Time to build the BST in function of the size'                       # plot title
set xlabel 'size'                              # x-axis label
set ylabel 'time'
plot "data.gnuplot" using 1:2 with linespoint title "Uniform", "data.gnuplot" using 1:5 with linespoint title "Non-Uniform"

set output "bst-search.png"
set title 'Time to perform 1000 searches in the BST in function of the size'                       # plot title
set xlabel 'size'                              # x-axis label
set ylabel 'time'
plot "data.gnuplot" using 1:4 with linespoint title "Uniform", "data.gnuplot" using 1:7 with linespoint title "Non-Uniform"

set title 'Height of the BST in function of the size'                       # plot title
set xlabel 'size'                              # x-axis label
set ylabel 'height'
set output "bst-height.png"
plot "data.gnuplot" using 1:3 with linespoint title "Uniform", "data.gnuplot" using 1:6 with linespoint title "Non-Uniform"


