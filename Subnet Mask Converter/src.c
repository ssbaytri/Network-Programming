#include "main.h"

void print_help(void)
{
	printf("Usage:\n");
	printf("  subnet_converter -c <subnet mask>   # Convert subnet mask to CIDR notation\n");
	printf("  subnet_converter -i <CIDR>          # Convert CIDR to subnet mask\n");
	printf("  subnet_converter -h | --help        # Show this help message\n");
}