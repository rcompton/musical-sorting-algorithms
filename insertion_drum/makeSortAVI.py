#! /usr/bin/env python

import Gnuplot,string,glob,re,os,subprocess

#os.system("g++ -Wall -D__LITTLE_ENDIAN__ -I/usr/include/stk -o musical_quick_sort musical_quick_sort.cpp -lstk -lpthread -lasound -lm")

#os.system("./musical_quick_sort")

#this function plots the data file currdata with number gen
def create_plot(currdata,gen):
    g = Gnuplot.Gnuplot(debug=1)
    g.title('Plot of data ' + str(gen)) # (optional)
    #g('set yrange[0:1]')
    g('set term png')
    g('set output  "'+ str(gen) + '.png"')
    g('set style data points')
    g.plot(currdata)

#this thing makes a list of everything called .dat
filenames = glob.glob("*.dat")
filenames = sorted(filenames)
#countGifula=0 #ounts the number of gifs made
stringOfNames = ""
for a in filenames:
    plotJunk = Gnuplot.PlotItems.File(a)
    name = re.sub(".dat","",a)
    create_plot(plotJunk,name)
#    countGifula = countGifula +1
    namegif = re.sub("dat","gif",a)
    stringOfNames += str(namegif) +" "

print(stringOfNames)

command = ('mencoder',
           'mf://*.png',
           '-mf',
           'type=png:w=800:h=600:fps=7.0',
           '-ovc',
           'lavc',
           '-lavcopts',
           'vcodec=mpeg4',
           '-oac',
           'copy',
           '-o',
           'output.avi')

#os.spawnvp(os.P_WAIT, 'mencoder', command)

print "\n\nabout to execute:\n%s\n\n" % ' '.join(command)
subprocess.check_call(command)

print "\n\n The movie was written to 'output.avi'"

print "\n\n You may want to delete *.png now.\n\n"


os.system(" mencoder -ovc copy -audiofile drumChordSort.wav -oac copy output.avi -o video_new.avi")
#os.system(" mencoder -ovc copy -audiofile musicalSampleQuickSorted.wav -oac copy output.avi -o video_new.avi")

os.system("rm *.dat")
os.system("rm *.png")
