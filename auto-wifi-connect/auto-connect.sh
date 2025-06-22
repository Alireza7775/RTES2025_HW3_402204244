#!/bin/bash

# Configuration
SSID="Alireza"
WIFI_PASSWORD="12345678"
INTERFACE="wlan0"
LOGFILE="/home/alireza/RTES2025_HW3/auto-wifi-connect/auto-connect.log"

# Timestamp
echo "[$(date)] Checking connection..." >> "$LOGFILE"

# Check if connected to a network
if ! nmcli -t -f WIFI g | grep -q "enabled"; then
    echo "[$(date)] Wi-Fi is disabled. Enabling Wi-Fi..." >> "$LOGFILE"
    nmcli radio wifi on
    sleep 2
fi

if ! nmcli -t -f ACTIVE,SSID dev wifi | grep -q "^yes"; then
    echo "[$(date)] Not connected to any network. Trying to connect to $SSID..." >> "$LOGFILE"

    # Check if connection profile exists
    if ! nmcli con show "$SSID" &>/dev/null; then
        echo "[$(date)] Creating connection profile for $SSID..." >> "$LOGFILE"
        nmcli dev wifi connect "$SSID" password "$WIFI_PASSWORD" ifname "$INTERFACE" >> "$LOGFILE" 2>&1
    else
        nmcli con up id "$SSID" ifname "$INTERFACE" >> "$LOGFILE" 2>&1
    fi

    sleep 5
    if nmcli -t -f ACTIVE,SSID dev wifi | grep -q "^yes:$SSID"; then
        echo "[$(date)] Successfully connected to $SSID." >> "$LOGFILE"
    else
        echo "[$(date)] Failed to connect to $SSID." >> "$LOGFILE"
    fi
else
    echo "[$(date)] Already connected to a network." >> "$LOGFILE"
fi
echo "[$(date)]"
nmcli -t -f ACTIVE,SSID dev wifi >> "$LOGFILE"
