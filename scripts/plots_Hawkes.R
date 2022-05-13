{
  script_dir = "~/hawkes/scripts/"
  build_dir = "~/hawkes/build/"
  output_dir = "~/hawkes/output/"
  source(paste0(script_dir,"functions_Hawkes.R"))
}

# load results
get_results(paste0(output_dir,"n=10_alpha=0.1_nsim=8/")); n=10;
# get_results(paste0(output_dir,"n=10_alpha=2.0_nsim=8/")); n=10;
# get_results(paste0(output_dir,"n=100_alpha=0.1_nsim=8/")); n=100;
# get_results(paste0(output_dir,"n=100_alpha=2.0_nsim=8/")); n=100;
get_results(paste0(output_dir,"n=10000_alpha=0.1_nsim=8/")); n=10000;
# get_results(paste0(output_dir,"n=10000_alpha=0.9_nsim=8/")); n=10000;
 get_results(paste0(output_dir,"n=10000_alpha=1.1_nsim=8/")); n=10000;

# get_results(paste0(output_dir,"n=1000_alpha=2.0_nsim=800/")); n=1000;
# get_results(paste0(output_dir,"n=1000_alpha=0.7_nsim=800/")); n=1000;

attach(p)

N %>%
  slice_sample(n=8) %>%
  plot_rows

C = (1-a) * ld / n;
C %>%
  slice_sample(n=1) %>%
  plot_rows

dC = data.frame(t(apply(C,1,diff)))
dC %>%
  slice_sample(n=1) %>%
  plot_rows(points = TRUE)

# # joint distribution of increments of C
ggplot(data = dC, aes(x=V900, y=V901))+
  geom_point()
cor(dC$V900, dC$V901)
hist(dC$V900, nclass=50)
 
