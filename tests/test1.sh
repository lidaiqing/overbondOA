#!/bin/bash
DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PARENT_DIR="$(dirname "$DIR")"
echo "Generating outcome to out1.csv"
$PARENT_DIR/Solution1 "$DIR/sample_input.csv" "$DIR/out1.csv"

echo "Comparing outcome with sample_output1.csv"
python $DIR/test1.py
