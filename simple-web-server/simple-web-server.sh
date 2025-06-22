#!/bin/bash

PORT=80

while true; do
  # Wait for an incoming connection and handle it
  echo "[+] Received connection at $(date)"
  echo -e "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n$(date)" | nc -l -p $PORT -q 1
done

