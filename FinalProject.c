#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _transactions
{
	int index;
	double trans[50];
	char option[50][20];
}Transactions;
typedef struct _customerDetails
{
	long acc_no;
	char fullName[120];
	double balance;
	Transactions tranAmount;
	int noDeposit;
	int noWithdrawal;
}CustomerDetails;

typedef struct custNode
{
	CustomerDetails cds;
	struct custNode *nextNode;
}CustNode;


int checkIsAlphabet(char string[])
{
  
	char *p=string;
	
	while(*p!='\0')
	{
	 
	      
	      if(*p==' ')
	      {
	      	p++;
	      	continue;
		  }
		if(isalpha(*p)==0)
		{
			return 0;
		}
	   p++;
	}
	return 1;
}

int checkDigit(char digit[])
{
	char *p=digit;
	while(*p!='\0')
	{
		if(isdigit(*p)==0)
		{
			return 0;
		}
		p++;
	}
	return 1;
}
CustNode *head=NULL;
  /* Function to reverse the linked list */
    void reverse() 
    { 
        // Initialize current, previous and 
        // next pointers 
        CustNode* current = head; 
        CustNode *prev = NULL, *next = NULL; 
  
        while (current != NULL) { 
            // Store next 
            next = current->nextNode; 
  
            // Reverse current node's pointer 
            current->nextNode = prev; 
  
            // Move pointers one position ahead. 
            prev = current; 
            current = next; 
        } 
        head = prev; 
    } 
void pushCustomerNode(CustNode **shead,CustomerDetails ncustomer)
{
	CustNode *newNode=(CustNode *)malloc(sizeof(CustNode));
	newNode->cds=ncustomer;
	newNode->nextNode=*shead;
	*shead=newNode;
}
void readFromFile()
{

	CustomerDetails cds;
	long acc_no;
	char firstName[60];
	char lastName[60];
	double balance;
	double tranAmount;
	int noDeposit;
	int noWithdrawal;
	FILE *ftr;
	ftr=fopen("BankingCustomer.dat","r");
	if(ftr==NULL)
	{
		printf("\n File cannot be opened !");
		return;
	}
	while(fscanf(ftr,"%ld %s %s %lf %lf %d %d",&cds.acc_no,firstName,lastName,&cds.balance,&tranAmount,&cds.noDeposit,&cds.noWithdrawal)!=EOF)
	{	
	 
	   char space[]="  ";
	   strcat(firstName,space);
	  strcat(firstName,lastName);
	  strcat(cds.fullName,firstName);
	  cds.tranAmount.index=0;
	  cds.tranAmount.trans[cds.tranAmount.index]=tranAmount;
	  strcpy(cds.tranAmount.option[cds.tranAmount.index],"Deposit");
	  pushCustomerNode(&head,cds);  //pushing the customer node into the stack
	  strcpy(cds.fullName,"");
	}
	fclose(ftr);

}

void deleteAccount()                                                                                                                                                                                                                                                                                         
{
	char swacc_no[20];
	CustNode *temp=head;
	CustNode *prev=head;
	printf("\n Enter the account number\t");
	long acc_no;
	scanf("%s",&swacc_no);
		if(checkDigit(swacc_no)==0)
	{
		printf("\n Invalid Account Number entered !");
		return;
	}
	acc_no=atoi(swacc_no);
	while(temp!=NULL)
	{
		if(acc_no==head->cds.acc_no)
		{
			head=temp->nextNode;
			writeToFile();
			return;
		}
		else if(temp->cds.acc_no==acc_no)
		{
			
			CustNode *temp1=temp;
			prev->nextNode=temp->nextNode;
			free(temp1);
			writeToFile();
			reverse();
			return;
		}
		prev=temp;
		temp=temp->nextNode;
	}
	
	printf("Account not found !");
}
void searchAccount()
{ 
	char swacc_no[20];
	CustNode *temp=head;
	printf("\n Enter the account number\t");
	long acc_no;
	scanf("%s",&swacc_no);
		if(checkDigit(swacc_no)==0)
	{
		printf("\n Invalid Account Number entered !");
		return;
	}
	acc_no=atoi(swacc_no);
	printf("\n %10s %16s %15s %20s %20s %29s","Acc_NO","Full Name","Balance","No. Deposit","No. Withdrawal"," Transaction Posted ");
	while(temp!=NULL)
	{
		if(temp->cds.acc_no==acc_no)
		{
			 printf("\n%10ld %20s  %10.2lf  %15d %15d %25.2lf %10s",temp->cds.acc_no,temp->cds.fullName,temp->cds.balance,temp->cds.noDeposit,temp->cds.noWithdrawal,temp->cds.tranAmount.trans[0],temp->cds.tranAmount.option[0]);
			 int i;
		    	for(i=1;i<=temp->cds.tranAmount.index;i++)
				{
				    printf("%230.2lf %10s",temp->cds.tranAmount.trans[i],temp->cds.tranAmount.option[i]);	
				    printf("\n");
				}
			 return;
		}
		temp=temp->nextNode;
	}
	printf("\n Account cannot be found !");
}

