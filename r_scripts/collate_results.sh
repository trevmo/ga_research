#!/bin/bash

###############################################################################
# This script is used for sequentially calling R scripts on batches of data. The
# end result is a csv file with a table representing the average slopes of the
# increase in fitness per damage range/mutation range combo.
#
# @author trevmo
###############################################################################

# specify full paths for ease of use
R_SCRIPTS_DIR=$1
DATA_DIR=$2

data_dirs=$(ls $DATA_DIR)
for dir in $data_dirs; do
   cd $dir
   $R_SCRIPTS_DIR/linear_approx.R $(ls *.csv)
   $R_SCRIPTS_DIR/avg_stats.R $(ls stats/*.csv)
   cd ..
done
$R_SCRIPTS_DIR/form_table.R $DATA_DIR mutate 2