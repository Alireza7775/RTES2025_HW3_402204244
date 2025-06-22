#!/bin/bash

# Configuration
FIFO_PATH="/tmp/myfifo"

# Create the FIFO if it doesn't exist
if [[ ! -p "$FIFO_PATH" ]]; then
    mkfifo "$FIFO_PATH"
fi

# Read from terminal and send input to FIFO
echo "Type messages to send (Ctrl+C to exit):"
while read -r line; do
    echo "$line" > "$FIFO_PATH"
done
