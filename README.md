# FT_PING
Собственная реализация утилиты ping по проекту ft_ping в школе программирования 21.


## RUN

```ruby
docker-machine create --driver virtualbox default
eval "$(docker-machine env default)"
docker-compose build
docker-compose run app bash
```

## Inside VM
```ruby
make
./ft_ping [-v] host
```

## Refs
*ICMP* - https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol

*Ping* - https://ru.wikipedia.org/wiki/Ping

*Internet protocol checksum* - https://tools.ietf.org/html/rfc1071

*tcpdump* - https://ru.wikipedia.org/wiki/Tcpdump
