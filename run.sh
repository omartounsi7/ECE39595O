#!/bin/bash

mkdir build

g++ -o build/parser src/parser.cpp

if [ $? -eq 0 ]; then
  echo -e "parser.cpp compiled successfully\n"
else
  echo -e "Error: Compilation of parser.cpp failed\n"
fi

g++ -o build/vm src/vm.cpp

if [ $? -eq 0 ]; then
  echo -e "vm.cpp compiled successfully\n"
else
  echo -e "Error: Compilation of vm.cpp failed\n"
fi

input_dir="testcases/parserInputs"
output_dir="testcases/parserOutputs"
expected_output_dir="testcases/parserExpectedOutputs"
tests=0
successful_tests=0

mkdir "$output_dir"

for input_file in "$input_dir"/*; do
  if [ -f "$input_file" ]; then
    ((tests++))
    echo -e "Running test $input_file"
    output_file="$output_dir/$(basename "$input_file").pout"
    touch "$output_file"
    build/parser "$input_file" > "$output_file"
    expected_output_file="$expected_output_dir/$(basename "$input_file").pout"
    exit_code=$?
    if [ $exit_code -eq 0 ] && diff -w -q "$output_file" "$expected_output_file" >/dev/null; then
      echo -e "Test $input_file successful.\n"
      ((successful_tests++))
    else
      echo -e "Test $input_file failed.\n"
    fi
  fi
done

echo "$successful_tests out of $tests tests passed."

read -p "Press Enter to exit..."
