#!/usr/bin/env Rscript


# This script is used for formatting ggplots. It can be sourced in other R scripts via:
# source("format_plot.R")
#
# @author trevmo

require(ggplot2)

FormatPlot <- function(plot) {
  # Add formatting to a ggplot.
  #
  # Arg:
  #   plot: ggplot
  #
  # Returns:
  #   formatted plot
  axis.font <- 20 #16
  secondary.font <- axis.font - 6
  title.margin <- margin(t = 10, r = 0, b = 14, l = 0, unit = "pt")
  
  return(plot +
    scale_color_grey(start = 0.2, end = 0.8) +
    theme_bw() +
    theme(axis.title = element_text(size = axis.font)) +
    theme(axis.text = element_text(size = secondary.font)) +
    theme(legend.position = c(0.12,0.9)) +
    theme(legend.background = element_rect(colour = 'black', fill = 'white', linetype='solid', size = 1.0)) +
    theme(legend.text = element_text(size = secondary.font)) +
    theme(legend.title = element_text(size = secondary.font)))
}