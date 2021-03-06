#!/usr/bin/env Rscript

# This script is used to form plots from the data collected by avg_stats.R.
#
# @author trevmo

require(tidyr)
require(ggplot2)
source("format_plot.R")

FormPlot <- function(data, type, title) {
  # Form a multi-variable plot from the specified matrix.
  #
  # Args:
  #   data: matrix of data to plot
  #   title: title label for the graph
  
  gath.dat <- gather(data, value = "Slope", key = "Value", 2:ncol(data))
  plot <- FormatPlot(ggplot(gath.dat, aes ( x = Range, y = Slope, color = Value))) +
    geom_point(size = 1.5, aes(shape = Value, fill = Value))
  
  ggsave(paste(title, "png", sep = "."), plot = plot, width = 10)
}
PlotResults <- function(batch, prefix) {
  # Pull the data out of the batch of files and form plots.
  #
  # Args:
  #   batch: vector of filenames/paths
  #   prefix: type of data to prefix file name with
  #
  # Returns:
  #   void (outputs plots to file)
  
  fileNum = 1
  names <- c()
  for (file in batch) {
    dat <- read.csv(file)
    for (row in 1:nrow(dat)) {
      if (fileNum == 1) {
        names <- c(names, row.names(dat)[row])
        if (row == 1) {
          slopes <- matrix(ncol = length(batch), nrow = nrow(dat)+1)
          slopes[1,] <- seq(0, length(batch)-1)
        }
      }
      slopes[row+1, fileNum] <- dat[row, 1]
    }
    fileNum <- fileNum + 1
  }
  rownames(slopes) <- c("Range", names)
  slopes <- as.data.frame(t(slopes))
  FormPlot(slopes, prefix, paste(prefix, "avg_slopes_for_data", sep = "_"))
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.")
}
PlotResults(args, strsplit(basename(args[1]), "_")[[1]][2])