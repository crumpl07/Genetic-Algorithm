/*
Start: 2/17/2020
End:3/12/2020
Goal: Make a GA guess my password
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

int Evaluate(char *,char[]);
char * Selection(char **,char[],int, int);
char * Crossover (char *,char *,int);
char * Mutation(char *,int);
void FreeMemory(char **,int);
char * FindBest(char **,int,char[],int);

int main(void)
{
    char **newPopulation, **oldPopulation;
    char *parent0, *parent1;
    char *kid, *best;
    int popSize = 50, x = 1;
    char answer[50] = "i like apples";
    int length = strlen(answer), count = 0;
    char vocab[] = "abcdefghijklmnopqrstuvwxyz ";
    int vocabLength = 27;
    srand(time(NULL));
//Setting aside memory
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
//Fill population
//==================================================================
    for(int i = 0; i < popSize; i++)
    {
        for(int j =0; j < length; j++)
        {
            oldPopulation[i][j] = vocab[rand() % vocabLength];
        }
        oldPopulation[i][length] = '\0';
    }
 // Run until user stops the program
 //==================================================================
     while(x)
     {
        for(int i = 0; i < 50; i++)
        {
            count+=1;
            for(int j = 0; j < popSize; j++)
            {
                parent0 = Selection(oldPopulation, answer, length, popSize);
                parent1 = Selection(oldPopulation, answer, length, popSize);
                kid = Crossover(parent0, parent1, length);
                newPopulation[j] = Mutation(kid, length);
                printf("individual -> %s : %d\n", newPopulation[j], count);
            }
            best = FindBest(newPopulation, popSize, answer, length);
            //printf("Best: %s\tGeneration: %d\n", best, count);
            for(int j = 0; j < popSize; j++)
            {
                oldPopulation[j] = newPopulation[j];
            }
        }
    }
    FreeMemory(newPopulation, popSize);
    FreeMemory(oldPopulation, popSize);
    return 0;
}

//Evaluates each individual by comparing each gene in the individual
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

//Selects two parents from the population given and returns the individual with the better evaluation
char * Selection(char **population, char answer[], int length, int popSize)
{
    char *temp1, *temp2, *choice;
    temp1 = (char*)malloc(length * sizeof(char*));
    temp2 = (char*)malloc(length * sizeof(char*));
    choice = (char*)malloc(length * sizeof(char*));
    //Setting temp1 & 2 to a random individual in the population given
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
    return choice;
}

//Splits the parents in half and gives half of each parent to the child
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
    return newInd;
}

//Goes through each individual's genes and picks a number between 0 and 100 if its less than two then it mutates that gene
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

//Frees memory of population given
void FreeMemory(char **oldPop, int popSize)
{
    for(int i = 0; i < popSize; i++)
    {
        free(oldPop[i]);
    }
    free(oldPop);
}

//Finds the best individual in each generation
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
