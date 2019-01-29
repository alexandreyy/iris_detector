#!/bin/bash
make clean
export IFT_DEBUG=1
make iftTrainForIrisDetection
./iftTrainForIrisDetection train weakClassifier.txt
