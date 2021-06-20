# Compare Videos

A tool to compare two videos side-by-side, and time segments within them.

## Building

This application depends on OpenCV.

```
mkdir build
cd build
cmake ..
make
```

## Usage

```
./main /path/to/video1 /path/to/video2
```

Click on a video feed to select it.
Press `Space` to play/pause the selected video feed, or `a` or `d` to step back/forwards by a single frame.
Press `s` to set the mark to the current frame of the video. Press `q` to quit.