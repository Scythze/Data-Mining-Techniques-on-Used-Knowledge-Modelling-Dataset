#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <time.h>
#include <math.h>

#define NUM_OF_ITERATIONS 100
#define SAMPLE_SIZE 250
typedef struct sample
{
    float STG;
    float SCG;
    float STR;
    float LPR;
    float PEG;
    char className[15];
    float distance[4];
}SAMPLE;

float calculateDistance(SAMPLE,SAMPLE);
float calculateDistanceByImportantInfo(SAMPLE,SAMPLE);
int findMinimumDistanceIndex(SAMPLE);

int main()
{
    srand(time(NULL));
    int r0,r1,r2,r3,i,j,k,numberOfSamples;
    FILE * pFile;

    pFile = fopen ("data_1.txt","r");
    fscanf (pFile, "%d", &numberOfSamples);

    SAMPLE samples[SAMPLE_SIZE];
    SAMPLE test[SAMPLE_SIZE];
    SAMPLE mean;
    SAMPLE points[4];

    for(i = 0; i < numberOfSamples; i++){
        fscanf(pFile,"%f,%f,%f,%f,%f,%s",&samples[i].STG, &samples[i].SCG, &samples[i].STR, &samples[i].LPR, &samples[i].PEG, samples[i].className);
        strcpy(test[i].className,samples[i].className);
    }

    do{
        r0 = rand() % 249;
    }while( strcmp(samples[r0].className, "very_low") != 0 );
    points[0] = samples[r0];
    strcpy(points[0].className,samples[r0].className);
    printf("\nPoint0 :[%d]: %f %f %f %f %f %s",r0,points[0].STG, points[0].SCG, points[0].STR,points[0].LPR, points[0].PEG,points[0].className);

    do{
        r1 = rand() % 249;
    }while( strcmp(samples[r1].className, "Low") != 0 );
    points[1] = samples[r1];
    strcpy(points[1].className,samples[r1].className);
    printf("\nPoint1 :[%d]: %f %f %f %f %f %s",r1,points[1].STG, points[1].SCG, points[1].STR,points[1].LPR, points[1].PEG,points[1].className);

    do{
        r2 = rand() % 249;
    }while( strcmp(samples[r2].className, "Middle") != 0 );
    points[2] = samples[r2];
    strcpy(points[2].className,samples[r2].className);
    printf("\nPoint2 :[%d]: %f %f %f %f %f %s",r2,points[2].STG, points[2].SCG, points[2].STR,points[2].LPR, points[2].PEG,points[2].className);

    do{
        r3 = rand() % 249;
    }while( strcmp(samples[r3].className, "High") != 0 );
    points[3] = samples[r3];
    strcpy(points[3].className,samples[r3].className);
    printf("\nPoint3 :[%d]: %f %f %f %f %f %s",r3,points[3].STG, points[3].SCG, points[3].STR,points[3].LPR, points[3].PEG,points[3].className);
    //printf("R0 : %d  ==> %f %f %f %f %f %f %s\n" ,r0,points[0].STG,points[0].SCG,points[0].STR,points[0].LPR,points[0].PEG, points[0].className);


    int minIndex;
    for(i=0; i< NUM_OF_ITERATIONS; i++){
        for(j=0; j< numberOfSamples; j++){
            for(k=0; k<4; k++){
               //
               samples[j].distance[k] = calculateDistance(samples[j],points[k]);
            }
            minIndex = findMinimumDistanceIndex(samples[j]);
            strcpy( samples[j].className , points[minIndex].className );
        }

     //   printf("R0 : %d  ==> %f %f %f %f %f %f %s\n" ,r0,points[0].STG,points[0].SCG,points[0].STR,points[0].LPR,points[0].PEG, points[0].className);
       // newMeanPointsByInfo(samples,numberOfSamples,&points[0],&points[1],&points[2],&points[3]);

        newMeanPoints(samples,numberOfSamples,&points[0],&points[1],&points[2],&points[3]);
/*
        printf("\n");
        printf("\nNew Point0 :[%d]: %f %f %f %f %f %s",r0,points[0].STG, points[0].SCG, points[0].STR,points[0].LPR, points[0].PEG,points[0].className);
        printf("\nNew Point1 :[%d]: %f %f %f %f %f %s",r1,points[1].STG, points[1].SCG, points[1].STR,points[1].LPR, points[1].PEG,points[1].className);
        printf("\nNew Point2 :[%d]: %f %f %f %f %f %s",r2,points[2].STG, points[2].SCG, points[2].STR,points[2].LPR, points[2].PEG,points[2].className);
        printf("\nNew Point3 :[%d]: %f %f %f %f %f %s",r3,points[3].STG, points[3].SCG, points[3].STR,points[3].LPR, points[3].PEG,points[3].className);
        printf("\n");
        getch();
*/
     //  printf("R0 : %d  ==> %f %f %f %f %f %f %s\n" ,r0,points[0].STG,points[0].SCG,points[0].STR,points[0].LPR,points[0].PEG, points[0].className);
    }


    int correct = 0;
    for(i=0; i< numberOfSamples; i++){
        if( strcmp(samples[i].className, test[i].className) == 0 )
            correct++;
    }

    float accuracy = (correct*1.0/numberOfSamples) * 100;
    printf("\n\n\Correctly classified percentage : %f",accuracy);



    fclose(pFile);
    return 0;
}

