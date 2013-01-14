
#include<vector>
#include<fstream>
#include<iomanip>

//make a file with the vector to print
//readable by gnuplot
template<typename T>
void print_step( const std::vector<T> &v, int m){
    std::ofstream fout;
    //some crap to make the int a string
    std::string s;
    std::stringstream out;
    out << std::setfill('0')<<std::setw(4) << m;
    s = out.str();
    s += ".dat";
    fout.open(s.c_str());

    for(int i=0;i<v.size();i++)
        fout << v[i].sort_value << std::endl;
    std::cout << "made file " << m << std::endl;

    fout.close();
    return;
}

