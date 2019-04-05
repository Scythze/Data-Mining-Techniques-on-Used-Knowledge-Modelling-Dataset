#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <time.h>
#include <math.h>

#define SAMPLE_SIZE 250

typedef struct training
{
    float STG;
    float SCG;
    float STR;
    float LPR;
    float PEG;
    char className[15];
}TRAINING;

typedef struct test
{
    float STG;
    float SCG;
    float STR;
    float LPR;
    float PEG;
    char className[15];
    float distance[225];
    char classifiedClassName[15];
}TEST;


float calculateDistance(TRAINING,TEST);
float calculateDistanceByImportantInfo(TRAINING,TEST);



int main()
{
    srand(time(NULL));
    int r1,i,j,k,numberOftraining;
    FILE * pFile;

    pFile = fopen ("data_1.txt","r");
    fscanf (pFile, "%d", &numberOftraining);

    TRAINING training[225];
    TEST test[24];


    for(i = 0; i < 24; i++){
        fscanf(pFile,"%f,%f,%f,%f,%f,%s",&test[i].STG, &test[i].SCG, &test[i].STR, &test[i].LPR, &test[i].PEG, test[i].className);
    }

    for(i = 0; i < 225; i++){
        fscanf(pFile,"%f,%f,%f,%f,%f,%s",&training[i].STG, &training[i].SCG, &training[i].STR, &training[i].LPR, &training[i].PEG, training[i].className);
    }




    for(i = 0; i < 24; i++){

    //    printf("%d  ==> %2f %2f %2f %2f %2f %s\n" ,i,test[i].STG,test[i].SCG,test[i].STR,test[i].LPR,test[i].PEG, test[i].className);
        for(j = 0; j < 225; j++){
            test[i].distance[j] = calculateDistance(training[j],test[i]);
        }
        applyKNN(&test[i],training);
    //    printf("%d  ==> %2f %2f %2f %2f %2f %s\n" ,i,test[i].STG,test[i].SCG,test[i].STR,test[i].LPR,test[i].PEG, test[i].classifiedClassName);
    }

    int correct = 0;
    for(i=0; i< 24; i++){
        if( strcmp(test[i].className, test[i].classifiedClassName) == 0 )
            correct++;
    }

    float accuracy = (correct*1.0/24) * 100;
    printf("\n\n\ Correctly classified percentage : %3f\n\n",accuracy);



    return 0;
}

float calculateDistance(TRAINING s1, TEST s2){
    float distance=0;
    distance += (s1.STG - s2.STG) * (s1.STG - s2.STG);
    distance += (s1.SCG - s2.SCG) * (s1.SCG - s2.SCG);
    distance += (s1.STR - s2.STR) * (s1.STR - s2.STR);
    distance += (s1.LPR - s2.LPR) * (s1.LPR - s2.LPR);
    distance += (s1.PEG - s2.PEG) * (s1.PEG - s2.PEG);

    distance = sqrt(distance);
    return distance;
}


float calculateDistanceByImportantInfo(TRAINING s1, TEST s2){
    float distance;

    distance = sqrt( (s1.PEG - s2.PEG) * (s1.PEG - s2.PEG) );
    return distance;

}

int returnHighest(int a,int b,int c,int d){
    if( a>=b && a>=c && a>=d)
        return a;
    if( b>=a && b>=c && b>=d)
        return b;
    if( c>=a && c>=b && c>=d)
        return c;
    if( d>=a && d>=b && d>=c)
        return d;
}

int applyKNN(TEST *t1,TRAINING training[]){
     int i;
     int indexes[5] = {0};
     int n1=0,n2=0,n3=0,n4=0;
     float firstmin = 99, secmin = 99, thirdmin = 99, fourthmin, fifthmin = 55;


     for(i=0; i<225; i++){

         if (t1->distance[i] < firstmin)
        {
            fifthmin = fourthmin; indexes[4] = indexes[3];
            fourthmin = thirdmin; indexes[3] = indexes[2];
            thirdmin = secmin; indexes[2] = indexes[1];
            secmin = firstmin; indexes[1] = indexes[0];
            firstmin = t1->distance[i]; indexes[0] = i;
        }

        if (t1->distance[i] < secmin)
        {
            fifthmin = fourthmin; indexes[4] = indexes[3];
            fourthmin = thirdmin; indexes[3] = indexes[2];
            thirdmin = secmin; indexes[2] = indexes[1];
            secmin = t1->distance[i]; indexes[1] = i;
        }

        if (t1->distance[i] < thirdmin)
        {
            fifthmin = fourthmin; indexes[4] = indexes[3];
            fourthmin = thirdmin; indexes[3] = indexes[2];
            thirdmin = t1->distance[i]; indexes[2] = i;
        }

        if (t1->distance[i] < fourthmin)
        {
            fifthmin = fourthmin; indexes[4] = indexes[3];
            fourthmin = t1->distance[i]; indexes[3] = i;
        }

        if (t1->distance[i] < fifthmin)
            fifthmin = t1->distance[i]; indexes[4] = i;
     }


     for(i = 0; i < 5 ; i++){
         if(strcmp(training[indexes[i]].className , "very_low") == 0 ){
            n1++;
         }
         else if(strcmp(training[indexes[i]].className , "Low") == 0 ){
            n2++;
         }
         else if(strcmp(training[indexes[i]].className , "Middle") == 0 ){
            n3++;
         }
         else if(strcmp(training[indexes[i]].className , "High") == 0 ){
            n4++;
         }
     }

    if ( n1 == returnHighest(n1,n2,n3,n4) )
        strcpy(t1->classifiedClassName , "very_low");
    else if( n2 == returnHighest(n1,n2,n3,n4) )
        strcpy(t1->classifiedClassName, "Low");
    else if( n3 == returnHighest(n1,n2,n3,n4) )
        strcpy(t1->classifiedClassName, "Middle");
    else if (n4 == returnHighest(n1,n2,n3,n4) )
        strcpy(t1->classifiedClassName, "High");

}
