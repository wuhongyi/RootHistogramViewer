# ROOT Histogram Viewer
This program allows users to view histograms in a [ROOT](https://root.cern.ch/) file. Users can read histograms while another program fills the ROOT file. 

列表显示 ROOT 文件中的 TH1/TH2/TH3，通过点击快速查看结果。

# Prerequisites
* cmake 2.6 +
* ROOT 6.00 +

# Installation
1. Create a build directory : `mkdir build`
2. Change to the build directory : `cd build`
3. Build the project : `cmake ../`
4. Make the project : `sudo make -j8`

# 版本修订

- 20190202 
	- 修复打开新文件后，没有清除之前hist信息的问题
	- 支持任意类型的TH1/TH2/TH3，支持任意 name
	
