# This is a simple script that creates a backup file
# for a file that the user enters 
# This was created as part of an Operating Systems class


#!/bin/bash

# Here teh user inputs the directory
read -rp "Enter the full path of the directory to back up: " source_dir

# Checking if the directory exists
if [ ! -d "$source_dir" ]; then
    echo "Directory $source_dir does not exist"
    exit 1
fi

# Creating a backup file if it doesn't exit
backup_dir="$HOME/backups"
mkdir -p "$backup_dir"


timestamp=$(date +"%Y%m%d_%H%M%S") 
#Creating the timestamp e.g. yyyymmdd_hhmmss
dir_name=$(basename "$source_dir") 
# This saves the name of the source on dir_name
backup_filename="backup_${dir_name}_${timestamp}.tar.gz"
# Creating the backup file name using the d=original file's name and the timestamp
backup_path="${backup_dir}/${backup_filename}" 
#creating the full path


tar -czf "$backup_path" -C "$(dirname "$source_dir")" "$dir_name" 
#czf = Create Zip File 
# -C change the parent directory of source_dir, so tar saves only the folder

# Checking if the previous statement was successful
if [ $? -eq 0 ]; then
    echo "Backup created!! "
else
    echo "Backup failed."
    exit 2
fi

# finds all the files this files name using their parent directories
#if the files are older than 6 days then it deletes them
find "$backup_dir" -name "backup_${dir_name}_*.tar.gz" -type f -mtime +6 -exec rm {} \;

echo "Old Backups Deleted"

exit 0

