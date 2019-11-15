#include <stdio.h>
#include <stdlib.h>

#define MAX_FOOD_NAME 50
#define MAX_TYPE_NAME 50
#define MAX_LINE 256
#define MAX_DRINK_NAME 50

void readType(char *type);

int main() {
    //read number of foods
    int noOfFoodTypes;
    printf("Please input number of food types:\n");
    scanf("%d", &noOfFoodTypes);

    //read foods
    char **foodTypes;
    foodTypes = (char**)malloc(noOfFoodTypes * sizeof(char*));
    printf("Please input food types (each on a new line, may contain spaces):\n");
    for(int i=0; i<noOfFoodTypes; i++)
    {
        //read each food
        foodTypes[i]=(char*)malloc(MAX_FOOD_NAME * sizeof(char));
        scanf("%s", foodTypes[i]);
    }

    //read number of types
    int  *noOfSpecificTypes = (int*)malloc(noOfFoodTypes * sizeof(int));
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
        printf("Please input %s specific foods &prices: each line in the format <specific food> (price):\n", foodTypes[i]);
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

    //read drinks
    char **drinks;
    drinks = (char**)malloc(noOfDrinks * sizeof(char*));
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
    printf("The food data is:\n");
    for(int i=0; i<noOfFoodTypes; i++)
    {
        printf("%s: ",foodTypes[i]);
        for(int j=0; j<noOfSpecificTypes[i]; j++)
            printf("( %s - %.2lf) ", specificTypes[i], prices[i]);
        printf("\n");
    }
    printf("The drinks data is:\ndrinks: ");
    for(int i=0; i<noOfDrinks-1; i++)
    {
        printf("%s, ",drinks[i]);
    }
    printf("%s\n",drinks[noOfDrinks-1]);
    printf("prices: ");
    for(int i=0; i<noOfDrinks-1; i++)
    {
        printf("%.2lf, ",drinkPrices[i]);
    }
    printf("%.2lf\n",drinkPrices[noOfDrinks-1]);

    //free memory
    for(int i=0;i<noOfFoodTypes;i++)
    {
        for(int j=0;j<noOfSpecificTypes;j++)
        {
            free(specificTypes[i][j]);
        }
        free(specificTypes[i]);
        free(prices[i]);
        free(foodTypes[i]);
    }

    free(specificTypes);
    free(prices);
    free(foodTypes);
    free(noOfSpecificTypes);
    free(noOfFoodTypes);

    for(int i=0;i<noOfDrinks;i++)
    {
        free(drinks[i]);
    }
    free(drinks);
    free(drinkPrices);
    free(noOfDrinks);
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
    type[i-1] = '\0';
}
