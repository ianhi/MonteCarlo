===================================README======================================
#Monte Carlo Generators and Plotting Macros

How to set up:
    cd  CMSSW_5_3_20/src/
    git clone git@github.com:ianhi/MonteCarlo.git //FOR HTTPS use:  https://github.com/ianhi/MonteCarlo.git 
    cd MonteCarlo/
    scram b -j(# of cores) // compile

How to use:

1. Call cmsenv in src/

2. Navigate to one of:
   	    GeneratorInterface/JewelInterface/test/
	    GeneratorInterface/YajemInterface/test/
	    GeneratorInterface/QPythiaInterface/test/
3. Call cmsrRun test<rest of name>.py on the file corresponding to the model you wish use.

4. Use the Macros in MonteCarlo/Macros/ to analyze the root file output from step 3.


How to Modify Model Parameters

There are two places in which parameters are set: The .py file you are using and DijetNtupleProducer.cc
      1. Modify parameters in .py 
      	 open the .py file and change the parameters as you wish. This is where you can change the number of events
      
      2. Modify parameters in DijetNtupleProducer.cc
      	 File contained in MonteCarlo/JetNtupleProducer/src/
	 Change parameters and save
	 Call scram b to recompile


Description of different parameters:




How this was built:
1. Created MonteCarlo/ directory under CMSSW_5_3_20/src/
2. Created a GeneratorInterface directory under MonteCarlo
3. Moved the YajemInterface, JewelInterface, QPythiaInterface directories in the cmssw folder from https://github.com/yenjie/HIGenerator.git to the GeneratorInterface/.
4. Moved the JetNtupleProducer/ from cmssw folder to MonteCarlo/.
5. cmsenv;scram b -j20

The above steps create the necessary GeneratorInterface folder and ensure that BuildFile.xml is two levels inside src/ so that it can be compiled.

==================================================================================

