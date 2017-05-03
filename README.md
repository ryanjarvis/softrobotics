# Code Sample for SoftRobotics

This was built and tested on OSX 10.11.6, NodeJS 7.7.1 and an Arduino Uno v3

This project illustrates how a website can be used to rotate a servo in realtime on an Arduino using WebSockets and serial communication.  This is accomplished by writing a custom Node addon in C++11/Boost and connecting an Arduino to the same machine that the remote webserver is on.

## sketch.cpp
This is the source code to be deployed to an Arduino Uno v3

## arduino.cpp
This is a Node addon that allows NodeJS to connect and send serial messages to a locally connected Arduino.  Must be compiled with node-gyp

## server.js
This is a NodeJS web server written in Koa that provides static hosting as well as a websocket connection at `/socket`

## public/
This folder contains a browser application and demonstrates basic WebSockets client functionality
