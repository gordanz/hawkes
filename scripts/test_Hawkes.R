{
script_dir = "~/.h/scripts/"
exe_dir = "~/.h/build/"
data_dir = "~/.h/build/"
source(paste0(script_dir,"functions_Hawkes.R"))
}

# parameters
{
n=100; alpha = 2; mu_0 = 10; tau_0 = 1; a_0 = 0.5;
  a = 1 - a_0/n; mu = mu_0*n; tau = tau_0*n;
ndiv = 1000; nthr = 8; nsim = 125;
}

# call 
simulate(exe_dir)
get_results(data_dir)

# sample a few trajectories and plot them
B %>%   
  slice_sample(n=10) %>%
  plot_rows


# code checks
mean(B[,ndiv])
sd(B[,ndiv])

# joint distribution of increments of ld
ggplot(data = dld, aes(x=V500, y=V501))+
  geom_density_2d()
cor(dld$V500, dld$V501)
hist(dld$V500, nclass=50)
