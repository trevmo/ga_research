#!/usr/bin/env Rscript

# This script is used to form plots from the data collected by avg_stats.R.
#
# @author trevmo

FormPlot <- function(x, y1, y2, y1lab, y2lab, xaxis, yaxis, title) {
  # Form a plot with two sets of data in the same range.
  #
  # Args:
  #   x: vector of x-axis data
  #   y1: vector of first set of y-axis data
  #   y2: vector of second set of y-axis data
  #   y1lab: label for the first set of y-axis data
  #   y2lab: label for the second set of y-axis data
  #   xaxis: label for the units of the x-axis
  #   yaxis: label for the units of the y-axis
  #   title: title label for the graph
  
  colors = rainbow(2, alpha = 1, start = 0, end = 4/6)
  plot(x, y1, col = colors[1], xlab = xaxis, ylab = yaxis, main = title, pch = 19)
  legend("bottomright", c(y1lab, y2lab), fill = colors)
  points(x, y2, col = colors[2], pch = 15)
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
      set1Avg <- c(set1Avg, dat$avgSlope)
      set1Best <- c(set1Best, dat$bestSlope)
    } else {
      #insert into the other set
      set2Avg <- c(set2Avg, dat$avgSlope)
      set2Best <- c(set2Best, dat$bestSlope)
    }
  }
  range <- seq(1, length(set1Avg))
  FormPlot(range, 
           set1Avg, 
           set2Avg, 
           paste(setLabel1, " avg"), 
           paste(setLabel2, " avg"), 
           "range/std. dev.", 
           "avg. slope", 
           "Averages of Average Slope")
  FormPlot(range, 
           set1Best, 
           set2Best, 
           paste(setLabel1, " best"), 
           paste(setLabel2, " best"),
           "range/std. dev.", 
           "avg. slope", 
           "Averages of Best Slope")
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
PlotResults(args, "gaussian", "uniform")