set xrange [0:6]
set yrange [0:20]
plot "./inputs/5.case1.in" usi 1:2
plot "./outputs/5.case1.out" usi 1:2
# if you want to save to png files
set terminal png
set output "plots/5.case1.out.png"
replot