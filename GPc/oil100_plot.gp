set palette gray
set palette gamma 2.5
set pm3d map
set pm3d explicit
splot "oil100_variance_matrix.dat" with pm3d, "oil100_latent_data1.dat" with points ps 2, "oil100_latent_data2.dat" with points ps 2, "oil100_latent_data3.dat" with points ps 2
pause -1