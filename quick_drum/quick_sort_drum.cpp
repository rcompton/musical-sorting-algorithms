
#include "stk/FileWvOut.h"
using namespace stk;

#include "SortaInstrmnts.h"
#include "print_step.cpp"



#include <vector>



int n=0; //icky
int partition(std::vector<SortaInstrmnt>& A, int left, int right, int pivot, FileWvOut & output, StkFloat fps){

    double pivotValue = A[pivot].sort_value;

    Instrmnt* music = new Drummer();//HevyMetl();//Bowed(57.01);//Saxofony(57.01);//Plucked(57.01);//Drummer();

    StkFrames frame(fps, 1);

    std::vector<SortaInstrmnt> Atemp = A;
    std::swap(A[pivot],A[right]); //don't count this swap as a step?



    if(A[pivot].sort_value == Atemp[pivot].sort_value)
        std::cout << "no change\n";
    else{
        music->noteOn(A[pivot].freq , A[pivot].loudness);
        music->noteOn(A[right].freq , A[right].loudness);
        music->tick(frame);
        output.tick(frame);
        std::cout << "yes change\n";
        print_step(A,n);
        n = n+1;
    }



    //    std::cout << "printing frame " << n << std::endl;

    int store = left;
    for(int i=left; i<right; i++)
        if(A[i].sort_value <= pivotValue){
            Atemp = A;
            //sort makes a swap here so we play noise
            std::swap(A[store],A[i]);


            if(A[i].sort_value == Atemp[i].sort_value)
                std::cout << "no change loop\n";
            else{
                //spec 2 notes and push call them from hit
                music->noteOn(A[store].freq , A[store].loudness);
                music->noteOn(A[i].freq , A[i].loudness);
                music->tick(frame);
                output.tick(frame);

                //for printing
                print_step(A,n);
                //           std::cout << "printing frame " << n << std::endl;
                std::cout << "yes change loop\n";
                n = n+1;
            }



            //for sorting
            store++; 
        }
    Atemp = A;
    std::swap(A[right],A[store]);

    if(A[right].sort_value == Atemp[right].sort_value)
        std::cout << "no change right\n";
    else{
        //spec 2 notes and push call them from hit
        music->noteOn(A[store].freq , A[store].loudness);
        music->noteOn(A[right].freq , A[right].loudness);

        music->tick(frame);
        output.tick(frame);
        print_step(A,n);
        n = n+1;
        std::cout << "yes change right\n";
    }

    //    std::cout << "printing frame " << n << std::endl;
    //    n = n+1;

    return store;
}

void quick_sort_the_place(std::vector<SortaInstrmnt> &A, int left, int right, FileWvOut & output, StkFloat fps){
    if(right > left){
        int newPivot = partition(A, left, right, left, output, fps);
        quick_sort_the_place(A, left, newPivot-1, output, fps);
        quick_sort_the_place(A, newPivot+1, right, output, fps);
    }
    return;
}