float calculateDistance(SAMPLE s1, SAMPLE s2){
    float distance=0;
    distance += (s1.STG - s2.STG) * (s1.STG - s2.STG);
    distance += (s1.SCG - s2.SCG) * (s1.SCG - s2.SCG);
    distance += (s1.STR - s2.STR) * (s1.STR - s2.STR);
    distance += (s1.LPR - s2.LPR) * (s1.LPR - s2.LPR);
    distance += (s1.PEG - s2.PEG) * (s1.PEG - s2.PEG);

    distance = sqrt(distance);
    return distance;
}


float calculateDistanceByImportantInfo(SAMPLE s1, SAMPLE s2){
    float distance;

    distance = sqrt( (s1.PEG - s2.PEG) * (s1.PEG - s2.PEG) );
    return distance;

}

int findMinimumDistanceIndex(SAMPLE s1){
    int i,minIndex;
    float minimum = 100;

    for(i=0; i<4; i++){
        if(s1.distance[i] < minimum){
                minimum = s1.distance[i];
                minIndex = i;
        }
    }

    return minIndex;
}


void newMeanPoints(SAMPLE samples[],int N, SAMPLE* p0,SAMPLE* p1,SAMPLE* p2,SAMPLE* p3){
    int i,nVery_Low=0,nLow=0,nMiddle=0,nHigh=0;
    float totalSTG=0,totalSCG=0,totalSTR=0,totalLPR=0,totalPEG=0;

    SAMPLE very_low,Low,Middle,High;
    very_low.STG = Low.STG = Middle.STG = High.STG = 0;
    very_low.SCG = Low.SCG = Middle.SCG = High.SCG = 0;
    very_low.STR = Low.STR = Middle.STR = High.STR = 0;
    very_low.LPR = Low.LPR = Middle.LPR = High.LPR = 0;
    very_low.PEG = Low.PEG = Middle.PEG = High.PEG = 0;

    for(i<0; i<N; i++)
    {
        if(strcmp(samples[i].className , "very_low") == 0){
            nVery_Low++;
            very_low.STG += samples[i].STG;
            very_low.SCG += samples[i].SCG;
            very_low.STR += samples[i].STR;
            very_low.LPR += samples[i].LPR;
            very_low.PEG += samples[i].PEG;
        }
        if(strcmp(samples[i].className , "Low") == 0){
            nLow++;
            Low.STG += samples[i].STG;
            Low.SCG += samples[i].SCG;
            Low.STR += samples[i].STR;
            Low.LPR += samples[i].LPR;
            Low.PEG += samples[i].PEG;
        }
        if(strcmp(samples[i].className , "Middle") == 0){
            nMiddle++;
            Middle.STG += samples[i].STG;
            Middle.SCG += samples[i].SCG;
            Middle.STR += samples[i].STR;
            Middle.LPR += samples[i].LPR;
            Middle.PEG += samples[i].PEG;

        }
        if(strcmp(samples[i].className , "High") == 0){
            nHigh++;
            High.STG += samples[i].STG;
            High.SCG += samples[i].SCG;
            High.STR += samples[i].STR;
            High.LPR += samples[i].LPR;
            High.PEG += samples[i].PEG;
        }
    }

        p0->STG = very_low.STG / nVery_Low ;
        p0->SCG = very_low.SCG / nVery_Low ;
        p0->STR = very_low.STR / nVery_Low ;
        p0->LPR = very_low.LPR / nVery_Low ;
        p0->PEG = very_low.PEG / nVery_Low ;

        p1->STG = Low.STG / nLow ;
        p1->SCG = Low.SCG / nLow ;
        p1->STR = Low.STR / nLow ;
        p1->LPR = Low.LPR / nLow ;
        p1->PEG = Low.PEG / nLow ;

        p2->STG = Middle.STG / nMiddle ;
        p2->SCG = Middle.SCG / nMiddle ;
        p2->STR = Middle.STR / nMiddle ;
        p2->LPR = Middle.LPR / nMiddle ;
        p2->PEG = Middle.PEG / nMiddle ;

        p3->STG = High.STG / nHigh ;
        p3->SCG = High.SCG / nHigh ;
        p3->STR = High.STR / nHigh ;
        p3->LPR = High.LPR / nHigh ;
        p3->PEG = High.PEG / nHigh ;

}


void newMeanPointsByInfo(SAMPLE samples[],int N, SAMPLE* p0,SAMPLE* p1,SAMPLE* p2,SAMPLE* p3){
    int i;
    int nVery_Low=0,nLow=0,nMiddle=0,nHigh=0;
    float totalSTG=0,totalSCG=0,totalSTR=0,totalLPR=0,totalPEG=0;
    SAMPLE very_low,Low,Middle,High;
    very_low.PEG = 0;
    Low.PEG = 0;
    Middle.PEG = 0;
    High.PEG = 0;




    for(i<0; i<N; i++)
    {
        if(strcmp(samples[i].className , "very_low") == 0){
            nVery_Low++;
            very_low.PEG += samples[i].PEG;
        }
        if(strcmp(samples[i].className , "Low") == 0){
            nLow++;
            Low.PEG += samples[i].PEG;
        }
        if(strcmp(samples[i].className , "Middle") == 0){
            nMiddle++;
            Middle.PEG += samples[i].PEG;

        }
        if(strcmp(samples[i].className , "High") == 0){
            nHigh++;
            High.PEG += samples[i].PEG;
        }
    }

        p0->PEG = very_low.PEG / nVery_Low ;
        p1->PEG = Low.PEG / nLow ;
        p2->PEG = Middle.PEG / nMiddle ;
        p3->PEG = High.PEG / nHigh ;
}

