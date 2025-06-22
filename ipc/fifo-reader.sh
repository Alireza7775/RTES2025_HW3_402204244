#!/bin/bash

# Configuration
FIFO_PATH="/tmp/myfifo"

# Create the FIFO if it doesn't exist
if [[ ! -p "$FIFO_PATH" ]]; then
    mkfifo "$FIFO_PATH"
fi

# Read from FIFO and display input
echo "Waiting for messages..."
while read -r line < "$FIFO_PATH"; do
    echo "Received: $line"
done
