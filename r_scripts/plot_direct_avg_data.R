require(ggplot2)
require(tidyr)

GetTitle <- function(filename) {
  str <- strsplit(filename, "[_ .]+")
  return(paste("Damage Type: ", str[[1]][2], " / ", "Range: ", str[[1]][3], sep = ''))
}
PlotFiles <- function(files) {
  for (file in files) {
    dat <- read.csv(file)
    png(paste(basename(file), "png", sep = "."), width = 1000, height = 700)
    
    gath.dat <- gather(dat, value = "Average.Value", key = "Value", 2:ncol(dat))
    plot <- ggplot(gath.dat, aes ( x = Generation, y = Average.Value, color = Value)) + 
      geom_point(size = 3) + 
      ggtitle(GetTitle(basename(file))) + 
      theme(plot.title = element_text(face = "bold", size = 24, hjust = 0.5)) +
      theme(axis.title = element_text(size = 20)) +
      theme(axis.text = element_text(size = 12)) + 
      theme(legend.text = element_text(size = 12)) +
      theme(legend.title = element_text(size = 12)) +
      theme(legend.position = "bottom")
    print(plot)
    dev.off()
  }
}
args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
PlotFiles(args)