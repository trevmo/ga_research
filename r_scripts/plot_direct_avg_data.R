require(ggplot2)
require(tidyr)
source("format_plot.R")

GetTitle <- function(filename) {
  str <- strsplit(filename, "[_ .]+")
  return(paste("Damage Type: ", str[[1]][2], " / ", "Range: ", str[[1]][3], sep = ''))
}
PlotFiles <- function(files, skipLines) {
  dirName <- "avg_data/plots/"
  dir.create(dirName, showWarnings = F)
  for (file in files) {
    dat <- read.csv(file, skip=skipLines)
    gath.dat <- gather(dat, value = "Average.Value", key = "Value", 2:ncol(dat))
    plot <- FormatPlot(ggplot(gath.dat, aes ( x = Generation, y = Average.Value, color = Value)))
    ggsave(paste(paste(dirName, basename(file), sep = ""), "png", sep = "."), plot = plot, width = 10)
  }
}
args = commandArgs(trailingOnly=TRUE)
if (length(args) < 2) {
  stop("You must specify csv file(s) on the command line.n")
}
skipLines <- strtoi(args[1])
PlotFiles(tail(args, length(args)-1), skipLines)