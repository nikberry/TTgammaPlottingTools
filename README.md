Instructions for using Phil's amazing TTgammaPlottingTools!
These save time and are much easier to use than the scripts

Step-by-step guide:

1. Fork the tools from git and clone it into a folder from src/ for example:
git clone  https://github.com/<user>/TTgammaPlottingTools.git TTgammaPlottingTools

2. Need to hadd files (if not done already, has been done for latest version V7
of files) such that DY, SingleTop and QCD are merged (makes things
easier):
./addFiles.sh <folder_where_root_files_are_located>

3. Set up folders where plots are stored:
source makedirs

4. Compile Phil's amazing TTgammaPlottingTools:
make

5. Run Phil's amazing TTgammaPlottingTools:
./TTgammaPlottingTools

6. Admire as all the plots are being produced!

***************************************************************************
Bonus tits:
***************************************************************************
A) To turn off any plots you can comment out the specific object in:
src/TTgammaPlottingTools.cpp
***************************************************************************
B) To add more histograms you can add these in for a specific object... e.g in
for Photons edit: src/Objects/Photons.cpp
To add an additional variable all that needs to be done is to add a new variable
specifying:
Variable::Variable(TString name_temp, TString xTitle_temp, double minX_temp, double maxX_temp, int rebinFact_temp)

where: 
TString name_temp: is the variable name to be read from the root file
TString xTitle_temp: Is the X-axis title
double minX_temp: is the minimum value on the x-axis
double maxX_temp: is the maximum value on the x-axis
int rebinFact_temp: the rebin factor

For example:
Variable photon_pt("Photon_ET", "Photon E_{T} [GeV]", 0, 150, 2);

To save the plot you then have to specify the selection and channel you want
e.g:
setSelectionAndChannel("TTbarDiLeptonAnalysis", "MuMu");
and then do:
savePlot(samples, met);
to save.
***************************************************************************
C) In src/GlobalVariables.cpp you can specify whether to:
bool Globals::addRatioPlot = true;
bool Globals::addHashErrors= true;    
bool Globals::addOverFlow = true;
bool Globals::doLogPlot = false;

Hopefully these are self explanitory
***************************************************************************
			ENJOY!
***************************************************************************			
