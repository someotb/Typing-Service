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

echo "Installing libcpp-httplib-dev..."
sudo apt install -y libcpp-httplib-dev

echo "Dependencies installed successfully!"
