/*
Start: 2/17/2020
End:
Goal: Make a GA guess my password

*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

//Prototypes
//void CreatePopMem(char**,char**,int,int);
//void FillPopMem(char **,char **,int,int);
int Evaluate(char *,char[]);
char * Selection(char **,char[],int, int);
char * Crossover (char *,char *,int);
char * Mutation(char *,int);
void FreeMemory(char **,int);
char * FindBest(char **,int,char[],int);



int main(void)
{
    char **newPopulation;
    char **oldPopulation;
    char *parent0;
    char *parent1;
    char *kid, *best;
    int popSize = 50, x = 1;
    char answer[50] = "i like apples";
    int length = strlen(answer), count = 0;
    printf("length %d", length);
    char vocab[] = "abcdefghijklmnopqrstuvwxyz ";
    int vocabLength = 27;
    srand(time(NULL));
//=================================================================
    parent0 = (char*)malloc(length * sizeof(char*));
    parent1 = (char*)malloc(length * sizeof(char*));
    kid = (char *)malloc(length * sizeof(char*));
    best = (char *)malloc(length * sizeof(char*));
    newPopulation = (char**)malloc((popSize) * sizeof(char*));
    oldPopulation = (char**)malloc((popSize) * sizeof(char*));
    for(int i = 0; i < popSize; i++)
    {
       newPopulation[i] = (char*)malloc((length) * sizeof(char));
       oldPopulation[i] = (char*)malloc((length) * sizeof(char));
    }
//==================================================================
    for(int i = 0; i < popSize; i++)
    {
        for(int j =0; j < length; j++)
        {
            oldPopulation[i][j] = vocab[rand() % vocabLength];
        }
        oldPopulation[i][length] = '\0';
    }
 //==================================================================
     while(x)
     {
         //printf("while\n");
        for(int i = 0; i < 50; i++)
        {
            count+=1;
            //printf("First for loop\n");
            for(int j = 0; j < popSize; j++)
            {
                //printf("Second for loop\n");
                parent0 = Selection(oldPopulation, answer, length, popSize);
                //printf("Parent 0: %s\n", parent0);
                parent1 = Selection(oldPopulation, answer, length, popSize);
                //printf("Parent 1: %s\n", parent1);
                kid = Crossover(parent0, parent1, length);
                //printf("Kid: %s, #%d\n", kid, count++);
                newPopulation[j] = Mutation(kid, length);
                printf("individual -> %s : %d\n", newPopulation[j], count);
            }
            best = FindBest(newPopulation, popSize, answer, length);
            //printf("Best: %s\tGeneration: %d\n", best, count);
            for(int j = 0; j < popSize; j++)
            {
                oldPopulation[j] = newPopulation[j];
                //printf("%s == %s : %d\n", oldPopulation[j], newPopulation[j], j);
                //printf("Old pop -> %s : %d\n", oldPopulation[j], j);
            }
        }
    }
    FreeMemory(newPopulation, popSize);
    FreeMemory(oldPopulation, popSize);
    return 0;
}
//==================================================================
int Evaluate(char *individual, char answer[])
{
    int eval = 0;
    for(int i = 0; i < strlen(answer); i++)
    {
        if(individual[i] == answer[i])
        {
            eval++;
        }
    }
    return eval;
}

char * Selection(char **population, char answer[], int length, int popSize)
{
    char *temp1, *temp2, *choice;
    temp1 = (char*)malloc(length * sizeof(char*));
    temp2 = (char*)malloc(length * sizeof(char*));
    choice = (char*)malloc(length * sizeof(char*));
    temp1 = population[rand() % popSize];
    temp2 = population[rand() % popSize];

    if(Evaluate(temp1, answer) > Evaluate(temp2, answer))
    {
        choice = temp1;
    }
    else
    {
       choice = temp2;
    }
    //printf("Made it though selection\n");
    return choice;
}

char * Crossover (char *parent0,char *parent1, int length)
{
    char * newInd;
    newInd = (char*)malloc(length * sizeof(char*));
    int split = length/2;

    for(int i = 0; i < length; i++)
    {
        if(i < split)
        {
            newInd[i] = parent0[i];
        }
        else
        {
            newInd[i] = parent1[i];
        }
    }
    //printf("Made it through crossover\n");
    return newInd;
}

char * Mutation (char *newInd, int length)
{
    int randNum = 0;
    int vocabLength = 27;
    char vocab[] = "abcdefghijklmonpqrstuvwxyz ";
    char randChar = 'c';
    for(int i = 0; i < length; i++)
    {
        randNum = rand() % 100;
        if(randNum < 2 && i != length)
        {
            randChar = vocab[rand() % vocabLength];
            newInd[i] = randChar;
        }

    }
    return newInd;
}

void FreeMemory(char **oldPop, int popSize)
{
    for(int i = 0; i < popSize; i++)
    {
        free(oldPop[i]);
    }
    free(oldPop);
}

//Doing this wrong. Evaluate the entire population to find the best.
char * FindBest(char** population, int popSize, char answer[], int length)
{
    int currentBest = 0;
    char * best;
    best = (char*)malloc(length * sizeof(char*));

    for(int i = 0; i < popSize; i++)
    {
        if(Evaluate(population[i], answer) > currentBest)
        {
            currentBest = Evaluate(population[i], answer);
            best = population[i];
        }
    }
    return best;
}
