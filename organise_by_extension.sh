#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Correct way to run the program is ./organise_by_extension.sh /path/to/the/catalog "
	exit 1
fi

path="$1"

if [ ! -d "$path" ]; then
	echo "Error: Path does not exist"
	exit 1
fi

cd "$path"

for file in "$path"/*; do
	if [ ! -f "$file"  ]; then
		continue
	fi

	filename=$(basename "$file")
	
	if [[ "$filename" == *.* && "$filename" != .* ]]; then
    		extension="${filename##*.}"
	else
    		extension="no_extension"
	fi

	destination="${path}/${extension}"
	if [ ! -d "$destination"  ]; then
		mkdir -pv "${destination}"
	fi

	echo "Moving $filename to $destination"
	mv "$file" "$destination/"
	

done

echo "Files have been organised "
