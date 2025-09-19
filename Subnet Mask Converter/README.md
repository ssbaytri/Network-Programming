# Subnet Converter

A lightweight, efficient command-line utility for converting between subnet masks and CIDR notation. Built in C for optimal performance and reliability.

## 🚀 Features

- **Bidirectional Conversion**: Convert subnet masks to CIDR notation and vice versa
- **Input Validation**: Robust validation for both subnet masks and CIDR values
- **Error Handling**: Clear error messages for invalid inputs
- **Fast Performance**: Written in C for maximum efficiency
- **Zero Dependencies**: Standalone binary with no external dependencies

## 📋 Requirements

- GCC compiler
- Make utility
- Standard C library

## 🔧 Installation

1. **Clone or download the project files**
2. **Compile using Make:**
   ```bash
   make
   ```
3. **The executable `subnet_converter` will be created in the project directory**

### Manual Compilation
If you prefer to compile manually:
```bash
gcc -Wall -Wextra -Werror -o subnet_converter main.c src.c
```

## 📖 Usage

### Convert Subnet Mask to CIDR
```bash
./subnet_converter -c <subnet_mask>
```

**Examples:**
```bash
./subnet_converter -c 255.255.255.0    # Output: CIDR notation: /24
./subnet_converter -c 255.255.0.0      # Output: CIDR notation: /16
./subnet_converter -c 255.255.255.192  # Output: CIDR notation: /26
```

### Convert CIDR to Subnet Mask
```bash
./subnet_converter -i <cidr_value>
```

**Examples:**
```bash
./subnet_converter -i 24    # Output: Subnet mask: 255.255.255.0
./subnet_converter -i 16    # Output: Subnet mask: 255.255.0.0
./subnet_converter -i 8     # Output: Subnet mask: 255.0.0.0
```

### Help
```bash
./subnet_converter -h
# or
./subnet_converter --help
```

## 🔍 Input Validation

The program includes comprehensive input validation:

### Subnet Mask Validation
- Must be in dotted decimal notation (e.g., `255.255.255.0`)
- Each octet must be between 0 and 255
- Must represent a valid subnet mask (contiguous 1s followed by contiguous 0s)
- Only numeric characters and dots are allowed

### CIDR Validation
- Must be a numeric value between 0 and 32
- Only numeric characters are allowed
- No leading zeros or special characters

## 🛠️ Build Commands

| Command | Description |
|---------|-------------|
| `make` or `make all` | Compile the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and executable |
| `make re` | Clean and rebuild the project |

## 📁 Project Structure

```
subnet_converter/
├── main.c          # Main program entry point and argument parsing
├── main.h          # Header file with function declarations
├── src.c           # Core conversion functions and validation
├── Makefile        # Build configuration
└── README.md       # This file
```

## 🔧 Function Overview

### Core Functions
- `mask_to_cidr()` - Converts subnet mask to CIDR notation
- `cidr_to_mask()` - Converts CIDR notation to subnet mask
- `validate_mask()` - Validates subnet mask format and values
- `validate_cidr()` - Validates CIDR notation
- `print_help()` - Displays usage information

## ⚠️ Error Handling

The program provides clear error messages for common issues:

- **Invalid subnet mask format**: "Invalid subnet mask: [input]"
- **Invalid CIDR value**: "Invalid CIDR: [input]"
- **Incorrect usage**: Displays help message automatically

Exit codes:
- `0` - Success
- `1` - Error (invalid input or incorrect usage)

## 🌐 Common Subnet Reference

| CIDR | Subnet Mask | Hosts |
|------|-------------|-------|
| /8   | 255.0.0.0   | 16,777,214 |
| /16  | 255.255.0.0 | 65,534 |
| /24  | 255.255.255.0 | 254 |
| /25  | 255.255.255.128 | 126 |
| /26  | 255.255.255.192 | 62 |
| /27  | 255.255.255.224 | 30 |
| /28  | 255.255.255.240 | 14 |
| /29  | 255.255.255.248 | 6 |
| /30  | 255.255.255.252 | 2 |

## 📝 Examples

### Valid Conversions
```bash
# Subnet mask to CIDR
./subnet_converter -c 255.255.255.0     # /24
./subnet_converter -c 255.255.248.0     # /21
./subnet_converter -c 255.255.255.240   # /28

# CIDR to subnet mask
./subnet_converter -i 24                # 255.255.255.0
./subnet_converter -i 21                # 255.255.248.0
./subnet_converter -i 28                # 255.255.255.240
```

### Invalid Inputs
```bash
./subnet_converter -c 256.255.255.0     # Invalid: octet > 255
./subnet_converter -c 255.255.128.255   # Invalid: non-contiguous mask
./subnet_converter -i 33                # Invalid: CIDR > 32
./subnet_converter -i abc               # Invalid: non-numeric CIDR
```

## 🤝 Contributing

Contributions are welcome! Please ensure your code:
- Follows the existing code style
- Includes proper error handling
- Passes all existing functionality tests
- Compiles without warnings using the provided Makefile

## 📄 License

This project is open source. Feel free to use, modify, and distribute as needed.

---

*Built with ❤️ in C for network administrators and developers*