void modifyAccount()
{
	CustNode *temp=head;
	char swacc_no[20];
	printf("\n Enter the account number\t");
	long acc_no;
	char fullName[50];
	double balance;
	scanf("%s",&swacc_no);
		if(checkDigit(swacc_no)==0)
	{
		printf("\n Invalid Account Number entered !");
		return;
	}
	acc_no=atoi(swacc_no);
	while(temp!=NULL)
	{
		if(temp->cds.acc_no==acc_no)
		{
			printf("\n Enter the accountee name\t");
			fflush(stdin);
			gets(fullName);
			fflush(stdin);
			if(checkIsAlphabet(fullName)==0)
			{
				printf("\n Invalid Account Name Entered !");
				return;
			}
			strcpy(temp->cds.fullName,fullName);
		
			printf("\n Account Updated Successfully !");
			writeToFile();
			
			return;
		}
		temp=temp->nextNode;
	}
	printf("\n Account Number not found");
}
void addAccount()
{
    CustomerDetails cds;
  
	cds.acc_no=head->cds.acc_no+1;
	printf("\n Enter the name of the accountee\t");
	char fullName[120];
	fflush(stdin);
	gets(fullName);
	fflush(stdin);
	if(checkIsAlphabet(fullName)==0)
	{
		printf("\n Invalid account name");
		return ;
	}

	cds.noDeposit=0;
	cds.noWithdrawal=0;
	cds.balance=0;
	cds.tranAmount.trans[0]=0;
	cds.tranAmount.index=0;
	strcpy(cds.tranAmount.option[cds.tranAmount.index],"Deposit");
	strcpy(cds.fullName,fullName);
	FILE *ftr;
	ftr=fopen("BankingCustomer.dat","a");
	if(ftr==NULL)
	{
		printf("\n File cannot be opened !");
	}
	else
	{
		 
		fprintf(ftr,"%ld %s %.2f %.2f %d %d\n",cds.acc_no,cds.fullName,cds.balance,cds.tranAmount.trans[0],cds.noDeposit,cds.noWithdrawal);
		
	}
	
	fclose(ftr);
	
	pushCustomerNode(&head,cds);
	printf("\n Account created successfully !");	
}
void displayRecord()
{
	
  CustNode *temp;
	temp=head;
	printf("\n %10s %16s %20s %25s %15s %19s","Acc_NO","Full Name","Balance","Latest Transaction","No. Deposit","No. Withdrawal");
	while(temp!=NULL)
	{
			
		 printf("\n%8ld %20s  %18.2lf %16.2lf %18d %15d",temp->cds.acc_no,temp->cds.fullName,temp->cds.balance,temp->cds.tranAmount.trans[temp->cds.tranAmount.index],temp->cds.noDeposit,temp->cds.noWithdrawal);
		temp=temp->nextNode;
	}	
}
void writeToFile()
{
	reverse();
	
	CustNode *temp=head;
	FILE *ftr;
	ftr=fopen("BankingCustomer.dat","w");
	if(ftr==NULL)
	{
		printf("\n File cannot be opened !");
	}
	else
	{
		while(temp!=NULL)
		{
		
		   fprintf(ftr,"%ld %s %.2f %.2f %d %d\n",temp->cds.acc_no,temp->cds.fullName,temp->cds.balance,temp->cds.tranAmount.trans[temp->cds.tranAmount.index],temp->cds.noDeposit,temp->cds.noWithdrawal);
		   temp=temp->nextNode;
		}
	
		 printf("\n File was written successfuly ");
	}
	
	fclose(ftr);
}
void depositInAccount()
{
	int acc_no;
	char swacc_no[20];
	char swdepositAmount[20];
	double depositAmount;
	printf("\n Enter the account number\t");
	scanf("%s",&swacc_no);
	if(checkDigit(swacc_no)==0)
	{
		printf("\n Invalid Account Number entered !");
		return;
	}
	acc_no=atoi(swacc_no);
	CustNode *temp;
	temp=head;
	while(temp!=NULL)
	{
		if(temp->cds.acc_no==acc_no)
		{
			printf("\n Enter the amount to be deposited ");
			scanf("%s",&swdepositAmount);
			if(checkDigit(swdepositAmount)==0)
			{
				printf("\n Not a valid deposit amount !");
				return;
			}
			depositAmount=atoi(swdepositAmount);
			if(depositAmount<0)
			{
				printf("\n Invalid Amount ");
				return;
			}
			temp->cds.balance=temp->cds.balance+depositAmount;
			temp->cds.tranAmount.index+=1;
			temp->cds.tranAmount.trans[temp->cds.tranAmount.index]=depositAmount;
			strcpy(temp->cds.tranAmount.option[temp->cds.tranAmount.index],"Deposit");
			
			temp->cds.noDeposit+=1;
			writeToFile();
			reverse();
			return;
			
		}
		temp=temp->nextNode;
	}
	printf("\n Sorry account number not found !");
}
void bubbleSort(CustomerDetails customers[],int size)
{
	int i,j;
  
	int flag;
	

	for(j=0;j<size;j++)
	{
		flag=0;
		for(i=0;i<size-1-j;i++)
		{
			if(customers[i].acc_no>customers[i+1].acc_no)
			{
				CustomerDetails cnds=customers[i];
				customers[i]=customers[i+1];
				customers[i+1]=cnds;
			
				flag=1;
			}
		}
		if(flag==0)
		{
			break;
		}
	}
	
	
}

