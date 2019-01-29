#!/bin/bash
export IFT_DEBUG=1
make iftDetectIris
./iftDetectIris test weakClassifier.txt
