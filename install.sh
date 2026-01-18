#!/bin/bash
set -e

echo "Cleaning previous build..."
bazel clean

echo "Building qrpdf..."
bazel build //:qrpdf

if [ -f bazel-bin/qrpdf ]; then
    echo "Installing qrpdf to /usr/local/bin..."
    # Check if we have write access to /usr/local/bin, otherwise use sudo
    if [ -w /usr/local/bin ]; then
        cp bazel-bin/qrpdf /usr/local/bin/qrpdf
        chmod +x /usr/local/bin/qrpdf
    else
        echo "Requesting sudo permissions to install..."
        sudo cp bazel-bin/qrpdf /usr/local/bin/qrpdf
        sudo chmod +x /usr/local/bin/qrpdf
    fi
    echo "Installation successful!"
else
    echo "Build failed: binary not found."
    exit 1
fi
