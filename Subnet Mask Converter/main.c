#include "main.h"

int main(int argc, char *argv[])
{
	if (argc == 2 &&(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
	{
		print_help();
		return 0;
	}

	if (argc != 3)
	{
		print_help();
		return 1;
	}

	if (!strcmp(argv[1], "-c"))
	{
		int cidr = mask_to_cidr(argv[2]);
		if (cidr == -1)
		{
			printf("Invalid subnet mask: %s\n", argv[2]);
        	return (1);
		}
		printf("CIDR notation: /%d\n", cidr);
    	return (0);
	}

	if (!strcmp(argv[1], "-i"))
	{
		int octets[4];
		if (cidr_to_mask(argv[2], octets) == -1)
		{
			printf("Invalid CIDR: %s\n", argv[2]);
			return (1);
		}
		printf("Subnet mask: %d.%d.%d.%d\n", octets[0], octets[1], octets[2], octets[3]);
    	return (0);
	}

	return 0;
}