int compareTo(const void *p1,const void *p2)
{
	CustomerDetails *item1=(CustomerDetails*)p1;
	CustomerDetails *item2=(CustomerDetails*)p2;
//	if(item1->quantity>item2->quantity)
//	{
//		return 1;
//	}
//	else if(item2->quantity>item1->quantity)
//	{
//		return -1;
//	}
//	else
//	{
//		return 0;
//	}

		return item1->acc_no-item2->acc_no;
}

void sortIntoArray()
{
	CustNode *temp=head;
	CustomerDetails customers[50];
	int in=0;
	while(temp!=NULL)
	{
		customers[in]=temp->cds;
		temp=temp->nextNode;
		in++;
		
	}
	
	int choice,i;
	printf("\n1>SORT THE RECORDS USING BUBBLE SORT !");
	printf("\n2>SORT THE RECORDS USING QUICK SORT !\n Input>\t");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: bubbleSort(customers,in);
				break;
		case 2: qsort(customers,in,sizeof(CustomerDetails),compareTo);
				break;
	}
		
	for(i=0;i<in;i++)
	{
		printf("\n %ld %s %.2lf %.2f %d %d",customers[i].acc_no,customers[i].fullName,customers[i].balance,customers[i].tranAmount.trans[customers[i].tranAmount.index],customers[i].noDeposit,customers[i].noWithdrawal);
	}

	
	
	
}
void withdrawFromAccount()
{
	long acc_no;
	char swacc_no[20];
	char swithDrawAmount[20];
	double withDrawAmount;
	printf("\n Enter the account number\t");
	scanf("%s",&swacc_no);
	if(checkDigit(swacc_no)==0)
	{
		printf("\n Invalid Account Number entered !");
		return;
	}
	acc_no=atoi(swacc_no);

	CustNode *temp;
	temp=head;
	while(temp!=NULL)
	{
		if(temp->cds.acc_no==acc_no)
		{
			printf("\n Enter the amount to be withdrawed ");
			scanf("%s",&swithDrawAmount);
			if(checkDigit(swithDrawAmount)==0)
			{
				printf("\n Invalid amount entered ");
				return;
			}
			withDrawAmount=atoi(swithDrawAmount);
			if(withDrawAmount<0)
			{
				printf("\n Invalid Amount ");
				return;
			}
			else if(temp->cds.balance<withDrawAmount)
			{
				printf("\n Insufficient Balance");
				return;
			}
			temp->cds.balance=temp->cds.balance-withDrawAmount;
	        temp->cds.tranAmount.index+=1;
			temp->cds.tranAmount.trans[temp->cds.tranAmount.index]=withDrawAmount;
			strcpy(temp->cds.tranAmount.option[temp->cds.tranAmount.index],"Withdraw");
			
			temp->cds.noWithdrawal+=1;
			writeToFile();
			reverse();
			return;
			
		}
		temp=temp->nextNode;
	}
	printf("\n Sorry account number not found !");
}

