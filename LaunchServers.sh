#!/bin/bash

# Relative path to script dir
dirPath=$(dirname "$0")

# Enable logging thanks https://serverfault.com/questions/103501/how-can-i-fully-log-all-bash-scripts-actions
exec 3>&1 4>&2
trap 'exec 2>&4 1>&3' 0 1 2 3
exec 1>"$dirPath/StartLatest.log" 2>&1

echo "Starting script at $(date +"%Y.%m_%a-%H-%M:%S")"

cat "$dirPath/EnabledServers" | while read i; do
    infoArr=($i)
    path="$dirPath/${infoArr[0]}"

    if [ ! -f "$path" ]; then
        echo "Could not find server launch file '$path'"
        echo "Skipping"
        continue
    fi

    # Redirect stdout/stderr to logfile
    echo "Starting '${infoArr[1]}' server with path '$path'"
    screen -dmS "${infoArr[1]}" "$path"
done


# Stop running processes with simulated strg+c
# screen -S "Satisfactory" -X stuff $'\003' # $'\003' == str+c
# screen -S "Satisfactory" -X stuff "quit\n" # generic command (eg. for minecraft server console

# screen -S "Satisfactory" -X quit # Force kill screen session
