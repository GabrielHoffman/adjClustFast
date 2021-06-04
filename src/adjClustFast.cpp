// [[Rcpp::depends("RcppArmadillo")]]
#include <RcppArmadillo.h>
// #include <omp.h>

// write RcppExports.R with: 
//       Rcpp::compileAttributes(".")



// Exports from mainFunctions.c

// There are written to RcppExport.cpp
// 	Once they are there, comment this out

// // [[Rcpp::export]]
// extern "C" SEXP percDown(SEXP Rpositions, SEXP Rdistances, SEXP Rl, SEXP Rpos);

// // [[Rcpp::export]]
// extern "C" SEXP cWardHeaps(SEXP RrcCumRight, SEXP RrcCumLeft, SEXP Rh, SEXP Rp, SEXP RchainedL, SEXP Rpositions, SEXP Rdistances, SEXP RlHeap, SEXP Rmerge, SEXP Rgains, SEXP RtraceW);




// Replace adjclust::matR() and adjclust::matL() with RcppArmadillo code
// Use separate version for matrix and sparseMatrix

// [[Rcpp::export]]
arma::SpMat<double> matL_sparse(const arma::SpMat<double> & Csq, const int & h) {

	int p = Csq.n_rows;
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


// [[Rcpp::export]]
arma::mat matL_full(const arma::mat & Csq, const int & h) {

	int p = Csq.n_rows;
	arma::mat out(p, h+1);

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




// [[Rcpp::export]]
arma::SpMat<double> matR_sparse(const arma::SpMat<double> & Csq, const int & h) {
	               
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


// [[Rcpp::export]]
arma::mat matR_full(const arma::mat & Csq, const int & h) {
	               
	int p = Csq.n_rows;
	arma::mat out(p, h+1);

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
