
#include "stk/FileWvOut.h"
using namespace stk;

#include "SortaInstrmnts.h"
#include "print_step.cpp"



#include <vector>


/*
 * Insertion sort Wikipedia code...
 *
 void insertionSort(vector<double> &A){
    double value;
    int j;
    for(int i=0; i<A.size(); i++){
        value = A[i];
        j = i-1;
        //note that we get out of bounds error
        //when j=-1 if we put A[j]>value as first condidtion
        while(j>=0 && A[j] > value){
            A[j+1] = A[j];
            j = j-1;
        }
        A[j+1] = value;
    }
    return;
}
*/



/* Insertion sort
 * input A vector of instrument specifiers
 * output is a reference to the audio stream we're writing to
 * fps is frames-per-second
 */
void insertion_sort_guitar(std::vector<SortaInstrmnt> &A, FileWvOut &output, StkFloat fps){
    //keep track of what to print
    int curr_step=0;
    //define some necc stk stuff...
    Stk::setSampleRate(44100.0);
    Stk::setRawwavePath("/home/ryan/stk-4.4.1/rawwaves/");



//    std::cout << curr_step << " curr_step\n";

    SortaInstrmnt temp_value;//placeholder for sorting
    int j;//placeholder for location of where to swap
    Instrmnt* the_guitar; //make an Instrmnt* for whatever we're playing
    the_guitar = new Drummer();//Saxofony(57.01);//new Plucked(57.01); //use the_guitar to play notes to the output stream, for some reason STK likes pointers...


    //regular musical insertion sort
    for(unsigned int i=0; i<A.size(); i++){
        temp_value = A[i];
        j = i-1;
        
        std::cout << j << " j\n";
        std::cout << temp_value.sort_value << " value\n";
        //loop to insert next value into the list
        //at the proper place
        //We order instrument specifiers by their
        //"sort_value"
        while( j>=0 && A[j].sort_value > temp_value.sort_value ){
            std::cout << A[j].sort_value << " A[j]\n";
            A[j+1] = A[j]; //swap the instrumets, not just "sort_value"

            //This part is specific to making noise
            //spec 2 notes and push call them from hit
            StkFrames frame(fps,1); //need 2 channels for chords... or 1
            the_guitar->noteOn(A[j].freq , A[j].loudness);
            the_guitar->noteOn(A[j+1].freq , A[j+1].loudness);

            //tick the sounds into a frame
            //then that frame to out
            the_guitar->tick(frame);
            output.tick(frame);

            //This part prints the current state of the array
            //to a file on disk
            std::cout << "printing frame " << curr_step << std::endl;
            print_step(A, curr_step);

            //done shifting stuff up
            curr_step++;
            j = j-1;

        }//end while

        A[j+1] = temp_value; //switch the last guy now

        //make the noise for when we switch the last guy
        //This part is specific to making noise
        //spec 2 notes and push call them from hit
        StkFrames frame(fps,1); //need 2 channels for chords...
        the_guitar->noteOn(A[i].freq , A[i].loudness);
        std::cout << "ticked\n";
        the_guitar->noteOn(A[j+1].freq , A[j+1].loudness);

        the_guitar->tick(frame);
        output.tick(frame);

        //make the ouput file for when we switch the last guy
        print_step(A, curr_step);
        std::cout << "printing frame " << curr_step << std::endl;
        curr_step++;

    }//end for

    return;
}

