FROM alpine
WORKDIR home/
RUN apk add build-base
RUN apk add vim
RUN apk add --no-cache git
RUN apk add gcc
RUN git clone https://github.com/the-florist/wordle.git
