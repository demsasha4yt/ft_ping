## RUN

```ruby
docker-machine create --driver virtualbox default
eval "$(docker-machine env default)"
docker-compose build
docker-compose run app bash
```