#!/bin/bash

# Relative path to script dir
dirPath=$(dirname "$0")

# Enable logging thanks https://serverfault.com/questions/103501/how-can-i-fully-log-all-bash-scripts-actions
exec 3>&1 4>&2
trap 'exec 2>&4 1>&3' 0 1 2 3
exec 1>"$dirPath/StopLatest.log" 2>&1

echo "Starting script at $(date +"%Y.%m_%a-%H-%M:%S")"

stopped=false
toStopArr=()

while read -r i; do
    # Skip empty line
    [[ -z "$i" ]] && continue

    infoArr=($i)
    toStopArr+=(${infoArr[1]})

    if ! screen -ls | grep -q "\.${infoArr[1]}[[:space:]]"; then
        echo "Could not find screen session for '${infoArr[1]}'"
        echo "Skipping"
        continue
    fi

    echo "Sending stop command to screen session '${infoArr[1]}'"
    screen -S "${infoArr[1]}" -X stuff $'\003'
    stopped=true # Attempted to stop at least 1 session
done < "$dirPath/EnabledServers"

if ! $stopped; then
    echo "Nothing to stop!"
    exit 0
fi

sleep 2

sessionUp=true
while $sessionUp; do
    sessionUp=false

    for sessName in "${toStopArr[@]}"; do
	if screen -ls | grep -q "\.$sessName[[:space:]]"; then
	    echo "Session '$sessName' still up, waiting"
	    sessionUp=true
	fi
    done

    sleep 2
done

echo "Every server session terminated!"
