
#include "insertion_sort_drum.cpp"

#include<vector>
#include<cmath>

int main(){

    //There's 10 drums
    //
    //To specify drums you use something like
    //it's MIDI number. It's a lot of fun
    //to figure which MIDI numbers to use...
    //This is just here for easier looping over drums
    std::vector<StkFloat> drum_numbers;
    drum_numbers.push_back(68.0);//bass
    drum_numbers.push_back(90.0);//loTom
    drum_numbers.push_back(112.0);//midTom
    drum_numbers.push_back(136.0);//hiTom
    drum_numbers.push_back(210.0);//cowbell
    drum_numbers.push_back(120.0);//ride
    drum_numbers.push_back(96.0);//hat
    drum_numbers.push_back(75.0);//snare
    drum_numbers.push_back(140.0);//crash
    drum_numbers.push_back(192.0);//tamborine

    //define some necc stk stuff...
    Stk::setSampleRate(44100.0);
    Stk::setRawwavePath("/home/ryan/stk-4.4.1/rawwaves/");

    StkFloat fps = 44100.0/7.0; //denominator frams per sec

    int N=40; //yeah, how many drums to play

    //store all our stuff in a vector
    //that points to lots of drums
    //
    std::vector<SortaInstrmnt> drums;
    for(int i=0;i<N;i++){
        SortaInstrmnt a_drum;
        a_drum.freq = drum_numbers[i%10];
        a_drum.loudness = (1.0*i)/(3.0*N) + 1.0/3.0;//some kinda varying loudness so it's less boring
        a_drum.sort_value = a_drum.freq;

        drums.push_back( a_drum); //push a pointer onto the drum
    }

    //scramble the vector of drums
    std::vector<SortaInstrmnt> temp;
    for(int i=0;i<N;i++){
        int rand_loc = rand()%drums.size();
        temp.push_back( drums[rand_loc]);
        drums.erase( drums.begin() + rand_loc);
    }
    drums = temp;
    //std::cout << drums.size() << "drums size\n";
    FileWvOut output;
    output.openFile("drumChordSort.wav", 1, FileWrite::FILE_WAV, Stk::STK_SINT16);

/* test the Drummer.h
 *
    for(int i=0;i<N;i++){
        Instrmnt* the_drummer;
        the_drummer = new Drummer();
        the_drummer->noteOn(drums[i].freq, .5);

        StkFrames frame(44100/7,1);
        the_drummer->tick(frame);
        output.tick(frame);
    }
*/

    //derr, get our output stuff together

    //do the sort and write to output
    insertion_sort_guitar( drums, output, fps);





    return 0;
}
