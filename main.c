#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOOD_NAME 100
#define MAX_TYPE_NAME 100
#define MAX_LINE 256
#define MAX_DRINK_NAME 100

void readType(char *type);

int main() {

    FILE *data;
    data=fopen("D:\\Faculta\\An1\\CP\\food-ordering\\cmake-build-debug\\data.txt", "w");

    if( data == NULL ) {
        perror("Error: ");
    }

    //read number of foods
    int noOfFoodTypes;
    printf("Please input number of food types:\n");
    scanf("%d", &noOfFoodTypes);
    getchar();

    //read foods
    char s[MAX_LINE];
    char **foodTypes;
    foodTypes = (char**)malloc(noOfFoodTypes * sizeof(char*));
    printf("Please input food types (each on a new line, may contain spaces):\n");
    for(int i=0; i<noOfFoodTypes; i++)
    {
        //read each food
        foodTypes[i]=(char*)malloc(MAX_FOOD_NAME * sizeof(char));
        gets(s);
        strcpy(foodTypes[i],s);
    }

    //read number of types
    int *noOfSpecificTypes;
    noOfSpecificTypes = (int *) malloc(noOfFoodTypes * sizeof(int));
    char ***specificTypes = (char***)malloc(noOfFoodTypes * sizeof(char**));
    double **prices = (double**)malloc(noOfFoodTypes * sizeof(double*));
    for(int i=0; i<noOfFoodTypes; i++)
    {
        //read no of types
        printf("Please input no of specific foods for food %s:\n", foodTypes[i]);
        scanf("%d", &noOfSpecificTypes[i]);
        getchar();
        //read types&prices
        specificTypes[i] = (char**)malloc(noOfSpecificTypes[i] * sizeof(char*));
        prices[i] = (double*)malloc(noOfSpecificTypes[i] * sizeof(double));
        printf("Please input %s specific foods & prices: each line in the format <specific food> (price):\n", foodTypes[i]);
        for(int j=0; j<noOfSpecificTypes[i]; j++)
        {
            specificTypes[i][j] = (char*)malloc(MAX_TYPE_NAME * sizeof(char));
            readType(specificTypes[i][j]);
            char line[MAX_LINE];
            gets(line);
            sscanf(line, "%lf", &prices[i][j]);
        }
    }

    //read number of drinks
    int noOfDrinks;
    printf("Please input number of drink types:\n");
    scanf("%d", &noOfDrinks);
    getchar();

    //read drinks
    char **drinks  = (char**)malloc(noOfDrinks * sizeof(char*));
    double *drinkPrices = (double*)malloc(noOfFoodTypes * sizeof(double));
    printf("Please input the drinks: each line in the format <drink> (price):\n");
    for(int i=0; i<noOfDrinks; i++)
    {
        //read each drink
        drinks[i]=(char*)malloc(MAX_DRINK_NAME * sizeof(char));
        readType(drinks[i]);
        char line[MAX_LINE];
        gets(line);
        sscanf(line, "%lf", &drinkPrices[i]);
    }

    //display data
    fprintf(data, "%d:\n", noOfFoodTypes);
    for(int i=0; i<noOfFoodTypes; i++)
    {
        fprintf(data,"%s %d: ",foodTypes[i],noOfSpecificTypes[i]);
        for(int j=0; j<noOfSpecificTypes[i]; j++)
            fprintf(data, "(%s - %.2lf) ", specificTypes[i][j], prices[i][j]);
        fprintf(data,"\n");
    }

    fprintf(data,"%d:\n",noOfDrinks);
    for(int i=0; i<noOfDrinks-1; i++)
    {
        fprintf(data,"(%s - %.2f), ",drinks[i],drinkPrices[i]);
    }
    fprintf(data,"(%s - %.2f)\n",drinks[noOfDrinks-1],drinkPrices[noOfDrinks-1]);

      //free memory
      for(int i=0;i<noOfFoodTypes;i++) {
          for(int j=0;j<noOfSpecificTypes[i];j++) {
              free(specificTypes[i][j]);
          }
          free(specificTypes[i]);
          free(prices[i]);
          free(foodTypes[i]);
      }
      free(specificTypes);
      free(prices);
      free(noOfSpecificTypes);
      free(foodTypes);
      for(int i=0;i<noOfDrinks;i++)
          free(drinks[i]);

      free(drinks);
      free(drinkPrices);

      fclose(data);
      return 0;
  }

  void readType(char *type)
  {
      char c = getchar();
      int i=0;
      while(c!='(') {
          type[i] = c;
          c = getchar();
          i++;
      }
      type[i-2] = '\0';
      strcpy(type,type+1);
  }
