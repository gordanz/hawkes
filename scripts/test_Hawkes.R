{
script_dir = "~/.h/scripts/"
exe_dir = "~/.h/build/"
data_dir_2 = "~/.h/output2/"
data_dir6 = "~/.h/output06/"
pic_dir = "~/.h/output/"
source(paste0(script_dir,"functions_Hawkes.R"))
}

# parameters
{
n=3000; alpha = 0.6; mu_0 = 1; sigma_0 = 1; a_0 = 0.9;
ndiv = 1000; nthr = 8; nsim = 1;
  
    a = 1 - a_0/n; mu = mu_0*n; sigma = sigma_0/n;
}
  
# call 
simulate(exe_dir, data_dir6)
get_results(data_dir)


C = (1-a) * ld / n;

# sample a few trajectories and plot them
C %>%
  slice_sample(n=1) %>%
  plot_rows

print(n/(1-a)/mean(N[,ndiv]));
print(n/(1-a)/sd(N[,ndiv]))
# save_to_png("dld-initial", width = 1500)
# save_to_pdf("B-multiple")

# # code checks
# print(mean(B[,ndiv])/sd(B[,ndiv]))
 
# # joint distribution of increments of ld
# ggplot(data = dld, aes(x=V500, y=V501))+
#   geom_density_2d()
# cor(dld$V500, dld$V501)
# hist(dld$V500, nclass=50)
N %>%
  slice_sample(n=15) %>%
  plot_rows
