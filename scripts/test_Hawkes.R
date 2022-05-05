{
  script_dir = "~/.h/scripts/"
  build_dir = "~/.h/build/"
  output_dir = "~/.h/output/"
  source(paste0(script_dir,"functions_Hawkes.R"))
}

# parameters
get_results(paste0(output_dir,"n=10_alpha=0.5_nsim=8/")); n=10;
attach(p)
C = (1-a) * ld / n;

# sample a few trajectories and plot them
C %>%
  slice_sample(n=1) %>%
  plot_rows

# print(n/(1-a)/mean(N[,ndiv]));
# print(n/(1-a)/sd(N[,ndiv]))
# save_to_png("dld-initial", width = 1500)
# save_to_pdf("B-multiple")

# # code checks
# print(mean(B[,ndiv])/sd(B[,ndiv]))
 
# # joint distribution of increments of ld
# ggplot(data = dld, aes(x=V500, y=V501))+
#   geom_density_2d()
# cor(dld$V500, dld$V501)
# hist(dld$V500, nclass=50)
B%>%
  slice_sample(n=15) %>%
  plot_rows
