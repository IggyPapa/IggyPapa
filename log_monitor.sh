#!/bin/bash

read -p "Enter the full path of the log file to monitor (e.g., /var/log/syslog): " log_file
#User inputs the full path of the log file

#Checking if the file is accessible
if [ ! -e "$log_file" ]; then
    echo "Error: File '$log_file' does not exist."
    exit 1
elif [ ! -r "$log_file" ]; then
    echo "Error: File exists but is not readable. Try 'sudo'."
    exit 1
fi

read -p "Enter keywords to search for (e.g. error, fail, warning): " -a keywords
#User Inputs Keywords 

#Checking if the user input was a Keyward
if [ ${#keywords[@]} -eq 0 ]; then
    echo "No keywords provided. Exiting."
    exit 2
fi

#Creates a patern with the keywors the user inputed
pattern=$(IFS='|'; echo "${keywords[*]}")

#Saving the keywords that were matched
matches=$(grep -iE "$pattern" "$log_file")

if [ -z "$matches" ]; then
    echo "No matching entries found for keywords: ${keywords[*]}"
    echo "No report file was created."
    exit 0
fi

#Outputs the lines in the logfile that have the keywords that were given
echo -e "\nMatching lines found:"
echo "$matches"

log_name=$(basename "$log_file")
current_date=$(date +%Y%m%d)
report_file="$HOME/important_${log_name}_${current_date}.log"

echo "$matches" > "$report_file"

echo "Matches saved at: $report_file"


