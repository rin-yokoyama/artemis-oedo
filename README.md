# artemis-oedo
artemis working directory for OEDO/SHARAQ experiments

## Installation
- Install cmake version of artemis (currently available at https://github.com/artemis-dev/artemis.git -b develop).
- Set artemis environment.
```
source thisartemis.sh
```
OR
```
module load artemis
```
- Create art_analysis directory in your home directory and make a copy of artlogin.sh there.
- Rename it to .artlogin.sh
- Add a function named artlogin in your shell as follows
```
function artlogin()
{
    export ART_ANALYSIS_DIR=$HOME/art_analysis #: the directory for analysis (ex. art_$
    export ART_USER_REPOS=https://github.com/rin-yokoyama/artemis-oedo.git # : the local or remote repositor$
    export ART_DATA_DIR=[path_to_data_dir] # data directory
    . $ART_ANALYSIS_DIR/.artlogin.sh $1
}
```
-
```
artlogin [user_name]
```
will create an directory in art_analysis/user/[user_name]. It will automatically setup the environment for artemis-oedo

### If you want to personally install artemis-oedo by hand
- Clone this repository and use cmake to build.
```
git clone https://github.com/rin-yokoyama/artemis-oedo.git
cd artemis-oedo
mkdir build
cd build
cmake ..
make install
```
- Set environment.
```
cd ..
source thisartemis-oedo.sh
```
You should be ready to use artemis with the oedo library now.

## Parquet output option
To enable parquet output, turn on the `BUILD_PARQUET` option in cmake. (Go to the build directory and call `cmake .. -DBUILD_PARQUET=ON`.)
Follow the instructions on https://arrow.apache.org/install to install arrow and parquet C++ packages beforehand.
If you make install in the build dir with this option, an executable named DumpParquet will be created.
```
Usage:
DumpParquet -i [input_file_name] (-o [output_file_name])
```
Edit analysis/DumpParquet.cpp to change which branches to dump.
You need to have a corresponding DataBuilder class in src-parquet/ for each artemis data class.

Currently, following classes are supported.
- TEventHeader
- TSimpleData
- TTimingChargeData
- TSRPPACPlaneData
- TMWDCHitData
- TTrackingResultData

