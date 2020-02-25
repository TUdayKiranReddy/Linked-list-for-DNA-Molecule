#include <stdio.h>
#include <stdlib.h>

struct node
{
	char nucleotide;
	struct node* inter;
	struct node* intra;
};


int char_check(char t)
{
	if(t == 'A' || t == 'a' || t == 'T' || t == 't' || t =='G' || t == 'g' || t == 'C' || t == 'c')
		return 1;
	else
		return 0;
}
int case_check(char t)
{
	if(t>= 97)
		return 0;
	else
		return 1;
}

int complement(char t)
{
	if(t == 'A' || t =='a')
		return 84;
	else if(t == 'T' || t =='t')
		return 65;
	else if(t == 'G' || t =='g')
		return 67;
	else if(t == 'C' || t =='c')
		return 71;
	else
		return 0;
}

void printChain(struct node *DNA_Molecule_ID)
{
	struct node* temp = NULL;
	struct node* another = NULL;
	temp = DNA_Molecule_ID;
	char s;
	printf("Alpha chain is:\t");
	while(temp != NULL)
	{
		s = temp->nucleotide; 
		if(case_check(s) == 0)
			printf("%c",s - 32);
		else
			printf("%c",s);
		temp = temp->inter;
	}
	temp = DNA_Molecule_ID;
	//another = temp->intra;
	printf("\nBeta chain is:\t");
	while(temp != NULL)
	{
		another = temp->intra ;
		printf("%c",complement(temp->nucleotide));//another->nucleotide);
		temp = temp->inter;
	}
	printf("\n");
}
struct node *CreateChain()
{
	struct node* head = NULL;
	struct node* temp = NULL;
	struct node* add = NULL;
	struct node* another = NULL;
	//char n;
	int k;
	printf("Enter the no of nucleotides in DNA Molecule:");
	scanf("%d",&k);
	for(int i =0;i<k;i++)
	{
		temp = (struct node*)malloc(sizeof(struct node));
		another = (struct node*)malloc(sizeof(struct node));
		printf("Enter the position %d nucleotide in DNA Molecule:",i+1);
		rescan:
			scanf("%s",&temp->nucleotide);
			another->nucleotide = complement(temp->nucleotide);
			if(char_check(temp->nucleotide) == 1)
			{
				if(head == NULL)
				{
					head = temp;	
					head->intra = another;
					another->intra = NULL;
					another->inter = NULL;
					add = head;
				}
				
				else
				{
					add->intra = another;
					add->inter = temp;
					another->intra = NULL;
					another->inter = NULL;
					add = add->inter;
				}
			}
			else
			{
				printf("Invalid Nucleotide please re-enter the position %d nucleotide in DNA Molecule:",i+1);
				goto rescan;
			}
	}
	printf("DNA Molecule is succesfully added.\n");
	return (head);
}

int chain_length(struct node* DNA_Molecule_ID)
{
	struct node*temp = NULL;
	temp = DNA_Molecule_ID;
	int i = 0;
	while(temp != NULL)
	{
		temp = temp->inter;
		i++;
	}
	return i;
}

