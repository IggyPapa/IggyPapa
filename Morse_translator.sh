#!/bin/bash

# the translations are done according to the table given to us 
# the .txt file Mosre_Text contains a correct version of the morse Translation of MORSE CODE due to a typo in the example given to us

encode() {
    filename="$1" # assigns the first command-line argument ($1) to the variable filename
    content=$(<"$filename") # assigns the content of filename to the variable content.
    encoded="" # initializing an empty string named encoded

    for ((i = 0; i < ${#content}; i++)); do # the code (${#content} returns the length of a string
        char="${content:i:1}" # assigns the value of a single character from the variable content to the variable char
        case $char in  
        # case statement, checking every letter until we find the current letter
        # once we find the current letter we add it in morse to the encoded variable
            'A') encoded+=".-" ;;
            'B') encoded+="-..." ;;
            'C') encoded+="-.-." ;;
            'D') encoded+="-.." ;;
            'E') encoded+="." ;;
            'F') encoded+="..-." ;;
            'G') encoded+="--." ;;
            'H') encoded+="...." ;;
            'I') encoded+=".." ;;
            'J') encoded+=".---" ;;
            'K') encoded+="-.-" ;;
            'L') encoded+=".-.." ;;
            'M') encoded+="--" ;;
            'N') encoded+="-." ;;
            'O') encoded+="---" ;;
            'P') encoded+=".--." ;;
            'Q') encoded+="--.-" ;;
            'R') encoded+=".-." ;;
            'S') encoded+="..." ;;
            'T') encoded+="-" ;;
            'U') encoded+="..-" ;;
            'V') encoded+="...-" ;;
            'W') encoded+=".--" ;;
            'X') encoded+="-..-" ;;
            'Y') encoded+=" -.--" ;;
            'Z') encoded+="--.." ;;
            '0') encoded+="-----" ;;
            '1') encoded+=".----" ;;
            '2') encoded+="..---" ;;
            '3') encoded+="...--" ;;
            '4') encoded+="....-" ;;
            '5') encoded+="....." ;;
            '6') encoded+="-...." ;;
            '7') encoded+="--..." ;;
            '8') encoded+="---.." ;;
            '9') encoded+="----." ;;
            ' ') encoded+="\t" ;;  # '\t' for space
            *) encoded+="$char" ;; # default case
        esac # end of the case statement
    done # end of the for loop

    echo "$encoded" #sending the encripted string to the main function
}

decode() {
    filename="$1" # assigns the first command-line argument ($1) to the variable filename
    content=$(<"$filename") # assigns the content of filename to the variable content.
    decoded="" # initializing an empty string named decoded

    IFS=' ' read -ra symbols <<< "$content" 
    # splits a string into blocks/ segments using space ' ' as a paramiter to locate where a morse character ends
    for ((i = 0; i < ${#symbols[@]}; i++)); do # the code (${#content} returns the length of a string
        symbol="${symbols[i]}" # retrieves the value of the element at index i
        case $symbol in
        # case statement, checking every letter until we find the current letter
        # once we find the current letter we add it in morse to the encoded variable
            '.-') decoded+='A' ;;
            '-...') decoded+='B' ;;
            '-.-.') decoded+='C' ;;
            '-..') decoded+='D' ;;
            '.') decoded+='E' ;;
            '..-.') decoded+='F' ;;
            '--.') decoded+='G' ;;
            '....') decoded+='H' ;;
            '..') decoded+='I' ;;
            '.---') decoded+='J' ;;
            '-.-') decoded+='K' ;;
            '.-..') decoded+='L' ;;
            '--') decoded+='M' ;;
            '-.') decoded+='N' ;;
            '---') decoded+='O' ;;
            '.--.') decoded+='P' ;;
            '--.-') decoded+='Q' ;;
            '.-.') decoded+='R' ;;
            '...') decoded+='S' ;;
            '-') decoded+='T' ;;
            '..-') decoded+='U' ;;
            '...-') decoded+='V' ;;
            '.--') decoded+='W' ;;
            '-..-') decoded+='X' ;;
            '-.--') decoded+='Y' ;;
            '--..') decoded+='Z' ;;
            '-----') decoded+='0' ;;
            '.----') decoded+='1' ;;
            '..---') decoded+='2' ;;
            '...--') decoded+='3' ;;
            '....-') decoded+='4' ;;
            '.....') decoded+='5' ;;
            '-....') decoded+='6' ;;
            '--...') decoded+='7' ;;
            '---..') decoded+='8' ;;
            '----.') decoded+='9' ;;

            '\t') decoded+=' ' ;; 
            *) decoded+="$symbol" ;; # default case
        esac # end of the case statement
    done # end of the for loop

    echo "$decoded" # sending the plaintext string to the main function
}

# Main function
# checking if the user asked for encription or decription
if [ "$1" == "-e" ]; then # if the user wants to turn plaintext into enctipted 
    filename="Text.txt" # filename is set to the content of the file Text.txt
    result=$(encode "$filename") # calls the encode function with the filename as a paramiter 
    echo "$result"
elif [ "$1" == "-d" ]; then # if the user wants to turn encripted into plaintext
    filename="Morse_Text.txt" # filename is set to the content of the file Morse_Text.txt
    result=$(decode "$filename") # calls the decode function with the filename as a paramiter
    echo "$result"
else
    echo "Not an option!"
fi
