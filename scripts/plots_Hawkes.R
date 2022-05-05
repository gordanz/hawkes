{
  script_dir = "~/.h/scripts/"
  build_dir = "~/.h/build/"
  output_dir = "~/.h/output/"
  source(paste0(script_dir,"functions_Hawkes.R"))
}

# load results
get_results(paste0(output_dir,"n=10_alpha=2.0_nsim=8/")); n=10;
attach(p)

N %>%
  slice_sample(n=1) %>%
  plot_rows

C = (1-a) * ld / n;
C %>%
  slice_sample(n=1) %>%
  plot_rows

dC = data.frame(t(apply(C,1,diff)))
dC %>%
  slice_sample(n=1) %>%
  plot_rows
 
