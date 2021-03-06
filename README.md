
# adjClustFast

This is a faster version of [adjclust](https://cran.r-project.org/package=adjclust) that: 

* uses [RcppArmadillo](https://cran.r-project.org/package=RcppArmadillo) to remove a bottleneck
* reduces memory usage by freeing matrices once they are no longer need
* removes expensive checking code

For a `sparseMatrix` similarity matrix of 10K SNPs, `adjClustFast` can be >10X faster then the original `adjclust`, while using ~10X less memory. `adjClustFast` can also handle >200K SNPs, while `adjclust` can crash after it allocates too much memory.


## Install
```
devtools::install_github("GabrielHoffman/adjClustFast")
```