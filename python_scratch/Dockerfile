FROM ubuntu:22.04

ENV NO_AT_BRIDGE=1

RUN apt-get -y update && apt-get upgrade -y
RUN apt-get install -y \
                python3 \
                python3-pip \
                picocom \
                git

# Set work directory
WORKDIR /app

COPY requirements.txt /app/requirements.txt
RUN pip3 install -r /app/requirements.txt

# Copy rest of the source files
COPY . /app
