#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int	id;
	char name;
	int	order; 
};

struct Node
{
    struct RecordType data;
    struct Node *next;
};

// Fill out this structure
struct HashType
{
	struct Node *head;
};

// Compute the hash function
int hash(int x)
{
	return x % 10;
}

void insertRecord(struct HashType hashTable[], int id, char name, int order)
{
    int index = hash(id);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data.id = id;
    newNode->data.name = name;
    newNode->data.order = order;
    newNode->next = NULL;

    if (hashTable[index].head == NULL)
    {
        hashTable[index].head = newNode;
    }
    else
    {
    	struct Node *temp = hashTable[index].head;
    	while (temp->next != NULL)
    	{
        	temp = temp->next;
    	}
    	temp->next = newNode;
    }
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType hashTable[], int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		printf("index %d -> ", i);
        struct Node *temp = hashTable[i].head;
        while (temp != NULL)
        {
            printf("(%d, %c, %d) -> ", temp->data.id, temp->data.name, temp->data.order);
            temp = temp->next;
        }
        printf("NULL\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	struct HashType hashTable[10];
    for (int i = 0; i < 10; ++i)
    {
        hashTable[i].head = NULL;
    }

    // Insert records into the hash table
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, pRecords[i].id, pRecords[i].name, pRecords[i].order);
    }

    // Display records in the hash structure
    displayRecordsInHash(hashTable, 10);

    return 0;
}