LIBS=`root-config --libs`
CFLAGS=`root-config --cflags`
CC=g++

#set compliler options
#	-g = debugging
#	-O# = optimisation
COPT=-g

default:
	$(CC) $(COPT) src/TTgammaPlottingTools.cpp src/GlobalVariables.cpp src/Samples/AllSamples.cpp src/Samples/AllSamples2D.cpp src/Samples/Sample.cpp src/Samples/Sample2D.cpp src/Variables/Variable.cpp src/Variables/Variable2D.cpp src/Objects/CutFlow.cpp  src/Objects/DiLepton.cpp  src/Objects/Jets.cpp  src/Objects/MET.cpp  src/Objects/Object.cpp  src/Objects/Photons.cpp  src/Objects/Fit.cpp src/Objects/TdrStyle.cpp  -o TTgammaPlottingTools $(LIBS) $(CFLAGS)
	
clean:
	rm -rf *o TTgammaPlottingTools
