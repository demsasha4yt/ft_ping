## RUN

```docker-machine create --driver virtualbox default
eval "$(docker-machine env default)"
docker-compose run app sh```