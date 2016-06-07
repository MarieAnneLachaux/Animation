set nosurface
set contour base
set cntrparam levels discrete 0.5
set term table # set output type to tables
set out 'unitsquaregp_decision.dat'
splot "unitsquaregp_prob_matrix.dat"
set cntrparam levels discrete 0.25, 0.75
set out 'unitsquaregp_contours.dat'
splot "unitsquaregp_prob_matrix.dat"
reset
set term x11
plot "unitsquaregp_positive.dat" with points ps 2, "unitsquaregp_negative.dat" with points ps 2, "unitsquaregp_active_set.dat" with points ps 4, "unitsquaregp_decision.dat" with lines lw 2, "unitsquaregp_contours.dat" with lines lw 2
pause -1
