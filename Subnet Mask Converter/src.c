#include "main.h"

void print_help(void)
{
	printf("Usage:\n");
	printf("  subnet_converter -c <subnet mask>   # Convert subnet mask to CIDR notation\n");
	printf("  subnet_converter -i <CIDR>          # Convert CIDR to subnet mask\n");
	printf("  subnet_converter -h | --help        # Show this help message\n");
}

static int validate_mask(const char *mask, int octets[4])
{
	char buf[32];
	strncpy(buf, mask, sizeof(buf));
	buf[sizeof(buf) - 1] = '\0';

	char *token = strtok(buf, ".");
	int count = 0;

	while (token)
	{
		for (int i = 0; token[i]; i++)
		{
			if (!isdigit((unsigned char)token[i]))
				return (-1);
		}
		int val = atoi(token);
		if (val < 0 || val > 255)
			return (-1);

		octets[count++] = val;
		token = strtok(NULL, ".");
	}
	return (count == 4) ? 0 : -1;
}

int mask_to_cidr(const char *mask)
{
	int octets[4];
	if (validate_mask(mask, octets) == -1)
		return (-1);

	int cidr = 0;
	int found_zero = 0;


	for (int i = 0; i < 4; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			int bit = (octets[i] >> j) & 1;
			if (bit)
			{
				if (found_zero)
					return (-1);
				cidr++;
			}
			else
				found_zero = 1;
		}
	}
	return (cidr);
}

static int validate_cidr(const char *cidr)
{
	int i = 0;
	int val;

	while (cidr[i])
	{
		if (!isdigit((unsigned char)cidr[i]))
			return (-1);
		i++;
	}
	val = atoi(cidr);
	if (val < 0 || val > 32)
		return (-1);
	return (val);
}

int cidr_to_mask(char *cidr, int octets[4])
{
	int val = validate_cidr(cidr);

	if (val == -1)
		return (-1);

	unsigned int mask = 0xFFFFFFFF;
	mask = mask << (32 - val);

	octets[0] = (mask >> 24) & 0xFF;
    octets[1] = (mask >> 16) & 0xFF;
    octets[2] = (mask >> 8) & 0xFF;
    octets[3] = mask & 0xFF;

	return (0);
}
