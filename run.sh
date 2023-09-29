#!/bin/bash

g++ -o build/parser src/parser.cpp

if [ $? -eq 0 ]; then
  echo "parser.cpp compiled successfully"
else
  echo "Error: Compilation of parser.cpp failed"
fi

g++ -o build/vm src/vm.cpp

if [ $? -eq 0 ]; then
  echo "vm.cpp compiled successfully"
else
  echo "Error: Compilation of vm.cpp failed"
fi

input_dir="testcases/parserInputs"
output_dir="testcases/parserOutputs"
expected_output_dir="testcases/parserExpectedOutputs"

for input_file in "$input_dir"/*; do
  if [ -f "$input_file" ]; then
    echo "Running test $input_file"
    output_file="$output_dir/$(basename "$input_file").pout"
    build/parser < "$input_file" > "$output_file"
  fi
done

read -p "Press Enter to exit..."