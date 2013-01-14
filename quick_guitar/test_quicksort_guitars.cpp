
#include "quick_sort_guitar.cpp"

#include<vector>
#include<cmath>

int main(){

    //define some necc stk stuff...
    Stk::setSampleRate(44100.0);
    Stk::setRawwavePath("/home/ryan/stk-4.4.1/rawwaves/");

    StkFloat fps = 44100.0/4.0; //denominator frams per sec

    int N=50; //yeah, how many guitars to play
    
    //store all our stuff in a vector
    //that points to lots of guitars
    std::vector<SortaInstrmnt> guitars;
    for(int i=0;i<N;i++){
        SortaInstrmnt a_guitar;
        a_guitar.freq = 60+i*5;//0 + 220.0*pow(2.0, (double) i/12.0); //different pitches
        a_guitar.loudness = .5;//log( (double) i/N +1);
        a_guitar.sort_value = a_guitar.freq;

        guitars.push_back( a_guitar); //push a pointer onto the guitar
    }

    //scramble the vector of guitars
    std::vector<SortaInstrmnt> temp;
    for(int i=0;i<N;i++){
        int rand_loc = rand()%guitars.size();
        temp.push_back( guitars[rand_loc]);
        guitars.erase( guitars.begin() + rand_loc);
    }
    guitars = temp;
    //std::cout << guitars.size() << "guitars size\n";

//    for(int i=0;i<N;i++)
//        std::cout << guitars[i].sort_value << "\n";


    //derr, get our output stuff together
    FileWvOut output;
    output.openFile("guitarChordSort.wav", 1, FileWrite::FILE_WAV, Stk::STK_SINT16);

    //do the sort and write to output
    quick_sort_the_place(guitars, 0, guitars.size()-1, output, fps);



    return 0;
}
