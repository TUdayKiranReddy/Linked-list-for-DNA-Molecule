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
	//~ struct node* another = NULL;
	temp = DNA_Molecule_ID;
	char s;
	printf("Alpha->");
	while(temp != NULL)
	{
		s = temp->nucleotide; 
		temp = temp->inter;
		if(temp!=NULL)
		{
			if(case_check(s) == 0)
				printf("%c--",s - 32);
			else
				printf("%c--",s);
		}
		else
		{
			if(case_check(s) == 0)
				printf("%c",s - 32);
			else
				printf("%c",s);
		}	
	}
	printf("\n");
	printf("       ");
	temp = DNA_Molecule_ID;
	while(temp != NULL)
	{
		printf("|  ");
		temp = temp->inter;
	}
	temp = DNA_Molecule_ID;
	//another = temp->intra;
	printf("\nBeta-->");
	while(temp != NULL)
	{
		//~ another = temp->intra ;
		s = complement(temp->nucleotide);
		temp = temp->inter;
		if(temp != NULL)
			printf("%c--",s);
		else
			printf("%c",s);
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
	//printf("DNA Molecule is succesfully added.\n");
	return (head);
}

struct node *create_psuedo_chain(struct node *DNA_Molecule_ID)
{
	struct node* head = NULL;
	struct node* temp = NULL;
	struct node* add = NULL;
	struct node* another = NULL;
	struct node* psuedo = DNA_Molecule_ID;
	
	while(psuedo != NULL)
	{
		temp = (struct node*)malloc(sizeof(struct node));
		another = (struct node*)malloc(sizeof(struct node));
		
		temp->nucleotide = psuedo->nucleotide;
		another->nucleotide = complement(temp->nucleotide);
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
		psuedo = psuedo->inter;
	}
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
				for(int i=0;i<position - 2 ;i++)
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
				for(int i=0;i<position - 2;i++)
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
struct node** split(struct node* DNA_Molecule_ID)
{
	static struct node* mole[2];
	mole[0] = (struct node*)malloc(sizeof(struct node));
	mole[1] = (struct node*)malloc(sizeof(struct node));
	mole[0] = create_psuedo_chain(DNA_Molecule_ID);
	mole[1]= create_psuedo_chain(DNA_Molecule_ID);

	//~ printf("Splited Molecules are:\n");
	//~ printf("First Molecule is:\n");
	//~ printChain(mole_1);
	//~ printf("Secound Molecule is:\n");
	//~ printChain(mole_2);
	return mole;
	
}
int main()
{
	struct node* dna[20];
	int d = 0;
	int i = 0;
	int stat = 0;
	

	start:
		printf("\nMenu\nPlease enter the required operation:\n");
		printf("1.CreateMolecule\n");
		printf("2.Insert nucleotide in a DNA Molecule\n");
		printf("3.Delete nucleotide in a DNA Molecule\n");
		printf("4.Split the DNA Molecule\n");
		printf("5.PrintChain\n");
		printf("6.PrintAllChain\n");
		scanf("%d",&d);
		if( d == 1)
		{
			dna[i] = CreateChain();
			printf("DNA %d is successfully added.\n",i+1);
			//printChain(dna[i]);
			i++;
			stat = 1;
			goto start;
		}
		else if( d == 2 && stat == 1)
		{
			redna:
				printf("Select in which DNA Molecule should the Nucleotide has to be inserted.\n");
				for(int w =0;w<i;w++)
					printf("DNA %d\t",w+1);
				printf("\n");
				int p;
				scanf("%d",&p);
				if(p < i+1 && p>0)
				{
					printf("Enter what nucleotide to should be inserted in DNA %d:",p);
					char s;
					renucleotide:
						scanf("%s",&s);
						//p++;
						if(char_check(s) == 1)
						{
							printf("Enter at which chain should %c be inserted in DNA %d:\n1.Alpha\t2.Beta\n",s,p+1);
							int q;
							rechain:
								scanf("%d",&q);
								if( q ==1 || q ==2)
								{
									printf("Enter at which position should %c nucleotide be inserted in DNA %d:",s,p+1);
									//printf("%d\n",p);
									int r;
									scanf("%d",&r);
									insert(dna[p],q,s,r);
								}
								else
								{
									printf("Invalid Chain please re-enter chain at which %c nucleotide be inserted in DNA %d:\n1.Alpha\t2.Beta\n",s,p);
									goto rechain;
								}
						}
						else
						{
							printf("Invalid nucleotide please re-enter what nucleotide to should be inserted in DNA %d:",p);
							goto renucleotide;
						}
				}
				else
				{
					printf("Invalid DNA.");
					goto redna;
				}
			goto start;
		}
		else if(d == 3 && stat == 1)
		{
			printf("Select in which DNA Molecule should the Nucleotide has to be deleted.\n");
			for(int w =0;w<i;w++)
				printf("DNA %d\t",w+1);
			printf("\n");
			int e;
			re_delete_dna:
				scanf("%d",&e);
				if(e < i+1 && e>0)
				{
					printf("Enter at which position should nucleotide be deleted:");
					int b;
					scanf("%d",&b);
					delete(dna[e-1],b);
				}
				else
				{
					printf("Invalid DNA.");
					goto re_delete_dna;
				}
			goto start;
		}
		else if ( d == 4 && stat ==1)
		{
			printf("Select in which DNA Molecule should be splited.\n");
			for(int w =0;w<i;w++)
				printf("DNA %d\t",w+1);
			printf("\n");
			int e;
			re_split_dna:
				scanf("%d",&e);
				if(e < i+1 && e>0)
				{
					struct node** cef = split(dna[e-1]);
					dna[e-1] = cef[0];
					dna[i] = cef[1];
					i++;
				}
				else
				{
					printf("Invalid DNA.");
					goto re_split_dna;
				}
			goto start;
		}
			
		else if(d == 5 && stat==1)
		{
			printf("Select which DNA molecule should be printed.\n");
			for(int w =0;w<i;w++)
				printf("DNA %d\t",w+1);
			printf("\n");
			int y;
			re_print_dna:
				scanf("%d",&y);
				if(y < i+1 && y >0)
				{
					printf("DNA %d is\n",y);
					printChain(dna[y-1]);
				}
				else
				{
					printf("Invalid DNA.\n");
					goto re_print_dna;
				}
			goto start;
		}
		else if(d==6 && stat==1)
		{
			for(int w =0;w<i;w++)
			{
				printf("DNA %d\t",w+1);
				printf("\n");
				printChain(dna[w]);
			}
		goto start;
		}
		else
		{
			printf("Invalid Input");
			goto start;
		}
//~ struct node* c = CreateChain();
//~ insert(c,2,'t',2);
//~ printChain(c);
}
