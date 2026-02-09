# Output Settings
set terminal pngcairo size 1400,600 enhanced font 'Arial,12'
set output 'complexity_comparison.png'

# Enable Multiplot (2 graphs in 1 image)
set multiplot layout 1,2 title "Median of Medians vs. Quickselect: Complexity Analysis" font ",16"

# ---------------------------------------------------------
# GRAPH 1: TIME COMPLEXITY
# ---------------------------------------------------------
set title "1. Time Complexity (Speed)" font ",14"
set xlabel "Input Size (N - Households)"
set ylabel "Operations (Log Scale)"
set grid
set key top left

# Range for N (Census size)
set xrange [100:120000]

# Log Scale required to show O(n) vs O(n^2)
set logscale y
set format y "10^{%L}"
set yrange [100:1000000000]

# Define Time Functions
# 1. Median of Medians (Worst Case): Linear O(n), but with high overhead constant
time_mom_worst(x) = 25 * x

# 2. Quickselect (Average Case): Linear O(n), very fast (low constant)
time_qs_avg(x) = 2 * x

# 3. Quickselect (Worst Case): Quadratic O(n^2). Scaled down slightly for visibility
time_qs_worst(x) = 0.05 * x**2

plot time_mom_worst(x) title 'Median of Medians (Worst Case O(n))' w lines lw 3 lc rgb "blue", \
     time_qs_avg(x)   title 'Quickselect (Avg Case O(n))'       w lines lw 3 lc rgb "green", \
     time_qs_worst(x) title 'Quickselect (Worst Case O(n^2))'    w lines lw 3 lc rgb "red"

# ---------------------------------------------------------
# GRAPH 2: SPACE COMPLEXITY
# ---------------------------------------------------------
set title "2. Space Complexity (Memory)" font ",14"
set xlabel "Input Size (N - Households)"
set ylabel "Memory Units (Linear Scale)"
set grid
set key top left

# Reset formatting (Linear scale is better for Space comparison)
unset logscale y
set format y "%.0f"
set yrange [0:120000]

# Define Space Functions
# 1. Median of Medians: Uses auxiliary array for medians. Approx N/5 space.
space_mom(x) = x / 5

# 2. Quickselect (Avg): Logarithmic stack depth O(log n).
space_qs_avg(x) = log(x)

# 3. Quickselect (Worst): Linear recursion depth O(n) if pivot is bad.
space_qs_worst(x) = x

plot space_mom(x)     title 'Median of Medians (Aux Array O(N))' w lines lw 3 lc rgb "blue", \
     space_qs_avg(x)  title 'Quickselect (Avg Stack O(log N))'   w lines lw 3 lc rgb "green", \
     space_qs_worst(x) title 'Quickselect (Worst Stack O(N))'     w lines lw 3 lc rgb "red"

# End Multiplot
unset multiplot