#include "cusplot.h"
#include "ui_cusplot.h"
#include <memory.h>
#include <QDebug>

void cusplot::qvectorToDouble(double* copy){
    if(coordinateY.isEmpty() == true)
        throw ("Input vector is empty. Please init data");
    else{
        for(int i = 0; i<coordinateY.size(); i++){
            copy[i] = coordinateY[i];
        }
    }
}
void cusplot::doubleToQvector(double* signal){
    if(coordinateY.isEmpty() == true)
        throw ("Input vector is empty. Please init data");
    else{
        if(!outputMedian.isEmpty())
            clearQVector(outputMedian);

        if(outputMedian.isEmpty() == true){
            for(int i = 0; i<coordinateY.size(); i++){
                outputMedian.push_back(signal[i]);
                //coordinateY[i] = outputMedian[i];
            }
        }
    }
}

void cusplot::initMedianFilter(){
    if(coordinateY.isEmpty() == true)
        throw ("Input vector is empty. Please init data");
    else{
        double signal[coordinateY.size()],result[coordinateY.size()];

        qvectorToDouble(signal);

        medianfilter(signal,result,coordinateY.size());

        doubleToQvector(result);
    }
}

void cusplot::_medianfilter(const double* signal, double* result, int N)
{
   //   Move window through all elements of the signal
   for (int i = 2; i < N - 2; ++i)
   {
      //   Pick up window elements
      double window[5];
      for (int j = 0; j < 5; ++j)
         window[j] = signal[i - 2 + j];
      //   Order elements (only half of them)
      for (int j = 0; j < 3; ++j)
      {
         //   Find position of minimum element
         int min = j;
         for (int k = j + 1; k < 5; ++k)
            if (window[k] < window[min])
               min = k;
         //   Put found minimum element in its place
         const double temp = window[j];
         window[j] = window[min];
         window[min] = temp;
      }
      //   Get result - the middle element
      result[i - 2] = window[2];
   }
}

void cusplot::medianfilter(double* signal, double* result, int N)
{

   if (!signal || N < 1)
      return;

   if (N == 1)
   {
      if (result)
         result[0] = signal[0];
      return;
   }

   double* extension = new double[N + 4];

   if (!extension)
      return;

   memcpy(extension + 2, signal, N * sizeof(double));
   for (int i = 0; i < 2; ++i)
   {
      extension[i] = signal[1 - i];
      extension[N + 2 + i] = signal[N - 1 - i];
   }

   _medianfilter(extension, result ? result : signal, N + 4);

   delete[] extension;
}
