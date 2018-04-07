#!/usr/bin/env Rscript

# This script is used for forming plots of averaged data. It expects csv files, with
# or without a header, where the first column contains the Generation and the remaining columns
# are data values with the last column being the fitness values.
#
# @author trevmo

require(ggplot2)
require(tidyr)
source("format_plot.R")


PlotFiles <- function(files, skipLines, includeFitness) {
  # Creates and saves a formatted plot for each of the files.
  #
  # Args:
  #   files: vector of filenames
  #   skipLines: number of (header) lines to skip in each file
  #   includeFitness: {0 - do not include; 1 - include}
  
  dirName <- "avg_data/plots/"
  dir.create(dirName, showWarnings = F)
  for (file in files) {
    dat <- read.csv(file, skip=skipLines)
    
    if (includeFitness)
      endRange <- ncol(dat)
    else
      endRange <- (ncol(dat) - 1)
    gath.dat <- gather(dat, value = "Average.Value", key = "Value", 2:endRange)
    
    plot <- FormatPlot(ggplot(gath.dat, aes ( x = Generation, y = Average.Value, color = Value))) +
      geom_point(size = 1.5, aes(shape = Value, fill = Value))
    ggsave(paste(paste(dirName, basename(file), sep = ""), "png", sep = "."), plot = plot, width = 10)
  }
}
args = commandArgs(trailingOnly=TRUE)
if (length(args) < 3) {
  stop("Args:\n\tskipLines: number of (header) lines to skip in each file\n\tincludeFitness: {0 - do not include; 1 - include}\n\tfiles: vector of filenames")
}
skipLines <- strtoi(args[1])
includeFitness <- strtoi(args[2])
PlotFiles(tail(args, length(args)-2), skipLines, includeFitness)