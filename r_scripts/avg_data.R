#!/usr/bin/env Rscript


# This script is used to average data collected in csv files. The expected format
# of the files is:
#     Lines 1-14: header info
#     Lines 15+: three columns of csv data
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
GetAvgs <- function(batch, outputDir) {
  # Calculate the average results from a batch of csv files.
  #
  # Arg:
  #   batch: vector of filenames/paths
  #   outputDir: name of the directory to place the output file
  #
  # Returns:
  #   void (outputs results to a new file)
  
  avgGen <- rep(0,100)
  avgAvg <- rep(0,100)
  avgBest <- rep(0,100)
  for (file in batch) {
    dat <- read.csv(file, skip = 14)
    
    for (r in 1:nrow(dat)) {
      avgGen[r] <- avgGen[r] + dat[r, 1] 
      avgAvg[r] <- avgAvg[r] + dat[r, 2]
      avgBest[r] <- avgBest[r] + dat[r, 3]
    }
  }
  
  avgGen <- avgGen / length(batch)
  avgAvg <- avgAvg / length(batch)
  avgBest <- avgBest / length(batch)
  
  #form the filename by splitting out the attack type and range from
  #the first file in the batch
  outputFile <- basename(batch[[1]])
  str <- strsplit(outputFile, "[_ ]+")
  outputFile <- paste("avgs_", str[[1]][1], "_", str[[1]][[2]], ".csv", sep = '')
  outputPath <- file.path(outputDir, outputFile)
  
  #form a table from the results and output to the new file
  labels <- c("Generation", "Average Fitness", "Best Fitness")
  table <- cbind(avgGen, avgAvg, avgBest)
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
  GetAvgs(batchedFiles[ , col], dirName)
}