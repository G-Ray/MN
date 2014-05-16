set xlabel "x (m)"
set ylabel "z (m)"
set title "position de la bille"
plot "positions.txt" u 2:4, "escalier.txt" with points
set term postscript color
set output "positions.ps"
plot "positions.txt" u 2:4, "escalier.txt" with points
set term x11