void insert(struct node* DNA_Molecule_ID,int Chain_ID,char Nucleotide,int position)
{
	struct node* temp = NULL;
	struct node* another = NULL;
	struct node* add = NULL;
	temp = (struct node*)malloc(sizeof(struct node));
	another = (struct node*)malloc(sizeof(struct node));
	int n = chain_length(DNA_Molecule_ID);
	
	if(char_check(Nucleotide) == 1)
	{
		if(Chain_ID == 1)
		{
			if(position > n +1 || position < 1)
				printf("Invalid position.");
				
			else if(position == 1)
			{
				temp->nucleotide = Nucleotide;
				temp->inter = DNA_Molecule_ID;
				DNA_Molecule_ID = temp;
				another->nucleotide = complement(Nucleotide);
				DNA_Molecule_ID->intra = another;
				another->inter = NULL;
				another->intra = NULL;
				printChain(DNA_Molecule_ID);
			}
			
			else
			{
				add = DNA_Molecule_ID;
				temp->nucleotide = Nucleotide;
				for(int i=0;i<position - 1 ;i++)
					add = add->inter;
				temp->inter = add->inter;
				add->inter = temp;
				another->nucleotide = complement(Nucleotide);
				temp->intra = another;
				another->inter = NULL;
				another->intra = NULL;
				printChain(DNA_Molecule_ID);
			}
		}
		else if(Chain_ID == 2)
		{
			if(position > n || position < 1)
				printf("Invalid position.");
				
			else if(position == 1)
			{
				temp->nucleotide = complement(Nucleotide);
				temp->inter = DNA_Molecule_ID;
				DNA_Molecule_ID = temp;
				another->nucleotide = Nucleotide;
				DNA_Molecule_ID->intra = another;
				another->inter = NULL;
				another->intra = NULL;
				printChain(DNA_Molecule_ID);
			}
			
			else
			{
				add = DNA_Molecule_ID;
				temp->nucleotide = complement(Nucleotide);
				for(int i=0;i<position - 1;i++)
					add = add->inter;
				temp->inter = add->inter;
				add->inter = temp;
				another->nucleotide = Nucleotide;
				temp->intra = another;
				another->inter = NULL;
				another->intra = NULL;
				printChain(DNA_Molecule_ID);
			}
		}
		else
			printf("Invalid Chain ID\n");
	}
	else
		printf("Invalid Nucleotide Insertion\n");
}

void delete(struct node* DNA_Molecule_ID,int position)
{
	struct node* temp =NULL;
	struct node* add =NULL;
	temp = (struct node*)malloc(sizeof(struct node));
	add = (struct node*)malloc(sizeof(struct node));
	
	int n = chain_length(DNA_Molecule_ID);
	
	if(position > n+1 || position <1)
		printf("No Nucleotide exits at that position to delete it.\n");
	else if(position == 1)
	{
		temp = DNA_Molecule_ID;
		DNA_Molecule_ID = temp->inter;
		printChain(DNA_Molecule_ID);
	}
	else
	{
		add = DNA_Molecule_ID;
		for(int i =0;i < position - 2;i++)
			add = add->inter;
		add->inter = add->inter->inter;
		printChain(DNA_Molecule_ID);
	}
}
void split(struct node* DNA_Molecule_ID)
{
	struct node* mole_1 = NULL;
	struct node* mole_2 = NULL;
	mole_1 = (struct node*)malloc(sizeof(struct node));
	mole_2 = (struct node*)malloc(sizeof(struct node));
	mole_1 = DNA_Molecule_ID;
	mole_2 = DNA_Molecule_ID;
	printf("Splited Molecules are:\n");
	printf("First Molecule is:\n");
	printChain(mole_1);
	printf("Secound Molecule is:\n");
	printChain(mole_2);
}
int main()
{
	struct node* dna[10];
	int d = 0;
	int i = 0;
	int stat = 0;
	start:
		printf("Menu\nPlease enter the required operation:\n");
		printf("1.CreateMolecule\n");
		printf("2.Insert nucleotide in a DNA Molecule\n");
		printf("3.Delete nucleotide in a DNA Molecule\n");
		printf("4.Split the DNA Molecule\n");
		printf("5.PrintChain\n");
		printf("6.PrintAllChain\n");
		scanf("%d",d);
		if( d == 1)
		{
			dna[i] = CreateChain();
			printf("DNA %d is\n",i+1);
			printChain(dna[i]);
			i++;
			stat = 1;
			goto start;
		}
		else if( d == 2 && stat == 1)
		{
			if( i != 1)
			{
				printf("Select in which DNA Molecule should the Nucleotide has to be inserted.\n");
				for(int w =0;w<i;w++)
					printf("DNA %d\t",w+1);
			
		
		
	
	//~ struct node* c;
	//~ c = CreateChain();
	//~ temp[0] = c;
	//~ printChain(temp[0]);

}
