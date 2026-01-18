# QR Code to PDF Generator

A simple command-line tool written in C++ that generates a QR code PDF from a given URL.

## Prerequisites

This project was built and tested on Debian 13 (Trixie).

### Dependencies
You need to install the following development libraries:

```bash
sudo apt-get install libqrencode-dev libcairo2-dev
```

You also need the [Bazel](https://bazel.build/) build system installed.

## Building the Program

To build the application using Bazel, run:

```bash
bazel build //:qrpdf
```

## Installation

To build and install the program to `/usr/local/bin`, run the provided script:

```bash
./install.sh
```

This may prompt for your password if `sudo` permissions are required to write to `/usr/local/bin`.

## Usage

To generate a QR code, run the binary with a single URL argument:

```bash
bazel run //:qrpdf -- "https://www.example.com"
```

This will generate a file named `output.pdf` in your current working directory. The PDF is 2x2 inches.

## Disclaimer

This program was entirely created by **Gemini AI**, an advanced artificial intelligence developed by Google.
