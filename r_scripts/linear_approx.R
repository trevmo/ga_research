#!/usr/bin/env Rscript

# This script is used to find the linear approximation, and associated
# values, from a batch of csv files. Each file is expected to have a
# header of 9 lines listing info about the trial run, followed by
# 100 rows of 3 columns of data.
#
# @author trevmo

require(ggplot2)

FindLinearApprox <- function (xvals, yvals, slopeLabel, r2Label) {
  # Calculates the linear approximation and retrieves the corresponding
  # slope and R^2 values.
  #
  # Args:
  #   xvals: vector of data comprising the x axis
  #   yvals: vector of data comprising the y axis
  #   slopeLabel: label for slope col of the table of results
  #   r2Label: label for r^2 col of the table of results
  # Returns:
  #   table containing the slope and R^2 values
  model <- lm (yvals ~ xvals)
  r2 <- summary(model)$r.squared
  slope <- model$coefficients['xvals']
  #form a table with those values and labels
  final <- matrix(c(slope, r2), ncol = 2, byrow = TRUE)
  colnames(final) <- c(slopeLabel, r2Label)
  final <- as.table(final)
  return(final)
}
FindResults <- function(filename) {
  # Find the results from the data in the specified csv file.
  #
  # Arg:
  #   filename: name of the csv file
  #
  # Returns:
  #   void (outputs results to a new file)
  dirName <- "stats"
  dir.create(dirName, showWarnings = F)
  output <- paste("stats", basename(filename), sep="_")
  outputPath <- file.path(dirName, output)
  header <- read.csv(filename, nrows=9)
  write.csv(header, outputPath, row.names = FALSE)
  dat <- read.csv(filename, skip = 10)
  gen <- dat$Generation
  avg <- dat$AvgFit
  best <- dat$BestFit
  #plot(x,y)
  avgFinal <- FindLinearApprox(gen, avg, 'avgSlope', 'r^2')
  bestFinal <- FindLinearApprox(gen, best, 'bestSlope', 'r^2')
  #write the table out to the file created earlier
  write.table(avgFinal, outputPath, sep = ",", col.names = T, row.names = F, append = T)
  write.table(bestFinal, outputPath, sep = ",", col.names = T, row.names = F, append = T)
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
#loop over the csv files, creating output files
for (arg in args) {
  FindResults(arg)
}