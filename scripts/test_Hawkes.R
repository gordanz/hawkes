source("~/.h/R/functions_Hawkes.R")
n=1000;
alpha = 2; a = 1 - 0.5/n; mu = 10*n; tau = n;
ndiv = 10000; nthr = 8; nsim = 1000/nthr;
simulate()

# # demean trajectories, sample a few and plot
ld %>%   
  slice_sample(n=1) %>%
  plot_rows

 
# # check if martingale
E(dM$V8)
# 
# # correlation between increments
# ggplot(data = dN, aes(x=X100, y=X101))+geom_density_2d()
# cor(dN$X100, dN$X101)
# hist(B$X1024)
