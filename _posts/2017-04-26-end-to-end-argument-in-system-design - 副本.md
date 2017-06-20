---
layout: post
title: end to end argument in system design
tags: system design
categories: system design
---

## basis for a class of arguments
从通讯系统的角度来看，该功能模块能够也只能被该应用完成。因此，通讯系统将该功能作为一个子模块是没有办法实现的（有时候通讯系统实现的该功能不完备的版本可能会带来一部分的性能增强）。

## end-to-end caretaking
以"文件传输"模块为例，主要有以下5个步骤：<br>
1.运行在HostA上的程序调用文件系统读取文件，这些文件存储在几个磁道上，文件系统将这些文件以磁盘格式无关的固定块传给程序；<br>
2.运行在HostA上的程序调用数据通讯子模块，通过某种通讯协议，将文件以固定大小的包传输出去，通常包的大小与磁盘的大小和文件块的大小都不一样；<br>
3.数据通讯网络将数据包从HostA传输到HostB；<br>
4.HostB上的通讯模块将数据包中的额外信息去除，并将有效数据传送给运行在HostB上的程序；<br>
5.运行在HostB上的程序将数据写入文件系统；<br>