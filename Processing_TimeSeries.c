///TheoB
#include <stdio.h>
int main()
{
    int i,z;
    float values[16]= {4109,3874,3842,3946,4207,3850,4030,4260,4193,4051,4126,4445,4344,4319,4571,4576};
    float sum[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    float sma[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    float wma[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    float dma[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    float cma[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    printf("\n --------------*******_*******-------------- \n")  ;
    printf("\n ******************************************--------------STEP 1 -----------****************************************** \n")  ;
    ///----------------------------------------------------------------------------------SIMPLE MOVING AVERAGE ----------------------------------------------------------------------------
    // N=4 since each value represents a quarter of a year. Wer'e gonna have to use the 3 adjacent values to calculate the SMA

    for(i=2; i<14; i++)
    {

        for (z=i-2; z<=i; z++)
        {

            sum[i]=sum[i]+values[z];
        }

        sma[i]=sum[i]/4;
    }
    printf("----------SMA---------- \n ");
    for(i=0; i<15; i++)
    {

        printf("%f \n",sma[i])  ;
    }
    ///----------------------------------------------------------------------------------WEIGHTED MOVING AVERAGE ----------------------------------------------------------------------------

    // the values closer to the current one weigh more into the value of the WMA
    // since we use 3 nearby values  the weight multiplier is 1/9
    for(i=1; i<14; i++)
    {
        wma[i]=(((2*values[i-1])/9)+((4*values[i])/9)+((2*values[i+1])/9)+((values[i+2])/9));

    }

    printf("----------WMA---------- \n ");
    for(i=0; i<16; i++)
    {

        printf("%f \n",wma[i])  ;
    }
///----------------------------------------------------------------------------------DOUBLE MOVING AVERAGE ----------------------------------------------------------------------------

//Utilizes the SMAs and calculates the 3 by 3 average
    for(i=2; i<14; ++i)
    {

        dma[i]=(sma[i-1]+sma[i]+sma[i+1])/3;
    }
    printf("----------DMA---------- \n ");
    for(i=0; i<16; i++)
    {

        printf("%f \n",dma[i])  ;
    }

///----------------------------------------------------------------------------------CENTERED MOVING AVERAGE ----------------------------------------------------------------------------

//calculating the Centered Moving Average
    float t1,t2;
    for (i=2; i<14; i++)
    {
        t1=(values[i-2]+values[i-1]+values[i]+values[i+1])/4;
        t2==(+values[i-1]+values[i]+values[i+1]+values[i+2])/4;
        cma[i]=(t1+t2); // this should be divided by 2 but i was getting weird results that i couldnt figure out.
    }
    printf("----------CMA---------- \n ");
    for(i=0; i<16; i++)
    {

        printf("%f \n",cma[i])  ;
    }

    printf("O CMA is the TxC \n ");

///-----------******************************************--------------STEP 2 -----------******************************************--------------
    printf("\n ******************************************--------------STEP 2 -----------****************************************** \n")  ;


// Seasonality Rate=(actual_value[i]/CMA[i])*100
    float seasonality_rate[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for (i=0; i<16; ++i)
    {
        seasonality_rate[i]=(values[i]/cma[i])*100;

    }

    printf("----------SEASONALITY RATES---------- \n ");
    for(i=3; i<14; i++)
    {

        printf("%f %% \n",seasonality_rate[i])  ;
    }

///-----------******************************************--------------STEP 3 -----------******************************************--------------
    printf("\n ******************************************--------------STEP 3 -----------****************************************** \n")  ;
    //Seasonality rate average

// //splitting the values into years
// each year will have 4 values
    float mo[4]= {0,0,0,0};
    for (i=0; i<4; ++i) // season multiplier
    {
        int megistos=i,elaxistos=i;
        for (z = i; z<16  ; z=z+4)  // max year
        {
            if (seasonality_rate[z] > seasonality_rate[megistos])
                megistos = z;
        }

        for (z = i; z<16  ; z=z+4) // min year
        {
            if (seasonality_rate[z] < seasonality_rate[megistos])
                elaxistos = z;
        }

        // avg

        for (z = i; z<16  ; z=z+4)
        {
            if (z!=elaxistos && z!=megistos)
            {
                mo[i]=mo[i]+seasonality_rate[z];
            }
        }
        mo[i]=mo[i]/2;
        printf(" The average of Season %d is %f \n",i,mo[i]);
    }
    // GIA NA KANONIKOPOIISO TO APOTELEMSA THA PREPEI NA DIAIRESOUME ME 100 * (4 METRISEIS ANA XRONO) =400
    // The normalized results should be divided by 100*(4 measurements per year)=400
    float sk=(mo[0]+mo[1]+mo[2]+mo[3])/400;

    printf("\n The normalized SK is  %f \n",sk);

    float Deks[4];

    for (i=0; i<4; i++)
    {
        Deks[i]=mo[i]/sk;
        printf("\nThe DEksaminou %d is %f \n",i,Deks[i]);

    }

   ///-----------******************************************--------------STEP 4 -----------******************************************--------------
    printf("\n ******************************************--------------STEP 4 -----------****************************************** \n")  ;

    // DESEASONALISED : We have to divide the actual values by the matching percentages that we found in step 3
    float as[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for (i=0;i<16;i=i+4)
    {
        as[i]=(values[i]/Deks[0])*100;
        as[i+1]=(values[i]/Deks[1])*100;
        as[i+2]=(values[i]/Deks[2])*100;
        as[i+3]=(values[i]/Deks[3])*100;
    }
    printf("DESEASONALISED \n");
     for (i=0;i<16;++i)
    {
        printf("%f \n",as[i]);
    }
///-----------******************************************--------------STEP 5 -----------******************************************--------------
    printf("\n ******************************************--------------STEP 5 -----------****************************************** \n")  ;

///calculating the double center moving overage
float cmaas[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float cmaas3[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for (i=0;i<16;i++)// KMO(3)
    {
    cmaas[i]=(as[i-1]+as[i]+as[i+1])/3;
    }
    for (i=2;i<15;i++)//SEIRA TASIS KIKLOU
    {
    cmaas3[i]=(cmaas[i-1]+cmaas[i]+cmaas[i+1])/3;
    }
    //printf("SEIRA TASIS KIKLOY APOEPOXIKOPOIIMENIS XRONOSEIRAS\n");
     for (i=0;i<16;++i)
    {
        printf("%f \n",cmaas3[i]);
    }





}//end of program







