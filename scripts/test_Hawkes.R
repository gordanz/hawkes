{
script_dir = "~/.h/scripts/"
exe_dir = "~/.h/build/"
data_dir = "~/.h/output/"
pic_dir = "~/.h/output/"
source(paste0(script_dir,"functions_Hawkes.R"))
}

# parameters
{
n=1000; alpha = 0.55; mu_0 = 10; sigma_0 = 10; a_0 = 0.5;
ndiv = 1000; nthr = 8; nsim = 15;
  
    a = 1 - a_0/n; mu = mu_0*n; sigma = sigma_0/n;
}
  
# call 
simulate(exe_dir, data_dir)
get_results(data_dir)

# sample a few trajectories and plot them
ld %>%
  slice_sample(n=15) %>%
  plot_rows
# save_to_png("dld-initial", width = 1500)
# save_to_pdf("B-multiple")

# # code checks
print(mean(B[,ndiv])/sd(B[,ndiv]))
 
# # joint distribution of increments of ld
# ggplot(data = dld, aes(x=V500, y=V501))+
#   geom_density_2d()
# cor(dld$V500, dld$V501)
# hist(dld$V500, nclass=50)
