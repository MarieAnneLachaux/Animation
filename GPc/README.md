//	for testing the gplvm, run the latter command in terminal
//	the swagger.svml is in so-called "SVM light" format
./gplvm -v 3 learn -L true examples/swagger.svml swagger.model

//the result of the upper command is swagger.model. For visualization, run
./gplvm gnuplot swagger.model swagger

/* 	the upper command creates swagger_plot.gp which is a plot for gnuplot,
	swagger_latent_data0.dat which contains the original data in 3D vector,
	swagger_variance_matrix.dat which contains the distribution of probability. 
	note that the 3-d data is shown in 2D space, the 3rd attribute of every line serves as the probability of the data, thus intensity of the point in the visualization.

	run the following command to paint the distribution map with gnuplot
*/
gnuplot swagger_plot.gp


/*when reading the files, note that 0x1.999999999999ap-3 is 0.2 in float type*/

//with back constraint, still bugged at 7 juin 2016. YET ACCORDING TO THE PROF, IT DOESNT MATTER THAT MUCH
./gplvm -v 3 learn -L true -c rbf -g 0.0001 examples/swagger.svml swagger_back_constrained.model
