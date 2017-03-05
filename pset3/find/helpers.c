/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"
#include <math.h>
#include <stdlib.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n){
int leftSide = 0;//начало
int rightSide = n - 1;//конец
int middle = (leftSide + rightSide) / 2;//середина
while (leftSide <= rightSide){  
	if (array[middle] == value){//проверяем значение 
		return true;
	}else if (value < array[middle]){//если нужное число меньше чем число середины - сдвигаемся влево
		rightSide = middle - 1;
		middle = floor((leftSide + rightSide) / 2);
	}else if (value > array[middle]){//если нужное число больше чем число середины - сдвигаемся вправо
		leftSide = middle + 1;
		middle = floor((leftSide + rightSide) / 2);
	}else{ 
		break;
	}
}
return false;
}

//----------------------------------1----------------------------------------------
/*
void sort(int values[], int n){   //Шейкер сортировка
int leftSide = 0, rightSide = n - 1;
int flag = 1, counter = 0, tmp = 0;
while ((leftSide < rightSide) && flag > 0){//выполняем пока есть какие-то изменения в циклах
	flag = 0;
	for (counter = leftSide; counter<rightSide; counter++){//передвигаем число вправо пока оно больше чем следующее
		if (values[counter]>values[counter + 1]){             
			tmp = values[counter];
			values[counter] = values[counter + 1];
			values[counter + 1] = tmp;
			flag = 1;     
		}
	}
	rightSide--; 
	for (counter = rightSide; counter>leftSide; counter--){//передвигаем число влево пока оно меньше чем следующее
		if (values[counter - 1]>values[counter]){            
			tmp = values[counter];
			values[counter] = values[counter - 1];
			values[counter - 1] = tmp;
			flag = 1;  
		}
	}
	leftSide++; 
}
}
*/
//-----------------------------------2---------------------------------------------------

void sort(int values[], int n){ //Сортировка Шелла
int increment = 2, counter1 = 0, counter2 = 0, tmp = 0;//increment - расстояние до следующего числа (расстояние между чисами в паре)
while (increment > 0){
	for (counter1 = 0; counter1 < n; counter1++){//
		counter2 = counter1;        
		tmp = values[counter1];
		while ((counter2 >= increment) && (values[counter2 - increment] > tmp)){//меняем местами числа в парах если следующее число в паре больше первого 
			values[counter2] = values[counter2 - increment]; 
			counter2 = counter2 - increment;       
		}
	values[counter2] = tmp; 
	}
	if (increment > 1){   
		increment = increment / 2;
	}else if (increment == 1){ 
		break; 
	}
}
}