# Memory Analysis Environment for HEVC and VVC Test Models

A Docker container to perform memory analyses on an isolated environment.

## Instructions

### Prerequisites

The only tools needed to run this container is Docker and git.

### Running the container

First you need to clone the repository to your local machine

```
git clone https://github.com/arthurcerveira/Video-Memory-Analysis-Environment.git
```

Then you'll need to create a directory `video_sequences` to store the videos(.yuv).

```
cd Video-Memory-Analysis-Environment
mkdir video_sequences
```

To build the container and start the analysis you need to run the following commands

```
docker build -t mem-analysis .
docker run -it --name running-mem mem-analysis
```

Once the execution is over you can get the results through [docker cp](https://docs.docker.com/engine/reference/commandline/cp/ "docker cp").

The default output is `automate_trace_output.txt` in the `Custom-Simulator` directory.

## Settings

The settings used for the analysis can be found in `Custom-Simulator/custom_simulator.py`.

The default values are:

```python
# Routines
AUTOMATE_TRACE = True
GENERATE_TRACE_GRAPH = False
GENERATE_BLOCK_GRAPH = False

AUTOMATE_VTUNE = False
GENERATE_VTUNE_GRAPH = False

# Trace Reader
AUTOMATE_TRACE_OUTPUT = "automate_trace_output.txt"

# Vtune Reader
AUTOMATE_VTUNE_OUTPUT = "automate_vtune_output.txt"

# Encoder Paths
HM = "../hm-videomem/"
VTM = "../vtm-mem/"

HEVC = True
VVC = True

ENCODER_CMD = dict()

CONFIG = {"HEVC": {"Low Delay": HM + "cfg/encoder_lowdelay_main.cfg",
                   "Random Access": HM + "cfg/encoder_randomaccess_main.cfg"},
          "VVC": {"Low Delay": VTM + "cfg/encoder_lowdelay_vtm.cfg",
                  "Random Access": VTM + "cfg/encoder_randomaccess_vtm.cfg"}}
VIDEO_CFG_PATH = {"HEVC": HM + "cfg/per-sequence/",
                  "VVC": VTM + "cfg/per-sequence/"}

VIDEO_SEQUENCES_PATH = "../video_sequences"

# Parameters
FRAMES = '17'
SEARCH_RANGE = ['96']
```

## Running the image on DockerHub

The image on DockerHub uses the default settings and the video sequence BQSquare.

```
docker container run arthurcerveira/video-memory-analysis:1.0
```
