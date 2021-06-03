// [[Rcpp::depends("RcppArmadillo")]]
#include <RcppArmadillo.h>
// #include <omp.h>

// another simple example: outer product of a vector, 
// returning a matrix
//
// [[Rcpp::export]]
arma::SpMat<double> matL(const arma::SpMat<double> & Csq, const int & h) {

	int p = Csq.n_rows;
// 	// int h = Rcpp::as<int>(h_);
	arma::SpMat<double> out(p, h+1);

	int k;
	double value;

	// omp_set_num_threads(4) ;
	// #pragma omp parallel for               
	for( int i=0; i<p; i++){
		k = 0;
		for( int j=i; j<std::min(i+h+1,p); j++){
			if(k == 0){
				out(i,k) = 1;
			}else{
				value = Csq(i,j);
				if( value!= 0.0){
					out(i,k) = 2.0*value;
				}
			}
			k++;
		}
	}

	return out;	           
}


arma::SpMat<double> matR(const arma::SpMat<double> & Csq, const int & h) {
	               
	int p = Csq.n_rows;
	arma::SpMat<double> out(p, h+1);

	int k;
	double value;

	// omp_set_num_threads(4) ;
	// #pragma omp parallel for   
	for( int i=0; i<p; i++){
		k = 0;
		for( int j=i; j>=std::max(i-h, (int) 0); j--){
		  if(k == 0){
		    out(p-i-1,k) = 1;
		  }else{
		    value = Csq(i,j);
		    if( value != 0.0){
		        out(p-i-1,k) = 2.0*value;
		    }
		  }
		  k++;
		}
	}

	return out;
}




