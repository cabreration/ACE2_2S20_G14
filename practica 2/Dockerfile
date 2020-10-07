FROM node:8.10.0

RUN mkdir -p /usr/src/app

WORKDIR /usr/src/app

COPY ./ ./

EXPOSE 80

RUN apt install npm

RUN npm install

CMD ["npm","start"]
