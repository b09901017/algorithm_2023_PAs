set xrange [0:1000]
set yrange [0:1000000]
plot "./inputs/1000.case1.in" usi 1:2
#plot "./outputs/5.case1.out" usi 1:2
# if you want to save to png files
set terminal png
set output "plots/1000.case1.in.png"
replot