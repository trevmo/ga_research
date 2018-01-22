#!/usr/bin/env Rscript

# This script is used to form plots from the data collected by avg_stats.R.
#
# @author trevmo

require(tidyr)
require(ggplot2)

FormPlot <- function(xvals, y1, y2, y1lab, y2lab, title) {
  # Form a plot with two sets of data in the same range.
  #
  # Args:
  #   xvals: vector of x-axis data
  #   y1: vector of first set of y-axis data
  #   y2: vector of second set of y-axis data
  #   y1lab: label for the first set of y-axis data
  #   y2lab: label for the second set of y-axis data
  #   title: title label for the graph
  
  dat <- cbind.data.frame(xvals, y1, y2)
  names(dat) <- c("Range", y1lab, y2lab)
  gath.dat <- gather(dat, value = "Slope", key = "Type", 2:3)
  png(paste(title, "png", sep = "."), width = 849, height = 535)
  plot <- ggplot(gath.dat, aes ( x = Range, y = Slope, color = Type)) + geom_point(size = 2)
  print(plot)
  dev.off()
}
PlotResults <- function(batch, setLabel1, setLabel2) {
  # Pull the data out of the batch of files and form plots.
  #
  # Args:
  #   batch: vector of filenames/paths
  #   setLabel1: unique name in first set of files
  #   setLabel2: unique name in second set of files
  #
  # Returns:
  #   void (outputs plots to file)
  
  set1Avg <- c()
  set1Best <- c()
  set2Avg <- c()
  set2Best <- c()
  for (file in batch) {
    dat <- read.csv(file)
    #TODO: generalize function
    if (grepl(setLabel1, file)) {
      #insert into that set
      set1Avg <- append(set1Avg, dat$avgSlope)
      set1Best <- append(set1Best, dat$bestSlope)
    } else {
      #insert into the other set
      set2Avg <- append(set2Avg, dat$avgSlope)
      set2Best <- append(set2Best, dat$bestSlope)
    }
  }
  range <- seq(0, length(set1Avg)-1)
  FormPlot(range, 
           set1Avg, 
           set2Avg, 
           paste(setLabel1, "avg", sep = "."), 
           paste(setLabel2, "avg", sep = "."),
           "Averages of Average Slope")
  FormPlot(range, 
           set1Best, 
           set2Best, 
           paste(setLabel1, "best", sep = "."), 
           paste(setLabel2, "best", sep = "."),
           "Averages of Best Slope")
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
PlotResults(args, "gaussian", "uniform")