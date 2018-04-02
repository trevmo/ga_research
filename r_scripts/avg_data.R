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
GetAvgs <- function(batch, numGenerations, outputDir) {
  # Calculate the average results from a batch of csv files.
  #
  # Arg:
  #   batch: vector of filenames/paths
  #   numGenerations: number of rows of data per file
  #   outputDir: name of the directory to place the output file
  #
  # Returns:
  #   void (outputs results to a new file)
  
  firstFile <- read.csv(batch[1], skip = 13)
  labels <- colnames(firstFile)
  avgMatrix <- matrix(0, nrow = numGenerations, ncol = ncol(firstFile))
  
  for (file in batch) {
    dat <- read.csv(file, skip = 14)
    
    for (r in 1:nrow(dat)) {
      for (c in 1:ncol(dat)) {
        avgMatrix[r, c] <- avgMatrix[r, c] + dat[r, c]
      }
    }
  }
  
  avgMatrix <- avgMatrix / length(batch)
  
  #form the filename by splitting out the attack type and range from
  #the first file in the batch
  outputFile <- basename(batch[[1]])
  str <- strsplit(outputFile, "[_ ]+")
  if (nchar(str[[1]][2]) == 1)
    suffix <- paste("0", str[[1]][2], sep = '')
  else
    suffix <- str[[1]][2]
  outputFile <- paste("avgs_", str[[1]][1], "_", suffix, ".csv", sep = '')
  outputPath <- file.path(outputDir, outputFile)
  
  #form a table from the results and output to the new file
  table <- as.table(avgMatrix)
  colnames(table) <- labels
  table <- as.table(table)
  write.table(table, outputPath, sep = ",", col.names = T, row.names = F, append = T)
}

args = commandArgs(trailingOnly=TRUE)
if (length(args) < 1) {
  stop("You must specify csv file(s) on the command line.n")
}
numGens <- strtoi(args[1])
batchSize <- strtoi(args[2])
batchedFiles <- BatchFiles(tail(args, length(args)-2), batchSize)
dirName <- "avg_data"
dir.create(dirName, showWarnings = F)
for (col in 1:ncol(batchedFiles)) {
  GetAvgs(batchedFiles[ , col], numGens, dirName)
}