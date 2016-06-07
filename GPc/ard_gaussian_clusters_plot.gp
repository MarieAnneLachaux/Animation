set nosurface
set contour base
set cntrparam levels discrete 0.5
set term table # set output type to tables
set out 'ard_gaussian_clusters_decision.dat'
splot "ard_gaussian_clusters_prob_matrix.dat"
set cntrparam levels discrete 0.25, 0.75
set out 'ard_gaussian_clusters_contours.dat'
splot "ard_gaussian_clusters_prob_matrix.dat"
reset
set term x11
plot "ard_gaussian_clusters_positive.dat" with points ps 2, "ard_gaussian_clusters_negative.dat" with points ps 2, "ard_gaussian_clusters_active_set.dat" with points ps 4, "ard_gaussian_clusters_decision.dat" with lines lw 2, "ard_gaussian_clusters_contours.dat" with lines lw 2
pause -1
