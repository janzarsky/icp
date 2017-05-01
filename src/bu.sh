#!/bin/bash
date=`date '+%m-%d---%H-%M'`

mkdir backups/${date}
cp *.cpp backups/${date}
cp *.hpp backups/${date}

