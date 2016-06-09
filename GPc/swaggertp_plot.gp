set palette gray
set palette gamma 2.5
set pm3d map
set pm3d explicit
splot "swaggertp_variance_matrix.dat" with pm3d, "swaggertp_latent_data0.dat" with points ps 2
pause -1