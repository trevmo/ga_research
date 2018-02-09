#!/usr/bin/Rscript

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
  names <- c()
  fileNum <- 1
  for (file in batch) {
    dat <- read.csv(file, skip = 13)
    
    for (row in 1:nrow(dat)) {
      if (fileNum == 1) {
        names <- c(names, row.names(dat)[row])
        if (row == 1) {
          slopes <- vector(mode = "double", length = nrow(dat))
          r2s <- vector(mode = "double", length = nrow(dat))
        }
      }
      for (name in names(dat)) {
        if (name == "slope") {
          slopes[row] <- slopes[row] + dat[row, name]
        }
        else {
          r2s[row] <- r2s[row] + dat[row, name]
        }
      }
    }
    fileNum <- fileNum + 1
  }
  # 
  #form the filename by splitting out the attack type and range from
  #the first file in the batch
  outputFile <- basename(batch[[1]])
  str <- strsplit(outputFile, "[_ ]+")
  if (nchar(str[[1]][3]) == 1)
    suffix <- paste("0", str[[1]][3], sep = '')
  else
    suffix <- str[[1]][3]
  outputFile <- paste("avgs_", str[[1]][2], "_", suffix, ".csv", sep = '')
  outputPath <- file.path(outputDir, outputFile)
  # 
  # #form a data frame from the results and output to the new file
  slopes <- slopes / (fileNum - 1)
  r2s <- r2s / (fileNum - 1)
  df <- data.frame(slopes, r2s)
  rownames(df) <- names
  write.table(df, outputPath, sep = ",", col.names = T, row.names = T, append = T)
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