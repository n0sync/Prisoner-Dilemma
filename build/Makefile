CC=gcc
CFLAGS=`pkg-config --cflags gtk+-3.0`
LIBS=`pkg-config --libs gtk+-3.0`

# Default target
all: main

# Build the application
main: ../src/main.c
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

# Install dependencies for different systems
install-deps:
	@echo "Installing dependencies..."
	@if command -v apt >/dev/null 2>&1; then \
		echo "Detected Debian/Ubuntu/Kali - using apt"; \
		sudo apt update && sudo apt install -y build-essential libgtk-3-dev pkg-config; \
	elif command -v dnf >/dev/null 2>&1; then \
		echo "Detected Fedora - using dnf"; \
		sudo dnf install -y gcc gtk3-devel pkgconfig make; \
	elif command -v yum >/dev/null 2>&1; then \
		echo "Detected CentOS/RHEL - using yum"; \
		sudo yum install -y gcc gtk3-devel pkgconfig make; \
	elif command -v pacman >/dev/null 2>&1; then \
		echo "Detected Arch Linux - using pacman"; \
		sudo pacman -S --needed base-devel gtk3 pkgconf; \
	elif command -v brew >/dev/null 2>&1; then \
		echo "Detected macOS - using Homebrew"; \
		brew install gtk+3 pkg-config; \
	else \
		echo "Unknown package manager. Please install manually:"; \
		echo "- GCC compiler"; \
		echo "- GTK+ 3.0 development libraries"; \
		echo "- pkg-config"; \
		echo ""; \
		echo "For Debian/Ubuntu/Kali: sudo apt install build-essential libgtk-3-dev pkg-config"; \
		echo "For Fedora: sudo dnf install gcc gtk3-devel pkgconfig"; \
		echo "For CentOS/RHEL: sudo yum install gcc gtk3-devel pkgconfig"; \
		echo "For Arch: sudo pacman -S base-devel gtk3 pkgconf"; \
		echo "For macOS: brew install gtk+3 pkg-config"; \
	fi

# Check if dependencies are installed
check-deps:
	@echo "Checking dependencies..."
	@command -v gcc >/dev/null 2>&1 || { echo "ERROR: GCC not found"; exit 1; }
	@command -v pkg-config >/dev/null 2>&1 || { echo "ERROR: pkg-config not found"; exit 1; }
	@pkg-config --exists gtk+-3.0 || { echo "ERROR: GTK+ 3.0 development libraries not found"; exit 1; }
	@echo "All dependencies are installed!"

# Setup: install dependencies and build
setup: install-deps main
	@echo "Setup complete! Run ./main to start the game."

# Clean build artifacts
clean:
	rm -f main

# Run the application
run: main
	./main

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build the application (default)"
	@echo "  install-deps - Install system dependencies"
	@echo "  check-deps   - Check if dependencies are installed"
	@echo "  setup        - Install dependencies and build"
	@echo "  clean        - Remove build artifacts"
	@echo "  run          - Build and run the application"
	@echo "  help         - Show this help message"

.PHONY: all install-deps check-deps setup clean run help