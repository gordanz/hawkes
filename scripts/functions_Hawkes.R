library(tidyverse)

simulate <- function(exe_dir) {
  command_name = paste0(exe_dir,"simulate_hawkes")
  command = paste(command_name, alpha, a, mu, tau, ndiv, nsim, nthr)
  system(command)
}

get_results <- function(data_dir) {
  p <<- read.table(paste0(data_dir,"par.csv"), header = TRUE, sep=",")
  dN <<- read.table(paste0(data_dir,"N.csv"), header  = FALSE, sep=",")
  ld <<- read.table(paste0(data_dir,"ld.csv"), header = FALSE, sep=",")
  dM <<- dN - ld*p$dt
  dB <<- dM/sqrt(ld)
  N <<- data.frame(t(apply(dN,1,cumsum)))
  dld <<- data.frame(t(apply(ld,1,diff)))
  M <<- data.frame(t(apply(dM,1,cumsum)))
  B <<- data.frame(t(apply(dB,1,cumsum)))
}

demean_cols <- function(df) {
  dld = colMeans(df)
  df %>% sweep(2,dld)
}

E <- function(X) {
  matrix(colMeans(as.data.frame(X)), nrow = 1)
}


plot_cols <- function(df) {
  if (!("data.frame" %in% class(df)) ) 
    df = data.frame(y=df)
  
    df_plot= df %>% 
    add_column(t = seq(from = 0, to = 1, length.out = nrow(df) )) %>%
    pivot_longer(cols=!t, values_to = "y") 

  p = ggplot(data=df_plot, aes(x=t, y=y, color=name))+
    geom_line(size = 0.4) + 
    theme(legend.position = "none",
          axis.title.x=element_blank(),
          axis.title.y=element_blank())+
    scale_color_brewer(palette = "Dark2")
  print(p)
}



plot_rows <- function(df){
  plot_cols(t(df))
}




