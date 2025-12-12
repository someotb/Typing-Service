#!/bin/bash

echo "Installing dependencies for typing_service..."

sudo apt update

sudo apt install -y \
    build-essential \
    cmake \
    wget \
    g++ \
    python3 \
    python3-pip

echo "Installing nlohmann/json..."
sudo apt install -y nlohmann-json3-dev


echo "Dependencies installed successfully!"
