Monte Carlo Generators and Plotting Macros

How to use:
clone into CMSSW_5_3_20/src/
call cmsenv
navigate to the test directory under one QPythiaInerface, JewelInterface, or YajemInterface which are located under GeneratorInterface/

call cmsRun  test<rest of name>.py

This will generate a .root file of the ouput which can be analyzed and plotted with the macros in Macros/ folder. 
The above steps run the model with the default parameters, in order to modify these parameters change the code of .py files or the file DijetNtupleProducer.cc which is located in the HIGenerator/src/ directory. After modifying the Dijet file you will need to recompile. Do this by navigating to MonteCarlo/ and calling "scram b -j(# of cores)"

Description of different parameters:




