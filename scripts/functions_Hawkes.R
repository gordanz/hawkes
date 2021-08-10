library(tidyverse)

simulate <- function() {
  sdir = "~/.h/build/"
  setwd(sdir)
  
  command_name = paste0(sdir,"simulate_hawkes")
  command = paste(command_name, alpha, a, mu, tau, ndiv, nsim, nthr)
  system(command)
  
  p <<- read.table("par.csv", header = TRUE, sep=",")
  dN <<- read.table("N.csv", header  = FALSE, sep=",")
  ld <<- read.table("ld.csv", header = FALSE, sep=",")
  dM <<- dN - ld*p$dt
  dB <<- dM/sqrt(ld)
  N <<- data.frame(t(apply(dN,1,cumsum)))
  dld <<- data.frame(t(apply(ld,1,diff)))
  # M <<- data.frame(t(apply(dM,1,cumsum)))
  # B <<- data.frame(t(apply(dB,1,cumsum)))
}

demean_cols <- function(df) {
  dld = colMeans(df)
  df %>% sweep(2,dld)
}

E <- function(X) {
  colMeans(as.data.frame(X))
}


plot_cols <- function(df) {
  if (!("data.frame" %in% class(df)) ) {
    df = data.frame(y=df)
  }
  df_plot= df %>% 
    add_column(t = seq(from = 0, to = 1, length.out = nrow(df) )) %>%
    pivot_longer(cols=!t, values_to = "y") 
  
  
  p = ggplot(data=df_plot, aes(x=t, y=y, color=name))+
    geom_line()
  print(p)
}

plot_rows <- function(df){
  plot_cols(t(df))
}




