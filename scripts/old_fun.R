library(tidyverse)
library(Rcpp)
library(parallel)
library(tictoc)

# make parameters global variables
nsim = 0; ndiv = 1; alpha = 1;
n = 1; mu = 1; a = 1; tau = 1

set_parameters <- function(muz,alpha,n,nsim,ndiv) {
  .GlobalEnv$alpha = alpha;
  .GlobalEnv$n = n;
  .GlobalEnv$nsim = nsim;
  .GlobalEnv$ndiv = ndiv;
  
  # derived parameters
  .GlobalEnv$mu = muz * n**alpha;
  .GlobalEnv$a = 1-n**(-alpha);
  .GlobalEnv$tau = n;
  .GlobalEnv$dt = 1/ndiv;
}

compile <- function() {
  tic("Compiling")
  sourceCpp("~/.hc/simulate.cpp", verbose = TRUE)
  toc()
}

simulate <- function(numcores = detectCores()) {
  
  if (nsim == 0) stop("Parameters not set. Use \"set_parameters\".")
  
  nsim_per_core = nsim %/% numcores;
  .GlobalEnv$nsim = nsim_per_core * numcores;
  
  print(paste("Using", numcores, "cores."))
  tic("")
  seeds = floor( 2147483647*runif(numcores) )
  
  f <- function(seed) {
    simulate_hawkes(seed, mu, a, alpha, tau, nsim_per_core, ndiv)
  }
  
  out_list = 
    mclapply(seeds, f, mc.cores = numcores)
  
  dN_l = numeric(); ld_l = numeric();
  for (i in 1:numcores) {
    dN_l = c(dN_l, out_list[[i]]$N);
    ld_l = c(ld_l, out_list[[i]]$ld);
  }
  
  .GlobalEnv$dN = dN_l %>% 
    matrix(byrow = TRUE, nrow = nsim) %>%
    data.frame
  
  .GlobalEnv$ld = ld_l %>% 
    matrix(byrow = TRUE, nrow = nsim) %>%
    data.frame
  
  .GlobalEnv$dM = .GlobalEnv$dN - .GlobalEnv$ld*dt
  .GlobalEnv$osqd = 1/sqrt(.GlobalEnv$ld)
  .GlobalEnv$dB = .GlobalEnv$osqd*.GlobalEnv$dM
  
  
  .GlobalEnv$M = t(apply(.GlobalEnv$dM, 1, cumsum)) %>% data.frame
  .GlobalEnv$B = t(apply(.GlobalEnv$dB, 1, cumsum)) %>% data.frame
  
  toc()
}

demean_cols <- function(df) {
  dld = colMeans(df)
  df %>% sweep(2,dld)
}

E <- function(X) {
  colMeans(as.data.frame(X))
}

Int <- function(X) {
  rowMeans(X)
}

plot_rows <- function(df) {
  
  if (class(df) != "data.frame") {
    df = data.frame(x=df)
  }
  
  df_plot= df %>% 
    t %>% 
    data.frame %>% 
    add_column(time) %>%
    pivot_longer(cols=!time) 
  
  p = ggplot(data=df_plot, aes(x=time, y=value, color=name))+
    geom_line()
  print(p)
}

plot_cols <- function(df) {
  if (!("data.frame" %in% class(df)) ) {
    df = data.frame(y=df)
  }
  df_plot= df %>% 
    add_column(t = seq(from = 0, to = 1, length.out = nrow(df) )) %>%
    pivot_longer(cols=!t, values_to = "y") 
  
  
  p = ggplot(data=df_plot, aes(x=t, y=y, color=name))+
    geom_line()
  print(p)
}

plot_rows <- function(df){
  plot_cols(t(df))
}




