{
script_dir = "~/.h/scripts/"
exe_dir = "~/.h/build/"
data_dir = "~/.h/build/"
pic_dir = "~/.h/output/"
source(paste0(script_dir,"functions_Hawkes.R"))
}

# parameters
{
n=1000; alpha = 0.75; mu_0 = 10; tau_0 = 1; a_0 = 0.5;
  a = 1 - a_0/n; mu = mu_0*n; tau = tau_0*n;
ndiv = 1000; nthr = 8; nsim = 1;
}
  
# call 
simulate(exe_dir)
get_results(data_dir)

# sample a few trajectories and plot them
dld[,1:100] %>%   
  slice_sample(n=1) %>%
  plot_rows
save_to_png("dld-initial", width = 1500)
# save_to_pdf("B-multiple")

# code checks
mean(B[,ndiv])
sd(B[,ndiv])

# joint distribution of increments of ld
ggplot(data = dld, aes(x=V500, y=V501))+
  geom_density_2d()
cor(dld$V500, dld$V501)
hist(dld$V500, nclass=50)
