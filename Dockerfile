FROM debian:8

RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y make gcc
WORKDIR "/app"
