#include <stdio.h>
#include <stdint.h>

#define HASH_SIZE	  16

#define ROR(reg, num) ((reg) = ((reg >> (num)) | (reg << (8U - (num)))))

void GetHash(uint32_t data[HASH_SIZE][HASH_SIZE], uint32_t hash[HASH_SIZE])
{
	for (uint8_t i = 0; i < HASH_SIZE; i++)
	{
		hash[i] = 0;

		// Incorporate all elements of data into the hash
		for (uint8_t j = 0; j < HASH_SIZE; j++)
		{
			hash[i] += data[i][j];

			// Rotate the hash by 1 bit
			ROR(hash[i], 5);
		}
	}
}

int main()
{
	uint32_t data[HASH_SIZE][HASH_SIZE];
	uint32_t hash[HASH_SIZE];

	uint8_t num = 0;

	// Initializing the array with unique values
	for (uint8_t i = 0; i < HASH_SIZE; i++)
	{
		for (uint8_t j = 0; j < HASH_SIZE; j++)
		{
			data[i][j] = num++;
			//data[1][1] = 1;
		}
	}

	printf("data:\n");
	for (uint8_t i = 0; i < HASH_SIZE; i++)
	{
		for (uint8_t j = 0; j < HASH_SIZE; j++)
		{
			printf(" %02x ", data[i][j]);
		}
		printf("\n");
	}

	// Calculating and printing the modified hash
	GetHash(data, hash);

	printf("\nhash:\n");

	for (int i = 0; i < HASH_SIZE; i++)
	{
		printf(" %02x ", hash[i]);
	}

	return 0;
}
