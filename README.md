# Prisoner's Dilemma GTK+

A graphical implementation of the classic Prisoner's Dilemma game theory experiment using GTK3.

## Game Rules

- **Both Cooperate**: 3 points each
- **Both Defect**: 1 point each  
- **One Cooperates, One Defects**: Defector gets 5 points, Cooperator gets 0 points

## Project Structure

```
prisoners-dilemma-gtk/
├── src/
│   ├── include.h              # Header file
│   └── main.c
├── build/
│   └── Makefile              # Build configuration
└── README.md                 
```

## Installation & Build

### Install Dependencies

**Ubuntu/Debian/Kali:**
```bash
sudo apt update
sudo apt install build-essential libgtk-3-dev pkg-config
```

**Fedora:**
```bash
sudo dnf install gcc gtk3-devel pkgconfig
```

**Arch Linux:**
```bash
sudo pacman -S base-devel gtk3 pkgconf
```

### Build & Run

```bash
cd build
make all
./main
```

## How to Play

1. Set number of rounds (1-20)
2. Click "Start Game"
3. Each player chooses "Cooperate" or "Defect"
4. View round results and continue
5. Winner announced after all rounds

## Makefile Commands

```bash
make all         # Build the application
make install-deps # Install dependencies automatically
make setup       # Install deps + build
make run         # Build and run
make clean       # Remove executable
make help        # Show all commands
```
