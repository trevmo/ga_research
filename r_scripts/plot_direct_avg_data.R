require(ggplot2)
require(tidyr)

GetTitle <- function(filename) {
  str <- strsplit(filename, "[_ .]+")
  return(paste("Damage Type: ", str[[1]][3], " / ", "Range: ", str[[1]][4], sep = ''))
}
PlotFiles <- function(files) {
  for (file in files) {
    dat <- read.csv(file)
    png(paste(basename(file), "png", sep = "."), width = 849, height = 535)
    
    gath.dat <- gather(dat, value = "Avg", key = "Value", 2:ncol(dat))
    plot <- ggplot(gath.dat, aes ( x = Generation, y = Avg, color = Value)) + 
      geom_point(size = 2) + 
      ggtitle(GetTitle(file)) + 
      theme(plot.title = element_text(face = "bold", size = 24, hjust = 0.5))
    print(plot)
    dev.off()
  }
}
args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
PlotFiles(args)