# F-SLPA
This repository contains a faster version of SLPA implementation. SLPA, as known as Speaker-Listener Label Propagation Algorithm.

# 社区发现(三)：SLPA算法（标签传播算法拓展）
https://blog.csdn.net/weixin_46348799/article/details/108296675

# run
```bash
cd SLPA_C++v1.3
make
./SLPA -i ../input/test.e -t 10 -M 10 -d ../output/
```
其它参数：
```
There are more options you can try:
    -r a specific threshold in [0,0.5) 
    -run number ofrepetitions 
    -d output directory
    -L set to 1 to use only the largest connected component 
    -t maximum iteration(default:100)
    -ov set to 0 to perform disjoint detection
    -M number of threads(C++,multi-threading)
```
更多运行介绍见：[pdf](./SLPA_C++v1.3/Readme.pdf)