void showAllTransaction()
{
	char swacc_no[20];
	long acc_no;
	printf("\n Enter the account number\t");
	scanf("%s",&swacc_no);
		if(checkDigit(swacc_no)==0)
	{
		printf("\n Invalid Account Number entered !");
		return;
	}
	acc_no=atoi(swacc_no);
	CustNode *temp;
	temp=head;
	while(temp!=NULL)
	{
			if(temp->cds.acc_no==acc_no)
			{
			     int i;
			
				for(i=0;i<=temp->cds.tranAmount.index;i++)
				{
				    printf("\n %.2lf %s",temp->cds.tranAmount.trans[i],temp->cds.tranAmount.option[i]);	
				}
				return;
		
			}
			temp=temp->nextNode;
	}
}

void listAllAccounts()
{
	CustNode *temp;
	temp=head;
	printf("\n %32sActive Accounts \n"," ");
	printf("\n %35s %20s","Account Number"," Full Name");
	while(temp!=NULL)
	{
	   printf("\n %30ld %26s",temp->cds.acc_no,temp->cds.fullName);
	   temp=temp->nextNode;
	}
}

void dailyTransaction()
{
	int choice;
	printf("\n1>Deposit into the account ");
	printf("\n2>Withdraw from the account");
	printf("\n3> Show all transactions for the account");
	printf("\n4>GO BACK ");
	printf("\nInput>\t");
	
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:depositInAccount();
				break;
		case 2:withdrawFromAccount();
				break;
		case 3:showAllTransaction();
				break;
		case 4:mainMenu();
		
	}
}
void binarySearchTree()
{
	
}
void mainMenu()
{
	int choice;
	printf("\n\n1> Open a new account(Add Account)");
	printf("\n2> Daily Transaction (deposit or withdraw)");
	printf("\n3> List of Accounts ( Display all active customer accounts)");
	printf("\n4> Search Customer");
	printf("\n5> Display Customer Record ");
	printf("\n6> Modify an account");
	printf("\n7> Delete an account");
	printf("\n8> QUIT");
	printf("\n9> Sort into the array");
	printf("\n10>Create Binary Search Tree ");
	printf("\nInput>\t");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:addAccount();
				break;
		case 2: dailyTransaction();
				break;
		case 3: listAllAccounts();
				break;
		case 4:searchAccount();
				break;
		case 5: displayRecord();
				break;
		case 6: modifyAccount();
				break;
		case 7:deleteAccount();
				break;
		case 8: exit(1);
		case 9: sortIntoArray();
				break;
		case 10:binarySearchTree();
				
				break;
	}	
	
}
int main()
{
	readFromFile();
	while(1)
	{
		mainMenu();
	}
	
	return 1;
}
