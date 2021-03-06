library(tidyverse)

simulate <- function(exe_dir, output_dir) {
  command_name = paste0(exe_dir,"simulate_hawkes")
  command = paste(command_name, 
                  "-d", Sys.glob(output_dir),
                  "-l", alpha, 
                  "-a", a, 
                  "-m", mu, 
                  "-s", sigma, 
                  "-D", ndiv, 
                  "-S", nsim, 
                  "-T", nthr)
  print(paste("Running",command))
  system(command)
}

get_results <- function(data_dir) {
  print("Loading data.")
  p <<- read.table(paste0(data_dir,"par.csv"), header = TRUE, sep=",")
  dN <<- read.table(paste0(data_dir,"dN.csv"), header  = FALSE, sep=",")
  N <<- read.table(paste0(data_dir,"N.csv"), header  = FALSE, sep=",")
  ld <<- read.table(paste0(data_dir,"ld.csv"), header = FALSE, sep=",")
  dL <<- read.table(paste0(data_dir,"dL.csv"), header  = FALSE, sep=",")
  print("Additional computations.")
  dB <<- (dN - dL)/sqrt(ld)
  B <<- data.frame(t(apply(dB,1,cumsum)))
  print("Done")
}

demean_cols <- function(df) {
  dld = colMeans(df)
  df %>% sweep(2,dld)
}

E <- function(X) {
  matrix(colMeans(as.data.frame(X)), nrow = 1)
}

p_string <- function(name="", ext="") {
  if (name != "" )
    name = paste0(name,"_")
  
  if (ext != "")
      ext = paste0(".", ext)
  
  paste0(
    name,
    "alpha=",p$alpha,"_",
    "a=",p$a,"_",
    "mu=",p$mu,"_",
    "tau=",p$tau,"_",
    "ndiv=",p$ndiv,"_",
    "nsim=",p$nsim,
    ext
  )
}

save_to_png <- function(name="", ...) {
  new_dir = paste0(pic_dir, p_string()) 
  dir.create(file.path(new_dir), showWarnings = FALSE)
  file_name = paste0(new_dir,"/", p_string(name,"png"))
  dev.print(png, file_name, ...)
}

save_to_pdf <- function(name="") {
  file_name = paste0(pic_dir, p_string(name,"pdf"))
  dev.print(pdf, file_name)
}

plot_cols <- function(df, points = FALSE) {
  if (!("data.frame" %in% class(df)) ) 
    df = data.frame(y=df)
  
    df_plot= df %>% 
    add_column(t = seq(from = 0, to = 1, length.out = nrow(df) )) %>%
    pivot_longer(cols=!t, values_to = "y") 

  if (points) {
  p = ggplot(data=df_plot, aes(x=t, y=y, color=name))+
    geom_point(size = 0.6) + 
    geom_segment(aes(x = t, y = y, xend = t, yend = 0))+
    theme(legend.position = "none",
          axis.title.x=element_blank(),
          axis.title.y=element_blank())
  # +
  #   scale_color_brewer(palette = "Dark2") 
  } else {
  p = ggplot(data=df_plot, aes(x=t, y=y, color=name))+
    geom_line(size = 0.6) + 
    theme(legend.position = "none",
          axis.title.x=element_blank(),
          axis.title.y=element_blank())
  # +
  #   scale_color_brewer(palette = "Dark2") }
  }
  print(p)
}



plot_rows <- function(df,...){
  plot_cols(t(df),...)
}




