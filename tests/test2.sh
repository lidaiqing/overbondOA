#!/bin/bash
DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PARENT_DIR="$(dirname "$DIR")"
echo "Generating outcome to out2.csv"
$PARENT_DIR/Solution2 "$DIR/sample_input.csv" "$DIR/out2.csv"

echo "Comparing outcome with sample_output2.csv"
python $DIR/test2.py

