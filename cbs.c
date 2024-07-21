#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VAT 0.13
#define DISCOUNT 0.05

struct Item 
{
    char name[50];
    int quantity;
    double unitPrice;
};

char customerName[50];
int long randomBillNumber;
int itemCount,i;
struct Item items[10];
double netTotal;
double subTotal;
double discount;
double vatAmount;
double grandTotal;

void getUserInput();
void calculator();
void displayBill();
void saveBill();

int main() 
{
    system("cls");
    getUserInput();
    calculator();
    displayBill();

    char choice;
    printf("\nDo you want to save the bill? (Y/N): ");
    fflush(stdin);
    scanf("%c", &choice);

    if(choice == 'y' || choice == 'Y')
    {
        saveBill();
    }

    else if(choice == 'n' || choice == 'N')
    {
        printf("\nBill was not saved");
    }

    else 
    {
        printf("\nInvalid Choice! Bill was not saved");
    }

    return 0;
}

void getUserInput() 
{
    fflush(stdin);
    printf("Enter customer name: ");
    fgets(customerName,50,stdin);
    fflush(stdin);

    printf("Enter the number of items: ");
    scanf("%d", &itemCount);

    for (i = 0; i < itemCount; i++)
    {
    	fflush(stdin);
        printf("\nEnter item %d name: ", i + 1);
		scanf("%s",&items[i].name);
        fflush(stdin);

        printf("Enter quantity: ");
        scanf("%d", &items[i].quantity);
        fflush(stdin);

        printf("Enter unit price: ");
        scanf("%lf", &items[i].unitPrice);
    }
}

void calculator() 
{
    subTotal = 0;

    for (i = 0; i < itemCount; i++)
    {
        double amount = items[i].unitPrice * items[i].quantity;
        subTotal = subTotal + amount;
    }

    discount = subTotal * DISCOUNT;
    netTotal = subTotal - discount;
    vatAmount = netTotal * VAT;
    grandTotal = netTotal + vatAmount;
}

void displayBill() 
{
	srand(time(0));
    time_t timeNow = time(NULL);
    randomBillNumber = rand() % 10000000;
    system("cls");
    printf("\t\t\t   BHAT-BHATENI SUPER MARKET\n");
    printf("\t\t\t\t KATHMANDU, NEPAL\n");
    printf("\nBill # : %ld-KTM-23",randomBillNumber);
    printf("\nDate   : %s",ctime(&timeNow));
    printf("Customer Name : %s",customerName);
    printf("\nSn\tItem\t\t\tQuantity\tRate\t\t\tAmount\n");

    for (i = 0; i < itemCount; i++)
    {
        printf("%d\t%s\t\t\t%d\t\tRs %.2f\t\tRs %.2f\n",
		i + 1, items[i].name, items[i].quantity, items[i].unitPrice, 
		items[i].unitPrice * items[i].quantity);
    }

    printf("-------------------------------------------");
	  printf("-------------------------------------------\n");

    printf("Sub Total:\t\t\t\t\t\t\tRs %.2f\n", subTotal);
    printf("Discount 5%%:\t\t\t\t\t\t\tRs %.2f\n", discount);

    printf("\t\t\t\t\t\t\t\t----------------------\n");
    printf("Net Total:\t\t\t\t\t\t\tRs %.2f\n", netTotal);

    printf("VAT 13%%:\t\t\t\t\t\t\tRs %.2f\n", vatAmount);
    printf("\t\t\t\t\t\t\t\t----------------------\n");
    printf("Grand Total:\t\t\t\t\t\t\tRs %.2f\n", grandTotal);
  	printf("-------------------------------------------");
  	printf("-------------------------------------------\n");    
  	printf("EXCHANGE WITHIN 7 DAYS WITH INVOICE BETWEEN 10AM-8PM\n");
  	printf("**TERMS AND CONDITIONS APPLY**\n");
  	printf("-------------------------------------------");
  	printf("-------------------------------------------\n");
    printf("BRANCH - KATHMANDU\n");
    printf("CASHIER : MARIO\n");
  	printf("-------------------------------------------");
  	printf("-------------------------------------------\n");
}


void saveBill() 
{
    FILE *fp;
    int i;
    fp = fopen("bill-record.csv", "a");

    fprintf(fp, "Bill #,%ld-KTM-23\n", randomBillNumber);
    fprintf(fp, "Customer Name,%s\n", customerName);

    fprintf(fp, "Sn,Item,Quantity,Rate,Amount\n");
    for (i = 0; i < itemCount; i++) 
	  {
        fprintf(fp, "%d,%s,%d,%.2f,%.2f\n", i + 1,
        items[i].name, items[i].quantity, items[i].unitPrice,
        items[i].unitPrice * items[i].quantity);
    }

    fprintf(fp, "Sub Total,%.2f\n", subTotal);
    fprintf(fp, "Discount 5%%,%.2f\n", discount);
    fprintf(fp, ",----------------------\n");
    fprintf(fp, "Net Total,%.2f\n", netTotal);
    fprintf(fp, "VAT 13%%,%.2f\n", vatAmount);
    fprintf(fp, ",----------------------\n");
    fprintf(fp, "Grand Total,%.2f\n", grandTotal);
    fprintf(fp, "----------------------");
    fprintf(fp, ",----------------------\n\n\n");

    fclose(fp);

    printf("\nBill Saved!");
}
