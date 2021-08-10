
{
source("~/.hc/functions_Hawkes.R")
compile()
set_parameters( muz = 100, alpha = 0.7, n = 100,
                nsim = 100, ndiv = 128)
simulate()
}


# demean trajectories, sample a few and plot
df_sample = ld %>% 
  slice_sample(n=10) %>% 
  plot_rows

# check if martingale
mean(dM$X128)

# correlation between increments
ggplot(data = dN, aes(x=X100, y=X101))+geom_density_2d()
cor(dN$X100, dN$X101)
hist(B$X1024)
