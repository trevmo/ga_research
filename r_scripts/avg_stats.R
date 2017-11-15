#!/usr/bin/env Rscript

# This script is used to average data collected in csv files. The expected format
# of the files is:
#     Lines 1-10: header info
#     Line 11: first labels
#     Line 12: first data
#     Line 13: second labels
#     Line 14: second data
#
# @author trevmo

BatchFiles <- function (files, numTrialsPerCombo) {
  # Forms a matrix such that each column of the matrix contains
  # a batch of trial data for a particular combo of attack type and range
  #
  # Arg:
  #   files: vector of filenames
  #   numTrialsPerCombo: number of files per batch
  #
  # Returns:
  #   matrix of batched files
  
  numCombos <- (length(files) / numTrialsPerCombo)
  batches <- matrix(files, ncol = numCombos, nrow = numTrialsPerCombo)
  return(batches)
}
FindAvgs <- function(batch, outputDir) {
  # Calculate the average results from a batch of csv files.
  #
  # Arg:
  #   batch: vector of filenames/paths
  #   outputDir: name of the directory to place the output file
  #
  # Returns:
  #   void (outputs results to a new file)
  
  avgSlopeVals <- c()
  avgR2Vals <- c()
  bestSlopeVals <- c()
  bestR2Vals <- c()
  for (file in batch) {
    dat <- read.csv(file, skip = 10)
    
    avgSlopeVals <- c(avgSlopeVals, dat$slope[[1]][[1]])
    avgR2Vals <- c(avgR2Vals, dat$r2[[1]][[1]])
    bestSlopeVals <- c(bestSlopeVals, dat$slope[[2]][[1]])
    bestR2Vals <- c(bestR2Vals, dat$r2[[2]][[1]])
  }
  
  #form the filename by splitting out the attack type and range from
  #the first file in the batch
  outputFile <- basename(batch[[1]])
  str <- strsplit(outputFile, "[_ ]+")
  outputFile <- paste("avgs_", str[[1]][2], "_", str[[1]][3], ".csv", sep = '')
  outputPath <- file.path(outputDir, outputFile)
  
  #form a table from the results and output to the new file
  labels <- c("avgSlope", "avgR2", "bestSlope", "bestR2")
  results <- c(mean(avgSlopeVals), mean(avgR2Vals), mean(bestSlopeVals), mean(bestR2Vals))
  table <- matrix(results, ncol = length(results), byrow = T)
  colnames(table) <- labels
  table <- as.table(table)
  write.table(table, outputPath, sep = ",", col.names = T, row.names = F, append = T)
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
batchedFiles <- BatchFiles(args, 20)
dirName <- "avgs"
dir.create(dirName, showWarnings = F)
for (col in 1:ncol(batchedFiles)) {
  FindAvgs(batchedFiles[ , col], dirName)
}