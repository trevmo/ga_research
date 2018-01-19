#!/usr/bin/env Rscript


# This script is to plot data results in the format Generation,Average Fitness, Best Fitness
#     Line 1: column labels
#     Lines 2+: three columns of data
#
# @author trevmo

require(tidyr)
require(ggplot2)

PlotData <- function(filename) {
  dat <- read.csv(filename)
  bygen <- gather(dat, value = "Fitness", key = "Type", Average.Fitness, Best.Fitness)
  ggplot(bygen, aes ( x = Generation, y = Fitness, color = Type)) + geom_point(size = 1.5)
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
PlotData(args[1])
