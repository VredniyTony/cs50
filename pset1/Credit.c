
#include <stdio.h>
#include <cs50.h>
#include <math.h>

long long int getNumb();
int getCardType(long long int card);
int inspectionCard(int length, long long int numb);
int printTypeCard(int idCard, long long int numb);

int main(void) {
	long long int numb = getNumb();
	int cardType = getCardType(numb);
	int print = printTypeCard(cardType, numb);
	return 0;
}

long long int getNumb() {
	long long int numbCard = 0;
	printf("Number:");
	numbCard = get_long_long();
	return numbCard;
}

int getCardType(long long int card) {
	int check15 = floor((card / 10000000000000));
	int check16 = floor((card / 100000000000000));
	if (check15 == 34 || check15 == 37)
		return 1;
	if (check16 == 51 || check16 == 52 || check16 == 53 || check16 == 54 || check16 == 55)
		return 2;
	if (floor((card / 1000000000000)) == 4)
		return 3;
	if (floor((card / 1000000000000000)) == 4)
		return 4;
	return 0;
}

int printTypeCard(int idCard, long long int numb) {
	int numbLength = 0;
	int getInspection = 0;
	switch (idCard) {
	case 0:
		printf("INVALID\n");
		return 0;
	case 1:
		numbLength = 15;
		getInspection = inspectionCard(numbLength, numb);
		if (getInspection == 1)
			printf("AMEX\n");
		else
			printf("INVALID\n");
		return 0;
	case 2:
		numbLength = 16;
		getInspection = inspectionCard(numbLength, numb);
		if (getInspection == 1)
			printf("MASTERCARD\n");
		else
			printf("INVALID\n");
		return 0;
	case 3:
		numbLength = 13;
		getInspection = inspectionCard(numbLength, numb);
		if (getInspection == 1)
			printf("VISA\n");
		else
			printf("INVALID\n");
		return 0;
	case 4:
		numbLength = 16;
		getInspection = inspectionCard(numbLength, numb);
		if (getInspection == 1)
			printf("VISA\n");
		else
			printf("INVALID\n");
		return 0;
	}
	return 0;
}

int inspectionCard(int length, long long int numb) {
	int sumDigit = 0;
	int counter = 0;
	int variable = 0;
	long long int numbCopy = numb;
	do {
		sumDigit = sumDigit + (numb % 10);
		numb = numb / 100;
		counter++;
	} while (counter != length - floor(length / 2));
	do {
		variable = floor((numbCopy % 100) / 10) * 2;
		if (variable >= 10) {
			sumDigit = sumDigit + floor(variable / 10);
			sumDigit = sumDigit + variable % 10;
		}
		else
			sumDigit = (sumDigit + variable);
		numbCopy = numbCopy / 100;
		counter++;
	} while (counter != length);
	if (sumDigit % 10 == 0)
		return 1;
	else return 0;
}
