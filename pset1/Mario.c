#include <stdio.h>
#include <cs50.h>

int getHeight();
int printAll(int printHeight);
int printSpace(int diffSpace);
int printHashtag(int hashtag);

int main(void) {
	const int height = getHeight();
	int print = printAll(height);
	return 0;
}

int getHeight() {
	int setHeight = 0;
	do {
		printf("Height:");
		setHeight = GetInt();
        if (setHeight == 0)
        {
            return 0;
        }
	} while (setHeight < 1 || setHeight > 23);
	return setHeight;
}

int printAll(int printHeight) {
	int counter = 1, space = 0, hashtag = 0;
	for (counter = 1; counter <= printHeight; counter++) {
		space = printSpace(printHeight - counter);
		hashtag = printHashtag(counter);
		printf("  ");
		hashtag = printHashtag(counter);
		printf("\n");
	}
	return 0;
}

int printSpace(int diffSpace) {
	int counterSpace = 1;
	while (counterSpace <= diffSpace) {
		printf(" ");
		counterSpace++;
	}
	return 0;
}

int printHashtag(int hashtag) {
	int counterHashtag = 1;
	while (counterHashtag <= hashtag) {
		printf("#");
		counterHashtag++;
	}
	return 0;
}
