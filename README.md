# AmBe_emergent_neutrons

Simulation of AmBe emergent neutrons (based on emergent neutrons simulation code for AmLi by J. Busenitz and R. Sazzad). 

Prerequisite: Geant 4.10.04.p02 and ROOT 5.34/07 (later versions are ok)

Author: Mariia Fedkevych, mariia.fedkevych@gmail.com

1. Download and unpack the AmBe_emergent_neutrons.tar.gz archive, e.g. run "tar -xf AmBe_emergent_neutrons.tar.gz" in Linux terminal
2. Source setup scripts for Geant4, e.g.

source /usr/local/geant4.10.04.p02/bin/geant4.sh
source /usr/local/geant4.10.04.p02/share/Geant4-10.4.2/geant4make/geant4make.sh

3. Go to the AmBe_emergent_gammas folder and run "cmake -DGeant4_DIR=/path/to/local/geant4VersionInstalled/lib64/Geant4.xxxx/ path/to/extracted/source/directory", e.g.
"cmake -DGeant4_DIR=/usr/local/geant4.10.04.p02/lib64/Geant4-10.4.2/ ."

4. Compile with "make" (it will create an executable named "capsule_emissionV2")
5. Prepare an HEPEvt format generator file for AmBe neutron spectrum (from "ambe_neutron.spectrum") which will be read by capsule_emissionV2: 
    - make an executable of am241be_neutron.cc, e.g. run "g++ am241be_neutron.cc -o am241be_neutron.exe" 
    - run the executable (it will generate an output file named "generator.data",) e.g. "./am241be_neutron.exe"
6. The simulations can be executed by running "./capsule_emissionV2 AmBe.mac"
7. The output root file "outcapsule.root" containing energy distributions of primary and detected gammas will be generated within the same folder (the filename and path can be changed in src/ExN03RunAction.cc file). 
8. If you didn't comment out the visualization options in AmBe.mac, it will generate .wrl file in the same folder. 
9. Example .wrl files which visualize the geometry is contained within "geometry_vis_example" subfolder
