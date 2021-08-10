script_dir = "~/.h/scripts/"
exe_dir = "~/.h/build/"
data_dir = "~/.h/build/"

source(paste0(script_dir,"functions_Hawkes.R"))

# parameters
n=1000; alpha = 2; mu_0 = 10; tau_0 = 1; a_0 = 0.5;
  a = 1 - a_0/n; mu = mu_0*n; tau = tau_0*n;
ndiv = 10000; nthr = 1; nsim = 1;

# call 
simulate(exe_dir)
get_results(data_dir)

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
