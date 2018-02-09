#!/usr/bin/Rscript

# This script is used to find the linear approximation, and associated
# values, from a batch of csv files. Each file is expected to have a
# header of 13 lines listing info about the trial run, followed by
# 100 rows of n columns of data.
#
# @author trevmo

FindLinearApprox <- function (xvals, yvals) {
  # Calculates the linear approximation and retrieves the corresponding
  # slope and R^2 values.
  #
  # Args:
  #   xvals: vector of data comprising the x axis
  #   yvals: vector of data comprising the y axis
  # Returns:
  #   vector containing the slope and R^2 values
  
  model <- lm (yvals ~ xvals)
  r2 <- summary(model)$r.squared
  slope <- model$coefficients['xvals']
  final <- c(slope, r2)
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
  
  header <- read.csv(filename, nrows=12)
  write.csv(header, outputPath, row.names = FALSE)
  dat <- read.csv(filename, skip = 13)
  approxVals <- c()
  names <- c()
  counter = 0
  for (col in names(dat)) {
    if (col == "Generation") {
      gen <- dat[[col]]
    } else {
      vals <- FindLinearApprox(gen, dat[[col]])
      approxVals <- c(approxVals, vals)
      names <- c(names, col)
      counter <- counter + 1
    }
  }
  table <- matrix(approxVals, ncol = counter, byrow = T)
  colnames(table) <- c("slope", "r2")
  rownames(table) <- names
  table <- as.table(table)
  #write the table out to the file created earlier
  write.table(table, outputPath, sep = ",", col.names = T, row.names = T, append = T)
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
#loop over the csv files, creating output files
for (arg in args) {
  FindResults(arg)
}