# Developed By Kordell Hutchins
#!/bin/bash
if [[ -z $1 ]]; then
    echo "Syntax ./junkmybinary.sh [binary] [text-file]"
    echo "Place the textfile in the filler directory"
elif [[ -z $2 ]]; then
    echo "Syntax ./junkmybinary.sh [binary] [text-file]"
    echo "Place the textfile in the filler directory"
else
    input="/root/hid/filler/${2}"
    while IFS= read -r line
    do
        echo "$line" >> ./$1
    done < "$input"
fi
